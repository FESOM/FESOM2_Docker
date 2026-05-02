/*!
   \file axis_algorithm_extract.cpp
   \brief Algorithm for extracting an axis.
 */
#include "axis_algorithm_extract.hpp"
#include "axis.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "extract_axis.hpp"

namespace xios {
CGenericAlgorithmTransformation* CAxisAlgorithmExtract::create(CGrid* gridDst, CGrid* gridSrc,
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

  CExtractAxis* extractAxis = dynamic_cast<CExtractAxis*> (transformation);
  int axisDstIndex = elementPositionInGridDst2AxisPosition[elementPositionInGrid];
  int axisSrcIndex = elementPositionInGridSrc2AxisPosition[elementPositionInGrid];

  return (new CAxisAlgorithmExtract(axisListDestP[axisDstIndex], axisListSrcP[axisSrcIndex], extractAxis));
}
CATCH

bool CAxisAlgorithmExtract::registerTrans()
TRY
{
  return CGridTransformationFactory<CAxis>::registerTransformation(TRANS_EXTRACT_AXIS, create);
}
CATCH

CAxisAlgorithmExtract::CAxisAlgorithmExtract(CAxis* axisDestination, CAxis* axisSource, CExtractAxis* extractAxis)
: CAxisAlgorithmTransformation(axisDestination, axisSource)
TRY
{
  extractAxis->checkValid(axisSource);
  extractBegin_ = extractAxis->begin.getValue();
  extractN_  = extractAxis->n.getValue();
  extractEnd_   = extractBegin_ + extractN_ - 1;

  if (extractN_ > axisSource->n_glo.getValue())
  {
    ERROR("CAxisAlgorithmExtract::CAxisAlgorithmExtract(CAxis* axisDestination, CAxis* axisSource, CExtractAxis* extractAxis)",
           << "Extract size is greater than global size of source axis"
           << "Global size of source axis " <<axisSource->getId() << " is " << axisSource->n_glo.getValue()  << std::endl
           << "Extract size is " << extractN_ );
  }

  int idxSrc, nDest = 0, beginDestLoc, beginDestGlo = 0 ;
  int indGloDest, indGloSrc, iSrc;
  for (int i = 0; i < axisSrc_->n.getValue(); i++)
  {
    idxSrc = axisSrc_->index(i);
    if ((idxSrc >= extractBegin_) && (idxSrc <= extractEnd_))
    {
      if (nDest == 0) beginDestLoc = i;
      ++nDest;
    }
  }
  beginDestGlo = beginDestLoc + axisSrc_->begin - extractBegin_;
  axisDest_->n_glo.setValue(extractN_);
  axisDest_->n.setValue(nDest);
  axisDest_->begin.setValue(beginDestGlo);
  axisDest_->index.resize(nDest);

  axisDest_->data_n.setValue(nDest);
  axisDest_->data_begin.setValue(0);
  axisDest_->data_index.resize(nDest);

  axisDest_->mask.resize(nDest);
  if (axisSrc_->hasValue) axisDest_->value.resize(nDest);
  if (axisSrc_->hasLabel) axisDest_->label.resize(nDest);
  if (axisSrc_->hasBounds) axisDest_->bounds.resize(2,nDest);

  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);
  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  for (int iDest = 0; iDest < nDest; iDest++)
  {
    iSrc = iDest + beginDestLoc;
    axisDest_->index(iDest) = iDest + beginDestGlo;
    axisDest_->data_index(iDest) = axisSrc_->data_index(iSrc) - beginDestLoc;
    axisDest_->mask(iDest) = axisSrc_->mask(iSrc);

    if (axisSrc_->hasValue)
      axisDest_->value(iDest) = axisSrc_->value(iSrc);
    if (axisSrc_->hasLabel)
      axisDest_->label(iDest) = axisSrc_->label(iSrc);
    if (axisSrc_->hasBounds)
    {
      axisDest_->bounds(0,iDest) = axisSrc_->bounds(0,iSrc);
      axisDest_->bounds(1,iDest) = axisSrc_->bounds(1,iSrc);
    }
    indGloDest = axisDest_->index(iDest);
    indGloSrc = axisSrc_->index(iSrc);
    transMap[indGloDest].push_back(indGloSrc);
    transWeight[indGloDest].push_back(1.0);

  }
}
CATCH

/*!
  Compute the index mapping between domain on grid source and one on grid destination
*/
void CAxisAlgorithmExtract::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
}

}
