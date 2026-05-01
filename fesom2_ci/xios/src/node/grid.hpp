#ifndef __XIOS_CGrid__
#define __XIOS_CGrid__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "group_factory.hpp"

#include "declare_group.hpp"
#include "domain.hpp"
#include "axis.hpp"
#include "scalar.hpp"
#include "array_new.hpp"
#include "attribute_array.hpp"
#include "distribution_server.hpp"
#include "client_server_mapping.hpp"
#include "utils.hpp"
#include "transformation_enum.hpp"

namespace xios {

   /// ////////////////////// Declarations ////////////////////// ///

   class CGridGroup;
   class CGridAttributes;
   class CDomainGroup;
   class CAxisGroup;
   class CScalarGroup;
   class CGrid;
   class CDistributionClient;
   class CDistributionServer;
   class CServerDistributionDescription;
   class CClientServerMapping;
   class CGridTransformation;

   ///--------------------------------------------------------------

   // Declare/Define CGridAttribute
   BEGIN_DECLARE_ATTRIBUTE_MAP(CGrid)
#  include "grid_attribute.conf"
   END_DECLARE_ATTRIBUTE_MAP(CGrid)

   ///--------------------------------------------------------------

   class CGrid
      : public CObjectTemplate<CGrid>
      , public CGridAttributes
   {
         /// typedef ///
         typedef CObjectTemplate<CGrid>   SuperClass;
         typedef CGridAttributes SuperClassAttribute;

      public:

         typedef CGridAttributes RelAttributes;
         typedef CGridGroup      RelGroup;

         enum EEventId
         {
           EVENT_ID_INDEX, EVENT_ID_ADD_DOMAIN, EVENT_ID_ADD_AXIS, EVENT_ID_ADD_SCALAR
         };

         /// Constructeurs ///
         CGrid(void);
         explicit CGrid(const StdString& id);
         CGrid(const CGrid& grid);       // Not implemented yet.
         CGrid(const CGrid* const grid); // Not implemented yet.

         /// Traitements ///
//         void solveReference(void);

         void checkEligibilityForCompressedOutput();

         void solveDomainAxisRef(bool areAttributesChecked);

         void checkMaskIndex(bool doCalculateIndex);

 //        virtual void toBinary  (StdOStream& os) const;
//         virtual void fromBinary(StdIStream& is);

         void addRelFileCompressed(const StdString& filename);

         /// Tests ///
         bool isCompressible(void) const;
         bool isWrittenCompressed(const StdString& filename) const;

      public:

         /// Accesseurs ///
         StdSize getDimension(void);

         StdSize  getDataSize(void) const;

         StdSize  getTileDataSize(int tileId);

         StdSize  getTileSize(int tileId);

         /// Entrees-sorties de champs
         template <int n>
         void inputField(const CArray<double,n>& field, CArray<double,1>& stored) const;
         template <int n>
         void maskField(const CArray<double,n>& field, CArray<double,1>& stored, bool isTiled = false) const;
         template <int n>
         void outputField(const CArray<double,1>& stored, CArray<double,n>& field) const;  
         template <int n>
         void uncompressField(const CArray<double,n>& data, CArray<double,1>& outData) const; 
         template <int n>
         void copyTile(const CArray<double,n>& tileData, CArray<double, 1>& stored, int tileId);

         virtual void parse(xml::CXMLNode& node);

         /// Destructeur ///
         virtual ~CGrid(void);

      public:

         /// Accesseurs statiques ///
         static StdString GetName(void);
         static StdString GetDefName(void);

         static ENodeType GetType(void);

         /// Instanciateurs Statiques ///
         static CGrid* createGrid(CDomain* domain);
         static CGrid* createGrid(CDomain* domain, CAxis* axis);
         static CGrid* createGrid(const std::vector<CDomain*>& domains, const std::vector<CAxis*>& axis,
                                  const CArray<int,1>& axisDomainOrder = CArray<int,1>());
         static CGrid* createGrid(StdString id, const std::vector<CDomain*>& domains, const std::vector<CAxis*>& axis,
                                  const std::vector<CScalar*>& scalars, const CArray<int,1>& axisDomainOrder = CArray<int,1>());
         static CGrid* createGrid(const std::vector<CDomain*>& domains, const std::vector<CAxis*>& axis,
                                  const std::vector<CScalar*>& scalars, const CArray<int,1>& axisDomainOrder);
         static StdString generateId(const std::vector<CDomain*>& domains, const std::vector<CAxis*>& axis,
                                     const std::vector<CScalar*>& scalars, const CArray<int,1>& axisDomainOrder = CArray<int,1>());
         static StdString generateId(const CGrid* gridSrc, const CGrid* gridDest);
         static CGrid* cloneGrid(const StdString& idNewGrid, CGrid* gridSrc);

      public:            
         void computeIndexServer(void);
         void computeIndex(void);
         void computeIndexScalarGrid();
         void computeWrittenIndex();

         void solveDomainRef(bool checkAtt);
         void solveAxisRef(bool checkAtt);
         void solveScalarRef(bool checkAtt);
         void solveDomainAxisRefInheritance(bool apply = true);
         void solveTransformations();
         void solveDomainAxisBaseRef();

         CDomain* addDomain(const std::string& id=StdString());
         CAxis* addAxis(const std::string& id=StdString());
         CScalar* addScalar(const std::string& id=StdString());
         void sendAddDomain(const std::string& id="");
         void sendAddAxis(const std::string& id="");
         void sendAddScalar(const std::string& id="");
         void sendGrid(void) ;

         static void recvAddDomain(CEventServer& event);
         void recvAddDomain(CBufferIn& buffer);
         static void recvAddAxis(CEventServer& event);
         void recvAddAxis(CBufferIn& buffer);
         static void recvAddScalar(CEventServer& event);
         void recvAddScalar(CBufferIn& buffer);

         static bool dispatchEvent(CEventServer& event);
         static void recvIndex(CEventServer& event);
         void recvIndex(vector<int> ranks, vector<CBufferIn*> buffers);
         void sendIndex(void);
         void sendIndexScalarGrid();

         void setContextClient(CContextClient* contextClient);

         void computeDomConServer();
         std::map<int, int> getDomConServerSide();
         std::map<int, StdSize> getAttributesBufferSize(CContextClient* client, bool bufferForWriting = false);
         std::map<int, StdSize> getDataBufferSize(CContextClient* client, const std::string& id = "", bool bufferForWriting = false);
         std::vector<StdString> getDomainList();
         std::vector<StdString> getAxisList();
         std::vector<StdString> getScalarList();
         std::vector<CDomain*> getDomains();
         std::vector<CAxis*> getAxis();
         std::vector<CScalar*> getScalars();
         CDomain* getDomain(int domainIndex);
         CAxis* getAxis(int axisIndex);
         CScalar* getScalar(int scalarIndex);
         std::vector<int> getAxisOrder();
         std::vector<int> getGlobalDimension();
         bool isScalarGrid() const;         

         bool doGridHaveDataToWrite();
         bool doGridHaveDataDistributed(CContextClient* client = 0);
         size_t getWrittenDataSize() const;
         int getNumberWrittenIndexes() const;
         int getTotalNumberWrittenIndexes() const;
         int getOffsetWrittenIndexes() const;

         CDistributionServer* getDistributionServer();
         CDistributionClient* getDistributionClient();
         CGridTransformation* getTransformations();

         void transformGrid(CGrid* transformGridSrc);
         void completeGrid(CGrid* transformGridSrc = 0);
         void doAutoDistribution(CGrid* transformGridSrc);
         bool isTransformed();
         void setTransformed();
         bool isGenerated();
         void setGenerated();
         void addTransGridSource(CGrid* gridSrc);
         std::map<CGrid*, std::pair<bool,StdString> >& getTransGridSource();
         bool hasTransform();
         size_t getGlobalWrittenSize(void) ;
      public:
         CArray<int, 1> storeIndex_client;
         CArray<int, 1> storeIndexTiled_client;
         CArray<bool, 1> storeMask_client;
         CArray<bool, 1> storeMaskTiled_client;

/** Map containing indexes that will be sent in sendIndex(). */
         std::map<CContextClient*, map<int, CArray<int, 1> > > storeIndex_toSrv;

/** Map storing the number of senders. Key = size of receiver's intracomm */
         std::map<int, std::map<int,int> > nbSenders;

         std::map<CContextClient*, std::map<int,int> > nbReadSenders;

         map<int, CArray<int, 1> > storeIndex_fromSrv; // Support, for now, reading with level-1 server

         map<int, CArray<size_t, 1> > outIndexFromClient;  // Deprecated

         map<int, CArray<size_t, 1> > compressedOutIndexFromClient;

/** Map storing received indexes. Key = sender rank, value = index array. */
         map<int, CArray<size_t, 1> > outGlobalIndexFromClient;

/** Map storing received indexes. Key = sender rank, value = index array for tiled domains */
         map<int, CArray<size_t, 1> > outGlobalIndexFromClientTiled;

// Manh Ha's comment: " A client receives global index from other clients (via recvIndex)
// then does mapping these index into local index of STORE_CLIENTINDEX
// In this way, store_clientIndex can be used as an input of a source filter
// Maybe we need a flag to determine whether a client wants to write. TODO "

/** Map storing received data. Key = sender rank, value = data array.
 *  The map is created in CGrid::computeClientIndex and filled upon receiving data in CField::recvUpdateData() */
         map<int, CArray<size_t, 1> > outLocalIndexStoreOnClient; 

/** Map storing received data. Key = sender rank, value = data array.
 *  The map is created in CGrid::computeClientIndex and filled upon receiving data in CField::recvUpdateData() */
         map<int, CArray<size_t, 1> > outLocalIndexStoreOnClientTiled;


/** Indexes calculated based on server-like distribution.
 *  They are used for writing/reading data and only calculated for server level that does the writing/reading.
 *  Along with localIndexToWriteOnClient, these indexes are used to correctly place incoming data. */
         CArray<size_t,1> localIndexToWriteOnServer;

/** Indexes calculated based on client-like distribution.
 *  They are used for writing/reading data and only calculated for server level that does the writing/reading.
 *  Along with localIndexToWriteOnServer, these indexes are used to correctly place incoming data. */
         CArray<size_t,1> localIndexToWriteOnClient;

         CArray<size_t,1> indexFromClients;

         bool hasMask(void) const;
         void checkMask(void);
         void createMask(void);
         void modifyMask(const CArray<int,1>& indexToModify, bool valueToModify = false);
         void modifyMaskSize(const std::vector<int>& newDimensionSize, bool newValue = false);

         void computeGridGlobalDimension(const std::vector<CDomain*>& domains,
                                         const std::vector<CAxis*>& axis,
                                         const std::vector<CScalar*>& scalars,
                                         const CArray<int,1>& axisDomainOrder);

         int getNTiles();
         bool isTiled(void) const;
         bool isTiledOnly(void) const;

      private:
       template<int N>
       void checkGridMask(CArray<bool,N>& gridMask,
                          const std::vector<CArray<bool,1>* >& domainMasks,
                          const std::vector<CArray<bool,1>* >& axisMasks,
                          const CArray<int,1>& axisDomainOrder,
                          bool createMask = false);
        template<int N>
        void modifyGridMask(CArray<bool,N>& gridMask, const CArray<int,1>& indexToModify, bool valueToModify);

        template<int N>
        void modifyGridMaskSize(CArray<bool,N>& gridMask, const std::vector<int>& eachDimSize, bool newValue);

        void storeField_arr(const double* const data, CArray<double, 1>& stored) const;
        void restoreField_arr(const CArray<double, 1>& stored, double* const data) const;
        void uncompressField_arr(const double* const data, CArray<double, 1>& outData) const;
        void maskField_arr(const double* const data, CArray<double, 1>& stored, bool isTiled = false) const;
        void copyTile_arr(const double* const tileData, CArray<double, 1>& stored, int tileId);

        void setVirtualDomainGroup(CDomainGroup* newVDomainGroup);
        void setVirtualAxisGroup(CAxisGroup* newVAxisGroup);
        void setVirtualScalarGroup(CScalarGroup* newVScalarGroup);

        void setDomainList(const std::vector<CDomain*> domains = std::vector<CDomain*>());
        void setAxisList(const std::vector<CAxis*> axis = std::vector<CAxis*>());
        void setScalarList(const std::vector<CScalar*> scalars = std::vector<CScalar*>());

        CDomainGroup* getVirtualDomainGroup() const;
        CAxisGroup* getVirtualAxisGroup() const;
        CScalarGroup* getVirtualScalarGroup() const;

        void checkAttributesAfterTransformation();
        void setTransformationAlgorithms();
        void computeIndexByElement(const std::vector<std::unordered_map<size_t,std::vector<int> > >& indexServerOnElement,
                                   const CContextClient* client,
                                   CClientServerMapping::GlobalIndexMap& globalIndexOnServer);
        int computeGridGlobalDimension(std::vector<int>& globalDim,
                                       const std::vector<CDomain*> domains,
                                       const std::vector<CAxis*> axis,
                                       const std::vector<CScalar*> scalars,
                                       const CArray<int,1>& axisDomainOrder);
        int getDistributedDimension();

        void computeClientIndex();
        void computeClientIndexTiled();
        void computeConnectedClients();
        void computeClientIndexScalarGrid(); 
        void computeConnectedClientsScalarGrid(); 

        void computeTileIndex();

      private:

/** Clients that have to send a grid. There can be multiple clients in case of secondary server, otherwise only one client. */
        std::list<CContextClient*> clients;
        std::set<CContextClient*> clientsSet;

        bool isChecked;
        bool isDomainAxisChecked;
        bool isIndexSent;

        int nTiles_;
/** True if tiled data is defined on the grid */
        bool isTiled_;
/** True if ONLY tiled data is defined on the grid */
        bool isTiledOnly_;

/** Vector containing local domain indexes for each tile */
        std::vector<CArray<int,1> > storeTileIndex;

        CDomainGroup* vDomainGroup_;
        CAxisGroup* vAxisGroup_;
        CScalarGroup* vScalarGroup_;
        std::vector<std::string> axisList_, domList_, scalarList_;
        bool isAxisListSet, isDomListSet, isScalarListSet;

/** Client-like distribution calculated based on the knowledge of the entire grid */
        CDistributionClient* clientDistribution_;

/** Client-like distribution calculated based on the knowledge of the entire grid in case of a tiled domain */
        CDistributionClient* clientDistributionTiled_;


/** Server-like distribution calculated upon receiving indexes */
        CDistributionServer* serverDistribution_;

        CClientServerMapping* clientServerMap_;
        size_t writtenDataSize_;
        int numberWrittenIndexes_, totalNumberWrittenIndexes_, offsetWrittenIndexes_;

/** Map storing local ranks of connected receivers. Key = size of receiver's intracomm.
  * It is calculated in computeConnectedClients(). */
        std::map<int, std::vector<int> > connectedServerRank_;

/** Map storing the size of data to be send. Key = size of receiver's intracomm
  * It is calculated in computeConnectedClients(). */
        std::map<int, std::map<int,size_t> > connectedDataSize_;

/** Ranks of connected receivers in case of reading. It is calculated in recvIndex(). */
        std::vector<int> connectedServerRankRead_;

/** Size of data to be send in case of reading. It is calculated in recvIndex(). */
        std::map<int,size_t> connectedDataSizeRead_;

        bool isDataDistributed_;        
         //! True if and only if the data defined on the grid can be outputted in a compressed way
        bool isCompressible_;
        std::set<std::string> relFilesCompressed;

        bool isTransformed_, isGenerated_;
        bool computedWrittenIndex_;
        std::vector<int> axisPositionInGrid_;
        CGridTransformation* transformations_;
        bool hasDomainAxisBaseRef_;        
        std::map<CGrid*, std::pair<bool,StdString> > gridSrc_;
        bool hasTransform_;

/** Map storing global indexes of server-like (band-wise) distribution for sending to receivers.
  * Key = size of receiver's intracomm.
  */
//        std::map<CContextClient*, CClientServerMapping::GlobalIndexMap> globalIndexOnServer_;
        std::map<int, CClientServerMapping::GlobalIndexMap> globalIndexOnServer_;


/** List order of axis and domain in a grid, if there is a domain, it will take value 1 (true), axis 0 (false) */
        std::vector<int> order_;

   }; // class CGrid

