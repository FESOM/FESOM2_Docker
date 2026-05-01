
#include "xios_spl.hpp"
#include "cxios.hpp"
#include "client.hpp"
#include "server.hpp"
#include "xml_parser.hpp"
#include <boost/functional/hash.hpp>
#include "mpi.hpp"
#include "memory.hpp"
#include <new>
#include "memtrack.hpp"
#include "registry.hpp"

#include "graphviz.hpp"

namespace xios
{
  string CXios::rootFile="./iodef.xml" ;
  string CXios::xiosCodeId="xios.x" ;
  string CXios::clientFile="./xios_client";
  string CXios::serverFile="./xios_server";
  string CXios::serverPrmFile="./xios_server1";
  string CXios::serverSndFile="./xios_server2";

  bool CXios::xiosStack = true;
  bool CXios::systemStack = false;

  bool CXios::isClient ;
  bool CXios::isServer ;
  MPI_Comm CXios::globalComm ;
  bool CXios::usingOasis ;
  bool CXios::usingServer = false;
  bool CXios::usingServer2 = false;
  int CXios::ratioServer2 = 50;
  int CXios::nbPoolsServer2 = 1;
  double CXios::bufferSizeFactor = 1.0;
  const double CXios::defaultBufferSizeFactor = 1.0;
  StdSize CXios::minBufferSize = 1024 * sizeof(double);
  StdSize CXios::maxBufferSize = std::numeric_limits<int>::max() ;
  bool CXios::printLogs2Files;
  bool CXios::isOptPerformance = true;
  CRegistry* CXios::globalRegistry = 0;
  double CXios::recvFieldTimeout = 300.0;
  bool CXios::checkEventSync=false ;
 
  //! Parse configuration file and create some objects from it
  void CXios::initialize()
  {
    set_new_handler(noMemory);
    parseFile(rootFile);
    parseXiosConfig();
  }

  /*!
  \brief Parse xios part of configuration file (.iodef.xml)
   Both client and server need information returned from this function
  */
  void CXios::parseXiosConfig()
  {
    usingOasis=getin<bool>("using_oasis",false) ;
    usingServer=getin<bool>("using_server",false) ;
    usingServer2=getin<bool>("using_server2",false) ;
    ratioServer2=getin<int>("ratio_server2",50);
    nbPoolsServer2=getin<int>("number_pools_server2",0);
    info.setLevel(getin<int>("info_level",0)) ;
    report.setLevel(getin<int>("info_level",50));
    printLogs2Files=getin<bool>("print_file",false);

    xiosStack=getin<bool>("xios_stack",true) ;
    systemStack=getin<bool>("system_stack",false) ;
    if (xiosStack && systemStack)
    {
      xiosStack = false;
    }

    StdString bufMemory("memory");
    StdString bufPerformance("performance");
    StdString bufOpt = getin<StdString>("optimal_buffer_size", bufPerformance);
    std::transform(bufOpt.begin(), bufOpt.end(), bufOpt.begin(), ::tolower);
    if (0 == bufOpt.compare(bufMemory)) isOptPerformance = false;
    else if (0 != bufOpt.compare(bufPerformance))
    {
      ERROR("CXios::parseXiosConfig()", << "optimal_buffer_size must be memory or performance "<< endl );
    }

    bufferSizeFactor = getin<double>("buffer_size_factor", defaultBufferSizeFactor);
    minBufferSize = getin<int>("min_buffer_size", 1024 * sizeof(double));
    maxBufferSize = getin<int>("max_buffer_size", std::numeric_limits<int>::max());
    recvFieldTimeout = getin<double>("recv_field_timeout", recvFieldTimeout);
    if (recvFieldTimeout < 0.0)
      ERROR("CXios::parseXiosConfig()", "recv_field_timeout cannot be negative.");

    checkEventSync = getin<bool>("check_event_sync", checkEventSync);

    globalComm=MPI_COMM_WORLD ;
  }

  /*!
  Initialize client
  \param [in] codeId identity of context
  \param [in] localComm local communicator
  \param [in/out] returnComm communicator corresponding to group of client with same codeId
  */
  void CXios::initClientSide(const string& codeId, MPI_Comm& localComm, MPI_Comm& returnComm)
  TRY
  {
    initialize() ;

    isClient = true;

    CClient::initialize(codeId,localComm,returnComm) ;
    if (CClient::getRank()==0) globalRegistry = new CRegistry(returnComm) ;

    // If there are no server processes then we are in attached mode
    // and the clients are also servers
    isServer = !usingServer;

    if (printLogs2Files)
    {
      CClient::openInfoStream(clientFile);
      CClient::openErrorStream(clientFile);
    }
    else
    {
      CClient::openInfoStream();
      CClient::openErrorStream();
    }
  }
  CATCH

  void CXios::clientFinalize(void)
  {
     CClient::finalize() ;
     if (CClient::getRank()==0)
     {
       info(80)<<"Write data base Registry"<<endl<<globalRegistry->toString()<<endl ;
       globalRegistry->toFile("xios_registry.bin") ;
       delete globalRegistry ;
       CGraphviz::buildWorkflowGraphVisjs_with_info();
     }

#ifdef XIOS_MEMTRACK

#ifdef XIOS_MEMTRACK_LIGHT
       report(10) << " Memory report : current memory used by XIOS : "<<  MemTrack::getCurrentMemorySize()*1.0/(1024*1024)<<" Mbyte" << endl ;
       report(10) << " Memory report : maximum memory used by XIOS : "<<  MemTrack::getMaxMemorySize()*1.0/(1024*1024)<<" Mbyte" << endl ;
#endif

#ifdef XIOS_MEMTRACK_FULL
     MemTrack::TrackListMemoryUsage() ;
     MemTrack::TrackDumpBlocks();
#endif

     CClient::closeInfoStream();

#endif
  }

