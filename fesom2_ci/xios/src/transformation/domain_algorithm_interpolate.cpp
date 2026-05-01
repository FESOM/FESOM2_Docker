/*!
   \file domain_algorithm_interpolate_from_file.cpp
   \author Ha NGUYEN
   \since 09 Jul 2015
   \date 15 Sep 2015

   \brief Algorithm for interpolation on a domain.
 */
#include "domain_algorithm_interpolate.hpp"
#include <unordered_map>
#include "context.hpp"
#include "context_client.hpp"
#include "distribution_client.hpp"
#include "client_server_mapping_distributed.hpp"
#include "netcdf.hpp"
#include "mapper.hpp"
#include "mpi_tag.hpp"
#include "domain.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "interpolate_domain.hpp"
#include "grid.hpp"

namespace xios {
CGenericAlgorithmTransformation* CDomainAlgorithmInterpolate::create(CGrid* gridDst, CGrid* gridSrc,
                                                                     CTransformation<CDomain>* transformation,
                                                                     int elementPositionInGrid,
                                                                     std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CDomain*> domainListDestP = gridDst->getDomains();
  std::vector<CDomain*> domainListSrcP  = gridSrc->getDomains();

  CInterpolateDomain* interpolateDomain = dynamic_cast<CInterpolateDomain*> (transformation);
  int domainDstIndex = elementPositionInGridDst2DomainPosition[elementPositionInGrid];
  int domainSrcIndex = elementPositionInGridSrc2DomainPosition[elementPositionInGrid];

  return (new CDomainAlgorithmInterpolate(domainListDestP[domainDstIndex], domainListSrcP[domainSrcIndex], interpolateDomain));
}
CATCH

bool CDomainAlgorithmInterpolate::registerTrans()
TRY
{
  return CGridTransformationFactory<CDomain>::registerTransformation(TRANS_INTERPOLATE_DOMAIN, create);
}
CATCH

CDomainAlgorithmInterpolate::CDomainAlgorithmInterpolate(CDomain* domainDestination, CDomain* domainSource, CInterpolateDomain* interpDomain)
: CDomainAlgorithmTransformation(domainDestination, domainSource), interpDomain_(interpDomain), writeToFile_(false), readFromFile_(false)
TRY
{
  CContext* context = CContext::getCurrent();
  interpDomain_->checkValid(domainSource);

  detectMissingValue = interpDomain_->detect_missing_value ;
  renormalize = interpDomain_->renormalize ;
  quantity = interpDomain_->quantity ;

  if (interpDomain_->read_write_convention == CInterpolateDomain::read_write_convention_attr::fortran) fortranConvention=true ;
  else fortranConvention=false ;
  
  fileToReadWrite_ = "xios_interpolation_weights_";

  if (interpDomain_->weight_filename.isEmpty())
  {
    fileToReadWrite_ += context->getId() + "_" + 
                    domainSource->getDomainOutputName() + "_" + 
                    domainDestination->getDomainOutputName() + ".nc";    
  }
  else 
    fileToReadWrite_ = interpDomain_->weight_filename;

  ifstream f(fileToReadWrite_.c_str());  
  switch (interpDomain_->mode)
  {
    case CInterpolateDomain::mode_attr::read:
      readFromFile_ = true;      
      break;
    case CInterpolateDomain::mode_attr::compute:
      readFromFile_ = false;
      break;
    case CInterpolateDomain::mode_attr::read_or_compute:      
      if (!f.good())
        readFromFile_ = false;
      else
        readFromFile_ = true;
      break;
    default:
      break;
  } 

  writeToFile_ = interpDomain_->write_weight;  
    
}
CATCH

/*!
  Compute remap with integrated remap calculation module
*/
void CDomainAlgorithmInterpolate::computeRemap()
TRY
{
  using namespace sphereRemap;

  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int i, j, k, idx;
  std::vector<double> srcPole(3,0), dstPole(3,0);
  int orderInterp = interpDomain_->order.getValue();


  const double poleValue = 90.0;
  const int constNVertex = 4; // Value by default number of vertex for rectangular domain
  int nVertexSrc, nVertexDest;
  nVertexSrc = nVertexDest = constNVertex;

  // First of all, try to retrieve the boundary values of domain source and domain destination
  int localDomainSrcSize = domainSrc_->i_index.numElements();
  int niSrc = domainSrc_->ni.getValue(), njSrc = domainSrc_->nj.getValue();
  bool hasBoundSrc = domainSrc_->hasBounds;
  if (hasBoundSrc) nVertexSrc = domainSrc_->nvertex.getValue();
  CArray<double,2> boundsLonSrc(nVertexSrc,localDomainSrcSize);
  CArray<double,2> boundsLatSrc(nVertexSrc,localDomainSrcSize);
  CArray<double,1> areaSrc;

  if (domainSrc_->hasPole) srcPole[2] = 1;
  if (hasBoundSrc)  // Suppose that domain source is curvilinear or unstructured
  {
    if (!domainSrc_->bounds_lon_2d.isEmpty())
    {
      for (j = 0; j < njSrc; ++j)
        for (i = 0; i < niSrc; ++i)
        {
          k=j*niSrc+i;
          for(int n=0;n<nVertexSrc;++n)
          {
            boundsLonSrc(n,k) = domainSrc_->bounds_lon_2d(n,i,j);
            boundsLatSrc(n,k) = domainSrc_->bounds_lat_2d(n,i,j);
          }
        }
    }
    else
    {
      boundsLonSrc = domainSrc_->bounds_lon_1d;
      boundsLatSrc = domainSrc_->bounds_lat_1d;
    }
  }
  else // if domain source is rectilinear, not do anything now
  {
    CArray<double,1> lon_g ;
    CArray<double,1> lat_g ;

    if (!domainSrc_->lonvalue_1d.isEmpty() && !domainSrc_->latvalue_1d.isEmpty())
    {
      domainSrc_->AllgatherRectilinearLonLat(domainSrc_->lonvalue_1d,domainSrc_->latvalue_1d, lon_g,lat_g) ;
    }
    else if (! domainSrc_->latvalue_rectilinear_read_from_file.isEmpty() && ! domainSrc_->lonvalue_rectilinear_read_from_file.isEmpty() )
    {
      lat_g=domainSrc_->latvalue_rectilinear_read_from_file ;
      lon_g=domainSrc_->lonvalue_rectilinear_read_from_file ;
    }
    else if (!domainSrc_->lon_start.isEmpty() && !domainSrc_->lon_end.isEmpty() &&
             !domainSrc_->lat_start.isEmpty() && !domainSrc_->lat_end.isEmpty())
    {
      double step=(domainSrc_->lon_end-domainSrc_->lon_start)/domainSrc_->ni_glo ;
      for (int i=0; i<domainSrc_->ni_glo; ++i) lon_g(i)=domainSrc_->lon_start+i*step ;
      step=(domainSrc_->lat_end-domainSrc_->lat_start)/domainSrc_->nj_glo ;
      for (int i=0; i<domainSrc_->ni_glo; ++i) lat_g(i)=domainSrc_->lat_start+i*step ;
    }
    else ERROR("void CDomainAlgorithmInterpolate::computeRemap()",<<"Cannot compute bounds for rectilinear domain") ;

    nVertexSrc = constNVertex;
    domainSrc_->fillInRectilinearBoundLonLat(lon_g,lat_g, boundsLonSrc, boundsLatSrc);
  }
  
  if (domainSrc_->hasArea) 
  {
    areaSrc.resize(niSrc*njSrc);
    for (int j = 0; j < njSrc; ++j)
      for (int i = 0; i < niSrc; ++i)
      {
        int k = j * niSrc + i;
        areaSrc(k) = domainSrc_->area(i,j);
      }
  }
  
  std::map<int,std::vector<std::pair<int,double> > > interpMapValueNorthPole;
  std::map<int,std::vector<std::pair<int,double> > > interpMapValueSouthPole;

  int localDomainDestSize = domainDest_->i_index.numElements();
  int niDest = domainDest_->ni.getValue(), njDest = domainDest_->nj.getValue();
  bool hasBoundDest = domainDest_->hasBounds;
  if (hasBoundDest) nVertexDest = domainDest_->nvertex.getValue();
  CArray<double,2> boundsLonDest(nVertexDest,localDomainDestSize);
  CArray<double,2> boundsLatDest(nVertexDest,localDomainDestSize);
  CArray<double,1> areaDest;

  if (domainDest_->hasPole) dstPole[2] = 1;
  if (hasBoundDest)
  {
    if (!domainDest_->bounds_lon_2d.isEmpty())
    {
      for (j = 0; j < njDest; ++j)
        for (i = 0; i < niDest; ++i)
        {
          k=j*niDest+i;
          for(int n=0;n<nVertexDest;++n)
          {
            boundsLonDest(n,k) = domainDest_->bounds_lon_2d(n,i,j);
            boundsLatDest(n,k) = domainDest_->bounds_lat_2d(n,i,j);
          }
        }
    }
    else
    {
      boundsLonDest = domainDest_->bounds_lon_1d;
      boundsLatDest = domainDest_->bounds_lat_1d;
    }
  }
  else
  {
    bool isNorthPole = false;
    bool isSouthPole = false;

    CArray<double,1> lon_g ;
    CArray<double,1> lat_g ;

    if (!domainDest_->lonvalue_1d.isEmpty() && !domainDest_->latvalue_1d.isEmpty())
    {
      domainDest_->AllgatherRectilinearLonLat(domainDest_->lonvalue_1d,domainDest_->latvalue_1d, lon_g,lat_g) ;
    }
    else if (! domainDest_->latvalue_rectilinear_read_from_file.isEmpty() && ! domainDest_->lonvalue_rectilinear_read_from_file.isEmpty() )
    {
      lat_g=domainDest_->latvalue_rectilinear_read_from_file ;
      lon_g=domainDest_->lonvalue_rectilinear_read_from_file ;
    }
    else if (!domainDest_->lon_start.isEmpty() && !domainDest_->lon_end.isEmpty() &&
             !domainDest_->lat_start.isEmpty() && !domainDest_->lat_end.isEmpty())
    {
      double step=(domainDest_->lon_end-domainDest_->lon_start)/domainDest_->ni_glo ;
      for(int i=0; i<domainDest_->ni_glo; ++i) lon_g(i)=domainDest_->lon_start+i*step ;
      step=(domainDest_->lat_end-domainDest_->lat_start)/domainDest_->nj_glo ;
      for(int i=0; i<domainDest_->ni_glo; ++i) lat_g(i)=domainDest_->lat_start+i*step ;
    }
    else ERROR("void CDomainAlgorithmInterpolate::computeRemap()",<<"Cannot compute bounds for rectilinear domain") ;
    
    if (std::abs(poleValue - std::abs(lat_g(0))) < NumTraits<double>::epsilon()) isNorthPole = true;
    if (std::abs(poleValue - std::abs(lat_g(domainDest_->nj_glo-1))) < NumTraits<double>::epsilon()) isSouthPole = true;




    if (isNorthPole && (0 == domainDest_->jbegin.getValue()))
    {
      int ibegin = domainDest_->ibegin.getValue();
      for (i = 0; i < niDest; ++i)
      {
        interpMapValueNorthPole[i+ibegin];
      }
    }

    if (isSouthPole && (domainDest_->nj_glo.getValue() == (domainDest_->jbegin.getValue() + njDest)))
    {
      int ibegin = domainDest_->ibegin.getValue();
      int njGlo = domainDest_->nj_glo.getValue();
      int niGlo = domainDest_->ni_glo.getValue();
      for (i = 0; i < niDest; ++i)
      {
        k = (njGlo - 1)*niGlo + i + ibegin;
        interpMapValueSouthPole[k];
      }
    }

    // Ok, fill in boundary values for rectangular domain
    nVertexDest = constNVertex;
    domainDest_->fillInRectilinearBoundLonLat(lon_g,lat_g, boundsLonDest, boundsLatDest);
  }
 
  if (domainDest_->hasArea) 
  {
    areaDest.resize(niDest*njDest);
    for (int j = 0; j < njDest; ++j)
      for (int i = 0; i < niDest; ++i)
      {
        int k = j * niDest + i;
        areaDest(k) = domainDest_->area(i,j);
      }
  }
 


  // Ok, now use mapper to calculate
  int nSrcLocal = domainSrc_->i_index.numElements();
  int nDstLocal = domainDest_->i_index.numElements();
  long int * globalSrc = new long int [nSrcLocal];
  long int * globalDst = new long int [nDstLocal];

  long int globalIndex;
  int i_ind, j_ind;
  for (int idx = 0; idx < nSrcLocal; ++idx)
  {
    i_ind=domainSrc_->i_index(idx) ;
    j_ind=domainSrc_->j_index(idx) ;

    globalIndex = i_ind + j_ind * domainSrc_->ni_glo;
    globalSrc[idx] = globalIndex;
  }

  for (int idx = 0; idx < nDstLocal; ++idx)
  {
    i_ind=domainDest_->i_index(idx) ;
    j_ind=domainDest_->j_index(idx) ;

    globalIndex = i_ind + j_ind * domainDest_->ni_glo;
    globalDst[idx] = globalIndex;
  }


  // Calculate weight index
  Mapper mapper(client->intraComm);
  mapper.setVerbosity(PROGRESS) ;

     
  // supress masked data for the source
  int nSrcLocalUnmasked = 0 ;
  for (int idx=0 ; idx < nSrcLocal; idx++) if (domainSrc_->localMask(idx)) ++nSrcLocalUnmasked ;


  CArray<double,2> boundsLonSrcUnmasked(nVertexSrc,nSrcLocalUnmasked);
  CArray<double,2> boundsLatSrcUnmasked(nVertexSrc,nSrcLocalUnmasked);
  CArray<double,1> areaSrcUnmasked(nSrcLocalUnmasked);
  
  long int * globalSrcUnmasked = new long int [nSrcLocalUnmasked];

  nSrcLocalUnmasked=0 ;
  bool hasSrcArea=domainSrc_->hasArea && !domainSrc_->radius.isEmpty() && !interpDomain_->use_area.isEmpty() && interpDomain_->use_area==true  ;
  double srcAreaFactor ;
  if (hasSrcArea) srcAreaFactor=1./(domainSrc_->radius*domainSrc_->radius) ;
  
  for (int idx=0 ; idx < nSrcLocal; idx++)
  {
    if (domainSrc_->localMask(idx))
    {
      for(int n=0;n<nVertexSrc;++n)
      {
        boundsLonSrcUnmasked(n,nSrcLocalUnmasked) = boundsLonSrc(n,idx) ;
        boundsLatSrcUnmasked(n,nSrcLocalUnmasked) = boundsLatSrc(n,idx) ;
      }
      if (hasSrcArea) areaSrcUnmasked(nSrcLocalUnmasked) = areaSrc(idx)*srcAreaFactor ;
      globalSrcUnmasked[nSrcLocalUnmasked]=globalSrc[idx] ;
      ++nSrcLocalUnmasked ;
    }
  }
 

  int nDstLocalUnmasked = 0 ;
  for (int idx=0 ; idx < nDstLocal; idx++) if (domainDest_->localMask(idx)) ++nDstLocalUnmasked ;

  CArray<double,2> boundsLonDestUnmasked(nVertexDest,nDstLocalUnmasked);
  CArray<double,2> boundsLatDestUnmasked(nVertexDest,nDstLocalUnmasked);
  CArray<double,1>   areaDstUnmasked(nDstLocalUnmasked);

  long int * globalDstUnmasked = new long int [nDstLocalUnmasked];

  nDstLocalUnmasked=0 ;
  bool hasDstArea=domainDest_->hasArea && !domainDest_->radius.isEmpty() && !interpDomain_->use_area.isEmpty() && interpDomain_->use_area==true ;
  double dstAreaFactor ;
  if (hasDstArea) dstAreaFactor=1./(domainDest_->radius*domainDest_->radius) ;
  for (int idx=0 ; idx < nDstLocal; idx++)
  {
    if (domainDest_->localMask(idx))
    {
      for(int n=0;n<nVertexDest;++n)
      {
        boundsLonDestUnmasked(n,nDstLocalUnmasked) = boundsLonDest(n,idx) ;
        boundsLatDestUnmasked(n,nDstLocalUnmasked) = boundsLatDest(n,idx) ;
      }
      if (hasDstArea) areaDstUnmasked(nDstLocalUnmasked) = areaDest(idx)*dstAreaFactor ;
      globalDstUnmasked[nDstLocalUnmasked]=globalDst[idx] ;
      ++nDstLocalUnmasked ;
    }
  }

  double* ptAreaSrcUnmasked = NULL ;
  if (hasSrcArea) ptAreaSrcUnmasked=areaSrcUnmasked.dataFirst() ;

  double* ptAreaDstUnmasked = NULL ;
  if (hasDstArea) ptAreaDstUnmasked=areaDstUnmasked.dataFirst() ;

  mapper.setSourceMesh(boundsLonSrcUnmasked.dataFirst(), boundsLatSrcUnmasked.dataFirst(), ptAreaSrcUnmasked, nVertexSrc, nSrcLocalUnmasked, &srcPole[0], globalSrcUnmasked);
  mapper.setTargetMesh(boundsLonDestUnmasked.dataFirst(), boundsLatDestUnmasked.dataFirst(), ptAreaDstUnmasked, nVertexDest, nDstLocalUnmasked, &dstPole[0], globalDstUnmasked);

  std::vector<double> timings = mapper.computeWeights(orderInterp,renormalize,quantity);

  std::map<int,std::vector<std::pair<int,double> > > interpMapValue;
  std::map<int,std::vector<std::pair<int,double> > >::const_iterator iteNorthPole = interpMapValueNorthPole.end(),
                                                                     iteSouthPole = interpMapValueSouthPole.end();
  for (int idx = 0;  idx < mapper.nWeights; ++idx)
  {
    interpMapValue[mapper.targetWeightId[idx]].push_back(make_pair(mapper.sourceWeightId[idx],mapper.remapMatrix[idx]));
    if (iteNorthPole != interpMapValueNorthPole.find(mapper.targetWeightId[idx]))
    {
      interpMapValueNorthPole[mapper.targetWeightId[idx]].push_back(make_pair(mapper.sourceWeightId[idx],mapper.remapMatrix[idx]));
    }

    if (iteSouthPole != interpMapValueSouthPole.find(mapper.targetWeightId[idx]))
    {
      interpMapValueSouthPole[mapper.targetWeightId[idx]].push_back(make_pair(mapper.sourceWeightId[idx],mapper.remapMatrix[idx]));
    }
  }
  int niGloDst = domainDest_->ni_glo.getValue();
  processPole(interpMapValueNorthPole, niGloDst);
  processPole(interpMapValueSouthPole, niGloDst);

  if (!interpMapValueNorthPole.empty())
  {
     std::map<int,std::vector<std::pair<int,double> > >::iterator itNorthPole = interpMapValueNorthPole.begin();
     for (; itNorthPole != iteNorthPole; ++itNorthPole)
     {
       if (!(itNorthPole->second.empty()))
        itNorthPole->second.swap(interpMapValue[itNorthPole->first]);
     }
  }

  if (!interpMapValueSouthPole.empty())
  {
     std::map<int,std::vector<std::pair<int,double> > >::iterator itSouthPole = interpMapValueSouthPole.begin();
     for (; itSouthPole != iteSouthPole; ++itSouthPole)
     {
       if (!(itSouthPole->second.empty()))
        itSouthPole->second.swap(interpMapValue[itSouthPole->first]);
     }
  }

  if (writeToFile_ && !readFromFile_) writeRemapInfo(interpMapValue);
//  exchangeRemapInfo(interpMapValue);
  convertRemapInfo(interpMapValue) ;

  delete [] globalSrc;
  delete [] globalSrcUnmasked;
  delete [] globalDst;
  delete [] globalDstUnmasked;

}
CATCH

void CDomainAlgorithmInterpolate::processPole(std::map<int,std::vector<std::pair<int,double> > >& interMapValuePole,
                                              int nbGlobalPointOnPole)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;

