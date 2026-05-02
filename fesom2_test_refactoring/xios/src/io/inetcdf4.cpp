#include "inetcdf4.hpp"
#include "netCdfInterface.hpp"
#include "netCdf_cf_constant.hpp"

#include <boost/algorithm/string.hpp>

namespace xios
{
  CINetCDF4::CINetCDF4(const StdString& filename, const MPI_Comm* comm /*= NULL*/, bool multifile /*= true*/,
                       bool readMetaDataPar /*= false*/, const StdString& timeCounterName /*= "time_counter"*/)
  {
    // Don't use parallel mode if there is only one process
    if (comm)
    {
      int commSize = 0;
      MPI_Comm_size(*comm, &commSize);
      if (commSize <= 1)
        comm = NULL;
    }
    mpi = comm && !multifile && readMetaDataPar;

    // The file format will be detected automatically by NetCDF, it is safe to always set NC_MPIIO
    // even if Parallel NetCDF ends up being used.
    if (mpi)
      CNetCdfInterface::openPar(filename, NC_NOWRITE | NC_MPIIO, *comm, MPI_INFO_NULL, this->ncidp);
    else
      CNetCdfInterface::open(filename, NC_NOWRITE, this->ncidp);

    this->timeCounterName = timeCounterName;

    if (!CNetCdfInterface::isDimExisted(this->ncidp, this->timeCounterName)) this->timeCounterName=this->getUnlimitedDimensionName() ;

  }

  CINetCDF4::~CINetCDF4(void)
  { /* Nothing to do */ }

  //---------------------------------------------------------------

  void CINetCDF4::close(void)
  {
    CNetCdfInterface::close(this->ncidp);
  }

  //---------------------------------------------------------------

  int CINetCDF4::getGroup(const CVarPath* const path)
  {
    int retvalue = this->ncidp;
    if (path == NULL) return retvalue;
    CVarPath::const_iterator it = path->begin(), end = path->end();

    for (; it != end; it++)
    {
      const StdString& groupid = *it;
      CNetCdfInterface::inqNcId(retvalue, groupid, retvalue);
    }

    return retvalue;
  }

  int CINetCDF4::getVariable(const StdString& varname,
                             const CVarPath* const path)
  {
    int varid = 0;
    int grpid = this->getGroup(path);
    if (this->hasVariable(varname, path))
      CNetCdfInterface::inqVarId(grpid, varname, varid);
    return varid;
  }

  int CINetCDF4::getDimension(const StdString& dimname,
                              const CVarPath* const path)
  {
    int dimid = 0;
    int grpid = this->getGroup(path);
    CNetCdfInterface::inqDimId(grpid, dimname, dimid);
    return dimid;
  }

  std::pair<nc_type, StdSize> CINetCDF4::getAttribute(const StdString& attname,
                                                      const StdString* const var,
                                                      const CVarPath* const path)
  {
    std::pair<nc_type, StdSize> retvalue;
    int grpid = this->getGroup(path);
    int varid = (var != NULL && this->hasVariable(*var, path)) ? this->getVariable(*var, path) : NC_GLOBAL;
    CNetCdfInterface::inqAtt(grpid, varid, attname, retvalue.first, retvalue.second);
    return retvalue;
  }

  
  bool CINetCDF4::hasUnlimitedDimension(const CVarPath* const path)
  {
    int dimid = 0;
    int grpid = this->getGroup(path);
    CNetCdfInterface::inqUnLimDim(grpid, dimid);
    if (dimid==-1) return false ;
    else return true ;
  }

  int CINetCDF4::getUnlimitedDimension(const CVarPath* const path)
  {
    int dimid = 0;
    int grpid = this->getGroup(path);
    CNetCdfInterface::inqUnLimDim(grpid, dimid);
    return dimid;
  }

  StdString CINetCDF4::getUnlimitedDimensionName(const CVarPath* const path)
  {
    int grpid = this->getGroup(path);
    int dimid = this->getUnlimitedDimension(path);

    StdString dimname;
    if (dimid != -1)
      CNetCdfInterface::inqDimName(grpid, dimid, dimname);
    return dimname;
  }

  //---------------------------------------------------------------

