/*!
   \file distribution_client.cpp
   \author Ha NGUYEN
   \since 13 Jan 2015
   \date 09 Mars 2015

   \brief Index distribution on client side.
 */
#include "distribution_client.hpp"

namespace xios {

CDistributionClient::CDistributionClient(int rank, CGrid* grid, bool isTiled)
   : CDistribution(rank, 0)
   , axisDomainOrder_()
   , nLocal_(), nGlob_(), nBeginLocal_(), nBeginGlobal_()
   , dataNIndex_(), dataDims_(), dataBegin_(), dataIndex_()
   , gridMask_(), indexMap_()
   , isDataDistributed_(true), axisNum_(0), domainNum_(0)
   , localDataIndex_(), localMaskIndex_()
   , globalLocalDataSendToServerMap_()
   , infoIndex_(), isComputed_(false)
   , elementLocalIndex_(), elementGlobalIndex_(), elementIndexData_()
   , elementNLocal_(), elementNGlobal_()
{
  readDistributionInfo(grid, isTiled);
  createGlobalIndex();
}

CDistributionClient::~CDistributionClient()
{ /* Nothing to do */ }

void CDistributionClient::partialClear()
{
  GlobalLocalMap void1 ;
  GlobalLocalMap void2 ;
  std::vector<int> void3 ;
  std::vector<bool> void4 ;

  globalLocalDataSendToServerMap_.swap(void1) ;
  globalDataIndex_.swap(void2) ;
  localDataIndex_.swap(void3);
  localMaskIndex_.swap(void4) ;
}

/*!
  Read information of a grid to generate distribution.
  Every grid is composed of several axis or/and domain(s). Their information are processed
stored and used to calculate index distribution between client and server
  \param [in] grid Grid to read
*/
void CDistributionClient::readDistributionInfo(CGrid* grid, bool isTiled)
{
  std::vector<CDomain*> domList = grid->getDomains();
  std::vector<CAxis*> axisList = grid->getAxis();
  std::vector<CScalar*> scalarList = grid->getScalars();
  CArray<int,1> axisDomainOrder = grid->axis_domain_order;

  readDistributionInfo(domList, axisList, scalarList, axisDomainOrder, isTiled);

  // Then check mask of grid
  int gridDim = domList.size() * 2 + axisList.size();
  switch (gridDim) {
    case 0:
      gridMask_.resize(1);
      gridMask_(0) = true;
      break;
    case 1:
      if (!grid->mask_1d.isEmpty()) readGridMaskInfo(grid->mask_1d);
      break;
    case 2:
      if (!grid->mask_2d.isEmpty()) readGridMaskInfo(grid->mask_2d);
      break;
    case 3:
      if (!grid->mask_3d.isEmpty()) readGridMaskInfo(grid->mask_3d);
      break;
    case 4:
      if (!grid->mask_4d.isEmpty()) readGridMaskInfo(grid->mask_4d);
      break;
    case 5:
      if (!grid->mask_5d.isEmpty()) readGridMaskInfo(grid->mask_5d);
      break;
    case 6:
      if (!grid->mask_6d.isEmpty()) readGridMaskInfo(grid->mask_6d);
      break;
    case 7:
      if (!grid->mask_7d.isEmpty()) readGridMaskInfo(grid->mask_7d);
      break;
    default:
      break;
  }
}

/*!
  Read information from domain(s) and axis to generate distribution.
  All information related to domain, e.g ibegin, jbegin, ni, nj, ni_glo, nj_glo
as well as related to axis, e.g dataNIndex, dataIndex will be stored to compute
the distribution between clients and servers. Till now, every data structure of domain has been kept
like before, e.g: data_n_index to make sure a compability, however, it should be changed?
  \param [in] domList List of domains of grid
  \param [in] axisList List of axis of grid
  \param [in] scalarList List of scalar of grid
  \param [in] axisDomainOrder order of axis and domain inside a grid. 2 if domain, 1 if axis and zero if scalar
  \param [in] isTiled If true, domain data attributes should be ignored
*/
void CDistributionClient::readDistributionInfo(const std::vector<CDomain*>& domList,
                                               const std::vector<CAxis*>& axisList,
                                               const std::vector<CScalar*>& scalarList,
                                               const CArray<int,1>& axisDomainOrder,
                                               bool isTiled)
{
  domainNum_ = domList.size();
  axisNum_   = axisList.size();
  numElement_ = axisDomainOrder.numElements(); // Number of element, e.x: Axis, Domain

  axisDomainOrder_.resize(numElement_);
  axisDomainOrder_ = axisDomainOrder;

  // Because domain and axis can be in any order (axis1, domain1, axis2, axis3, )
  // their position should be specified. In axisDomainOrder, domain == true, axis == false
  int idx = 0;
  indexMap_.resize(numElement_);
  this->dims_ = numElement_;
  for (int i = 0; i < numElement_; ++i)
  {
    indexMap_[i] = idx;
    if (2 == axisDomainOrder(i))
    {
      ++(this->dims_);
      idx += 2;
    }
    else ++idx;
  }

  // Size of each dimension (local and global)
  nLocal_.resize(this->dims_);
  nGlob_.resize(this->dims_);
  nBeginLocal_.resize(this->dims_,0);
  nBeginGlobal_.resize(this->dims_,0);

  // Data_n_index of domain or axis (For now, axis uses its size as data_n_index
  dataNIndex_.resize(numElement_);
  dataDims_.resize(numElement_);
  dataBegin_.resize(this->dims_);

  // Data_*_index of each dimension
  dataIndex_.resize(this->dims_);
  infoIndex_.resize(this->dims_);

  // A trick to determine position of each domain in domainList
  int domIndex = 0, axisIndex = 0, scalarIndex = 0;
  idx = 0;

  elementLocalIndex_.resize(numElement_);
  elementGlobalIndex_.resize(numElement_);
  elementIndexData_.resize(numElement_);
  elementNLocal_.resize(numElement_);
  elementNGlobal_.resize(numElement_);
  elementNLocal_[0] = 1;
  elementNGlobal_[0] = 1;
  size_t localSize = 1, globalSize = 1;

  isDataDistributed_ = false;
  // Update all the vectors above
  for (idx = 0; idx < numElement_; ++idx)
  {
    int eleDim = axisDomainOrder(idx);
    elementNLocal_[idx] = localSize;
    elementNGlobal_[idx] = globalSize;

    // If this is a domain
    if (2 == eleDim)
    {
      // On the j axis
      nLocal_.at(indexMap_[idx]+1) = domList[domIndex]->nj.getValue();
      nGlob_.at(indexMap_[idx]+1)  = domList[domIndex]->nj_glo.getValue();
      nBeginLocal_.at(indexMap_[idx]+1) = 0;
      nBeginGlobal_.at(indexMap_[idx]+1) = domList[domIndex]->jbegin;

      // On the i axis
      nLocal_.at(indexMap_[idx]) = domList[domIndex]->ni.getValue();
      nGlob_.at(indexMap_[idx]) = domList[domIndex]->ni_glo.getValue();
      nBeginLocal_.at(indexMap_[idx]) = 0;
      nBeginGlobal_.at(indexMap_[idx]) = domList[domIndex]->ibegin;

      if (isTiled)
      // Ignore all data attributes, if defined, for tiled domains
      {
        dataBegin_.at(indexMap_[idx]+1) = 0;
        dataBegin_.at(indexMap_[idx]) = 0;

        // Fill dataIndex_ and infoIndex_
        CArray<int,1>& infoIndexI = infoIndex_.at(indexMap_[idx]);
        CArray<int,1>& infoIndexJ = infoIndex_.at(indexMap_[idx]+1);
        CArray<int,1>& dataIndexI = dataIndex_.at(indexMap_[idx]);
        CArray<int,1>& dataIndexJ = dataIndex_.at(indexMap_[idx]+1);
        domList[domIndex]->computeCompressionTiled(dataIndexI, dataIndexJ, infoIndexI, infoIndexJ);

      }
      else
      {
        // On the j axis
        dataBegin_.at(indexMap_[idx]+1) = domList[domIndex]->data_jbegin.getValue();
        dataIndex_.at(indexMap_[idx]+1).reference(domList[domIndex]->data_j_index);
        infoIndex_.at(indexMap_[idx]+1).reference(domList[domIndex]->j_index);

        // On the i axis
        dataBegin_.at(indexMap_[idx]) = domList[domIndex]->data_ibegin.getValue();
        dataIndex_.at(indexMap_[idx]).reference(domList[domIndex]->data_i_index);
        infoIndex_.at(indexMap_[idx]).reference(domList[domIndex]->i_index);

      }

      dataNIndex_.at(idx) = isTiled ? (domList[domIndex]->ni*domList[domIndex]->nj) : domList[domIndex]->data_i_index.numElements();
      dataDims_.at(idx) = isTiled ? 1 : domList[domIndex]->data_dim.getValue();

      isDataDistributed_ |= domList[domIndex]->isDistributed();

      localSize *= nLocal_.at(indexMap_[idx]+1)* nLocal_.at(indexMap_[idx]);
      globalSize *= nGlob_.at(indexMap_[idx]+1)* nGlob_.at(indexMap_[idx]);
      ++domIndex;
    }
    else if (1 == eleDim)// So it's an axis
    {
      nLocal_.at(indexMap_[idx]) = axisList[axisIndex]->n.getValue();
      nGlob_.at(indexMap_[idx]) = axisList[axisIndex]->n_glo.getValue();
      nBeginLocal_.at(indexMap_[idx]) = 0;
      nBeginGlobal_.at(indexMap_[idx]) = axisList[axisIndex]->begin.getValue();

      dataBegin_.at(indexMap_[idx]) = axisList[axisIndex]->data_begin.getValue();
      dataIndex_.at(indexMap_[idx]).reference(axisList[axisIndex]->data_index);
      infoIndex_.at(indexMap_[idx]).reference(axisList[axisIndex]->index);
      dataNIndex_.at(idx) = axisList[axisIndex]->data_index.numElements();
      dataDims_.at(idx) = 1;

      isDataDistributed_ |= axisList[axisIndex]->isDistributed();

      localSize *= nLocal_.at(indexMap_[idx]);
      globalSize *= nGlob_.at(indexMap_[idx]);

      ++axisIndex;
    }
    else // scalar
    {
      nLocal_.at(indexMap_[idx]) = 1;
      nGlob_.at(indexMap_[idx]) = 1;
      nBeginLocal_.at(indexMap_[idx]) = 0;
      nBeginGlobal_.at(indexMap_[idx]) = 1;

      dataBegin_.at(indexMap_[idx]) = 0;
      dataIndex_.at(indexMap_[idx]).resize(1); dataIndex_.at(indexMap_[idx])(0) = 0;
      infoIndex_.at(indexMap_[idx]).resize(1); infoIndex_.at(indexMap_[idx])(0) = 0;
      dataNIndex_.at(idx) = 1;
      dataDims_.at(idx) = 1;

      isDataDistributed_ |= false;

      localSize *= nLocal_.at(indexMap_[idx]);
      globalSize *= nGlob_.at(indexMap_[idx]);

      ++scalarIndex;
    }
  }
}

/*!
  Create local index of domain(s).
  A domain can have data index which even contains the "ghost" points. Very often, these
data surround the true data. In order to send correct data to server,
a client need to know index of the true data.
*/
void CDistributionClient::createLocalDomainDataIndex()
{
  int idxDomain = 0;
  for (int i = 0; i < axisDomainOrder_.numElements(); ++i)
  {
    if (2 == axisDomainOrder_(i))
    {
      elementIndexData_[i].resize(dataNIndex_[i]);
      elementIndexData_[i] = false;
      int iIdx, jIdx = 0, count = 0, localIndex;
      for (int j = 0; j < dataNIndex_[i]; ++j)
      {
        iIdx = getDomainIndex((dataIndex_[indexMap_[i]])(j), (dataIndex_[indexMap_[i]+1])(j),
                              dataBegin_[indexMap_[i]], dataBegin_[indexMap_[i]+1],
                              dataDims_[i], nLocal_[indexMap_[i]], jIdx);

        if ((iIdx >= nBeginLocal_[indexMap_[i]]) && (iIdx < nLocal_[indexMap_[i]]) &&
           (jIdx >= nBeginLocal_[indexMap_[i]+1]) && (jIdx < nLocal_[indexMap_[i]+1]))
        {
          ++count;
          elementIndexData_[i](j) = true;
        }
      }

      elementLocalIndex_[i].resize(count);
      elementGlobalIndex_[i].resize(count);
      count = 0;
      CArray<bool,1>& tmpIndexElementData = elementIndexData_[i];
      CArray<int,1>& tmpLocalElementIndex = elementLocalIndex_[i];
      CArray<size_t,1>& tmpGlobalElementIndex = elementGlobalIndex_[i];
      for (int j = 0; j < dataNIndex_[i]; ++j)
      {
        if (tmpIndexElementData(j))
        {
          iIdx = getDomainIndex((dataIndex_[indexMap_[i]])(j), (dataIndex_[indexMap_[i]+1])(j),
                                dataBegin_[indexMap_[i]], dataBegin_[indexMap_[i]+1],
                                dataDims_[i], nLocal_[indexMap_[i]], jIdx);
          localIndex = tmpLocalElementIndex(count) = iIdx + jIdx * nLocal_[indexMap_[i]];
          tmpGlobalElementIndex(count) = (infoIndex_[indexMap_[i]])(localIndex) + ((infoIndex_[indexMap_[i]+1])(localIndex))*nGlob_[indexMap_[i]];
          ++count;
        }
      }
      ++idxDomain;
    }
  }
}

/*!
  Create local index of axis.
*/
void CDistributionClient::createLocalAxisDataIndex()
{
  int idxAxis = 0;
  for (int i = 0; i < axisDomainOrder_.numElements(); ++i)
  {
    if (1 == axisDomainOrder_(i))
    {
      elementIndexData_[i].resize(dataNIndex_[i]);
      elementIndexData_[i] = false;
      int iIdx = 0, count = 0;
      for (int j = 0; j < dataNIndex_[i]; ++j)
      {
        iIdx = getAxisIndex((dataIndex_[indexMap_[i]])(j), dataBegin_[indexMap_[i]], nLocal_[indexMap_[i]]);
        if ((iIdx >= nBeginLocal_[indexMap_[i]]) &&
           (iIdx < nLocal_[indexMap_[i]]) )//&& (axisMasks_[idxAxis](iIdx)))
        {
          ++count;
          elementIndexData_[i](j) = true;
        }
      }

      elementLocalIndex_[i].resize(count);
      elementGlobalIndex_[i].resize(count);
      count = 0;
      CArray<bool,1>& tmpIndexElementData = elementIndexData_[i];
      CArray<int,1>& tmpLocalElementIndex = elementLocalIndex_[i];
      CArray<size_t,1>& tmpGlobalElementIndex = elementGlobalIndex_[i];
      for (int j = 0; j < dataNIndex_[i]; ++j)
      {
        if (tmpIndexElementData(j))
        {
          iIdx = tmpLocalElementIndex(count) = getAxisIndex((dataIndex_[indexMap_[i]])(j), dataBegin_[indexMap_[i]], nLocal_[indexMap_[i]]);
          tmpGlobalElementIndex(count) = (infoIndex_[indexMap_[i]])(iIdx);
          ++count;
        }
      }
      ++idxAxis;
    }
  }
}

/*!
  Create local index of scalar.
*/
void CDistributionClient::createLocalScalarDataIndex()
{
  int idxAxis = 0;
  for (int i = 0; i < axisDomainOrder_.numElements(); ++i)
  {
    if (0 == axisDomainOrder_(i))
    {
      elementIndexData_[i].resize(dataNIndex_[i]);
      elementIndexData_[i] = true;
      int count = 1;

      elementLocalIndex_[i].resize(count);
      elementLocalIndex_[i] = 0;
      elementGlobalIndex_[i].resize(count);
      elementGlobalIndex_[i] = 0;
    }
  }
}

/*!
   Create global index on client
   In order to do the mapping between client-server, each client creates its own
global index of sending data. This global index is then used to calculate to which server
the client needs to send it data as well as which part of data belongs to the server.
So as to make clients and server coherent in order of index, global index is calculated by
take into account of C-convention, the rightmost dimension varies faster.
*/
void CDistributionClient::createGlobalIndexSendToServer()
{
  if (isComputed_) return;
  isComputed_ = true;
  createLocalDomainDataIndex();
  createLocalAxisDataIndex();
  createLocalScalarDataIndex();

  int idxDomain = 0, idxAxis = 0;
  std::vector<int> eachElementSize(numElement_);

  // Precompute size of the loop
  for (int i = 0; i < numElement_; ++i)
  {
    eachElementSize[i] = elementLocalIndex_[i].numElements();
  }

  //   Compute size of the global index on client
  std::vector<StdSize> idxLoop(numElement_,0);
  std::vector<StdSize> currentIndex(numElement_,0);
  std::vector<StdSize> currentGlobalIndex(numElement_,0);
  int innerLoopSize = eachElementSize[0];
  size_t idx = 0, indexLocalDataOnClientCount = 0;
  size_t ssize = 1;

  for (int i = 0; i < numElement_; ++i) ssize *= eachElementSize[i];

  localDataIndex_.resize(ssize);
  if (!gridMask_.isEmpty()) localMaskIndex_.resize(ssize);
  localMaskedDataIndex_.resize(ssize);
  globalDataIndex_.rehash(std::ceil(ssize/globalDataIndex_.max_load_factor()));
  globalLocalDataSendToServerMap_.rehash(std::ceil(ssize/globalLocalDataSendToServerMap_.max_load_factor()));


  // We need to loop with data index
  idxLoop.assign(numElement_,0);
  idx = indexLocalDataOnClientCount = 0;
  ssize = 1; for (int i = 0; i < numElement_; ++i) ssize *= dataNIndex_[i];
  innerLoopSize = dataNIndex_[0];
  int countLocalData = 0;
  std::vector<int> correctIndexOfElement(numElement_,0);
  bool isOuterIndexCorrect = true;
  while (idx < ssize)
  {
    for (int i = 0; i < numElement_-1; ++i)
    {
      if (idxLoop[i] == dataNIndex_[i])
      {
        idxLoop[i] = 0;
        correctIndexOfElement[i] = 0;
        ++idxLoop[i+1];
        if (isOuterIndexCorrect) ++correctIndexOfElement[i+1];
      }
    }

    // Depending the inner-most element axis or domain,
    // The outer loop index begins correspondingly at one (1) or zero (0)
    bool isIndexElementDataCorrect = true;
    for (int i = 1; i < numElement_; ++i)
    {
      if (elementIndexData_[i](idxLoop[i]))
      {
        currentIndex[i] = elementLocalIndex_[i](correctIndexOfElement[i]);
        currentGlobalIndex[i] = elementGlobalIndex_[i](correctIndexOfElement[i]);
        isIndexElementDataCorrect &= true;
      }
      else isIndexElementDataCorrect = false;
    }

    isOuterIndexCorrect = isIndexElementDataCorrect;

    if (isOuterIndexCorrect)
    {
      // Inner most index
      int correctIndexInnerElement = 0;
      for (int i = 0; i < innerLoopSize; ++i)
      {
        bool isCurrentIndexDataCorrect = isOuterIndexCorrect;
        if (elementIndexData_[0](i))
        {
          currentIndex[0] = elementLocalIndex_[0](correctIndexInnerElement);
          currentGlobalIndex[0] = elementGlobalIndex_[0](correctIndexInnerElement);
          isCurrentIndexDataCorrect &= true;
          ++correctIndexInnerElement;
        }
        else isCurrentIndexDataCorrect = false;

        if (isCurrentIndexDataCorrect)
        {
          bool maskTmp = true;
          bool maskGridTmp = true;
          size_t globalIndex = 0;
          for (int k = 0; k < numElement_; ++k)
          {
            globalIndex += (currentGlobalIndex[k])*elementNGlobal_[k];
          }
          globalDataIndex_[globalIndex] = indexLocalDataOnClientCount;
          localDataIndex_[indexLocalDataOnClientCount] = countLocalData;
          globalLocalDataSendToServerMap_[globalIndex] = indexLocalDataOnClientCount;
          localMaskedDataIndex_[indexLocalDataOnClientCount] = indexLocalDataOnClientCount;

          // Grid mask: unmasked values will be replaces by NaN and then all values will be sent
          if (!gridMask_.isEmpty())
          {
            int gridMaskIndex = 0;
            for (int k = 0; k < this->numElement_; ++k)
            {
              gridMaskIndex += (currentIndex[k])*elementNLocal_[k];
            }
            maskGridTmp =  gridMask_(gridMaskIndex);
            if (maskGridTmp)
              localMaskIndex_[indexLocalDataOnClientCount] = true;
            else
              localMaskIndex_[indexLocalDataOnClientCount] = false;
          }

          ++indexLocalDataOnClientCount;

        }
        ++countLocalData;
        correctIndexOfElement[0] = correctIndexInnerElement;;
      }
    }
    else countLocalData+=innerLoopSize ;

    idxLoop[0] += innerLoopSize;
    idx += innerLoopSize;
  }
}

void CDistributionClient::createGlobalIndex()
{
}

/*!
  Retrieve index i and index j of a domain from its data index
  Data contains not only true data, which are sent to servers, but also ghost data, which
very often play a role of border of each local data, so does data index. Because data of a domain
can be one dimension, or two dimensions, there is a need to convert data index to domain index
  \param [in] dataIIndex index of i data
  \param [in] dataJIndex index of j data
  \param [in] dataIBegin index begin of i data
  \param [in] dataJBegin index begin of j data
  \param [in] dataDim dimension of data (1 or 2)
  \param [in] ni local size ni of domain
  \param [out] j j index of domain
  \return i index of domain
*/
int CDistributionClient::getDomainIndex(const int& dataIIndex, const int& dataJIndex,
                                        const int& dataIBegin, const int& dataJBegin,
                                        const int& dataDim, const int& ni, int& j)
{
  int i;
  int tempI = dataIIndex + dataIBegin,
      tempJ = (dataJIndex + dataJBegin);
  if (ni == 0)
  {
    i = -1;
    j = -1;
    return i;
  }
  if ((tempI < 0) || (tempJ < 0))
  {
    i = -1;
    j = -1;
    return i;
  }
  else
  {
    i = (dataDim == 1) ? (tempI) % ni : (tempI) ;
    j = (dataDim == 1) ? (tempI) / ni : (tempJ) ;
  }
  return i;
}

/*!
  Retrieve index of an axis from its data index
  \param [in] dataIndex index of data
  \param [in] dataBegin index begin of data
  \param [in] ni local size of axis
  \return index of domain
*/
int CDistributionClient::getAxisIndex(const int& dataIndex, const int& dataBegin, const int& ni)
{
  if (ni == 0)
  {
    return -1;
  }
  int tempI = dataIndex;
  if ((tempI < 0) || (tempI > ni))
    return -1;
  else
    return tempI;
}

/*!
  Return global local data mapping of client
*/
CDistributionClient::GlobalLocalDataMap& CDistributionClient::getGlobalLocalDataSendToServer()
{
  if (!isComputed_) createGlobalIndexSendToServer();
  return globalLocalDataSendToServerMap_;
}

CDistributionClient::GlobalLocalDataMap& CDistributionClient::getGlobalDataIndexOnClient()
{
  if (!isComputed_) createGlobalIndexSendToServer();
  return globalDataIndex_;
}

/*!
  Return local data index of client
*/
const std::vector<int>& CDistributionClient::getLocalDataIndexOnClient()
{
  if (!isComputed_) createGlobalIndexSendToServer();
  return localDataIndex_;
}

/*!
  Return local mask index of client
*/
const std::vector<bool>& CDistributionClient::getLocalMaskIndexOnClient()
{
  if (!isComputed_) createGlobalIndexSendToServer();
  return localMaskIndex_;
}

/*!
  Return local mask index of client
*/
const std::vector<int>& CDistributionClient::getLocalMaskedDataIndexOnClient()
{
  if (!isComputed_) createGlobalIndexSendToServer();
  return localMaskedDataIndex_;
}

} // namespace xios
