/*!
   \file domain_algorithm_reorder.cpp
   \brief Algorithm for reorder a domain.
 */
#include "domain_algorithm_reorder.hpp"
#include "reorder_domain.hpp"
#include "domain.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"

namespace xios {
CGenericAlgorithmTransformation* CDomainAlgorithmReorder::create(CGrid* gridDst, CGrid* gridSrc,
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

  CReorderDomain* reorderDomain = dynamic_cast<CReorderDomain*> (transformation);
  int domainDstIndex = elementPositionInGridDst2DomainPosition[elementPositionInGrid];
  int domainSrcIndex = elementPositionInGridSrc2DomainPosition[elementPositionInGrid];

  return (new CDomainAlgorithmReorder(domainListDestP[domainDstIndex], domainListSrcP[domainSrcIndex], reorderDomain));
}
CATCH

bool CDomainAlgorithmReorder::registerTrans()
TRY
{
  return CGridTransformationFactory<CDomain>::registerTransformation(TRANS_REORDER_DOMAIN, create);
}
CATCH

CDomainAlgorithmReorder::CDomainAlgorithmReorder(CDomain* domainDestination, CDomain* domainSource, CReorderDomain* reorderDomain)
: CDomainAlgorithmTransformation(domainDestination, domainSource)
TRY
{
  reorderDomain->checkValid(domainSource);
  if (domainDestination->type !=  CDomain::type_attr::rectilinear)
  {
      ERROR("CDomainAlgorithmReorder::CDomainAlgorithmReorder(CDomain* domainDestination, CDomain* domainSource, CReorderDomain* reorderDomain)",
           << "Domain destination is not rectilinear. This filter work only for rectilinear domain and destination domain with < id = "
           <<domainDestination->getId() <<" > is of type "<<domainDestination->type<<std::endl);
  }
  
  if (domainDestination == domainSource)
  {
    ERROR("CDomainAlgorithmReorder::CDomainAlgorithmReorder(CDomain* domainDestination, CDomain* domainSource, CReorderDomain* reorderDomain)",
           << "Domain source and domain destination are the same. Please make sure domain destination refers to domain source" << std::endl
           << "Domain source " <<domainSource->getId() << std::endl
           << "Domain destination " <<domainDestination->getId() << std::endl);
  }
  this->type_ = (ELEMENT_MODIFICATION_WITHOUT_DATA);

  if (!reorderDomain->invert_lat.isEmpty())
  {
    CArray<int,1>& j_index=domainDestination->j_index ;
    int nglo = j_index.numElements() ;
    int nj_glo =domainDestination->nj_glo ;
    
    for (size_t i = 0; i < nglo ; ++i)
    {
      j_index(i)=(nj_glo-1)-j_index(i) ;
    }
  }

  if (!reorderDomain->shift_lon_fraction.isEmpty())
  {
    int ni_glo =domainDestination->ni_glo ;
    int  offset = ni_glo*reorderDomain->shift_lon_fraction ;
    CArray<int,1>& i_index=domainDestination->i_index ;
    int nglo = i_index.numElements() ;
    
    for (size_t i = 0; i < nglo ; ++i)
    {
      i_index(i)=  (i_index(i)+offset+ni_glo)%ni_glo ;
    }
  }

  if (!reorderDomain->min_lon.isEmpty() && !reorderDomain->max_lon.isEmpty())
  {
    double min_lon=reorderDomain->min_lon ;
    double max_lon=reorderDomain->max_lon ;
    double delta=max_lon-min_lon ;
    
    if (!domainDestination->lonvalue_1d.isEmpty() )
    {
      CArray<double,1>& lon=domainDestination->lonvalue_1d ;
      for (int i=0;i<lon.numElements();++i)
      {
        while  (lon(i) > max_lon) lon(i)=lon(i)-delta ;
        while  (lon(i) < min_lon) lon(i)=lon(i)+delta ;
      }
    }

    if (!domainDestination->bounds_lon_1d.isEmpty() )
    {
      CArray<double,2>& bounds_lon=domainDestination->bounds_lon_1d ;
      for (int i=0;i<bounds_lon.extent(0);++i)
      {
        while  (bounds_lon(0,i) > max_lon) bounds_lon(0,i)=bounds_lon(0,i)-delta ;
        while  (bounds_lon(1,i) > max_lon) bounds_lon(1,i)=bounds_lon(1,i)-delta ;

        while  (bounds_lon(0,i) < min_lon) bounds_lon(0,i)=bounds_lon(0,i)+delta ;
        while  (bounds_lon(1,i) < min_lon) bounds_lon(1,i)=bounds_lon(1,i)+delta ;
      }
    }
  }
}
CATCH

/*!
  Compute the index mapping between domain on grid source and one on grid destination
*/
void CDomainAlgorithmReorder::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
/*
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];
*/
}


}
