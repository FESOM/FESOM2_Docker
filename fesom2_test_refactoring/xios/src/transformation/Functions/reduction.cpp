#include "reduction.hpp"
#include "sum_reduction.hpp"
#include "min_reduction.hpp"
#include "max_reduction.hpp"
#include "extract.hpp"
#include "average_reduction.hpp"

namespace xios {

CReductionAlgorithm::CallBackMap* CReductionAlgorithm::reductionCreationCallBacks_ = 0;
std::map<StdString,EReductionType> CReductionAlgorithm::ReductionOperations = std::map<StdString,EReductionType>();
bool CReductionAlgorithm::initReductionOperation(std::map<StdString,EReductionType>& m)
{
  // So so stupid way to intialize operation but it works ...
  m["sum"] = TRANS_REDUCE_SUM;
  CSumReductionAlgorithm::registerTrans();

  m["min"] = TRANS_REDUCE_MIN;
  CMinReductionAlgorithm::registerTrans();

  m["max"] = TRANS_REDUCE_MAX;
  CMaxReductionAlgorithm::registerTrans();

  m["extract"] = TRANS_REDUCE_EXTRACT;
  CExtractReductionAlgorithm::registerTrans();

  m["average"] = TRANS_REDUCE_AVERAGE;
  CAverageReductionAlgorithm::registerTrans();

  return true;
}

bool CReductionAlgorithm::_dummyInit = CReductionAlgorithm::initReductionOperation(CReductionAlgorithm::ReductionOperations);

CReductionAlgorithm* CReductionAlgorithm::createOperation(EReductionType reduceType)
{
  int reduceTypeInt = reduceType;
  CallBackMap::const_iterator it = (*reductionCreationCallBacks_).find(reduceType);
  if ((*reductionCreationCallBacks_).end() == it)
  {
     ERROR("CReductionAlgorithm::createOperation(EReductionType reduceType)",
           << "Operation type " << reduceType
           << "doesn't exist. Please define.");
  }
  return (it->second)();
}

bool CReductionAlgorithm::registerOperation(EReductionType reduceType, CreateOperationCallBack createFn)
{
  if (0 == reductionCreationCallBacks_)
    reductionCreationCallBacks_ = new CallBackMap();

  return (*reductionCreationCallBacks_).insert(make_pair(reduceType, createFn)).second;
}

bool CReductionAlgorithm::unregisterOperation(EReductionType reduceType)
{
  int reduceTypeInt = reduceType;
  return (1 == (*reductionCreationCallBacks_).erase(reduceType));
}


}
