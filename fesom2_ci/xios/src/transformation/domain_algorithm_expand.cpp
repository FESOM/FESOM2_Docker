/*!
   \file domain_algorithm_expand.cpp
   \author Ha NGUYEN
   \since 08 Aug 2016
   \date 19 Sep 2016

   \brief Algorithm for expanding an domain.
 */
#include "domain_algorithm_expand.hpp"
#include "expand_domain.hpp"
#include "mesh.hpp"
#include "domain.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "context.hpp"
#include "context_client.hpp"

namespace xios {
CGenericAlgorithmTransformation* CDomainAlgorithmExpand::create(CGrid* gridDst, CGrid* gridSrc,
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

  CExpandDomain* expandDomain = dynamic_cast<CExpandDomain*> (transformation);
  int domainDstIndex = elementPositionInGridDst2DomainPosition[elementPositionInGrid];
  int domainSrcIndex = elementPositionInGridSrc2DomainPosition[elementPositionInGrid];

  return (new CDomainAlgorithmExpand(domainListDestP[domainDstIndex], domainListSrcP[domainSrcIndex], expandDomain));
}
CATCH

bool CDomainAlgorithmExpand::registerTrans()
TRY
{
  return CGridTransformationFactory<CDomain>::registerTransformation(TRANS_EXPAND_DOMAIN, create);
}
CATCH

CDomainAlgorithmExpand::CDomainAlgorithmExpand(CDomain* domainDestination,
                                               CDomain* domainSource,
                                               CExpandDomain* expandDomain)
: CDomainAlgorithmTransformation(domainDestination, domainSource),
  isXPeriodic_(false), isYPeriodic_(false)
TRY
{
  if (domainDestination == domainSource)
  {
    ERROR("CDomainAlgorithmExpand::CDomainAlgorithmExpand(CDomain* domainDestination,CDomain* domainSource, CExpandDomain* expandDomain)",
           << "Domain source and domain destination are the same. Please make sure domain destination refers to domain source" << std::endl
           << "Domain source " <<domainSource->getId() << std::endl
           << "Domain destination " <<domainDestination->getId() << std::endl);
  }

  this->type_ = (ELEMENT_MODIFICATION_WITH_DATA);
  // Make sure domain source have all valid attributes
  // domainSource->checkAllAttributes();
  domainSource->initLonLatValue();
  expandDomain->checkValid(domainDestination);
  if (!expandDomain->i_periodic.isEmpty()) isXPeriodic_ = expandDomain->i_periodic;
  if (!expandDomain->j_periodic.isEmpty()) isYPeriodic_ = expandDomain->j_periodic;
  
  switch (expandDomain->type)
  {
    case CExpandDomain::type_attr::node :
      expandDomainNodeConnectivity(domainDestination,
                                   domainSource);
      break;
    case CExpandDomain::type_attr::edge :
      expandDomainEdgeConnectivity(domainDestination,
                                   domainSource);
      break;
    default:
      break;
  }
}
CATCH

/*!
 *  Expand domain with edge-type neighbor
 *  \param[in/out] domainDestination domain destination and will be modified
 *  \param[in] domainSource domain source
 */
void CDomainAlgorithmExpand::expandDomainEdgeConnectivity(CDomain* domainDestination,
                                                          CDomain* domainSource)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;

  int type = 1; // For edge
  CMesh mesh;
  CArray<double,2>& bounds_lon_src = domainSource->bounds_lon_1d;
  CArray<double,2>& bounds_lat_src = domainSource->bounds_lat_1d;
  CArray<int,2> neighborsSrc;
  switch (domainSource->type) {
   case CDomain::type_attr::unstructured:      
      mesh.getGlobalNghbFaces(type, client->intraComm, domainSource->i_index, bounds_lon_src, bounds_lat_src, neighborsSrc);
      updateUnstructuredDomainAttributes(domainDestination, domainSource, neighborsSrc);
      break;
   default:
      updateRectilinearDomainAttributes(domainDestination, domainSource, neighborsSrc);
      break;      
  }  
}
CATCH

/*!
 *  Expand domain with node-type neighbor
 *  \param[in/out] domainDestination domain destination and will be modified
 *  \param[in] domainSource domain source
 */
