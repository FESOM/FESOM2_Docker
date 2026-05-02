#include <cassert>
#include "node.hpp"
#include "timerRemap.hpp"
#include "circle.hpp"
#include "meshutil.hpp"
#include "polyg.hpp"
#include "gridRemap.hpp"
#include "intersect.hpp"
#include "errhandle.hpp"
#include "mpi_routing.hpp"
#include "misc.hpp"

#include "parallel_tree.hpp"

namespace sphereRemap {

static const int assignLevel = 2;

// only the circle is packed, rest of node will be initialized on unpacking
static void packNode(Node& node, char *buffer, int& index)
{
	if (buffer == NULL) // compute size only
		index += 4 * sizeof(double);
	else
	{
		*(Coord *)(&buffer[index]) = node.centre;
		index += sizeof(Coord);

		*(double *)(&buffer[index]) = node.radius;
		index += sizeof(double);
	}
}

static void unpackNode(Node& node, char *buffer, int& index)
{
	Coord centre;
	double r;

	centre = *(Coord *)(&buffer[index]);
	index += sizeof(Coord);

	r = *(double *)(&buffer[index]);
	index += sizeof(double);

	node.centre = centre;
	node.radius = r;
}


static void packElement(Elt *ptElement, char *buffer, int& index)
{
	if (buffer == NULL) index += packedPolygonSize(*ptElement);
	else packPolygon(*ptElement, buffer, index);
}

static void unpackElement(Elt *ptElement, char *buffer, int& index)
{
	unpackPolygon(*ptElement, buffer, index);
}

static void packVector(const vector<int>& vec, char *buf, int& pos)
{
	if (buf == NULL)
		pos += sizeof(int) + vec.size()*sizeof(int);
	else
	{
		*((int *) &(buf[pos])) = vec.size();
		pos += sizeof(int);
		for (int i = 0; i < vec.size(); i++)
		{
			*((int *) &(buf[pos])) = vec[i];
			pos += sizeof(int);
		}
	}
}

static void unpackVector(vector<int>& vec, const char *buf, int& pos)
{
	vec.resize(*((int *) &(buf[pos])));
	pos += sizeof(int);
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i] = *((int *) &(buf[pos]));
		pos += sizeof(int);
	}
}

static void assignRoute(CSampleTree& tree, const CCascadeLevel& cl)  // newroot <- root
{
	vector<int> routeRank(cl.group_size);
	for (int i = 0; i < cl.group_size; i++)
		routeRank[i] = i; //(cl.group_size + cl.polour() - i) % cl.group_size;
	std::vector<int>::iterator rank = routeRank.begin();
	tree.root->assignRoute(rank, assignLevel);
}

static void transferRoutedNodes(CMPIRouting& MPIRoute, /*const*/ vector<Node>& nodeSend, const vector<int>& route, vector<Node>& nodeRecv)
{
	/* `route` knows what goes where */
	MPIRoute.init(route);
	int nRecv = MPIRoute.getTotalSourceElement();
	nodeRecv.resize(nRecv);
	MPIRoute.transferToTarget(&nodeSend[0], &nodeRecv[0], packNode, unpackNode);
}

static void transferRoutedIntersections(CMPIRouting& MPIRoute, const vector<Node>& nodeSend, const vector<vector<int> >& route, vector<Node>& nodeRecv)
{
	// `route` knows what goes where
	MPIRoute.init(route);
	int nRecv = MPIRoute.getTotalSourceElement();
	nodeRecv.resize(nRecv);
	MPIRoute.transferToTarget((Node * /*mpi wants non-const*/) &nodeSend[0], &nodeRecv[0], packNode, unpackNode);
//cout << MPIRoute.mpiRank << " ROUTE " << nRecv << ": " << nodeSend.size() << " " << nodeRecv.size() << "    ";
}

//CParallelTree::CParallelTree(MPI_Comm comm) : communicator(comm), cascade(MIN_NODE_SZ*MIN_NODE_SZ, comm)
CParallelTree::CParallelTree(MPI_Comm comm) : communicator(comm), cascade(MAX_NODE_SZ*MAX_NODE_SZ*2, comm)
{
	treeCascade.reserve(cascade.num_levels);
	for (int lev = 0; lev < cascade.num_levels; lev++)
		treeCascade.push_back(CSampleTree(cascade.level[lev].group_size, assignLevel));
}

