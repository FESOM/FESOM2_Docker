#include "mpi.hpp"
#include <map>
#include "cputime.hpp"       /* time */
#include "meshutil.hpp"
#include "polyg.hpp"
#include "circle.hpp"
#include "intersect.hpp"
#include "intersection_ym.hpp"
#include "errhandle.hpp"
#include "mpi_routing.hpp"
#include "gridRemap.hpp"

#include "mapper.hpp"

namespace sphereRemap {

/* A subdivition of an array into N sub-arays
   can be represented by the length of the N arrays
   or by the offsets when each of the N arrays starts.
   This function convertes from the former to the latter. */
void cptOffsetsFromLengths(const int *lengths, int *offsets, int sz)
{
  offsets[0] = 0;
  for (int i = 1; i < sz; i++)
    offsets[i] = offsets[i-1] + lengths[i-1];
}


void Mapper::setSourceMesh(const double* boundsLon, const double* boundsLat, const double* area, int nVertex, int nbCells, const double* pole, const long int* globalId)
{
  srcGrid.pole = Coord(pole[0], pole[1], pole[2]);

  int mpiRank, mpiSize;
  MPI_Comm_rank(communicator, &mpiRank);
  MPI_Comm_size(communicator, &mpiSize);

  sourceElements.reserve(nbCells);
  sourceMesh.reserve(nbCells);
  sourceGlobalId.resize(nbCells) ;

  if (globalId==NULL)
  {
    long int offset ;
    long int nb=nbCells ;
    MPI_Scan(&nb,&offset,1,MPI_LONG,MPI_SUM,communicator) ;
    offset=offset-nb ;
    for(int i=0;i<nbCells;i++) sourceGlobalId[i]=offset+i ;
  }
  else sourceGlobalId.assign(globalId,globalId+nbCells);

  for (int i = 0; i < nbCells; i++)
  {
    int offs = i*nVertex;
    Elt elt(boundsLon + offs, boundsLat + offs, nVertex);
    elt.src_id.rank = mpiRank;
    elt.src_id.ind = i;
    elt.src_id.globalId = sourceGlobalId[i];
    sourceElements.push_back(elt);
    sourceMesh.push_back(Node(elt.x, cptRadius(elt), &sourceElements.back()));
    cptEltGeom(sourceElements[i], Coord(pole[0], pole[1], pole[2]));
    if (area!=NULL) sourceElements[i].given_area=area[i] ;
    else sourceElements[i].given_area=sourceElements[i].area ;
  }

}

void Mapper::setTargetMesh(const double* boundsLon, const double* boundsLat, const double* area, int nVertex, int nbCells, const double* pole, const long int* globalId)
{
  tgtGrid.pole = Coord(pole[0], pole[1], pole[2]);

  int mpiRank, mpiSize;
  MPI_Comm_rank(communicator, &mpiRank);
  MPI_Comm_size(communicator, &mpiSize);

  targetElements.reserve(nbCells);
  targetMesh.reserve(nbCells);

  targetGlobalId.resize(nbCells) ;
  if (globalId==NULL)
  {
    long int offset ;
    long int nb=nbCells ;
    MPI_Scan(&nb,&offset,1,MPI_LONG,MPI_SUM,communicator) ;
    offset=offset-nb ;
    for(int i=0;i<nbCells;i++) targetGlobalId[i]=offset+i ;
  }
  else targetGlobalId.assign(globalId,globalId+nbCells);

  for (int i = 0; i < nbCells; i++)
  {
    int offs = i*nVertex;
    Elt elt(boundsLon + offs, boundsLat + offs, nVertex);
    targetElements.push_back(elt);
    targetMesh.push_back(Node(elt.x, cptRadius(elt), &sourceElements.back()));
    cptEltGeom(targetElements[i], Coord(pole[0], pole[1], pole[2]));
    if (area!=NULL) targetElements[i].given_area=area[i] ;
    else targetElements[i].given_area=targetElements[i].area ;
  }


}

void Mapper::setSourceValue(const double* val)
{
  int size=sourceElements.size() ;
  for(int i=0;i<size;++i) sourceElements[i].val=val[i] ;
}

void Mapper::getTargetValue(double* val)
{
  int size=targetElements.size() ;
  for(int i=0;i<size;++i) val[i]=targetElements[i].val ;
}

vector<double> Mapper::computeWeights(int interpOrder, bool renormalize, bool quantity)
{
  vector<double> timings;
  int mpiSize, mpiRank;
  MPI_Comm_size(communicator, &mpiSize);
  MPI_Comm_rank(communicator, &mpiRank);

  this->buildSSTree(sourceMesh, targetMesh);

  if (mpiRank == 0 && verbose) cout << "Computing intersections ..." << endl;
  double tic = cputime();
  computeIntersection(&targetElements[0], targetElements.size());
  timings.push_back(cputime() - tic);

  tic = cputime();
  if (interpOrder == 2) {
    if (mpiRank == 0 && verbose) cout << "Computing grads ..." << endl;
    buildMeshTopology();
    computeGrads();
  }
  timings.push_back(cputime() - tic);

  /* Prepare computation of weights */
  /* compute number of intersections which for the first order case
           corresponds to the number of edges in the remap matrix */
  int nIntersections = 0;
  for (int j = 0; j < targetElements.size(); j++)
  {
    Elt &elt = targetElements[j];
    for (list<Polyg*>::iterator it = elt.is.begin(); it != elt.is.end(); it++)
      nIntersections++;
  }
  /* overallocate for NMAX neighbours for each elements */
  remapMatrix = new double[nIntersections*NMAX];
  srcAddress = new int[nIntersections*NMAX];
  srcRank = new int[nIntersections*NMAX];
  dstAddress = new int[nIntersections*NMAX];
  sourceWeightId =new long[nIntersections*NMAX];
  targetWeightId =new long[nIntersections*NMAX];


  if (mpiRank == 0 && verbose) cout << "Remapping..." << endl;
  tic = cputime();
  nWeights = remap(&targetElements[0], targetElements.size(), interpOrder, renormalize, quantity);
  timings.push_back(cputime() - tic);

  for (int i = 0; i < targetElements.size(); i++) targetElements[i].delete_intersections();

  return timings;
}

/**
   @param elements are cells of the target grid that are distributed over CPUs
          indepentently of the distribution of the SS-tree.
   @param nbElements is the size of the elements array.
   @param order is the order of interpolaton (must be 1 or 2).
*/
int Mapper::remap(Elt *elements, int nbElements, int order, bool renormalize, bool quantity)
{
  int mpiSize, mpiRank;
  MPI_Comm_size(communicator, &mpiSize);
  MPI_Comm_rank(communicator, &mpiRank);

  /* create list of intersections (super mesh elements) for each rank */
  multimap<int, Polyg *> *elementList = new multimap<int, Polyg *>[mpiSize];
  for (int j = 0; j < nbElements; j++)
  {
    Elt& e = elements[j];
    for (list<Polyg *>::iterator it = e.is.begin(); it != e.is.end(); it++)
      elementList[(*it)->id.rank].insert(pair<int, Polyg *>((*it)->id.ind, *it));
  }

  int *nbSendElement = new int[mpiSize];
  int **sendElement = new int*[mpiSize]; /* indices of elements required from other rank */
  double **recvValue = new double*[mpiSize];
  double **recvArea = new double*[mpiSize];
  double **recvGivenArea = new double*[mpiSize];
  Coord **recvGrad = new Coord*[mpiSize];
  GloId **recvNeighIds = new GloId*[mpiSize]; /* ids of the of the source neighbours which also contribute through gradient */
  for (int rank = 0; rank < mpiSize; rank++)
  {
    /* get size for allocation */
    int last = -1; /* compares unequal to any index */
    int index = -1; /* increased to starting index 0 in first iteration */
    for (multimap<int, Polyg *>::iterator it = elementList[rank].begin(); it != elementList[rank].end(); ++it)
    {
      if (last != it->first)
        index++;
      (it->second)->id.ind = index;
      last = it->first;
    }
    nbSendElement[rank] = index + 1;

    /* if size is non-zero allocate and collect indices of elements on other ranks that we intersect */
    if (nbSendElement[rank] > 0)
    {
      sendElement[rank] = new int[nbSendElement[rank]];
      recvValue[rank]   = new double[nbSendElement[rank]];
      recvArea[rank]    = new double[nbSendElement[rank]];
      recvGivenArea[rank] = new double[nbSendElement[rank]];
      if (order == 2)
      {
        recvNeighIds[rank] = new GloId[nbSendElement[rank]*(NMAX+1)];
        recvGrad[rank]    = new Coord[nbSendElement[rank]*(NMAX+1)];
      }
      else
        recvNeighIds[rank] = new GloId[nbSendElement[rank]];

      last = -1;
      index = -1;
      for (multimap<int, Polyg *>::iterator it = elementList[rank].begin(); it != elementList[rank].end(); ++it)
      {
        if (last != it->first)
          index++;
        sendElement[rank][index] = it->first;
        last = it->first;
      }
    }
  }

  /* communicate sizes of source elements to be sent (index lists and later values and gradients) */
  int *nbRecvElement = new int[mpiSize];
  MPI_Alltoall(nbSendElement, 1, MPI_INT, nbRecvElement, 1, MPI_INT, communicator);

  /* communicate indices of source elements on other ranks whoes value and gradient we need (since intersection) */
  int nbSendRequest = 0;
  int nbRecvRequest = 0;
  int **recvElement = new int*[mpiSize];
  double **sendValue = new double*[mpiSize];
  double **sendArea = new double*[mpiSize];
  double **sendGivenArea = new double*[mpiSize];
  Coord **sendGrad = new Coord*[mpiSize];
  GloId **sendNeighIds = new GloId*[mpiSize];
  MPI_Request *sendRequest = new MPI_Request[5*mpiSize];
  MPI_Request *recvRequest = new MPI_Request[5*mpiSize];
  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbSendElement[rank] > 0)
    {
      MPI_Issend(sendElement[rank], nbSendElement[rank], MPI_INT, rank, 0, communicator, &sendRequest[nbSendRequest]);
      nbSendRequest++;
    }