void CDomainAlgorithmExpand::expandDomainNodeConnectivity(CDomain* domainDestination,
                                                          CDomain* domainSource)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;

  int type = 1; // For edge
  CMesh mesh;
  CArray<double,2>& bounds_lon_src = domainSource->bounds_lon_1d;
  CArray<double,2>& bounds_lat_src = domainSource->bounds_lat_1d;
  CArray<int,2> neighborsSrc;
  switch (domainSource->type) {
   case CDomain::type_attr::unstructured:      
      mesh.getGlobalNghbFaces(type, client->intraComm, domainSource->i_index, bounds_lon_src, bounds_lat_src, neighborsSrc);
      updateUnstructuredDomainAttributes(domainDestination, domainSource, neighborsSrc);
      break;
   default:
      updateRectilinearDomainAttributes(domainDestination, domainSource, neighborsSrc);
      break;      
  }  
}
CATCH

/*!
 *  Extend rectilinear or curvilinear domain destination and update its attributes
 *  Suppose that domain destination and domain source have the same values for all attributes (by inheritance)
 *  \param [in/out] domainDestination domain destination
 *  \param [in] domainSource domain source
 *  \param [in] neighborsDomainSrc neighbor of domain source. For now, we don't need it for rectilinear
 */
void CDomainAlgorithmExpand::updateRectilinearDomainAttributes(CDomain* domainDestination,
                                                               CDomain* domainSource,
                                                               CArray<int,2>& neighborsDomainSrc)
