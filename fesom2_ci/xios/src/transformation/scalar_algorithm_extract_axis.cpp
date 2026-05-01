/*!
   \file scalar_algorithm_extract_scalar.cpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Algorithm for extract an axis to a scalar
 */
#include "scalar_algorithm_extract_axis.hpp"
#include "axis.hpp"
#include "scalar.hpp"
#include "extract_axis_to_scalar.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"

#include "reduction.hpp"

namespace xios {
CGenericAlgorithmTransformation* CScalarAlgorithmExtractAxis::create(CGrid* gridDst, CGrid* gridSrc,
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

  CExtractAxisToScalar* extractAxis = dynamic_cast<CExtractAxisToScalar*> (transformation);
  int scalarDstIndex = elementPositionInGridDst2ScalarPosition[elementPositionInGrid];
  int axisSrcIndex = elementPositionInGridSrc2AxisPosition[elementPositionInGrid];

  return (new CScalarAlgorithmExtractAxis(scalarListDestP[scalarDstIndex], axisListSrcP[axisSrcIndex], extractAxis));
}
CATCH

bool CScalarAlgorithmExtractAxis::registerTrans()
TRY
{
  return CGridTransformationFactory<CScalar>::registerTransformation(TRANS_EXTRACT_AXIS_TO_SCALAR, create);
}
CATCH

CScalarAlgorithmExtractAxis::CScalarAlgorithmExtractAxis(CScalar* scalarDestination, CAxis* axisSource, CExtractAxisToScalar* algo)
 : CScalarAlgorithmTransformation(scalarDestination, axisSource),
   reduction_(0)
TRY
{
  algo->checkValid(scalarDestination, axisSource);
  StdString op = "extract";
  pos_ = algo->position;
  reduction_ = CReductionAlgorithm::createOperation(CReductionAlgorithm::ReductionOperations[op]);
}
CATCH

void CScalarAlgorithmExtractAxis::apply(const std::vector<std::pair<int,double> >& localIndex,
                                         const double* dataInput,
                                         CArray<double,1>& dataOut,
                                         std::vector<bool>& flagInitial,                     
                                         bool ignoreMissingValue, bool firstPass)
TRY
{
  reduction_->apply(localIndex, dataInput, dataOut, flagInitial, ignoreMissingValue, firstPass);
}
CATCH

CScalarAlgorithmExtractAxis::~CScalarAlgorithmExtractAxis()
TRY
{
  if (0 != reduction_) delete reduction_;
}
CATCH

void CScalarAlgorithmExtractAxis::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  transMap[0].push_back(pos_);
  transWeight[0].push_back(1.0);
}
CATCH

}
