/*!
   \file distribution_server.cpp
   \author Ha NGUYEN
   \since 13 Jan 2015
   \date 10 Sep 2016

   \brief Index distribution on server side.
 */
#include "distribution_server.hpp"
#include "utils.hpp"

namespace xios {

CDistributionServer::CDistributionServer(int rank, const std::vector<int>& nBegin,
                                         const std::vector<int>& nSize,
                                         const std::vector<int>& nBeginGlobal,
                                         const std::vector<int>& nGlobal)
  : CDistribution(rank, nGlobal.size()), nGlobal_(nGlobal), nBeginGlobal_(nBeginGlobal),
    nSize_(nSize), nBegin_(nBegin), globalLocalIndexMap_()
{
  createGlobalIndex();
}

CDistributionServer::CDistributionServer(int rank,
                                        const std::vector<CArray<int,1> >& globalIndexElements,
                                        const CArray<int,1>& elementOrder,
                                        const std::vector<int>& nBegin,
                                        const std::vector<int>& nSize,
                                        const std::vector<int>& nBeginGlobal,
                                        const std::vector<int>& nGlobal)
  : CDistribution(rank, nGlobal.size()), nGlobal_(nGlobal), nBeginGlobal_(nBeginGlobal),
    nSize_(nSize), nBegin_(nBegin), globalLocalIndexMap_()
{
  createGlobalIndex(globalIndexElements, elementOrder);
}

CDistributionServer::~CDistributionServer()
{
}

/*!
  Create global index on server side
  Like the similar function on client side, this function serves on creating global index
for data written by the server. The global index is used to calculating local index of data
written on each server
*/
void CDistributionServer::createGlobalIndex()
{
  size_t idx = 0, ssize = 1;
  for (int i = 0; i < nSize_.size(); ++i) ssize *= nSize_[i];

  this->globalIndex_.resize(ssize);
  std::vector<int> idxLoop(this->getDims(),0);
  std::vector<int> currentIndex(this->getDims());
  int innerLoopSize = nSize_[0];

  globalLocalIndexMap_.rehash(std::ceil(ssize/globalLocalIndexMap_.max_load_factor()));
  while (idx<ssize)
  {
    for (int i = 0; i < this->dims_-1; ++i)
    {
      if (idxLoop[i] == nSize_[i])
      {
        idxLoop[i] = 0;
        ++idxLoop[i+1];
      }
    }

    for (int i = 1; i < this->dims_; ++i)  currentIndex[i] = idxLoop[i] + nBegin_[i];

    size_t mulDim, globalIndex;
    for (int i = 0; i < innerLoopSize; ++i)
    {
      mulDim = 1;
      globalIndex = i + nBegin_[0];

      for (int k = 1; k < this->dims_; ++k)
      {
        mulDim *= nGlobal_[k-1];
        globalIndex += (currentIndex[k])*mulDim;
      }
      globalLocalIndexMap_[globalIndex] = idx;
      this->globalIndex_(idx) = globalIndex;

      ++idx;
    }
    idxLoop[0] += innerLoopSize;
  }
}

/*!
  Create global index on server side
  Like the similar function on client side, this function serves on creating global index
for data written by the server. The global index is used to calculating local index of data
written on each server
  \param[in] globalIndexElement global index on server side of each element of grid (scalar, axis, domain)
  \param[in] elementOrder the order of elements of grid (e.x: domain->axis or domain->scalar)
*/
void CDistributionServer::createGlobalIndex(const std::vector<CArray<int,1> >& globalIndexElements,
                                            const CArray<int,1>& elementOrder)
{
  int numElement = elementOrder.numElements(), elementIdx = 0;  
  std::vector<int> indexMap(numElement);
  for (int i = 0; i < numElement; ++i)
  {
    indexMap[i] = elementIdx;
    if (2 == elementOrder(i))
    {      
      elementIdx += 2;
    }
    else
      ++elementIdx;
  }

  std::vector<size_t> elementGlobalSize(numElement);
  size_t globalSize = 1;
  for (int i = 0; i < numElement; ++i)
  {
    int elementType = elementOrder(i);
    elementGlobalSize[i] = globalSize;
    if (2 == elementType) // domain
    {
      globalSize *= nGlobal_[indexMap[i]+1] * nGlobal_[indexMap[i]];
    }
    else // axis or scalar
    {
      globalSize *= nGlobal_[indexMap[i]];
    }
  } 

  size_t ssize = 1;
  for (int i = 0; i < globalIndexElements.size(); ++i) ssize *= globalIndexElements[i].numElements();
  this->globalIndex_.resize(ssize);
  globalLocalIndexMap_.rehash(std::ceil(ssize/globalLocalIndexMap_.max_load_factor()));

  std::vector<int> idxLoop(numElement,0);
  std::vector<int> currentIndex(numElement);
  int innerLoopSize = globalIndexElements[0].numElements();

  size_t idx = 0;
  while (idx<ssize)
  {
    for (int i = 0; i < numElement-1; ++i)
    {
      if (idxLoop[i] == globalIndexElements[i].numElements())
      {
        idxLoop[i] = 0;
        ++idxLoop[i+1];
      }
    }

    for (int i = 1; i < numElement; ++i)  currentIndex[i] = globalIndexElements[i](idxLoop[i]);

    size_t mulDim, globalIndex;
    for (int i = 0; i < innerLoopSize; ++i)
    {      
      globalIndex = 0;
      currentIndex[0] = globalIndexElements[0](i);

      for (int k = 0; k < numElement; ++k)
      {     
        globalIndex += (currentIndex[k])*elementGlobalSize[k];
      }
      globalLocalIndexMap_[globalIndex] = idx;
      this->globalIndex_(idx) = globalIndex;
      ++idx;
    }
    idxLoop[0] += innerLoopSize;
  }
}

/*!
  Compute local index for writing data on server
  \param [in] globalIndex Global index received from client
*/
void CDistributionServer::computeLocalIndex(CArray<size_t,1>& globalIndex)
{
  size_t ssize = globalIndex.numElements();
  size_t localIndexSize = std::min(globalIndex_.numElements(), ssize);
  CArray<size_t,1> localIndex(localIndexSize);
  GlobalLocalMap::const_iterator ite = globalLocalIndexMap_.end(), it;
  int i = 0;
  for (size_t idx = 0; idx < ssize; ++idx)
  {
    it = globalLocalIndexMap_.find(globalIndex(idx));
    if (ite != it)
    {
      localIndex(i) = it->second;
      ++i;
    }
  }

  globalIndex.reference(localIndex);
}

/*!
  Transforms local indexes owned by the server into global indexes
  \param [in/out] indexes on input, local indexes of the server,
                          on output, the corresponding global indexes
*/
void CDistributionServer::computeGlobalIndex(CArray<int,1>& indexes) const
{
  for (int i = 0; i < indexes.numElements(); ++i)
  {
    indexes(i) = globalIndex_(indexes(i));
  }
}

/*!
  Get the size of grid index in server (e.x: sizeGrid *= size of each dimensiion)
*/
int CDistributionServer::getGridSize() const
{
   return globalLocalIndexMap_.size();
}

void CDistributionServer::partialClear(void)
{
  GlobalLocalMap void1 ;
  globalLocalIndexMap_.swap(void1) ;
}
  
} // namespace xios
