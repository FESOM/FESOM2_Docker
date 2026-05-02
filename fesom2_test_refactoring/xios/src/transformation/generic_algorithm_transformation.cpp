/*!
   \file generic_algorithm_transformation.hpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 21 Mars 2016

   \brief Interface for all transformation algorithms.
 */
#include "generic_algorithm_transformation.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "client_client_dht_template.hpp"
#include "utils.hpp"
#include "timer.hpp"
#include "mpi.hpp"

namespace xios {

CGenericAlgorithmTransformation::CGenericAlgorithmTransformation()
 : transformationMapping_(), transformationWeight_(), transformationPosition_(),
   idAuxInputs_(), type_(ELEMENT_NO_MODIFICATION_WITH_DATA), indexElementSrc_(),
   computedProcSrcNonTransformedElement_(false), eliminateRedondantSrc_(true), isDistributedComputed_(false)
{
}

void CGenericAlgorithmTransformation::updateData(CArray<double,1>& dataOut)
{

}

void CGenericAlgorithmTransformation::apply(const std::vector<std::pair<int,double> >& localIndex,
                                            const double* dataInput,
                                            CArray<double,1>& dataOut,
                                            std::vector<bool>& flagInitial,
                                            bool ignoreMissingValue, bool firstPass  )
TRY
{
  int nbLocalIndex = localIndex.size();   
  double defaultValue = std::numeric_limits<double>::quiet_NaN();
    
  if (ignoreMissingValue)
  {
    if (firstPass) dataOut=defaultValue ;
    
    for (int idx = 0; idx < nbLocalIndex; ++idx)
    {
      if (! NumTraits<double>::isNan(*(dataInput + idx)))
      {
        if (flagInitial[localIndex[idx].first]) dataOut(localIndex[idx].first) = *(dataInput + idx) * localIndex[idx].second;
        else dataOut(localIndex[idx].first) += *(dataInput + idx) * localIndex[idx].second;
        flagInitial[localIndex[idx].first] = false; // Reset flag to indicate not all data source are nan
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

void CGenericAlgorithmTransformation::computePositionElements(CGrid* dst, CGrid* src)
TRY
{
  int idxScalar = 0, idxAxis = 0, idxDomain = 0;
  CArray<int,1> axisDomainOrderDst = dst->axis_domain_order;
  for (int i = 0; i < axisDomainOrderDst.numElements(); ++i)
  {
    int dimElement = axisDomainOrderDst(i);
    if (2 == dimElement)
    {
      elementPositionInGridDst2DomainPosition_[i] = idxDomain;
      ++idxDomain;
    }
    else if (1 == dimElement)
    {
      elementPositionInGridDst2AxisPosition_[i] = idxAxis;
      ++idxAxis;
    }
    else
    {
      elementPositionInGridDst2ScalarPosition_[i] = idxScalar;
      ++idxScalar;
    }
  }

  idxScalar = idxAxis = idxDomain = 0;
  CArray<int,1> axisDomainOrderSrc = src->axis_domain_order;
  for (int i = 0; i < axisDomainOrderSrc.numElements(); ++i)
  {
    int dimElement = axisDomainOrderSrc(i);
    if (2 == dimElement)
    {
      elementPositionInGridSrc2DomainPosition_[i] = idxDomain;
      ++idxDomain;
    }
    else if (1 == dimElement)
    {
      elementPositionInGridSrc2AxisPosition_[i] = idxAxis;
      ++idxAxis;
    }
    else
    {
      elementPositionInGridSrc2ScalarPosition_[i] = idxScalar;
      ++idxScalar;
    }
  }
}
CATCH

bool CGenericAlgorithmTransformation::isDistributedTransformation(int elementPositionInGrid, CGrid* gridSrc, CGrid* gridDst)
TRY
{

  if (!isDistributedComputed_)
  {
    isDistributedComputed_=true ;
    if (!eliminateRedondantSrc_) isDistributed_=true ;
    else
    {
      CContext* context = CContext::getCurrent();
      CContextClient* client = context->client;
  
      computePositionElements(gridSrc, gridDst);
      std::vector<CScalar*> scalarListSrcP  = gridSrc->getScalars();
      std::vector<CAxis*> axisListSrcP = gridSrc->getAxis();
      std::vector<CDomain*> domainListSrcP = gridSrc->getDomains();
      int distributed, distributed_glo ;
  
      CArray<int,1> axisDomainSrcOrder = gridSrc->axis_domain_order;
      if (2 == axisDomainSrcOrder(elementPositionInGrid)) // It's domain
      {
        distributed=domainListSrcP[elementPositionInGridSrc2DomainPosition_[elementPositionInGrid]]->isDistributed() ;
        MPI_Allreduce(&distributed,&distributed_glo, 1, MPI_INT, MPI_LOR, client->intraComm) ;
    
      }
      else if (1 == axisDomainSrcOrder(elementPositionInGrid))//it's an axis
      {
        distributed=axisListSrcP[elementPositionInGridSrc2AxisPosition_[elementPositionInGrid]]->isDistributed() ;
        MPI_Allreduce(&distributed,&distributed_glo, 1, MPI_INT, MPI_LOR, client->intraComm) ;
      }
      else //it's a scalar
      {
        distributed_glo=false ;
      } 
      isDistributed_=distributed_glo ;
    }
  }
  return isDistributed_ ;
}
CATCH

/*!
  This function computes the global indexes of grid source, which the grid destination is in demand.
  \param[in] elementPositionInGrid position of an element in a grid .E.g: if grid is composed of domain and axis (in order),
                then position of axis in grid is 1 and domain is positioned at 0.
  \param[in] gridSrc Grid source
  \param[in] gridDst Grid destination
  \param[in\out] globaIndexWeightFromSrcToDst mapping of each global index source and weight to index destination
*/
void CGenericAlgorithmTransformation::computeGlobalSourceIndex(int elementPositionInGrid,
                                                               CGrid* gridSrc,
                                                               CGrid* gridDst,
                                                               SourceDestinationIndexMap& globaIndexWeightFromSrcToDst)
TRY
 {
  CContext* context = CContext::getCurrent();
  CContextClient* client = context->client;
  int nbClient = client->clientSize;

  typedef std::unordered_map<int, std::vector<std::pair<int,double> > > SrcToDstMap;
  int idx;

  // compute position of elements on grids
  computePositionElements(gridDst, gridSrc);
  std::vector<CScalar*> scalarListDestP = gridDst->getScalars();
  std::vector<CAxis*> axisListDestP = gridDst->getAxis();
  std::vector<CDomain*> domainListDestP = gridDst->getDomains();
  CArray<int,1> axisDomainDstOrder = gridDst->axis_domain_order;
  std::vector<CScalar*> scalarListSrcP  = gridSrc->getScalars();
  std::vector<CAxis*> axisListSrcP = gridSrc->getAxis();
  std::vector<CDomain*> domainListSrcP = gridSrc->getDomains();
  CArray<int,1> axisDomainSrcOrder = gridSrc->axis_domain_order;  
  
  bool isTransPosEmpty = transformationPosition_.empty();
  CArray<size_t,1> transPos;
  if (!isTransPosEmpty) transPos.resize(transformationMapping_.size());
  std::set<size_t> allIndexSrc; // All index of source, which can be scattered among processes, need for doing transformation 
  
  for (size_t idxTrans = 0; idxTrans < transformationMapping_.size(); ++idxTrans)
  {
    TransformationIndexMap::const_iterator itbTransMap = transformationMapping_[idxTrans].begin(), itTransMap,
                                           iteTransMap = transformationMapping_[idxTrans].end();
    TransformationWeightMap::const_iterator itbTransWeight = transformationWeight_[idxTrans].begin(), itTransWeight;

    // Build mapping between global source element index and global destination element index.
    itTransWeight = itbTransWeight;
    for (itTransMap = itbTransMap; itTransMap != iteTransMap; ++itTransMap, ++itTransWeight)
    {
      const std::vector<int>& srcIndex = itTransMap->second;
      for (idx = 0; idx < srcIndex.size(); ++idx)
        allIndexSrc.insert(srcIndex[idx]);
    }

    if (!isTransPosEmpty)
    {
      TransformationPositionMap::const_iterator itPosMap = transformationPosition_[idxTrans].begin();
      transPos(idxTrans) = itPosMap->second[0];
    }
  }

  size_t indexSrcSize = 0;
  CArray<size_t,1> indexSrc(allIndexSrc.size());
  for (std::set<size_t>::iterator it = allIndexSrc.begin(); it != allIndexSrc.end(); ++it, ++indexSrcSize)
    indexSrc(indexSrcSize) = *it;

  // Flag to indicate whether we will recompute distribution of source global index  on processes
  bool computeGlobalIndexOnProc = false; 
  if (indexElementSrc_.size() != allIndexSrc.size())
    computeGlobalIndexOnProc = true;  
  else
  {
    for (std::set<size_t>::iterator it = allIndexSrc.begin(); it != allIndexSrc.end(); ++it)
      if (0 == indexElementSrc_.count(*it))
      {
        computeGlobalIndexOnProc = true;
        break;        
      }
  }

  if (computeGlobalIndexOnProc)
    indexElementSrc_.swap(allIndexSrc);
      
  int sendValue = (computeGlobalIndexOnProc) ? 1 : 0;
  int recvValue = 0;
  MPI_Allreduce(&sendValue, &recvValue, 1, MPI_INT, MPI_SUM, client->intraComm);
  computeGlobalIndexOnProc = (0 < recvValue);

//  CClientClientDHTInt::Index2VectorInfoTypeMap globalIndexOfTransformedElementOnProc;

  if (computeGlobalIndexOnProc || !computedProcSrcNonTransformedElement_)
  {    
    {
      CClientClientDHTInt::Index2VectorInfoTypeMap tmp ;
      globalIndexOfTransformedElementOnProc_.swap(tmp) ;
    }
    // Find out global index source of transformed element on corresponding process.    
    if (globalElementIndexOnProc_.empty())
      globalElementIndexOnProc_.resize(axisDomainDstOrder.numElements());
    
    for (idx = 0; idx < axisDomainDstOrder.numElements(); ++idx)
    {
      
      if (idx == elementPositionInGrid)
        computeExchangeGlobalIndex(indexSrc, axisDomainSrcOrder(idx), globalIndexOfTransformedElementOnProc_); //globalElementIndexOnProc[idx]);
      if (!computedProcSrcNonTransformedElement_)
      {
        if (2 == axisDomainDstOrder(idx)) // It's domain
        {
          if (idx != elementPositionInGrid)
            computeExchangeDomainIndex(domainListDestP[elementPositionInGridDst2DomainPosition_[idx]],
                                       domainListSrcP[elementPositionInGridSrc2DomainPosition_[idx]],
                                       transPos,
                                       globalElementIndexOnProc_[idx]);      

        }
        else if (1 == axisDomainDstOrder(idx))//it's an axis
        {
          if (idx != elementPositionInGrid)
            computeExchangeAxisIndex(axisListDestP[elementPositionInGridDst2AxisPosition_[idx]],
                                     axisListSrcP[elementPositionInGridSrc2AxisPosition_[idx]],
                                     transPos,
                                     globalElementIndexOnProc_[idx]);
        }
        else //it's a scalar
        {
          if (idx != elementPositionInGrid)
            computeExchangeScalarIndex(scalarListDestP[elementPositionInGridDst2ScalarPosition_[idx]],
                                       scalarListSrcP[elementPositionInGridSrc2ScalarPosition_[idx]],
                                       transPos,
                                       globalElementIndexOnProc_[idx]);

        }
      }
    }

    if (!isTransPosEmpty && !computedProcSrcNonTransformedElement_)
    {
      for (idx = 0; idx < globalElementIndexOnProc_.size(); ++idx)
      {
        if (idx != elementPositionInGrid)
        {
          std::unordered_map<int,std::vector<size_t> >::iterator itb = globalElementIndexOnProc_[idx].begin(), it,
                                                                   ite = globalElementIndexOnProc_[idx].end();
          for (it = itb; it != ite; ++it) it->second.resize(1);
        }
      }
    }

/*      
    if (!computedProcSrcNonTransformedElement_)
    {
      for (idx = 0; idx < globalElementIndexOnProc_.size(); ++idx)
      {
        if (idx != elementPositionInGrid)
        {
          std::unordered_map<int,std::vector<size_t> >::iterator itb = globalElementIndexOnProc_[idx].begin(), it,
                                                                   ite = globalElementIndexOnProc_[idx].end();
          for (it = itb; it != ite; ++it) procOfNonTransformedElements_.insert(it->first);
          if (procOfNonTransformedElements_.size() == nbClient)
            break;
        }
      }
    }
   
    // Processes contain the source index of transformed element
    std::set<int> procOfTransformedElement; 
    CClientClientDHTInt::Index2VectorInfoTypeMap::iterator itIdxb = globalIndexOfTransformedElementOnProc.begin(),
                                                           itIdxe = globalIndexOfTransformedElementOnProc.end(), itIdx;
    for (itIdx = itIdxb; itIdx != itIdxe; ++itIdx)
    {
      std::vector<int>& tmp = itIdx->second;
      for (int i = 0; i < tmp.size(); ++i)
        procOfTransformedElement.insert(tmp[i]);
      if (tmp.size() == nbClient)
        break;
    }                                                           
    
    std::set<int>& commonProc = (procOfTransformedElement.size() < procOfNonTransformedElements_.size()) ? procOfTransformedElement 
                              : (!procOfNonTransformedElements_.empty() ? procOfNonTransformedElements_ : procOfTransformedElement);
    
    std::vector<int> procContainSrcElementIdx(commonProc.size());
    int count = 0;
    for (std::set<int>::iterator it = commonProc.begin(); it != commonProc.end(); ++it)
      procContainSrcElementIdx[count++] = *it;

    procContainSrcElementIdx_.swap(procContainSrcElementIdx);    
*/
    
    if (procElementList_.empty()) procElementList_.resize(axisDomainDstOrder.numElements()) ;
    for (idx = 0; idx < axisDomainDstOrder.numElements(); ++idx)
    {
      std::set<int>& procList=procElementList_[idx] ;
      std::set<int> commonTmp ;
      if (idx == elementPositionInGrid)
      {
          set<int> tmpSet ; 
          procList.swap(tmpSet) ;
          CClientClientDHTInt::Index2VectorInfoTypeMap::iterator itIdxb = globalIndexOfTransformedElementOnProc_.begin(),
                                                                 itIdxe = globalIndexOfTransformedElementOnProc_.end(), itIdx;
          for (itIdx = itIdxb; itIdx != itIdxe; ++itIdx)
          {
             std::vector<int>& tmp = itIdx->second;
             for (int i = 0; i < tmp.size(); ++i) procList.insert(tmp[i]);
             if (tmp.size() == nbClient)
             break;
          }
      }
      else
      {
        if (!computedProcSrcNonTransformedElement_)
        {
          set<int> tmpSet ; 
          procList.swap(tmpSet) ;
          std::unordered_map<int,std::vector<size_t> >::iterator itb = globalElementIndexOnProc_[idx].begin(), it,
                                                                   ite = globalElementIndexOnProc_[idx].end();
          for (it = itb; it != ite; ++it)
          {
            procList.insert(it->first);
            if (procList.size() == nbClient)  break;
          }
        }
      }

      if (idx==0) commonProc_= procList ;
      else
      {
        for (std::set<int>::iterator it = commonProc_.begin(); it != commonProc_.end(); ++it)
          if (procList.count(*it)==1) commonTmp.insert(*it) ;
        commonProc_.swap(commonTmp) ;
      }
    }
    std::vector<int> procContainSrcElementIdx(commonProc_.size());
    int count = 0;
    for (std::set<int>::iterator it = commonProc_.begin(); it != commonProc_.end(); ++it) procContainSrcElementIdx[count++] = *it;
    procContainSrcElementIdx_.swap(procContainSrcElementIdx);
    
        // For the first time, surely we calculate proc containing non transformed elements
    if (!computedProcSrcNonTransformedElement_) computedProcSrcNonTransformedElement_ = true;
  }
  
  for (size_t idxTrans = 0; idxTrans < transformationMapping_.size(); ++idxTrans)
  {
    TransformationIndexMap::const_iterator itbTransMap = transformationMapping_[idxTrans].begin(), itTransMap,
                                           iteTransMap = transformationMapping_[idxTrans].end();
    TransformationWeightMap::const_iterator itbTransWeight = transformationWeight_[idxTrans].begin(), itTransWeight;
    SrcToDstMap src2DstMap;
    src2DstMap.rehash(std::ceil(transformationMapping_[idxTrans].size()/src2DstMap.max_load_factor()));

    // Build mapping between global source element index and global destination element index.
    std::unordered_map<int,std::vector<size_t> >().swap(globalElementIndexOnProc_[elementPositionInGrid]);
    std::set<int> tmpCounter;
    itTransWeight = itbTransWeight;
    for (itTransMap = itbTransMap; itTransMap != iteTransMap; ++itTransMap, ++itTransWeight)
    {
      const std::vector<int>& srcIndex = itTransMap->second;
      const std::vector<double>& weight = itTransWeight->second;
      for (idx = 0; idx < srcIndex.size(); ++idx)
      {
        src2DstMap[srcIndex[idx]].push_back(make_pair(itTransMap->first, weight[idx]));
        if (0 == tmpCounter.count(srcIndex[idx]))
        {          
          tmpCounter.insert(srcIndex[idx]);
       
          vector<int>& rankSrc = globalIndexOfTransformedElementOnProc_[srcIndex[idx]] ;
          for (int n=0;n<rankSrc.size();++n)
          {
            if (commonProc_.count(rankSrc[n])==1) globalElementIndexOnProc_[elementPositionInGrid][rankSrc[n]].push_back(srcIndex[idx]);
          }
//          for (int j = 0; j < procContainSrcElementIdx_.size(); ++j)
//            globalElementIndexOnProc_[elementPositionInGrid][procContainSrcElementIdx_[j]].push_back(srcIndex[idx]);
        }
      }
    }
  
    if (!isTransPosEmpty)
    {
      for (idx = 0; idx < globalElementIndexOnProc_.size(); ++idx)
      {
        if (idx != elementPositionInGrid)
        {
          std::unordered_map<int,std::vector<size_t> >::iterator itb = globalElementIndexOnProc_[idx].begin(), it,
                                                                   ite = globalElementIndexOnProc_[idx].end();
          for (it = itb; it != ite; ++it) it->second[0] = transPos(idxTrans);
        }
      }
    }

    // Ok, now compute global index of grid source and ones of grid destination
    computeGlobalGridIndexMapping(elementPositionInGrid,
                                  procContainSrcElementIdx_, //srcRank,
                                  src2DstMap,
                                  gridSrc,
                                  gridDst,
                                  globalElementIndexOnProc_,
                                  globaIndexWeightFromSrcToDst);
  }  
 }
CATCH

/*!
  Compute mapping of global index of grid source and grid destination
  \param [in] elementPositionInGrid position of element in grid. E.x: grid composed of domain and axis, domain has position 0 and axis 1.
  \param [in] srcRank rank of client from which we demand global index of element source
  \param [in] src2DstMap mapping of global index of element source and global index of element destination
  \param [in] gridSrc Grid source
  \param [in] gridDst Grid destination
  \param [in] globalElementIndexOnProc Global index of element source on different client rank
  \param [out] globaIndexWeightFromSrcToDst Mapping of global index of grid source and grid destination
*/
void CGenericAlgorithmTransformation::computeGlobalGridIndexMapping(int elementPositionInGrid,
                                                                   const std::vector<int>& srcRank,
                                                                   std::unordered_map<int, std::vector<std::pair<int,double> > >& src2DstMap,
                                                                   CGrid* gridSrc,
                                                                   CGrid* gridDst,
                                                                   std::vector<std::unordered_map<int,std::vector<size_t> > >& globalElementIndexOnProc,
                                                                   SourceDestinationIndexMap& globaIndexWeightFromSrcToDst)
TRY
{
  SourceDestinationIndexMap globaIndexWeightFromSrcToDst_tmp ;
  
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  
  std::vector<CDomain*> domainListSrcP = gridSrc->getDomains();
  std::vector<CAxis*> axisListSrcP = gridSrc->getAxis();
  std::vector<CScalar*> scalarListSrcP = gridSrc->getScalars();
  CArray<int,1> axisDomainSrcOrder = gridSrc->axis_domain_order;

  size_t nbElement = axisDomainSrcOrder.numElements();
  std::vector<size_t> nGlobSrc(nbElement);
  size_t globalSrcSize = 1;
  int domainIndex = 0, axisIndex = 0, scalarIndex = 0;
  for (int idx = 0; idx < nbElement; ++idx)
  {
    nGlobSrc[idx] = globalSrcSize;
    int elementDimension = axisDomainSrcOrder(idx);

    // If this is a domain
    if (2 == elementDimension)
    {
      globalSrcSize *= domainListSrcP[domainIndex]->nj_glo.getValue() * domainListSrcP[domainIndex]->ni_glo.getValue();
      ++domainIndex;
    }
    else if (1 == elementDimension) // So it's an axis
    {
      globalSrcSize *= axisListSrcP[axisIndex]->n_glo.getValue();
      ++axisIndex;
    }
    else
    {
      globalSrcSize *= 1;
      ++scalarIndex;
    }
  }

  std::vector<CDomain*> domainListDestP = gridDst->getDomains();
  std::vector<CAxis*> axisListDestP = gridDst->getAxis();
  std::vector<CScalar*> scalarListDestP = gridDst->getScalars();
  CArray<int,1> axisDomainDstOrder = gridDst->axis_domain_order;

  std::vector<size_t> nGlobDst(nbElement);
  size_t globalDstSize = 1;
  domainIndex = axisIndex = scalarIndex = 0;
  set<size_t>  globalSrcStoreIndex ;
  
  for (int idx = 0; idx < nbElement; ++idx)
  {
    nGlobDst[idx] = globalDstSize;
    int elementDimension = axisDomainDstOrder(idx);

    // If this is a domain
    if (2 == elementDimension)
    {
      globalDstSize *= domainListDestP[domainIndex]->nj_glo.getValue() * domainListDestP[domainIndex]->ni_glo.getValue();
      ++domainIndex;
    }
    else if (1 == elementDimension) // So it's an axis
    {
      globalDstSize *= axisListDestP[axisIndex]->n_glo.getValue();
      ++axisIndex;
    }
    else
    {
      globalDstSize *= 1;
      ++scalarIndex;
    }
  }

  std::map< std::pair<size_t,size_t>, int > rankMap ;
  std::map< std::pair<size_t,size_t>, int >:: iterator rankMapIt ;
  
  for (int i = 0; i < srcRank.size(); ++i)
  {
    size_t ssize = 1;
    int rankSrc = srcRank[i];
    for (int idx = 0; idx < nbElement; ++idx)
    {
      ssize *= (globalElementIndexOnProc[idx][rankSrc]).size();
    }

    std::vector<int> idxLoop(nbElement,0);
    std::vector<int> currentIndexSrc(nbElement, 0);
    std::vector<int> currentIndexDst(nbElement, 0);
    int innnerLoopSize = (globalElementIndexOnProc[0])[rankSrc].size();
    size_t idx = 0;
    while (idx < ssize)
    {
      for (int ind = 0; ind < nbElement; ++ind)
      {
        if (idxLoop[ind] == (globalElementIndexOnProc[ind])[rankSrc].size())
        {
          idxLoop[ind] = 0;
          ++idxLoop[ind+1];
        }

        currentIndexDst[ind] = currentIndexSrc[ind] = (globalElementIndexOnProc[ind])[rankSrc][idxLoop[ind]];
      }

      for (int ind = 0; ind < innnerLoopSize; ++ind)
      {
        currentIndexDst[0] = currentIndexSrc[0] = (globalElementIndexOnProc[0])[rankSrc][ind];
        int globalElementDstIndexSize = 0;
        if (1 == src2DstMap.count(currentIndexSrc[elementPositionInGrid]))
        {
          globalElementDstIndexSize = src2DstMap[currentIndexSrc[elementPositionInGrid]].size();
        }

        std::vector<size_t> globalDstVecIndex(globalElementDstIndexSize,0);
        size_t globalSrcIndex = 0;
        for (int idxElement = 0; idxElement < nbElement; ++idxElement)
        {
          if (idxElement == elementPositionInGrid)
          {
            for (int k = 0; k < globalElementDstIndexSize; ++k)
            {
              globalDstVecIndex[k] += src2DstMap[currentIndexSrc[elementPositionInGrid]][k].first * nGlobDst[idxElement];
            }
          }
          else
          {
            for (int k = 0; k < globalElementDstIndexSize; ++k)
            {
              globalDstVecIndex[k] += currentIndexDst[idxElement] * nGlobDst[idxElement];
            }
          }
          globalSrcIndex += currentIndexSrc[idxElement] * nGlobSrc[idxElement];
        }

        for (int k = 0; k < globalElementDstIndexSize; ++k)
        {
          
          globaIndexWeightFromSrcToDst_tmp[rankSrc][globalSrcIndex].push_back(make_pair(globalDstVecIndex[k],src2DstMap[currentIndexSrc[elementPositionInGrid]][k].second ));
          rankMapIt=rankMap.find(make_pair(globalSrcIndex,globalDstVecIndex[k])) ;
          if (rankMapIt==rankMap.end()) rankMap[make_pair(globalSrcIndex,globalDstVecIndex[k])] = rankSrc ;
          else if (rankSrc==clientRank) rankMapIt->second = rankSrc ;
        }
        ++idxLoop[0];
      }
      idx += innnerLoopSize;
    }
  }

  // eliminate redondant global src point owned by differrent processes.
  // Avoid as possible to tranfer data from an other process if the src point is also owned by current process 
      int rankSrc ;
      size_t globalSrcIndex ;
      size_t globalDstIndex ;
      double weight ;
 
      SourceDestinationIndexMap::iterator rankIt,rankIte ;
      std::unordered_map<size_t, std::vector<std::pair<size_t,double> > >::iterator globalSrcIndexIt, globalSrcIndexIte ;
      std::vector<std::pair<size_t,double> >::iterator vectIt,vectIte ;
   
      rankIt=globaIndexWeightFromSrcToDst_tmp.begin() ; rankIte=globaIndexWeightFromSrcToDst_tmp.end() ;
      for(;rankIt!=rankIte;++rankIt)
      {
        rankSrc = rankIt->first ;
        globalSrcIndexIt = rankIt->second.begin() ; globalSrcIndexIte = rankIt->second.end() ;
        for(;globalSrcIndexIt!=globalSrcIndexIte;++globalSrcIndexIt)
        { 
          globalSrcIndex = globalSrcIndexIt->first ;
          vectIt = globalSrcIndexIt->second.begin() ; vectIte = globalSrcIndexIt->second.end() ;
          for(vectIt; vectIt!=vectIte; vectIt++)
          {
            globalDstIndex = vectIt->first ;
            weight = vectIt->second ;
            if (eliminateRedondantSrc_)
            {
              if (rankMap[make_pair(globalSrcIndex,globalDstIndex)] == rankSrc)  
                globaIndexWeightFromSrcToDst[rankSrc][globalSrcIndex].push_back(make_pair(globalDstIndex,weight)) ;
            }
            else globaIndexWeightFromSrcToDst[rankSrc][globalSrcIndex].push_back(make_pair(globalDstIndex,weight)) ;
         }
       }
     }
}
CATCH

/*!
  Find out proc and global index of axis source which axis destination is on demande
  \param[in] scalar Scalar destination
  \param[in] scalar Scalar source
  \param[in] destGlobalIndexPositionInGrid Relative position of axis corresponds to other element of grid.
  \param[out] globalScalarIndexOnProc Global index of axis source on different procs
*/
void CGenericAlgorithmTransformation::computeExchangeScalarIndex(CScalar* scalarDst,
                                                                 CScalar* scalarSrc,
                                                                 CArray<size_t,1>& destGlobalIndexPositionInGrid,
                                                                 std::unordered_map<int,std::vector<size_t> >& globalScalarIndexOnProc)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int clientSize = client->clientSize;

  globalScalarIndexOnProc.rehash(std::ceil(clientSize/globalScalarIndexOnProc.max_load_factor()));
  for (int idx = 0; idx < clientSize; ++idx)
  {
    globalScalarIndexOnProc[idx].push_back(0);
  }
}
CATCH

/*!
  Find out proc and global index of axis source which axis destination is on demande
  \param[in] axisDst Axis destination
  \param[in] axisSrc Axis source
  \param[in] destGlobalIndexPositionInGrid Relative position of axis corresponds to other element of grid.
  \param[out] globalAxisIndexOnProc Global index of axis source on different procs
*/
void CGenericAlgorithmTransformation::computeExchangeAxisIndex(CAxis* axisDst,
                                                               CAxis* axisSrc,
                                                               CArray<size_t,1>& destGlobalIndexPositionInGrid,
                                                               std::unordered_map<int,std::vector<size_t> >& globalAxisIndexOnProc)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int clientSize = client->clientSize;

  size_t globalIndex;
  int nIndexSize = axisSrc->index.numElements();
  CClientClientDHTInt::Index2VectorInfoTypeMap globalIndex2ProcRank;
  globalIndex2ProcRank.rehash(std::ceil(nIndexSize/globalIndex2ProcRank.max_load_factor()));
  for (int idx = 0; idx < nIndexSize; ++idx)
  {
    if (axisSrc->mask(idx))
    {
      globalIndex = axisSrc->index(idx);
      globalIndex2ProcRank[globalIndex].push_back(clientRank);
    }
  }

  CClientClientDHTInt dhtIndexProcRank(globalIndex2ProcRank, client->intraComm);
  CArray<size_t,1> globalAxisIndex(axisDst->index.numElements());
  for (int idx = 0; idx < globalAxisIndex.numElements(); ++idx)
  {
    globalAxisIndex(idx) = axisDst->index(idx);
  }
  dhtIndexProcRank.computeIndexInfoMapping(globalAxisIndex);

  std::vector<int> countIndex(clientSize,0);
  const CClientClientDHTInt::Index2VectorInfoTypeMap& computedGlobalIndexOnProc = dhtIndexProcRank.getInfoIndexMap();
  CClientClientDHTInt::Index2VectorInfoTypeMap::const_iterator itb = computedGlobalIndexOnProc.begin(), it,
                                                               ite = computedGlobalIndexOnProc.end();
  for (it = itb; it != ite; ++it)
  {
    const std::vector<int>& procList = it->second;
    for (int idx = 0; idx < procList.size(); ++idx) ++countIndex[procList[idx]];
  }

  globalAxisIndexOnProc.rehash(std::ceil(clientSize/globalAxisIndexOnProc.max_load_factor()));
  for (int idx = 0; idx < clientSize; ++idx)
  {
    if (0 != countIndex[idx])
    {
      globalAxisIndexOnProc[idx].resize(countIndex[idx]);
      countIndex[idx] = 0;
    }
  }

  for (it = itb; it != ite; ++it)
  {
    const std::vector<int>& procList = it->second;
    for (int idx = 0; idx < procList.size(); ++idx)
    {
      globalAxisIndexOnProc[procList[idx]][countIndex[procList[idx]]] = it->first;
      ++countIndex[procList[idx]];
    }
  }
}
CATCH

/*!
  Find out proc and global index of domain source which domain destination is on demande
  \param[in] domainDst Domain destination
  \param[in] domainSrc Domain source
  \param[in] destGlobalIndexPositionInGrid Relative position of domain corresponds to other element of grid.
  \param[out] globalDomainIndexOnProc Global index of domain source on different procs
*/
void CGenericAlgorithmTransformation::computeExchangeDomainIndex(CDomain* domainDst,
                                                                 CDomain* domainSrc,
                                                                 CArray<size_t,1>& destGlobalIndexPositionInGrid,
                                                                 std::unordered_map<int,std::vector<size_t> >& globalDomainIndexOnProc)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int clientSize = client->clientSize;

  int niGlobSrc = domainSrc->ni_glo.getValue();
  size_t globalIndex;
  int i_ind, j_ind;
  int nIndexSize = (destGlobalIndexPositionInGrid.isEmpty()) ? domainSrc->i_index.numElements()
                                                             : destGlobalIndexPositionInGrid.numElements();
  CClientClientDHTInt::Index2VectorInfoTypeMap globalIndex2ProcRank;
  globalIndex2ProcRank.rehash(std::ceil(nIndexSize/globalIndex2ProcRank.max_load_factor()));
  
  if (destGlobalIndexPositionInGrid.isEmpty())
  {
    for (int idx = 0; idx < nIndexSize; ++idx)
    {
      i_ind=domainSrc->i_index(idx) ;
      j_ind=domainSrc->j_index(idx) ;

      if (domainSrc->localMask(idx))
      {
        globalIndex = i_ind + j_ind * niGlobSrc;
        globalIndex2ProcRank[globalIndex].resize(1);
        globalIndex2ProcRank[globalIndex][0] = clientRank;
      }
    }
  }
  else
  {
    for (int idx = 0; idx < nIndexSize; ++idx)
    {
//      if (domainSrc->localMask(idx)) -> not necessairy, mask seem to be included in  destGlobalIndexPositionInGrid(idx)    (ym)
        globalIndex2ProcRank[destGlobalIndexPositionInGrid(idx)].push_back(clientRank);
    }
  }

  CArray<size_t,1> globalDomainIndex;
  if (destGlobalIndexPositionInGrid.isEmpty())
  {
    int niGlobDst = domainDst->ni_glo.getValue();
    globalDomainIndex.resize(domainDst->i_index.numElements());
    nIndexSize = domainDst->i_index.numElements();

    for (int idx = 0; idx < nIndexSize; ++idx)
    {
      i_ind=domainDst->i_index(idx) ;
      j_ind=domainDst->j_index(idx) ;

      globalDomainIndex(idx) = i_ind + j_ind * niGlobDst;
    }
  }
  else
  {
    globalDomainIndex.reference(destGlobalIndexPositionInGrid);
  }

  CClientClientDHTInt dhtIndexProcRank(globalIndex2ProcRank, client->intraComm);
  dhtIndexProcRank.computeIndexInfoMapping(globalDomainIndex);

  std::vector<int> countIndex(clientSize,0);
  const CClientClientDHTInt::Index2VectorInfoTypeMap& computedGlobalIndexOnProc = dhtIndexProcRank.getInfoIndexMap();
  CClientClientDHTInt::Index2VectorInfoTypeMap::const_iterator itb = computedGlobalIndexOnProc.begin(), it,
                                                               ite = computedGlobalIndexOnProc.end();
  for (it = itb; it != ite; ++it)
  {
    const std::vector<int>& procList = it->second;
    for (int idx = 0; idx < procList.size(); ++idx) ++countIndex[procList[idx]];
  }

  globalDomainIndexOnProc.rehash(std::ceil(clientSize/globalDomainIndexOnProc.max_load_factor()));
  for (int idx = 0; idx < clientSize; ++idx)
  {
    if (0 != countIndex[idx])
    {
      globalDomainIndexOnProc[idx].resize(countIndex[idx]);
      countIndex[idx] = 0;
    }
  }

  for (it = itb; it != ite; ++it)
  {
    const std::vector<int>& procList = it->second;
    for (int idx = 0; idx < procList.size(); ++idx)
    {
      globalDomainIndexOnProc[procList[idx]][countIndex[procList[idx]]] = it->first;
      ++countIndex[procList[idx]];
    }
  }
}
CATCH

void CGenericAlgorithmTransformation::computeTransformationMappingNonDistributed(int elementPositionInGrid, CGrid* gridSrc, CGrid* gridDst,
                                                                                 vector<int>& localSrc, vector<int>& localDst, vector<double>& weight,
                                                                                 int& nlocalIndexDest)
TRY
{

  CContext* context = CContext::getCurrent();
  CContextClient* client = context->client;
  int nbClient = client->clientSize;

  computePositionElements(gridDst, gridSrc);
  std::vector<CScalar*> scalarListDstP = gridDst->getScalars();
  std::vector<CAxis*> axisListDstP = gridDst->getAxis();
  std::vector<CDomain*> domainListDstP = gridDst->getDomains();
  CArray<int,1> axisDomainDstOrder = gridDst->axis_domain_order;
  std::vector<CScalar*> scalarListSrcP  = gridSrc->getScalars();
  std::vector<CAxis*> axisListSrcP = gridSrc->getAxis();
  std::vector<CDomain*> domainListSrcP = gridSrc->getDomains();
  CArray<int,1> axisDomainSrcOrder = gridSrc->axis_domain_order;  

  int nElement=axisDomainSrcOrder.numElements() ;
  int indSrc=1 ;
  int indDst=1 ;
  vector<int> nIndexSrc(nElement) ;
  vector<int> nIndexDst(nElement) ;
  vector< CArray<bool,1>* > maskSrc(nElement) ;
  vector< CArray<bool,1>* > maskDst(nElement) ;
    
  int nlocalIndexSrc=1 ;
//  int nlocalIndexDest=1 ;
  nlocalIndexDest=1 ;
  CArray<bool,1> maskScalar(1) ;
  maskScalar  = true ;
  
  
  for(int i=0 ; i<nElement; i++)
  {
    int dimElement = axisDomainSrcOrder(i);
    if (2 == dimElement) //domain
    {
      CDomain* domain=domainListSrcP[elementPositionInGridSrc2DomainPosition_[i]] ;
      nIndexSrc[i] = domain->i_index.numElements() ;
      maskSrc[i]=&domain->localMask ;
    }
    else if (1 == dimElement) //axis
    {
      CAxis* axis=axisListSrcP[elementPositionInGridSrc2AxisPosition_[i]] ;
      nIndexSrc[i] = axis->index.numElements() ;
      maskSrc[i]=&axis->mask ;
    }
    else  //scalar
    {
      nIndexSrc[i]=1 ;
      maskSrc[i]=&maskScalar ;
    }
    nlocalIndexSrc=nlocalIndexSrc*nIndexSrc[i] ;
  }



  int offset=1 ;
  for(int i=0 ; i<nElement; i++)
  {
    int dimElement = axisDomainDstOrder(i);
    if (2 == dimElement) //domain
    {
      CDomain* domain=domainListDstP[elementPositionInGridDst2DomainPosition_[i]] ;
      int nIndex=domain->i_index.numElements() ;
      CArray<bool,1>& localMask=domain->localMask ;
      int nbInd=0 ;
      for(int j=0;j<nIndex;j++) if (localMask(j)) nbInd++ ;
      nIndexDst[i] = nbInd ;
      maskDst[i]=&domain->localMask ;
    }
    else if (1 == dimElement) //axis
    {
      CAxis* axis = axisListDstP[elementPositionInGridDst2AxisPosition_[i]] ;
      int nIndex=axis->index.numElements() ;
      CArray<bool,1>& localMask=axis->mask ;
      int nbInd=0 ;
      for(int j=0;j<nIndex;j++) if (localMask(j)) nbInd++ ;
      nIndexDst[i] = nbInd ;
      maskDst[i]=&axis->mask ;
    }
    else  //scalar
    {
      nIndexDst[i]=1 ;
      maskDst[i]=&maskScalar ;
    }
    if (i<elementPositionInGrid) offset=offset*nIndexDst[i] ;
    nlocalIndexDest=nlocalIndexDest*nIndexDst[i] ;
  }

  vector<int> dstLocalInd ;
  int dimElement = axisDomainDstOrder(elementPositionInGrid);
  if (2 == dimElement) //domain
  {
    CDomain* domain = domainListDstP[elementPositionInGridDst2DomainPosition_[elementPositionInGrid]] ;
    int ni_glo=domain->ni_glo ;
    int nj_glo=domain->nj_glo ;
    int nindex_glo=ni_glo*nj_glo ;
    dstLocalInd.resize(nindex_glo,-1) ;
    int nIndex=domain->i_index.numElements() ;
    CArray<bool,1>& localMask=domain->localMask ;
    int unmaskedInd=0 ;
    int globIndex ;
    for(int i=0;i<nIndex;i++)
    {
      if (localMask(i))
      {
        globIndex=domain->j_index(i)*ni_glo+domain->i_index(i) ;
        dstLocalInd[globIndex]=unmaskedInd ;
        unmaskedInd++ ;
      }
    }
  }
  else if (1 == dimElement) //axis
  {
    CAxis* axis = axisListDstP[elementPositionInGridDst2AxisPosition_[elementPositionInGrid]] ;
    int nindex_glo=axis->n_glo ;
    dstLocalInd.resize(nindex_glo,-1) ;
    int nIndex=axis->index.numElements() ;
    CArray<bool,1>& localMask=axis->mask ; // axis mask must include later data_index
    int unmaskedInd=0 ;
    for(int i=0;i<nIndex;i++)
    {
      if (localMask(i))
      {
        dstLocalInd[axis->index(i)]=unmaskedInd ;
        unmaskedInd++ ;
      }
    }
  }
  else  //scalar
  {
    dstLocalInd.resize(1) ; 
    dstLocalInd[0]=0 ; 
  }

  vector<vector<vector<pair<int,double> > > > dstIndWeight(transformationMapping_.size()) ;
   
  for(int t=0;t<transformationMapping_.size();++t)
  {
    TransformationIndexMap::const_iterator   itTransMap = transformationMapping_[t].begin(),
                                             iteTransMap = transformationMapping_[t].end();
    TransformationWeightMap::const_iterator itTransWeight = transformationWeight_[t].begin();
    dstIndWeight[t].resize(nIndexSrc[elementPositionInGrid]) ;
    
    for(;itTransMap!=iteTransMap;++itTransMap,++itTransWeight)
    {
      int dst=dstLocalInd[itTransMap->first] ;
      if (dst!=-1)
      {
        const vector<int>& srcs=itTransMap->second;
        const vector<double>& weights=itTransWeight->second;
        for(int i=0;i<srcs.size() ;i++) dstIndWeight[t][srcs[i]].push_back(pair<int,double>(dst*offset+t,weights[i])) ;
      }
    }
  }
  int srcInd=0 ;  
  int currentInd ;
  int t=0 ;  
  int srcIndCompressed=0 ;
  
  nonDistributedrecursiveFunct(nElement-1,true,elementPositionInGrid,maskSrc,maskDst, srcInd, srcIndCompressed, nIndexSrc, t, dstIndWeight,  
                               currentInd,localSrc,localDst,weight);
               
}
CATCH


void CGenericAlgorithmTransformation::nonDistributedrecursiveFunct(int currentPos, bool masked, int elementPositionInGrid,
                                                                   vector< CArray<bool,1>* >& maskSrc, vector< CArray<bool,1>* >& maskDst,
                                                                   int& srcInd, int& srcIndCompressed, vector<int>& nIndexSrc,
                                                                   int& t, vector<vector<vector<pair<int,double> > > >& dstIndWeight, int currentInd,
                                                                   vector<int>& localSrc, vector<int>& localDst, vector<double>& weight)
TRY
{
  int masked_ ;
  if (currentPos!=elementPositionInGrid)
  {
    if (currentPos!=0)
    {
      CArray<bool,1>& mask = *maskSrc[currentPos] ;
     
      for(int i=0;i<nIndexSrc[currentPos];i++)
      {
        masked_=masked ;
        if (!mask(i)) masked_=false ;
        nonDistributedrecursiveFunct(currentPos-1, masked_, elementPositionInGrid, maskSrc, maskDst, srcInd, srcIndCompressed, nIndexSrc, t,
                                     dstIndWeight, currentInd, localSrc, localDst, weight);
      }
    }
    else
    {
      CArray<bool,1>& mask = *maskSrc[currentPos] ;
      for(int i=0;i<nIndexSrc[currentPos];i++)
      {
        if (masked && mask(i))
        {
          if (dstIndWeight[t][currentInd].size()>0)
          {
            for(vector<pair<int,double> >::iterator it = dstIndWeight[t][currentInd].begin(); it!=dstIndWeight[t][currentInd].end(); ++it)
            {
              localSrc.push_back(srcIndCompressed) ;
              localDst.push_back(it->first) ;
              weight.push_back(it->second) ;
              (it->first)++ ;
            }
          }
          if (t < dstIndWeight.size()-1) t++ ;
            srcIndCompressed ++ ;
        }
        srcInd++ ;
      }
    }
  }
  else
  {
 
    if (currentPos!=0)
    {

      CArray<bool,1>& mask = *maskSrc[currentPos] ;
      for(int i=0;i<nIndexSrc[currentPos];i++)
      {
        t=0 ;
        masked_=masked ;
        if (!mask(i)) masked_=false ; 
        nonDistributedrecursiveFunct(currentPos-1, masked_, elementPositionInGrid, maskSrc, maskDst, srcInd,
                                     srcIndCompressed, nIndexSrc, t, dstIndWeight , i,  localSrc, localDst, weight);
      }
    }
    else
    {
      for(int i=0;i<nIndexSrc[currentPos];i++)
      {
        if (masked)
        {
          t=0 ;        
          if (dstIndWeight[t][i].size()>0)
          {
            for(vector<pair<int,double> >::iterator it = dstIndWeight[t][i].begin(); it!=dstIndWeight[t][i].end(); ++it)
            {
              localSrc.push_back(srcIndCompressed) ;
              localDst.push_back(it->first) ;
              weight.push_back(it->second) ;
              (it->first)++ ;
            }
           }
          if (t < dstIndWeight.size()-1) t++ ;
          srcIndCompressed ++ ;
        }
        srcInd++ ;
      }
    }
  }

}
CATCH

/*!
  Compute index mapping between element source and element destination with an auxiliary inputs which determine
position of each mapped index in global index of grid destination.
  \param [in] dataAuxInputs auxiliary inputs
*/
void CGenericAlgorithmTransformation::computeIndexSourceMapping(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  computeIndexSourceMapping_(dataAuxInputs);
}
CATCH

std::vector<StdString> CGenericAlgorithmTransformation::getIdAuxInputs()
TRY
{
  return idAuxInputs_;
}
CATCH

CGenericAlgorithmTransformation::AlgoTransType CGenericAlgorithmTransformation::type()
TRY
{
  return type_;
}
CATCH

}
