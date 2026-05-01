#ifndef __XIOS_CDomain__
#define __XIOS_CDomain__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "group_factory.hpp"

#include "declare_group.hpp"
#include "declare_ref_func.hpp"
#include "event_client.hpp"
#include "event_server.hpp"
#include "buffer_in.hpp"
#include "array_new.hpp"
#include "attribute_array.hpp"
#include "attribute_enum.hpp"
#include "transformation.hpp"
#include "transformation_enum.hpp"
#include "server_distribution_description.hpp"
#include "mesh.hpp"

namespace xios {

   /// ////////////////////// Déclarations ////////////////////// ///

   class CDomainGroup;
   class CDomainAttributes;
   class CDomain;
   class CFile;

   ///--------------------------------------------------------------

   // Declare/Define CDomainAttribute
   BEGIN_DECLARE_ATTRIBUTE_MAP(CDomain)
#  include "domain_attribute.conf"
#  include "domain_attribute_private.conf"
   END_DECLARE_ATTRIBUTE_MAP(CDomain)

   ///--------------------------------------------------------------

   class CDomain
      : public CObjectTemplate<CDomain>
      , public CDomainAttributes
   {
     /// typedef ///
     typedef CObjectTemplate<CDomain>   SuperClass;
     typedef CDomainAttributes SuperClassAttribute;
     public:
         enum EEventId
         {
           EVENT_ID_INDEX, EVENT_ID_LON, EVENT_ID_LAT, 
           EVENT_ID_AREA,
           EVENT_ID_DATA_INDEX, EVENT_ID_SERVER_ATTRIBUT
         } ;

      public:

         typedef CDomainAttributes RelAttributes;
         typedef CDomainGroup      RelGroup;
         typedef CTransformation<CDomain>::TransformationMapTypes TransMapTypes;

         /// Constructeurs ///
         CDomain(void);
         explicit CDomain(const StdString & id);
         CDomain(const CDomain & domain);       // Not implemented yet.
         CDomain(const CDomain * const domain); // Not implemented yet.

         static CDomain* createDomain();
         
         CMesh* mesh;
         void assignMesh(const StdString, const int);
        
         virtual void parse(xml::CXMLNode & node);

         void setContextClient(CContextClient* contextClient);

         /// Vérifications ///
         void checkAttributes(void);
         void checkAttributesOnClient();
         void checkAttributesOnClientAfterTransformation();
         void checkEligibilityForCompressedOutput(void);

         void sendCheckedAttributes();

         bool hasTransformation();
         void solveInheritanceTransformation();
         TransMapTypes getAllTransformations();
         void redistribute(int nbLocalDomain);
         void duplicateTransformation(CDomain*);
         CTransformation<CDomain>* addTransformation(ETranformationType transType, const StdString& id="");

      public:
         const std::set<StdString> & getRelFiles(void) const;
         bool IsWritten(const StdString & filename) const;
         bool isWrittenCompressed(const StdString& filename) const;
         
         int getNumberWrittenIndexes(MPI_Comm writtenCom);
         int getTotalNumberWrittenIndexes(MPI_Comm writtenCom);
         int getOffsetWrittenIndexes(MPI_Comm writtenCom);
         CArray<int,1>& getCompressedIndexToWriteOnServer(MPI_Comm writtenCom);

         std::map<int, StdSize> getAttributesBufferSize(CContextClient* client, bool bufferForWriting = false);

         bool isEmpty(void) const;
         bool isDistributed(void) const;
         bool isCompressible(void) const; 

         bool isTiled(void) const;
         bool isTiledOnly(void) const;
         int getTileId(int i, int j) const;
         int getTileDataISize(int tileId) const;
         int getTileDataJSize(int tileId) const;
         void computeCompressionTiled(CArray<int,1>& dataIndexI, CArray<int,1>& dataIndexJ,
                                      CArray<int,1>& infoIndexI, CArray<int,1>& infoIndexJ);

         std::vector<int> getNbGlob();
         bool isEqual(CDomain* domain);

         static bool dispatchEvent(CEventServer& event);

      public:
         /// Mutateur ///
         void addRelFile(const StdString & filename);
         void addRelFileCompressed(const StdString& filename);            
         
         void computeWrittenIndex();
         void computeWrittenCompressedIndex(MPI_Comm);

         void AllgatherRectilinearLonLat(CArray<double,1>& lon, CArray<double,1>& lat,
                                         CArray<double,1>& lon_g, CArray<double,1>& lat_g);

         void fillInRectilinearBoundLonLat(CArray<double,1>& lon, CArray<double,1>& lat,
                                           CArray<double,2>& boundsLon, CArray<double,2>& boundsLat);
         
         void fillInLonLat();
         void initLonLatValue();
         bool distributionAttributesHaveValue() const;

         size_t getGlobalWrittenSize() ;
         /// Destructeur ///
         virtual ~CDomain(void);

         /// Accesseurs statiques ///
         static StdString GetName(void);
         static StdString GetDefName(void);

         static ENodeType GetType(void);        

      public:
         CArray<double, 1> lonvalue, latvalue;
         CArray<double, 2> bounds_lonvalue, bounds_latvalue;
         CArray<double, 1> areavalue;

         CArray<int,1> localIndexToWriteOnServer;

         CArray<bool, 1> domainMask; // mask_1d, mask_2d -> domainMask
         CArray<bool, 1> localMask; // domainMask + indexing
         bool isCurvilinear ;
         bool hasBounds ;
         bool hasArea;
         bool hasLonLat;
         bool hasPole ;
         bool hasLatInReadFile_ ; // specify if latitude is defined on read file, so it can be read later when grid distribution will be defined
         bool hasBoundsLatInReadFile_ ; // specify if latitude boundarues are defined on read file, so it can be read later when grid distribution will be defined
         bool hasLonInReadFile_ ; // specify if longitude is defined on read file, so it can be read later when grid distribution will be defined
         bool hasBoundsLonInReadFile_ ; // specify if longitude boundaries are defined on read file, so it can be read later when grid distribution will be defined

         void computeLocalMask(void) ;
      private:
         void checkDomain(void);
         void checkLocalIDomain(void);
         void checkLocalJDomain(void);

         void checkMask(void);
         void checkDomainData(void);
         void checkCompression(void);

         void checkBounds(void);
         void checkArea(void);
         void checkLonLat();
         void checkTiles();

         void setTransformations(const TransMapTypes&);         
         void computeNGlobDomain();
         void sendAttributes();
         void sendIndex();
         void sendDistributionAttributes();
         void sendArea();
         void sendLonLat();         
         void sendDataIndex();
         void convertLonLatValue();
         void fillInRectilinearLonLat();
         void fillInCurvilinearLonLat();
         void fillInUnstructuredLonLat();
         
         static void recvDistributionAttributes(CEventServer& event);
         static void recvIndex(CEventServer& event);
         static void recvLon(CEventServer& event);
         static void recvLat(CEventServer& event);
         static void recvArea(CEventServer& event);
         static void recvDataIndex(CEventServer& event);
         void recvDistributionAttributes(CBufferIn& buffer);                  
         void recvIndex(std::map<int, CBufferIn*>& rankBuffers);         
         void recvLon(std::map<int, CBufferIn*>& rankBuffers);
         void recvLat(std::map<int, CBufferIn*>& rankBuffers);
         void recvArea(std::map<int, CBufferIn*>& rankBuffers);         
         void recvDataIndex(std::map<int, CBufferIn*>& rankBuffers);

         void completeLonLatClient(void);  
         void computeConnectedClients();    

       private:         

/** Clients that have to send a domain. There can be multiple clients in case of secondary server, otherwise only one client. */
         std::list<CContextClient*> clients;
         std::set<CContextClient*> clientsSet;

         bool isChecked, computedWrittenIndex_;
         std::set<StdString> relFiles, relFilesCompressed;
         bool isClientChecked; // Verify whether all attributes of domain on the client side are good
         bool isClientAfterTransformationChecked;
         std::map<int, CArray<int,1> > indGlob_;
         std::map<int, map<int,int> > nbSenders; // Mapping of number of communicating client to a server

/** Global index of each client sent to server: map<serverSize, map<serverRank, indexes>> */
         std::map<int, std::unordered_map<int, vector<size_t> > > indSrv_;
         // std::map<CContextClient*, std::map<int, vector<int> > > indWrittenSrv_; // Global written index of each client sent to server
         std::vector<int> indexesToWrite;
         std::vector<int> recvClientRanks_;
         std::map<int,int> numberWrittenIndexes_, totalNumberWrittenIndexes_, offsetWrittenIndexes_;
         std::map<int, CArray<int, 1> > compressedIndexToWriteOnServer;     
         std::map<int, std::map<int,size_t> > connectedDataSize_;
         std::map<int, std::vector<int> > connectedServerRank_;

//! True if and only if the data defined on the domain can be outputted in a compressed way
         bool isCompressible_;
         bool isRedistributed_;
         TransMapTypes transformationMap_;         
         bool isUnstructed_;
         std::unordered_map<size_t,size_t> globalLocalIndexMap_;

//! True if tiled data is defined on the domain
         bool isTiled_;
//! True if ONLY tiled data is defined on the domain
         bool isTiledOnly_;

       private:
         static bool initializeTransformationMap(std::map<StdString, ETranformationType>& m);
         static std::map<StdString, ETranformationType> transformationMapList_;
         static bool _dummyTransformationMapList;

         DECLARE_REF_FUNC(Domain,domain)

   }; // class CDomain

   ///--------------------------------------------------------------

   // Declare/Define CDomainGroup and CDomainDefinition
   DECLARE_GROUP(CDomain);

   ///--------------------------------------------------------------

} // namespace xios

#endif //__XIOS_CDomain__
