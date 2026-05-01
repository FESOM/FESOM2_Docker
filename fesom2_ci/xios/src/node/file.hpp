#ifndef __XIOS_CFile__
#define __XIOS_CFile__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "field.hpp"
#include "data_output.hpp"
#include "data_input.hpp"
#include "declare_group.hpp"
#include "date.hpp"
#include "attribute_enum.hpp"
#include "attribute_enum_impl.hpp"
#include "context_client.hpp"
#include "mpi.hpp"

namespace xios {

   /// ////////////////////// Déclarations ////////////////////// ///

   class CFileGroup;
   class CFileAttributes;
   class CFile;

   class CGarbageCollector;

   ///--------------------------------------------------------------

   // Declare/Define CFileAttribute
   BEGIN_DECLARE_ATTRIBUTE_MAP(CFile)
#  include "file_attribute.conf"
   END_DECLARE_ATTRIBUTE_MAP(CFile)

   ///--------------------------------------------------------------

   /*!
   \class CFile
   This class corresponds to file component of the xml.
   The class contains all the nessceary information to write data into a netcdf file: The most important thing
   is the field(s) which will be written into file. Besides, there are some options to write
   data into file, e.g: writting into only one file or multiple file; splitting a running into several files.
   Moreover, there are some other attributes of netcdf file which are also stored in this class
   */
   class CFile
      : public CObjectTemplate<CFile>
      , public CFileAttributes
   {
         /// typedef ///
         typedef CObjectTemplate<CFile>   SuperClass;
         typedef CFileAttributes SuperClassAttribute;

      public :
         enum EEventId
         {
           EVENT_ID_ADD_FIELD, EVENT_ID_ADD_FIELD_GROUP, EVENT_ID_ADD_VARIABLE,
           EVENT_ID_ADD_VARIABLE_GROUP, EVENT_ID_CREATE_ENABLED_FIELDS
         };

         typedef CFileAttributes RelAttributes;
         typedef CFileGroup      RelGroup;

         /// Constructeurs ///
         CFile(void);
         explicit CFile(const StdString& id);
         CFile(const CFile& file);       // Not implemented yet.
         CFile(const CFile* const file); // Not implemented yet.

         /// Destructeur ///
         virtual ~CFile(void);

      public:
         /// Accesseurs ///
         const StdString getFileOutputName(void) const;
         std::shared_ptr<CDataOutput> getDataOutput(void) const;
         std::shared_ptr<CDataInput> getDataInput(void) const;
         CFieldGroup* getVirtualFieldGroup(void) const;
         CVariableGroup* getVirtualVariableGroup(void) const;
         std::vector<CField*> getAllFields(void) const;
         std::vector<CVariable*> getAllVariables(void) const;

         std::vector<CField* > getEnabledFields(int default_outputlevel = 5,
                                                int default_level = 1,
                                                bool default_enabled = true);

         StdString dumpClassAttributes(void);

      public :
         // Some functions to verify state of file
         bool isSyncTime(void);
         bool checkSplit(void);
         bool checkSync(void);
         void checkWriteFile(void);
         void checkReadFile(void);
         void initWrite(void);
         void initRead(void);
         bool isEmptyZone();

         /// Mutateurs ///
         // Set some root definitions in a file
         void setVirtualFieldGroup(CFieldGroup* newVFieldGroup);
         void setVirtualVariableGroup(CVariableGroup* newVVariableGroup);

         void createHeader(void);
         void openInReadMode(void);
         void close(void);
         void readAttributesOfEnabledFieldsInReadMode();

         // Some processing on file
         void solveFieldRefInheritance(bool apply);
         void processEnabledFile(void);
         void solveOnlyRefOfEnabledFields(bool sendToServer);
         void generateNewTransformationGridDest();
         
         void buildFilterGraphOfEnabledFields(CGarbageCollector& gc);
         void postProcessFilterGraph();
         void prefetchEnabledReadModeFields();
         void doPreTimestepOperationsForEnabledReadModeFields();
         void doPostTimestepOperationsForEnabledReadModeFields();

         void solveAllRefOfEnabledFieldsAndTransform(bool sendToServer);
         void checkGridOfEnabledFields();
         void sendGridOfEnabledFields();
         void sendGridComponentOfEnabledFields();

         void sortEnabledFieldsForUgrid();

         // Add component into file
         CField* addField(const string& id = "");
         CFieldGroup* addFieldGroup(const string& id = "");
         CVariable* addVariable(const string& id = "");
         CVariableGroup* addVariableGroup(const string& id = "");
         void setContextClient(CContextClient* newContextClient);
         CContextClient* getContextClient();

         void setReadContextClient(CContextClient* newContextClient);
         CContextClient* getReadContextClient();

         // Send info to server         
         void sendEnabledFields(CContextClient* client);         
         void sendAddField(const string& id, CContextClient* client);         
         void sendAddFieldGroup(const string& id, CContextClient* client);                           
         void sendAddVariable(const string& id, CContextClient* client);
         void sendAddVariableGroup(const string& id, CContextClient* client);
         void sendAddAllVariables(CContextClient* client);
         
         // Receive info from client
         static void recvAddField(CEventServer& event);
         void recvAddField(CBufferIn& buffer);
         static void recvAddFieldGroup(CEventServer& event);
         void recvAddFieldGroup(CBufferIn& buffer);
         static void recvAddVariable(CEventServer& event);
         void recvAddVariable(CBufferIn& buffer);
         static void recvAddVariableGroup(CEventServer& event);
         void recvAddVariableGroup(CBufferIn& buffer);

         // Dispatch event
         static bool dispatchEvent(CEventServer& event);

      public:
         /// Accesseurs statiques ///
         static StdString GetName(void);
         static StdString GetDefName(void);

         static ENodeType GetType(void);
      public:
         /// Traitements ///
         virtual void solveDescInheritance(bool apply, const CAttributeMap* const parent = 0);

          /// Autres ///
         virtual void parse(xml::CXMLNode& node);
         virtual StdString toString(void) const;
      public:

         CDate lastSync;
         CDate lastSplit;
         int nbAxis, nbDomains;
         bool isOpen;         
         MPI_Comm fileComm;

      private:
         void createSubComFile();
         bool checkRead;
         bool allZoneEmpty;
         
      private :
         /// Propriétés privées ///
         CContextClient* client;
         CContextClient* read_client; // Context client for reading (channel between server 1 and client)
         CFieldGroup* vFieldGroup;
         CVariableGroup* vVariableGroup;
         std::shared_ptr<CDataOutput> data_out;
         std::shared_ptr<CDataInput> data_in;
         std::vector<CField*> enabledFields;


      public:
        //         virtual void toBinary  (StdOStream& os) const;
        //         virtual void fromBinary(StdIStream& is);

   }; // class CFile

   ///--------------------------------------------------------------

   // Declare/Define CFileGroup and CFileDefinition
   DECLARE_GROUP(CFile);

   ///--------------------------------------------------------------

} // namespace xios

#endif // __XIOS_CFile__
