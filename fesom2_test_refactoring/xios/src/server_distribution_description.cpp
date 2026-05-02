/*!
   \file server_distribution_description.hpp
   \author Ha NGUYEN
   \since 04 Jan 2015
   \date 11 Jan 2016

   \brief Description of index distribution on server(s).
 */

#include "server_distribution_description.hpp"
#include "exception.hpp"

namespace xios
{
  /*!
  \param [in] globalDimensionSize global dimension of grid
  \param [in] nServer number of server
  \param [in] serType type of server distribution. For now, we can distribute server by band or plan
  */
CServerDistributionDescription::CServerDistributionDescription(const std::vector<int>& globalDimensionSize,
                                                               int nServer,
                                                               ServerDistributionType serType)
  : nGlobal_(globalDimensionSize), indexBegin_(), dimensionSizes_(), globalIndex_(),
    vecGlobalIndex_(), serverType_(serType), nServer_(nServer), positionDimensionDistributed_(1)
{
}

CServerDistributionDescription::~CServerDistributionDescription()
{ /* Nothing to do */ }

int CServerDistributionDescription::defaultDistributedDimension(int gridDimension,                                   
                                                                ServerDistributionType serType)
{  
  switch (serType) 
  {
    case BAND_DISTRIBUTION:       
       return ((1 == gridDimension) ? 0 : 1);
      break;
    default:
      break;
  } 
  return -1 ;
}

/*!
  Compute pre-defined global index distribution of server(s).
  \param [in] doComputeGlobalIndex flag to compute global index on each server. By default, false

*/
void CServerDistributionDescription::computeServerDistribution(bool doComputeGlobalIndex,
                                                               int positionDimensionDistributed)
{
  switch (serverType_) {
    case BAND_DISTRIBUTION:
      computeBandDistribution(nServer_, positionDimensionDistributed);
      break;
    default:
      break;
  }

  if (doComputeGlobalIndex)
  {
    vecGlobalIndex_.resize(nServer_);
    int dim = nGlobal_.size();
    std::vector<int> currentIndex(dim);

    for (int idxServer = 0; idxServer < nServer_; ++idxServer)
    {
      size_t ssize = 1, idx = 0;
      for (int j = 0; j < dim; ++j) ssize *= dimensionSizes_[idxServer][j];
      vecGlobalIndex_[idxServer].resize(ssize);

      std::vector<int> idxLoop(dim,0);

      int innerLoopSize = dimensionSizes_[idxServer][0];

      while (idx<ssize)
      {
        for (int idxDim = 0; idxDim < dim-1; ++idxDim)
        {
          if (idxLoop[idxDim] == dimensionSizes_[idxServer][idxDim])
          {
            idxLoop[idxDim] = 0;
            ++idxLoop[idxDim+1];
          }
        }

        for (int idxDim = 1; idxDim < dim; ++idxDim)  currentIndex[idxDim] = idxLoop[idxDim] + indexBegin_[idxServer][idxDim];

        size_t mulDim, globalIndex;
        for (int j = 0; j < innerLoopSize; ++j)
        {
          mulDim = 1;
          globalIndex = j + indexBegin_[idxServer][0];

          for (int k = 1; k < dim; ++k)
          {
            mulDim *= nGlobal_[k-1];
            globalIndex += currentIndex[k] * mulDim;
          }
          vecGlobalIndex_[idxServer](idx) = globalIndex;
          ++idx;
        }
        idxLoop[0] += innerLoopSize;
      }
    }
  }
}

/*!
  Compute global index assigned to a server with a range.E.g: if a grid has 100 points and
  there are 2 servers, the first one takes index from 0 to 49, the second has index from 50 to 99
  \param [in] indexBeginEnd begining and ending index of range
  \param [in] positionDimensionDistributed dimension of server on which we make the cut.
*/
std::vector<int> CServerDistributionDescription::computeServerGlobalIndexInRange(const std::pair<size_t, size_t>& indexBeginEnd,
                                                                     int positionDimensionDistributed)
{
  int nBand  = 0;
  switch (serverType_)
  {
    case BAND_DISTRIBUTION:
      nBand = computeBandDistribution(nServer_, positionDimensionDistributed);
      break;
    case ROOT_DISTRIBUTION:
      nBand = computeRootDistribution(nServer_);
    default:
      break;
  }

  size_t indexBegin = indexBeginEnd.first;
  size_t indexEnd   = indexBeginEnd.second;
  if (indexBegin > indexEnd)
     ERROR("CServerDistributionDescription::computeServerGlobalIndexInRange",
           << "Index begin is larger than index end");

  globalIndex_.rehash(std::ceil((indexEnd-indexBegin+1)/globalIndex_.max_load_factor()));

  int dim = nGlobal_.size();
  std::vector<int> currentIndex(dim);

  for (int idxServer = 0; idxServer < nBand; ++idxServer)
  {
    size_t ssize = 1, idx = 0;
    for (int j = 0; j < dim; ++j) ssize *= dimensionSizes_[idxServer][j];

    std::vector<int> idxLoop(dim,0);
    int innerLoopSize = dimensionSizes_[idxServer][0];

    while (idx<ssize)
    {
      for (int idxDim = 0; idxDim < dim-1; ++idxDim)
      {
        if (idxLoop[idxDim] == dimensionSizes_[idxServer][idxDim])
        {
          idxLoop[idxDim] = 0;
          ++idxLoop[idxDim+1];
        }
      }

      for (int idxDim = 1; idxDim < dim; ++idxDim)  currentIndex[idxDim] = idxLoop[idxDim] + indexBegin_[idxServer][idxDim];

      size_t mulDim, globalIndex;
      for (int j = 0; j < innerLoopSize; ++j)
      {
        mulDim = 1;
        globalIndex = j + indexBegin_[idxServer][0];

        for (int k = 1; k < dim; ++k)
        {
          mulDim *= nGlobal_[k-1];
          globalIndex += (currentIndex[k])*mulDim;
        }
        if ((indexBegin <= globalIndex) && (globalIndex <= indexEnd))
          globalIndex_[globalIndex] = idxServer;
        ++idx;
      }
      idxLoop[0] += innerLoopSize;
    }
  }

    // List of servers without distribution (cause total number of server is greater than number of bands, for example)
  std::vector<int> zeroIndexServer(nServer_-nBand); 
  for (int idxServer = nBand; idxServer < nServer_; ++idxServer)
    zeroIndexServer[idxServer-nBand] = idxServer;

  return zeroIndexServer;
}

/*!
  Compute the global index of grid elements (domain, axis) and their associated server rank.
  Each client knows the general distribution of servers and from which they can compute the pieces of information to hold
  \param [out] indexServerOnElement global index of each element as well as the corresponding server which contains these indices
  \param [in] clientRank rank of client
  \param [in] clientSize number of client
  \param [in] axisDomainOrder the order of element in grid (2 for domain, 1 for axis, 0 for scalar)
  \param [in] positionDimensionDistributed dimension of server on which we make the cut.
*/
std::vector<int> CServerDistributionDescription::computeServerGlobalByElement(std::vector<std::unordered_map<size_t,std::vector<int> > >& indexServerOnElement,
                                                                              int clientRank,
                                                                              int clientSize,
                                                                              const CArray<int,1>& axisDomainOrder,
                                                                              int positionDimensionDistributed)
{
  int nBand  = 0;
  switch (serverType_) {
    case BAND_DISTRIBUTION:
      nBand = computeBandDistribution(nServer_, positionDimensionDistributed);
      break;
    default:
      break;
  }

  int nbElement = axisDomainOrder.numElements();
  indexServerOnElement.resize(nbElement);
  int idx = 0;
  std::vector<int> idxMap(nbElement);
  for (int i = 0; i < nbElement; ++i)
  {
    idxMap[i] = idx;
    if (2 == axisDomainOrder(i)) idx += 2;
    else if (1 == axisDomainOrder(i)) idx += 1;
    // nothing for scalar
  }

  for (int idxServer = 0; idxServer < nBand; ++idxServer)
  {
    std::vector<int> elementDimension(4);
    for (int i = 0; i < nbElement; ++i)
    {
      int elementSize = 1;
      if (2 == axisDomainOrder(i))
      {
        elementSize *= dimensionSizes_[idxServer][idxMap[i]] * dimensionSizes_[idxServer][idxMap[i]+1];
        elementDimension[0] = indexBegin_[idxServer][idxMap[i]];
        elementDimension[1] = indexBegin_[idxServer][idxMap[i]+1];
        elementDimension[2] = dimensionSizes_[idxServer][idxMap[i]];
        elementDimension[3] = dimensionSizes_[idxServer][idxMap[i]+1];
      }

      else if (1 == axisDomainOrder(i))
      {
        elementSize *= dimensionSizes_[idxServer][idxMap[i]];
        elementDimension[0] = indexBegin_[idxServer][idxMap[i]];
        elementDimension[1] = 0;
        elementDimension[2] = dimensionSizes_[idxServer][idxMap[i]];
        elementDimension[3] = 1;
      }
      else
      {
        elementSize *= dimensionSizes_[idxServer][idxMap[i]];
        elementDimension[0] = 0;
        elementDimension[1] = 0;
        elementDimension[2] = 1;
        elementDimension[3] = 1;
      }

      int rangeBegin, rangeSize;
      computeRangeProcIndex(clientRank, clientSize, elementSize, rangeBegin, rangeSize);

      size_t globalIndexElement;
      idx = 0; int idxRange = 0;
      for (int k = 0; k < elementDimension[3]; ++k)
        for (int l = 0; l < elementDimension[2]; ++l)
        {
          globalIndexElement = (l+elementDimension[0]) + (k+elementDimension[1])*elementDimension[2];
          if ((rangeBegin <= idx) && (idxRange < rangeSize))
          {
            indexServerOnElement[i][globalIndexElement].push_back(idxServer);
            ++idxRange;
          }
          ++idx;
        }
    }
  }

  // List of servers without distribution (cause total number of server is greater than number of bands, for example)
  std::vector<int> zeroIndexServer(nServer_-nBand); 
  for (int idxServer = nBand; idxServer < nServer_; ++idxServer)
    zeroIndexServer[idxServer-nBand] = idxServer;

  return zeroIndexServer;
}

/*!
  Compute a range of index on server which a client holds
  For a range of index on a specific server, each client can hold a piece of the index range
  If the range size is smaller than the number of client, there are some clients holding the same index
  \param [in] clientRank rank of client
  \param [in] clientSize number of client
  \param [in] rangeProcSize index range size
  \param [out] rangeBegin begin of range index a client holds
  \param [out] rangeSize size of range index a client holds
*/
void CServerDistributionDescription::computeRangeProcIndex(int clientRank,
                                                           int clientSize,
                                                           int rangeProcSize,
                                                           int& rangeBegin,
                                                           int& rangeSize)
{
  if (rangeProcSize < clientSize)
  {
    int rangeIndex = 0;
    for (int idx = 0; idx < clientSize; ++idx)
    {
      if (idx == clientRank)
      {
        rangeBegin = rangeIndex;
        rangeSize = 1;
      }
      ++rangeIndex;
      if (rangeIndex == rangeProcSize) rangeIndex = 0;
    }
    return;
  }

  int range, indexBegin = 0;
  for (int i = 0; i < clientSize; ++i)
  {
    range = rangeProcSize / clientSize;
    if (i < (rangeProcSize%clientSize)) ++range;
    if (i == clientRank) break;
    indexBegin += range;
  }
  rangeBegin = indexBegin;
  rangeSize = range;
}

/*!
  Compute global index of servers with band distribution
  \param [in] nServer number of server
*/
int CServerDistributionDescription::computeBandDistribution(int nServer, int positionDimensionDistributed)
{
  int dim = nGlobal_.size();
  positionDimensionDistributed_ = positionDimensionDistributed;
  if (1 == dim) positionDimensionDistributed_ = 0;
  if (positionDimensionDistributed_ > dim)
    ERROR("CServerDistributionDescription::computeBandDistribution(int nServer, int positionDimensionDistributed)",
          << "Position of distributed dimension is invalid" << std::endl
          << "Position of distributed dimension is " << positionDimensionDistributed_
          << "Dimension " << dim)

  indexBegin_.resize(nServer);
  dimensionSizes_.resize(nServer);

  for (int i = 0; i< nServer; ++i)
  {
    indexBegin_[i].resize(dim);
    dimensionSizes_[i].resize(dim);
  }

  int njRangeSize;
  int nGlobTemp = 0;
  std::vector<int> njRangeBegin(nServer,0);
  std::vector<int> njRangeEnd(nServer,0);

  int positionDistributed = (1<dim) ? positionDimensionDistributed_ : 0;
  nGlobTemp = nGlobal_[positionDistributed];
  int nbBand = std::min(nGlobTemp, nServer);

  for (int i = 0; i < nbBand; ++i)
  {
    if (0 < i) njRangeBegin[i] = njRangeEnd[i-1];
    njRangeSize = nGlobTemp / nbBand;
    if (i < nGlobTemp%nbBand) ++njRangeSize;
    njRangeEnd[i] = njRangeSize + njRangeBegin[i];
  }
  njRangeEnd[nbBand-1] = nGlobTemp;

  for (int i = nbBand; i < nServer; ++i)
  {
    njRangeBegin[i] = njRangeEnd[i] = 0;
  }

  for (int i = 0; i < nServer; ++i)
  {
    for (int j = 0; j < dim; ++j)
    {
      if (positionDistributed != j)
      {
        if (1 == dim)
        {
          indexBegin_[i][j] = njRangeBegin[i];
          dimensionSizes_[i][j] = njRangeEnd[i] - njRangeBegin[i];
        }
        else
        {
          indexBegin_[i][j] = 0;
          dimensionSizes_[i][j] = nGlobal_[j];
        }
      }
      else
      {
        indexBegin_[i][j] = njRangeBegin[i];
        dimensionSizes_[i][j] = njRangeEnd[i] - njRangeBegin[i];
      }
    }
  }

  return nbBand;
}


/*!
  Compute global index of servers with root distribution : only root server will received data
  \param [in] nServer number of server
*/
int CServerDistributionDescription::computeRootDistribution(int nServer, int positionDimensionDistributed)
{
  int dim = nGlobal_.size();
  positionDimensionDistributed_ = positionDimensionDistributed;
  if (1 == dim) positionDimensionDistributed_ = 0;
  if (positionDimensionDistributed_ > dim)
    ERROR("CServerDistributionDescription::computeBandDistribution(int nServer, int positionDimensionDistributed)",
          << "Position of distributed dimension is invalid" << std::endl
          << "Position of distributed dimension is " << positionDimensionDistributed_
          << "Dimension " << dim)

  indexBegin_.resize(nServer);
  dimensionSizes_.resize(nServer);

  for (int i = 0; i< nServer; ++i)
  {
    indexBegin_[i].resize(dim);
    dimensionSizes_[i].resize(dim);
  }

  int nGlobTemp = 0;

  int positionDistributed = (1<dim) ? positionDimensionDistributed_ : 0;
  nGlobTemp = nGlobal_[positionDistributed];
  int nbBand = 1 ;


  for (int i = 0; i < nServer; ++i)
  {
    for (int j = 0; j < dim; ++j)
    {
      if (positionDistributed != j) // bad coding, need to be rewrite
      {
        if (1 == dim)
        {
          if (i==0)
          {
            indexBegin_[i][j] = 0;
            dimensionSizes_[i][j] = nGlobTemp;
          }
          else
          {
            indexBegin_[i][j] = nGlobTemp-1;
            dimensionSizes_[i][j] = 0;
          }
        }
        else
        {
          indexBegin_[i][j] = 0;
          dimensionSizes_[i][j] = nGlobal_[j];
        }
      }
      else
      {
        if (i==0)
        {
          indexBegin_[i][j] = 0;
          dimensionSizes_[i][j] = nGlobTemp;
        }
        else
        {
          indexBegin_[i][j] = nGlobTemp-1;
          dimensionSizes_[i][j] = 0;
        }
      }
    }
  }

  return nbBand;
}




/*!
  Get size of each dimension on distributed server
  \return size of dimensions on server(s)
*/
std::vector<std::vector<int> > CServerDistributionDescription::getServerDimensionSizes() const
{
  return dimensionSizes_;
}

/*!
  Get index begin of each dimension on distributed server
  \return index begin of dimensions on server(s)
*/
std::vector<std::vector<int> > CServerDistributionDescription::getServerIndexBegin() const
{
  return indexBegin_;
}

/*!
  Get global index on distributed server
  \return global index on server(s)
*/
const std::vector<CArray<size_t,1> >& CServerDistributionDescription::getGlobalIndex() const
{
  return vecGlobalIndex_;
}

/*!
  Get global index calculated by computeServerGlobalIndexInRange
*/
const std::unordered_map<size_t,int>& CServerDistributionDescription::getGlobalIndexRange() const
{
  return globalIndex_;
}

int CServerDistributionDescription::getDimensionDistributed()
{
  return ((1<nGlobal_.size()) ? positionDimensionDistributed_ : 0);
}

} // namespace xios
