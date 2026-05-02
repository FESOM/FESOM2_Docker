/*!
   \file extract.cpp
   \author Ha NGUYEN
   \since 27 June 2016
   \date 27 June 2016

   \brief extract reduction
 */
#include "extract.hpp"

namespace xios {

CExtractReductionAlgorithm::CExtractReductionAlgorithm()
  : CReductionAlgorithm()
{
}

CReductionAlgorithm* CExtractReductionAlgorithm::create()
{
  return (new CExtractReductionAlgorithm());
}

bool CExtractReductionAlgorithm::registerTrans()
{
  return registerOperation(TRANS_REDUCE_EXTRACT, CExtractReductionAlgorithm::create);
}

void CExtractReductionAlgorithm::apply(const std::vector<std::pair<int,double> >& localIndex,
                                       const double* dataInput,
                                       CArray<double,1>& dataOut,
                                       std::vector<bool>& flagInitial,
                                       bool ignoreMissingValue, bool firstPass)
{
  int nbLocalIndex = localIndex.size();
  int currentlocalIndex = 0;
  for (int idx = 0; idx < nbLocalIndex; ++idx)
  {
    currentlocalIndex = localIndex[idx].first;
    dataOut(currentlocalIndex) = *(dataInput + idx);
  }
}

}
