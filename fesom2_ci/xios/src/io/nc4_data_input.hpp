#ifndef __XIOS_NC4_DATA_INPUT__
#define __XIOS_NC4_DATA_INPUT__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "data_input.hpp"
#include "inetcdf4.hpp"

namespace xios
{
  class CDomain;
  class CAxis;
  class CScalar;

  class CNc4DataInput
    : protected CINetCDF4
    , public virtual CDataInput
  {
  public:
    /// Type definitions ///
    typedef CINetCDF4  SuperClassWriter;
    typedef CDataInput SuperClass;

    /// Constructors ///
    CNc4DataInput(const StdString& filename, MPI_Comm comm_file, bool multifile, bool isCollective = true,
                  bool readMetaDataPar = false, bool ugridConvention = false, const StdString& timeCounterName = "time_counter");
    CNc4DataInput(const CNc4DataInput& dataInput);       // Not implemented.
    CNc4DataInput(const CNc4DataInput* const dataInput); // Not implemented.

    /// Destructor ///
    virtual ~CNc4DataInput(void);

    /// Getters ///
    const StdString& getFileName(void) const;

  protected:
    // Read methods
    virtual StdSize getFieldNbRecords_(CField* field);
    virtual void readFieldData_(CField* field);
    virtual void readFieldAttributes_(CField* field, bool readAttributeValues);
    virtual void closeFile_(void);

  private:
    void readDomainAttributesFromFile(CDomain* domain, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                      int elementPosition, const StdString& fieldId);
    void readDomainAttributeValueFromFile(CDomain* domain, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                          int elementPosition, const StdString& fieldId);

    void readAxisAttributesFromFile(CAxis* axis, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                    int elementPosition, const StdString& fieldId);
    void readAxisAttributeValueFromFile(CAxis* axis, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                        int elementPosition, const StdString& fieldId);

    void readScalarAttributesFromFile(CScalar* scalar, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                      int elementPosition, const StdString& fieldId);
    void readScalarAttributeValueFromFile(CScalar* scalar, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                          int elementPosition, const StdString& fieldId);

    template <typename T, int Ndim>
    void readFieldVariableValue(CArray<T, Ndim>& var, const StdString& varId,
                                const std::vector<StdSize>& nBegin,
                                const std::vector<StdSize>& nSize,
                                bool forceIndependent = false);

  private:
    std::set<StdString> readMetaDataDomains_, readValueDomains_;
    std::set<StdString> readMetaDataAxis_, readValueAxis_;
    std::set<StdString> readMetaDataScalar_, readValueScalar_;

  private:
    /// Private attributes ///
    MPI_Comm comm_file;
    const StdString filename;
    bool isCollective;
    bool ugridConvention;
  }; // class CNc4DataInput

template <typename T, int Ndim>
void CNc4DataInput::readFieldVariableValue(CArray<T,Ndim>& var, const StdString& varId,
                                           const std::vector<StdSize>& nBegin,
                                           const std::vector<StdSize>& nSize,
                                           bool forceIndependent)
{
  if (SuperClass::type==MULTI_FILE || !isCollective) return;

  bool openCollective = isCollective;
  if (forceIndependent) openCollective = !isCollective;
  switch (SuperClass::type)
  {
    case MULTI_FILE:
      ERROR("CINetCDF4::readFieldVariableValue(...)",
            << "Only support attributes reading with one_file mode");
      break;
    case ONE_FILE:
    {
      SuperClassWriter::getData(var, varId, openCollective, 0, &nBegin, &nSize);
      break;
    }
  }
}
} // namespace xios

#endif //__XIOS_NC4_DATA_INPUT__