   ///--------------------------------------------------------------

   template <int n>
   void CGrid::inputField(const CArray<double,n>& field, CArray<double,1>& stored) const
   TRY
   {
//#ifdef __XIOS_DEBUG
      if (this->getDataSize() != field.numElements())
         ERROR("void CGrid::inputField(const  CArray<double,n>& field, CArray<double,1>& stored) const",
                << "[ Awaiting data of size = " << this->getDataSize() << ", "
                << "Received data size = "      << field.numElements() << " ] "
                << "The data array does not have the right size! "
                << "Grid = " << this->getId())
//#endif
      this->storeField_arr(field.dataFirst(), stored);
   }
   CATCH

   template <int n>
   void CGrid::copyTile(const CArray<double,n>& tileData, CArray<double,1>& storedData, int tileId)
   {
      this->copyTile_arr(tileData.dataFirst(), storedData, tileId);
   }

   template <int n>
   void CGrid::maskField(const CArray<double,n>& field, CArray<double,1>& stored, bool isTiled) const
   {
//#ifdef __XIOS_DEBUG
      if (this->getDataSize() != field.numElements())
         ERROR("void CGrid::maskField(const  CArray<double,n>& field, CArray<double,1>& stored) const",
                << "[ Awaiting data of size = " << this->getDataSize() << ", "
                << "Received data size = "      << field.numElements() << " ] "
                << "The data array does not have the right size! "
                << "Grid = " << this->getId())
//#endif
      this->maskField_arr(field.dataFirst(), stored, isTiled);
   }

