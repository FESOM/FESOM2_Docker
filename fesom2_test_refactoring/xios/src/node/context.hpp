#ifndef __XIOS_CContext__
#define __XIOS_CContext__

/// XIOS headers ///
#include "xios_spl.hpp"
//#include "node_type.hpp"
#include "calendar_wrapper.hpp"

#include "declare_group.hpp"
#include "data_output.hpp"
#include "garbage_collector.hpp"
#include "registry.hpp"
#include "mpi.hpp"


namespace xios {
   class CContextClient;
   class CContextServer;


   /// ////////////////////// Déclarations ////////////////////// ///
   class CContextGroup;
   class CContextAttributes;
   class CContext;
   class CFile;
   ///--------------------------------------------------------------

   // Declare/Define CFileAttribute
   BEGIN_DECLARE_ATTRIBUTE_MAP(CContext)
#  include "context_attribute.conf"
   END_DECLARE_ATTRIBUTE_MAP(CContext)

   ///--------------------------------------------------------------
  /*!
  \class CContext
   This class corresponds to the concrete presentation of context in xml file and in play an essential role in XIOS
   Each object of this class contains all root definition of elements: files, fiels, domains, axis, etc, ... from which
   we can have access to each element.
   In fact, every thing must a be inside a particuliar context. After the xml file (iodef.xml) is parsed,
   object of the class is created and its contains all information of other elements in the xml file.
  */
   class CContext
      : public CObjectTemplate<CContext>
      , public CContextAttributes
   {
         public :
         enum EEventId
         {
           EVENT_ID_CLOSE_DEFINITION,EVENT_ID_UPDATE_CALENDAR,
           EVENT_ID_CREATE_FILE_HEADER,EVENT_ID_CONTEXT_FINALIZE,
           EVENT_ID_POST_PROCESS, EVENT_ID_SEND_REGISTRY,
           EVENT_ID_POST_PROCESS_GLOBAL_ATTRIBUTES,
           EVENT_ID_PROCESS_GRID_ENABLED_FIELDS
         };

         /// typedef ///
         typedef CObjectTemplate<CContext>   SuperClass;
         typedef CContextAttributes SuperClassAttribute;

      public :

         typedef CContextAttributes RelAttributes;
         typedef CContext           RelGroup;

         //---------------------------------------------------------

      public :

         /// Constructeurs ///
         CContext(void);
         explicit CContext(const StdString & id);
         CContext(const CContext & context);       // Not implemented yet.
         CContext(const CContext * const context); // Not implemented yet.

         /// Destructeur ///
         virtual ~CContext(void);

         //---------------------------------------------------------

      public :

         /// Mutateurs ///
         void setCalendar(std::shared_ptr<CCalendar> newCalendar);

         /// Accesseurs ///
         std::shared_ptr<CCalendar>      getCalendar(void) const;

      public :
         // Initialize server or client
         void initClient(MPI_Comm intraComm, MPI_Comm interComm, CContext* cxtServer = 0);
         void initServer(MPI_Comm intraComm, MPI_Comm interComm, CContext* cxtClient = 0);
         bool isInitialized(void);

         StdString dumpClassAttributes(void);

         // Put sever or client into loop state
         bool checkBuffersAndListen(bool enableEventsProcessing=true);

         // Finalize a context
         void finalize(void);
         bool isFinalized(void);

         void closeDefinition(void);

         // Some functions to process context
         void findAllEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles);
         // void findAllEnabledFields(void);
         // void findAllEnabledFieldsInReadModeFiles(void);
         void readAttributesOfEnabledFieldsInReadModeFiles();
         void solveAllInheritance(bool apply=true);
         void findEnabledFiles(void);
         void findEnabledWriteModeFiles(void);
         void findEnabledReadModeFiles(void);
         void closeAllFile(void);
         void updateCalendar(int step);
         void createFileHeader(void);
         void initReadFiles(void);
         void checkAxisDomainsGridsEligibilityForCompressedOutput();
         void prepareTimeseries(void);
         void solveOnlyRefOfEnabledFields(bool sendToServer);         
         void buildFilterGraphOfEnabledFields();
         void postProcessFilterGraph();
         void startPrefetchingOfEnabledReadModeFiles();
         void doPreTimestepOperationsForEnabledReadModeFiles();
         void doPostTimestepOperationsForEnabledReadModeFiles();
         void findFieldsWithReadAccess(void);
         void solveAllRefOfFieldsWithReadAccess();
         void buildFilterGraphOfFieldsWithReadAccess();
         void postProcessing();
         void postProcessingGlobalAttributes();         