  MPI_Comm poleComme(MPI_COMM_NULL);
  MPI_Comm_split(client->intraComm, interMapValuePole.empty() ? MPI_UNDEFINED : 1, 0, &poleComme);
  if (MPI_COMM_NULL != poleComme)
  {
    int nbClientPole;
    MPI_Comm_size(poleComme, &nbClientPole);

    std::map<int,std::vector<std::pair<int,double> > >::iterator itePole = interMapValuePole.end(), itPole,
                                                                 itbPole = interMapValuePole.begin();

    int nbWeight = 0;
    for (itPole = itbPole; itPole != itePole; ++itPole)
       nbWeight += itPole->second.size();

    std::vector<int> recvCount(nbClientPole,0);
    std::vector<int> displ(nbClientPole,0);
    MPI_Allgather(&nbWeight,1,MPI_INT,&recvCount[0],1,MPI_INT,poleComme) ;

    displ[0]=0;
    for(int n=1;n<nbClientPole;++n) displ[n]=displ[n-1]+recvCount[n-1] ;
    int recvSize=displ[nbClientPole-1]+recvCount[nbClientPole-1] ;

    std::vector<int> sendSourceIndexBuff(nbWeight);
    std::vector<double> sendSourceWeightBuff(nbWeight);
    int k = 0;
    for (itPole = itbPole; itPole != itePole; ++itPole)
    {
      for (int idx = 0; idx < itPole->second.size(); ++idx)
      {
        sendSourceIndexBuff[k] = (itPole->second)[idx].first;
        sendSourceWeightBuff[k] = (itPole->second)[idx].second;
        ++k;
      }
    }

    std::vector<int> recvSourceIndexBuff(recvSize);
    std::vector<double> recvSourceWeightBuff(recvSize);

    // Gather all index and weight for pole
    MPI_Allgatherv(&sendSourceIndexBuff[0],nbWeight,MPI_INT,&recvSourceIndexBuff[0],&recvCount[0],&displ[0],MPI_INT,poleComme);
    MPI_Allgatherv(&sendSourceWeightBuff[0],nbWeight,MPI_DOUBLE,&recvSourceWeightBuff[0],&recvCount[0],&displ[0],MPI_DOUBLE,poleComme);

    std::map<int,double> recvTemp;
    for (int idx = 0; idx < recvSize; ++idx)
    {
      if (recvTemp.end() != recvTemp.find(recvSourceIndexBuff[idx]))
        recvTemp[recvSourceIndexBuff[idx]] += recvSourceWeightBuff[idx]/nbGlobalPointOnPole;
      else
        recvTemp[recvSourceIndexBuff[idx]] = recvSourceWeightBuff[idx]/nbGlobalPointOnPole;
    }

    std::map<int,double>::const_iterator itRecvTemp, itbRecvTemp = recvTemp.begin(), iteRecvTemp = recvTemp.end();

    for (itPole = itbPole; itPole != itePole; ++itPole)
    {
      itPole->second.clear();
      for (itRecvTemp = itbRecvTemp; itRecvTemp != iteRecvTemp; ++itRecvTemp)
          itPole->second.push_back(make_pair(itRecvTemp->first, itRecvTemp->second));
    }
  }

}
CATCH

