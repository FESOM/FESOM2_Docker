/*!
   \file netCdfInterface.cpp
   \author Ha NGUYEN
   \date 08 Oct 2014
   \since 03 Oct 2014

   \brief Wrapper of netcdf functions.
 */

#include "netCdfInterface.hpp"
#include "netCdfException.hpp"

namespace xios
{
/*!
This function creates a new netcdf file and return its id
\param [in] fileName Name of the file
\param [in] cMode create mode
\param [in/out] ncId id of the created file
\return Status code
*/
int CNetCdfInterface::create(const StdString& fileName, int cMode, int& ncId)
{
  int status = nc_create(fileName.c_str(), cMode, &ncId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;
    sstr << "Error when calling function: nc_create(fileName.c_str(), cMode, &ncId) " << std::endl
         << errormsg << std::endl
         << "Unable to create file, given its name: " << fileName
         << " and its creation mode " << creationMode2String(cMode) << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function creates a new netcdf file on parallel file system
\param [in] fileName Name of the file
\param [in] cMode create mode
\param [in] comm MPI communicator
\param [in] info MPI information
\param [in/out] ncId id of the created file
\return Status code
*/
int CNetCdfInterface::createPar(const StdString& fileName, int cMode, MPI_Comm comm, MPI_Info info, int& ncId)
{
  int status = xios::nc_create_par(fileName.c_str(), cMode, comm, info, &ncId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;
    sstr << "Error when calling function: nc_create_par(fileName.c_str(), cMode, comm, info, &ncId) " << std::endl
         << errormsg << std::endl
         << "Unable to create file on parallel file system, given its name: " << std::endl
         << "and its creation mode " << creationMode2String(cMode) << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function opens a netcdf file, given its name and open mode, return its id
\param [in] fileName Name of the file
\param [in] oMode open mode
\param [in/out] ncId id of the opening file
\return Status code
*/
int CNetCdfInterface::open(const StdString& fileName, int oMode, int& ncId)
{
  int status = nc_open(fileName.c_str(), oMode, &ncId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;
    sstr << "Error when calling function: nc_open(fileName.c_str(), oMode, &ncId) "<< std::endl
         << errormsg << std::endl
         << "Unable to open file, given its name: " << fileName
         << "and its open mode " << openMode2String(oMode) << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}


/*!
This function opens a new netcdf file on parallel file system
\param [in] fileName Name of the file
\param [in] oMode open mode
\param [in] comm MPI communicator
\param [in] info MPI information
\param [in/out] ncId id of the opened file
\return Status code
*/
int CNetCdfInterface::openPar(const StdString& fileName, int oMode, MPI_Comm comm, MPI_Info info, int& ncId)
{
  int status = xios::nc_open_par(fileName.c_str(), oMode, comm, info, &ncId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;
    sstr << "Error when calling function nc_open_par(fileName.c_str(), oMode, comm, info, &ncId) " << std::endl
         << errormsg << std::endl
         << "Unable to open file on parallel file system, given its name: " << fileName
         << "and its open mode " << openMode2String(oMode) << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function closes a netcdf file, given its id
\param [in] ncId id of the opening netcdf file
\return Status code
*/
int CNetCdfInterface::close(int ncId)
{
  int status = nc_close(ncId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;
    sstr << "Error when calling function nc_close(ncId)" << std::endl
         << errormsg << std::endl
         << "Unable to close file, given its id: " << ncId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function put a netcdf file into define mode, given its id
\param [in] ncId id of the opening netcdf file to be put into define mode
\return Status code
*/
int CNetCdfInterface::reDef(int ncId)
{
  int status = nc_redef(ncId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;
    sstr << "Error when calling function nc_redef(ncId)" << std::endl
      << errormsg << std::endl
      << "Unable to put this file into define mode given its id: " << ncId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function ends a netcdf file define mode, given its id
\param [in] ncId id of the opening netcdf file to be put into define mode
\return Status code
*/
int CNetCdfInterface::endDef(int ncId)
{
  int status = nc_enddef(ncId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_enddef(ncId)" << std::endl
         << errormsg << std::endl
         << "Unable to end define mode of this file, given its id: " << ncId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf with ncid and group name then return ncid of the named group
\param [in] ncid Groupd id (or File Id)
\param [in] grpName Name of the desired group (or file)
\param [in/out] grpId Group id if the group is found
\return Status code
*/
int CNetCdfInterface::inqNcId(int ncid, const StdString& grpName, int& grpId)
{
  int status = nc_inq_ncid(ncid, grpName.c_str(), &grpId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_ncid(ncid, grpName.c_str(), &grpId)" << std::endl
         << errormsg << std::endl
         << "Unable to get id of a group (File), given its name: " << grpName << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}


/*!
This function makes a request to netcdf with ncid and variable name then return ncid of the named variable
\param [in] ncid Groupd id (or File Id)
\param [in] varName Name of the desired variable
\param [in/out] varId Variable id if this variable is found
\return Status code
*/
int CNetCdfInterface::inqVarId(int ncid, const StdString& varName, int& varId)
{
  int status = nc_inq_varid(ncid, varName.c_str(), &varId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function: nc_inq_varid(ncid, varName.c_str(), &varId)" << std::endl
         << (errormsg) << std::endl
         << "Unable to get id of variable with name: " << varName << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf with a netCdf dimension name then return ncid of the named dimension
\param [in] ncid Groupd id (or File Id)
\param [in] dimName Name of the desired dimension
\param [in/out] dimId Dimension id if this dimension is found
\return Status code
*/
int CNetCdfInterface::inqDimId(int ncid, const StdString& dimName, int& dimId)
{
  int status = nc_inq_dimid(ncid, dimName.c_str(), &dimId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_dimid(ncid, dimName.c_str(), &dimId)" << std::endl
         << errormsg << std::endl
         << "Unable to get id of dimension, given its name: " << dimName << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function queries the name of a variable given its id.
\param [in] ncid Groupd id (or File Id)
\param [in] varId Id of desired variable
\param [out] varName name of desired variable
\return Status code
*/
int CNetCdfInterface::inqVarName(int ncid, int varId, StdString& varName)
{
  char varNameBuff[NC_MAX_NAME + 1];
  int status = nc_inq_varname(ncid, varId, varNameBuff);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_varname(ncid, varId, varNameBuff)" << std::endl
         << errormsg << std::endl
         << "Unable to get variable name: "<< varName << " given its id: " << varId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }
  varName = varNameBuff;
  return status;
}

/*!
This function makes a request to netcdf with a netCdf dimension name then return ncid of the named dimension
\param [in] ncid Groupd id (or File Id)
\param [in/out] dimId Dimension id if this dimension is found
\return Status code
*/
int CNetCdfInterface::inqUnLimDim(int ncid, int& dimId)
{
  int status = nc_inq_unlimdim(ncid, &dimId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_dimid" << std::endl
      << errormsg << std::endl
      << "Unable to get id of unlimited dimension " << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
 }

  return status;
}

/*!
This function makes a request to netcdf, returns name of a dimension, given its id
\param [in] ncid Groupd id (or File Id)
\param [in] dimId Id of desired dimension
\param [out] dimName Name of desired dimension
\return Status code
*/
int CNetCdfInterface::inqDimName(int ncid, int dimId, StdString& dimName)
{
  char fullNameIn[NC_MAX_NAME + 1];
  int status = nc_inq_dimname(ncid, dimId, fullNameIn);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_dimname(ncid, dimId, fullNameIn)" << std::endl
         << errormsg << std::endl
         << "Unable to get dimension name: " << dimName << " given its id: " << dimId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }
  dimName = StdString(fullNameIn);
  return status;
}

/*!
This function makes a request to netcdf, returns length of a dimension, given its id
\param [in] ncid Groupd id (or File Id)
\param [in] dimId Id of desired dimension
\param [in/out] dimLen Length of desired dimension
\return Status code
*/
int CNetCdfInterface::inqDimLen(int ncid, int dimId, StdSize& dimLen)
{
  int status = nc_inq_dimlen(ncid, dimId, &dimLen);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_dimlen(ncid, dimId, &dimLen)" << std::endl
         << errormsg << std::endl
         << "Unable to get dimension length given its id: " << dimId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf, returns number of dimensions of a variable, given its id
\param [in] ncid Groupd id (or File Id)
\param [in] varId Id of variable
\param [in/out] ndims number of dimension of the variable
\return Status code
*/
int CNetCdfInterface::inqVarNDims(int ncid, int varId, int& nDims)
{
  int status = nc_inq_varndims(ncid, varId, &nDims);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_varndims(ncid, varId, &nDims)" << std::endl
         << errormsg << std::endl
         << "Unable to get the number of dimension of variable with Id: " << varId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf, returns a list of dimension ID describing the shape of the variable, given its id
\param [in] ncid Groupd id (or File Id)
\param [in] varId Id of variable
\param [in/out] dimIds list of dimension of the variable
\return Status code
*/
int CNetCdfInterface::inqVarDimId(int ncid, int varId, int* dimIds)
{
  int status = nc_inq_vardimid(ncid, varId, dimIds);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_vardimid(ncid, varId, dimIds)" << std::endl
         << errormsg << std::endl
         << "Unable to get list of dimension id of the variable with id " << varId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf, to find all dimension in a group
\param [in] ncid Groupd id (or File Id)
\param [in/out] nDims number of list of dimension
\param [in/out] dimIds list of dimension in a group or any of its parent
\param [in] includeParents number of parents
\return Status code
*/
int CNetCdfInterface::inqDimIds(int ncid, int& nDims, int* dimIds, int includeParents)
{
  int status = nc_inq_dimids(ncid, &nDims, dimIds, includeParents);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_dimids(ncid, &nDims, dimIds, includeParents)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to retrieve number of dimension in the group with id: " << ncid << std::endl;
    sstr << "With number of Parents " << includeParents << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function queries the full name of a group given its id.
\param [in] ncid Groupd id (or File Id)
\param [in/out] grpFullName the full name of the group
\return Status code
*/
int CNetCdfInterface::inqGrpFullName(int ncid, StdString& grpFullName)
{
  StdSize strlen = 0;
  std::vector<char> buff;
  int status = nc_inq_grpname_full(ncid, &strlen, NULL);
  if (NC_NOERR == status)
  {
    buff.resize(strlen + 1);
    status = nc_inq_grpname_full(ncid, NULL, &buff[0]);
  }

  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_grpname_full(ncid, &strlen, &buff[0])" << std::endl
         << errormsg << std::endl
         << "Unable to get the full group name given its id: " << ncid << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  grpFullName.assign(buff.begin(), buff.end());

  return status;
}

/*!
This function queries the list of group ids given a location id.
\param [in] ncid Groupd id (or File Id)
\param [in/out] numgrps number of groups
\param [in/out] ncids list of group ids
\return Status code
*/
int CNetCdfInterface::inqGrpIds(int ncid, int& numgrps, int* ncids)
{
  int status = nc_inq_grps(ncid, &numgrps, ncids);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_grps(ncid, &numgrps, ncids)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to retrieve the list of groups for location id: " << ncid << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function queries the list of variable ids given a location id.
\param [in] ncid Groupd id (or File Id)
\param [in/out] nvars number of variables
\param [in/out] varids list of variable ids
\return Status code
*/
int CNetCdfInterface::inqVarIds(int ncid, int& nvars, int* varids)
{
  int status = nc_inq_varids(ncid, &nvars, varids);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_varids(ncid, &nvars, varids)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to retrieve the list of variables for location id: " << ncid << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function queries the type and the size of an attribute given its name and the id of the variable to which it is attached.
\param [in] ncid Groupd id (or File Id)
\param [in] varid the id of the variable to which the attribute is attached
\param [in] name the name of the attribute
\param [out] type the type of the attribute
\param [out] len the size of the attribute
\return Status code
*/
int CNetCdfInterface::inqAtt(int ncid, int varid, const StdString& name, nc_type& type, size_t& len)
{
  int status = nc_inq_att(ncid, varid, name.c_str(), &type, &len);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_att(ncid, varid, name.c_str(), &type, &len)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to query the attribute information given its name: " << name << " and its variable id:" << varid << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function queries the number of global attributes given a location id.
\param [in] ncid Groupd id (or File Id)
\param [out] ngatts the number of global attributes
\return Status code
*/
int CNetCdfInterface::inqNAtts(int ncid, int& ngatts)
{
  int status = nc_inq_natts(ncid, &ngatts);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_natts(ncid, &ngatts)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to query the number of global attributes given the location id:" << ncid << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function queries the number of global attributes given a location id and a variable id.
\param [in] ncid Groupd id (or File Id)
\param [in] varid the id of the variable
\param [out] natts the number of global attributes
\return Status code
*/
int CNetCdfInterface::inqVarNAtts(int ncid, int varid, int& natts)
{
  int status = nc_inq_varnatts(ncid, varid, &natts);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_varnatts(ncid, varid, &natts)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to query the number of attributes given the location id:" << ncid << " and the variable id:" << varid << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}


//! Query the name of an attribute given a location id, a variable id and the attribute number
int CNetCdfInterface::inqAttName(int ncid, int varid, int attnum, StdString& name)
{
  std::vector<char> attName(NC_MAX_NAME + 1,' ');
  int status = nc_inq_attname(ncid, varid, attnum, &attName[0]);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_inq_attname(ncid, varid, attnum, attName)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to query the name: " << name << " of attribute " << attnum << " given the location id:" << ncid << " and the variable id:" << varid << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  int nameSize = 0;
  while ((nameSize < NC_MAX_NAME) && (' ' != attName[nameSize] )) ++nameSize;
  name.resize(nameSize);
//  for (int idx = 0; idx < nameSize; ++idx) name.at(idx) = attName[idx];
  std::copy(&attName[0], &attName[nameSize-1], name.begin());

  return status;
}

/*!
This function makes a request to netcdf with a id of a prent groupd and then return id of the created group, given its name
\param [in] parentNcid Id of parent groupd(or File Id)
\param [in] grpName Name of the desired group
\param [in/out] grpId Group id if this group is created sucessfully
\return Status code
*/
int CNetCdfInterface::defGrp(int parentNcid, const StdString& grpName, int& grpId)
{
  int status = nc_def_grp(parentNcid, grpName.c_str(), &grpId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_def_grp(parentNcid, grpName.c_str(), &grpId)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to create group Id, given its name: " << grpName << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf, add a new dimension to an open netcdf in define mode
\param [in] ncid Id of groupd(or File Id)
\param [in] dimName Name of the desired dimension
\param [in/out] grpId Group id if this group is created sucessfully
\return Status code
*/
int CNetCdfInterface::defDim(int ncid, const StdString& dimName, StdSize dimLen, int& dimId)
{
  int status = nc_def_dim(ncid, dimName.c_str(), dimLen, &dimId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_def_dim(ncid, dimName.c_str(), dimLen, &dimId)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to create dimension with name: " << dimName
         << " and with length " << dimLen << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf with its id, to add a new variable to an open netCdf in define mode,
return a variable id, given its name, type, the number of dimensions and list of dimension id
\param [in] ncid Id of groupd(or File Id)
\param [in] varName Name of the desired dimension
\param [in] xtypes One of the set of predefined netCDF data types
\param [in] nDims Number of dimension for the variable
\param [in] dimIds List of ndims dimension ids corresponding to the variable dimensions
\param [in/out] varId Variable id if it is added sucessfully
\return Status code
*/
int CNetCdfInterface::defVar(int ncid, const StdString& varName, nc_type xtype,
                             int nDims, const int dimIds[], int& varId)
{
  int status = nc_def_var(ncid, varName.c_str(), xtype, nDims, dimIds, &varId);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function  nc_def_var(ncid, varName.c_str(), xtype, nDims, dimIds, &varId)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to add a new variable with name: " << varName
         << " with type " << xtype
         << " and number of dimension " << nDims << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf with a ncid, to set the chunking size of a variable,
given variable id and type of storage
\param [in] ncid Id groupd(or File Id)
\param [in] varId Id of the variable
\param [in] storage Type of storage (It can be: NC_CONTIGUOUS, NC_CHUNKED)
\param [in/out] chunkSize array list of chunk sizes
\return Status code
*/
int CNetCdfInterface::defVarChunking(int ncid, int varId, int storage, StdSize chunkSize[])
{
  int status = nc_def_var_chunking(ncid, varId, storage, chunkSize);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_def_var_chunking(ncid, varId, storage, chunkSize)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to set chunk size of the variable with id: " << varId
      << " and storage type " << storage << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function sets the compression level to the specified variable
\param [in] ncid Groud id (or file id)
\param [in] varId Id of the variable
\param [in] compressionLevel The compression level from 0 to 9 (0 disables the compression, 9 is the higher compression)
\return Status code
*/
int CNetCdfInterface::defVarDeflate(int ncid, int varId, int compressionLevel)
{

  if (compressionLevel == 0) return NC_NOERR ;
  // Blosc filter (HDF5 id 32001) with zstd subcodec + byte shuffle.
  // cd_values layout: [ver, verformat, typesize(0=auto), chunksize(0=auto),
  //                    clevel, shuffle(1=byte), subcodec(5=zstd)].
  // Requires HDF5_PLUGIN_PATH to point at a dir containing libh5blosc*.so
  // with c-blosc >= 1.11 (zstd subcodec) at runtime (writer and reader).
  unsigned int cd_values[7] = { 0, 0, 0, 0,
                                (unsigned) compressionLevel,
                                1,  /* byte shuffle */
                                5 /* zstd subcodec */ };
  int status = nc_def_var_filter(ncid, varId, 32001, 7, cd_values);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling nc_def_var_filter(blosc/zstd id=32001) for varId " << varId
         << " with compressionLevel=" << compressionLevel << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Check that HDF5_PLUGIN_PATH points at a dir containing libh5blosc*.so." << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
Set or unset the fill mode for a NetCDF file specified by its file id.
\param [in] ncid File id
\param [in] fill Define whether the fill mode should be enabled or not
\return Status code
*/
int CNetCdfInterface::setFill(int ncid, bool fill)
{
  int old_fill_mode;
  int status = nc_set_fill(ncid, fill ? NC_FILL: NC_NOFILL, &old_fill_mode);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_set_fill(ncid, fill ? NC_FILL: NC_NOFILL, &old_fill_mode)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to set the fill mode to: " << (fill ? "NC_FILL": "NC_NOFILL") << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf with a ncid, to set the fill parameters for a variable,
given variable id and type of fill
\param [in] ncid Id groupd(or File Id)
\param [in] varId Id of the variable
\param [in] noFill turn on/off nofill mode on a variable
\param [in/out] fillValue
\return Status code
*/
int CNetCdfInterface::defVarFill(int ncid, int varId, int noFill, void* fillValue)
{
  int status = nc_def_var_fill(ncid, varId, noFill, fillValue);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_def_var_fill(ncid, varId, noFill, fillValue)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to set fill parameters of the variable with id: " << varId
      << " and fill option " << noFill << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a request to netcdf with a ncid, to change the way read/write operations are performed
collectively or independently on the variable.
\param [in] ncid Id groupd(or File Id)
\param [in] varId Id of the variable
\param [in] noFill turn on/off nofill mode on a variable
\param [in/out] fillValue
\return Status code
*/
int CNetCdfInterface::varParAccess(int ncid, int varId, int access)
{
  int status = nc_var_par_access(ncid, varId, access);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_var_par_access(ncid, varId, access)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to change read/write option of the variable with id: " << varId << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

/*!
This function makes a synchronisation of the disk copy of a netCDF dataset.
\param [in] ncid Id groupd(or File Id)
\return Status code
*/
int CNetCdfInterface::sync(int ncid)
{
  int status = nc_sync(ncid);
  if (NC_NOERR != status)
  {
    StdString errormsg(nc_strerror(status));
    StdStringStream sstr;

    sstr << "Error when calling function nc_sync(ncid)" << std::endl;
    sstr << errormsg << std::endl;
    sstr << "Unable to make a synchronization of a netCDF file with id: " << ncid << std::endl;
    StdString e = sstr.str();
    throw CNetCdfException(e);
  }

  return status;
}

// Some specializations of getAttributeType
template<>
int CNetCdfInterface::ncGetAttType(int ncid, int varid, const char* attrName, double* data)
{
  return nc_get_att_double(ncid, varid, attrName, data);
}

template<>
int CNetCdfInterface::ncGetAttType(int ncid, int varid, const char* attrName, float* data)
{
  return nc_get_att_float(ncid, varid, attrName, data);
}

template<>
int CNetCdfInterface::ncGetAttType(int ncid, int varid, const char* attrName, int* data)
{
  return nc_get_att_int(ncid, varid, attrName, data);
}

template<>
int CNetCdfInterface::ncGetAttType(int ncid, int varid, const char* attrName, long* data)
{
  return nc_get_att_long(ncid, varid, attrName, data);
}

template<>
int CNetCdfInterface::ncGetAttType(int ncid, int varid, const char* attrName, short* data)
{
  return nc_get_att_short(ncid, varid, attrName, data);
}

template<>
int CNetCdfInterface::ncGetAttType(int ncid, int varid, const char* attrName, char* data)
{
  return nc_get_att_text(ncid, varid, attrName, data);
}

// Some specializations of putAttributeType
template<>
int CNetCdfInterface::ncPutAttType(int ncid, int varid, const char* attrName,
                                   StdSize numVal, const double* data)
{
  return nc_put_att_double(ncid, varid, attrName, NC_DOUBLE, numVal, data);
}

template<>
int CNetCdfInterface::ncPutAttType(int ncid, int varid, const char* attrName,
                                   StdSize numVal, const float* data)
{
  return nc_put_att_float(ncid, varid, attrName, NC_FLOAT, numVal, data);
}

template<>
int CNetCdfInterface::ncPutAttType(int ncid, int varid, const char* attrName,
                                   StdSize numVal, const int* data)
{
  return nc_put_att_int(ncid, varid, attrName, NC_INT, numVal, data);
}

template<>
int CNetCdfInterface::ncPutAttType(int ncid, int varid, const char* attrName,
                                   StdSize numVal, const long* data)
{
  return nc_put_att_long(ncid, varid, attrName, NC_LONG, numVal, data);
}

template<>
int CNetCdfInterface::ncPutAttType(int ncid, int varid, const char* attrName,
                                   StdSize numVal, const short* data)
{
  return nc_put_att_short(ncid, varid, attrName, NC_SHORT, numVal, data);
}

template<>
int CNetCdfInterface::ncPutAttType(int ncid, int varid, const char* attrName,
                                   StdSize numVal, const char* data)
{
  return nc_put_att_text(ncid, varid, attrName, numVal, data);
}

// Some specializations of getVariableType
template<>
int CNetCdfInterface::ncGetVaraType(int ncid, int varid, const StdSize* start, const StdSize* count, double* data)
{
  return nc_get_vara_double(ncid, varid, start, count, data);
}

template<>
int CNetCdfInterface::ncGetVaraType(int ncid, int varid, const StdSize* start, const StdSize* count, float* data)
{
  return nc_get_vara_float(ncid, varid, start, count, data);
}

template<>
int CNetCdfInterface::ncGetVaraType(int ncid, int varid, const StdSize* start, const StdSize* count, int* data)
{
  return nc_get_vara_int(ncid, varid, start, count, data);
}

template<>
int CNetCdfInterface::ncGetVaraType(int ncid, int varid, const StdSize* start, const StdSize* count, char* data)
{
  return nc_get_vara_text(ncid, varid, start, count, data);
}

// Some specializations of putVariableType
template<>
int CNetCdfInterface::ncPutVaraType(int ncid, int varid, const StdSize* start, const StdSize* count, const double* data)
{
  return nc_put_vara_double(ncid, varid, start, count, data);
}

template<>
int CNetCdfInterface::ncPutVaraType(int ncid, int varid, const StdSize* start, const StdSize* count, const float* data)
{
  return nc_put_vara_float(ncid, varid, start, count, data);
}

template<>
int CNetCdfInterface::ncPutVaraType(int ncid, int varid, const StdSize* start, const StdSize* count, const int* data)
{
  return nc_put_vara_int(ncid, varid, start, count, data);
}

template<>
int CNetCdfInterface::ncPutVaraType(int ncid, int varid, const StdSize* start, const StdSize* count, const char* data)
{
  return nc_put_vara_text(ncid, varid, start, count, data);
}

 /*!
 This function verifies an existence of a variable by using its name.
 Be careful, althoug false means variable doens't exist, it could show that netCDF file doesn't either
 \param [in] ncid Id of groupd(or File Id)
 \param [in] attrName Name of the variable
 \return Existence of variable
 */
bool CNetCdfInterface::isVarExisted(int ncId, const StdString& varName)
{
   int varId = 0;
   return (NC_NOERR == (nc_inq_varid(ncId, varName.c_str(), &varId)));
}

bool CNetCdfInterface::isDimExisted(int ncId, const StdString& dimName)
{
   int dimId = 0;
   return (NC_NOERR == (nc_inq_dimid(ncId, dimName.c_str(), &dimId)));
}

StdString CNetCdfInterface::openMode2String(int oMode)
{
  StdString modeMes;
  switch (oMode)
  {
  case NC_NOWRITE:
    modeMes = StdString("NC_NOWRITE: Opening netCDF file with read-only access with buffering and caching access");
    break;
  case NC_SHARE:
    modeMes = StdString("NC_SHARE: Several processes can read the file concurrently");
    break;
  case NC_WRITE:
    modeMes = StdString("NC_WRITE: NetCDF file is readable and writable");
    break;
  default:
    modeMes = StdString("In the composed opening mode");
    break;
  }
  return modeMes;
}

StdString CNetCdfInterface::creationMode2String(int cMode)
{
  StdString modeMes;
  switch (cMode)
  {
  case NC_NOCLOBBER:
    modeMes = StdString("NC_NOCLOBBER: Not overwrite an exisiting netCDF file ");
    break;
  case NC_SHARE:
    modeMes = StdString("NC_SHARE: Several processes can read from and write into the file concurrently");
    break;
  case NC_64BIT_OFFSET:
    modeMes = StdString("NC_64BIT_OFFSET: NetCDF file is 64-bit offset");
    break;
  case NC_NETCDF4:
    modeMes = StdString("NC_NETCDF4: NetCDF file is HDF5/NetCDF-4");
    break;
  case NC_CLASSIC_MODEL:
    modeMes = StdString("NC_CLASSIC_MODEL: NetCDF file is classical model");
    break;
  default:
    modeMes = StdString("In the composed creation mode");
    break;
  }
  return modeMes;
}

}
