#ifndef __XIOS_CAxis__
#define __XIOS_CAxis__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "group_factory.hpp"
#include "virtual_node.hpp"

#include "declare_group.hpp"
#include "declare_ref_func.hpp"
#include "declare_virtual_node.hpp"
#include "attribute_array.hpp"
#include "attribute_enum.hpp"
#include "attribute_enum_impl.hpp"
#include "server_distribution_description.hpp"
#include "transformation.hpp"
#include "transformation_enum.hpp"

namespace xios {
   /// ////////////////////// Déclarations ////////////////////// ///

   class CAxisGroup;
   class CAxisAttributes;
   class CAxis;

   ///--------------------------------------------------------------

   // Declare/Define CAxisAttribute
   BEGIN_DECLARE_ATTRIBUTE_MAP(CAxis)
#  include "axis_attribute.conf"
   END_DECLARE_ATTRIBUTE_MAP(CAxis)

   ///--------------------------------------------------------------

   class CAxis
      : public CObjectTemplate<CAxis>
      , public CAxisAttributes
   {
               /// typedef ///
         typedef CObjectTemplate<CAxis>   SuperClass;
         typedef CAxisAttributes SuperClassAttribute;
         
      public:
         enum EEventId
         {
           EVENT_ID_DISTRIBUTION_ATTRIBUTE,           
           EVENT_ID_DISTRIBUTED_VALUE,
           EVENT_ID_NON_DISTRIBUTED_VALUE,
           EVENT_ID_NON_DISTRIBUTED_ATTRIBUTES,
           EVENT_ID_DISTRIBUTED_ATTRIBUTES
         } ;

      public:
         typedef CAxisAttributes RelAttributes;
         typedef CAxisGroup      RelGroup;
         typedef CTransformation<CAxis>::TransformationMapTypes TransMapTypes;

      public:
         /// Constructeurs ///
         CAxis(void);
         explicit CAxis(const StdString & id);
         CAxis(const CAxis & axis);       // Not implemented yet.
         CAxis(const CAxis * const axis); // Not implemented yet.

         static CAxis* createAxis();

         /// Accesseurs ///
         const std::set<StdString> & getRelFiles(void) const;

         int getNumberWrittenIndexes(MPI_Comm writtenCom);
         int getTotalNumberWrittenIndexes(MPI_Comm writtenCom);
         int getOffsetWrittenIndexes(MPI_Comm writtenCom);
         CArray<int, 1>& getCompressedIndexToWriteOnServer(MPI_Comm writtenCom);

         std::map<int, StdSize> getAttributesBufferSize(CContextClient* client, const std::vector<int>& globalDim, int orderPositionInGrid,
                                                        CServerDistributionDescription::ServerDistributionType disType = CServerDistributionDescription::BAND_DISTRIBUTION);

         /// Test ///
         bool IsWritten(const StdString & filename) const;
         bool isWrittenCompressed(const StdString& filename) const;
         bool isDistributed(void) const;
         bool isCompressible(void) const;

         /// Mutateur ///
         void addRelFile(const StdString & filename);
         void addRelFileCompressed(const StdString& filename);

         /// Vérifications ///
         void checkAttributes(void);

         /// Destructeur ///
         virtual ~CAxis(void);

         virtual void parse(xml::CXMLNode & node);

         void setContextClient(CContextClient* contextClient);

         /// Accesseurs statiques ///
         static StdString GetName(void);
         static StdString GetDefName(void);
         static ENodeType GetType(void);

         static bool dispatchEvent(CEventServer& event);         
         
         void checkAttributesOnClient();
         void checkAttributesOnClientAfterTransformation(const std::vector<int>& globalDim, int orderPositionInGrid,
                                                         CServerDistributionDescription::ServerDistributionType distType = CServerDistributionDescription::BAND_DISTRIBUTION);
         void sendCheckedAttributes(const std::vector<int>& globalDim, int orderPositionInGrid,
                                    CServerDistributionDescription::ServerDistributionType disType = CServerDistributionDescription::BAND_DISTRIBUTION);

         void checkEligibilityForCompressedOutput();
         size_t getGlobalWrittenSize(void) ;

         void computeWrittenIndex();
         void computeWrittenCompressedIndex(MPI_Comm);
         bool hasTransformation();
         void solveInheritanceTransformation();
         TransMapTypes getAllTransformations();         
         void duplicateTransformation(CAxis*);
         CTransformation<CAxis>* addTransformation(ETranformationType transType, const StdString& id="");
         bool isEqual(CAxis* axis);

      public: 
        bool hasValue;        
        bool hasBounds;
        bool hasLabel;

        CArray<int,1> localIndexToWriteOnServer;

      private:
         void checkData();
         void checkMask();
         void checkBounds();
         void checkLabel();
         void sendAttributes(const std::vector<int>& globalDim, int orderPositionInGrid,
                             CServerDistributionDescription::ServerDistributionType distType);
         void sendDistributionAttribute(const std::vector<int>& globalDim, int orderPositionInGrid,
                                        CServerDistributionDescription::ServerDistributionType distType);
         void computeConnectedClients(const std::vector<int>& globalDim, int orderPositionInGrid,
                                     CServerDistributionDescription::ServerDistributionType distType);

         void sendNonDistributedAttributes(void);
         void sendDistributedAttributes(void);

         static void recvNonDistributedAttributes(CEventServer& event);
         static void recvDistributedAttributes(CEventServer& event);
         static void recvDistributionAttribute(CEventServer& event);
         void recvNonDistributedAttributes(int rank, CBufferIn& buffer);
         void recvDistributedAttributes(vector<int>& rank, vector<CBufferIn*> buffers);
         void recvDistributionAttribute(CBufferIn& buffer);

         void setTransformations(const TransMapTypes&);

      private:

/** Clients that have to send a domain. There can be multiple clients in case of secondary server, otherwise only one client. */
         std::list<CContextClient*> clients;
         std::set<CContextClient*> clientsSet;

         bool isChecked;
         bool areClientAttributesChecked_;
         bool isClientAfterTransformationChecked;
         std::set<StdString> relFiles, relFilesCompressed;
         TransMapTypes transformationMap_;         
         //! True if and only if the data defined on the axis can be outputted in a compressed way
         bool isCompressible_;
         std::map<int, map<int,int> > nbSenders; // Mapping of number of communicating client to a server
         std::map<int, std::unordered_map<int, vector<size_t> > > indSrv_; // Global index of each client sent to server
         // std::map<int, vector<int> > indWrittenSrv_; // Global written index of each client sent to server
         std::unordered_map<size_t,size_t> globalLocalIndexMap_;
         std::vector<int> indexesToWrite;
         std::map<int,int> numberWrittenIndexes_, totalNumberWrittenIndexes_, offsetWrittenIndexes_;
         std::map<int, CArray<int, 1> > compressedIndexToWriteOnServer;
         std::map<int, std::vector<int> > connectedServerRank_;
         bool computedWrittenIndex_;                  

       private:
         static bool initializeTransformationMap(std::map<StdString, ETranformationType>& m);
         static std::map<StdString, ETranformationType> transformationMapList_;
         static bool dummyTransformationMapList_;

         DECLARE_REF_FUNC(Axis,axis)
   }; // class CAxis

   ///--------------------------------------------------------------

   // Declare/Define CAxisGroup and CAxisDefinition
   DECLARE_GROUP(CAxis);
} // namespace xios

#endif // __XIOS_CAxis__
