#ifndef __XIOS_DATA_OUTPUT__
#define __XIOS_DATA_OUTPUT__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "grid.hpp"
#include "field.hpp"


namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
      class CDataOutput
      {
         public :

            /// Définition de type ///
            typedef enum { ONE_FILE = 0, MULTI_GROUP, MULTI_FILE } EDataOutputType;

            /// Ecriture ///
            void writeFile     (CFile*     file);
            void writeAttribute(CVariable* var);
            void syncFile      (void);
            void closeFile     (void);
            void writeField    (CField* field);
            void writeFieldTimeAxis(CField* field) ;
            void writeFieldGrid(CField* field);
            void writeTimeDimension(void);
            void writeFieldData(CField* field);

            virtual void definition_start(void) = 0;
            virtual void definition_end(void)   = 0;

            //!< Test if the file was opened in append mode
            virtual bool IsInAppendMode() const { return appendMode; };

            virtual ~CDataOutput(void);

         protected:

            /// Ecriture ///
            void writeGrid(CGrid* grid, bool allowCompressedOutput = false);
            void writeGrid(CDomain* domain, CAxis* axis);
            void writeGrid(CDomain* domain);
            void writeGrid(std::vector<CDomain*> domain, std::vector<CAxis*> axis);
            void writeGrid(std::vector<CDomain*> domains, std::vector<CAxis*> axis, std::vector<CScalar*> scalars);

            virtual void writeFile_     (CFile*      file)   = 0;
            virtual void writeAttribute_(CVariable*  var)    = 0;
            virtual void closeFile_     (void)               = 0;
            virtual void syncFile_      (void)               = 0;
            virtual void writeField_    (CField*     field)  = 0;
            virtual void writeFieldData_(CField*     field)  = 0;
            virtual void writeDomain_   (CDomain*    domain) = 0;
            virtual void writeAxis_     (CAxis*      axis)   = 0;
            virtual void writeScalar_   (CScalar*    scalar) = 0;
            virtual void writeGridCompressed_(CGrid* grid)   = 0;
            virtual void writeTimeDimension_(void)           = 0;
            virtual void writeTimeAxis_ (CField*     field,
                                         const std::shared_ptr<CCalendar> cal) = 0;

            /// Propriétés protégées ///
            EDataOutputType type;
            bool appendMode; //!< If true, we are appending data to an existing file

      }; // class CDataOutput

} // namespace xios

#endif //__XIOS_DATA_OUTPUT__
