#include "domain_algorithm_zoom.hpp"
#include "zoom_domain.hpp"
#include "domain.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "attribute_template.hpp"

namespace xios {
CGenericAlgorithmTransformation* CDomainAlgorithmZoom::create(CGrid* gridDst, CGrid* gridSrc,
                                                             CTransformation<CDomain>* transformation,
                                                             int elementPositionInGrid,
                                                             std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                             std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                             std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                             std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                             std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                             std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CDomain*> domainListDestP = gridDst->getDomains();
  std::vector<CDomain*> domainListSrcP  = gridSrc->getDomains();

  CZoomDomain* zoomDomain = dynamic_cast<CZoomDomain*> (transformation);
  int domainDstIndex = elementPositionInGridDst2DomainPosition[elementPositionInGrid];
  int domainSrcIndex = elementPositionInGridSrc2DomainPosition[elementPositionInGrid];

  return (new CDomainAlgorithmZoom(domainListDestP[domainDstIndex], domainListSrcP[domainSrcIndex], zoomDomain));
}
CATCH

bool CDomainAlgorithmZoom::registerTrans()
TRY
{
  return CGridTransformationFactory<CDomain>::registerTransformation(TRANS_ZOOM_DOMAIN, create);
}
CATCH

CDomainAlgorithmZoom::CDomainAlgorithmZoom(CDomain* domainDestination, CDomain* domainSource, CZoomDomain* zoomDomain)
: CDomainAlgorithmTransformation(domainDestination, domainSource)
TRY
{
  zoomDomain->checkValid(domainSource);
  zoomIBegin_ = zoomDomain->ibegin.getValue();
  zoomJBegin_ = zoomDomain->jbegin.getValue();

  zoomNi_  = zoomDomain->ni.getValue();
  zoomNj_  = zoomDomain->nj.getValue();

  zoomIEnd_ = zoomIBegin_ + zoomNi_ - 1;
  zoomJEnd_ = zoomJBegin_ + zoomNj_ - 1;

  if (zoomNi_ > domainSource->ni_glo.getValue())
  {
    ERROR("CDomainAlgorithmZoom::CDomainAlgorithmZoom(CDomain* domainDestination, CDomain* domainSource, CZoomDomain* zoomDomain)",
           << "Zoom size is greater than size of domain source"
           << "Size ni_glo of domain source " <<domainSource->getId() << " is " << domainSource->ni_glo.getValue()  << std::endl
           << "Zoom size is " << zoomNi_ );
  }

  if (zoomNj_ > domainSource->nj_glo.getValue())
  {
    ERROR("CDomainAlgorithmZoom::CDomainAlgorithmZoom(CDomain* domainDestination, CDomain* domainSource, CZoomDomain* zoomDomain)",
           << "Zoom size is greater than size of domain source"
           << "Size nj_glo of domain source " <<domainSource->getId() << " is " << domainSource->nj_glo.getValue()  << std::endl
           << "Zoom size is " << zoomNj_ );
  }

  // Calculate the size of local domain
  int ind, indLocSrc, indLocDest, iIdxSrc, jIdxSrc, destIBegin = -1, destJBegin = -1, niDest = 0, njDest = 0, ibeginDest, jbeginDest ;
  int indGloDest, indGloSrc, niGloSrc = domainSrc_->ni_glo, iSrc, jSrc, nvertex = 0;
  for (int j = 0; j < domainSrc_->nj.getValue(); j++)
  {
    for (int i = 0; i < domainSrc_->ni.getValue(); i++)
    {
      ind = j*domainSrc_->ni + i;
      iIdxSrc = domainSrc_->i_index(ind);
      if ((iIdxSrc >= zoomIBegin_) && (iIdxSrc <= zoomIEnd_))
      {
        jIdxSrc = domainSrc_->j_index(ind);
        if ((jIdxSrc >= zoomJBegin_) && (jIdxSrc <= zoomJEnd_))
        {
          if ((niDest == 0) && (njDest == 0))
          {
            destIBegin = i;
            destJBegin = j;
          }
          if (i == destIBegin) ++njDest;
        }
        if (j == destJBegin) ++niDest;

      }
    }
  }
  ibeginDest = destIBegin + domainSrc_->ibegin - zoomIBegin_;
  jbeginDest = destJBegin + domainSrc_->jbegin - zoomJBegin_;
  domainDest_->ni_glo.setValue(zoomNi_);
  domainDest_->nj_glo.setValue(zoomNj_);
  domainDest_->ni.setValue(niDest);
  domainDest_->nj.setValue(njDest);
  if ( (niDest==0) || (njDest==0))
  {
    domainDest_->ibegin.setValue(0);
    domainDest_->jbegin.setValue(0);
  }
  else
  {
    domainDest_->ibegin.setValue(ibeginDest);
    domainDest_->jbegin.setValue(jbeginDest);
  }
  domainDest_->i_index.resize(niDest*njDest);
  domainDest_->j_index.resize(niDest*njDest);

  domainDest_->data_ni.setValue(niDest);
  domainDest_->data_nj.setValue(njDest);
  domainDest_->data_ibegin.setValue(0);
  domainDest_->data_jbegin.setValue(0);
  domainDest_->data_i_index.resize(niDest*njDest);
  domainDest_->data_j_index.resize(niDest*njDest);

  domainDest_->domainMask.resize(niDest*njDest);

  if (!domainSrc_->lonvalue_1d.isEmpty())
  {
    if (domainDest_->type == CDomain::type_attr::rectilinear)
    {
      domainDest_->lonvalue_1d.resize(niDest);
      domainDest_->latvalue_1d.resize(njDest);
    }
    else if (domainDest_->type == CDomain::type_attr::unstructured)
    {
      domainDest_->lonvalue_1d.resize(niDest);
      domainDest_->latvalue_1d.resize(niDest);
    }
    else if (domainDest_->type == CDomain::type_attr::curvilinear)
    {
      domainDest_->lonvalue_1d.resize(niDest*njDest);
      domainDest_->latvalue_1d.resize(niDest*njDest);
    }
  }
  else if (!domainSrc_->lonvalue_2d.isEmpty())
  {
    domainDest_->lonvalue_2d.resize(niDest,njDest);
    domainDest_->latvalue_2d.resize(niDest,njDest);
  }

  if (domainSrc_->hasBounds)
  {
    nvertex = domainSrc_->nvertex;
    domainDest_->nvertex.setValue(nvertex);
    if (!domainSrc_->bounds_lon_1d.isEmpty())
    {
      if (domainDest_->type == CDomain::type_attr::rectilinear)
      {
        domainDest_->bounds_lon_1d.resize(nvertex, niDest);
        domainDest_->bounds_lat_1d.resize(nvertex, njDest);
      }
      else if (domainDest_->type == CDomain::type_attr::unstructured)
      {
        domainDest_->bounds_lon_1d.resize(nvertex, niDest);
        domainDest_->bounds_lat_1d.resize(nvertex, niDest);
      }
      else if (domainDest_->type == CDomain::type_attr::curvilinear)
      {
        domainDest_->bounds_lon_1d.resize(nvertex, niDest*njDest);
        domainDest_->bounds_lat_1d.resize(nvertex, niDest*njDest);
      }
    }
    else if (!domainSrc_->bounds_lon_2d.isEmpty())
    {
      domainDest_->bounds_lon_2d.resize(nvertex, niDest, njDest);
      domainDest_->bounds_lat_2d.resize(nvertex, niDest, njDest);
    }
  }
  if (domainSrc_->hasArea) domainDest_->area.resize(niDest,njDest);

  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);
  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  for (int iDest = 0; iDest < niDest; iDest++)
  {
    iSrc = iDest + destIBegin;
    for (int jDest = 0; jDest < njDest; jDest++)
    {
      jSrc = jDest + destJBegin;
      ind = jSrc * domainSrc_->ni + iSrc;
      iIdxSrc = domainSrc_->i_index(ind);
      jIdxSrc = domainSrc_->j_index(ind);
      indLocDest = jDest*niDest + iDest;
      indGloDest = (jDest + jbeginDest)*zoomNi_ + (iDest + ibeginDest);
      indLocSrc = (jDest+destJBegin)*domainSrc_->ni + (iDest+destIBegin);
      indGloSrc = (jIdxSrc )* niGloSrc + iIdxSrc;
      domainDest_->i_index(indLocDest) = iDest + ibeginDest;                                             // i_index contains global positions
      domainDest_->j_index(indLocDest) = jDest + jbeginDest;                                             // i_index contains global positions
      domainDest_->data_i_index(indLocDest) = (domainSrc_->data_dim == 1) ? indLocDest : iDest;          // data_i_index contains local positions
      domainDest_->data_j_index(indLocDest) = (domainSrc_->data_dim == 1) ? 0 :jDest;                    // data_i_index contains local positions
      domainDest_->domainMask(indLocDest) = domainSrc_->domainMask(indLocSrc);

      if (domainSrc_->hasArea)
        domainDest_->area(iDest,jDest) = domainSrc_->area(iSrc,jSrc);

      if (domainSrc_->hasLonLat)
      {
        if (!domainSrc_->latvalue_1d.isEmpty())
        {
          if (domainDest_->type == CDomain::type_attr::rectilinear)
          {
            domainDest_->latvalue_1d(jDest) = domainSrc_->latvalue_1d(jSrc);
          }
          else
          {
            domainDest_->lonvalue_1d(indLocDest) = domainSrc_->lonvalue_1d(ind);
            domainDest_->latvalue_1d(indLocDest) = domainSrc_->latvalue_1d(ind);
          }
        }
        else if (!domainSrc_->latvalue_2d.isEmpty())
        {
          domainDest_->lonvalue_2d(iDest,jDest) = domainSrc_->lonvalue_2d(iSrc,jSrc);
          domainDest_->latvalue_2d(iDest,jDest) = domainSrc_->latvalue_2d(iSrc,jSrc);
        }
      }

      if (domainSrc_->hasBounds)
      {
        if (!domainSrc_->bounds_lon_1d.isEmpty())
        {
          if (domainDest_->type == CDomain::type_attr::rectilinear)
          {
            for (int n = 0; n < nvertex; ++n)
              domainDest_->bounds_lat_1d(n,jDest) = domainSrc_->bounds_lat_1d(n,jSrc);
          }
          else
          {
            for (int n = 0; n < nvertex; ++n)
            {
              domainDest_->bounds_lon_1d(n,indLocDest) = domainSrc_->bounds_lon_1d(n,ind);
              domainDest_->bounds_lat_1d(n,indLocDest) = domainSrc_->bounds_lat_1d(n,ind);
            }
          }
        }
        else if (!domainSrc_->bounds_lon_2d.isEmpty())
        {
          for (int n = 0; n < nvertex; ++n)
          {
            domainDest_->bounds_lon_2d(n,iDest,jDest) = domainSrc_->bounds_lon_2d(n,iSrc,jSrc);
            domainDest_->bounds_lat_2d(n,iDest,jDest) = domainSrc_->bounds_lat_2d(n,iSrc,jSrc);
          }
        }

      }

      transMap[indGloDest].push_back(indGloSrc);
      transWeight[indGloDest].push_back(1.0);
    }

    if (domainSrc_->hasLonLat && !domainSrc_->latvalue_1d.isEmpty())
    {
      if (domainDest_->type == CDomain::type_attr::rectilinear)
      {
        domainDest_->lonvalue_1d(iDest) = domainSrc_->lonvalue_1d(iSrc);
      }
    }

    if (domainSrc_->hasBounds && !domainSrc_->bounds_lon_1d.isEmpty())
    {
      if (domainDest_->type == CDomain::type_attr::rectilinear)
      {
        for (int n = 0; n < nvertex; ++n)
          domainDest_->bounds_lon_1d(n,iDest) = domainSrc_->bounds_lon_1d(n,iSrc);
      }
    }
  }
  domainDest_->computeLocalMask();
}
CATCH

/*!
  Compute the index mapping between domain on grid source and one on grid destination
*/
void CDomainAlgorithmZoom::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
}


}