   template <int n>
   void CGrid::outputField(const CArray<double,1>& stored, CArray<double,n>& field) const
   TRY
   {
//#ifdef __XIOS_DEBUG
      if (this->getDataSize() != field.numElements())
         ERROR("void CGrid::outputField(const CArray<double,1>& stored, CArray<double,n>& field) const",
                << "[ Size of the data = " << this->getDataSize() << ", "
                << "Output data size = "   << field.numElements() << " ] "
                << "The ouput array does not have the right size! "
                << "Grid = " << this->getId())
//#endif
      this->restoreField_arr(stored, field.dataFirst());
   }
   CATCH

   /*!
     This function removes the effect of mask on received data on the server.
     This function only serve for the checking purpose. TODO: Something must be done to seperate mask and data_index from each other in received data
     \data data received data with masking effect on the server
     \outData data without masking effect
   */
   template <int N>
   void CGrid::uncompressField(const CArray<double,N>& data, CArray<double,1>& outData) const
   TRY
   {      
     uncompressField_arr(data.dataFirst(), outData);
   }
   CATCH

   template<int N>
   void CGrid::checkGridMask(CArray<bool,N>& gridMask,
                             const std::vector<CArray<bool,1>* >& domainMasks,
                             const std::vector<CArray<bool,1>* >& axisMasks,
                             const CArray<int,1>& axisDomainOrder,
                             bool createMask)
   TRY
   {
     int idx = 0;
     int numElement = axisDomainOrder.numElements();
     int dim = domainMasks.size() * 2 + axisMasks.size();
     std::vector<CDomain*> domainP = this->getDomains();
     std::vector<CAxis*> axisP = this->getAxis();

     std::vector<int> idxLoop(dim,0), indexMap(numElement), eachDimSize(dim);
     std::vector<int> currentIndex(dim);
     int idxDomain = 0, idxAxis = 0;
    for (int i = 0; i < numElement; ++i)
    {
      indexMap[i] = idx;
      if (2 == axisDomainOrder(i)) {
          eachDimSize[indexMap[i]]   = domainP[idxDomain]->ni;
          eachDimSize[indexMap[i]+1] = domainP[idxDomain]->nj;
          idx += 2; ++idxDomain;
      }
      else if (1 == axisDomainOrder(i)) {
//        eachDimSize[indexMap[i]] = axisMasks[idxAxis]->numElements();
        eachDimSize[indexMap[i]] = axisP[idxAxis]->n;
        ++idx; ++idxAxis;
      }
      else {};
    }

    if (!gridMask.isEmpty() && !createMask)
    {
      for (int i = 0; i < dim; ++i)
      {
        if (gridMask.extent(i) != eachDimSize[i])
          ERROR("CGrid::checkMask(void)",
                << "The mask has one dimension whose size is different from the one of the local grid." << std::endl
                << "Local size of dimension " << i << " is " << eachDimSize[i] << "." << std::endl
                << "Mask size for dimension " << i << " is " << gridMask.extent(i) << "." << std::endl
                << "Grid = " << this->getId())
      }
    }
    else {
        CArrayBoolTraits<CArray<bool,N> >::resizeArray(gridMask,eachDimSize);
        gridMask = true;
    }

    int ssize = gridMask.numElements();
    idx = 0;
    while (idx < ssize)
    {
      for (int i = 0; i < dim-1; ++i)
      {
        if (idxLoop[i] == eachDimSize[i])
        {
          idxLoop[i] = 0;
          ++idxLoop[i+1];
        }
      }

      // Find out outer index
      idxDomain = idxAxis = 0;
      bool maskValue = true;
      for (int i = 0; i < numElement; ++i)
      {
        if (2 == axisDomainOrder(i))
        {
          int idxTmp = idxLoop[indexMap[i]] + idxLoop[indexMap[i]+1] * eachDimSize[indexMap[i]];
          if (idxTmp < (*domainMasks[idxDomain]).numElements())
            maskValue = maskValue && (*domainMasks[idxDomain])(idxTmp);
          else
            maskValue = false;
          ++idxDomain;
        }
        else if (1 == axisDomainOrder(i))
        {
          int idxTmp = idxLoop[indexMap[i]];
          if (idxTmp < (*axisMasks[idxAxis]).numElements())
            maskValue = maskValue && (*axisMasks[idxAxis])(idxTmp);
          else
            maskValue = false;

          ++idxAxis;
        }
      }

      int maskIndex = idxLoop[0];
      int mulDim = 1;
      for (int k = 1; k < dim; ++k)
      {
        mulDim *= eachDimSize[k-1];
        maskIndex += idxLoop[k]*mulDim;
      }
      *(gridMask.dataFirst()+maskIndex) &= maskValue;

      ++idxLoop[0];
      ++idx;
    }
   }
   CATCH_DUMP_ATTR