  StdSize CINetCDF4::getNbVertex(const StdString& name,
                                 const CVarPath* const path)
  {

    if (this->isRectilinear(name, path) ||
       this->isCurvilinear(name, path))
    {
      if (this->is3Dim(name, path)) return 8;
      else return 4;
    }
    if (this->isUnstructured(name, path))
    {
      StdString bound = this->getBoundsId
            (this->getCoordinatesIdList(name, path).back(), path);
      StdString dim = this->getDimensionsList(&bound, path).back();
      return this->getDimensions(&bound, path)[dim];
    }
    return size_t(-1);
  }

  //---------------------------------------------------------------

  std::list<StdString> CINetCDF4::getGroups(const CVarPath* const path)
  {
    int nbgroup = 0, *groupid = NULL;
    int grpid = this->getGroup(path);
    std::list<StdString> retvalue;

    CNetCdfInterface::inqGrpIds(grpid, nbgroup, NULL);
    groupid = new int[nbgroup]();
    CNetCdfInterface::inqGrpIds(grpid, nbgroup, groupid);

    for (int i = 0; i < nbgroup; i++)
    {
      StdString fullGrpName;
      CNetCdfInterface::inqGrpFullName(groupid[i], fullGrpName);
      retvalue.push_back(fullGrpName);
    }

    delete [] groupid;
    return retvalue;
  }

  std::list<StdString> CINetCDF4::getVariables(const CVarPath* const path)
  {
    int nbvar = 0, *varid = NULL;
    int grpid = this->getGroup(path);
    std::list<StdString> retvalue;

    CNetCdfInterface::inqVarIds(grpid, nbvar, NULL);
    varid = new int[nbvar]();
    CNetCdfInterface::inqVarIds(grpid, nbvar, varid);

    for (int i = 0; i < nbvar; i++)
    {
      StdString varName;
      CNetCdfInterface::inqVarName(grpid, varid[i], varName);
      retvalue.push_back(varName);
    }

    delete [] varid;
    return retvalue;
  }

  std::set<StdString> CINetCDF4::getBoundVariables(const CVarPath* const path)
  {
    std::set<StdString> retvalue;
    std::list<StdString> variables = this->getVariables(path);
    std::list<StdString>::const_iterator it = variables.begin(), end = variables.end();
    for (; it != end; it++)
    {
      const StdString& var = *it;
      if (this->hasBounds(var, path))
        retvalue.insert(retvalue.end(), this->getBoundsId(var, path));
    }
    return retvalue;
  }

  std::set<StdString> CINetCDF4::getCoordVariables(const CVarPath* const path)
  {
    std::set<StdString> retvalue;
    std::list<StdString> variables = this->getVariables(path);
    std::list<StdString>::const_iterator it = variables.begin(), end = variables.end();
    for (; it != end; it++)
    {
      const StdString& var = *it;
      std::list<StdString> coords = this->getCoordinatesIdList(var, path);
      std::list<StdString>::const_iterator it = coords.begin(), end = coords.end();
      for (; it != end; it++)
      {
        const StdString& coord = *it;
        if (this->hasVariable(coord, path))
          retvalue.insert(retvalue.end(), coord);
      }
    }
    return retvalue;
  }

  std::list<StdString> CINetCDF4::getDimensionsList(const StdString* const var, const CVarPath* const path)
  {
    int nbdim = 0, *dimid = NULL;
    int grpid = this->getGroup(path);
    int varid = (var != NULL && this->hasVariable(*var, path)) ? this->getVariable(*var, path) : NC_GLOBAL;
    std::list<StdString> retvalue;

    if (var != NULL && this->hasVariable(*var, path))
    {
      CNetCdfInterface::inqVarNDims(grpid, varid, nbdim);
      dimid = new int[nbdim]();
      CNetCdfInterface::inqVarDimId(grpid, varid, dimid);
    }
    else
    {
      CNetCdfInterface::inqDimIds(grpid, nbdim, NULL, 1);
      dimid = new int[nbdim]();
      CNetCdfInterface::inqDimIds(grpid, nbdim, dimid, 1);
    }

    for (int i = 0; i < nbdim; i++)
    {
      std::string dimname;
      CNetCdfInterface::inqDimName(grpid, dimid[i], dimname);
      retvalue.push_back(dimname);
    }
    delete [] dimid;

    return retvalue;
  }