/*!
  Compute the index mapping between domain on grid source and one on grid destination
*/
void CDomainAlgorithmInterpolate::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  if (readFromFile_)  
    readRemapInfo();
  else
  {
    computeRemap(); 
  }
}
CATCH

void CDomainAlgorithmInterpolate::writeRemapInfo(std::map<int,std::vector<std::pair<int,double> > >& interpMapValue)
TRY
{  
  writeInterpolationInfo(fileToReadWrite_, interpMapValue);
}
CATCH

void CDomainAlgorithmInterpolate::readRemapInfo()
TRY
{  
  std::map<int,std::vector<std::pair<int,double> > > interpMapValue;
  readInterpolationInfo(fileToReadWrite_, interpMapValue);

  exchangeRemapInfo(interpMapValue);
}
CATCH

void CDomainAlgorithmInterpolate::convertRemapInfo(std::map<int,std::vector<std::pair<int,double> > >& interpMapValue)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;

  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  std::map<int,std::vector<std::pair<int,double> > >::const_iterator itb = interpMapValue.begin(), it,
                                                                     ite = interpMapValue.end();
  
  for (it = itb; it != ite; ++it)
  {    
    const std::vector<std::pair<int,double> >& tmp = it->second;
    for (int i = 0; i < tmp.size(); ++i)
    {
      transMap[it->first].push_back(tmp[i].first);
      transWeight[it->first].push_back(tmp[i].second);
    }      
  }      
}
CATCH

