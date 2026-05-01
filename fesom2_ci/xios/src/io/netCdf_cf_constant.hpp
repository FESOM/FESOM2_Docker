#ifndef __XIOS_INETCDF4_IMPL__
#define __XIOS_INETCDF4_IMPL__

#include "inetcdf4.hpp"
#include "netCdfInterface.hpp"

namespace xios
{
const StdString CFLatUnits[] = {"degrees_north", "degree_north", "degree_N", "degrees_N", "degreeN", "degreesN"};
const StdString CFLonUnits[] = {"degrees_east", "degree_east", "degree_E", "degrees_E", "degreeE", "degreesE"};

struct CCFKeywords
{
  static const StdString XIOS_CF_units;
  static const StdString XIOS_CF_standard_name;
  static const StdString XIOS_CF_coordinates;
  static const StdString XIOS_CF_bounds;
};
const StdString CCFKeywords::XIOS_CF_units("units");
const StdString CCFKeywords::XIOS_CF_standard_name("standard_name");
const StdString CCFKeywords::XIOS_CF_coordinates("coordinates");
const StdString CCFKeywords::XIOS_CF_bounds("bounds");

struct CCFConvention
{
  static const std::set<StdString> XIOS_CF_Latitude_units;
  static const std::set<StdString> XIOS_CF_Longitude_units;

private:
  CCFConvention();
};

const std::set<StdString> CCFConvention::XIOS_CF_Latitude_units(CFLatUnits, CFLatUnits+sizeof(CFLatUnits)/sizeof(CFLatUnits[0]));
const std::set<StdString> CCFConvention::XIOS_CF_Longitude_units(CFLonUnits, CFLonUnits+sizeof(CFLonUnits)/sizeof(CFLonUnits[0]));

} // namespace xios

#endif //__XIOS_INETCDF4_IMPL__
