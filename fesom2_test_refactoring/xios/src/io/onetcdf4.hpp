#ifndef __XIOS_ONETCDF4__
#define __XIOS_ONETCDF4__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "data_output.hpp"
#include "array_new.hpp"
#include "mpi.hpp"
#include "netcdf.hpp"

#ifndef UNLIMITED_DIM
   #define UNLIMITED_DIM (size_t)(-1)
#endif  //UNLIMITED_DIM

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
      class CONetCDF4
         : public virtual CDataOutput
      {
         public :

            /// Définition de type ///
            typedef std::vector<StdString> CONetCDF4Path;

            /// Constructeurs ///
            CONetCDF4(const StdString& filename, bool append, bool useClassicFormat = false,
            		  bool useCFConvention = true,
                      const MPI_Comm* comm = NULL, bool multifile = true,
                      const StdString& timeCounterName = "time_counter");

            CONetCDF4(const CONetCDF4& onetcdf4);       // Not implemented.
            CONetCDF4(const CONetCDF4* const onetcdf4); // Not implemented.


            /// Initialisation ///
            void initialize(const StdString& filename, bool append, bool useClassicFormat, bool useCFConvention,
                            const MPI_Comm* comm, bool multifile, const StdString& timeCounterName);
            void close(void);
            void sync(void);
            void definition_start(void);
            void definition_end(void);

            /// Mutateurs ///
            void setCurrentPath(const CONetCDF4Path& path);

            int addGroup(const StdString& name);
            int addDimension(const StdString& name, const StdSize size = UNLIMITED_DIM);
            int addVariable(const StdString& name, nc_type type,
                            const std::vector<StdString>& dim, int compressionLevel=0);

      //----------------------------------------------------------------
         public :

            template <class T>
               void setDefaultValue(const StdString& varname, const T* value = NULL);

            void setCompressionLevel(const StdString& varname, int compressionLevel);

            template <class T>  void addAttribute (const StdString& name, const T& value, const StdString* varname = NULL);

            /// Ecriture des données ///
            template <class T, int ndim>
               void writeData(const CArray<T,ndim>& data, const StdString& name,
                              bool collective, StdSize record,
                              const std::vector<StdSize>* start = NULL,
                              const std::vector<StdSize>* count = NULL);

            void writeData(const CArray<int, 2>& data, const StdString& name);
            void writeTimeAxisData(const CArray<double,1>& data, const StdString& name,
                                   bool collective, StdSize record, bool Isroot);
            void writeTimeAxisDataBounds(const CArray<double,1>& data, const StdString& name,
                                   bool collective, StdSize record, bool Isroot);
            /// Accesseur ///
            const CONetCDF4Path& getCurrentPath(void) const;

            /// Destructeur ///
            virtual ~CONetCDF4(void);

      //----------------------------------------------------------------

         protected :

            /// Ecriture ///
            virtual void writeField_ (CField*  field)  = 0;
            virtual void writeDomain_(CDomain* domain) = 0;
            virtual void writeAxis_  (CAxis*   axis)   = 0;

            /// Accesseurs ///
            int getCurrentGroup(void);
            int getGroup(const CONetCDF4Path& path);
            int getVariable(const StdString& varname);
            int getDimension(const StdString& dimname);
            std::vector<StdSize>   getDimensions       (const StdString& varname);
            std::vector<StdString> getDimensionsIdList (const StdString* varname);
            int       getUnlimitedDimension(void);
            StdString getUnlimitedDimensionName(void);
            const StdString& getTimeCounterName(void) const { return timeCounterName; };

            void getTimeAxisBounds(CArray<double,2>& timeAxisBounds, const StdString& name, bool collective );
            void getTimeAxisBounds(CArray<double,2>& timeAxisBounds, const StdString& name, bool collective, size_t record);

            bool varExist(const StdString& varname);
            bool dimExist(const StdString& dimname);

            bool useClassicFormat; //!< If true, NetCDF4 will use the classic NetCDF3 format
            bool useCFConvention;  //!< If true data is written in the CF convention otherwise in UGRID

      //----------------------------------------------------------------

         private :
            template <class T>
            void writeData_(int grpid, int varid,
                            const std::vector<StdSize>& sstart,
                            const std::vector<StdSize>& scount, T* data);

            void getWriteDataInfos(const StdString& name, StdSize record, StdSize& array_size,
                                   std::vector<StdSize>& sstart,
                                   std::vector<StdSize>& scount,
                                   const std::vector<StdSize>* start,
                                   const std::vector<StdSize>* count);

            /// Propriétés privées ///
            CONetCDF4Path path;
            int ncidp;
            bool wmpi;
            map<int,size_t> timeAxis;
            StdString timeCounterName;
      }; // class CONetCDF4

      ///---------------------------------------------------------------



} // namespace xios

#endif //__XIOS_ONETCDF4__