/*!
  Read remap information from file then distribute it among clients
*/
void CDomainAlgorithmInterpolate::exchangeRemapInfo(std::map<int,std::vector<std::pair<int,double> > >& interpMapValue)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;

  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  std::unordered_map<size_t,int> globalIndexOfDomainDest;
  int ni = domainDest_->ni.getValue();
  int nj = domainDest_->nj.getValue();
  int ni_glo = domainDest_->ni_glo.getValue();
  size_t globalIndex;
  int nIndexSize = domainDest_->i_index.numElements(), i_ind, j_ind;
  for (int idx = 0; idx < nIndexSize; ++idx)
  {
    i_ind=domainDest_->i_index(idx) ;
    j_ind=domainDest_->j_index(idx) ;

    globalIndex = i_ind + j_ind * ni_glo;
    globalIndexOfDomainDest[globalIndex] = clientRank;
  }

  CClientServerMappingDistributed domainIndexClientClientMapping(globalIndexOfDomainDest,
                                                                 client->intraComm,
                                                                 true);
  CArray<size_t,1> globalIndexInterp(interpMapValue.size());
  std::map<int,std::vector<std::pair<int,double> > >::const_iterator itb = interpMapValue.begin(), it,
                                                                     ite = interpMapValue.end();
  size_t globalIndexCount = 0;
  for (it = itb; it != ite; ++it)
  {
    globalIndexInterp(globalIndexCount) = it->first;
    ++globalIndexCount;
  }

  domainIndexClientClientMapping.computeServerIndexMapping(globalIndexInterp, client->serverSize);
  const CClientServerMapping::GlobalIndexMap& globalIndexInterpSendToClient = domainIndexClientClientMapping.getGlobalIndexOnServer();

  //Inform each client number of index they will receive
  int nbClient = client->clientSize;
  int* sendBuff = new int[nbClient];
  int* recvBuff = new int[nbClient];

  int* sendParticipants = new int[nbClient];
  int* recvParticipants = new int[nbClient];
  
  for (int i = 0; i < nbClient; ++i)
  {
    sendBuff[i] = 0;
    recvBuff[i] = 0;
    sendParticipants[i]=0 ;
    recvParticipants[i]=0 ;
  }
  int sendBuffSize = 0;
  CClientServerMapping::GlobalIndexMap::const_iterator itbMap = globalIndexInterpSendToClient.begin(), itMap,
                                                       iteMap = globalIndexInterpSendToClient.end();
  for (itMap = itbMap; itMap != iteMap; ++itMap)
  {
    const std::vector<size_t>& tmp = itMap->second;
    int sizeIndex = 0, mapSize = (itMap->second).size();
    for (int idx = 0; idx < mapSize; ++idx)
    {
//      sizeIndex += interpMapValue.at((itMap->second)[idx]).size();
      sizeIndex += (interpMapValue[(int)(itMap->second)[idx]]).size();
    }
    sendBuff[itMap->first] = sizeIndex;
    sendParticipants[itMap->first] = 1 ;
    sendBuffSize += sizeIndex;
  }

  MPI_Allreduce(sendBuff, recvBuff, nbClient, MPI_INT, MPI_SUM, client->intraComm);
  MPI_Allreduce(sendParticipants, recvParticipants, nbClient, MPI_INT, MPI_SUM, client->intraComm);

  int* sendIndexDestBuff = new int [sendBuffSize];
  int* sendIndexSrcBuff  = new int [sendBuffSize];
  double* sendWeightBuff = new double [sendBuffSize];

  std::vector<MPI_Request> sendRequest;

  int sendOffSet = 0, l = 0;
  for (itMap = itbMap; itMap != iteMap; ++itMap)
  {
    const std::vector<size_t>& indexToSend = itMap->second;
    int mapSize = indexToSend.size();
    int k = 0;
    for (int idx = 0; idx < mapSize; ++idx)
    {
      std::vector<std::pair<int,double> >& interpMap = interpMapValue[(int)indexToSend[idx]]; //interpMapValue.at(indexToSend[idx]);
      for (int i = 0; i < interpMap.size(); ++i)
      {
        sendIndexDestBuff[l] = indexToSend[idx];
        sendIndexSrcBuff[l]  = interpMap[i].first;
        sendWeightBuff[l]    = interpMap[i].second;
        ++k;
        ++l;
      }
    }
    
    sendRequest.push_back(MPI_Request());
    MPI_Isend(&clientRank,
             1,
             MPI_INT,
             itMap->first,
             MPI_DOMAIN_INTERPOLATION_SOURCE_RANK,
             client->intraComm,
             &sendRequest.back());

    sendRequest.push_back(MPI_Request());
    MPI_Isend(sendIndexDestBuff + sendOffSet,
             k,
             MPI_INT,
             itMap->first,
             MPI_DOMAIN_INTERPOLATION_DEST_INDEX,
             client->intraComm,
             &sendRequest.back());
    sendRequest.push_back(MPI_Request());
    MPI_Isend(sendIndexSrcBuff + sendOffSet,
             k,
             MPI_INT,
             itMap->first,
             MPI_DOMAIN_INTERPOLATION_SRC_INDEX,
             client->intraComm,
             &sendRequest.back());
    sendRequest.push_back(MPI_Request());
    MPI_Isend(sendWeightBuff + sendOffSet,
             k,
             MPI_DOUBLE,
             itMap->first,
             MPI_DOMAIN_INTERPOLATION_WEIGHT,
             client->intraComm,
             &sendRequest.back());
    sendOffSet += k;
  }

  int recvBuffSize = recvBuff[clientRank];
  int numberOfParticipants = recvParticipants[clientRank] ;

  int* recvIndexDestBuff = new int [recvBuffSize];
  int* recvIndexSrcBuff  = new int [recvBuffSize];
  double* recvWeightBuff = new double [recvBuffSize];
  int receivedSize = 0;
  int clientSrcRank;
 
 
 // this part is done to impose a specific order for reception to retrive reproducibility 
  set<int> rankOrder ; 
  for (int np=0 ; np < numberOfParticipants; ++np)
  {
    MPI_Status recvStatus;
    int rank ;
    MPI_Recv(&rank,
             1,
             MPI_INT,
             MPI_ANY_SOURCE,
             MPI_DOMAIN_INTERPOLATION_SOURCE_RANK,
             client->intraComm,
             &recvStatus);
    rankOrder.insert(rank) ;
  }
  
  for (auto  clientSrcRank : rankOrder)
  {
    MPI_Status recvStatus;
    MPI_Recv((recvIndexDestBuff + receivedSize),
             recvBuffSize,
             MPI_INT,
             clientSrcRank,
             MPI_DOMAIN_INTERPOLATION_DEST_INDEX,
             client->intraComm,
             &recvStatus);

    int countBuff = 0;
    MPI_Get_count(&recvStatus, MPI_INT, &countBuff);
//    clientSrcRank = recvStatus.MPI_SOURCE;

    MPI_Recv((recvIndexSrcBuff + receivedSize),
             recvBuffSize,
             MPI_INT,
             clientSrcRank,
             MPI_DOMAIN_INTERPOLATION_SRC_INDEX,
             client->intraComm,
             &recvStatus);

    MPI_Recv((recvWeightBuff + receivedSize),
             recvBuffSize,
             MPI_DOUBLE,
             clientSrcRank,
             MPI_DOMAIN_INTERPOLATION_WEIGHT,
             client->intraComm,
             &recvStatus);

    for (int idx = 0; idx < countBuff; ++idx)
    {
      transMap[*(recvIndexDestBuff + receivedSize + idx)].push_back(*(recvIndexSrcBuff + receivedSize + idx));
      transWeight[*(recvIndexDestBuff + receivedSize + idx)].push_back(*(recvWeightBuff + receivedSize + idx));
    }
    receivedSize += countBuff;
  }
  
  MPI_Waitall(sendRequest.size(), &sendRequest[0], MPI_STATUS_IGNORE);

  delete [] sendParticipants ;
  delete [] recvParticipants ;
  delete [] sendIndexDestBuff;
  delete [] sendIndexSrcBuff;
  delete [] sendWeightBuff;
  delete [] recvIndexDestBuff;
  delete [] recvIndexSrcBuff;
  delete [] recvWeightBuff;
  delete [] sendBuff;
  delete [] recvBuff;
}
CATCH
 
