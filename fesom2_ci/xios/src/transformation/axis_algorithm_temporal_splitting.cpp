/*!
   \file axis_algorithm_temporal_splitting.cpp

   \brief Algorithm to split scalar into  axis by temporal accumulation
 */
#include "axis_algorithm_temporal_splitting.hpp"
#include "temporal_splitting.hpp"
#include "axis.hpp"
#include "scalar.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"

namespace xios {
CGenericAlgorithmTransformation* CAxisAlgorithmTemporalSplitting::create(CGrid* gridDst, CGrid* gridSrc,
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

  CTemporalSplitting* temporalSplitting = dynamic_cast<CTemporalSplitting*> (transformation);
  int axisDstIndex = elementPositionInGridDst2AxisPosition[elementPositionInGrid];
  int scalarSrcIndex = elementPositionInGridSrc2ScalarPosition[elementPositionInGrid];

  return (new CAxisAlgorithmTemporalSplitting(axisListDestP[axisDstIndex], scalarListSrcP[scalarSrcIndex], temporalSplitting));
}
CATCH

bool CAxisAlgorithmTemporalSplitting::registerTrans()
TRY
{
  return CGridTransformationFactory<CAxis>::registerTransformation(TRANS_TEMPORAL_SPLITTING, create);
}
CATCH

CAxisAlgorithmTemporalSplitting::CAxisAlgorithmTemporalSplitting(CAxis* axisDestination, CScalar* scalarSource, CTemporalSplitting* algo)
 : CAxisAlgorithmTransformation(axisDestination, scalarSource)
{

}


CAxisAlgorithmTemporalSplitting::~CAxisAlgorithmTemporalSplitting()
{
}

void CAxisAlgorithmTemporalSplitting::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
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
    if (idxAxis==0)
    {
      transMap[globalAxisIdx].resize(1);
      transWeight[globalAxisIdx].resize(1);
      transMap[globalAxisIdx][0] = 0 ;
      transWeight[globalAxisIdx][0] = 1.0 ;
    }
  }
}
CATCH

}
