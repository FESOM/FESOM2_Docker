/*!
   \file scalar_algorithm_reduce_scalar.cpp
 
   \brief Algorithm for reduce an scalar to a scalar
 */
#include "scalar_algorithm_reduce_scalar.hpp"
#include "scalar.hpp"
#include "reduce_scalar_to_scalar.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "reduction.hpp"


namespace xios {
CGenericAlgorithmTransformation* CScalarAlgorithmReduceScalar::create(CGrid* gridDst, CGrid* gridSrc,
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
  std::vector<CScalar*> scalarListSrcP  = gridSrc->getScalars();

  CReduceScalarToScalar* reduceScalar = dynamic_cast<CReduceScalarToScalar*> (transformation);
  int scalarDstIndex = elementPositionInGridDst2ScalarPosition[elementPositionInGrid];
  int scalarSrcIndex = elementPositionInGridSrc2AxisPosition[elementPositionInGrid];

  return (new CScalarAlgorithmReduceScalar(scalarListDestP[scalarDstIndex], scalarListSrcP[scalarSrcIndex], reduceScalar));
}
CATCH

bool CScalarAlgorithmReduceScalar::registerTrans()
TRY
{
  return CGridTransformationFactory<CScalar>::registerTransformation(TRANS_REDUCE_SCALAR_TO_SCALAR, create);
}
CATCH

CScalarAlgorithmReduceScalar::CScalarAlgorithmReduceScalar(CScalar* scalarDestination, CScalar* scalarSource, CReduceScalarToScalar* algo)
 : CScalarAlgorithmTransformation(scalarDestination, scalarSource),
   reduction_(0)
TRY
{
  eliminateRedondantSrc_= false ;
  if (algo->operation.isEmpty())
    ERROR("CScalarAlgorithmReduceScalar::CScalarAlgorithmReduceScalar(CScalar* scalarDestination, CScalar* scalarSource, CReduceScalarToScalar* algo)",
           << "Operation must be defined."
           << "Scalar source " <<scalarSource->getId() << std::endl
           << "Scalar destination " << scalarDestination->getId());
  StdString op;
  switch (algo->operation)
  {
    case CReduceScalarToScalar::operation_attr::sum:
      op = "sum";
      break;
    case CReduceScalarToScalar::operation_attr::min:
      op = "min";
      break;
    case CReduceScalarToScalar::operation_attr::max:
      op = "max";
      break;
    case CReduceScalarToScalar::operation_attr::average:
      op = "average";
      break;
    default:
        ERROR("CScalarAlgorithmReduceScalar::CScalarAlgorithmReduceScalar(CScalar* scalarDestination, CScalar* scalarSource, CReduceScalarToScalar* algo)",
         << "Operation is wrongly defined. Supported operations: sum, min, max, average." << std::endl
         << "Scalar source " <<scalarSource->getId() << std::endl
         << "Scalar destination " << scalarDestination->getId());

  }
  
  if (CReductionAlgorithm::ReductionOperations.end() == CReductionAlgorithm::ReductionOperations.find(op))
    ERROR("CScalarAlgorithmReduceScalar::CScalarAlgorithmReduceScalar(CScalar* scalarDestination, CScalar* scalarSource, CReduceScalarToScalar* algo)",
       << "Operation '" << op << "' not found. Please make sure to use a supported one"
       << "Scalar source " <<scalarSource->getId() << std::endl
       << "Scalar destination " << scalarDestination->getId());

  reduction_ = CReductionAlgorithm::createOperation(CReductionAlgorithm::ReductionOperations[op]);
}
CATCH

void CScalarAlgorithmReduceScalar::apply(const std::vector<std::pair<int,double> >& localIndex, const double* dataInput, CArray<double,1>& dataOut,
                                         std::vector<bool>& flagInitial, bool ignoreMissingValue, bool firstPass)
TRY
{
  reduction_->apply(localIndex, dataInput, dataOut, flagInitial, ignoreMissingValue, firstPass);
}
CATCH

void CScalarAlgorithmReduceScalar::updateData(CArray<double,1>& dataOut)
TRY
{
  reduction_->updateData(dataOut);
}
CATCH

CScalarAlgorithmReduceScalar::~CScalarAlgorithmReduceScalar()
TRY
{
  if (0 != reduction_) delete reduction_;
}
CATCH

void CScalarAlgorithmReduceScalar::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  transMap[0].push_back(0);
  transWeight[0].push_back(1.0);

}
CATCH

}
