/*!
   \file axis_algorithm_reduce_axis.cpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Algorithm for reduce a axis to an axis
 */
#include "axis_algorithm_reduce_axis.hpp"
#include "reduce_axis_to_axis.hpp"
#include "axis.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "reduction.hpp"

namespace xios {
CGenericAlgorithmTransformation* CAxisAlgorithmReduceAxis::create(CGrid* gridDst, CGrid* gridSrc,
                                                                   CTransformation<CAxis>* transformation,
                                                                   int elementPositionInGrid,
                                                                   std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                                   std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                                   std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                                   std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                                   std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                                   std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CAxis*> axisListDestP = gridDst->getAxis();
  std::vector<CAxis*> axisListSrcP  = gridSrc->getAxis();

  CReduceAxisToAxis* reduceAxis = dynamic_cast<CReduceAxisToAxis*> (transformation);
  int axisDstIndex   = elementPositionInGridDst2AxisPosition[elementPositionInGrid];
  int axisSrcIndex = elementPositionInGridSrc2AxisPosition[elementPositionInGrid];

  return (new CAxisAlgorithmReduceAxis(axisListDestP[axisDstIndex], axisListSrcP[axisSrcIndex], reduceAxis));
}
CATCH

bool CAxisAlgorithmReduceAxis::registerTrans()
TRY
{
  return CGridTransformationFactory<CAxis>::registerTransformation(TRANS_REDUCE_AXIS_TO_AXIS, create);
}
CATCH


CAxisAlgorithmReduceAxis::CAxisAlgorithmReduceAxis(CAxis* axisDestination, CAxis* axisSource, CReduceAxisToAxis* algo)
 : CAxisAlgorithmTransformation(axisDestination, axisSource), reduction_(0)
TRY
{
  eliminateRedondantSrc_= false ;
  algo->checkValid(axisDestination, axisSource);
  StdString op;
  switch (algo->operation)
  {
    case CReduceAxisToAxis::operation_attr::sum:
      op = "sum";
      break;
    case CReduceAxisToAxis::operation_attr::min:
      op = "min";
      break;
    case CReduceAxisToAxis::operation_attr::max:
      op = "max";
      break;
    case CReduceAxisToAxis::operation_attr::average:
      op = "average";
      break;
    default:
        ERROR("CAxisAlgorithmReduceAxis::CAxisAlgorithmReduceAxis(CAxis* axisDestination, CAxis* axisSource, CReduceAxisToAxis* algo)",
         << "Operation is wrongly defined. Supported operations: sum, min, max, average." << std::endl
         << "Axis source " <<axisSource->getId() << std::endl
         << "Axis destination " << axisDestination->getId());

  }

  reduction_ = CReductionAlgorithm::createOperation(CReductionAlgorithm::ReductionOperations[op]);
}
CATCH

void CAxisAlgorithmReduceAxis::apply(const std::vector<std::pair<int,double> >& localIndex,
                                       const double* dataInput,
                                       CArray<double,1>& dataOut,
                                       std::vector<bool>& flagInitial,                     
                                       bool ignoreMissingValue, bool firstPass)
TRY
{
  reduction_->apply(localIndex, dataInput, dataOut, flagInitial, ignoreMissingValue, firstPass);
}
CATCH

void CAxisAlgorithmReduceAxis::updateData(CArray<double,1>& dataOut)
TRY
{
  reduction_->updateData(dataOut);
}
CATCH

CAxisAlgorithmReduceAxis::~CAxisAlgorithmReduceAxis()
TRY
{
  if (0 != reduction_) delete reduction_;
}
CATCH

void CAxisAlgorithmReduceAxis::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];
  CArray<int,1>& axisDstIndex = axisDest_->index;
  int nbAxisIdx = axisDstIndex.numElements();
  for (int idxAxis = 0; idxAxis < nbAxisIdx; ++idxAxis)
  {
    int globalAxisIdx = axisDstIndex(idxAxis);
    transMap[globalAxisIdx].resize(1);
    transWeight[globalAxisIdx].resize(1);
    transMap[globalAxisIdx][0]=globalAxisIdx ;      
    transWeight[globalAxisIdx][0] = 1.0 ;      
  }
}
CATCH

}
