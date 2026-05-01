#ifndef __ONETCDF4_IMPL_HPP__
#define __ONETCDF4_IMPL_HPP__

#include "onetcdf4.hpp"
#include "netCdfInterface.hpp"
#include "timer.hpp"

namespace xios
{
  template <class T, int ndim>
  void CONetCDF4::writeData(const CArray<T, ndim>& data, const StdString & name,
                            bool collective, StdSize record,
                            const std::vector<StdSize> * start,
                            const std::vector<StdSize> * count)
  {
    int grpid = this->getCurrentGroup();
    int varid = this->getVariable(name);
    StdSize array_size = 1;
    std::vector<StdSize> sstart, scount;

    if (this->wmpi && collective)
    CNetCdfInterface::varParAccess(grpid, varid, NC_COLLECTIVE);
    if (this->wmpi && !collective)
    CNetCdfInterface::varParAccess(grpid, varid, NC_INDEPENDENT);

    CTimer::get("Files : get data infos").resume();
    this->getWriteDataInfos
    (name, record, array_size,  sstart, scount, start, count);
    CTimer::get("Files : get data infos").suspend();

    if (data.numElements() != array_size)
    {
      ERROR("CONetCDF4::writeData(...)",
      << "[ input array size = "  << data.numElements()
      << ", intern array size = " << array_size
      << " ] Invalid input data !" );
    }

    this->writeData_(grpid, varid, sstart, scount, data.dataFirst());
  }

  template <>
  void CONetCDF4::writeData(const CArray<StdString, 1>& data, const StdString & name,
                            bool collective, StdSize record,
                            const std::vector<StdSize> * start,
                            const std::vector<StdSize> * count)
  {
    int grpid = this->getCurrentGroup();
    int varid = this->getVariable(name);
    StdSize array_size = 1;
    std::vector<StdSize> sstart, scount;

    if (this->wmpi && collective)
    CNetCdfInterface::varParAccess(grpid, varid, NC_COLLECTIVE);
    if (this->wmpi && !collective)
    CNetCdfInterface::varParAccess(grpid, varid, NC_INDEPENDENT);

    CTimer::get("CONetCDF4::writeData getWriteDataInfos").resume();
    this->getWriteDataInfos(name, record, array_size,  sstart, scount, start, count);
    CTimer::get("CONetCDF4::writeData getWriteDataInfos").suspend();
 
    int dimArrayLen;
    for (int i=0; i<scount.size(); i++)
      if (scount[i] == stringArrayLen)
        dimArrayLen = i;

    if (data.numElements()*stringArrayLen != array_size)
    {
      ERROR("CONetCDF4::writeData(...)",
      << "[ input array size = "  << data.numElements()*stringArrayLen
      << ", intern array size = " << array_size
      << " ] Invalid input data !" );
    }
    char *PtrArrayStr ;
    PtrArrayStr=new char[stringArrayLen*data.numElements()] ;
    memset (PtrArrayStr,' ',stringArrayLen*data.numElements());
    size_t offset=0 ;

// pb with iterator with blitz++ string array  with recent compiler
/*
    Array<StdString,1>::const_iterator it, itb=data.begin(), ite=data.end() ;
    for(it=itb;it!=ite;++it, offset+=stringArrayLen)
    {
      it->copy(PtrArrayStr+offset,it->size()) ;
      PtrArrayStr[offset+it->size()]='\0' ;
    }
*/
     for(int i=0;i<data.numElements();i++,offset+=stringArrayLen)
     {
       data(i).copy(PtrArrayStr+offset,data(i).size()) ;
       PtrArrayStr[offset+data(i).size()]='\0' ;
     } 
     CTimer::get("CONetCDF4::writeData writeData_").resume();
     this->writeData_(grpid, varid, sstart, scount, PtrArrayStr);
     CTimer::get("CONetCDF4::writeData writeData_").suspend();

    delete []  PtrArrayStr;
  }

//----------------------------------------------------------------

  template <class T>
  void CONetCDF4::setDefaultValue(const StdString & varname, const T * value)
  {
    int grpid = this->getCurrentGroup();
    int varid = this->getVariable(varname);

    if (value != NULL)
    {
      // nc_def_var_fill will automatically set the _FillValue attribute when
      // using the NetCDF 4 format but we need to do it manually otherwise
      if (useClassicFormat)
        this->addAttribute(StdString("_FillValue"), *value, &varname);
      else
        CNetCdfInterface::defVarFill(grpid, varid, 0, (void*)value);
      this->addAttribute(StdString("missing_value"), *value, &varname);
    }
    else if (!useClassicFormat)
    {
      // The "no-fill mode" is set globally for the classic NetCDF format
      CNetCdfInterface::defVarFill(grpid, varid, 1, NULL);
    }
  }

  ///---------------------------------------------------------------

}



#endif