/*! Redefined some functions of CONetCDF4 to make use of them */
CDomainAlgorithmInterpolate::WriteNetCdf::WriteNetCdf(const StdString& filename, const MPI_Comm comm)
  : CNc4DataOutput(NULL, filename, false, false, true, comm, false, true) {}
int CDomainAlgorithmInterpolate::WriteNetCdf::addDimensionWrite(const StdString& name, 
                                                                const StdSize size)
TRY
{
  return CONetCDF4::addDimension(name, size);  
}
CATCH

int CDomainAlgorithmInterpolate::WriteNetCdf::addVariableWrite(const StdString& name, nc_type type,
                                                               const std::vector<StdString>& dim)
TRY
{
  return CONetCDF4::addVariable(name, type, dim);
}
CATCH

void CDomainAlgorithmInterpolate::WriteNetCdf::endDefinition()
TRY
{
  CONetCDF4::definition_end();
}
CATCH

void CDomainAlgorithmInterpolate::WriteNetCdf::writeDataIndex(const CArray<int,1>& data, const StdString& name,
                                                              bool collective, StdSize record,
                                                              const std::vector<StdSize>* start,
                                                              const std::vector<StdSize>* count)
TRY
{
  CONetCDF4::writeData<int,1>(data, name, collective, record, start, count);
}
CATCH