    if (nbRecvElement[rank] > 0)
    {
      recvElement[rank] = new int[nbRecvElement[rank]];
      sendValue[rank]   = new double[nbRecvElement[rank]];
      sendArea[rank]   = new double[nbRecvElement[rank]];
      sendGivenArea[rank] = new double[nbRecvElement[rank]];
      if (order == 2)
      {
        sendNeighIds[rank] = new GloId[nbRecvElement[rank]*(NMAX+1)];
        sendGrad[rank]    = new Coord[nbRecvElement[rank]*(NMAX+1)];
      }
      else
      {
        sendNeighIds[rank] = new GloId[nbRecvElement[rank]];
      }
      MPI_Irecv(recvElement[rank], nbRecvElement[rank], MPI_INT, rank, 0, communicator, &recvRequest[nbRecvRequest]);
      nbRecvRequest++;
    }
  }
  MPI_Status *status = new MPI_Status[5*mpiSize];
  
  MPI_Waitall(nbSendRequest, sendRequest, status);
        MPI_Waitall(nbRecvRequest, recvRequest, status);

  /* for all indices that have been received from requesting ranks: pack values and gradients, then send */
  nbSendRequest = 0;
  nbRecvRequest = 0;
  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbRecvElement[rank] > 0)
    {
      int jj = 0; // jj == j if no weight writing
      for (int j = 0; j < nbRecvElement[rank]; j++)
      {
        sendValue[rank][j] = sstree.localElements[recvElement[rank][j]].val;
        sendArea[rank][j] = sstree.localElements[recvElement[rank][j]].area;
        sendGivenArea[rank][j] = sstree.localElements[recvElement[rank][j]].given_area;
        if (order == 2)
        {
          sendGrad[rank][jj] = sstree.localElements[recvElement[rank][j]].grad;
//          cout<<"grad  "<<jj<<"  "<<recvElement[rank][j]<<"  "<<sendGrad[rank][jj]<<" "<<sstree.localElements[recvElement[rank][j]].grad<<endl ;
          sendNeighIds[rank][jj] = sstree.localElements[recvElement[rank][j]].src_id;
          jj++;
          for (int i = 0; i < NMAX; i++)
          {
            sendGrad[rank][jj] = sstree.localElements[recvElement[rank][j]].gradNeigh[i];
//            cout<<"grad  "<<jj<<"  "<<sendGrad[rank][jj]<<" "<<sstree.localElements[recvElement[rank][j]].grad<<endl ;
            sendNeighIds[rank][jj] = sstree.localElements[recvElement[rank][j]].neighId[i];
            jj++;
          }
        }
        else
          sendNeighIds[rank][j] = sstree.localElements[recvElement[rank][j]].src_id;
      }
      MPI_Issend(sendValue[rank],  nbRecvElement[rank], MPI_DOUBLE, rank, 0, communicator, &sendRequest[nbSendRequest]);
      nbSendRequest++;
      MPI_Issend(sendArea[rank],  nbRecvElement[rank], MPI_DOUBLE, rank, 0, communicator, &sendRequest[nbSendRequest]);
      nbSendRequest++;
      MPI_Issend(sendGivenArea[rank],  nbRecvElement[rank], MPI_DOUBLE, rank, 0, communicator, &sendRequest[nbSendRequest]);
      nbSendRequest++;
      if (order == 2)
      {
        MPI_Issend(sendGrad[rank], 3*nbRecvElement[rank]*(NMAX+1), MPI_DOUBLE, rank, 0, communicator, &sendRequest[nbSendRequest]);
        nbSendRequest++;
        MPI_Issend(sendNeighIds[rank], 4*nbRecvElement[rank]*(NMAX+1), MPI_INT, rank, 0, communicator, &sendRequest[nbSendRequest]);
//ym  --> attention taille GloId
        nbSendRequest++;
      }
      else
      {
        MPI_Issend(sendNeighIds[rank], 4*nbRecvElement[rank], MPI_INT, rank, 0, communicator, &sendRequest[nbSendRequest]);
//ym  --> attention taille GloId
        nbSendRequest++;
      }
    }
    if (nbSendElement[rank] > 0)
    {
      MPI_Irecv(recvValue[rank],  nbSendElement[rank], MPI_DOUBLE, rank, 0, communicator, &recvRequest[nbRecvRequest]);
      nbRecvRequest++;
      MPI_Irecv(recvArea[rank],  nbSendElement[rank], MPI_DOUBLE, rank, 0, communicator, &recvRequest[nbRecvRequest]);
      nbRecvRequest++;
      MPI_Irecv(recvGivenArea[rank],  nbSendElement[rank], MPI_DOUBLE, rank, 0, communicator, &recvRequest[nbRecvRequest]);
      nbRecvRequest++;
      if (order == 2)
      {
        MPI_Irecv(recvGrad[rank], 3*nbSendElement[rank]*(NMAX+1),
            MPI_DOUBLE, rank, 0, communicator, &recvRequest[nbRecvRequest]);
        nbRecvRequest++;
        MPI_Irecv(recvNeighIds[rank], 4*nbSendElement[rank]*(NMAX+1), MPI_INT, rank, 0, communicator, &recvRequest[nbRecvRequest]);
//ym  --> attention taille GloId
        nbRecvRequest++;
      }
      else
      {
        MPI_Irecv(recvNeighIds[rank], 4*nbSendElement[rank], MPI_INT, rank, 0, communicator, &recvRequest[nbRecvRequest]);
//ym  --> attention taille GloId
        nbRecvRequest++;
      }
    }
  }
        
        MPI_Waitall(nbSendRequest, sendRequest, status);
  MPI_Waitall(nbRecvRequest, recvRequest, status);
  

  /* now that all values and gradients are available use them to computed interpolated values on target
     and also to compute weights */
  int i = 0;
  for (int j = 0; j < nbElements; j++)
  {
    Elt& e = elements[j];

    /* since for the 2nd order case source grid elements can contribute to a destination grid element over several "paths"
       (step1: gradient is computed using neighbours on same grid, step2: intersection uses several elements on other grid)
       accumulate them so that there is only one final weight between two elements */
    map<GloId,double> wgt_map;

    /* for destination element `e` loop over all intersetions/the corresponding source elements */
    for (list<Polyg *>::iterator it = e.is.begin(); it != e.is.end(); it++)
    {
      /* it is the intersection element, so it->x and it->area are barycentre and area of intersection element (super mesh)
      but it->id is id of the source element that it intersects */
      int n1 = (*it)->id.ind;
      int rank = (*it)->id.rank;
      double fk = recvValue[rank][n1];
      double srcArea = recvArea[rank][n1];
      double srcGivenArea = recvGivenArea[rank][n1];
      double w = (*it)->area;
      if (quantity) w/=srcArea ;
      else w=w*srcGivenArea/srcArea*e.area/e.given_area ;

      /* first order: src value times weight (weight = supermesh area), later divide by target area */
      int kk = (order == 2) ? n1 * (NMAX + 1) : n1;
      GloId neighID = recvNeighIds[rank][kk];
      wgt_map[neighID] += w;

      if (order == 2)
      {
        for (int k = 0; k < NMAX+1; k++)
        {
          int kk = n1 * (NMAX + 1) + k;
          GloId neighID = recvNeighIds[rank][kk];
          if (neighID.ind != -1)  wgt_map[neighID] += w * scalarprod(recvGrad[rank][kk], (*it)->x);
        }

      }
    }

    double renorm=0;
    if (renormalize) 
    {
      if (quantity) for (map<GloId,double>::iterator it = wgt_map.begin(); it != wgt_map.end(); it++) renorm+=it->second ;
      else for (map<GloId,double>::iterator it = wgt_map.begin(); it != wgt_map.end(); it++) renorm+=it->second / e.area;
    }
    else renorm=1. ;

    for (map<GloId,double>::iterator it = wgt_map.begin(); it != wgt_map.end(); it++)
    {
      if (quantity)  this->remapMatrix[i] = (it->second ) / renorm;
      else this->remapMatrix[i] = (it->second / e.area) / renorm;
      this->srcAddress[i] = it->first.ind;
      this->srcRank[i] = it->first.rank;
      this->dstAddress[i] = j;
      this->sourceWeightId[i]= it->first.globalId ;
      this->targetWeightId[i]= targetGlobalId[j] ;
      i++;
    }
  }

  /* free all memory allocated in this function */
  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbSendElement[rank] > 0)
    {
      delete[] sendElement[rank];
      delete[] recvValue[rank];
      delete[] recvArea[rank];
      delete[] recvGivenArea[rank];
      if (order == 2)
      {
        delete[] recvGrad[rank];
      }
      delete[] recvNeighIds[rank];
    }
    if (nbRecvElement[rank] > 0)
    {
      delete[] recvElement[rank];
      delete[] sendValue[rank];
      delete[] sendArea[rank];
      delete[] sendGivenArea[rank];
      if (order == 2)
        delete[] sendGrad[rank];
      delete[] sendNeighIds[rank];
    }
  }
  delete[] status;
  delete[] sendRequest;
  delete[] recvRequest;
  delete[] elementList;
  delete[] nbSendElement;
  delete[] nbRecvElement;
  delete[] sendElement;
  delete[] recvElement;
  delete[] sendValue;
  delete[] recvValue;
  delete[] sendGrad;
  delete[] recvGrad;
  delete[] sendNeighIds;
  delete[] recvNeighIds;
  return i;
}

