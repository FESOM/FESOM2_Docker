#include "context.hpp"
#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"

#include "calendar_type.hpp"
#include "duration.hpp"

#include "context_client.hpp"
#include "context_server.hpp"
#include "nc4_data_output.hpp"
#include "node_type.hpp"
#include "message.hpp"
#include "type.hpp"
#include "xios_spl.hpp"
#include "timer.hpp"
#include "memtrack.hpp"
#include <limits>
#include <fstream>
#include "server.hpp"
#include "distribute_file_server2.hpp"

namespace xios {

  std::shared_ptr<CContextGroup> CContext::root;

   /// ////////////////////// Définitions ////////////////////// ///

   CContext::CContext(void)
      : CObjectTemplate<CContext>(), CContextAttributes()
      , calendar(), hasClient(false), hasServer(false)
      , isPostProcessed(false), finalized(false)
      , idServer_(), client(0), server(0)
      , allProcessed(false), countChildCtx_(0)

   { /* Ne rien faire de plus */ }

   CContext::CContext(const StdString & id)
      : CObjectTemplate<CContext>(id), CContextAttributes()
      , calendar(), hasClient(false), hasServer(false)
      , isPostProcessed(false), finalized(false)
      , idServer_(), client(0), server(0)
      , allProcessed(false), countChildCtx_(0)
   { /* Ne rien faire de plus */ }

   CContext::~CContext(void)
   {
     delete client;
     delete server;
     for (std::vector<CContextClient*>::iterator it = clientPrimServer.begin(); it != clientPrimServer.end(); it++)  delete *it;
     for (std::vector<CContextServer*>::iterator it = serverPrimServer.begin(); it != serverPrimServer.end(); it++)  delete *it;

   }

   //----------------------------------------------------------------
   //! Get name of context
   StdString CContext::GetName(void)   { return (StdString("context")); }
   StdString CContext::GetDefName(void){ return (CContext::GetName()); }
   ENodeType CContext::GetType(void)   { return (eContext); }

   //----------------------------------------------------------------

   /*!
   \brief Get context group (context root)
   \return Context root
   */
   CContextGroup* CContext::getRoot(void)
   TRY
   {
      if (root.get()==NULL) root=std::shared_ptr<CContextGroup>(new CContextGroup(xml::CXMLNode::GetRootName()));
      return root.get();
   }
   CATCH

   //----------------------------------------------------------------

   /*!
   \brief Get calendar of a context
   \return Calendar
   */
   std::shared_ptr<CCalendar> CContext::getCalendar(void) const
   TRY
   {
      return (this->calendar);
   }
   CATCH

   //----------------------------------------------------------------