void CDomainAlgorithmInterpolate::WriteNetCdf::writeDataIndex(const CArray<double,1>& data, const StdString& name,
                                                              bool collective, StdSize record,
                                                              const std::vector<StdSize>* start,
                                                              const std::vector<StdSize>* count)
TRY
{
  CONetCDF4::writeData<double,1>(data, name, collective, record, start, count);
}
CATCH

/*
   Write interpolation weights into a file
   \param [in] filename name of output file
   \param interpMapValue mapping of global index of domain destination and domain source as well as the corresponding weight
*/
void CDomainAlgorithmInterpolate::writeInterpolationInfo(std::string& filename,
                                                         std::map<int,std::vector<std::pair<int,double> > >& interpMapValue)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;

  size_t n_src = domainSrc_->ni_glo * domainSrc_->nj_glo;
  size_t n_dst = domainDest_->ni_glo * domainDest_->nj_glo;

  long localNbWeight = 0;
  long globalNbWeight;
  long startIndex;
  typedef std::map<int,std::vector<std::pair<int,double> > > IndexRemap;
  IndexRemap::iterator itb = interpMapValue.begin(), it,
                       ite = interpMapValue.end();
  for (it = itb; it!=ite; ++it)
  {
    localNbWeight += (it->second).size();
  }

  CArray<int,1> src_idx(localNbWeight);
  CArray<int,1> dst_idx(localNbWeight);
  CArray<double,1> weights(localNbWeight);

  int index = 0;
  int indexOffset=0 ;
  if (fortranConvention) indexOffset=1 ;
  for (it = itb; it !=ite; ++it)
  {
    std::vector<std::pair<int,double> >& tmp = it->second;
    for (int idx = 0; idx < tmp.size(); ++idx)
    {
      dst_idx(index) = it->first + indexOffset;
      src_idx(index) = tmp[idx].first + indexOffset;
      weights(index) = tmp[idx].second;
      ++index;
    }    
  }

  MPI_Allreduce(&localNbWeight, &globalNbWeight, 1, MPI_LONG, MPI_SUM, client->intraComm);
  MPI_Scan(&localNbWeight, &startIndex, 1, MPI_LONG, MPI_SUM, client->intraComm);
  
  if (0 == globalNbWeight)
  {
    info << "There is no interpolation weights calculated between "
         << "domain source: " << domainSrc_->getDomainOutputName()
         << " and domain destination: " << domainDest_->getDomainOutputName()
         << std::endl;
    return;
  }

  std::vector<StdSize> start(1, startIndex - localNbWeight);
  std::vector<StdSize> count(1, localNbWeight);
  
  WriteNetCdf netCdfWriter(filename, client->intraComm);  

  // Define some dimensions
  netCdfWriter.addDimensionWrite("n_src", n_src);
  netCdfWriter.addDimensionWrite("n_dst", n_dst);
  netCdfWriter.addDimensionWrite("n_weight", globalNbWeight);
  
  std::vector<StdString> dims(1,"n_weight");

  // Add some variables
  netCdfWriter.addVariableWrite("src_idx", NC_INT, dims);
  netCdfWriter.addVariableWrite("dst_idx", NC_INT, dims);
  netCdfWriter.addVariableWrite("weight", NC_DOUBLE, dims);

  // End of definition
  netCdfWriter.endDefinition();

  // // Write variables
  if (0 != localNbWeight)
  {
    netCdfWriter.writeDataIndex(src_idx, "src_idx", false, 0, &start, &count);
    netCdfWriter.writeDataIndex(dst_idx, "dst_idx", false, 0, &start, &count);
    netCdfWriter.writeDataIndex(weights, "weight", false, 0, &start, &count);
  }

  netCdfWriter.closeFile();
}
CATCH

