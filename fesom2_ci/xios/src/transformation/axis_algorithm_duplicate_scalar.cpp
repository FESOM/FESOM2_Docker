/*!
   \file axis_algorithm_duplicate_scalar.cpp

   \brief Algorithm to duplicate scalar into  axis 
 */
#include "axis_algorithm_duplicate_scalar.hpp"
#include "duplicate_scalar_to_axis.hpp"
#include "axis.hpp"
#include "scalar.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"

namespace xios {
CGenericAlgorithmTransformation* CAxisAlgorithmDuplicateScalar::create(CGrid* gridDst, CGrid* gridSrc,
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
  std::vector<CScalar*> scalarListSrcP = gridSrc->getScalars();

  CDuplicateScalarToAxis* duplicateScalar = dynamic_cast<CDuplicateScalarToAxis*> (transformation);
  int axisDstIndex = elementPositionInGridDst2AxisPosition[elementPositionInGrid];
  int scalarSrcIndex = elementPositionInGridSrc2ScalarPosition[elementPositionInGrid];

  return (new CAxisAlgorithmDuplicateScalar(axisListDestP[axisDstIndex], scalarListSrcP[scalarSrcIndex], duplicateScalar));
}
CATCH

bool CAxisAlgorithmDuplicateScalar::registerTrans()
TRY
{
  return CGridTransformationFactory<CAxis>::registerTransformation(TRANS_DUPLICATE_SCALAR_TO_AXIS, create);
}
CATCH


CAxisAlgorithmDuplicateScalar::CAxisAlgorithmDuplicateScalar(CAxis* axisDestination, CScalar* scalarSource, CDuplicateScalarToAxis* algo)
 : CAxisAlgorithmTransformation(axisDestination, scalarSource)
{

}


CAxisAlgorithmDuplicateScalar::~CAxisAlgorithmDuplicateScalar()
{
}

void CAxisAlgorithmDuplicateScalar::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
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
    transMap[globalAxisIdx][0] = 0 ;
    transWeight[globalAxisIdx][0] = 1.0 ;
  }
}
CATCH
}