  std::map<StdString, StdSize> CINetCDF4::getDimensions(const StdString* const var, const CVarPath* const path)
  {
    int nbdim = 0, *dimid = NULL;
    int grpid = this->getGroup(path);
    int varid = (var != NULL && this->hasVariable(*var, path)) ? this->getVariable(*var, path) : NC_GLOBAL;
    std::map<StdString, StdSize> retvalue;

    if (var != NULL && this->hasVariable(*var, path))
    {
      CNetCdfInterface::inqVarNDims(grpid, varid, nbdim);
      dimid = new int[nbdim]();
      CNetCdfInterface::inqVarDimId(grpid, varid, dimid);
    }
    else
    {
      CNetCdfInterface::inqDimIds(grpid, nbdim, NULL, 1);
      dimid = new int[nbdim]();
      CNetCdfInterface::inqDimIds(grpid, nbdim, dimid, 1);
    }

    for (int i = 0; i < nbdim; i++)
    {
      std::string dimname;
      CNetCdfInterface::inqDimName(grpid, dimid[i], dimname);
      StdSize size = 0;
      CNetCdfInterface::inqDimLen(grpid, dimid[i], size);

      retvalue.insert(retvalue.end(), std::make_pair(dimname, size));
    }
    delete [] dimid;

    return retvalue;
  }

  std::list<StdString> CINetCDF4::getAttributes(const StdString* const var, const CVarPath* const path)
  {
    int nbatt = 0;
    std::list<StdString> retvalue;
    int grpid = this->getGroup(path);
    int varid = (var != NULL && this->hasVariable(*var, path)) ? this->getVariable(*var, path) : NC_GLOBAL;

    if (var != NULL && this->hasVariable(*var, path))
      CNetCdfInterface::inqVarNAtts(grpid, varid, nbatt);
    else
      CNetCdfInterface::inqNAtts(grpid, nbatt);

    for (int i = 0; i < nbatt; i++)
    {
      StdString attname;
      CNetCdfInterface::inqAttName(grpid, varid, i, attname);
      retvalue.push_back(attname);
    }
    return retvalue;
  }

  int CINetCDF4::getAttributeId(const StdString& name,
                                const StdString* const var,
                                const CVarPath* const path)
  {
    int retvalue = 0;
    std::list<StdString> atts = this->getAttributes(var, path);
    std::list<StdString>::const_iterator it = atts.begin(), end = atts.end();
    for (; it != end; it++)
    {
      const StdString& attname = *it;
      if (attname.compare(0, name.size(), name) == 0)
        return retvalue;
      retvalue++;
    }
    return -1;
  }

  //---------------------------------------------------------------

  bool CINetCDF4::hasMissingValue(const StdString& name,
                                  const CVarPath* const path)
  {
    return (this->hasAttribute("missing_value", &name, path) || this->hasAttribute("_FillValue", &name, path));
  }

  bool CINetCDF4::hasAttribute(const StdString& name,
                               const StdString* const var ,
                               const CVarPath* const path)
  {
    std::list<StdString> atts = this->getAttributes(var, path);
    std::list<StdString>::const_iterator it = atts.begin(), end = atts.end();
    for (; it != end; it++)
    {
      const StdString& attname = *it;
      if (attname.compare(0, name.size(), name) == 0) return true;
    }
    return false;
  }

  template <class T>
  bool CINetCDF4::hasAttribute(const StdString& name, const StdString* const var, const CVarPath* const path)
  {
    std::list<StdString> atts = this->getAttributes(var, path);
    std::list<StdString>::const_iterator it = atts.begin(), end = atts.end();
    for (; it != end; it++)
    {
      const StdString& attname = *it;
      if (attname.compare(0, name.size(), name) == 0)
      { 
        std::pair<nc_type , StdSize> attinfos = this->getAttribute(name, var, path);
        std::vector<T> retvalue(attinfos.second);
        nc_type type = CNetCdfInterface::getNcType<T>();
        if (attinfos.first == type) return true;
        else return false ;
      }
    }
    return false;
  }
  
  template bool  CINetCDF4::hasAttribute<double>(const StdString& name, const StdString* const var, const CVarPath* const path);
  template bool  CINetCDF4::hasAttribute<float>(const StdString& name, const StdString* const var, const CVarPath* const path);
  template bool  CINetCDF4::hasAttribute<int>(const StdString& name, const StdString* const var, const CVarPath* const path);
  template bool  CINetCDF4::hasAttribute<char>(const StdString& name, const StdString* const var, const CVarPath* const path);
  

