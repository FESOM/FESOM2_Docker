#ifndef __XIOS_DATA_INPUT__
#define __XIOS_DATA_INPUT__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "field.hpp"


namespace xios
{
  class CDataInput
  {
    public:
      /// Input type ///
      typedef enum { ONE_FILE = 0, MULTI_GROUP, MULTI_FILE } EDataInputType;

      /// Read methods ///
      StdSize getFieldNbRecords(CField* field);
      void readFieldData(CField* field);
      void readFieldAttributesMetaData(CField* field);
      void readFieldAttributesValues(CField* field);
      void closeFile(void);

      virtual ~CDataInput(void);

    protected:
      virtual StdSize getFieldNbRecords_(CField* field) = 0;
      virtual void readFieldData_(CField* field) = 0;
      virtual void readFieldAttributes_(CField* field, bool readAttributeValues) = 0;
      virtual void closeFile_(void) = 0;

      /// Protected properties ///
      EDataInputType type;
  }; // class CDataInput
} // namespace xios

#endif //__XIOS_DATA_INPUT__