         void solveAllRefOfEnabledFieldsAndTransform(bool sendToServer);
         void checkGridEnabledFields();
         void checkGridEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles);
         void sendGridEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles);  
         void sendGridComponentEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles)       ;

         std::map<int, StdSize> getAttributesBufferSize(std::map<int, StdSize>& maxEventSize, CContextClient* contextClient, bool bufferForWriting = false);
         std::map<int, StdSize> getDataBufferSize(std::map<int, StdSize>& maxEventSize, CContextClient* contextClient, bool bufferForWriting = false);
         void setClientServerBuffer(CContextClient* contextClient, bool bufferForWriting = false);

         // Distribute files (in write mode) among secondary-server pools according to the estimated data flux
         void distributeFiles(void);
         void distributeFileOverBandwith() ;
         void distributeFileOverMemoryBandwith() ;
         
         // Send context close definition
         void sendCloseDefinition(void);
         // There are something to send on closing context defintion
         void sendUpdateCalendar(int step);
         void sendCreateFileHeader(void);
         void sendEnabledFiles(const std::vector<CFile*>& activeFiles);
         void sendEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles);
         void sendRefDomainsAxisScalars(const std::vector<CFile*>& activeFiles);
         void sendRefGrid(const std::vector<CFile*>& activeFiles);
         void sendPostProcessing();
         void sendPostProcessingGlobalAttributes();
         void sendProcessingGridOfEnabledFields();
         //!< after be gathered to the root process of the context, merged registry is sent to the root process of the servers
         void sendRegistry(void) ;

         const StdString& getIdServer();
         const StdString& getIdServer(const int srvPoolNb);

         // Client side: Receive and process messages
         static void recvUpdateCalendar(CEventServer& event);
         void recvUpdateCalendar(CBufferIn& buffer);
         static void recvCloseDefinition(CEventServer& event);
         static void recvCreateFileHeader(CEventServer& event);
         void recvCreateFileHeader(CBufferIn& buffer);
         static void recvSolveInheritanceContext(CEventServer& event);
         void recvSolveInheritanceContext(CBufferIn& buffer);
         static void recvPostProcessing(CEventServer& event);
         void recvPostProcessing(CBufferIn& buffer);
         static void recvProcessingGridOfEnabledFields(CEventServer& event);
         static void recvPostProcessingGlobalAttributes(CEventServer& event);
         void recvPostProcessingGlobalAttributes(CBufferIn& buffer);
         static void recvRegistry(CEventServer& event) ;
         void recvRegistry(CBufferIn& buffer) ; //!< registry is received by the servers

         void freeComms(void);                  //!< Free internally allcoated communicators
         void releaseClientBuffers(void);       //! Deallocate buffers allocated by clientContexts

         // dispatch event
         static bool dispatchEvent(CEventServer& event);

      public:
        // Get current context
        static CContext* getCurrent(void);

        // Get context root
        static CContextGroup* getRoot(void);

        // Set current context
        static void setCurrent(const string& id);

        // Create new context
        static CContext* create(const string& id = "");

        /// Accesseurs statiques ///
        static StdString GetName(void);
        static StdString GetDefName(void);
        static ENodeType GetType(void);

        static CContextGroup* GetContextGroup(void);

        // Some functions to visualize structure of current context
        static void ShowTree(StdOStream & out = std::clog);
        static void CleanTree(void);

      public :
         // Parse xml node and write all info into context
         virtual void parse(xml::CXMLNode & node);

         // Visualize a context
         virtual StdString toString(void) const;


         // Solve all inheritance relation in current context
         virtual void solveDescInheritance(bool apply, const CAttributeMap * const parent = 0);

         // Verify if all root definition in a context have children
         virtual bool hasChild(void) const;


      public :
         // Calendar of context
         std::shared_ptr<CCalendar>   calendar;

         // List of all enabled files (files on which fields are written or read)
         std::vector<CFile*> enabledFiles;
         // List of all enabled files in read mode (files on which fields are read)
         std::vector<CFile*> enabledReadModeFiles;
         // List of all enabled files in write mode
         std::vector<CFile*> enabledWriteModeFiles;

         // List of all enabled fields whose instant data is accessible from the public API
         // but which are not part of a file
         std::vector<CField*> fieldsWithReadAccess;

         // Context root
         static std::shared_ptr<CContextGroup> root;

         // Determine context on client or not
         bool hasClient;

         // Determine context on server or not
         bool hasServer;

         CContextServer* server;    //!< Concrete context server
         CContextClient* client;    //!< Concrete contex client
         std::vector<CContextServer*> serverPrimServer;
         std::vector<CContextClient*> clientPrimServer;

         CRegistry* registryIn ;    //!< input registry which is read from file
         CRegistry* registryOut ;   //!< output registry which will be written into file at the finalize

      private:
         bool isPostProcessed;
         bool allProcessed;
         bool finalized;
         int countChildCtx_;        //!< Counter of child contexts (for now it is the number of secondary server pools)
         StdString idServer_;
         CGarbageCollector garbageCollector;
         std::list<MPI_Comm> comms; //!< Communicators allocated internally

      public: // Some function maybe removed in the near future
        // virtual void toBinary  (StdOStream & os) const;
        // virtual void fromBinary(StdIStream & is);
   }; // class CContext

   ///--------------------------------------------------------------

   // Declare/Define CContextGroup and CContextDefinition
   DECLARE_GROUP(CContext);

   ///--------------------------------------------------------------

} // namespace xios

#endif // __XIOS_CContext__