  bool CINetCDF4::hasVariable(const StdString& name,
                              const CVarPath* const path)
  {
    std::list<StdString> variables = this->getVariables(path);
    std::list<StdString>::const_iterator it = variables.begin(), end = variables.end();
    for (; it != end; it++)
    {
      const StdString& varname = *it;
      if ((varname.compare(0, name.size(), name) == 0) && (0 != name.size()))  return true;
    }
    return false;
  }

  bool CINetCDF4::hasCoordinates(const StdString& name,
                                 const CVarPath* const path)
  {
    return this->hasAttribute(CCFKeywords::XIOS_CF_coordinates, &name, path);
  }

  bool CINetCDF4::hasBounds(const StdString& name,
                            const CVarPath* const path)
  {
    return this->hasAttribute(CCFKeywords::XIOS_CF_bounds, &name, path);
  }

  bool CINetCDF4::hasTemporalDim(const CVarPath* const path)
  {
    std::list<StdString> dims = this->getDimensionsList(NULL, path);
    return (std::find(dims.begin(), dims.end(), timeCounterName) != dims.end());
  }

  //---------------------------------------------------------------

  template <class T>
  std::vector<T> CINetCDF4::getAttributeValue(const StdString& name,
                                              const StdString* const var,
                                              const CVarPath* const path)
  {
    int grpid = this->getGroup(path);
    int varid = (var != NULL && this->hasVariable(*var, path)) ? this->getVariable(*var, path) : NC_GLOBAL;
    std::pair<nc_type , StdSize> attinfos = this->getAttribute(name, var, path);
    std::vector<T> retvalue(attinfos.second);
    nc_type type = CNetCdfInterface::getNcType<T>();
    if (attinfos.first != type)
      ERROR("CINetCDF4::getAttributeValue<T>(name, var, path)",
            << "[ name : " << name
            << ", type requested :" << attinfos.first
            << ", type stored : " << type << "]"
            << " Invalid type !");
    CNetCdfInterface::getAttType(grpid, varid, name.c_str(), &retvalue[0]);
    return retvalue;
  }

  template std::vector<double> CINetCDF4::getAttributeValue(const StdString& name,
                                                            const StdString* const var,
                                                            const CVarPath* const path);
  template std::vector<float> CINetCDF4::getAttributeValue(const StdString& name,
                                                           const StdString* const var,
                                                           const CVarPath* const path);
  template std::vector<int> CINetCDF4::getAttributeValue(const StdString& name,
                                                         const StdString* const var,
                                                         const CVarPath* const path);
  template std::vector<char> CINetCDF4::getAttributeValue(const StdString& name,
                                                          const StdString* const var,
                                                          const CVarPath* const path);

  StdString CINetCDF4::getAttributeValue(const StdString& name,
                                         const StdString* const var,
                                         const CVarPath* const path)
  {
    std::vector<char> data = this->getAttributeValue<char>(name, var, path);

    return StdString(data.begin(), data.end());
  }

  template <class T>
  T CINetCDF4::getMissingValue(const StdString& name, const CVarPath* const path)
  {
    if (this->hasAttribute("missing_value", &name, path))
      return this->getAttributeValue<T>("missing_value", &name, path)[0];
    if (this->hasAttribute("_FillValue", &name, path))
      return this->getAttributeValue<T>("_FillValue", &name, path)[0];
    return 0;
  }

  template double CINetCDF4::getMissingValue(const StdString& name, const CVarPath* const path);
  template float CINetCDF4::getMissingValue(const StdString& name, const CVarPath* const path);
  template int CINetCDF4::getMissingValue(const StdString& name, const CVarPath* const path);
  template char CINetCDF4::getMissingValue(const StdString& name, const CVarPath* const path);

  //---------------------------------------------------------------

  std::list<StdString> CINetCDF4::getCoordinatesIdList(const StdString& name, const CVarPath* const path)
  {
    std::list<StdString> retvalue;
    StdString value = this->getCoordinatesId(name, path);

    boost::split(retvalue, value, boost::is_any_of(" "));

    std::list<StdString>::iterator it = retvalue.begin(), end = retvalue.end();
    for (; it != end; it++)
    {
      StdString& coord = *it;
      coord.assign(coord.data());
    }
    return retvalue;
  }