TRY
{
  int index, globalIndex, idx;
  int iindexDst, jindexDst, globIndexDst;
  int iindexSrc, jindexSrc, globIndexSrc;
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;

  // First of all, "copy" all attributes of domain source to domain destination
  StdString domainDstRef = (!domainDestination->domain_ref.isEmpty()) ? domainDestination->domain_ref.getValue()
                                                                      : "";
  if (domainDstRef != domainSource->getId())
  {
    domainDestination->domain_ref.setValue(domainSource->getId());
    domainDestination->solveRefInheritance(true);
  }

  if (domainDstRef.empty()) domainDestination->domain_ref.reset();
  else domainDestination->domain_ref.setValue(domainDstRef);

  
  // Here are attributes of source need tranfering
  int niGloSrc = domainSource->ni_glo;
  int njGloSrc = domainSource->nj_glo;
  int niSrc = domainSource->ni, ibegin = domainSource->ibegin;
  int njSrc = domainSource->nj, jbegin = domainSource->jbegin;
  int dataDimSrc = domainSource->data_dim;
  CArray<bool,1>& mask_1d_src = domainSource->domainMask;
  CArray<int,1>& i_index_src = domainSource->i_index;
  CArray<int,1>& j_index_src = domainSource->j_index;
  CArray<int,1>& data_i_index_src = domainSource->data_i_index;
  CArray<int,1>& data_j_index_src = domainSource->data_j_index;
  int data_i_begin_src = domainSource->data_ibegin;
  int data_j_begin_src = domainSource->data_jbegin;
  CArray<double,1>& lon_src = domainSource->lonvalue;
  CArray<double,1>& lat_src = domainSource->latvalue;
  CArray<double,1> lon_g;
  CArray<double,1> lat_g;

  // We need to generate boundary for longitude and latitude
  if (domainSource->bounds_lon_1d.isEmpty() || domainSource->bounds_lat_1d.isEmpty())
  {
    CArray<double,1> lon = lon_src(Range(0,niSrc-1));
    CArray<double,1> lat = lat_src(Range(0,lat_src.numElements()-niSrc,niSrc));
    CArray<double,2>& bounds_lon_src = domainSource->bounds_lon_1d;
    CArray<double,2>& bounds_lat_src = domainSource->bounds_lat_1d;
    domainSource->AllgatherRectilinearLonLat(lon_src, lat_src, lon_g,lat_g);
    domainSource->fillInRectilinearBoundLonLat(lon_g, lat_g, bounds_lon_src, bounds_lat_src);
  }


  CArray<double,2>& bounds_lon_src = domainSource->bounds_lon_1d;
  CArray<double,2>& bounds_lat_src = domainSource->bounds_lat_1d;

  int nVertex       = bounds_lon_src.shape()[0];
  int oldNbLocal = i_index_src.numElements();
  // Calculate ni, nj by using i_index and j_index
  int niSrcByIndex = max(i_index_src) - min(i_index_src) + 1;
  int njSrcByIndex = max(j_index_src) - min(j_index_src) + 1;  
  int dataIindexBoundSrc = (1 == dataDimSrc) ? (niSrcByIndex * njSrcByIndex) : niSrcByIndex;
  int dataJindexBoundSrc = (1 == dataDimSrc) ? (niSrcByIndex * njSrcByIndex) : njSrcByIndex;

  // Uncompress data_i_index, data_j_index
  CArray<int,1> data_i_index_src_full(oldNbLocal);
  CArray<int,1> data_j_index_src_full(oldNbLocal);
  int nbUnMaskedPointOnLocalDomain = 0;
  data_i_index_src_full = -1; // Suppose all values are masked
  data_j_index_src_full = -1; // Suppose all values are masked
  for (idx = 0; idx < data_i_index_src.numElements(); ++idx)
  {
    int dataIidx = data_i_index_src(idx) + data_i_begin_src;
    int dataJidx = data_j_index_src(idx) + data_j_begin_src;
    if ((0 <= dataIidx) && (dataIidx < dataIindexBoundSrc) &&
        (0 <= dataJidx) && (dataJidx < dataJindexBoundSrc))
    {
      data_i_index_src_full(nbUnMaskedPointOnLocalDomain) = dataIidx;
      data_j_index_src_full(nbUnMaskedPointOnLocalDomain) = dataJidx;
      ++nbUnMaskedPointOnLocalDomain;
    }
  }

  // Expand domain destination, not only local but also global
  int niGloDst = niGloSrc + 2;
  int njGloDst = njGloSrc + 2;
  int niDst = niSrc + 2;
  int njDst = njSrc + 2;
  domainDestination->ni_glo.setValue(niGloDst);
  domainDestination->nj_glo.setValue(njGloDst);
  domainDestination->ni.setValue(niDst);
  domainDestination->nj.setValue(njDst);

  CArray<bool,1>& mask_1d_dst = domainDestination->domainMask;
  CArray<int,1>& i_index_dst  = domainDestination->i_index;
  CArray<int,1>& j_index_dst  = domainDestination->j_index;  
  CArray<int,1>& data_i_index_dst  = domainDestination->data_i_index;
  CArray<int,1>& data_j_index_dst  = domainDestination->data_j_index;
  
  // Make sure that we use only lonvalue_client, latvalue_client
  if (!domainDestination->lonvalue_1d.isEmpty()) domainDestination->lonvalue_1d.reset();
  if (!domainDestination->latvalue_1d.isEmpty()) domainDestination->latvalue_1d.reset();
  if (!domainDestination->lonvalue_2d.isEmpty()) domainDestination->lonvalue_2d.reset();
  if (!domainDestination->latvalue_2d.isEmpty()) domainDestination->latvalue_2d.reset();

  // Recalculate i_index, j_index of extended domain
  // Should be enough for common case, but if we have arbitrary distribution?
  int newNbLocalDst = niDst * njDst;     

  mask_1d_dst.resize(newNbLocalDst);
  i_index_dst.resize(newNbLocalDst);
  j_index_dst.resize(newNbLocalDst);
  CArray<int,1> data_i_index_dst_full(newNbLocalDst);
  CArray<int,1> data_j_index_dst_full(newNbLocalDst);

  domainDestination->lonvalue.resizeAndPreserve(newNbLocalDst);
  domainDestination->latvalue.resizeAndPreserve(newNbLocalDst);
  domainDestination->bounds_lon_1d.resizeAndPreserve(nVertex, newNbLocalDst);
  domainDestination->bounds_lat_1d.resizeAndPreserve(nVertex, newNbLocalDst);
  CArray<double,1>& lon_dst   = domainDestination->lonvalue;
  CArray<double,1>& lat_dst   = domainDestination->latvalue;
  CArray<double,2>& bounds_lon_dst = domainDestination->bounds_lon_1d;
  CArray<double,2>& bounds_lat_dst = domainDestination->bounds_lat_1d;

  // Update i_index, j_index
  for (int j = 0; j < njDst; ++j)
    for (int i = 0; i < niDst; ++i)
    {
      idx = j * niDst + i; 
      i_index_dst(idx) = i + ibegin;
      j_index_dst(idx) = j + jbegin;
    }
 

  // 1. Fill in array relating to global index (i_index, j_index, transmap, etc, ...)
  // Global index mapping between destination and source
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);
  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  transMap.rehash(std::ceil(newNbLocalDst/transMap.max_load_factor()));
  transWeight.rehash(std::ceil(newNbLocalDst/transWeight.max_load_factor()));
  
  // Index mapping for local domain
  // Mapping global index of expanded domain into original one 
  // (Representing global index of expanded domain in form of global index of original one)
  CArray<size_t,1> globalIndexSrcOnDstDomain(newNbLocalDst); 
  for (idx = 0; idx < newNbLocalDst; ++idx)
  {
    iindexDst = i_index_dst(idx);
    jindexDst = j_index_dst(idx);
    globIndexDst = jindexDst * niGloDst + iindexDst;
    globIndexSrc = (((jindexDst-1)+njGloSrc) % njGloSrc) * niGloSrc + (((iindexDst-1)+niGloSrc) % niGloSrc) ;
    globalIndexSrcOnDstDomain(idx) = globIndexSrc;

    transMap[globIndexDst].push_back(globIndexSrc);
    transWeight[globIndexDst].push_back(1.0); 
  }

  // 2. Exchange local info among domains (lon,lat,bounds,mask,etc,...)
  CClientClientDHTDouble::Index2VectorInfoTypeMap localData;
  localData.rehash(std::ceil(oldNbLocal/localData.max_load_factor()));

  // Information exchanged among domains (attention to their order), number in parentheses presents size of data
  // lon(1) + lat(1) + bounds_lon(nVertex) + bounds_lat(nVertex) + mask(1) + data_i_index(1)
  int dataPackageSize =  1 + 1 + // lon + lat
                         nVertex + nVertex + //bounds_lon + bounds_lat
                         1 + // mask_1d_dst;
                         1 + 1; // data_i_index + data_j_index
  // Initialize database
  for (int idx = 0; idx < oldNbLocal; ++idx)
  {
    index = i_index_src(idx) + j_index_src(idx) * niGloSrc;
    localData[index].resize(dataPackageSize);
    std::vector<double>& data = localData[index];

    //Pack data
    int dataIdx = 0;
    data[dataIdx] = lon_src(idx);++dataIdx;
    data[dataIdx] = lat_src(idx);++dataIdx;
    for (int i = 0; i < nVertex; ++i)
    {
      data[dataIdx] = bounds_lon_src(i,idx); ++dataIdx;
    }
    for (int i = 0; i < nVertex; ++i)
    {
      data[dataIdx] = bounds_lat_src(i,idx); ++dataIdx;
    }
    data[dataIdx] = mask_1d_src(idx) ? 1.0 : -1.0; ++dataIdx;
    data[dataIdx] = data_i_index_src_full(idx);++dataIdx;
    data[dataIdx] = data_j_index_src_full(idx);
  }

  CClientClientDHTDouble dhtData(localData,client->intraComm);
  dhtData.computeIndexInfoMapping(globalIndexSrcOnDstDomain);
  CClientClientDHTDouble::Index2VectorInfoTypeMap& neighborData = dhtData.getInfoIndexMap();
  CClientClientDHTDouble::Index2VectorInfoTypeMap::iterator ite = neighborData.end(), it;

  // Ok get all data for destination
  // If domain is not periodic, then we mask all extended part.
  int nbUnMaskedPointOnExtendedPart = 0, remainder = 0, dataIIndex, dataJIndex;
  size_t nIdx;
  double maskValue = 1.0;
  for (index = 0; index < newNbLocalDst; ++index)
  {
     nIdx = globalIndexSrcOnDstDomain(index);
     it = neighborData.find(nIdx);
     if (ite != it)
     {
        std::vector<double>& data = it->second;
        // Unpack data
        int dataIdx = 0;
        lon_dst(index) = data[dataIdx]; ++dataIdx;
        lat_dst(index) = data[dataIdx]; ++dataIdx;
        for (int i = 0; i < nVertex; ++i)
        {
          bounds_lon_dst(i,index) = data[dataIdx]; ++dataIdx;
        }
        for (int i = 0; i < nVertex; ++i)
        {
          bounds_lat_dst(i,index) = data[dataIdx]; ++dataIdx;
        }
        
        // Check whether we have x periodic. If we don't, we should mask all point at 0 and niGloDst-1
        maskValue = data[dataIdx];
        if (!isXPeriodic_) 
        {
          remainder = i_index_dst(index) % (niGloDst-1);
          if (0 == remainder) 
          {
            maskValue = -1.0;
          }
        }

        if (!isYPeriodic_) 
        {
          remainder = j_index_dst(index) % (njGloDst-1);
          if (0 == remainder) 
          {
            maskValue = -1.0;
          }
        }

        mask_1d_dst(index) = (1.0 == maskValue) ? true : false; ++dataIdx;

        dataIIndex = (int) data[dataIdx];
        if (!isXPeriodic_) 
        {
          remainder = i_index_dst(index) % (niGloDst-1);
          if (0 == remainder) 
          {
            dataIIndex = -1;
          }
        }
        data_i_index_dst_full(index) = dataIIndex; ++dataIdx;
        
        dataJIndex = (int) data[dataIdx];
        if (!isYPeriodic_) 
        {
          remainder = j_index_dst(index) % (njGloDst-1);
          if (0 == remainder) 
          {
            dataJIndex = -1;
          }
        }        
        data_j_index_dst_full(index) = dataJIndex;

        if ((0 <= data_i_index_dst_full(index)) && (0 <= data_j_index_dst_full(index)))
        {
          ++nbUnMaskedPointOnExtendedPart;
        }
     }
  }

  
  // Finally, update data_i_index, data_j_index
  int dataDstDim = domainDestination->data_dim;
  data_i_index_dst.resize(nbUnMaskedPointOnExtendedPart);
  data_j_index_dst.resize(nbUnMaskedPointOnExtendedPart); 
  int count = 0; 
  for (idx = 0; idx < newNbLocalDst; ++idx)
  {
    dataIIndex = data_i_index_dst_full(idx);
    dataJIndex = data_j_index_dst_full(idx);
    if ((0 <= dataIIndex) && (0 <= dataJIndex))
    {
      data_i_index_dst(count) = (1 == dataDstDim) ? idx : i_index_dst(idx) - i_index_dst(0);
      data_j_index_dst(count) = (1 == dataDstDim) ? 0   : j_index_dst(idx) - j_index_dst(0);
      ++count;
    }
  }

  // Update data_ni, data_nj
  
  domainDestination->data_ni.setValue((1==dataDstDim) ? niDst * njDst : niDst);
  domainDestination->data_nj.setValue((1==dataDstDim) ? niDst * njDst : njDst);  
  domainDestination->data_ibegin.setValue(0);
  domainDestination->data_jbegin.setValue(0);

  // Update longitude and latitude 
  if (niSrc == domainSource->lonvalue_1d.numElements() && njSrc == domainSource->latvalue_1d.numElements()) // Ok, we have rectilinear here
  {
     domainDestination->lonvalue_1d.resize(niDst);
     domainDestination->lonvalue_1d = lon_dst(Range(0,niDst-1));
     domainDestination->latvalue_1d.resize(njDst);
     domainDestination->latvalue_1d = lat_dst(Range(0,lat_dst.numElements()-niDst,niDst));
  }
  else // It should be curvilinear
  {
     domainDestination->lonvalue_1d.resize(lon_dst.numElements());
     domainDestination->lonvalue_1d = lon_dst;
     domainDestination->latvalue_1d.resize(lat_dst.numElements());
     domainDestination->latvalue_1d = (lat_dst);
  }
   domainDestination->mask_1d.resize(domainDestination->domainMask.numElements()) ;
   domainDestination->mask_1d=domainDestination->domainMask ;
   domainDestination->computeLocalMask() ;
}
CATCH

