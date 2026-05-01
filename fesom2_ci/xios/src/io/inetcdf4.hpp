#ifndef __XIOS_INETCDF4__
#define __XIOS_INETCDF4__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "array_new.hpp"

#include "mpi.hpp"
#include "netcdf.hpp"

#ifndef UNLIMITED_DIM
#define UNLIMITED_DIM (size_t)(-1)
#endif  // UNLIMITED_DIM

namespace xios
{
  typedef std::vector<StdString> CVarPath;

  class CINetCDF4
  {
    public:
      /// Constructors ///
      CINetCDF4(const StdString& filename, const MPI_Comm* comm = NULL, bool multifile = true,
                bool readMetaDataPar = false, const StdString& timeCounterName = "time_counter");

      CINetCDF4(const CINetCDF4& inetcdf4);       // Not implemented.
      CINetCDF4(const CINetCDF4* const inetcdf4); // Not implemented.

      //-------------------------------------------------------------

      /// Destructor ///
      virtual ~CINetCDF4(void);

      //-------------------------------------------------------------

      void close(void);

      //-------------------------------------------------------------

      /// Getters ///

      StdString getUnlimitedDimensionName(const CVarPath* const path = NULL);

      const StdString& getTimeCounterName(void) const { return timeCounterName; };

      StdString getCoordinatesId(const StdString& name, const CVarPath* const path = NULL);

      StdString getBoundsId(const StdString& name, const CVarPath* const path = NULL);

      StdString getLonCoordName(const StdString& varname, const CVarPath* const path = NULL);
      StdString getLatCoordName(const StdString& varname, const CVarPath* const path = NULL);
      StdString getVertCoordName(const StdString& varname, const CVarPath* const path = NULL);

      std::set<StdString> getCoordVariables(const CVarPath* const path = NULL);
      std::set<StdString> getBoundVariables(const CVarPath* const path = NULL);

      std::list<StdString> getGroups   (const CVarPath* const path = NULL);
      std::list<StdString> getVariables(const CVarPath* const path = NULL);

      std::list<StdString> getDataVariables(bool _is3D       = true,
                                            bool _isRecti    = true,
                                            bool _isCurvi    = true,
                                            bool _isUnstr    = true,
                                            bool _isCellData = true,
                                            bool _isTemporal = true,
                                            const CVarPath* const path = NULL);

      std::list<StdString> getAttributes(const StdString* const var  = NULL,
                                         const CVarPath* const path = NULL);

      std::list<StdString> getDimensionsList(const StdString* const var  = NULL,
                                             const CVarPath* const path = NULL);

      std::list<StdString> getCoordinatesIdList(const StdString& name,
                                                const CVarPath* const path = NULL);

      std::map<StdString, StdSize> getDimensions(const StdString* const var  = NULL,
                                                 const CVarPath* const path = NULL);

      StdSize getNbVertex(const StdString& name, const CVarPath* const path = NULL);

      //-------------------------------------------------------------

      template <class T>
      T getMissingValue(const StdString& name, const CVarPath* const path = NULL);

      template <class T>
      std::vector<T> getAttributeValue(const StdString& name,
                                       const StdString* const var  = NULL,
                                       const CVarPath* const path = NULL);

      StdString getAttributeValue(const StdString& name,
                                  const StdString* const var,
                                  const CVarPath* const path);

      template <class T>
      void getData(CArray<T, 1>& data,
                   const StdString& var,
                   const CVarPath* const path = NULL,
                   StdSize record = UNLIMITED_DIM);

      template <class T, int Ndim>
      void getData(CArray<T, Ndim>& data, const StdString& var,
                   bool collective, StdSize record,
                   const std::vector<StdSize>* start = NULL,
                   const std::vector<StdSize>* count = NULL);

      //-------------------------------------------------------------

      /// Tests ///
      bool hasMissingValue(const StdString& name, const CVarPath* const path = NULL);
      bool hasAttribute(const StdString& name, const StdString* const var  = NULL, const CVarPath* const path = NULL);
      
      template <class T>
      bool hasAttribute(const StdString& name, const StdString* const var  = NULL, const CVarPath* const path = NULL);

      bool hasVariable(const StdString& name, const CVarPath* const path = NULL);

      bool hasCoordinates(const StdString& name, const CVarPath* const path = NULL);

      bool hasTemporalDim(const CVarPath* const path = NULL);

      bool hasBounds(const StdString& name, const CVarPath* const path = NULL);

      //-------------------------------------------------------------

      bool isBound(const StdString& name, const CVarPath* const path = NULL);
      bool isCoordinate(const StdString& name, const CVarPath* const path = NULL);
      bool isRectilinear(const StdString& name, const CVarPath* const path = NULL);
      bool isCurvilinear(const StdString& name, const CVarPath* const path = NULL);
      bool isUnknown(const StdString& name, const CVarPath* const path = NULL);
      bool isUnstructured(const StdString& name, const CVarPath* const path = NULL);

      bool isTemporal(const StdString& name, const CVarPath* const path = NULL);
      bool is3Dim(const StdString& name, const CVarPath* const path = NULL);
      bool isCellGrid(const StdString& name, const CVarPath* const path = NULL);

      bool isLonOrLat(const StdString& varname, const CVarPath* const path = NULL);

    protected:
      /// Getters ///
      int getGroup   (const CVarPath* const path = NULL);
      int getVariable(const StdString& varname, const CVarPath* const path = NULL);
      int getDimension(const StdString& dimname, const CVarPath* const path = NULL);
      int getUnlimitedDimension(const CVarPath* const path = NULL);
      bool hasUnlimitedDimension(const CVarPath* const path = NULL);

      int getAttributeId(const StdString& name,
                         const StdString* const var = NULL,
                         const CVarPath* const path = NULL);

      std::pair<nc_type , StdSize> getAttribute(const StdString& attname,
                                                const StdString* const var  = NULL,
                                                const CVarPath* const path = NULL);

      //-------------------------------------------------------------

      void getDataInfo(const StdString& var, const CVarPath* const path, StdSize record,
                       std::vector<StdSize>& sstart, std::vector<StdSize>& scount, StdSize& array_size,
                       const std::vector<StdSize>* start = NULL, const std::vector<StdSize>* count = NULL);

    private:
      int ncidp; //< Id of the NetCDF file
      bool mpi;  //< Whether parallel file access is used
      StdString timeCounterName;
  }; // class CINetCDF4
} // namespace xios

#endif //__XIOS_INETCDF4__