  StdString CINetCDF4::getCoordinatesId(const StdString& name, const CVarPath* const path)
  {
    StdString retvalue;
    if (this->hasAttribute(CCFKeywords::XIOS_CF_coordinates, &name, path))
    {
      return this->getAttributeValue(CCFKeywords::XIOS_CF_coordinates, &name, path);
    }
    else
    {
      std::list<StdString> dims = this->getDimensionsList(&name, path);
      std::list<StdString>::const_iterator it = dims.begin(), end = dims.end();
      for (; it != end; it++)
      {
        const StdString& value = *it;
        retvalue.append(value).push_back(' ');
      }
      retvalue.erase(retvalue.end() - 1) ;
    }

    return retvalue;
  }

  StdString CINetCDF4::getBoundsId(const StdString& name,
                                   const CVarPath* const path)
  {
    StdString retvalue;
    if (this->hasAttribute(CCFKeywords::XIOS_CF_bounds, &name, path))
      retvalue = this->getAttributeValue(CCFKeywords::XIOS_CF_bounds, &name, path);
    return retvalue;
  }

  //---------------------------------------------------------------

  bool CINetCDF4::isBound(const StdString& name,
                          const CVarPath* const path)
  {
    std::set<StdString> bounds = this->getBoundVariables(path);
    return (bounds.find(name) != bounds.end());
  }

  bool CINetCDF4::isCoordinate(const StdString& name,
                               const CVarPath* const path)
  {
    std::set<StdString> coords = this->getCoordVariables(path);
    return (coords.find(name) != coords.end());
  }

  bool CINetCDF4::isRectilinear(const StdString& name, const CVarPath* const path)
  {
    std::list<StdString> varCoords = this->getCoordinatesIdList(name, path);
    std::list<StdString> varDims = this->getDimensionsList(&name, path);
    std::list<StdString>::const_iterator it = varCoords.begin(), end = varCoords.end();
    std::set<StdString> varDims1D;

    // Firstly, loop over coordinate list
    for (; it != end; it++)
    {
      const StdString& coord = *it;
      if (this->hasVariable(coord, path) && !this->isTemporal(coord, path) )
      {
        std::map<StdString, StdSize> coordDims = this->getDimensions(&coord, path);
        for (std::map<StdString, StdSize>::const_iterator itTmp = coordDims.begin(); itTmp != coordDims.end(); itTmp++)
        {
          varDims.remove(itTmp->first);
        }
        if (this->isLonOrLat(coord, path) && coordDims.size() == 1)
        {
          varDims1D.insert(coordDims.begin()->first);
          continue;
        }
      }
    }
    // Secondly, loop over remaining dimensions
    for (it= varDims.begin(); it != varDims.end(); it++)
    {
      const StdString& coord = *it;
      std::map<StdString, StdSize> coordDims = this->getDimensions(&coord, path);
      if (this->hasVariable(coord, path) && !this->isTemporal(coord, path) )
      {
        if (this->isLonOrLat(coord, path) && coordDims.size() == 1)
        {
          varDims1D.insert(coordDims.begin()->first);
          continue;
        }
      }
    }

    return (varDims1D.size() == 2);
  }

  bool CINetCDF4::isCurvilinear(const StdString& name, const CVarPath* const path)
  {
    if (this->isRectilinear(name, path) || !this->hasCoordinates(name, path))
      return false;

    bool isCurVi = true;
    unsigned int nbLonLat = 0;
    std::list<StdString> coords = this->getCoordinatesIdList(name, path);
    std::list<StdString>::const_iterator it = coords.begin(), end = coords.end();
    for (; it != end; it++)
    {
      const StdString& coord = *it;
      if (this->hasVariable(coord, path) && !this->isTemporal(coord, path) && this->isLonOrLat(coord, path))
      {
        std::map<StdString, StdSize> dimvar = this->getDimensions(&coord, path);
        if (2 == dimvar.size()) ++nbLonLat;
      }
    }
    if (2 != nbLonLat) isCurVi = false;

    return isCurVi;
  }

