#include "inetcdf4_impl.hpp"

namespace xios
{
# define  macro(type,size) \
  template void CINetCDF4::getData(CArray<type, size>& data, const StdString& var, \
                                   bool collective, StdSize record,                \
                                   const std::vector<StdSize>* start,              \
                                   const std::vector<StdSize>* count);             \

  macro(double, 1)
  macro(double, 2)
  macro(double, 3)
} // namespace xios