void CParallelTree::buildSampleTreeCascade(vector<Node>& sampleNodes /*route field will be modified*/, int level)
{
	buildSampleTree(treeCascade[level], sampleNodes, cascade.level[level]);
	assignRoute(treeCascade[level] /*out*/, cascade.level[level] /*in*/);

	if (level+1 < cascade.num_levels)
	{
		vector<int> route(sampleNodes.size());
		treeCascade[level].routeNodes(route, sampleNodes, assignLevel);

		vector<Node> routedNodes;
		CMPIRouting mpiRoute(cascade.level[level].pg_comm);
		transferRoutedNodes(mpiRoute, sampleNodes, route, routedNodes);
		buildSampleTreeCascade(routedNodes, level+1);
	}
}

void buildSampleTree(CSampleTree& tree, const vector<Node>& node, const CCascadeLevel& comm)
/*
	In the beginning all the sample elements are distributed
	-> communicate to make available at each rank
	   so that each rank can build the same sample tree
*/
{
	int n = node.size(); // number of samples intially on this rank (local)

	int blocSize = comm.group_size * ipow(MAX_NODE_SZ, assignLevel);

	int nrecv; // global number of samples  THIS WILL BE THE NUMBER OF LEAFS IN THE SAMPLE TREE
	MPI_Allreduce(&n, &nrecv, 1, MPI_INT, MPI_SUM, comm.comm); // => size of sample tree does not depend on keepNodes!
	double ratio = blocSize / (1.0 * nrecv);
	int nsend = ratio * n + 1; // nsend = n_local_samples / n_global_samples * blocksize + 1 = blocksize/comm.size
	if (nsend > n) nsend = n;

	int *counts = new int[comm.size];
	MPI_Allgather(&nsend, 1, MPI_INT, counts, 1, MPI_INT, comm.comm);

	nrecv = 0;
	int *displs = new int[comm.size];
	for (int i = 0; i < comm.size; i++)
	{
		displs[i] = 4 * nrecv;
		nrecv += counts[i];
		counts[i] = 4 * counts[i];
	}

	/* pack circles around sample elements */
	double *sendBuffer = new double[nsend*4];
	int index = 0;
	vector<int> randomArray(n);
	randomizeArray(randomArray);
	for (int i = 0; i < nsend; i++)
	{
		const Node& no = node[randomArray[i]];
		*((Coord *) (sendBuffer + index)) = no.centre;
		index += sizeof(Coord)/sizeof(*sendBuffer);
		sendBuffer[index++] = no.radius;
	}

	/* each process needs the sample elements from all processes */
	double *recvBuffer = new double[nrecv*4];
	MPI_Allgatherv(sendBuffer, 4 * nsend, MPI_DOUBLE, recvBuffer, counts, displs, MPI_DOUBLE, comm.comm);
	delete[] sendBuffer;
	delete[] counts;
	delete[] displs;

	/* unpack */
/*
	randomArray.resize(nrecv);
	randomizeArray(randomArray);
	tree.leafs.resize(nrecv);
	index = 0;


  for (int i = 0; i < nrecv; i++)
	{
		Coord x = *(Coord *)(&recvBuffer[index]);
		index += sizeof(Coord)/sizeof(*recvBuffer);
		double radius = recvBuffer[index++];
		tree.leafs[randomArray[i]].centre = x;
		tree.leafs[randomArray[i]].radius = radius;

	}
*/

  randomArray.resize(blocSize);
	randomizeArray(randomArray);
	tree.leafs.resize(blocSize);
	index = 0;
  
  size_t s=(sizeof(Coord)/sizeof(*recvBuffer)+1)*nrecv ;
  
  for (int i = 0; i < blocSize; i++)
	{
		Coord x = *(Coord *)(&recvBuffer[index%s]);
		index += sizeof(Coord)/sizeof(*recvBuffer);
		double radius = recvBuffer[index%s];
    index++ ;
		tree.leafs[randomArray[i]].centre = x;
		tree.leafs[randomArray[i]].radius = radius;

	}


	delete [] recvBuffer;

	CTimer::get("buildSampleTree(local)").resume();
	tree.build(tree.leafs);
//	cout << "SampleTree build : assign Level " << assignLevel << " nb Nodes : " << tree.levelSize[assignLevel] << endl;
	CTimer::get("buildSampleTree(local)").suspend();
	CTimer::get("buildSampleTree(local)").print();

	/* End gracefully if sample tree could not be constructed with desired number of nodes on assignLevel */
	int allok, ok = (tree.levelSize[assignLevel] == comm.group_size);
	if (!ok)
  {
    cerr << comm.rank << ": PROBLEM: (node assign)" << tree.levelSize[assignLevel] << " != " << comm.group_size << " (keepNodes)" 
         << "   node size : "<<node.size()<<"   bloc size : "<<blocSize<<"  total number of leaf : "<<tree.leafs.size()<<endl ;
/*
	MPI_Allreduce(&ok, &allok, 1, MPI_INT, MPI_PROD, communicator);
	if (!allok) {
		MPI_Finalize();
		exit(1);
	}
*/
    MPI_Abort(MPI_COMM_WORLD,-1) ;
  }
/*
  cout<<"*******************************************"<<endl ;
  cout<<"******* Sample Tree output        *********"<<endl ;
  cout<<"*******************************************"<<endl ;
  tree.output(cout,1) ;

  cout<<"*******************************************"<<endl ;
*/

  assert(tree.root->incluCheck() == 0);
}