   template<int N>
   void CGrid::modifyGridMaskSize(CArray<bool,N>& gridMask,
                                  const std::vector<int>& eachDimSize,
                                  bool newValue)
   TRY
   {
      if (N != eachDimSize.size())
      {
        // ERROR("CGrid::modifyGridMaskSize(CArray<bool,N>& gridMask,
        //                                  const std::vector<int>& eachDimSize,
        //                                  bool newValue)",
        //       << "Dimension size of the mask is different from input dimension size." << std::endl
        //       << "Mask dimension is " << N << "." << std::endl
        //       << "Input dimension is " << eachDimSize.size() << "." << std::endl
        //       << "Grid = " << this->getId())
      }
      CArrayBoolTraits<CArray<bool,N> >::resizeArray(gridMask,eachDimSize);
      gridMask = newValue;
   }
   CATCH_DUMP_ATTR
                                 

   /*!
     Modify the current mask of grid, the local index to be modified will take value false
     \param [in/out] gridMask current mask of grid
     \param [in] indexToModify local index to modify
   */
   template<int N>
   void CGrid::modifyGridMask(CArray<bool,N>& gridMask, const CArray<int,1>& indexToModify, bool valueToModify)
   TRY
   {     
     int num = indexToModify.numElements();
     for (int idx = 0; idx < num; ++idx)
     {
       *(gridMask.dataFirst()+indexToModify(idx)) = valueToModify;
     }
   }
   CATCH_DUMP_ATTR

   ///--------------------------------------------------------------



   // Declare/Define CGridGroup and CGridDefinition
   DECLARE_GROUP(CGrid);

   ///--------------------------------------------------------------

} // namespace xios

#endif // __XIOS_CGrid__