  bool CINetCDF4::isUnstructured(const StdString& name, const CVarPath* const path)
  {
    if (this->isRectilinear(name, path) ||
        this->isCurvilinear(name, path) ||
        !this->hasCoordinates(name, path))
       return false;
    else return true ;
    
// check this part above    
    StdString dimname = this->getDimensionsList(&name, path).back();

    std::list<StdString> coords = this->getCoordinatesIdList(name, path);
    std::list<StdString>::const_iterator it = coords.begin(), end = coords.end();
    for (; it != end; it++)
    {
      const StdString& coord = *it;
      if (this->hasVariable(coord, path) && !this->isTemporal(coord, path) && this->isLonOrLat(coord, path))
      {
        std::map<StdString, StdSize> dimvar = this->getDimensions(&coord, path);
        if ((dimvar.size() == 1) &&
            (dimvar.find(dimname) != dimvar.end()))
          continue;
        else
          return false;
      }
    }

    return true;
  }

  bool CINetCDF4::isUnknown(const StdString& name, const CVarPath* const path)
  {
    return !(this->isRectilinear(name, path) || this->isCurvilinear(name, path) || this->isUnstructured(name, path));
  }

  bool CINetCDF4::isTemporal(const StdString& name, const CVarPath* const path)
  {
    std::list<StdString> dims = this->getDimensionsList(&name, path);
    return (std::find(dims.begin(), dims.end(), timeCounterName) != dims.end());
  }

  bool CINetCDF4::is3Dim(const StdString& name, const CVarPath* const path)
  {
    int i = 0;
    std::list<StdString> coords = this->getCoordinatesIdList(name, path);
    std::list<StdString>::const_iterator it = coords.begin(), end = coords.end();
    for (; it != end; it++)
    {
      const StdString& coord = *it;
      if (this->hasVariable(coord, path))
      {
        if (this->isTemporal(coord, path))
          continue;
        i++;
      }
      else
      {
        StdString unlimitedDimName = this->getUnlimitedDimensionName();
        if (coord.compare(0, unlimitedDimName.size(), unlimitedDimName) == 0)
          continue;
        i++;
      }
    }
    return (i == 3);
  }

  bool CINetCDF4::isCellGrid(const StdString& name, const CVarPath* const path)
  {
    if (this->isCoordinate(name, path))
    {
      return this->hasBounds(name, path);
    }
    else
    {
      std::list<StdString> coords = this->getCoordinatesIdList(name, path);
      std::list<StdString>::const_iterator it = coords.begin(), end = coords.end();
      for (; it != end; it++)
      {
        const StdString& coord = *it;
        if (this->hasVariable(coord, path))
        {
          if (this->isTemporal(coord, path))
            continue;
          if (this->isCellGrid(coord, path))
            continue;
          return false;
        }
        else
        {
          StdString unlimitedDimName = this->getUnlimitedDimensionName();
          if (coord.compare(0, unlimitedDimName.size(), unlimitedDimName) == 0)
            continue;
          return false;
        }
      }
    }

    return true;
  }

  //---------------------------------------------------------------

  std::list<StdString> CINetCDF4::getDataVariables(bool _is3D,       bool _isRecti,
                                                   bool _isCurvi,    bool _isUnstr,
                                                   bool _isCellData, bool _isTemporal,
                                                   const CVarPath* const path)
  {
    std::list<StdString> retvalue;
    std::list<StdString> allvars  = this->getVariables(path);
    std::set<StdString> allcoords = this->getCoordVariables(path);

    std::list<StdString>::const_iterator it = allvars.begin(), end = allvars.end();
    for (; it != end; it++)
    {
      const StdString& var = *it;
      if (this->isCoordinate(var, path)) continue;

      if (!_isRecti && this->isRectilinear(var, path))  continue;
      if (!_isCurvi && this->isCurvilinear(var, path))  continue;
      if (!_isUnstr && this->isUnstructured(var, path)) continue;

      if (!_isTemporal && this->isTemporal(var, path)) continue;
      if (!_is3D       && this->is3Dim(var, path))     continue;
      if (!_isCellData && this->isCellGrid(var, path)) continue;

      if (this->isUnknown(var, path)) continue;

      retvalue.push_back(var);
    }
    return retvalue;
  }

  //---------------------------------------------------------------