  //! Init server by parsing only xios part of config file
  void CXios::initServer()
  {
    set_new_handler(noMemory);
    std::set<StdString> parseList;
    parseList.insert("xios");
    xml::CXMLParser::ParseFile(rootFile, parseList);
    parseXiosConfig();
  }

  //! Initialize server then put it into listening state
  void CXios::initServerSide(void)
  {
    initServer();
    isClient = false;
    isServer = true;

    // Initialize all aspects MPI
    CServer::initialize();
    if (CServer::getRank()==0 && CServer::serverLevel != 1) globalRegistry = new CRegistry(CServer::intraComm) ;
    
    if (printLogs2Files)
    {
      if (CServer::serverLevel == 0)
      {
        CServer::openInfoStream(serverFile);
        CServer::openErrorStream(serverFile);
      }
      else if (CServer::serverLevel == 1)
      {
        CServer::openInfoStream(serverPrmFile);
        CServer::openErrorStream(serverPrmFile);
      }
      else
      {
        CServer::openInfoStream(serverSndFile);
        CServer::openErrorStream(serverSndFile);
      }
    }
    else
    {
      CServer::openInfoStream();
      CServer::openErrorStream();
    }

    // Enter the loop to listen message from Client
    CServer::eventLoop();

    // Finalize
    if (CServer::serverLevel == 0)
    {
      if (CServer::getRank()==0)
      {
        info(80)<<"Write data base Registry"<<endl<<globalRegistry->toString()<<endl ;
        globalRegistry->toFile("xios_registry.bin") ;
        delete globalRegistry ;
      }
    }
    else
    {
      // If using two server levels:
      // (1) merge registries on each pool
      // (2) send merged registries to the first pool
      // (3) merge received registries on the first pool
      if (CServer::serverLevel == 2)
      {
        vector<int>& secondaryServerGlobalRanks = CServer::getSecondaryServerGlobalRanks();
        int firstPoolGlobalRank = secondaryServerGlobalRanks[0];
        int rankGlobal;
        MPI_Comm_rank(globalComm, &rankGlobal);

        // Merge registries defined on each pools
        CRegistry globalRegistrySndServers (CServer::intraComm);

        // All pools (except the first): send globalRegistry to the first pool
        for (int i=1; i<secondaryServerGlobalRanks.size(); i++)
        {
          if (rankGlobal == secondaryServerGlobalRanks[i])
          {
            globalRegistrySndServers.mergeRegistry(*globalRegistry) ;
            int registrySize = globalRegistrySndServers.size();
            MPI_Send(&registrySize,1,MPI_LONG,firstPoolGlobalRank,15,CXios::globalComm) ;
            CBufferOut buffer(registrySize) ;
            globalRegistrySndServers.toBuffer(buffer) ;
            MPI_Send(buffer.start(),registrySize,MPI_CHAR,firstPoolGlobalRank,15,CXios::globalComm) ;
          }
        }

        // First pool: receive globalRegistry of all secondary server pools, merge and write the resultant registry
        if (rankGlobal == firstPoolGlobalRank)
        {
          MPI_Status status;
          char* recvBuff;

          globalRegistrySndServers.mergeRegistry(*globalRegistry) ;

          for (int i=1; i< secondaryServerGlobalRanks.size(); i++)
          {
            int rank = secondaryServerGlobalRanks[i];
            int registrySize = 0;
            MPI_Recv(&registrySize, 1, MPI_LONG, rank, 15, CXios::globalComm, &status);
            recvBuff = new char[registrySize];
            MPI_Recv(recvBuff, registrySize, MPI_CHAR, rank, 15, CXios::globalComm, &status);
            CBufferIn buffer(recvBuff, registrySize) ;
            CRegistry recvRegistry;
            recvRegistry.fromBuffer(buffer) ;
            globalRegistrySndServers.mergeRegistry(recvRegistry) ;
            delete[] recvBuff;
          }

          info(80)<<"Write data base Registry"<<endl<<globalRegistrySndServers.toString()<<endl ;
          globalRegistrySndServers.toFile("xios_registry.bin") ;

        }
      }
      delete globalRegistry;
    }
    CServer::finalize();

#ifdef XIOS_MEMTRACK

#ifdef XIOS_MEMTRACK_LIGHT
       report(10) << " Memory report : current memory used by XIOS : "<<  MemTrack::getCurrentMemorySize()*1.0/(1024*1024)<<" Mbyte" << endl ;
       report(10) << " Memory report : maximum memory used by XIOS : "<<  MemTrack::getMaxMemorySize()*1.0/(1024*1024)<<" Mbyte" << endl ;
#endif

#ifdef XIOS_MEMTRACK_FULL
     MemTrack::TrackListMemoryUsage() ;
     MemTrack::TrackDumpBlocks();
#endif
#endif
    CServer::closeInfoStream();
  }

  //! Parse configuration file
  void CXios::parseFile(const string& filename)
  {
    xml::CXMLParser::ParseFile(filename);
  }

  //! Set using server
  void CXios::setUsingServer()
  {
    usingServer = true;
  }

  //! Unset using server
  void CXios::setNotUsingServer()
  {
    usingServer = false;
  }
}
