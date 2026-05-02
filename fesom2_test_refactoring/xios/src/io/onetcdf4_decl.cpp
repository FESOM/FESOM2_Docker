#include "onetcdf4_impl.hpp"

namespace xios
{
# define  macro(type,size) \
  template void CONetCDF4::writeData<type,size>(const CArray<type, size>& data, const StdString & name, \
                                               bool collective, StdSize record, \
                                               const std::vector<StdSize> * start, \
                                               const std::vector<StdSize> * count) ;
 
  macro(int, 1)
  macro(int, 2)
  macro(double, 1)
  macro(double, 2)
  macro(double, 3)
  macro(StdString, 1)
 
  template void CONetCDF4::setDefaultValue<double>(const StdString & varname, const double* value) ;
  template void CONetCDF4::setDefaultValue<short>(const StdString & varname, const short* value) ;
  template void CONetCDF4::setDefaultValue<float>(const StdString & varname, const float* value) ;
}