void CParallelTree::buildLocalTree(const vector<Node>& node, const vector<int>& route)
{
	CMPIRouting MPIRoute(communicator);
	MPI_Barrier(communicator);
	CTimer::get("buildLocalTree(initRoute)").resume();
	MPIRoute.init(route);
	CTimer::get("buildLocalTree(initRoute)").suspend();
	CTimer::get("buildLocalTree(initRoute)").print();

	nbLocalElements = MPIRoute.getTotalSourceElement();
	localElements = new Elt[nbLocalElements];

	vector<Elt*> ptElement(node.size());
	for (int i = 0; i < node.size(); i++)
		ptElement[i] = (Elt *) (node[i].data);

	vector<Elt*> ptLocalElement(nbLocalElements);
	for (int i = 0; i < nbLocalElements; i++)
		ptLocalElement[i] = &localElements[i];

	CTimer::get("buildLocalTree(transfer)").resume();
	MPIRoute.transferToTarget(&ptElement[0], &ptLocalElement[0], packElement, unpackElement);
	CTimer::get("buildLocalTree(transfer)").suspend();
	CTimer::get("buildLocalTree(transfer)").print();

	CTimer::get("buildLocalTree(local)").resume();

	int mpiRank;
	MPI_Comm_rank(communicator, &mpiRank);
	localTree.leafs.reserve(nbLocalElements);
	for (int i = 0; i < nbLocalElements; i++)
	{
		Elt& elt = localElements[i];
		elt.id.ind = i;
		elt.id.rank = mpiRank;
		localTree.leafs.push_back(Node(elt.x, cptRadius(elt), &localElements[i]));
	}
	localTree.build(localTree.leafs);

	cptAllEltsGeom(localElements, nbLocalElements, srcGrid.pole);
	CTimer::get("buildLocalTree(local)").suspend();
	CTimer::get("buildLocalTree(local)").print();
}

