/*!
   \file scalar_algorithm_reduce_scalar.cpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Algorithm for reduce an axis to a scalar
 */
#include "scalar_algorithm_reduce_axis.hpp"
#include "axis.hpp"
#include "scalar.hpp"
#include "reduce_axis_to_scalar.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"

#include "reduction.hpp"

namespace xios {
CGenericAlgorithmTransformation* CScalarAlgorithmReduceAxis::create(CGrid* gridDst, CGrid* gridSrc,
                                                                     CTransformation<CScalar>* transformation,
                                                                     int elementPositionInGrid,
                                                                     std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CScalar*> scalarListDestP = gridDst->getScalars();
  std::vector<CAxis*> axisListSrcP  = gridSrc->getAxis();

  CReduceAxisToScalar* reduceAxis = dynamic_cast<CReduceAxisToScalar*> (transformation);
  int scalarDstIndex = elementPositionInGridDst2ScalarPosition[elementPositionInGrid];
  int axisSrcIndex = elementPositionInGridSrc2AxisPosition[elementPositionInGrid];

  return (new CScalarAlgorithmReduceAxis(scalarListDestP[scalarDstIndex], axisListSrcP[axisSrcIndex], reduceAxis));
}
CATCH

bool CScalarAlgorithmReduceAxis::registerTrans()
TRY
{
  return CGridTransformationFactory<CScalar>::registerTransformation(TRANS_REDUCE_AXIS_TO_SCALAR, create);
}
CATCH

CScalarAlgorithmReduceAxis::CScalarAlgorithmReduceAxis(CScalar* scalarDestination, CAxis* axisSource, CReduceAxisToScalar* algo)
 : CScalarAlgorithmTransformation(scalarDestination, axisSource),
   reduction_(0)
TRY
{
  if (algo->operation.isEmpty())
    ERROR("CScalarAlgorithmReduceAxis::CScalarAlgorithmReduceAxis(CAxis* axisDestination, CAxis* axisSource, CReduceAxisToScalar* algo)",
           << "Operation must be defined."
           << "Axis source " <<axisSource->getId() << std::endl
           << "Scalar destination " << scalarDestination->getId());
  StdString op;
  switch (algo->operation)
  {
    case CReduceAxisToScalar::operation_attr::sum:
      op = "sum";
      break;
    case CReduceAxisToScalar::operation_attr::min:
      op = "min";
      break;
    case CReduceAxisToScalar::operation_attr::max:
      op = "max";
      break;
    case CReduceAxisToScalar::operation_attr::average:
      op = "average";
      break;
    default:
        ERROR("CScalarAlgorithmReduceAxis::CScalarAlgorithmReduceAxis(CScalar* scalarDestination, CAxis* axisSource, CReduceAxisToScalar* algo)",
         << "Operation is wrongly defined. Supported operations: sum, min, max, average." << std::endl
         << "Domain source " <<axisSource->getId() << std::endl
         << "Scalar destination " << scalarDestination->getId());

  }
  
  if (CReductionAlgorithm::ReductionOperations.end() == CReductionAlgorithm::ReductionOperations.find(op))
    ERROR("CScalarAlgorithmReduceAxis::CScalarAlgorithmReduceAxis(CAxis* axisDestination, CAxis* axisSource, CReduceAxisToScalar* algo)",
       << "Operation '" << op << "' not found. Please make sure to use a supported one"
       << "Axis source " <<axisSource->getId() << std::endl
       << "Scalar destination " << scalarDestination->getId());

  reduction_ = CReductionAlgorithm::createOperation(CReductionAlgorithm::ReductionOperations[op]);
}
CATCH

void CScalarAlgorithmReduceAxis::apply(const std::vector<std::pair<int,double> >& localIndex, const double* dataInput, CArray<double,1>& dataOut,
                                         std::vector<bool>& flagInitial, bool ignoreMissingValue, bool firstPass)
TRY
{
  reduction_->apply(localIndex, dataInput, dataOut, flagInitial, ignoreMissingValue, firstPass);
}
CATCH

void CScalarAlgorithmReduceAxis::updateData(CArray<double,1>& dataOut)
TRY
{
  reduction_->updateData(dataOut);
}
CATCH

CScalarAlgorithmReduceAxis::~CScalarAlgorithmReduceAxis()
TRY
{
  if (0 != reduction_) delete reduction_;
}
CATCH

void CScalarAlgorithmReduceAxis::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  int globalIndexSize = axisSrc_-> n_glo;

  for (int idx = 0; idx < globalIndexSize; ++idx)
  {
    transMap[0].push_back(idx);
    transWeight[0].push_back(1.0);
  }
}
CATCH

}
