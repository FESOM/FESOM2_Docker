#ifndef __XIOS_INETCDF4_IMPL__
#define __XIOS_INETCDF4_IMPL__

#include "inetcdf4.hpp"
#include "netCdfInterface.hpp"

namespace xios
{
template <class T, int Ndim>
void CINetCDF4::getData(CArray<T, Ndim>& data, const StdString& var,
                       bool collective, StdSize record,
                       const std::vector<StdSize>* start,
                       const std::vector<StdSize>* count)
{
  int varid = this->getVariable(var);

  if (this->mpi && collective)
    CNetCdfInterface::varParAccess(ncidp, varid, NC_COLLECTIVE);
  else if (this->mpi && !collective)
    CNetCdfInterface::varParAccess(ncidp, varid, NC_INDEPENDENT);

  std::vector<StdSize> sstart, scount;
  StdSize array_size = 1;
  this->getDataInfo(var, NULL, record, sstart, scount, array_size, start, count);

  if (data.numElements() != array_size)
  {
    ERROR("CINetCDF4::getData(...)",
          << "[ Array size = " << data.numElements()
          << ", Data size = "  << array_size
          << " ] Invalid array size");
  }

  CNetCdfInterface::getVaraType(ncidp, varid, &sstart[0], &scount[0], data.dataFirst());
}

} // namespace xios

#endif //__XIOS_INETCDF4_IMPL__
