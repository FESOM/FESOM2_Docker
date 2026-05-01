#include "group_template_impl.hpp"
#include "node_type.hpp"

namespace xios
{
#  define macro(T) \
  template class CGroupTemplate<C##T, C##T##Group, C##T##Attributes> ;

  macro(Context)
  macro(Field)
  macro(File)
  macro(Domain)
  macro(Grid)
  macro(Axis)
  macro(Variable)
  macro(InverseAxis)
  macro(ZoomAxis)
  macro(InterpolateAxis)
  macro(ExtractAxis)
  macro(ZoomDomain)
  macro(InterpolateDomain)
  macro(GenerateRectilinearDomain)
  macro(Scalar)
  macro(ReduceAxisToScalar)
  macro(ReduceDomainToAxis)
  macro(ReduceAxisToAxis)
  macro(ExtractDomainToAxis)
  macro(ComputeConnectivityDomain)
  macro(ExpandDomain)
  macro(ExtractAxisToScalar)
  macro(ReduceDomainToScalar)
  macro(TemporalSplitting)
  macro(DuplicateScalarToAxis)
  macro(ReduceScalarToScalar)
  macro(ReorderDomain)
  macro(ExtractDomain)

}