void Mapper::computeGrads()
{
  /* array of pointers to collect local elements and elements received from other cpu */
  vector<Elt*> globalElements(sstree.nbLocalElements + nbNeighbourElements);
  int index = 0;
  for (int i = 0; i < sstree.nbLocalElements; i++, index++)
    globalElements[index] = &(sstree.localElements[i]);
  for (int i = 0; i < nbNeighbourElements; i++, index++)
    globalElements[index] = &neighbourElements[i];

  update_baryc(sstree.localElements, sstree.nbLocalElements);
  computeGradients(&globalElements[0], sstree.nbLocalElements);
}

/** for each element of the source grid, finds all the neighbouring elements that share an edge
    (filling array neighbourElements). This is used later to compute gradients */
void Mapper::buildMeshTopology()
{
  int mpiSize, mpiRank;
  MPI_Comm_size(communicator, &mpiSize);
  MPI_Comm_rank(communicator, &mpiRank);

  vector<Node> *routingList = new vector<Node>[mpiSize];
  vector<vector<int> > routes(sstree.localTree.leafs.size());

  sstree.routeIntersections(routes, sstree.localTree.leafs);

  for (int i = 0; i < routes.size(); ++i)
    for (int k = 0; k < routes[i].size(); ++k)
      routingList[routes[i][k]].push_back(sstree.localTree.leafs[i]);
  routingList[mpiRank].clear();


  CMPIRouting mpiRoute(communicator);
  mpiRoute.init(routes);
  int nRecv = mpiRoute.getTotalSourceElement();
// cout << mpiRank << " NRECV " << nRecv << "(" << routes.size() << ")"<< endl;

  int *nbSendNode = new int[mpiSize];
  int *nbRecvNode = new int[mpiSize];
  int *sendMessageSize = new int[mpiSize];
  int *recvMessageSize = new int[mpiSize];

  for (int rank = 0; rank < mpiSize; rank++)
  {
    nbSendNode[rank] = routingList[rank].size();
    sendMessageSize[rank] = 0;
    for (size_t j = 0; j < routingList[rank].size(); j++)
    {
      Elt *elt = (Elt *) (routingList[rank][j].data);
      sendMessageSize[rank] += packedPolygonSize(*elt);
    }
  }

  MPI_Alltoall(nbSendNode, 1, MPI_INT, nbRecvNode, 1, MPI_INT, communicator);
  MPI_Alltoall(sendMessageSize, 1, MPI_INT, recvMessageSize, 1, MPI_INT, communicator);

  char **sendBuffer = new char*[mpiSize];
  char **recvBuffer = new char*[mpiSize];
  int *pos = new int[mpiSize];

  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbSendNode[rank] > 0) sendBuffer[rank] = new char[sendMessageSize[rank]];
    if (nbRecvNode[rank] > 0) recvBuffer[rank] = new char[recvMessageSize[rank]];
  }

  for (int rank = 0; rank < mpiSize; rank++)
  {
    pos[rank] = 0;
    for (size_t j = 0; j < routingList[rank].size(); j++)
    {
      Elt *elt = (Elt *) (routingList[rank][j].data);
      packPolygon(*elt, sendBuffer[rank], pos[rank]);
    }
  }
  delete [] routingList;


  int nbSendRequest = 0;
  int nbRecvRequest = 0;
  MPI_Request *sendRequest = new MPI_Request[mpiSize];
  MPI_Request *recvRequest = new MPI_Request[mpiSize];
  MPI_Status  *status      = new MPI_Status[mpiSize];

  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbSendNode[rank] > 0)
    {
      MPI_Issend(sendBuffer[rank], sendMessageSize[rank], MPI_CHAR, rank, 0, communicator, &sendRequest[nbSendRequest]);
      nbSendRequest++;
    }
    if (nbRecvNode[rank] > 0)
    {
      MPI_Irecv(recvBuffer[rank], recvMessageSize[rank], MPI_CHAR, rank, 0, communicator, &recvRequest[nbRecvRequest]);
      nbRecvRequest++;
    }
  }

  MPI_Waitall(nbRecvRequest, recvRequest, status);
  MPI_Waitall(nbSendRequest, sendRequest, status);

  for (int rank = 0; rank < mpiSize; rank++)
    if (nbSendNode[rank] > 0) delete [] sendBuffer[rank];
  delete [] sendBuffer;

  char **sendBuffer2 = new char*[mpiSize];
  char **recvBuffer2 = new char*[mpiSize];

  for (int rank = 0; rank < mpiSize; rank++)
  {
    nbSendNode[rank] = 0;
    sendMessageSize[rank] = 0;

    if (nbRecvNode[rank] > 0)
    {
      set<NodePtr> neighbourList;
      pos[rank] = 0;
      for (int j = 0; j < nbRecvNode[rank]; j++)
      {
        Elt elt;
        unpackPolygon(elt, recvBuffer[rank], pos[rank]);
        Node node(elt.x, cptRadius(elt), &elt);
        findNeighbour(sstree.localTree.root, &node, neighbourList);
      }
      nbSendNode[rank] = neighbourList.size();
      for (set<NodePtr>::iterator it = neighbourList.begin(); it != neighbourList.end(); it++)
      {
        Elt *elt = (Elt *) ((*it)->data);
        sendMessageSize[rank] += packedPolygonSize(*elt);
      }

      sendBuffer2[rank] = new char[sendMessageSize[rank]];
      pos[rank] = 0;

      for (set<NodePtr>::iterator it = neighbourList.begin(); it != neighbourList.end(); it++)
      {
        Elt *elt = (Elt *) ((*it)->data);
        packPolygon(*elt, sendBuffer2[rank], pos[rank]);
      }
    }
  }
  for (int rank = 0; rank < mpiSize; rank++)
    if (nbRecvNode[rank] > 0) delete [] recvBuffer[rank];
  delete [] recvBuffer;


  MPI_Barrier(communicator);
  MPI_Alltoall(nbSendNode, 1, MPI_INT, nbRecvNode, 1, MPI_INT, communicator);
  MPI_Alltoall(sendMessageSize, 1, MPI_INT, recvMessageSize, 1, MPI_INT, communicator);

  for (int rank = 0; rank < mpiSize; rank++)
    if (nbRecvNode[rank] > 0) recvBuffer2[rank] = new char[recvMessageSize[rank]];

  nbSendRequest = 0;
  nbRecvRequest = 0;

  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbSendNode[rank] > 0)
    {
      MPI_Issend(sendBuffer2[rank], sendMessageSize[rank], MPI_CHAR, rank, 0, communicator, &sendRequest[nbSendRequest]);
      nbSendRequest++;
    }
    if (nbRecvNode[rank] > 0)
    {
      MPI_Irecv(recvBuffer2[rank], recvMessageSize[rank], MPI_CHAR, rank, 0, communicator, &recvRequest[nbRecvRequest]);
      nbRecvRequest++;
    }
  }

  MPI_Waitall(nbRecvRequest, recvRequest, status);
  MPI_Waitall(nbSendRequest, sendRequest, status);

  int nbNeighbourNodes = 0;
  for (int rank = 0; rank < mpiSize; rank++)
    nbNeighbourNodes += nbRecvNode[rank];

  neighbourElements = new Elt[nbNeighbourNodes];
  nbNeighbourElements = nbNeighbourNodes;

  int index = 0;
  for (int rank = 0; rank < mpiSize; rank++)
  {
    pos[rank] = 0;
    for (int j = 0; j < nbRecvNode[rank]; j++)
    {
      unpackPolygon(neighbourElements[index], recvBuffer2[rank], pos[rank]);
      neighbourElements[index].id.ind = sstree.localTree.leafs.size() + index;
      index++;
    }
  }
  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbRecvNode[rank] > 0) delete [] recvBuffer2[rank];
    if (nbSendNode[rank] > 0) delete [] sendBuffer2[rank];
  }
  delete [] recvBuffer2;
  delete [] sendBuffer2;
  delete [] sendMessageSize;
  delete [] recvMessageSize;
  delete [] nbSendNode;
  delete [] nbRecvNode;
  delete [] sendRequest;
  delete [] recvRequest;
  delete [] status;
  delete [] pos;

  /* re-compute on received elements to avoid having to send this information */
  neighbourNodes.resize(nbNeighbourNodes);
  setCirclesAndLinks(neighbourElements, neighbourNodes);
  cptAllEltsGeom(neighbourElements, nbNeighbourNodes, srcGrid.pole);

  /* the local SS tree must include nodes from other cpus if they are potential
           intersector of a local node */
  sstree.localTree.insertNodes(neighbourNodes);

  /* for every local element,
           use the SS-tree to find all elements (including neighbourElements)
           who are potential neighbours because their circles intersect,
     then check all canditates for common edges to build up connectivity information
  */
  for (int j = 0; j < sstree.localTree.leafs.size(); j++)
  {
    Node& node = sstree.localTree.leafs[j];

    /* find all leafs whoes circles that intersect node's circle and save into node->intersectors */
    node.search(sstree.localTree.root);

    Elt *elt = (Elt *)(node.data);

    for (int i = 0; i < elt->n; i++) elt->neighbour[i] = NOT_FOUND;

    /* for element `elt` loop through all nodes in the SS-tree
                   whoes circles intersect with the circle around `elt` (the SS intersectors)
                   and check if they are neighbours in the sense that the two elements share an edge.
                   If they do, save this information for elt */
    for (list<NodePtr>::iterator it = (node.intersectors).begin(); it != (node.intersectors).end(); ++it)
    {
      Elt *elt2 = (Elt *)((*it)->data);
      set_neighbour(*elt, *elt2);
    }

/*
    for (int i = 0; i < elt->n; i++)
    {
      if (elt->neighbour[i] == NOT_FOUND)
        error_exit("neighbour not found");
    }
*/
  }
}

