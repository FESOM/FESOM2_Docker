#include "xml_parser_impl.hpp"
#include "group_template.hpp"
#include "node_type.hpp"

namespace xios
{
  namespace xml
  {
    template void CXMLParser::ParseInclude<CContext>(StdIStream & stream, const string& fluxId, CContext& object) ;

 #   define macro(T) \
    template void CXMLParser::ParseInclude< CGroupTemplate<C##T, C##T##Group, C##T##Attributes> >(StdIStream & stream, const string& fluxId, CGroupTemplate<C##T, C##T##Group, C##T##Attributes>& object) ;

    macro( Context )
    macro( Axis )
    macro( Domain )
    macro( Grid )
    macro( Field )
    macro( File )
    macro( Variable )
    macro( InverseAxis )
    macro( ZoomAxis )
    macro( InterpolateAxis )
    macro( ExtractAxis )
    macro( ZoomDomain )
    macro( InterpolateDomain )
    macro( GenerateRectilinearDomain )
    macro( Scalar )
    macro( ReduceAxisToScalar )
    macro( ReduceDomainToAxis )
    macro( ReduceAxisToAxis )
    macro( ExtractDomainToAxis )
    macro( ComputeConnectivityDomain )
    macro( ExpandDomain )
    macro( ExtractAxisToScalar )
    macro( ReduceDomainToScalar )
    macro( TemporalSplitting )
    macro( DuplicateScalarToAxis )
    macro( ReduceScalarToScalar )
    macro( ReorderDomain )
    macro( ExtractDomain )
  }
}
