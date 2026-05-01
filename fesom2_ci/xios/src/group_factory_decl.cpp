#include "group_factory_impl.hpp"
#include "node_type.hpp"

namespace xios
{
# define  macro(U) \
  template void CGroupFactory::AddGroup<U>(std::shared_ptr<U> pgroup, std::shared_ptr<U> cgroup); \
  template void CGroupFactory::AddChild<U>(std::shared_ptr<U> group, std::shared_ptr<U::RelChild> child); \
  template std::shared_ptr<U>  CGroupFactory::GetGroup<U>(std::shared_ptr<U> group, const StdString & id); \
  template std::shared_ptr<U::RelChild> CGroupFactory::GetChild<U>( std::shared_ptr<U> group, const StdString & id); \
  template int CGroupFactory::GetGroupNum<U>(std::shared_ptr<U> group); \
  template int CGroupFactory::GetGroupIdNum<U>(std::shared_ptr<U> group); \
  template int CGroupFactory::GetChildNum<U>(std::shared_ptr<U> group); \
  template int CGroupFactory::GetChildIdNum<U>(std::shared_ptr<U> group); \
  template bool CGroupFactory::HasGroup<U>(std::shared_ptr<U> group, const StdString & id); \
  template bool CGroupFactory::HasChild<U>(std::shared_ptr<U> group, const StdString & id); \
  template std::shared_ptr<U> CGroupFactory::CreateGroup<U>(std::shared_ptr<U> group, const StdString & id ); \
  template std::shared_ptr<U::RelChild>  CGroupFactory::CreateChild<U>(std::shared_ptr<U> group, const StdString & id);

  macro(CFieldGroup)
  macro(CFileGroup)
  macro(CGridGroup)
  macro(CAxisGroup)
  macro(CDomainGroup)
  macro(CContextGroup)
  macro(CVariableGroup)
  macro(CInverseAxisGroup)
  macro(CZoomAxisGroup)
  macro(CInterpolateAxisGroup)
  macro(CExtractAxisGroup)
  macro(CZoomDomainGroup)
  macro(CInterpolateDomainGroup)
  macro(CGenerateRectilinearDomainGroup)
  macro(CScalarGroup)
  macro(CReduceAxisToScalarGroup)
  macro(CReduceDomainToAxisGroup)
  macro(CReduceAxisToAxisGroup)
  macro(CExtractDomainToAxisGroup)
  macro(CComputeConnectivityDomainGroup)
  macro(CExpandDomainGroup)
  macro(CExtractAxisToScalarGroup)
  macro(CReduceDomainToScalarGroup)
  macro(CTemporalSplittingGroup)
  macro(CDuplicateScalarToAxisGroup)
  macro(CReduceScalarToScalarGroup)
  macro(CReorderDomainGroup)
  macro(CExtractDomainGroup)
}
