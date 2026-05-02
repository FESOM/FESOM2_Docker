/*!
   \file axis_algorithm_zoom.cpp
   \brief Algorithm for zooming an axis.
 */
#include "axis_algorithm_zoom.hpp"
#include "axis.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "zoom_axis.hpp"

namespace xios {
CGenericAlgorithmTransformation* CAxisAlgorithmZoom::create(CGrid* gridDst, CGrid* gridSrc,
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

  CZoomAxis* zoomAxis = dynamic_cast<CZoomAxis*> (transformation);
  int axisDstIndex = elementPositionInGridDst2AxisPosition[elementPositionInGrid];
  int axisSrcIndex = elementPositionInGridSrc2AxisPosition[elementPositionInGrid];

  return (new CAxisAlgorithmZoom(axisListDestP[axisDstIndex], axisListSrcP[axisSrcIndex], zoomAxis));
}
CATCH

bool CAxisAlgorithmZoom::registerTrans()
TRY
{
  return CGridTransformationFactory<CAxis>::registerTransformation(TRANS_ZOOM_AXIS, create);
}
CATCH

CAxisAlgorithmZoom::CAxisAlgorithmZoom(CAxis* axisDestination, CAxis* axisSource, CZoomAxis* zoomAxis)
: CAxisAlgorithmTransformation(axisDestination, axisSource)
TRY
{
  zoomAxis->checkValid(axisSource);
  zoomBegin_ = zoomAxis->begin.getValue();
  zoomN_  = zoomAxis->n.getValue();
  zoomEnd_   = zoomBegin_ + zoomN_ - 1;

  if (zoomN_ > axisSource->n_glo.getValue())
  {
    ERROR("CAxisAlgorithmZoom::CAxisAlgorithmZoom(CAxis* axisDestination, CAxis* axisSource, CZoomAxis* zoomAxis)",
           << "Zoom size is greater than global size of source axis"
           << "Global size of source axis " <<axisSource->getId() << " is " << axisSource->n_glo.getValue()  << std::endl
           << "Zoom size is " << zoomN_ );
  }

  int idxSrc, nDest = 0, beginDestLoc, beginDestGlo = 0 ;
  int indGloDest, indGloSrc, iSrc;
  for (int i = 0; i < axisSrc_->n.getValue(); i++)
  {
    idxSrc = axisSrc_->index(i);
    if ((idxSrc >= zoomBegin_) && (idxSrc <= zoomEnd_))
    {
      if (nDest == 0) beginDestLoc = i;
      ++nDest;
    }
  }
  beginDestGlo = beginDestLoc + axisSrc_->begin - zoomBegin_;
  axisDest_->n_glo.setValue(zoomN_);
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
void CAxisAlgorithmZoom::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
}

}
