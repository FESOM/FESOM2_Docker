#ifndef __XIOS_CField__
#define __XIOS_CField__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "group_factory.hpp"
#include "functor.hpp"
#include "functor_type.hpp"
#include "filter.hpp"
#include "duration.hpp"
#include "date.hpp"
#include "declare_group.hpp"
#include "calendar_util.hpp"
#include "array_new.hpp"
#include "attribute_array.hpp"
#include "declare_ref_func.hpp"
#include "transformation_enum.hpp"
#include "variable.hpp"
#include "context_client.hpp"


namespace xios {

   /// ////////////////////// Déclarations ////////////////////// ///

   class CFieldGroup;
   class CFieldAttributes;
   class CField;

   class CFile;
   class CGrid;
   class CContext;
   class CGenericFilter;

   class CGarbageCollector;
   class COutputPin;
   class CSourceFilter;
   class CStoreFilter;
   class CFileWriterFilter;
   class CFileServerWriterFilter;

   ///--------------------------------------------------------------

   // Declare/Define CFieldAttribute
   BEGIN_DECLARE_ATTRIBUTE_MAP(CField)
#  include "field_attribute.conf"
   END_DECLARE_ATTRIBUTE_MAP(CField)

   ///--------------------------------------------------------------
   class CField
      : public CObjectTemplate<CField>
      , public CFieldAttributes
   {
         /// friend ///
         friend class CFile;

         /// typedef ///
         typedef CObjectTemplate<CField>   SuperClass;
         typedef CFieldAttributes SuperClassAttribute;

         enum EReadField
         {
           RF_NODATA, RF_EOF, RF_DATA
         };
         
      public:

         typedef CFieldAttributes RelAttributes;
         typedef CFieldGroup      RelGroup;

         enum EEventId
         {
           EVENT_ID_UPDATE_DATA, EVENT_ID_READ_DATA, EVENT_ID_READ_DATA_READY,
           EVENT_ID_ADD_VARIABLE, EVENT_ID_ADD_VARIABLE_GROUP
         };

         /// Constructeurs ///
         CField(void);
         explicit CField(const StdString& id);
         CField(const CField& field);       // Not implemented yet.
         CField(const CField* const field); // Not implemented yet.

         /// Accesseurs ///

         CGrid* getRelGrid(void) const;
         CFile* getRelFile(void) const;

         func::CFunctor::ETimeType getOperationTimeType() const;

      public:
         int getNStep(void) const;

         template <int N> void getData(CArray<double, N>& _data) const;

         std::shared_ptr<COutputPin> getInstantDataFilter();

         /// Mutateur ///
         void setRelFile(CFile* _file);
         void incrementNStep(void);
         void resetNStep(int nstep = 0);
         void resetNStepMax();

         std::map<int, StdSize> getGridAttributesBufferSize(CContextClient* client, bool bufferForWriting = false);
         // Grid data buffer size for each connection of contextclient
         std::map<int, StdSize> getGridDataBufferSize(CContextClient* client, bool bufferForWriting = false);

         void setContextClient(CContextClient* newContextClient);
         CContextClient* getContextClient();

       public:
         bool isActive(bool atCurrentTimestep = false) const;
         bool hasOutputFile;

         bool wasWritten() const;
         void setWritten();

         bool getUseCompressedOutput() const;
         void setUseCompressedOutput();

         /// Traitements ///
         void solveGridReference(void);
         void solveServerOperation(void);
         void solveCheckMaskIndex(bool doSendingIndex);
         void solveAllReferenceEnabledField(bool doSending2Server);
         void solveOnlyReferenceEnabledField(bool doSending2Server);
         void generateNewTransformationGridDest();
         void updateRef(CGrid* grid);
         void buildGridTransformationGraph();
         void solveGridDomainAxisRef(bool checkAtt);
         void solveTransformedGrid();
         void solveGenerateGrid();
         void solveGridDomainAxisBaseRef();

         void solveAllEnabledFieldsAndTransform();
         void checkGridOfEnabledFields();
         void sendGridOfEnabledFields();
         void sendGridComponentOfEnabledFields();

         /// Vérifications ///
         void checkTimeAttributes(CDuration* freqOp=NULL);

         void buildFilterGraph(CGarbageCollector& gc, bool enableOutput, Time start_graph=-1, Time end_graph=-1);
         size_t getGlobalWrittenSize(void) ;
         
         
         std::shared_ptr<COutputPin> getFieldReference(CGarbageCollector& gc, Time start_graph=-1, Time end_graph=-1);
         std::shared_ptr<COutputPin> getSelfReference(CGarbageCollector& gc, Time start_graph=-1, Time end_graph=-1);
         std::shared_ptr<COutputPin> getTemporalDataFilter(CGarbageCollector& gc, CDuration outFreq);
         std::shared_ptr<COutputPin> getSelfTemporalDataFilter(CGarbageCollector& gc, CDuration outFreq);

//         virtual void fromBinary(StdIStream& is);

         /// Destructeur ///
         virtual ~CField(void);

         /// Accesseurs statiques ///
         static StdString GetName(void);
         static StdString GetDefName(void);

         static ENodeType GetType(void);

        template <int N> void setData(const CArray<double, N>& _data, int ntile = -1);
	void checkSumLike( const double* array, int numElements, bool output ) const;
        static bool dispatchEvent(CEventServer& event);
        void sendAllAttributesToServer(CContextClient* client) ;
        static size_t totalSendBytes;
        static size_t totalRecvBytes;
        void sendUpdateData(const CArray<double,1>& data);
        void sendUpdateData(const CArray<double,1>& data, CContextClient* client);
        static void recvUpdateData(CEventServer& event);
        void recvUpdateData(std::map<int,CBufferIn*>& rankBuffers);
        void writeField(void);
        bool sendReadDataRequest(const CDate& tsDataRequested);
        bool sendReadDataRequestIfNeeded(void);
        static void recvReadDataRequest(CEventServer& event);
        void recvReadDataRequest(void);
        EReadField readField(void);
        static void recvReadDataReady(CEventServer& event);
        void recvReadDataReady(vector<int> ranks, vector<CBufferIn*> buffers);
        void checkForLateDataFromServer(void);
        void checkIfMustAutoTrigger(void);
        void autoTriggerIfNeeded(void);
        void outputField(CArray<double,3>& fieldOut);
        void outputField(CArray<double,2>& fieldOut);
        void outputField(CArray<double,1>& fieldOut);
        void inputField(CArray<double,3>& fieldOut);
        void inputField(CArray<double,2>& fieldOut);
        void inputField(CArray<double,1>& fieldOut);
        void outputCompressedField(CArray<double, 1>& fieldOut);
        void scaleFactorAddOffset(double scaleFactor, double addOffset);
        void invertScaleFactorAddOffset(double scaleFactor, double addOffset);
        void parse(xml::CXMLNode& node);

        void setVirtualVariableGroup(CVariableGroup* newVVariableGroup);
        CVariableGroup* getVirtualVariableGroup(void) const;
        vector<CVariable*> getAllVariables(void) const;
        virtual void solveDescInheritance(bool apply, const CAttributeMap* const parent = 0);

        CVariable* addVariable(const string& id = "");
        CVariableGroup* addVariableGroup(const string& id = "");        
        void sendAddVariable(const string& id, CContextClient* client);
        void sendAddVariableGroup(const string& id, CContextClient* client);
        static void recvAddVariable(CEventServer& event);
        void recvAddVariable(CBufferIn& buffer);
        static void recvAddVariableGroup(CEventServer& event);
        void recvAddVariableGroup(CBufferIn& buffer);        
        void sendAddAllVariables(CContextClient* client);
        void writeUpdateData(const CArray<double,1>& data);

        const std::vector<StdString>& getRefDomainAxisIds();

        const string& getExpression(void);
        bool hasExpression(void) const;

        bool hasGridMask(void) const;

      public:
         /// Propriétés privées ///
         CVariableGroup* vVariableGroup;

         CGrid*  grid;
         CFile*  file;

         CDuration freq_operation_srv, freq_write_srv;

         bool written; //<! Was the field written at least once
         int nstep, nstepMax;
         bool isEOF;
         CDate lastlast_Write_srv, last_Write_srv, last_operation_srv;
         CDate lastDataRequestedFromServer, lastDataReceivedFromServer, dateEOF;
         bool wasDataRequestedFromServer, wasDataAlreadyReceivedFromServer;
         bool mustAutoTrigger;

         map<int,std::shared_ptr<func::CFunctor> > foperation_srv;

         // map<int, CArray<double,1> > data_srv;
         CArray<double,1> recvDataSrv;
         
         std::shared_ptr<func::CFunctor> recvFoperationSrv;
         string content;

         std::vector<StdString> domAxisScalarIds_;
         bool useCompressedOutput;

         // Two variables to identify the time_counter meta data written in file, which has no time_counter
         bool hasTimeInstant;
         bool hasTimeCentered;

         Time field_graph_start;
         Time field_graph_end;


         DECLARE_REF_FUNC(Field,field)

      private:
         CContextClient* client;

         bool areAllReferenceSolved;
         bool isReferenceSolved;
         bool isReferenceSolvedAndTransformed;
         bool isGridChecked;
         bool nstepMaxRead;

      private:
         //! The type of operation attached to the field
         func::CFunctor::ETimeType operationTimeType;

         //! The output pin of the filter providing the instant data for the field
         std::shared_ptr<COutputPin> instantDataFilter;
         //! The output pin of the filters providing the result of the field's temporal operation
         std::map<CDuration, std::shared_ptr<COutputPin>, DurationFakeLessComparator> temporalDataFilters;
         //! The output pin of the filter providing the instant data for self references
         std::shared_ptr<COutputPin> selfReferenceFilter;
         //! The source filter for data provided by the client
         std::shared_ptr<CSourceFilter> clientSourceFilter;
         //! The source filter for data provided by the server
         std::shared_ptr<CSourceFilter> serverSourceFilter;
         //! The terminal filter which stores the instant data
         std::shared_ptr<CStoreFilter> storeFilter;
         //! The terminal filter which writes the data to file
         std::shared_ptr<CFileWriterFilter> fileWriterFilter;
         //! The terminal filter which writes data to file
         std::shared_ptr<CFileServerWriterFilter> fileServerWriterFilter;
   }; // class CField

   ///--------------------------------------------------------------

   // Declare/Define CFieldGroup and CFieldDefinition
   DECLARE_GROUP(CField);

   ///-----------------------------------------------------------------

   template <>
      void CGroupTemplate<CField, CFieldGroup, CFieldAttributes>::solveRefInheritance(void);

   ///-----------------------------------------------------------------
} // namespace xios


#endif // __XIOS_CField__
