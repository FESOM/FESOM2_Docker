#ifndef __XIOS_NC4_DATA_OUTPUT__
#define __XIOS_NC4_DATA_OUTPUT__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "onetcdf4.hpp"
#include "data_output.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///

      class CNc4DataOutput
         : protected CONetCDF4
         , public virtual CDataOutput
      {
         public :

            /// Définition de type ///
            typedef CONetCDF4   SuperClassWriter;
            typedef CDataOutput SuperClass;

            /// Constructeurs ///
            CNc4DataOutput
               (CFile* file, const StdString & filename, bool exist);
            CNc4DataOutput
               (CFile* file, const StdString & filename, bool exist, bool useClassicFormat,
                bool useCFConvention,
                MPI_Comm comm_file, bool multifile, bool isCollective = true,
                const StdString& timeCounterName = "time_counter");

            CNc4DataOutput(const CNc4DataOutput & dataoutput);       // Not implemented.
            CNc4DataOutput(const CNc4DataOutput * const dataoutput); // Not implemented.
            
            /// Accesseur ///
            const StdString & getFileName(void) const;

            /// Destructeur ///
            virtual ~CNc4DataOutput(void);
            
            bool singleDomain ;
            bool isCollective ;
            int compressionLevel ;
                      
            CFile* file;
                      
         protected :

            /// Ecriture ///
            virtual void writeDomain_   (CDomain* domain);
            virtual void writeAxis_     (CAxis* axis);
            virtual void writeScalar_   (CScalar* scalar);
            virtual void writeGridCompressed_(CGrid* grid);
            virtual void writeTimeDimension_(void);
            virtual void writeField_    (CField* field);
            virtual void writeAttribute_(CVariable* var);
            virtual void writeAttribute_(CVariable* var, const string& fieldId);
            virtual void writeFieldData_(CField* field);
            virtual void writeFile_     (CFile* file);
            virtual void closeFile_     (void);
            virtual void syncFile_      (void);
            virtual void writeTimeAxis_ (CField* field,
                                         const std::shared_ptr<CCalendar> cal);

         protected :
            void writeUnstructuredDomain (CDomain* domain);
            void writeUnstructuredDomainUgrid (CDomain* domain);
            void writeLocalAttributes(int ibegin, int ni, int jbegin, int nj, StdString domid);
            void writeLocalAttributes_IOIPSL(const StdString& dimXid, const StdString& dimYid,
                                             int ibegin, int ni, int jbegin, int nj, int ni_glo, int nj_glo, int rank, int size);
            void writeTimeAxisAttributes(const StdString & axis_name,
                                         const StdString & calendar,
                                         const StdString & units,
                                         const StdString & time_origin,
                                         const StdString & time_bounds   = StdString("bounds"),
                                         const StdString & standard_name = StdString("time"),
                                         const StdString & long_name     = StdString("Time axis"));

            void writeFileAttributes(const StdString & name,
                                     const StdString & description,
                                     const StdString & conventions,
                                     const StdString & production,
                                     const StdString & timeStamp);

            void writeMaskAttributes(const StdString & mask_name,
                                     int data_dim,
                                     int data_ni     = 0,
                                     int data_nj     = 0,
                                     int data_ibegin = 0,
                                     int data_jbegin = 0);

            void writeAxisAttributes(const StdString & axis_name,
                                     const StdString & axis,
                                     const StdString & standard_name,
                                     const StdString & long_name,
                                     const StdString & units,
                                     const StdString & nav_model);

            StdSize getRecordFromTime(Time time, double factorUnit);

         private :

            /// Traitement ///
            StdString getTimeStamp(void) const;

            bool isWrittenDomain(const std::string& domainName) const;
            bool isWrittenCompressedDomain(const std::string& domainName) const;
            bool isWrittenAxis(const std::string& axisName) const;
            bool isWrittenCompressedAxis(const std::string& axisName) const;
            bool isWrittenScalar(const std::string& scalarName) const;

            void setWrittenDomain(const std::string& domainName);
            void setWrittenCompressedDomain(const std::string& domainName);
            void setWrittenAxis(const std::string& axisName);
            void setWrittenCompressedAxis(const std::string& axisName);
            void setWrittenScalar(const std::string& scalarName);

            /// Propriétés privées ///
            MPI_Comm comm_file;
            const StdString filename;
            std::map<Time, StdSize> timeToRecordCache;

            std::set<std::string> writtenDomains, writtenCompressedDomains;
            std::set<std::string> writtenAxis, writtenCompressedAxis;
            std::set<std::string> writtenScalar;

            enum { none, centered, instant, record} timeCounterType ;
            bool hasTimeInstant ;
            bool hasTimeCentered ;
      }; // class CNc4DataOutput

} // namespace xios

#endif //__XIOS_NC4_DATA_OUTPUT__
