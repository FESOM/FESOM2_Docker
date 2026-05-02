/*!
   \file netCdfInterface_impl.hpp
   \author Ha NGUYEN
   \date 08 Oct 2014
   \since 06 Oct 2014

   \brief Implementation of some templated functions in netCdfInterface
 */

#ifndef __NETCDF_INTERFACE_IMPL_HPP__
#define __NETCDF_INTERFACE_IMPL_HPP__

#include "netCdfInterface.hpp"
#include "netCdfException.hpp"

namespace xios
{
  /*!
  This function reads a variable attribute or a global attribute
  given a location id, a variable id and the attribute name
  \param [in] ncid Id of group (or file id)
  \param [in] varId Id of the variable
  \param [in] attrName Name of the attribute
  \param [out] data Array of values
  \return Status code
  */
  template<typename T>
  int CNetCdfInterface::getAttType(int ncid, int varId, const StdString& attrName, T* data)
  {
    int status = ncGetAttType(ncid, varId, attrName.c_str(), data);
    if (NC_NOERR != status)
    {
      StdStringStream sstr;
      StdString varName;
      sstr << "Error when calling function ncGetAttType(ncid, varId, attrName.c_str(), data)" << std::endl;
      sstr << nc_strerror(status) << std::endl;
      inqVarName(ncid, varId, varName);
      sstr << "Unable to read attribute " << attrName << " given the location id: " << ncid << " and the variable whose id: " << varId << " and name: " << varName << std::endl;
      throw CNetCdfException(sstr.str());
    }

    return status;
  }

  /*!
  This function adds or modifies a variable attribute or a global attribute
  given a location id, a variable id and the attribute name
  \param [in] ncid Id of group (or file id)
  \param [in] varId Id of the variable
  \param [in] attrName Name of the attribute
  \param [in] numVal Number of values to set
  \param [in] data Array of values
  \return Status code
  */
  template<typename T>
  int CNetCdfInterface::putAttType(int ncid, int varId, const StdString& attrName,
                                   StdSize numVal, const T* data)
  {
    int status = ncPutAttType(ncid, varId, attrName.c_str(), numVal, data);
    if (NC_NOERR != status)
    {
      StdStringStream sstr;
      StdString varName;
      sstr << "Error when calling function ncPutAttType(ncid, varId, attrName.c_str(), numVal, data)" << std::endl;
      sstr << nc_strerror(status) << std::endl;
      inqVarName(ncid, varId, varName);
      sstr << "Unable to set attribute " << attrName << " given the location id: " << ncid << " and the variable whose id: " << varId << " and name: " << varName << std::endl
           << " with " << numVal << " elements." << std::endl;
      throw CNetCdfException(sstr.str());
    }

    return status;
  }

  /*!
  This function reads data for the specified variable.
  \param [in] ncid Id of group (or file id)
  \param [in] varId Id of the variable
  \param [in] start Array specifying the index in the variable where the first data value will be written
  \param [in] count Array specifying the edge lengths along each dimension of the data block
  \param [out] data Array of values
  \return Status code
  */
  template<typename T>
  int CNetCdfInterface::getVaraType(int ncid, int varId, const StdSize* start, const StdSize* count, T* data)
  {
    int status = ncGetVaraType(ncid, varId, start, count, data);
    if (NC_NOERR != status)
    {
      StdStringStream sstr;
      StdString varName;
      sstr << "Error when calling function ncGetVaraType(ncid, varId, start, count, data)" << std::endl;
      sstr << nc_strerror(status) << std::endl;
      inqVarName(ncid, varId, varName);
      sstr << "Unable to read data given the location id: " << ncid << " and the variable whose id: " << varId << " and name: " << varName << std::endl;
      throw CNetCdfException(sstr.str());
    }

    return status;
  }

  /*!
  This function writes the given data for the specified variable.
  \param [in] ncid Id of group (or file id)
  \param [in] varId Id of the variable
  \param [in] start Array specifying the index in the variable where the first data value will be written
  \param [in] count Array specifying the edge lengths along each dimension of the data block
  \param [in] data Array of values
  \return Status code
  */
  template<typename T>
  int CNetCdfInterface::putVaraType(int ncid, int varId, const StdSize* start, const StdSize* count, const T* data)
  {
    int status = ncPutVaraType(ncid, varId, start, count, data);
    if (NC_NOERR != status)
    {
      StdStringStream sstr;
      StdString varName;
      sstr << "Error when calling function ncPutVaraType(ncid, varId, start, count, data)" << std::endl;
      sstr << nc_strerror(status) << std::endl;
      inqVarName(ncid, varId, varName);
      sstr << "Unable to write data given the location id: " << ncid << " and the variable whose id: " << varId << " and name: " << varName << std::endl;
      throw CNetCdfException(sstr.str());
    }

    return status;
  }
}

#endif // __NETCDF_INTERFACE_IMPL_HPP__