/*!
  Read interpolation information from a file
  \param [in] filename interpolation file
  \param [in/out] interpMapValue Mapping between (global) index of domain on grid destination and
         corresponding global index of domain and associated weight value on grid source
*/
void CDomainAlgorithmInterpolate::readInterpolationInfo(std::string& filename,
                                                        std::map<int,std::vector<std::pair<int,double> > >& interpMapValue)
TRY
{
  int ncid ;
  int weightDimId ;
  size_t nbWeightGlo ;


  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int clientSize = client->clientSize;


  {
    ifstream f(filename.c_str());
    if (!f.good()) ERROR("void CDomainAlgorithmInterpolate::readInterpolationInfo",
                      << "Attempt to read file weight :"  << filename << " which doesn't seem to exist." << std::endl
                      << "Please check this file ");
  }
                  
  nc_open(filename.c_str(),NC_NOWRITE, &ncid) ;
  nc_inq_dimid(ncid,"n_weight",&weightDimId) ;
  nc_inq_dimlen(ncid,weightDimId,&nbWeightGlo) ;

  size_t nbWeight ;
  size_t start ;
  size_t div = nbWeightGlo/clientSize ;
  size_t mod = nbWeightGlo%clientSize ;
  if (clientRank < mod)
  {
    nbWeight=div+1 ;
    start=clientRank*(div+1) ;
  }
  else
  {
    nbWeight=div ;
    start= mod * (div+1) + (clientRank-mod) * div ;
  }

  double* weight=new double[nbWeight] ;
  int weightId ;
  nc_inq_varid (ncid, "weight", &weightId) ;
  nc_get_vara_double(ncid, weightId, &start, &nbWeight, weight) ;

  long* srcIndex=new long[nbWeight] ;
  int srcIndexId ;
  nc_inq_varid (ncid, "src_idx", &srcIndexId) ;
  nc_get_vara_long(ncid, srcIndexId, &start, &nbWeight, srcIndex) ;

  long* dstIndex=new long[nbWeight] ;
  int dstIndexId ;
  nc_inq_varid (ncid, "dst_idx", &dstIndexId) ;
  nc_get_vara_long(ncid, dstIndexId, &start, &nbWeight, dstIndex) ;

  int indexOffset=0 ;
  if (fortranConvention) indexOffset=1 ;
    for(size_t ind=0; ind<nbWeight;++ind)
      interpMapValue[dstIndex[ind]-indexOffset].push_back(make_pair(srcIndex[ind]-indexOffset,weight[ind]));
 }