void CParallelTree::build(vector<Node>& node, vector<Node>& node2)
{

	int assignLevel = 2;
	int nbSampleNodes = 2*ipow(MAX_NODE_SZ + 1, assignLevel);


  long int nb1, nb2, nb, nbTot ;
  nb1=node.size() ; nb2=node2.size() ;
  nb=nb1+nb2 ;
  MPI_Allreduce(&nb, &nbTot, 1, MPI_LONG, MPI_SUM, communicator) ;
  int commSize ;
  MPI_Comm_size(communicator,&commSize) ;
  
	// make multiple of two
	nbSampleNodes /= 2;
	nbSampleNodes *= 2;
//  assert( nbTot > nbSampleNodes*commSize) ;
    
  int nbSampleNodes1 = nbSampleNodes * (nb1*commSize)/(1.*nbTot) ;
  int nbSampleNodes2 = nbSampleNodes * (nb2*commSize)/(1.*nbTot) ;
  

//	assert(node.size() > nbSampleNodes);
//	assert(node2.size() > nbSampleNodes);
//	assert(node.size() + node2.size() > nbSampleNodes);
	vector<Node> sampleNodes; sampleNodes.reserve(nbSampleNodes1+nbSampleNodes2);

	vector<int> randomArray1(node.size());
	randomizeArray(randomArray1);
	vector<int> randomArray2(node2.size());
	randomizeArray(randomArray2);

/*	
        int s1,s2 ;
        
        if (node.size()< nbSampleNodes/2)
        { 
          s1 = node.size() ;
          s2 = nbSampleNodes-s1 ;
        }
        else if (node2.size()< nbSampleNodes/2)
        {
          s2 = node.size() ;
          s1 = nbSampleNodes-s2 ;
        }
        else
        {
          s1=nbSampleNodes/2 ;
          s2=nbSampleNodes/2 ;
        }
*/
        for (int i = 0; i <nbSampleNodes1; i++) sampleNodes.push_back(Node(node[randomArray1[i%nb1]].centre,  node[randomArray1[i%nb1]].radius, NULL));
        for (int i = 0; i <nbSampleNodes2; i++) sampleNodes.push_back(Node(node2[randomArray2[i%nb2]].centre, node2[randomArray2[i%nb2]].radius, NULL));

/*          
        for (int i = 0; i < nbSampleNodes/2; i++)
	{
          sampleNodes.push_back(Node(node[randomArray1[i]].centre,  node[randomArray1[i]].radius, NULL));
	  sampleNodes.push_back(Node(node2[randomArray2[i]].centre, node2[randomArray2[i]].radius, NULL));
	}
*/
	CTimer::get("buildParallelSampleTree").resume();
	//sampleTree.buildParallelSampleTree(sampleNodes, cascade);
	buildSampleTreeCascade(sampleNodes);
	CTimer::get("buildParallelSampleTree").suspend();
	CTimer::get("buildParallelSampleTree").print();

	//route source mesh
	CTimer::get("parallelRouteNode").resume();
	vector<int> route(node.size());
	routeNodes(route /*out*/, node);
	CTimer::get("parallelRouteNode").suspend();
	CTimer::get("parallelRouteNode").print();

	CTimer::get("buildLocalTree").resume();
	buildLocalTree(node, route);
	CTimer::get("buildLocalTree").suspend();
	CTimer::get("buildLocalTree").print();

	CTimer::get("buildRouteTree").resume();
	/* update circles of tree cascade so it can be used for routing */
	updateCirclesForRouting(localTree.root->centre, localTree.root->radius);
	CTimer::get("buildRouteTree").suspend();
	CTimer::get("buildRouteTree").print();
}

void CParallelTree::routeNodes(vector<int>& route, vector<Node>& nodes /*route field used*/, int level)
{
	treeCascade[level].routeNodes(route /*assign*/, nodes, assignLevel);

	if (level+1 < cascade.num_levels)
	{
		vector<Node> routedNodes;
		CMPIRouting MPIRoute(cascade.level[level].pg_comm);
		transferRoutedNodes(MPIRoute, nodes, route /*use*/, routedNodes);
		vector<int> globalRank(routedNodes.size());
		routeNodes(globalRank, routedNodes, level + 1);
		MPIRoute.transferFromSource(&route[0] /*override*/, &globalRank[0]);
	}
	else
	{
		CMPIRouting MPIRoute(cascade.level[level].comm); // or use pg_comm, on last cascade level identical
		MPIRoute.init(route);
		int nbRecvNode = MPIRoute.getTotalSourceElement();
		vector<int> globalRank(nbRecvNode);
		for (int i = 0; i < globalRank.size(); i++)
			globalRank[i] = cascade.level[0].rank;
		MPIRoute.transferFromSource(&route[0] /*override*/, &globalRank[0]);
	}
}

/* assume `to` to be empty vector at entry */
void linearize(const vector<vector<int> >& from, vector<int>& to)
{
	int cnt = 0;
	for (int i = 0; i < from.size(); ++i)
		cnt += from[i].size();
	to.resize(cnt);
	vector<int>::iterator dest = to.begin();
	for (int i = 0; i < from.size(); ++i)
		dest = copy(from[i].begin(), from[i].end(), dest);
}