/*!
 *  Extend domain destination and update its attributes
 *  Suppose that domain destination and domain source have the same values for all attributes (by inheritance)
 *  \param [in/out] domainDestination domain destination
 *  \param [in] domainSource domain source
 *  \param [in] neighborsDomainSrc domain extended part
 */
void CDomainAlgorithmExpand::updateUnstructuredDomainAttributes(CDomain* domainDestination,
                                                                CDomain* domainSource,
                                                                CArray<int,2>& neighborsDomainSrc)
TRY
{

  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;

  // First of all, "copy" all attributes of domain source to domain destination
  StdString domainDstRef = (!domainDestination->domain_ref.isEmpty()) ? domainDestination->domain_ref.getValue()
                                                                      : "";
  if (domainDstRef != domainSource->getId())
  {
    domainDestination->domain_ref.setValue(domainSource->getId());
    domainDestination->solveRefInheritance(true);
  }

  if (domainDstRef.empty()) domainDestination->domain_ref.reset();
  else domainDestination->domain_ref.setValue(domainDstRef);

  // Now extend domain destination
  int niGlob = domainSource->ni_glo;
  CArray<bool,1>& mask_1d_src = domainSource->domainMask;
  CArray<int,1>& i_index_src = domainSource->i_index;
  CArray<double,1>& lon_src = domainSource->lonvalue_1d;
  CArray<double,1>& lat_src = domainSource->latvalue_1d;
  CArray<double,2>& bounds_lon_src = domainSource->bounds_lon_1d;
  CArray<double,2>& bounds_lat_src = domainSource->bounds_lat_1d;
  CArray<int,1>& data_i_index_src = domainSource->data_i_index;

  int oldNbLocal = i_index_src.numElements(), index, globalIndex;
  // Uncompress data_i_index
  CArray<int,1> data_i_index_src_full(oldNbLocal);
  int nbUnMaskedPointOnLocalDomain = 0;
  data_i_index_src_full = -1; // Suppose all values are masked
  for (int idx = 0; idx < data_i_index_src.numElements(); ++idx)
  {
    int dataIdx = data_i_index_src(idx);
    if ((0 <= dataIdx) && (dataIdx < oldNbLocal))
    {
      data_i_index_src_full(nbUnMaskedPointOnLocalDomain) = dataIdx;
      ++nbUnMaskedPointOnLocalDomain;
    }
  }

  CArray<bool,1>& mask_1d_dst = domainDestination->domainMask;
  CArray<int,1>& i_index_dst = domainDestination->i_index;
  CArray<int,1>& j_index_dst = domainDestination->j_index;
  CArray<double,1>& lon_dst = domainDestination->lonvalue_1d;
  CArray<double,1>& lat_dst = domainDestination->latvalue_1d;
  CArray<double,2>& bounds_lon_dst = domainDestination->bounds_lon_1d;
  CArray<double,2>& bounds_lat_dst = domainDestination->bounds_lat_1d;
  CArray<int,1>& data_i_index_dst = domainDestination->data_i_index;
  CArray<int,1>& data_j_index_dst = domainDestination->data_j_index;

  // Resize all array-like attributes of domain destination
  int nbNeighbor    = neighborsDomainSrc.shape()[1];
  int newNbLocalDst = nbNeighbor + oldNbLocal;
  int nVertex       = bounds_lon_dst.shape()[0];

  mask_1d_dst.resizeAndPreserve(newNbLocalDst);
  i_index_dst.resizeAndPreserve(newNbLocalDst);
  j_index_dst.resizeAndPreserve(newNbLocalDst);
  lon_dst.resizeAndPreserve(newNbLocalDst);
  lat_dst.resizeAndPreserve(newNbLocalDst);
  bounds_lon_dst.resizeAndPreserve(nVertex, newNbLocalDst);
  bounds_lat_dst.resizeAndPreserve(nVertex, newNbLocalDst);
  CArray<int,1> data_i_index_dst_full(newNbLocalDst);
  data_i_index_dst_full(Range(0,oldNbLocal-1)) = data_i_index_src_full;
  data_i_index_dst_full(Range(oldNbLocal,newNbLocalDst-1)) = -1;

  // 1. Fill in array relating to global index (i_index, j_index, transmap, etc, ...)
  // Global index mapping between destination and source
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);
  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  transMap.rehash(std::ceil(newNbLocalDst/transMap.max_load_factor()));
  transWeight.rehash(std::ceil(newNbLocalDst/transWeight.max_load_factor()));
  // First, index mapping for local domain
  for (int idx = 0; idx < oldNbLocal; ++idx)
  {
    index = i_index_dst(idx);
    transMap[index].push_back(index);
    transWeight[index].push_back(1.0);
  }
  // Then, index mapping for extended part
  for (int idx = 0; idx < nbNeighbor; ++idx)
  {
    index = idx + oldNbLocal;
    globalIndex = neighborsDomainSrc(0,idx);
    i_index_dst(index) = globalIndex;
    j_index_dst(index) = 0;
    transMap[globalIndex].push_back(globalIndex);
    transWeight[globalIndex].push_back(1.0);
  }

  // 2. Exchange local info among domains (lon,lat,bounds,mask,etc,...)
  CClientClientDHTDouble::Index2VectorInfoTypeMap localData;
  localData.rehash(std::ceil(oldNbLocal/localData.max_load_factor()));
  // Information exchanged among domains (attention to their order), number in parentheses presents size of data
  // lon(1) + lat(1) + bounds_lon(nVertex) + bounds_lat(nVertex) + mask(1) + data_i_index(1)
  int dataPackageSize =  1 + 1 + // lon + lat
                         nVertex + nVertex + //bounds_lon + bounds_lat
                         1 + // mask_1d_dst;
                         1; // data_i_index
  // Initialize database
  for (int idx = 0; idx < oldNbLocal; ++idx)
  {
    index = i_index_src(idx);
    localData[index].resize(dataPackageSize);
    std::vector<double>& data = localData[index];

    //Pack data
    int dataIdx = 0;
    data[dataIdx] = lon_src(idx);++dataIdx;
    data[dataIdx] = lat_src(idx);++dataIdx;
    for (int i = 0; i < nVertex; ++i)
    {
      data[dataIdx] = bounds_lon_src(i,idx); ++dataIdx;
    }
    for (int i = 0; i < nVertex; ++i)
    {
      data[dataIdx] = bounds_lat_src(i,idx); ++dataIdx;
    }
    data[dataIdx] = mask_1d_src(idx) ? 1.0 : -1.0; ++dataIdx;
    data[dataIdx] = data_i_index_src_full(idx);
  }

  CClientClientDHTDouble dhtData(localData,client->intraComm);
  CArray<size_t,1> neighborInd(nbNeighbor);
  for (int idx = 0; idx < nbNeighbor; ++idx)
    neighborInd(idx) = neighborsDomainSrc(0,idx);

  // Compute local data on other domains
  dhtData.computeIndexInfoMapping(neighborInd);
  CClientClientDHTDouble::Index2VectorInfoTypeMap& neighborData = dhtData.getInfoIndexMap();
  CClientClientDHTDouble::Index2VectorInfoTypeMap::iterator ite = neighborData.end(), it;
  // Ok get neighbor data
  size_t nIdx;
  int nbUnMaskedPointOnExtendedPart = 0;
  for (int idx = 0; idx < nbNeighbor; ++idx)
  {
    nIdx  = neighborInd(idx);
    it = neighborData.find(nIdx);
    if (ite != it)
    {
      index = idx + oldNbLocal;
      std::vector<double>& data = it->second;
      // Unpack data
      int dataIdx = 0;
      lon_dst(index) = data[dataIdx]; ++dataIdx;
      lat_dst(index) = data[dataIdx]; ++dataIdx;
      for (int i = 0; i < nVertex; ++i)
      {
        bounds_lon_dst(i,index) = data[dataIdx]; ++dataIdx;
      }
      for (int i = 0; i < nVertex; ++i)
      {
        bounds_lat_dst(i,index) = data[dataIdx]; ++dataIdx;
      }
      mask_1d_dst(index) = (1.0 == data[dataIdx]) ? true : false; ++dataIdx;
      data_i_index_dst_full(index) = (int)(data[dataIdx]);
      if (0 <= data_i_index_dst_full(index))
      {
        data_i_index_dst_full(index) = index;
        ++nbUnMaskedPointOnExtendedPart;
      }
    }
  }


  // Finally, update data_i_index
  int nbUnMaskedPointOnNewDstDomain = (nbUnMaskedPointOnExtendedPart + nbUnMaskedPointOnLocalDomain);
  int count = 0, dataIdx;
  for (int idx = 0; idx < newNbLocalDst; ++idx)
  {
    dataIdx = data_i_index_dst_full(idx);
    if ((0 <= dataIdx))
    {
      ++count;
    }
  }

  data_i_index_dst.resize(count);
  data_j_index_dst.resize(count);
  data_j_index_dst = 0;

  count = 0;
  for (int idx = 0; idx < newNbLocalDst; ++idx)
  {
    dataIdx = data_i_index_dst_full(idx);
    if ((0 <= dataIdx))
    {
      data_i_index_dst(count) = dataIdx;
      ++count;
    }
  }

  // Update ni
  domainDestination->ni.setValue(newNbLocalDst);
  domainDestination->mask_1d.resize(domainDestination->domainMask.numElements()) ;
  domainDestination->mask_1d=domainDestination->domainMask ;
  domainDestination->computeLocalMask() ;
}
CATCH

/*!
  Compute the index mapping between domain on grid source and one on grid destination
*/
void CDomainAlgorithmExpand::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{

}

}
