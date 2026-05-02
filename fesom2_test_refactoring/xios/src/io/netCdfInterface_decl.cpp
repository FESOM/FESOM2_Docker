/*!
   \file netCdfInterface_impl.hpp
   \author Ha NGUYEN
   \date 06 Oct 2014
   \since 06 Oct 2014

   \brief Implemention of some templated functions in netCdfInterface
 */

#include "netCdfInterface_impl.hpp"

namespace xios
{
#define macroAtt(type) \
  template int CNetCdfInterface::getAttType(int ncid, int varid, const StdString& attrName, type* data); \
  template int CNetCdfInterface::putAttType(int ncid, int varid, const StdString& attrName,              \
                                            StdSize numVal, const type* data);

  macroAtt(double)
  macroAtt(float)
  macroAtt(int)
  macroAtt(long)
  macroAtt(short)
  macroAtt(char)

#define macroPutVar(type) \
 template int CNetCdfInterface::getVaraType(int ncid, int varId, const StdSize* start, \
                                            const StdSize* count, type* data);         \
 template int CNetCdfInterface::putVaraType(int ncid, int varId, const StdSize* start, \
                                            const StdSize* count, const type* data);

  macroPutVar(double)
  macroPutVar(float)
  macroPutVar(int)
  macroPutVar(char)
  
#define macroType(type, ncType) \
  template<> nc_type CNetCdfInterface::getNcType<type>() { return ncType; }

  macroType(double, NC_DOUBLE)
  macroType(float, NC_FLOAT)
  macroType(int, NC_INT)
  macroType(long, NC_LONG)
  macroType(short, NC_SHORT)
  macroType(char, NC_CHAR)
}