/* at entry `to` must already have it's final shape and only values are overriden */
void delinearize(const vector<int>& from, vector<vector<int> >& to)
{
	vector<int>::const_iterator end, src = from.begin();
	for (int i = 0; i < to.size(); ++i, src=end)
		copy(src, end = src + to[i].size(), to[i].begin());
}

void CParallelTree::routeIntersections(vector<vector<int> >& routes, vector<Node>& nodes, int level)
{
	treeCascade[level].routeIntersections(routes /*assign*/, nodes);

	if (level+1 < cascade.num_levels)
	{
		vector<Node> routedNodes;
		CMPIRouting MPIRoute(cascade.level[level].pg_comm);

		vector<int> flattenedRoutes1;
		linearize(routes, flattenedRoutes1);
		vector<Node> double_nodes(flattenedRoutes1.size());
		int j = 0;
		for (int i = 0; i < routes.size(); ++i)
			for (int k = 0; k < routes[i].size(); ++k, ++j)
				double_nodes[j] = nodes[i];
		transferRoutedNodes(MPIRoute, double_nodes, flattenedRoutes1 /*use*/, routedNodes);
		vector<vector<int> > globalRanks(routedNodes.size());
		routeIntersections(globalRanks /*out*/, routedNodes /*in*/, level + 1);
		vector<vector<int> > flattenedRoutes(flattenedRoutes1.size());
		// transferFromSource expects sizes (nbSendNode=flattenedRoutes, nbRecvNode=routedNodes.size())
		MPIRoute.transferFromSource(&flattenedRoutes[0], &globalRanks[0], packVector, unpackVector);
		for (int i = 0, j = 0; i < routes.size(); ++i)
		{
			int old_size = routes[i].size();
			routes[i].resize(0);
			for (int k = 0; k < old_size; ++k, ++j)
				for (int l = 0; l < flattenedRoutes[j].size(); ++l)
					routes[i].push_back(flattenedRoutes[j][l]);
		}
		assert(j == flattenedRoutes1.size());

	}
	else
	{
		CMPIRouting MPIRoute(cascade.level[level].comm);
		MPIRoute.init(routes);
		int nbRecvNode = MPIRoute.getTotalSourceElement();
		vector<int> globalRanks(nbRecvNode, cascade.level[0].rank);
		vector<int> flattened_routes;
		linearize(routes, flattened_routes);
		MPIRoute.transferFromSource(&flattened_routes[0], &globalRanks[0]);
		delinearize(flattened_routes, routes);
	}
	if (level!=level)
	{
		for (int i = 0; i < routes.size(); ++i)
			for (int k = 0; k < routes[i].size(); ++k)
				if (routes[i][k] == cascade.level[0].rank) routes[i].erase(routes[i].begin() + (k--));
	}
}

void CParallelTree::updateCirclesForRouting(Coord rootCentre, double rootRadius, int level)
{
	if (level + 1 < cascade.num_levels) // children in the cascade have to update first
	{
		updateCirclesForRouting(rootCentre, rootRadius, level + 1);
		rootCentre = treeCascade[level+1].root->centre;
		rootRadius = treeCascade[level+1].root->radius;
	}

	// gather circles on this level of the cascade
	int pg_size;
	MPI_Comm_size(cascade.level[level].pg_comm, &pg_size);
	vector<Coord> allRootCentres(pg_size);
	vector<double> allRootRadia(pg_size);
	MPI_Allgather(&rootCentre, 3, MPI_DOUBLE, &allRootCentres[0], 3, MPI_DOUBLE, cascade.level[level].pg_comm);
	MPI_Allgather(&rootRadius, 1, MPI_DOUBLE, &allRootRadia[0],   1, MPI_DOUBLE, cascade.level[level].pg_comm);

	// now allRootsRadia and allRootCentres must be inserted into second levels of us and propagated to root
	treeCascade[level].root->assignCircleAndPropagateUp(&allRootCentres[0], &allRootRadia[0], assignLevel);
}

CParallelTree::~CParallelTree()
{
	delete [] localElements;
}

}
