#include "object_template_impl.hpp"
#include "xios_spl.hpp"
#include "node_type.hpp"

namespace xios
{
  template class CObjectTemplate<CContext>;
  template class CObjectTemplate<CCalendarWrapper>;
  template class CObjectTemplate<CField>;
  template class CObjectTemplate<CFile>;
  template class CObjectTemplate<CDomain>;
  template class CObjectTemplate<CGrid>;
  template class CObjectTemplate<CAxis>;
  template class CObjectTemplate<CVariable>;
  template class CObjectTemplate<CInverseAxis>;
  template class CObjectTemplate<CZoomAxis>;
  template class CObjectTemplate<CInterpolateAxis>;
  template class CObjectTemplate<CExtractAxis>;
  template class CObjectTemplate<CZoomDomain>;
  template class CObjectTemplate<CInterpolateDomain>;
  template class CObjectTemplate<CGenerateRectilinearDomain>;
  template class CObjectTemplate<CScalar>;
  template class CObjectTemplate<CReduceAxisToScalar>;
  template class CObjectTemplate<CReduceDomainToAxis>;
  template class CObjectTemplate<CReduceAxisToAxis>;
  template class CObjectTemplate<CExtractDomainToAxis>;
  template class CObjectTemplate<CComputeConnectivityDomain>;
  template class CObjectTemplate<CExpandDomain>;
  template class CObjectTemplate<CExtractAxisToScalar>;
  template class CObjectTemplate<CReduceDomainToScalar>;
  template class CObjectTemplate<CTemporalSplitting>;
  template class CObjectTemplate<CDuplicateScalarToAxis>;
  template class CObjectTemplate<CReduceScalarToScalar>;
  template class CObjectTemplate<CReorderDomain>;
  template class CObjectTemplate<CExtractDomain>;
  
  template class CObjectTemplate<CContextGroup>;
  template class CObjectTemplate<CFieldGroup>;
  template class CObjectTemplate<CFileGroup>;
  template class CObjectTemplate<CDomainGroup>;
  template class CObjectTemplate<CGridGroup>;
  template class CObjectTemplate<CAxisGroup>;
  template class CObjectTemplate<CVariableGroup>;
  template class CObjectTemplate<CInverseAxisGroup>;
  template class CObjectTemplate<CZoomAxisGroup>;
  template class CObjectTemplate<CInterpolateAxisGroup>;
  template class CObjectTemplate<CExtractAxisGroup>;
  template class CObjectTemplate<CZoomDomainGroup>;
  template class CObjectTemplate<CInterpolateDomainGroup>;
  template class CObjectTemplate<CGenerateRectilinearDomainGroup>;
  template class CObjectTemplate<CScalarGroup>;
  template class CObjectTemplate<CReduceAxisToScalarGroup>;
  template class CObjectTemplate<CReduceDomainToAxisGroup>;
  template class CObjectTemplate<CReduceAxisToAxisGroup>;
  template class CObjectTemplate<CExtractDomainToAxisGroup>;
  template class CObjectTemplate<CComputeConnectivityDomainGroup>;
  template class CObjectTemplate<CExpandDomainGroup>;
  template class CObjectTemplate<CExtractAxisToScalarGroup>;
  template class CObjectTemplate<CReduceDomainToScalarGroup>;
  template class CObjectTemplate<CTemporalSplittingGroup>;
  template class CObjectTemplate<CDuplicateScalarToAxisGroup>;
  template class CObjectTemplate<CReduceScalarToScalarGroup>;
  template class CObjectTemplate<CReorderDomainGroup>;
  template class CObjectTemplate<CExtractDomainGroup>;
}
