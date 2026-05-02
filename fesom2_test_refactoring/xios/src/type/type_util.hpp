#ifndef __TYPE_UTIL_HPP__
#define __TYPE_UTIL_HPP__

#include <string>
namespace xios
{
    class CDomain;
    class CDomainGroup;
    class CField;
    class CFieldGroup;
    class CGrid;
    class CGridGroup;
    class CAxis;
    class CAxisGroup;
    class CFile;
    class CFileGroup;
    class CContext;
    class CContextGroup;
    class CCalendarWrapper;
    class CVariable;
    class CVariableGroup;
    class CInverseAxis;
    class CInverseAxisGroup;
    class CZoomAxis;
    class CZoomAxisGroup;
    class CInterpolateAxis;
    class CInterpolateAxisGroup;
    class CExtractAxis;
    class CExtractAxisGroup;
    class CZoomDomain;
    class CZoomDomainGroup;
    class CInterpolateDomain;
    class CInterpolateDomainGroup;
    class CGenerateRectilinearDomain;
    class CGenerateRectilinearDomainGroup;
    class CScalar;
    class CScalarGroup;
    class CReduceAxisToScalar;
    class CReduceAxisToScalarGroup;
    class CReduceDomainToAxis;
    class CReduceDomainToAxisGroup;
    class CReduceAxisToAxis;
    class CReduceAxisToAxisGroup;
    class CExtractDomainToAxis;
    class CExtractDomainToAxisGroup;
    class CComputeConnectivityDomain;
    class CComputeConnectivityDomainGroup;
    class CExpandDomain;
    class CExpandDomainGroup;
    class CExtractAxisToScalar;
    class CExtractAxisToScalarGroup;
    class CReduceDomainToScalar;
    class CReduceDomainToScalarGroup;
    class CTemporalSplitting;
    class CTemporalSplittingGroup;
    class CDuplicateScalarToAxis;
    class CDuplicateScalarToAxisGroup;
    class CReduceScalarToScalar;
    class CReduceScalarToScalarGroup;
    class CReorderDomain;
    class CReorderDomainGroup;
    class CExtractDomain;
    class CExtractDomainGroup;
     
  template <typename T> inline string getStrType(void);

#define macro(T) template <> inline string getStrType<T>(void) { return std::string(#T); }

  macro(short)
  macro(unsigned short)
  macro(int)
  macro(unsigned int)
  macro(long)
  macro(unsigned long)
  macro(float)
  macro(double)
  macro(long double)
  macro(char)
  macro(unsigned char)
  macro(wchar_t)
  macro(bool)
#undef macro

#define macro(T) template <> inline string getStrType<T>(void) { return std::string(#T); }
  macro(CDomain)
  macro(CDomainGroup)
  macro(CField)
  macro(CFieldGroup)
  macro(CGrid)
  macro(CGridGroup)
  macro(CAxis)
  macro(CAxisGroup)
  macro(CFile)
  macro(CFileGroup)
  macro(CContext)
  macro(CContextGroup)
  macro(CCalendarWrapper)
  macro(CVariable)
  macro(CVariableGroup)
  macro(CInverseAxis)
  macro(CInverseAxisGroup)
  macro(CZoomAxis)
  macro(CZoomAxisGroup)
  macro(CInterpolateAxis)
  macro(CInterpolateAxisGroup)
  macro(CExtractAxis)
  macro(CExtractAxisGroup)
  macro(CZoomDomain)
  macro(CZoomDomainGroup)
  macro(CInterpolateDomain)
  macro(CInterpolateDomainGroup)
  macro(CGenerateRectilinearDomain)
  macro(CGenerateRectilinearDomainGroup)
  macro(CScalar)
  macro(CScalarGroup)
  macro(CReduceAxisToScalar)
  macro(CReduceAxisToScalarGroup)
  macro(CReduceDomainToAxis)
  macro(CReduceDomainToAxisGroup)
  macro(CReduceAxisToAxis)
  macro(CReduceAxisToAxisGroup)
  macro(CExtractDomainToAxis)
  macro(CExtractDomainToAxisGroup)
  macro(CComputeConnectivityDomain)
  macro(CComputeConnectivityDomainGroup)
  macro(CExpandDomain)
  macro(CExpandDomainGroup)
  macro(CExtractAxisToScalar)
  macro(CExtractAxisToScalarGroup)
  macro(CReduceDomainToScalar)
  macro(CReduceDomainToScalarGroup)
  macro(CTemporalSplitting)
  macro(CTemporalSplittingGroup)
  macro(CDuplicateScalarToAxis)
  macro(CDuplicateScalarToAxisGroup)
  macro(CReduceScalarToScalar)
  macro(CReduceScalarToScalarGroup)
  macro(CReorderDomain)
  macro(CReorderDomainGroup)
  macro(CExtractDomain)
  macro(CExtractDomainGroup)
  
#undef macro
}


#endif