CATCH

void CDomainAlgorithmInterpolate::apply(const std::vector<std::pair<int,double> >& localIndex,
                                            const double* dataInput,
                                            CArray<double,1>& dataOut,
                                            std::vector<bool>& flagInitial,
                                            bool ignoreMissingValue, bool firstPass  )
TRY
{
  int nbLocalIndex = localIndex.size();   
  double defaultValue = std::numeric_limits<double>::quiet_NaN();
   
  if (detectMissingValue)
  {
     if (firstPass && renormalize)
     {
       renormalizationFactor.resize(dataOut.numElements()) ;
       renormalizationFactor=1 ;
     }

    if (firstPass)
    {
      allMissing.resize(dataOut.numElements()) ;
      allMissing=true ;
    }

    for (int idx = 0; idx < nbLocalIndex; ++idx)
    {
      if (NumTraits<double>::isNan(*(dataInput + idx)))
      {
        allMissing(localIndex[idx].first) = allMissing(localIndex[idx].first) && true;
        if (renormalize) renormalizationFactor(localIndex[idx].first)-=localIndex[idx].second ;
      }
      else
      {
        dataOut(localIndex[idx].first) += *(dataInput + idx) * localIndex[idx].second;
        allMissing(localIndex[idx].first) = allMissing(localIndex[idx].first) && false; // Reset flag to indicate not all data source are nan
      }
    }

  }
  else
  {
    for (int idx = 0; idx < nbLocalIndex; ++idx)
    {
      dataOut(localIndex[idx].first) += *(dataInput + idx) * localIndex[idx].second;
    }
  }
}
CATCH

void CDomainAlgorithmInterpolate::updateData(CArray<double,1>& dataOut)
TRY
{
  if (detectMissingValue)
  {
    double defaultValue = std::numeric_limits<double>::quiet_NaN();
    size_t nbIndex=dataOut.numElements() ; 

    if (allMissing.numElements()>0)
    {
      for (int idx = 0; idx < nbIndex; ++idx)
      {
        if (allMissing(idx)) dataOut(idx) = defaultValue; // If all data source are nan then data destination must be nan
      }
    }
    else
    {
      for (int idx = 0; idx < nbIndex; ++idx)
      {
        dataOut(idx) = defaultValue; // If allMissing has no element means you have no source element so target is NaN
      }
    }
    if (renormalize)
    {
      if (renormalizationFactor.numElements()>0) dataOut/=renormalizationFactor ; // In some case, process doesn't received any data for interpolation (mask)
                                                                                 // so renormalizationFactor is not initialized
    }
  }
}
CATCH

}
