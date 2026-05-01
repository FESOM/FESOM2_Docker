/*!
   \file distribution.hpp
   \author Ha NGUYEN
   \since 13 Jan 2015
   \date 09 Feb 2015

   \brief Index distribution on server side.
 */
#include "distribution.hpp"

namespace xios {

CDistribution::CDistribution(int rank, int dims, const CArray<size_t,1>& globalIndex)
  : rank_(rank), dims_(dims), globalIndex_(globalIndex.shape())
{
  if (0 != globalIndex.numElements())
    globalIndex_ = globalIndex;
}

const CArray<size_t,1>& CDistribution:: getGlobalIndex() const 
{ 
  return globalIndex_; 
}

CDistribution::~CDistribution()
{ /* Nothing to do */ }

int CDistribution::getDims() const
{
  return dims_;
}

int CDistribution::getRank() const
{
  return rank_;
}

} // namespace xios