/** @param elements are the target grid elements */
void Mapper::computeIntersection(Elt *elements, int nbElements)
{
  int mpiSize, mpiRank;
  MPI_Comm_size(communicator, &mpiSize);
  MPI_Comm_rank(communicator, &mpiRank);

  MPI_Barrier(communicator);

  vector<Node> *routingList = new vector<Node>[mpiSize];

  vector<Node> routeNodes;  routeNodes.reserve(nbElements);
  for (int j = 0; j < nbElements; j++)
  {
    elements[j].id.ind = j;
    elements[j].id.rank = mpiRank;
    routeNodes.push_back(Node(elements[j].x, cptRadius(elements[j]), &elements[j]));
  }

  vector<vector<int> > routes(routeNodes.size());
  sstree.routeIntersections(routes, routeNodes);
  for (int i = 0; i < routes.size(); ++i)
    for (int k = 0; k < routes[i].size(); ++k)
      routingList[routes[i][k]].push_back(routeNodes[i]);

  if (verbose >= 2)
  {
    cout << " --> rank  " << mpiRank << " nbElements " << nbElements << " : ";
    for (int rank = 0; rank < mpiSize; rank++)
      cout << routingList[rank].size() << "   ";
    cout << endl;
  }
  MPI_Barrier(communicator);

  int *nbSendNode = new int[mpiSize];
  int *nbRecvNode = new int[mpiSize];
  int *sentMessageSize = new int[mpiSize];
  int *recvMessageSize = new int[mpiSize];

  for (int rank = 0; rank < mpiSize; rank++)
  {
    nbSendNode[rank] = routingList[rank].size();
    sentMessageSize[rank] = 0;
    for (size_t j = 0; j < routingList[rank].size(); j++)
    {
      Elt *elt = (Elt *) (routingList[rank][j].data);
      sentMessageSize[rank] += packedPolygonSize(*elt);
    }
  }

  MPI_Alltoall(nbSendNode, 1, MPI_INT, nbRecvNode, 1, MPI_INT, communicator);
  MPI_Alltoall(sentMessageSize, 1, MPI_INT, recvMessageSize, 1, MPI_INT, communicator);

  int total = 0;

  for (int rank = 0; rank < mpiSize; rank++)
  {
    total = total + nbRecvNode[rank];
  }

  if (verbose >= 2) cout << "---> rank " << mpiRank << " : compute intersection : total received nodes  " << total << endl;
  char **sendBuffer = new char*[mpiSize];
  char **recvBuffer = new char*[mpiSize];
  int *pos = new int[mpiSize];

  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbSendNode[rank] > 0) sendBuffer[rank] = new char[sentMessageSize[rank]];
    if (nbRecvNode[rank] > 0) recvBuffer[rank] = new char[recvMessageSize[rank]];
  }

  for (int rank = 0; rank < mpiSize; rank++)
  {
    pos[rank] = 0;
    for (size_t j = 0; j < routingList[rank].size(); j++)
    {
      Elt* elt = (Elt *) (routingList[rank][j].data);
      packPolygon(*elt, sendBuffer[rank], pos[rank]);
    }
  }
  delete [] routingList;

  int nbSendRequest = 0;
  int nbRecvRequest = 0;
  MPI_Request *sendRequest = new MPI_Request[mpiSize];
  MPI_Request *recvRequest = new MPI_Request[mpiSize];
  MPI_Status   *status = new MPI_Status[mpiSize];

  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbSendNode[rank] > 0)
    {
      MPI_Issend(sendBuffer[rank], sentMessageSize[rank], MPI_CHAR, rank, 0, communicator, &sendRequest[nbSendRequest]);
      nbSendRequest++;
    }
    if (nbRecvNode[rank] > 0)
    {
      MPI_Irecv(recvBuffer[rank], recvMessageSize[rank], MPI_CHAR, rank, 0, communicator, &recvRequest[nbRecvRequest]);
      nbRecvRequest++;
    }
  }

  MPI_Waitall(nbRecvRequest, recvRequest, status);
  MPI_Waitall(nbSendRequest, sendRequest, status);
  char **sendBuffer2 = new char*[mpiSize];
  char **recvBuffer2 = new char*[mpiSize];

  double tic = cputime();
  for (int rank = 0; rank < mpiSize; rank++)
  {
    sentMessageSize[rank] = 0;

    if (nbRecvNode[rank] > 0)
    {
      Elt *recvElt = new Elt[nbRecvNode[rank]];
      pos[rank] = 0;
      for (int j = 0; j < nbRecvNode[rank]; j++)
      {
        unpackPolygon(recvElt[j], recvBuffer[rank], pos[rank]);
        cptEltGeom(recvElt[j], tgtGrid.pole);
        Node recvNode(recvElt[j].x, cptRadius(recvElt[j]), &recvElt[j]);
        recvNode.search(sstree.localTree.root);
        /* for a node holding an element of the target, loop throught candidates for intersecting source */
        for (list<NodePtr>::iterator it = (recvNode.intersectors).begin(); it != (recvNode.intersectors).end(); ++it)
        {
          Elt *elt2 = (Elt *) ((*it)->data);
          /* recvElt is target, elt2 is source */
//          intersect(&recvElt[j], elt2);
          intersect_ym(&recvElt[j], elt2);
        }

        if (recvElt[j].is.size() > 0) sentMessageSize[rank] += packIntersectionSize(recvElt[j]);

        // here recvNode goes out of scope
      }

      if (sentMessageSize[rank] > 0)
      {
        sentMessageSize[rank] += sizeof(int);
        sendBuffer2[rank] = new char[sentMessageSize[rank]];
        *((int *) sendBuffer2[rank]) = 0;
        pos[rank] = sizeof(int);
        for (int j = 0; j < nbRecvNode[rank]; j++)
        {
          packIntersection(recvElt[j], sendBuffer2[rank], pos[rank]);
          //FIXME should be deleted: recvElt[j].delete_intersections(); // intersection areas have been packed to buffer and won't be used any more
        }
      }
      delete [] recvElt;

    }
  }
  delete [] pos;

  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbSendNode[rank] > 0) delete [] sendBuffer[rank];
    if (nbRecvNode[rank] > 0) delete [] recvBuffer[rank];
    nbSendNode[rank] = 0;
  }

  if (verbose >= 2) cout << "Rank " << mpiRank << "  Compute (internal) intersection " << cputime() - tic << " s" << endl;
  MPI_Alltoall(sentMessageSize, 1, MPI_INT, recvMessageSize, 1, MPI_INT, communicator);

  for (int rank = 0; rank < mpiSize; rank++)
    if (recvMessageSize[rank] > 0)
      recvBuffer2[rank] = new char[recvMessageSize[rank]];

  nbSendRequest = 0;
  nbRecvRequest = 0;

  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (sentMessageSize[rank] > 0)
    {
      MPI_Issend(sendBuffer2[rank], sentMessageSize[rank], MPI_CHAR, rank, 0, communicator, &sendRequest[nbSendRequest]);
      nbSendRequest++;
    }
    if (recvMessageSize[rank] > 0)
    {
      MPI_Irecv(recvBuffer2[rank], recvMessageSize[rank], MPI_CHAR, rank, 0, communicator, &recvRequest[nbRecvRequest]);
      nbRecvRequest++;
    }
  }

  MPI_Waitall(nbRecvRequest, recvRequest, status);
  MPI_Waitall(nbSendRequest, sendRequest, status);

  delete [] sendRequest;
  delete [] recvRequest;
  delete [] status;
  for (int rank = 0; rank < mpiSize; rank++)
  {
    if (nbRecvNode[rank] > 0)
    {
      if (sentMessageSize[rank] > 0)
        delete [] sendBuffer2[rank];
    }

    if (recvMessageSize[rank] > 0)
    {
      unpackIntersection(elements, recvBuffer2[rank]);
      delete [] recvBuffer2[rank];
    }
  }
  delete [] sendBuffer2;
  delete [] recvBuffer2;
  delete [] sendBuffer;
  delete [] recvBuffer;

  delete [] nbSendNode;
  delete [] nbRecvNode;
  delete [] sentMessageSize;
  delete [] recvMessageSize;
}

Mapper::~Mapper()
{
  delete [] remapMatrix;
  delete [] srcAddress;
  delete [] srcRank;
  delete [] dstAddress;
  if (neighbourElements) delete [] neighbourElements;
}

}
