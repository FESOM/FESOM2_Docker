#include <fstream>

#include "onetcdf4.hpp"
#include "group_template.hpp"
#include "mpi.hpp"
#include "netcdf.hpp"
#include "netCdfInterface.hpp"
#include "netCdfException.hpp"
#include "timer.hpp"

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///

      CONetCDF4::CONetCDF4(const StdString& filename, bool append, bool useClassicFormat,
							bool useCFConvention,
                           const MPI_Comm* comm, bool multifile, const StdString& timeCounterName)
        : path()
        , wmpi(false)
        , useClassicFormat(useClassicFormat)
        , useCFConvention(useCFConvention)
      {
         this->initialize(filename, append, useClassicFormat, useCFConvention, comm, multifile, timeCounterName);
      }

      //---------------------------------------------------------------

      CONetCDF4::~CONetCDF4(void)
      {
      }

      ///--------------------------------------------------------------

      void CONetCDF4::initialize(const StdString& filename, bool append, bool useClassicFormat, bool useCFConvention, 
                                 const MPI_Comm* comm, bool multifile, const StdString& timeCounterName)
      {
         this->useClassicFormat = useClassicFormat;
         this->useCFConvention = useCFConvention;

         int mode = useClassicFormat ? 0 : NC_NETCDF4;

         // Don't use parallel mode if there is only one process
         if (comm)
         {
            int commSize = 0;
            MPI_Comm_size(*comm, &commSize);
            if (commSize <= 1)
               comm = NULL;
         }
         wmpi = comm && !multifile;

         if (wmpi)
            mode |= useClassicFormat ? NC_PNETCDF : NC_MPIIO;

         // If the file does not exist, we always create it
         if (!append || !std::ifstream(filename.c_str()))
         {
            CTimer::get("Files : create").resume();
            if (wmpi)
               CNetCdfInterface::createPar(filename, mode, *comm, MPI_INFO_NULL, this->ncidp);
            else
               CNetCdfInterface::create(filename, mode, this->ncidp);
            CTimer::get("Files : create").suspend();
 
            this->appendMode = false;
         }
         else
         {
            mode |= NC_WRITE;
            CTimer::get("Files : open").resume();
            if (wmpi)
               CNetCdfInterface::openPar(filename, mode, *comm, MPI_INFO_NULL, this->ncidp);
            else
               CNetCdfInterface::open(filename, mode, this->ncidp);
            CTimer::get("Files : open").suspend();
            this->appendMode = true;
         }

         // If the classic NetCDF format is used, we enable the "no-fill mode" globally.
         // This is done per variable for the NetCDF4 format.
         if (useClassicFormat)
            CNetCdfInterface::setFill(this->ncidp, false);

         this->timeCounterName = timeCounterName;
      }

      void CONetCDF4::close()
      {
        CTimer::get("Files : close").resume();
        CNetCdfInterface::close(this->ncidp);
        CTimer::get("Files : close").suspend();
      }

      //---------------------------------------------------------------

      void CONetCDF4::definition_start(void)
      {
         CNetCdfInterface::reDef(this->ncidp);
      }

      //---------------------------------------------------------------

      void CONetCDF4::definition_end(void)
      {
         CNetCdfInterface::endDef(this->ncidp);
      }

      //---------------------------------------------------------------

      int CONetCDF4::getCurrentGroup(void)
      {
         return this->getGroup(this->getCurrentPath());
      }

      //---------------------------------------------------------------

      int CONetCDF4::getGroup(const CONetCDF4Path& path)
      {
         int retvalue = this->ncidp;

         CONetCDF4Path::const_iterator it = path.begin(), end = path.end();

         for (; it != end; it++)
         {
            const StdString& groupid = *it;
            CNetCdfInterface::inqNcId(retvalue, groupid, retvalue);
         }
         return retvalue;
      }

      //---------------------------------------------------------------

      int CONetCDF4::getVariable(const StdString& varname)
      {
         int varid = 0;
         int grpid = this->getCurrentGroup();
         CNetCdfInterface::inqVarId(grpid, varname, varid);
         return varid;
      }

      //---------------------------------------------------------------

      int CONetCDF4::getDimension(const StdString& dimname)
      {
         int dimid = 0;
         int grpid = this->getCurrentGroup();
         CNetCdfInterface::inqDimId(grpid, dimname, dimid);
         return dimid;
      }

      //---------------------------------------------------------------

      int CONetCDF4::getUnlimitedDimension(void)
      {
         int dimid = 0;
         int grpid = this->getCurrentGroup();
         CNetCdfInterface::inqUnLimDim(grpid, dimid);
         return dimid;
      }

      StdString CONetCDF4::getUnlimitedDimensionName(void)
      {
         int grpid = this->getGroup(path);
         int dimid = this->getUnlimitedDimension();

         StdString dimname;
         if (dimid != -1)
           CNetCdfInterface::inqDimName(grpid, dimid, dimname);
         return dimname;
      }

      //---------------------------------------------------------------

      std::vector<StdSize> CONetCDF4::getDimensions(const StdString& varname)
      {
         StdSize size = 0;
         std::vector<StdSize> retvalue;
         int grpid = this->getCurrentGroup();
         int varid = this->getVariable(varname);
         int nbdim = 0, *dimid = NULL;

         CNetCdfInterface::inqVarNDims(grpid, varid, nbdim);
         dimid = new int[nbdim]();
         CNetCdfInterface::inqVarDimId(grpid, varid, dimid);

         for (int i = 0; i < nbdim; i++)
         {
            CNetCdfInterface::inqDimLen(grpid, dimid[i], size);
            if (size == NC_UNLIMITED)
                size = UNLIMITED_DIM;
            retvalue.push_back(size);
         }
         delete [] dimid;
         return retvalue;
      }

      std::vector<std::string> CONetCDF4::getDimensionsIdList(const std::string* _varname)
      {
         int nDimNull = 0;
         int nbdim = 0, *dimid = NULL;
         int grpid = this->getCurrentGroup();
         int varid = (_varname != NULL) ? this->getVariable(*_varname) : NC_GLOBAL;
         std::vector<std::string> retvalue;

         if (_varname != NULL)
         {
            CNetCdfInterface::inqVarNDims(grpid, varid, nbdim);
            dimid = new int[nbdim]();
            CNetCdfInterface::inqVarDimId(grpid, varid, dimid);
         }
         else
         {
            CNetCdfInterface::inqDimIds(grpid, nbdim, NULL, 1);
            dimid = new int[nbdim]();
            CNetCdfInterface::inqDimIds(grpid, nDimNull, dimid, 1);
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

      //---------------------------------------------------------------

      void CONetCDF4::getTimeAxisBounds(CArray<double,2>& timeAxisBounds, const StdString& name, bool collective)
      {
        int grpid = this->getCurrentGroup();
        int varid = this->getVariable(name);

        std::vector<StdSize> start(2), count(2);
        start[0] = 0;
        // Find out how many temporal records have been written already to the file we are opening
        int ncUnlimitedDimId;
        CNetCdfInterface::inqUnLimDim(this->ncidp, ncUnlimitedDimId);
        CNetCdfInterface::inqDimLen(this->ncidp, ncUnlimitedDimId, count[0]);
        start[1] = 0;
        count[1] = 2;

        timeAxisBounds.resize(count[1], count[0]);

        if (this->wmpi && collective)
          CNetCdfInterface::varParAccess(grpid, varid, NC_COLLECTIVE);
        if (this->wmpi && !collective)
          CNetCdfInterface::varParAccess(grpid, varid, NC_INDEPENDENT);

        CNetCdfInterface::getVaraType(grpid, varid, &start[0], &count[0], timeAxisBounds.dataFirst());
      }

      void CONetCDF4::getTimeAxisBounds(CArray<double,2>& timeAxisBounds, const StdString& name, bool collective, size_t record)
      {
        int grpid = this->getCurrentGroup();
        int varid = this->getVariable(name);

        std::vector<StdSize> start(2), count(2);
        start[0] = record;
        count[0] = 1 ;
        start[1] = 0;
        count[1] = 2;

        timeAxisBounds.resize(2, 1);

        if (this->wmpi && collective)
          CNetCdfInterface::varParAccess(grpid, varid, NC_COLLECTIVE);
        if (this->wmpi && !collective)
          CNetCdfInterface::varParAccess(grpid, varid, NC_INDEPENDENT);

        CNetCdfInterface::getVaraType(grpid, varid, &start[0], &count[0], timeAxisBounds.dataFirst());
      }



      const CONetCDF4::CONetCDF4Path& CONetCDF4::getCurrentPath(void) const
      { return this->path; }

      void CONetCDF4::setCurrentPath(const CONetCDF4Path& path)
      { this->path = path; }

      //---------------------------------------------------------------

      int CONetCDF4::addGroup(const StdString& name)
      {
         int retvalue = 0;
         int grpid = this->getCurrentGroup();
         CNetCdfInterface::defGrp(grpid, name, retvalue);
         return retvalue;
      }

      //---------------------------------------------------------------

      int CONetCDF4::addDimension(const StdString& name, const StdSize size)
      {
         int retvalue = 0;
         int grpid = this->getCurrentGroup();
         if (size != UNLIMITED_DIM)
            CNetCdfInterface::defDim(grpid, name, size, retvalue);
         else
            CNetCdfInterface::defDim(grpid, name, NC_UNLIMITED, retvalue);
         return retvalue;
      }

      //---------------------------------------------------------------

      int CONetCDF4::addVariable(const StdString& name, nc_type type,
                                 const std::vector<StdString>& dim, int compressionLevel)
      {
         int varid = 0;
         std::vector<int> dimids;
         std::vector<StdSize> dimsizes;
         int dimSize = dim.size();
         
         StdSize size;
         StdSize totalSize;
         // Target HDF5 chunk size: ~1 MB in elements. 1 M 4-byte floats or
         // 128 K 8-byte doubles. Keeps chunks efficient for compression filter
         // pipeline and MPI-IO coordination. The old default (256 M elements,
         // ~1-2 GB per chunk) combined with the "flatten to 1" cap below
         // produced pathological tiny chunks (e.g. (1, 1, 56) = 224 bytes for
         // FESOM ocean 3D fields), which crushed write throughput.
         StdSize maxSize = 1024 * 1024;

         int grpid = this->getCurrentGroup();

         std::vector<StdString>::const_iterator it = dim.begin(), end = dim.end();

         for (int idx = 0; it != end; it++, ++idx)
         {
            const StdString& dimid = *it;
            dimids.push_back(this->getDimension(dimid));
            CNetCdfInterface::inqDimLen(grpid, this->getDimension(dimid), size);
            if (size == NC_UNLIMITED) size = 1;
            dimsizes.push_back(size);
         }

         CNetCdfInterface::defVar(grpid, name, type, dimids.size(), &dimids[0], varid);

         // The classic NetCDF format does not support chunking nor fill parameters
         if (!useClassicFormat)
         {
            // Set chunk shape: iterate dims inner-to-outer and cap each dim
            // proportionally so the running product stays <= maxSize.
            // Previously: any dim that pushed over maxSize was flattened to 1,
            // and totalSize wasn't recomputed, cascading the flatten to all
            // outer dims.
            totalSize = 1;
            for (vector<StdSize>::reverse_iterator it = dimsizes.rbegin(); it != dimsizes.rend(); ++it)
            {
              StdSize prior = totalSize;
              totalSize *= *it;
              if (totalSize > maxSize)
              {
                StdSize cap = (prior > 0) ? (maxSize / prior) : maxSize;
                if (cap < 1) cap = 1;
                if (cap > *it) cap = *it;
                *it = cap;
                totalSize = prior * cap;
              }
            }
            int storageType = (0 == dimSize) ? NC_CONTIGUOUS : NC_CHUNKED;
            CNetCdfInterface::defVarChunking(grpid, varid, storageType, &dimsizes[0]);
            CNetCdfInterface::defVarFill(grpid, varid, true, NULL);
         }

         setCompressionLevel(name, compressionLevel) ;
         
         return varid;
      }

      //---------------------------------------------------------------

      void CONetCDF4::setCompressionLevel(const StdString& varname, int compressionLevel)
      {
         if (compressionLevel < 0 || compressionLevel > 9)
           ERROR("void CONetCDF4::setCompressionLevel(const StdString& varname, int compressionLevel)",
                 "Invalid compression level for variable \"" << varname << "\", the value should range between 0 and 9.");
         // Parallel-compressed collective writes require netCDF >= 4.7.4 and HDF5 >= 1.10.3.
         // Levante has netCDF 4.8.1 + HDF5 1.12.1 (has_parallel4=yes), so allow compression in parallel mode.

         int grpid = this->getCurrentGroup();
         int varid = this->getVariable(varname);
         CNetCdfInterface::defVarDeflate(grpid, varid, compressionLevel);
      }

      //---------------------------------------------------------------

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const StdString& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, value.size(), value.c_str());
      }

      //---------------------------------------------------------------

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const double& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, 1, &value);
      }

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const CArray<double,1>& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, value.numElements(), value.dataFirst());
      }
      //---------------------------------------------------------------

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const float& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, 1, &value);
      }

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const CArray<float,1>& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, value.numElements(), value.dataFirst());
      }

      //---------------------------------------------------------------

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const int& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, 1, &value);
      }

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const CArray<int,1>& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, value.numElements(), value.dataFirst());
      }

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const short int& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, 1, &value);
      }

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const CArray<short int,1>& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, value.numElements(), value.dataFirst());
      }

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const long int& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, 1, &value);
      }

      template <>
      void CONetCDF4::addAttribute(const StdString& name, const CArray<long int,1>& value, const StdString* varname)
      {
         int grpid = this->getCurrentGroup();
         int varid = (varname == NULL) ? NC_GLOBAL : this->getVariable(*varname);
         CNetCdfInterface::putAttType(grpid, varid, name, value.numElements(), value.dataFirst());
      }

      //---------------------------------------------------------------

      void CONetCDF4::getWriteDataInfos(const StdString& name, StdSize record, StdSize& array_size,
                                        std::vector<StdSize>& sstart,
                                        std::vector<StdSize>& scount,
                                        const std::vector<StdSize>* start,
                                        const std::vector<StdSize>* count)
      {
         std::vector<std::size_t> sizes  = this->getDimensions(name);
         if (sizes.size()==0) 
         {
            array_size=1 ;
            sstart.push_back(0);
            scount.push_back(1);
         }
         else
         {
           std::vector<std::string> iddims = this->getDimensionsIdList (&name);
           std::vector<std::size_t>::const_iterator
           it  = sizes.begin(), end = sizes.end();
           int i = 0;

           if (iddims.begin()->compare(timeCounterName) == 0)
           {
             sstart.push_back(record);
             scount.push_back(1);
              if ((start == NULL) &&
                  (count == NULL)) i++;
              it++;
           }

           for (;it != end; it++)
           {
              if ((start != NULL) && (count != NULL))
              {
                 sstart.push_back((*start)[i]);
                 scount.push_back((*count)[i]);
                 array_size *= (*count)[i];
                 i++;
              }
              else
              {
                 sstart.push_back(0);
                 scount.push_back(sizes[i]);
                 array_size *= sizes[i];
                 i++;
              }
           }

         }
      }


      template <>
      void CONetCDF4::writeData_(int grpid, int varid,
                                 const std::vector<StdSize>& sstart,
                                 const std::vector<StdSize>& scount, const double* data)
      {
         CNetCdfInterface::putVaraType(grpid, varid, &sstart[0], &scount[0], data);
      }

      //---------------------------------------------------------------

      template <>
      void CONetCDF4::writeData_(int grpid, int varid,
                                 const std::vector<StdSize>& sstart,
                                 const std::vector<StdSize>& scount, char* data)
      {
          CNetCdfInterface::putVaraType(grpid, varid, &sstart[0], &scount[0], data);
      }

      template <>

      void CONetCDF4::writeData_(int grpid, int varid,
                                 const std::vector<StdSize>& sstart,
                                 const std::vector<StdSize>& scount, const int* data)
      {
          CNetCdfInterface::putVaraType(grpid, varid, &sstart[0], &scount[0], data);
      }
      //---------------------------------------------------------------

      template <>
      void CONetCDF4::writeData_(int grpid, int varid,
                                 const std::vector<StdSize>& sstart,
                                 const std::vector<StdSize>& scount, const float* data)
      {
          CNetCdfInterface::putVaraType(grpid, varid, &sstart[0], &scount[0], data);
      }

      //---------------------------------------------------------------

      void CONetCDF4::writeData(const CArray<int, 2>& data, const StdString& name)
      {
         int grpid = this->getCurrentGroup();
         int varid = this->getVariable(name);
         StdSize array_size = 1;
         std::vector<StdSize> sstart, scount;

         this->getWriteDataInfos(name, 0, array_size,  sstart, scount, NULL, NULL);

         this->writeData_(grpid, varid, sstart, scount, data.dataFirst());

      }

      void CONetCDF4::writeTimeAxisData(const CArray<double, 1>& data, const StdString& name,
                                        bool collective, StdSize record, bool isRoot)
      {
         int grpid = this->getCurrentGroup();
         int varid = this->getVariable(name);

         map<int,size_t>::iterator it=timeAxis.find(varid);
         if (it == timeAxis.end()) timeAxis[varid] = record;
         else
         {
           if (it->second >= record) return;
           else it->second =record;
         }

         StdSize array_size = 1;
         std::vector<StdSize> sstart, scount;

         if (this->wmpi && collective)
            CNetCdfInterface::varParAccess(grpid, varid, NC_COLLECTIVE);
         if (this->wmpi && !collective)
            CNetCdfInterface::varParAccess(grpid, varid, NC_INDEPENDENT);

         this->getWriteDataInfos(name, record, array_size,  sstart, scount, NULL, NULL);
         this->writeData_(grpid, varid, sstart, scount, data.dataFirst());
       }

      void CONetCDF4::writeTimeAxisDataBounds(const CArray<double, 1>& data, const StdString& name,
                                        bool collective, StdSize record, bool isRoot)
      {
         int grpid = this->getCurrentGroup();
         int varid = this->getVariable(name);

         map<int,size_t>::iterator it=timeAxis.find(varid);
         if (it == timeAxis.end()) timeAxis[varid] = record;
         else
         {
           if (it->second >= record) return;
           else it->second =record;
         }

         StdSize array_size = 1;
         std::vector<StdSize> sstart, scount;

         if (this->wmpi && collective)
            CNetCdfInterface::varParAccess(grpid, varid, NC_COLLECTIVE);
         if (this->wmpi && !collective)
            CNetCdfInterface::varParAccess(grpid, varid, NC_INDEPENDENT);

         this->getWriteDataInfos(name, record, array_size,  sstart, scount, NULL, NULL);
         this->writeData_(grpid, varid, sstart, scount, data.dataFirst());
       }


      //---------------------------------------------------------------

      bool CONetCDF4::varExist(const StdString& varname)
      {
         int grpid = this->getCurrentGroup();
         return CNetCdfInterface::isVarExisted(grpid, varname);
      }

      bool CONetCDF4::dimExist(const StdString& dimname)
      {
         int grpid = this->getCurrentGroup();
         return CNetCdfInterface::isDimExisted(grpid, dimname);
      }

      void CONetCDF4::sync(void)
      {
         CNetCdfInterface::sync(this->ncidp);
      }
      ///--------------------------------------------------------------
 } // namespace xios