   /*!
   \brief Set a context with a calendar
   \param[in] newCalendar new calendar
   */
   void CContext::setCalendar(std::shared_ptr<CCalendar> newCalendar)
   TRY
   {
      this->calendar = newCalendar;
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------
   /*!
   \brief Parse xml file and write information into context object
   \param [in] node xmld node corresponding in xml file
   */
   void CContext::parse(xml::CXMLNode & node)
   TRY
   {
      CContext::SuperClass::parse(node);

      // PARSING POUR GESTION DES ENFANTS
      xml::THashAttributes attributes = node.getAttributes();

      if (attributes.end() != attributes.find("src"))
      {
         StdIFStream ifs ( attributes["src"].c_str() , StdIFStream::in );
         if ( (ifs.rdstate() & std::ifstream::failbit ) != 0 )
            ERROR("void CContext::parse(xml::CXMLNode & node)",
                  <<endl<< "Can not open <"<<attributes["src"].c_str()<<"> file" );
         if (!ifs.good())
            ERROR("CContext::parse(xml::CXMLNode & node)",
                  << "[ filename = " << attributes["src"] << " ] Bad xml stream !");
         xml::CXMLParser::ParseInclude(ifs, attributes["src"], *this);
      }

      if (node.getElementName().compare(CContext::GetName()))
         DEBUG("Le noeud is wrong defined but will be considered as a context !");

      if (!(node.goToChildElement()))
      {
         DEBUG("Le context ne contient pas d'enfant !");
      }
      else
      {
         do { // Parcours des contextes pour traitement.

            StdString name = node.getElementName();
            attributes.clear();
            attributes = node.getAttributes();

            if (attributes.end() != attributes.find("id"))
            {
              DEBUG(<< "Definition node has an id,"
                    << "it will not be taking account !");
            }

#define DECLARE_NODE(Name_, name_)    \
   if (name.compare(C##Name_##Definition::GetDefName()) == 0) \
   { C##Name_##Definition::create(C##Name_##Definition::GetDefName()) -> parse(node); continue; }
#define DECLARE_NODE_PAR(Name_, name_)
#include "node_type.conf"

            DEBUG(<< "The element \'"     << name
                  << "\' in the context \'" << CContext::getCurrent()->getId()
                  << "\' is not a definition !");

         } while (node.goToNextElement());

         node.goToParentElement(); // Retour au parent
      }
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------
   //! Show tree structure of context
   void CContext::ShowTree(StdOStream & out)
   TRY
   {
      StdString currentContextId = CContext::getCurrent() -> getId();
      std::vector<CContext*> def_vector =
         CContext::getRoot()->getChildList();
      std::vector<CContext*>::iterator
         it = def_vector.begin(), end = def_vector.end();

      out << "<? xml version=\"1.0\" ?>" << std::endl;
      out << "<"  << xml::CXMLNode::GetRootName() << " >" << std::endl;

      for (; it != end; it++)
      {
         CContext* context = *it;
         CContext::setCurrent(context->getId());
         out << *context << std::endl;
      }

      out << "</" << xml::CXMLNode::GetRootName() << " >" << std::endl;
      CContext::setCurrent(currentContextId);
   }
   CATCH

   //----------------------------------------------------------------

   //! Convert context object into string (to print)
   StdString CContext::toString(void) const
   TRY
   {
      StdOStringStream oss;
      oss << "<" << CContext::GetName()
          << " id=\"" << this->getId() << "\" "
          << SuperClassAttribute::toString() << ">" << std::endl;
      if (!this->hasChild())
      {
         //oss << "<!-- No definition -->" << std::endl; // fait planter l'incrémentation
      }
      else
      {

#define DECLARE_NODE(Name_, name_)    \
   if (C##Name_##Definition::has(C##Name_##Definition::GetDefName())) \
   oss << * C##Name_##Definition::get(C##Name_##Definition::GetDefName()) << std::endl;
#define DECLARE_NODE_PAR(Name_, name_)
#include "node_type.conf"

      }
      oss << "</" << CContext::GetName() << " >";
      return (oss.str());
   }
   CATCH

   //----------------------------------------------------------------

   /*!
   \brief Find all inheritace among objects in a context.
   \param [in] apply (true) write attributes of parent into ones of child if they are empty
                     (false) write attributes of parent into a new container of child
   \param [in] parent unused
   */
   void CContext::solveDescInheritance(bool apply, const CAttributeMap * const UNUSED(parent))
   TRY
   {
#define DECLARE_NODE(Name_, name_)    \
   if (C##Name_##Definition::has(C##Name_##Definition::GetDefName())) \
     C##Name_##Definition::get(C##Name_##Definition::GetDefName())->solveDescInheritance(apply);
#define DECLARE_NODE_PAR(Name_, name_)
#include "node_type.conf"
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   //! Verify if all root definition in the context have child.
   bool CContext::hasChild(void) const
   TRY
   {
      return (
#define DECLARE_NODE(Name_, name_)    \
   C##Name_##Definition::has(C##Name_##Definition::GetDefName())   ||
#define DECLARE_NODE_PAR(Name_, name_)
#include "node_type.conf"
      false);
}
   CATCH

   //----------------------------------------------------------------

   void CContext::CleanTree(void)
   TRY
   {
#define DECLARE_NODE(Name_, name_) C##Name_##Definition::ClearAllAttributes();
#define DECLARE_NODE_PAR(Name_, name_)
#include "node_type.conf"
   }
   CATCH

   ///---------------------------------------------------------------

   //! Initialize client side
   void CContext::initClient(MPI_Comm intraComm, MPI_Comm interComm, CContext* cxtServer /*= 0*/)
   TRY
   {

     hasClient = true;
     MPI_Comm intraCommServer, interCommServer;
     

     if (CServer::serverLevel != 1)
      // initClient is called by client
     {
       client = new CContextClient(this, intraComm, interComm, cxtServer);
       if (cxtServer) // Attached mode
       {
         intraCommServer = intraComm;
         interCommServer = interComm;
       }
       else
       {
         MPI_Comm_dup(intraComm, &intraCommServer);
         comms.push_back(intraCommServer);
         MPI_Comm_dup(interComm, &interCommServer);
         comms.push_back(interCommServer);
       }
/* for registry take the id of client context */
/* for servers, supress the _server_ from id  */
       string contextRegistryId=getId() ;
       size_t pos=contextRegistryId.find("_server_") ;
       if (pos!=std::string::npos)  contextRegistryId=contextRegistryId.substr(0,pos) ;

       registryIn=new CRegistry(intraComm);
       registryIn->setPath(contextRegistryId) ;
       if (client->clientRank==0) registryIn->fromFile("xios_registry.bin") ;
       registryIn->bcastRegistry() ;
       registryOut=new CRegistry(intraComm) ;
       
       registryOut->setPath(contextRegistryId) ;

       server = new CContextServer(this, intraCommServer, interCommServer);
     }
     else
     // initClient is called by primary server
     {
       clientPrimServer.push_back(new CContextClient(this, intraComm, interComm));
       MPI_Comm_dup(intraComm, &intraCommServer);
       comms.push_back(intraCommServer);
       MPI_Comm_dup(interComm, &interCommServer);
       comms.push_back(interCommServer);
       serverPrimServer.push_back(new CContextServer(this, intraCommServer, interCommServer));
     }
   }
   CATCH_DUMP_ATTR

   /*!
    Sets client buffers.
    \param [in] contextClient
    \param [in] bufferForWriting True if buffers are used for sending data for writing
    This flag is only true for client and server-1 for communication with server-2
  */
   void CContext::setClientServerBuffer(CContextClient* contextClient, bool bufferForWriting)
   TRY
   {
      // Estimated minimum event size for small events (10 is an arbitrary constant just for safety)
     const size_t minEventSize = CEventClient::headerSize + getIdServer().size() + 10 * sizeof(int);

      // Ensure there is at least some room for 20 of such events in the buffers
      size_t minBufferSize = std::max(CXios::minBufferSize, 20 * minEventSize);

#define DECLARE_NODE(Name_, name_)    \
     if (minBufferSize < sizeof(C##Name_##Definition)) minBufferSize = sizeof(C##Name_##Definition);
#define DECLARE_NODE_PAR(Name_, name_)
#include "node_type.conf"
#undef DECLARE_NODE
#undef DECLARE_NODE_PAR

     // Compute the buffer sizes needed to send the attributes and data corresponding to fields
     std::map<int, StdSize> maxEventSize;
     std::map<int, StdSize> bufferSize = getAttributesBufferSize(maxEventSize, contextClient, bufferForWriting);
     std::map<int, StdSize> dataBufferSize = getDataBufferSize(maxEventSize, contextClient, bufferForWriting);

     std::map<int, StdSize>::iterator it, ite = dataBufferSize.end();
     for (it = dataBufferSize.begin(); it != ite; ++it)
       if (it->second > bufferSize[it->first]) bufferSize[it->first] = it->second;

     // Apply the buffer size factor, check that we are above the minimum buffer size and below the maximum size
     ite = bufferSize.end();
     for (it = bufferSize.begin(); it != ite; ++it)
     {
       it->second *= CXios::bufferSizeFactor;
       if (it->second < minBufferSize) it->second = minBufferSize;
       if (it->second > CXios::maxBufferSize) it->second = CXios::maxBufferSize;
     }

     // Leaders will have to send some control events so ensure there is some room for those in the buffers
     if (contextClient->isServerLeader())
     {
       const std::list<int>& ranks = contextClient->getRanksServerLeader();
       for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
       {
         if (!bufferSize.count(*itRank))
         {
           bufferSize[*itRank] = minBufferSize;
           maxEventSize[*itRank] = minEventSize;
         }
       }
     }
     contextClient->setBufferSize(bufferSize, maxEventSize);
   }
   CATCH_DUMP_ATTR

   //! Verify whether a context is initialized
   bool CContext::isInitialized(void)
   TRY
   {
     return hasClient;
   }
   CATCH_DUMP_ATTR

   void CContext::initServer(MPI_Comm intraComm, MPI_Comm interComm, CContext* cxtClient /*= 0*/)
   TRY
   {
     hasServer=true;
     server = new CContextServer(this,intraComm,interComm);

/* for registry take the id of client context */
/* for servers, supress the _server_ from id  */
     string contextRegistryId=getId() ;
     size_t pos=contextRegistryId.find("_server_") ;
     if (pos!=std::string::npos)  contextRegistryId=contextRegistryId.substr(0,pos) ;
       
     registryIn=new CRegistry(intraComm);
     registryIn->setPath(contextRegistryId) ;
     if (server->intraCommRank==0) registryIn->fromFile("xios_registry.bin") ;
     registryIn->bcastRegistry() ;
     registryOut=new CRegistry(intraComm) ;
     registryOut->setPath(contextRegistryId) ;

     MPI_Comm intraCommClient, interCommClient;
     if (cxtClient) // Attached mode
     {
       intraCommClient = intraComm;
       interCommClient = interComm;
     }
     else
     {
       MPI_Comm_dup(intraComm, &intraCommClient);
       comms.push_back(intraCommClient);
       MPI_Comm_dup(interComm, &interCommClient);
       comms.push_back(interCommClient);
     }
     client = new CContextClient(this,intraCommClient,interCommClient, cxtClient);
   }
   CATCH_DUMP_ATTR

   //! Try to send the buffers and receive possible answers
  bool CContext::checkBuffersAndListen(bool enableEventsProcessing /*= true*/)
  TRY
  {
    bool clientReady, serverFinished;

    // Only classical servers are non-blocking
    if (CServer::serverLevel == 0)
    {
      client->checkBuffers();
      bool hasTmpBufferedEvent = client->hasTemporarilyBufferedEvent();
      if (hasTmpBufferedEvent)
        hasTmpBufferedEvent = !client->sendTemporarilyBufferedEvent();
      // Don't process events if there is a temporarily buffered event
      return server->eventLoop(!hasTmpBufferedEvent || !enableEventsProcessing);
    }
    else if (CServer::serverLevel == 1)
    {
      if (!finalized)
        client->checkBuffers();
      bool serverFinished = true;
      if (!finalized)
        serverFinished = server->eventLoop(enableEventsProcessing);
      bool serverPrimFinished = true;
      for (int i = 0; i < clientPrimServer.size(); ++i)
      {
        if (!finalized)
          clientPrimServer[i]->checkBuffers();
        if (!finalized)
          serverPrimFinished *= serverPrimServer[i]->eventLoop(enableEventsProcessing);
      }
      return ( serverFinished && serverPrimFinished);
    }

    else if (CServer::serverLevel == 2)
    {
      client->checkBuffers();
      return server->eventLoop(enableEventsProcessing);
    }
  }
   CATCH_DUMP_ATTR

   //! Terminate a context
   void CContext::finalize(void)
   TRY
   {
      if (hasClient && !hasServer) // For now we only use server level 1 to read data
      {
        doPreTimestepOperationsForEnabledReadModeFiles();
      }
     // Send registry upon calling the function the first time
     if (countChildCtx_ == 0)
       if (hasClient) sendRegistry() ;

     // Client:
     // (1) blocking send context finalize to its server
     // (2) blocking receive context finalize from its server
     // (3) some memory deallocations
     if (CXios::isClient)
     {
       // Make sure that client (model) enters the loop only once
       if (countChildCtx_ < 1)
       {
         ++countChildCtx_;

         client->finalize();
         while (client->havePendingRequests())
            client->checkBuffers();

         while (!server->hasFinished())
           server->eventLoop();

         if (hasServer) // Mode attache
         {
           closeAllFile();
           registryOut->hierarchicalGatherRegistry() ;
           if (server->intraCommRank==0) CXios::globalRegistry->mergeRegistry(*registryOut) ;
         }

         //! Deallocate client buffers
         client->releaseBuffers();

         //! Free internally allocated communicators
         for (std::list<MPI_Comm>::iterator it = comms.begin(); it != comms.end(); ++it)
           /* MPI_Comm_free(&(*it)) */ ; // WARNING remove freeing communicator !! --> deadlock raised, to be checked
         comms.clear();

         info(20)<<"CContext: Context <"<<getId()<<"> is finalized."<<endl;
       }
     }
     else if (CXios::isServer)
     {
       // First context finalize message received from a model
       // Send context finalize to its child contexts (if any)
       if (countChildCtx_ == 0)
         for (int i = 0; i < clientPrimServer.size(); ++i)
           clientPrimServer[i]->finalize();

       // (Last) context finalized message received
       if (countChildCtx_ == clientPrimServer.size())
       {
         // Blocking send of context finalize message to its client (e.g. primary server or model)
         info(100)<<"DEBUG: context "<<getId()<<" Send client finalize<<"<<endl ;
         client->finalize();
         bool bufferReleased;
         do
         {
           client->checkBuffers();
           bufferReleased = !client->havePendingRequests();
         } while (!bufferReleased);
         finalized = true;

         closeAllFile(); // Just move to here to make sure that server-level 1 can close files
         if (hasServer && !hasClient)
         {           
           registryOut->hierarchicalGatherRegistry() ;
           if (server->intraCommRank==0) CXios::globalRegistry->mergeRegistry(*registryOut) ;
         }

         //! Deallocate client buffers
         client->releaseBuffers();
         for (int i = 0; i < clientPrimServer.size(); ++i)
           clientPrimServer[i]->releaseBuffers();

         //! Free internally allocated communicators
         for (std::list<MPI_Comm>::iterator it = comms.begin(); it != comms.end(); ++it)
           /* MPI_Comm_free(&(*it)) */;  // WARNING remove freeing communicator !! --> deadlock raised, to be checked
         comms.clear();

         info(20)<<"CContext: Context <"<<getId()<<"> is finalized."<<endl;
       }

       ++countChildCtx_;
     }
   }
   CATCH_DUMP_ATTR

   //! Free internally allocated communicators
   void CContext::freeComms(void)
   TRY
   {
     for (std::list<MPI_Comm>::iterator it = comms.begin(); it != comms.end(); ++it)
       /* MPI_Comm_free(&(*it)) */ ; // WARNING remove freeing communicator !! --> deadlock raised, to be checked
     comms.clear();
   }
   CATCH_DUMP_ATTR

   //! Deallocate buffers allocated by clientContexts
   void CContext::releaseClientBuffers(void)
   TRY
   {
     client->releaseBuffers();
     for (int i = 0; i < clientPrimServer.size(); ++i)
       clientPrimServer[i]->releaseBuffers();
   }
   CATCH_DUMP_ATTR

   void CContext::postProcessingGlobalAttributes()
   TRY
   {
     if (allProcessed) return;  
     
     // After xml is parsed, there are some more works with post processing
     postProcessing();

     // Check grid and calculate its distribution
     checkGridEnabledFields();
 
     // Distribute files between secondary servers according to the data size
     distributeFiles();

     setClientServerBuffer(client, (hasClient && !hasServer));
     for (int i = 0; i < clientPrimServer.size(); ++i)
         setClientServerBuffer(clientPrimServer[i], true);

     if (hasClient)
     {
      // Send all attributes of current context to server
      this->sendAllAttributesToServer();

      // Send all attributes of current calendar
      CCalendarWrapper::get(CCalendarWrapper::GetDefName())->sendAllAttributesToServer();

      // We have enough information to send to server
      // First of all, send all enabled files
      sendEnabledFiles(this->enabledWriteModeFiles);
      // We only use server-level 1 (for now) to read data
      if (!hasServer)
        sendEnabledFiles(this->enabledReadModeFiles);

      // Then, send all enabled fields      
      sendEnabledFieldsInFiles(this->enabledWriteModeFiles);
      if (!hasServer)
        sendEnabledFieldsInFiles(this->enabledReadModeFiles);

      // Then, check whether we have domain_ref, axis_ref or scalar_ref attached to the enabled fields
      // If any, so send them to server
       sendRefDomainsAxisScalars(this->enabledWriteModeFiles);
      if (!hasServer)
        sendRefDomainsAxisScalars(this->enabledReadModeFiles);        

       // Check whether enabled fields have grid_ref, if any, send this info to server
      sendRefGrid(this->enabledFiles);
      // This code may be useful in the future when we want to seperate completely read and write
      // sendRefGrid(this->enabledWriteModeFiles);
      // if (!hasServer)
      //   sendRefGrid(this->enabledReadModeFiles);
      
      // A grid of enabled fields composed of several components which must be checked then their
      // checked attributes should be sent to server
      sendGridComponentEnabledFieldsInFiles(this->enabledFiles); // This code can be seperated in two (one for reading, another for writing)

       // We have a xml tree on the server side and now, it should be also processed
      sendPostProcessing();
       
      // Finally, we send information of grid itself to server 
      sendGridEnabledFieldsInFiles(this->enabledWriteModeFiles);       
      if (!hasServer)
        sendGridEnabledFieldsInFiles(this->enabledReadModeFiles);       
     }
     allProcessed = true;
   }
   CATCH_DUMP_ATTR

   void CContext::sendPostProcessingGlobalAttributes()
   TRY
   {
      // Use correct context client to send message
     // int nbSrvPools = (hasServer) ? clientPrimServer.size() : 1;
    int nbSrvPools = (this->hasServer) ? (this->hasClient ? this->clientPrimServer.size() : 0) : 1;
     for (int i = 0; i < nbSrvPools; ++i)
     {
       CContextClient* contextClientTmp = (0 != clientPrimServer.size()) ? clientPrimServer[i] : client;
       CEventClient event(getType(),EVENT_ID_POST_PROCESS_GLOBAL_ATTRIBUTES);

       if (contextClientTmp->isServerLeader())
       {
         CMessage msg;
         if (hasServer)
           msg<<this->getIdServer(i);
         else
           msg<<this->getIdServer();
         const std::list<int>& ranks = contextClientTmp->getRanksServerLeader();
         for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
           event.push(*itRank,1,msg);
         contextClientTmp->sendEvent(event);
       }
       else contextClientTmp->sendEvent(event);
     }
   }
   CATCH_DUMP_ATTR

   void CContext::recvPostProcessingGlobalAttributes(CEventServer& event)
   TRY
   {
      CBufferIn* buffer=event.subEvents.begin()->buffer;
      string id;
      *buffer>>id;
      get(id)->recvPostProcessingGlobalAttributes(*buffer);
   }
   CATCH

   void CContext::recvPostProcessingGlobalAttributes(CBufferIn& buffer)
   TRY
   {      
      postProcessingGlobalAttributes();
   }
   CATCH_DUMP_ATTR

   /*!
   \brief Close all the context defintion and do processing data
      After everything is well defined on client side, they will be processed and sent to server
   From the version 2.0, sever and client work no more on the same database. Moreover, client(s) will send
   all necessary information to server, from which each server can build its own database.
   Because the role of server is to write out field data on a specific netcdf file,
   the only information that it needs is the enabled files
   and the active fields (fields will be written onto active files)
   */

   void CContext::closeDefinition(void)
   TRY
   {
    CTimer::get("Context : close definition").resume() ;
    postProcessingGlobalAttributes();

    if (hasClient) sendPostProcessingGlobalAttributes();

    // There are some processings that should be done after all of above. For example: check mask or index
    this->buildFilterGraphOfEnabledFields();
    
     if (hasClient && !hasServer)
    {
      buildFilterGraphOfFieldsWithReadAccess();
      postProcessFilterGraph();
    }
    
    checkGridEnabledFields();   

    if (hasClient) this->sendProcessingGridOfEnabledFields();
    if (hasClient) this->sendCloseDefinition();

    // Nettoyage de l'arborescence
    if (hasClient) CleanTree(); // Only on client side??

    if (hasClient)
    {
      sendCreateFileHeader();
      if (!hasServer) startPrefetchingOfEnabledReadModeFiles();
    }
    CTimer::get("Context : close definition").suspend() ;
   }
   CATCH_DUMP_ATTR

   void CContext::findAllEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles)
   TRY
   {
     for (unsigned int i = 0; i < activeFiles.size(); i++)
     (void)activeFiles[i]->getEnabledFields();
   }
   CATCH_DUMP_ATTR

   void CContext::readAttributesOfEnabledFieldsInReadModeFiles()
   TRY
   {
      for (unsigned int i = 0; i < this->enabledReadModeFiles.size(); ++i)
        (void)this->enabledReadModeFiles[i]->readAttributesOfEnabledFieldsInReadMode();
   }
   CATCH_DUMP_ATTR

   void CContext::sendGridComponentEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles)
   TRY
   {
     int size = activeFiles.size();
     for (int i = 0; i < size; ++i)
     {       
       activeFiles[i]->sendGridComponentOfEnabledFields();
     }
   }
   CATCH_DUMP_ATTR

   /*!
      Send active (enabled) fields in file from a client to others
      \param [in] activeFiles files contains enabled fields to send
   */
   void CContext::sendGridEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles)
   TRY
   {
     int size = activeFiles.size();
     for (int i = 0; i < size; ++i)
     {       
       activeFiles[i]->sendGridOfEnabledFields();
     }
   }
   CATCH_DUMP_ATTR

   void CContext::checkGridEnabledFields()
   TRY
   {
     int size = enabledFiles.size();
     for (int i = 0; i < size; ++i)
     {
       enabledFiles[i]->checkGridOfEnabledFields();       
     }
   }
   CATCH_DUMP_ATTR

   /*!
      Check grid of active (enabled) fields in file 
      \param [in] activeFiles files contains enabled fields whose grid needs checking
   */
   void CContext::checkGridEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles)
   TRY
   {
     int size = activeFiles.size();
     for (int i = 0; i < size; ++i)
     {
       activeFiles[i]->checkGridOfEnabledFields();       
     }
   }
   CATCH_DUMP_ATTR

    /*!
      Go up the hierachical tree via field_ref and do check of attributes of fields
      This can be done in a client then all computed information will be sent from this client to others
      \param [in] sendToServer Flag to indicate whether calculated information will be sent
   */
   void CContext::solveOnlyRefOfEnabledFields(bool sendToServer)
   TRY
   {
     int size = this->enabledFiles.size();
     for (int i = 0; i < size; ++i)
     {
       this->enabledFiles[i]->solveOnlyRefOfEnabledFields(sendToServer);
     }

     for (int i = 0; i < size; ++i)
     {
       this->enabledFiles[i]->generateNewTransformationGridDest();
     }
   }
   CATCH_DUMP_ATTR

    /*!
      Go up the hierachical tree via field_ref and do check of attributes of fields.
      The transformation can be done in this step.
      All computed information will be sent from this client to others.
      \param [in] sendToServer Flag to indicate whether calculated information will be sent
   */
   void CContext::solveAllRefOfEnabledFieldsAndTransform(bool sendToServer)
   TRY
   {
     int size = this->enabledFiles.size();
     for (int i = 0; i < size; ++i)
     {
       this->enabledFiles[i]->solveAllRefOfEnabledFieldsAndTransform(sendToServer);
     }
   }
   CATCH_DUMP_ATTR

   void CContext::buildFilterGraphOfEnabledFields()
   TRY
   {
     int size = this->enabledFiles.size();
     for (int i = 0; i < size; ++i)
     {
       this->enabledFiles[i]->buildFilterGraphOfEnabledFields(garbageCollector);
     }
   }
   CATCH_DUMP_ATTR

   void CContext::postProcessFilterGraph()
   TRY
   {
     int size = enabledFiles.size();
     for (int i = 0; i < size; ++i)
     {
        enabledFiles[i]->postProcessFilterGraph();
     }
   }
   CATCH_DUMP_ATTR

   void CContext::startPrefetchingOfEnabledReadModeFiles()
   TRY
   {
     int size = enabledReadModeFiles.size();
     for (int i = 0; i < size; ++i)
     {
        enabledReadModeFiles[i]->prefetchEnabledReadModeFields();
     }
   }
   CATCH_DUMP_ATTR

   void CContext::doPreTimestepOperationsForEnabledReadModeFiles()
   TRY
   {
     int size = enabledReadModeFiles.size();
     for (int i = 0; i < size; ++i)
     {
        enabledReadModeFiles[i]->doPreTimestepOperationsForEnabledReadModeFields();
     }
   }
   CATCH_DUMP_ATTR

   void CContext::doPostTimestepOperationsForEnabledReadModeFiles()
   TRY
   {
     int size = enabledReadModeFiles.size();
     for (int i = 0; i < size; ++i)
     {
        enabledReadModeFiles[i]->doPostTimestepOperationsForEnabledReadModeFields();
     }
   }
   CATCH_DUMP_ATTR

  void CContext::findFieldsWithReadAccess(void)
  TRY
  {
    fieldsWithReadAccess.clear();
    const vector<CField*> allFields = CField::getAll();
    for (size_t i = 0; i < allFields.size(); ++i)
    {
      CField* field = allFields[i];

      if (field->file && !field->file->mode.isEmpty() && field->file->mode == CFile::mode_attr::read)
        field->read_access = true;
      else if (!field->read_access.isEmpty() && field->read_access && (field->enabled.isEmpty() || field->enabled))
        fieldsWithReadAccess.push_back(field);
    }
  }
  CATCH_DUMP_ATTR

  void CContext::solveAllRefOfFieldsWithReadAccess()
  TRY
  {
    for (size_t i = 0; i < fieldsWithReadAccess.size(); ++i)
      fieldsWithReadAccess[i]->solveAllReferenceEnabledField(false);
  }
  CATCH_DUMP_ATTR

  void CContext::buildFilterGraphOfFieldsWithReadAccess()
  TRY
  {
    for (size_t i = 0; i < fieldsWithReadAccess.size(); ++i)
      fieldsWithReadAccess[i]->buildFilterGraph(garbageCollector, true);
  }
  CATCH_DUMP_ATTR

   void CContext::solveAllInheritance(bool apply)
   TRY
   {
     // Résolution des héritages descendants (càd des héritages de groupes)
     // pour chacun des contextes.
      solveDescInheritance(apply);

     // Résolution des héritages par référence au niveau des fichiers.
      const vector<CFile*> allFiles=CFile::getAll();
      const vector<CGrid*> allGrids= CGrid::getAll();

      if (hasClient && !hasServer)
      //if (hasClient)
      {
        for (unsigned int i = 0; i < allFiles.size(); i++)
          allFiles[i]->solveFieldRefInheritance(apply);
      }

      unsigned int vecSize = allGrids.size();
      unsigned int i = 0;
      for (i = 0; i < vecSize; ++i)
        allGrids[i]->solveDomainAxisRefInheritance(apply);

   }
  CATCH_DUMP_ATTR

   void CContext::findEnabledFiles(void)
   TRY
   {
      const std::vector<CFile*> allFiles = CFile::getAll();
      const CDate& initDate = calendar->getInitDate();

      for (unsigned int i = 0; i < allFiles.size(); i++)
         if (!allFiles[i]->enabled.isEmpty()) // Si l'attribut 'enabled' est défini.
         {
            if (allFiles[i]->enabled.getValue()) // Si l'attribut 'enabled' est fixé à vrai.
            {
              if (allFiles[i]->output_freq.isEmpty())
              {
                 ERROR("CContext::findEnabledFiles()",
                     << "Mandatory attribute output_freq must be defined for file \""<<allFiles[i]->getFileOutputName()
                     <<" \".")
              }
              if ((initDate + allFiles[i]->output_freq.getValue()) < (initDate + this->getCalendar()->getTimeStep()))
              {
                error(0)<<"WARNING: void CContext::findEnabledFiles()"<<endl
                    << "Output frequency in file \""<<allFiles[i]->getFileOutputName()
                    <<"\" is less than the time step. File will not be written."<<endl;
              }
              else
               enabledFiles.push_back(allFiles[i]);
            }
         }
         else
         {
           if (allFiles[i]->output_freq.isEmpty())
           {
              ERROR("CContext::findEnabledFiles()",
                  << "Mandatory attribute output_freq must be defined for file \""<<allFiles[i]->getFileOutputName()
                  <<" \".")
           }
           if ( (initDate + allFiles[i]->output_freq.getValue()) < (initDate + this->getCalendar()->getTimeStep()))
           {
             error(0)<<"WARNING: void CContext::findEnabledFiles()"<<endl
                 << "Output frequency in file \""<<allFiles[i]->getFileOutputName()
                 <<"\" is less than the time step. File will not be written."<<endl;
           }
           else
             enabledFiles.push_back(allFiles[i]); // otherwise true by default
         }

      if (enabledFiles.size() == 0)
         DEBUG(<<"Aucun fichier ne va être sorti dans le contexte nommé \""
               << getId() << "\" !");

   }
   CATCH_DUMP_ATTR

   void CContext::distributeFiles(void)
   TRY
   {
     bool distFileMemory=false ;
     distFileMemory=CXios::getin<bool>("server2_dist_file_memory", distFileMemory);

     if (distFileMemory) distributeFileOverMemoryBandwith() ;
     else distributeFileOverBandwith() ;
   }
   CATCH_DUMP_ATTR

   void CContext::distributeFileOverBandwith(void)
   TRY
   {
     double eps=std::numeric_limits<double>::epsilon()*10 ;
     
     // If primary server
     if (hasServer && hasClient)
     {
       std::ofstream ofs(("distribute_file_"+getId()+".dat").c_str(), std::ofstream::out);
       int nbPools = clientPrimServer.size();

       // (1) Find all enabled files in write mode
       // for (int i = 0; i < this->enabledFiles.size(); ++i)
       // {
       //   if (enabledFiles[i]->mode.isEmpty() || (!enabledFiles[i]->mode.isEmpty() && enabledFiles[i]->mode.getValue() == CFile::mode_attr::write ))
       //    enabledWriteModeFiles.push_back(enabledFiles[i]);
       // }

       // (2) Estimate the data volume for each file
       int size = this->enabledWriteModeFiles.size();
       std::vector<std::pair<double, CFile*> > dataSizeMap;
       double dataPerPool = 0;
       int nfield=0 ;
       ofs<<size<<endl ;
       for (size_t i = 0; i < size; ++i)
       {
         CFile* file = this->enabledWriteModeFiles[i];
         ofs<<file->getId()<<endl ;
         StdSize dataSize=0;
         std::vector<CField*> enabledFields = file->getEnabledFields();
         size_t numEnabledFields = enabledFields.size();
         ofs<<numEnabledFields<<endl ;
         for (size_t j = 0; j < numEnabledFields; ++j)
         {
           dataSize += enabledFields[j]->getGlobalWrittenSize() ;
           ofs<<enabledFields[j]->grid->getId()<<endl ;
           ofs<<enabledFields[j]->getGlobalWrittenSize()<<endl ;
         }
         double outFreqSec = (Time)(calendar->getCurrentDate()+file->output_freq)-(Time)(calendar->getCurrentDate()) ;
         double dataSizeSec= dataSize/ outFreqSec;
         ofs<<dataSizeSec<<endl ;
         nfield++ ;
// add epsilon*nField to dataSizeSec in order to  preserve reproductive ordering when sorting
         dataSizeMap.push_back(make_pair(dataSizeSec + dataSizeSec * eps * nfield , file));
         dataPerPool += dataSizeSec;
       }
       dataPerPool /= nbPools;
       std::sort(dataSizeMap.begin(), dataSizeMap.end());

       // (3) Assign contextClient to each enabled file

       std::multimap<double,int> poolDataSize ;
// multimap is not garanty to preserve stable sorting in c++98 but it seems it does for c++11

       int j;
       double dataSize ;
       for (j = 0 ; j < nbPools ; ++j) poolDataSize.insert(std::pair<double,int>(0.,j)) ;  
              
       for (int i = dataSizeMap.size()-1; i >= 0; --i)
       {
         dataSize=(*poolDataSize.begin()).first ;
         j=(*poolDataSize.begin()).second ;
         dataSizeMap[i].second->setContextClient(clientPrimServer[j]);
         dataSize+=dataSizeMap[i].first;
         poolDataSize.erase(poolDataSize.begin()) ;
         poolDataSize.insert(std::pair<double,int>(dataSize,j)) ; 
       }

       for (std::multimap<double,int>:: iterator it=poolDataSize.begin() ; it!=poolDataSize.end(); ++it) info(30)<<"Load Balancing for servers (perfect=1) : "<<it->second<<" :  ratio "<<it->first*1./dataPerPool<<endl ;
 
       for (int i = 0; i < this->enabledReadModeFiles.size(); ++i)
       {
         enabledReadModeFiles[i]->setContextClient(client);          
       }
     }
     else
     {
       for (int i = 0; i < this->enabledFiles.size(); ++i)
         enabledFiles[i]->setContextClient(client);
     }
   }
   CATCH_DUMP_ATTR

   void CContext::distributeFileOverMemoryBandwith(void)
   TRY
   {
     // If primary server
     if (hasServer && hasClient)
     {
       int nbPools = clientPrimServer.size();
       double ratio=0.5 ;
       ratio=CXios::getin<double>("server2_dist_file_memory_ratio", ratio);

       int nFiles = this->enabledWriteModeFiles.size();
       vector<SDistFile> files(nFiles);
       vector<SDistGrid> grids;
       map<string,int> gridMap ;
       string gridId; 
       int gridIndex=0 ;

       for (size_t i = 0; i < nFiles; ++i)
       {
         StdSize dataSize=0;
         CFile* file = this->enabledWriteModeFiles[i];
         std::vector<CField*> enabledFields = file->getEnabledFields();
         size_t numEnabledFields = enabledFields.size();

         files[i].id_=file->getId() ;
         files[i].nbGrids_=numEnabledFields;
         files[i].assignedGrid_ = new int[files[i].nbGrids_] ;
         
         for (size_t j = 0; j < numEnabledFields; ++j)
         {
           gridId=enabledFields[j]->grid->getId() ;
           if (gridMap.find(gridId)==gridMap.end())
           {
              gridMap[gridId]=gridIndex  ;
              SDistGrid newGrid; 
              grids.push_back(newGrid) ;
              gridIndex++ ;
           }
           files[i].assignedGrid_[j]=gridMap[gridId] ;
           grids[files[i].assignedGrid_[j]].size_=enabledFields[j]->getGlobalWrittenSize() ;
           dataSize += enabledFields[j]->getGlobalWrittenSize() ; // usefull
         }
         double outFreqSec = (Time)(calendar->getCurrentDate()+file->output_freq)-(Time)(calendar->getCurrentDate()) ;
         files[i].bandwith_= dataSize/ outFreqSec ;
       }

       double bandwith=0 ;
       double memory=0 ;
   
       for(int i=0; i<nFiles; i++)  bandwith+=files[i].bandwith_ ;
       for(int i=0; i<nFiles; i++)  files[i].bandwith_ = files[i].bandwith_/bandwith * ratio ;

       for(int i=0; i<grids.size(); i++)  memory+=grids[i].size_ ;
       for(int i=0; i<grids.size(); i++)  grids[i].size_ = grids[i].size_ / memory * (1.0-ratio) ;
       
       distributeFileOverServer2(nbPools, grids.size(), &grids[0], nFiles, &files[0]) ;

       vector<double> memorySize(nbPools,0.) ;
       vector< set<int> > serverGrids(nbPools) ;
       vector<double> bandwithSize(nbPools,0.) ;
       
       for (size_t i = 0; i < nFiles; ++i)
       {
         bandwithSize[files[i].assignedServer_] += files[i].bandwith_* bandwith /ratio ;
         for(int j=0 ; j<files[i].nbGrids_;j++)
         {
           if (serverGrids[files[i].assignedServer_].find(files[i].assignedGrid_[j]) == serverGrids[files[i].assignedServer_].end())
           {
             memorySize[files[i].assignedServer_]+= grids[files[i].assignedGrid_[j]].size_ * memory / (1.0-ratio);
             serverGrids[files[i].assignedServer_].insert(files[i].assignedGrid_[j]) ;
           }
         }
         enabledWriteModeFiles[i]->setContextClient(clientPrimServer[files[i].assignedServer_]) ;
         delete [] files[i].assignedGrid_ ;
       }

       for (int i = 0; i < nbPools; ++i) info(100)<<"Pool server level2 "<<i<<"   assigned file bandwith "<<bandwithSize[i]*86400.*4./1024/1024.<<" Mb / days"<<endl ;
       for (int i = 0; i < nbPools; ++i) info(100)<<"Pool server level2 "<<i<<"   assigned grid memory "<<memorySize[i]*100/1024./1024.<<" Mb"<<endl ;


       for (int i = 0; i < this->enabledReadModeFiles.size(); ++i)
       {
         enabledReadModeFiles[i]->setContextClient(client);          
       }

   }
   else
   {
     for (int i = 0; i < this->enabledFiles.size(); ++i)
        enabledFiles[i]->setContextClient(client);
   }
}
   CATCH_DUMP_ATTR

   /*!
      Find all files in write mode
   */
   void CContext::findEnabledWriteModeFiles(void)
   TRY
   {
     int size = this->enabledFiles.size();
     for (int i = 0; i < size; ++i)
     {
       if (enabledFiles[i]->mode.isEmpty() || 
          (!enabledFiles[i]->mode.isEmpty() && enabledFiles[i]->mode.getValue() == CFile::mode_attr::write ))
        enabledWriteModeFiles.push_back(enabledFiles[i]);
     }
   }
   CATCH_DUMP_ATTR

   /*!
      Find all files in read mode
   */
   void CContext::findEnabledReadModeFiles(void)
   TRY
   {
     int size = this->enabledFiles.size();
     for (int i = 0; i < size; ++i)
     {
       if (!enabledFiles[i]->mode.isEmpty() && enabledFiles[i]->mode.getValue() == CFile::mode_attr::read)
        enabledReadModeFiles.push_back(enabledFiles[i]);
     }
   }
   CATCH_DUMP_ATTR

   void CContext::closeAllFile(void)
   TRY
   {
     std::vector<CFile*>::const_iterator
            it = this->enabledFiles.begin(), end = this->enabledFiles.end();

     for (; it != end; it++)
     {
       info(30)<<"Closing File : "<<(*it)->getId()<<endl;
       (*it)->close();
     }
   }
   CATCH_DUMP_ATTR

   /*!
   \brief Dispatch event received from client
      Whenever a message is received in buffer of server, it will be processed depending on
   its event type. A new event type should be added in the switch list to make sure
   it processed on server side.
   \param [in] event: Received message
   */
   bool CContext::dispatchEvent(CEventServer& event)
   TRY
   {

      if (SuperClass::dispatchEvent(event)) return true;
      else
      {
        switch(event.type)
        {
           case EVENT_ID_CLOSE_DEFINITION :
             recvCloseDefinition(event);
             return true;
             break;
           case EVENT_ID_UPDATE_CALENDAR:
             recvUpdateCalendar(event);
             return true;
             break;
           case EVENT_ID_CREATE_FILE_HEADER :
             recvCreateFileHeader(event);
             return true;
             break;
           case EVENT_ID_POST_PROCESS:
             recvPostProcessing(event);
             return true;
            case EVENT_ID_SEND_REGISTRY:
             recvRegistry(event);
             return true;
             break;
            case EVENT_ID_POST_PROCESS_GLOBAL_ATTRIBUTES:
             recvPostProcessingGlobalAttributes(event);
             return true;
             break;
            case EVENT_ID_PROCESS_GRID_ENABLED_FIELDS:
             recvProcessingGridOfEnabledFields(event);
             return true;
             break;
           default :
             ERROR("bool CContext::dispatchEvent(CEventServer& event)",
                    <<"Unknown Event");
           return false;
         }
      }
   }
   CATCH

   //! Client side: Send a message to server to make it close
   void CContext::sendCloseDefinition(void)
   TRY
   {
     // Use correct context client to send message
     int nbSrvPools = (this->hasServer) ? (this->hasClient ? this->clientPrimServer.size() : 0) : 1;
     for (int i = 0; i < nbSrvPools; ++i)
     {
       CContextClient* contextClientTmp = (hasServer) ? clientPrimServer[i] : client;
       CEventClient event(getType(),EVENT_ID_CLOSE_DEFINITION);
       if (contextClientTmp->isServerLeader())
       {
         CMessage msg;
         if (hasServer)
           msg<<this->getIdServer(i);
         else
           msg<<this->getIdServer();
         const std::list<int>& ranks = contextClientTmp->getRanksServerLeader();
         for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
           event.push(*itRank,1,msg);
         contextClientTmp->sendEvent(event);
       }
       else contextClientTmp->sendEvent(event);
     }
   }
   CATCH_DUMP_ATTR

   //! Server side: Receive a message of client announcing a context close
   void CContext::recvCloseDefinition(CEventServer& event)
   TRY
   {
      CBufferIn* buffer=event.subEvents.begin()->buffer;
      string id;
      *buffer>>id;
      get(id)->closeDefinition();
   }
   CATCH

   //! Client side: Send a message to update calendar in each time step
   void CContext::sendUpdateCalendar(int step)
   TRY
   {
     // Use correct context client to send message
    int nbSrvPools = (this->hasServer) ? (this->hasClient ? this->clientPrimServer.size() : 0) : 1;
     for (int i = 0; i < nbSrvPools; ++i)
     {
       CContextClient* contextClientTmp = (hasServer) ? clientPrimServer[i] : client;
       CEventClient event(getType(),EVENT_ID_UPDATE_CALENDAR);

         if (contextClientTmp->isServerLeader())
         {
           CMessage msg;
           if (hasServer)
             msg<<this->getIdServer(i)<<step;
           else
             msg<<this->getIdServer()<<step;
           const std::list<int>& ranks = contextClientTmp->getRanksServerLeader();
           for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
             event.push(*itRank,1,msg);
           contextClientTmp->sendEvent(event);
         }
         else contextClientTmp->sendEvent(event);
     }
   }
   CATCH_DUMP_ATTR

   //! Server side: Receive a message of client annoucing calendar update
   void CContext::recvUpdateCalendar(CEventServer& event)
   TRY
   {
      CBufferIn* buffer=event.subEvents.begin()->buffer;
      string id;
      *buffer>>id;
      get(id)->recvUpdateCalendar(*buffer);
   }
   CATCH

   //! Server side: Receive a message of client annoucing calendar update
   void CContext::recvUpdateCalendar(CBufferIn& buffer)
   TRY
   {
      int step;
      buffer>>step;
      updateCalendar(step);
      if (hasClient && hasServer)
      {        
        sendUpdateCalendar(step);
      }
   }
   CATCH_DUMP_ATTR

   //! Client side: Send a message to create header part of netcdf file
   void CContext::sendCreateFileHeader(void)
   TRY
   {
     // Use correct context client to send message
     // int nbSrvPools = (hasServer) ? clientPrimServer.size() : 1;
     int nbSrvPools = (this->hasServer) ? (this->hasClient ? this->clientPrimServer.size() : 0) : 1;
     for (int i = 0; i < nbSrvPools; ++i)
     {
       CContextClient* contextClientTmp = (hasServer) ? clientPrimServer[i] : client;
       CEventClient event(getType(),EVENT_ID_CREATE_FILE_HEADER);

       if (contextClientTmp->isServerLeader())
       {
         CMessage msg;
         if (hasServer)
           msg<<this->getIdServer(i);
         else
           msg<<this->getIdServer();
         const std::list<int>& ranks = contextClientTmp->getRanksServerLeader();
         for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
           event.push(*itRank,1,msg) ;
         contextClientTmp->sendEvent(event);
       }
       else contextClientTmp->sendEvent(event);
     }
   }
   CATCH_DUMP_ATTR

   //! Server side: Receive a message of client annoucing the creation of header part of netcdf file
   void CContext::recvCreateFileHeader(CEventServer& event)
   TRY
   {
      CBufferIn* buffer=event.subEvents.begin()->buffer;
      string id;
      *buffer>>id;
      get(id)->recvCreateFileHeader(*buffer);
   }
   CATCH

   //! Server side: Receive a message of client annoucing the creation of header part of netcdf file
   void CContext::recvCreateFileHeader(CBufferIn& buffer)
   TRY
   {
      createFileHeader();
   }
   CATCH_DUMP_ATTR

   //! Client side: Send a message to do some post processing on server
   void CContext::sendProcessingGridOfEnabledFields()
   TRY
   {
      // Use correct context client to send message
     int nbSrvPools = (this->hasServer) ? (this->hasClient ? this->clientPrimServer.size() : 0) : 1;
     for (int i = 0; i < nbSrvPools; ++i)
     {
       CContextClient* contextClientTmp = (0 != clientPrimServer.size()) ? clientPrimServer[i] : client;
       CEventClient event(getType(),EVENT_ID_PROCESS_GRID_ENABLED_FIELDS);

       if (contextClientTmp->isServerLeader())
       {
         CMessage msg;
         if (hasServer)
           msg<<this->getIdServer(i);
         else
           msg<<this->getIdServer();
         const std::list<int>& ranks = contextClientTmp->getRanksServerLeader();
         for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
           event.push(*itRank,1,msg);
         contextClientTmp->sendEvent(event);
       }
       else contextClientTmp->sendEvent(event);
     }
   }
   CATCH_DUMP_ATTR

   //! Server side: Receive a message to do some post processing
   void CContext::recvProcessingGridOfEnabledFields(CEventServer& event)
   TRY
   {
      CBufferIn* buffer=event.subEvents.begin()->buffer;
      string id;
      *buffer>>id;      
   }
   CATCH

   //! Client side: Send a message to do some post processing on server
   void CContext::sendPostProcessing()
   TRY
   {
      // Use correct context client to send message
     // int nbSrvPools = (hasServer) ? clientPrimServer.size() : 1;
     int nbSrvPools = (this->hasServer) ? (this->hasClient ? this->clientPrimServer.size() : 0) : 1;
     for (int i = 0; i < nbSrvPools; ++i)
     {
       CContextClient* contextClientTmp = (hasServer) ? clientPrimServer[i] : client;
       CEventClient event(getType(),EVENT_ID_POST_PROCESS);
       if (contextClientTmp->isServerLeader())
       {
         CMessage msg;
         if (hasServer)
           msg<<this->getIdServer(i);
         else
           msg<<this->getIdServer();
         const std::list<int>& ranks = contextClientTmp->getRanksServerLeader();
         for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
         event.push(*itRank,1,msg);
         contextClientTmp->sendEvent(event);
       }
       else contextClientTmp->sendEvent(event);
     }
   }
   CATCH_DUMP_ATTR

   //! Server side: Receive a message to do some post processing
   void CContext::recvPostProcessing(CEventServer& event)
   TRY
   {
      CBufferIn* buffer=event.subEvents.begin()->buffer;
      string id;
      *buffer>>id;
      get(id)->recvPostProcessing(*buffer);
   }
   CATCH

   //! Server side: Receive a message to do some post processing
   void CContext::recvPostProcessing(CBufferIn& buffer)
   TRY
   {
      CCalendarWrapper::get(CCalendarWrapper::GetDefName())->createCalendar();
      postProcessing();
   }
   CATCH_DUMP_ATTR

   const StdString& CContext::getIdServer()
   TRY
   {
      if (hasClient)
      {
        idServer_ = this->getId();
        idServer_ += "_server";
        return idServer_;
      }
      if (hasServer) return (this->getId());
   }
   CATCH_DUMP_ATTR

   const StdString& CContext::getIdServer(const int i)
   TRY
   {
     idServer_ = this->getId();
     idServer_ += "_server_";
     idServer_ += std::to_string(static_cast<unsigned long long>(i));
     return idServer_;
   }
   CATCH_DUMP_ATTR

   /*!
   \brief Do some simple post processings after parsing xml file
      After the xml file (iodef.xml) is parsed, it is necessary to build all relations among
   created object, e.g: inhertance among fields, domain, axis. After that, all fiels as well as their parents (reference fields),
   which will be written out into netcdf files, are processed
   */
   void CContext::postProcessing()
   TRY
   {
     if (isPostProcessed) return;

      // Make sure the calendar was correctly created
      if (!calendar)
        ERROR("CContext::postProcessing()", << "A calendar must be defined for the context \"" << getId() << "!\"")
      else if (calendar->getTimeStep() == NoneDu)
        ERROR("CContext::postProcessing()", << "A timestep must be defined for the context \"" << getId() << "!\"")
      // Calendar first update to set the current date equals to the start date
      calendar->update(0);

      // Find all inheritance in xml structure
      this->solveAllInheritance();

//      ShowTree(info(10));

      // Check if some axis, domains or grids are eligible to for compressed indexed output.
      // Warning: This must be done after solving the inheritance and before the rest of post-processing
      checkAxisDomainsGridsEligibilityForCompressedOutput();      

      // Check if some automatic time series should be generated
      // Warning: This must be done after solving the inheritance and before the rest of post-processing      

      // The timeseries should only be prepared in client
      if (hasClient && !hasServer) prepareTimeseries();

      //Initialisation du vecteur 'enabledFiles' contenant la liste des fichiers à sortir.
      findEnabledFiles();
      findEnabledWriteModeFiles();
      findEnabledReadModeFiles();

      // For now, only read files with client and only one level server
      // if (hasClient && !hasServer) findEnabledReadModeFiles();      

      // Find all enabled fields of each file      
      findAllEnabledFieldsInFiles(this->enabledWriteModeFiles);
      findAllEnabledFieldsInFiles(this->enabledReadModeFiles);

      // For now, only read files with client and only one level server
      // if (hasClient && !hasServer) 
      //   findAllEnabledFieldsInFiles(this->enabledReadModeFiles);      

      if (hasClient && !hasServer)
      {
        initReadFiles();
        // Try to read attributes of fields in file then fill in corresponding grid (or domain, axis)
        this->readAttributesOfEnabledFieldsInReadModeFiles();
      }

      // Only search and rebuild all reference objects of enable fields, don't transform
      this->solveOnlyRefOfEnabledFields(false);

      // Search and rebuild all reference object of enabled fields, and transform
      this->solveAllRefOfEnabledFieldsAndTransform(false);

      // Find all fields with read access from the public API
      if (hasClient && !hasServer) findFieldsWithReadAccess();
      // and solve the all reference for them
      if (hasClient && !hasServer) solveAllRefOfFieldsWithReadAccess();

      isPostProcessed = true;
   }
   CATCH_DUMP_ATTR

   /*!
    * Compute the required buffer size to send the attributes (mostly those grid related).
    * \param maxEventSize [in/out] the size of the bigger event for each connected server
    * \param [in] contextClient
    * \param [in] bufferForWriting True if buffers are used for sending data for writing
      This flag is only true for client and server-1 for communication with server-2
    */
   std::map<int, StdSize> CContext::getAttributesBufferSize(std::map<int, StdSize>& maxEventSize,
                                                           CContextClient* contextClient, bool bufferForWriting /*= "false"*/)
   TRY
   {
	 // As calendar attributes are sent even if there are no active files or fields, maps are initialized according the size of calendar attributes
     std::map<int, StdSize> attributesSize = CCalendarWrapper::get(CCalendarWrapper::GetDefName())->getMinimumBufferSizeForAttributes(contextClient);
     maxEventSize = CCalendarWrapper::get(CCalendarWrapper::GetDefName())->getMinimumBufferSizeForAttributes(contextClient);

     std::vector<CFile*>& fileList = this->enabledFiles;
     size_t numEnabledFiles = fileList.size();
     for (size_t i = 0; i < numEnabledFiles; ++i)
     {
//         CFile* file = this->enabledWriteModeFiles[i];
        CFile* file = fileList[i];
        std::vector<CField*> enabledFields = file->getEnabledFields();
        size_t numEnabledFields = enabledFields.size();
        for (size_t j = 0; j < numEnabledFields; ++j)
        {
          const std::map<int, StdSize> mapSize = enabledFields[j]->getGridAttributesBufferSize(contextClient, bufferForWriting);
          std::map<int, StdSize>::const_iterator it = mapSize.begin(), itE = mapSize.end();
          for (; it != itE; ++it)
          {
		     // If attributesSize[it->first] does not exist, it will be zero-initialized
		     // so we can use it safely without checking for its existence
             if (attributesSize[it->first] < it->second)
			   attributesSize[it->first] = it->second;

		     if (maxEventSize[it->first] < it->second)
			   maxEventSize[it->first] = it->second;
          }
        }
     }
     return attributesSize;
   }
   CATCH_DUMP_ATTR

   /*!
    * Compute the required buffer size to send the fields data.
    * \param maxEventSize [in/out] the size of the bigger event for each connected server
    * \param [in] contextClient
    * \param [in] bufferForWriting True if buffers are used for sending data for writing
      This flag is only true for client and server-1 for communication with server-2
    */
   std::map<int, StdSize> CContext::getDataBufferSize(std::map<int, StdSize>& maxEventSize,
                                                      CContextClient* contextClient, bool bufferForWriting /*= "false"*/)
   TRY
   {
     std::map<int, StdSize> dataSize;

     // Find all reference domain and axis of all active fields
     std::vector<CFile*>& fileList = bufferForWriting ? this->enabledWriteModeFiles : this->enabledReadModeFiles;
     size_t numEnabledFiles = fileList.size();
     for (size_t i = 0; i < numEnabledFiles; ++i)
     {
       CFile* file = fileList[i];
       if (file->getContextClient() == contextClient)
       {
         std::vector<CField*> enabledFields = file->getEnabledFields();
         size_t numEnabledFields = enabledFields.size();
         for (size_t j = 0; j < numEnabledFields; ++j)
         {
           // const std::vector<std::map<int, StdSize> > mapSize = enabledFields[j]->getGridDataBufferSize(contextClient);
           const std::map<int, StdSize> mapSize = enabledFields[j]->getGridDataBufferSize(contextClient,bufferForWriting);
           std::map<int, StdSize>::const_iterator it = mapSize.begin(), itE = mapSize.end();
           for (; it != itE; ++it)
           {
             // If dataSize[it->first] does not exist, it will be zero-initialized
             // so we can use it safely without checking for its existance
        	 if (CXios::isOptPerformance)
               dataSize[it->first] += it->second;
             else if (dataSize[it->first] < it->second)
               dataSize[it->first] = it->second;

        	 if (maxEventSize[it->first] < it->second)
               maxEventSize[it->first] = it->second;
           }
         }
       }
     }
     return dataSize;
   }
   CATCH_DUMP_ATTR

   //! Client side: Send infomation of active files (files are enabled to write out)
   void CContext::sendEnabledFiles(const std::vector<CFile*>& activeFiles)
   TRY
   {
     int size = activeFiles.size();

     // In a context, each type has a root definition, e.g: axis, domain, field.
     // Every object must be a child of one of these root definition. In this case
     // all new file objects created on server must be children of the root "file_definition"
     StdString fileDefRoot("file_definition");
     CFileGroup* cfgrpPtr = CFileGroup::get(fileDefRoot);

     for (int i = 0; i < size; ++i)
     {
       CFile* f = activeFiles[i];
       cfgrpPtr->sendCreateChild(f->getId(),f->getContextClient());
       f->sendAllAttributesToServer(f->getContextClient());
       f->sendAddAllVariables(f->getContextClient());
     }
   }
   CATCH_DUMP_ATTR

   //! Client side: Send information of active fields (ones are written onto files)
   void CContext::sendEnabledFieldsInFiles(const std::vector<CFile*>& activeFiles)
   TRY
   {
     int size = activeFiles.size();
     for (int i = 0; i < size; ++i)
     {
       activeFiles[i]->sendEnabledFields(activeFiles[i]->getContextClient());
     }
   }
   CATCH_DUMP_ATTR

   //! Client side: Check if the defined axis, domains and grids are eligible for compressed indexed output
   void CContext::checkAxisDomainsGridsEligibilityForCompressedOutput()
   TRY
   {
     if (!hasClient) return;

     const vector<CAxis*> allAxis = CAxis::getAll();
     for (vector<CAxis*>::const_iterator it = allAxis.begin(); it != allAxis.end(); it++)
       (*it)->checkEligibilityForCompressedOutput();

     const vector<CDomain*> allDomains = CDomain::getAll();
     for (vector<CDomain*>::const_iterator it = allDomains.begin(); it != allDomains.end(); it++)
       (*it)->checkEligibilityForCompressedOutput();

     const vector<CGrid*> allGrids = CGrid::getAll();
     for (vector<CGrid*>::const_iterator it = allGrids.begin(); it != allGrids.end(); it++)
       (*it)->checkEligibilityForCompressedOutput();
   }
   CATCH_DUMP_ATTR

   //! Client side: Prepare the timeseries by adding the necessary files
   void CContext::prepareTimeseries()
   TRY
   {
     if (!hasClient) return;

     const std::vector<CFile*> allFiles = CFile::getAll();
     for (size_t i = 0; i < allFiles.size(); i++)
     {
       CFile* file = allFiles[i];

       std::vector<CVariable*> fileVars, fieldVars, vars = file->getAllVariables();
       for (size_t k = 0; k < vars.size(); k++)
       {
         CVariable* var = vars[k];

         if (var->ts_target.isEmpty()
              || var->ts_target == CVariable::ts_target_attr::file || var->ts_target == CVariable::ts_target_attr::both)
           fileVars.push_back(var);

         if (!var->ts_target.isEmpty()
              && (var->ts_target == CVariable::ts_target_attr::field || var->ts_target == CVariable::ts_target_attr::both))
           fieldVars.push_back(var);
       }

       if (!file->timeseries.isEmpty() && file->timeseries != CFile::timeseries_attr::none)
       {
         StdString fileNameStr("%file_name%") ;
         StdString tsPrefix = !file->ts_prefix.isEmpty() ? file->ts_prefix : fileNameStr ;
         
         StdString fileName=file->getFileOutputName();
         size_t pos=tsPrefix.find(fileNameStr) ;
         while (pos!=std::string::npos)
         {
           tsPrefix=tsPrefix.replace(pos,fileNameStr.size(),fileName) ;
           pos=tsPrefix.find(fileNameStr) ;
         }
        
         const std::vector<CField*> allFields = file->getAllFields();
         for (size_t j = 0; j < allFields.size(); j++)
         {
           CField* field = allFields[j];

           if (!field->ts_enabled.isEmpty() && field->ts_enabled)
           {
             CFile* tsFile = CFile::create();
             tsFile->duplicateAttributes(file);

             // Add variables originating from file and targeted to timeserie file
             for (size_t k = 0; k < fileVars.size(); k++)
               tsFile->getVirtualVariableGroup()->addChild(fileVars[k]);

            
             tsFile->name = tsPrefix + "_";
             if (!field->name.isEmpty())
               tsFile->name.get() += field->name;
             else if (field->hasDirectFieldReference()) // We cannot use getBaseFieldReference() just yet
               tsFile->name.get() += field->field_ref;
             else
               tsFile->name.get() += field->getId();

             if (!field->ts_split_freq.isEmpty())
               tsFile->split_freq = field->ts_split_freq;

             CField* tsField = tsFile->addField();
             tsField->field_ref = field->getId();

             // Add variables originating from file and targeted to timeserie field
             for (size_t k = 0; k < fieldVars.size(); k++)
               tsField->getVirtualVariableGroup()->addChild(fieldVars[k]);

             vars = field->getAllVariables();
             for (size_t k = 0; k < vars.size(); k++)
             {
               CVariable* var = vars[k];

               // Add variables originating from field and targeted to timeserie field
               if (var->ts_target.isEmpty()
                    || var->ts_target == CVariable::ts_target_attr::field || var->ts_target == CVariable::ts_target_attr::both)
                 tsField->getVirtualVariableGroup()->addChild(var);

               // Add variables originating from field and targeted to timeserie file
               if (!var->ts_target.isEmpty()
                    && (var->ts_target == CVariable::ts_target_attr::file || var->ts_target == CVariable::ts_target_attr::both))
                 tsFile->getVirtualVariableGroup()->addChild(var);
             }

             tsFile->solveFieldRefInheritance(true);

             if (file->timeseries == CFile::timeseries_attr::exclusive)
               field->enabled = false;
           }
         }

         // Finally disable the original file is need be
         if (file->timeseries == CFile::timeseries_attr::only)
          file->enabled = false;
       }
     }
   }
   CATCH_DUMP_ATTR

   //! Client side: Send information of reference grid of active fields
   void CContext::sendRefGrid(const std::vector<CFile*>& activeFiles)
   TRY
   {
     std::set<StdString> gridIds;
     int sizeFile = activeFiles.size();
     CFile* filePtr(NULL);

     // Firstly, find all reference grids of all active fields
     for (int i = 0; i < sizeFile; ++i)
     {
       filePtr = activeFiles[i];
       std::vector<CField*> enabledFields = filePtr->getEnabledFields();
       int sizeField = enabledFields.size();
       for (int numField = 0; numField < sizeField; ++numField)
       {
         if (0 != enabledFields[numField]->getRelGrid())
           gridIds.insert(CGrid::get(enabledFields[numField]->getRelGrid())->getId());
       }
     }

     // Create all reference grids on server side
     StdString gridDefRoot("grid_definition");
     CGridGroup* gridPtr = CGridGroup::get(gridDefRoot);
     std::set<StdString>::const_iterator it, itE = gridIds.end();
     for (it = gridIds.begin(); it != itE; ++it)
     {
       gridPtr->sendCreateChild(*it);
       CGrid::get(*it)->sendGrid() ;
     }
   }
   CATCH_DUMP_ATTR

   //! Client side: Send information of reference domain, axis and scalar of active fields
   void CContext::sendRefDomainsAxisScalars(const std::vector<CFile*>& activeFiles)
   TRY
   {
     std::set<StdString> domainIds, axisIds, scalarIds;

     // Find all reference domain and axis of all active fields
     int numEnabledFiles = activeFiles.size();
     for (int i = 0; i < numEnabledFiles; ++i)
     {
       std::vector<CField*> enabledFields = activeFiles[i]->getEnabledFields();
       int numEnabledFields = enabledFields.size();
       for (int j = 0; j < numEnabledFields; ++j)
       {
         const std::vector<StdString>& prDomAxisScalarId = enabledFields[j]->getRefDomainAxisIds();
         if ("" != prDomAxisScalarId[0]) domainIds.insert(prDomAxisScalarId[0]);
         if ("" != prDomAxisScalarId[1]) axisIds.insert(prDomAxisScalarId[1]);
         if ("" != prDomAxisScalarId[2]) scalarIds.insert(prDomAxisScalarId[2]);
       }
     }

     // Create all reference axis on server side
     std::set<StdString>::iterator itDom, itAxis, itScalar;
     std::set<StdString>::const_iterator itE;

     StdString scalarDefRoot("scalar_definition");
     CScalarGroup* scalarPtr = CScalarGroup::get(scalarDefRoot);
     itE = scalarIds.end();
     for (itScalar = scalarIds.begin(); itScalar != itE; ++itScalar)
     {
       if (!itScalar->empty())
       {
         scalarPtr->sendCreateChild(*itScalar);
         CScalar::get(*itScalar)->sendAllAttributesToServer();
       }
     }

     StdString axiDefRoot("axis_definition");
     CAxisGroup* axisPtr = CAxisGroup::get(axiDefRoot);
     itE = axisIds.end();
     for (itAxis = axisIds.begin(); itAxis != itE; ++itAxis)
     {
       if (!itAxis->empty())
       {
         axisPtr->sendCreateChild(*itAxis);
         CAxis::get(*itAxis)->sendAllAttributesToServer();
       }
     }

     // Create all reference domains on server side
     StdString domDefRoot("domain_definition");
     CDomainGroup* domPtr = CDomainGroup::get(domDefRoot);
     itE = domainIds.end();
     for (itDom = domainIds.begin(); itDom != itE; ++itDom)
     {
       if (!itDom->empty()) {
          domPtr->sendCreateChild(*itDom);
          CDomain::get(*itDom)->sendAllAttributesToServer();
       }
     }
   }
   CATCH_DUMP_ATTR

   //! Update calendar in each time step
   void CContext::updateCalendar(int step)
   TRY
   {
      int prevStep = calendar->getStep();

      if (prevStep < step)
      {
        if (hasClient && !hasServer) // For now we only use server level 1 to read data
        {
          doPreTimestepOperationsForEnabledReadModeFiles();
        }

        info(50) << "updateCalendar : before : " << calendar->getCurrentDate() << endl;
        calendar->update(step);
        info(50) << "updateCalendar : after : " << calendar->getCurrentDate() << endl;
  #ifdef XIOS_MEMTRACK_LIGHT
        info(50) << " Current memory used by XIOS : "<<  MemTrack::getCurrentMemorySize()*1.0/(1024*1024)<<" Mbyte, at timestep "<<step<<" of context "<<this->getId()<<endl ;
  #endif

        if (hasClient && !hasServer) // For now we only use server level 1 to read data
        {
          doPostTimestepOperationsForEnabledReadModeFiles();
          garbageCollector.invalidate(calendar->getCurrentDate());
        }
      }
      else if (prevStep == step)
        info(50) << "updateCalendar: already at step " << step << ", no operation done." << endl;
      else // if (prevStep > step)
        ERROR("void CContext::updateCalendar(int step)",
              << "Illegal calendar update: previous step was " << prevStep << ", new step " << step << "is in the past!")
   }
   CATCH_DUMP_ATTR

   void CContext::initReadFiles(void)
   TRY
   {
      vector<CFile*>::const_iterator it;

      for (it=enabledReadModeFiles.begin(); it != enabledReadModeFiles.end(); it++)
      {
         (*it)->initRead();
      }
   }
   CATCH_DUMP_ATTR

   //! Server side: Create header of netcdf file
   void CContext::createFileHeader(void)
   TRY
   {
      vector<CFile*>::const_iterator it;
      if (!hasClient && hasServer) 
        for (it=enabledFiles.begin(); it != enabledFiles.end(); it++) (*it)->initWrite();
      else if (hasClient && hasServer)
        for (it=enabledReadModeFiles.begin(); it != enabledReadModeFiles.end(); it++)  (*it)->initWrite();
   }
   CATCH_DUMP_ATTR

   //! Get current context
   CContext* CContext::getCurrent(void)
   TRY
   {
     return CObjectFactory::GetObject<CContext>(CObjectFactory::GetCurrentContextId()).get();
   }
   CATCH

   /*!
   \brief Set context with an id be the current context
   \param [in] id identity of context to be set to current
   */
   void CContext::setCurrent(const string& id)
   TRY
   {
     CObjectFactory::SetCurrentContextId(id);
     CGroupFactory::SetCurrentContextId(id);
   }
   CATCH

  /*!
  \brief Create a context with specific id
  \param [in] id identity of new context
  \return pointer to the new context or already-existed one with identity id
  */
  CContext* CContext::create(const StdString& id)
  TRY
  {
    CContext::setCurrent(id);

    bool hasctxt = CContext::has(id);
    CContext* context = CObjectFactory::CreateObject<CContext>(id).get();
    getRoot();
    if (!hasctxt) CGroupFactory::AddChild(root, context->getShared());

#define DECLARE_NODE(Name_, name_) \
    C##Name_##Definition::create(C##Name_##Definition::GetDefName());
#define DECLARE_NODE_PAR(Name_, name_)
#include "node_type.conf"

    return (context);
  }
  CATCH

     //! Server side: Receive a message to do some post processing
  void CContext::recvRegistry(CEventServer& event)
  TRY
  {
    CBufferIn* buffer=event.subEvents.begin()->buffer;
    string id;
    *buffer>>id;
    get(id)->recvRegistry(*buffer);
  }
  CATCH

  void CContext::recvRegistry(CBufferIn& buffer)
  TRY
  {
    if (server->intraCommRank==0)
    {
      CRegistry registry(server->intraComm) ;
      registry.fromBuffer(buffer) ;
      registryOut->mergeRegistry(registry) ;
    }
  }
  CATCH_DUMP_ATTR

  void CContext::sendRegistry(void)
  TRY
  {
    registryOut->hierarchicalGatherRegistry() ;

    // Use correct context client to send message
    int nbSrvPools = (this->hasServer) ? (this->hasClient ? this->clientPrimServer.size() : 0) : 1;
    for (int i = 0; i < nbSrvPools; ++i)
    {
      CContextClient* contextClientTmp = (hasServer) ? clientPrimServer[i] : client;
      CEventClient event(CContext::GetType(), CContext::EVENT_ID_SEND_REGISTRY);
        if (contextClientTmp->isServerLeader())
        {
           CMessage msg ;
           if (hasServer)
             msg<<this->getIdServer(i);
           else
             msg<<this->getIdServer();
           if (contextClientTmp->clientRank==0) msg<<*registryOut ;
           const std::list<int>& ranks = contextClientTmp->getRanksServerLeader();
           for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
             event.push(*itRank,1,msg);
           contextClientTmp->sendEvent(event);
         }
         else contextClientTmp->sendEvent(event);
    }
  }
  CATCH_DUMP_ATTR

  /*!
  * \fn bool CContext::isFinalized(void)
  * Context is finalized if it received context post finalize event.
  */
  bool CContext::isFinalized(void)
  TRY
  {
    return finalized;
  }
  CATCH_DUMP_ATTR
  ///--------------------------------------------------------------
  StdString CContext::dumpClassAttributes(void)
  {
    StdString str;
    str.append("enabled files=\"");
    int size = this->enabledFiles.size();
    for (int i = 0; i < size; ++i)
    {
      str.append(enabledFiles[i]->getId());
      str.append(" ");
    }
    str.append("\"");
    return str;
  }

} // namespace xios