  void CINetCDF4::getDataInfo(const StdString& var, const CVarPath* const path, StdSize record,
                              std::vector<StdSize>& sstart, std::vector<StdSize>& scount, StdSize& array_size,
                              const std::vector<StdSize>* start /*= NULL*/, const std::vector<StdSize>* count /*= NULL*/)
  {
    std::list<StdString> dimlist = this->getDimensionsList(&var, path);
    std::map<StdString, StdSize> dimmap = this->getDimensions(&var, path);
    std::list<StdString>::iterator it = dimlist.begin();
    if (this->isTemporal(var, path))
    {
      if (record != UNLIMITED_DIM)
        sstart.push_back(record);
      else
        sstart.push_back(0);
      scount.push_back(1);
      it++;
    }
    for (int i = 0; it != dimlist.end(); it++, i++)
    {
      if (start && count)
      {
        sstart.push_back((*start)[i]);
        scount.push_back((*count)[i]);
        array_size *= (*count)[i];
      }
      else
      {
        sstart.push_back(0);
        scount.push_back(dimmap[*it]);
        array_size *= dimmap[*it];
      }
    }
  }

  template <class T>
  void CINetCDF4::getData(CArray<T, 1>& data, const StdString& var,
                          const CVarPath* const path, StdSize record)
  {
    std::vector<StdSize> start, count;
    int grpid = this->getGroup(path);
    int varid = this->getVariable(var, path);
    StdSize array_size = 1;
    this->getDataInfo(var, path, record, start, count, array_size);
    data.resize(array_size);
    CNetCdfInterface::getVaraType(grpid, varid, &start[0], &count[0], data.dataFirst());
  }

  template <>
  void CINetCDF4::getData(CArray<int, 1>& data, const StdString& var,
                          const CVarPath* const path, StdSize record);
  template <>
  void CINetCDF4::getData(CArray<double, 1>& data, const StdString& var,
                          const CVarPath* const path, StdSize record);
  template <>
  void CINetCDF4::getData(CArray<float, 1>& data, const StdString& var,
                          const CVarPath* const path, StdSize record);

  //---------------------------------------------------------------

  StdString CINetCDF4::getLonCoordName(const StdString& varname,
                                       const CVarPath* const path)
  {
    StdString lonName;
    std::list<StdString>::const_iterator itbList, itList, iteList;
    std::list<StdString> clist = this->getCoordinatesIdList(varname, path);
    itbList = clist.begin(); iteList = clist.end();
    for (itList = itbList; itList != iteList; ++itList)
    {
      if (this->hasAttribute(CCFKeywords::XIOS_CF_units, &(*itList), path))
      {
        StdString unit = this->getAttributeValue(CCFKeywords::XIOS_CF_units, &(*itList), path);
        if (CCFConvention::XIOS_CF_Longitude_units.end() != CCFConvention::XIOS_CF_Longitude_units.find(unit))
        {
          lonName = *itList;
          return lonName;
        }
      }
    }
    return lonName;
  }

  StdString CINetCDF4::getLatCoordName(const StdString& varname,
                                       const CVarPath* const path)
  {
    StdString latName;
    std::list<StdString>::const_iterator itbList, itList, iteList;
    std::list<StdString> clist = this->getCoordinatesIdList(varname, path);
    itbList = clist.begin(); iteList = clist.end();
    for (itList = itbList; itList != iteList; ++itList)
    {
      if (this->hasAttribute(CCFKeywords::XIOS_CF_units, &(*itList), path))
      {
        StdString unit = this->getAttributeValue(CCFKeywords::XIOS_CF_units, &(*itList), path);
        if (CCFConvention::XIOS_CF_Latitude_units.end() != CCFConvention::XIOS_CF_Latitude_units.find(unit))
        {
          latName = *itList;
          return latName;
        }
      }
    }
    return latName;
  }

  StdString CINetCDF4::getVertCoordName(const StdString& varname,
                                        const CVarPath* const path)
  {
    if (!this->is3Dim(varname, path)) return "";
    std::list<StdString> clist = this->getCoordinatesIdList(varname, path);
    if (this->hasCoordinates(varname, path))
      return *(++(++clist.begin()));
    else
      return *(++(++clist.rbegin()));
  }

  bool CINetCDF4::isLonOrLat(const StdString& varname, const CVarPath* const path)
  {
    if (this->hasAttribute(CCFKeywords::XIOS_CF_units, &varname, path))
    {
      StdString unit = this->getAttributeValue(CCFKeywords::XIOS_CF_units, &varname, path);
      return      (CCFConvention::XIOS_CF_Latitude_units.end() != CCFConvention::XIOS_CF_Latitude_units.find(unit)
                || CCFConvention::XIOS_CF_Longitude_units.end() != CCFConvention::XIOS_CF_Longitude_units.find(unit));
    }
    else return false ;
  }

} // namespace xios
