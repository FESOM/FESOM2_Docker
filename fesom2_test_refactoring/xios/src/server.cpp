#include "globalScopeData.hpp"
#include "xios_spl.hpp"
#include "cxios.hpp"
#include "server.hpp"
#include "client.hpp"
#include "type.hpp"
#include "context.hpp"
#include "object_template.hpp"
#include "oasis_cinterface.hpp"
#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>
#include "mpi.hpp"
#include "tracer.hpp"
#include "timer.hpp"
#include "event_scheduler.hpp"
#include "string_tools.hpp"
#include "field.hpp"

namespace xios
{
    MPI_Comm CServer::intraComm ;
    std::list<MPI_Comm> CServer::interCommLeft ;
    std::list<MPI_Comm> CServer::interCommRight ;
    std::list<MPI_Comm> CServer::contextInterComms;
    std::list<MPI_Comm> CServer::contextIntraComms;
    int CServer::serverLevel = 0 ;
    int CServer::nbContexts = 0;
    bool CServer::isRoot = false ;
    int CServer::rank_ = INVALID_RANK;
    StdOFStream CServer::m_infoStream;
    StdOFStream CServer::m_errorStream;
    map<string,CContext*> CServer::contextList ;
    vector<int> CServer::sndServerGlobalRanks;
    bool CServer::finished=false ;
    bool CServer::is_MPI_Initialized ;
    CEventScheduler* CServer::eventScheduler = 0;

//---------------------------------------------------------------
/*!
 * \fn void CServer::initialize(void)
 * Creates intraComm for each possible type of servers (classical, primary or secondary).
 * Creates interComm and stores them into the following lists:
 *   classical server -- interCommLeft
 *   primary server -- interCommLeft and interCommRight
 *   secondary server -- interCommLeft for each pool.
 *   IMPORTANT: CXios::usingServer2 should NOT be used beyond this function. Use CServer::serverLevel instead.
 */
    void CServer::initialize(void)
    {
      int initialized ;
      MPI_Initialized(&initialized) ;
      if (initialized) is_MPI_Initialized=true ;
      else is_MPI_Initialized=false ;
      int rank ;

      // Not using OASIS
      if (!CXios::usingOasis)
      {

        if (!is_MPI_Initialized)
        {
          MPI_Init(NULL, NULL);
        }
        CTimer::get("XIOS").resume() ;

        boost::hash<string> hashString ;
        unsigned long hashServer = hashString(CXios::xiosCodeId);

        unsigned long* hashAll ;
        unsigned long* srvLevelAll ;

        int size ;
        int myColor ;
        int i,c ;
        MPI_Comm newComm;

        MPI_Comm_size(CXios::globalComm, &size) ;
        MPI_Comm_rank(CXios::globalComm, &rank_);

        hashAll=new unsigned long[size] ;
        MPI_Allgather(&hashServer, 1, MPI_LONG, hashAll, 1, MPI_LONG, CXios::globalComm) ;

        map<unsigned long, int> colors ;
        map<unsigned long, int> leaders ;
        map<unsigned long, int>::iterator it ;

        // (1) Establish client leaders, distribute processes between two server levels
        std::vector<int> srvRanks;
        for(i=0,c=0;i<size;i++)
        {
          if (colors.find(hashAll[i])==colors.end())
          {
            colors[hashAll[i]]=c ;
            leaders[hashAll[i]]=i ;
            c++ ;
          }
          if (CXios::usingServer2)
            if (hashAll[i] == hashServer)
              srvRanks.push_back(i);
        }

        if (CXios::usingServer2)
        {
          int reqNbProc = srvRanks.size()*CXios::ratioServer2/100.;
          if (reqNbProc<1 || reqNbProc==srvRanks.size())
          {
            error(0)<<"WARNING: void CServer::initialize(void)"<<endl
                << "It is impossible to dedicate the requested number of processes = "<<reqNbProc
                <<" to secondary server. XIOS will run in the classical server mode."<<endl;
          }
          else
          {
            if (CXios::nbPoolsServer2 == 0) CXios::nbPoolsServer2 = reqNbProc;
            int firstSndSrvRank = srvRanks.size()*(100.-CXios::ratioServer2)/100. ;
            int poolLeader = firstSndSrvRank;
//*********** (1) Comment out the line below to set one process per pool
            sndServerGlobalRanks.push_back(srvRanks[poolLeader]);
            int nbPools = CXios::nbPoolsServer2;
            if ( nbPools > reqNbProc || nbPools < 1)
            {
              error(0)<<"WARNING: void CServer::initialize(void)"<<endl
                  << "It is impossible to allocate the requested number of pools = "<<nbPools
                  <<" on the secondary server. It will be set so that there is one process per pool."<<endl;
              nbPools = reqNbProc;
            }
            int remainder = ((int) (srvRanks.size()*CXios::ratioServer2/100.)) % nbPools;
            int procsPerPool = ((int) (srvRanks.size()*CXios::ratioServer2/100.)) / nbPools;
            for (i=0; i<srvRanks.size(); i++)
            {
              if (i >= firstSndSrvRank)
              {
                if (rank_ == srvRanks[i])
                {
                  serverLevel=2;
                }
                poolLeader += procsPerPool;
                if (remainder != 0)
                {
                  ++poolLeader;
                  --remainder;
                }
//*********** (2) Comment out the two lines below to set one process per pool
                if (poolLeader < srvRanks.size())
                  sndServerGlobalRanks.push_back(srvRanks[poolLeader]);
//*********** (3) Uncomment the line below to set one process per pool
//                sndServerGlobalRanks.push_back(srvRanks[i]);
              }
              else
              {
                if (rank_ == srvRanks[i]) serverLevel=1;
              }
            }
            if (serverLevel==2)
            {
              info(50)<<"The number of secondary server pools is "<< sndServerGlobalRanks.size() <<endl ;
              for (i=0; i<sndServerGlobalRanks.size(); i++)
              {
                if (rank_>= sndServerGlobalRanks[i])
                {
                  if ( i == sndServerGlobalRanks.size()-1)
                  {
                    myColor = colors.size() + sndServerGlobalRanks[i];
                  }
                  else if (rank_< sndServerGlobalRanks[i+1])
                  {
                    myColor = colors.size() + sndServerGlobalRanks[i];
                    break;
                  }
                }
              }
            }
          }
        }

        // (2) Create intraComm
        if (serverLevel != 2) myColor=colors[hashServer];
        MPI_Comm_split(CXios::globalComm, myColor, rank_, &intraComm) ;

        // (3) Create interComm
        if (serverLevel == 0)
        {
          int clientLeader;
          for(it=leaders.begin();it!=leaders.end();it++)
          {
            if (it->first!=hashServer)
            {
              clientLeader=it->second ;
              int intraCommSize, intraCommRank ;
              MPI_Comm_size(intraComm,&intraCommSize) ;
              MPI_Comm_rank(intraComm,&intraCommRank) ;
              info(50)<<"intercommCreate::server (classical mode) "<<rank_<<" intraCommSize : "<<intraCommSize
                       <<" intraCommRank :"<<intraCommRank<<"  clientLeader "<< clientLeader<<endl ;

              MPI_Intercomm_create(intraComm, 0, CXios::globalComm, clientLeader, 0, &newComm) ;
              interCommLeft.push_back(newComm) ;
            }
          }
        }
        else if (serverLevel == 1)
        {
          int clientLeader, srvSndLeader;
          int srvPrmLeader ;

          for (it=leaders.begin();it!=leaders.end();it++)
          {
            if (it->first != hashServer)
            {
              clientLeader=it->second ;
              int intraCommSize, intraCommRank ;
              MPI_Comm_size(intraComm, &intraCommSize) ;
              MPI_Comm_rank(intraComm, &intraCommRank) ;
              info(50)<<"intercommCreate::server (server level 1) "<<rank_<<" intraCommSize : "<<intraCommSize
                       <<" intraCommRank :"<<intraCommRank<<"  clientLeader "<< clientLeader<<endl ;
              MPI_Intercomm_create(intraComm, 0, CXios::globalComm, clientLeader, 0, &newComm) ;
              interCommLeft.push_back(newComm) ;
            }
          }

          for (int i = 0; i < sndServerGlobalRanks.size(); ++i)
          {
            int intraCommSize, intraCommRank ;
            MPI_Comm_size(intraComm, &intraCommSize) ;
            MPI_Comm_rank(intraComm, &intraCommRank) ;
            info(50)<<"intercommCreate::client (server level 1) "<<rank_<<" intraCommSize : "<<intraCommSize
                <<" intraCommRank :"<<intraCommRank<<"  clientLeader "<< sndServerGlobalRanks[i]<<endl ;
            MPI_Intercomm_create(intraComm, 0, CXios::globalComm, sndServerGlobalRanks[i], 1, &newComm) ;
            interCommRight.push_back(newComm) ;
          }
        }
        else
        {
          int clientLeader;
          clientLeader = leaders[hashString(CXios::xiosCodeId)];
          int intraCommSize, intraCommRank ;
          MPI_Comm_size(intraComm, &intraCommSize) ;
          MPI_Comm_rank(intraComm, &intraCommRank) ;
          info(50)<<"intercommCreate::server (server level 2) "<<rank_<<" intraCommSize : "<<intraCommSize
                   <<" intraCommRank :"<<intraCommRank<<"  clientLeader "<< clientLeader<<endl ;

          MPI_Intercomm_create(intraComm, 0, CXios::globalComm, clientLeader, 1, &newComm) ;
          interCommLeft.push_back(newComm) ;
        }

        delete [] hashAll ;

      }
      // using OASIS
      else
      {
        int size;
        int myColor;
        int* srvGlobalRanks;
        if (!is_MPI_Initialized) oasis_init(CXios::xiosCodeId);

        CTimer::get("XIOS").resume() ;
        MPI_Comm localComm;
        oasis_get_localcomm(localComm);
        MPI_Comm_rank(localComm,&rank_) ;

//      (1) Create server intraComm
        if (!CXios::usingServer2)
        {
          MPI_Comm_dup(localComm, &intraComm);
        }
        else
        {
          int globalRank;
          MPI_Comm_size(localComm,&size) ;
          MPI_Comm_rank(CXios::globalComm,&globalRank) ;
          srvGlobalRanks = new int[size] ;
          MPI_Allgather(&globalRank, 1, MPI_INT, srvGlobalRanks, 1, MPI_INT, localComm) ;

          int reqNbProc = size*CXios::ratioServer2/100.;
          if (reqNbProc < 1 || reqNbProc == size)
          {
            error(0)<<"WARNING: void CServer::initialize(void)"<<endl
                << "It is impossible to dedicate the requested number of processes = "<<reqNbProc
                <<" to secondary server. XIOS will run in the classical server mode."<<endl;
            MPI_Comm_dup(localComm, &intraComm);
          }
          else
          {
            if (CXios::nbPoolsServer2 == 0) CXios::nbPoolsServer2 = reqNbProc;
            int firstSndSrvRank = size*(100.-CXios::ratioServer2)/100. ;
            int poolLeader = firstSndSrvRank;
//*********** (1) Comment out the line below to set one process per pool
            sndServerGlobalRanks.push_back(srvGlobalRanks[poolLeader]);
            int nbPools = CXios::nbPoolsServer2;
            if ( nbPools > reqNbProc || nbPools < 1)
            {
              error(0)<<"WARNING: void CServer::initialize(void)"<<endl
                  << "It is impossible to allocate the requested number of pools = "<<nbPools
                  <<" on the secondary server. It will be set so that there is one process per pool."<<endl;
              nbPools = reqNbProc;
            }
            int remainder = ((int) (size*CXios::ratioServer2/100.)) % nbPools;
            int procsPerPool = ((int) (size*CXios::ratioServer2/100.)) / nbPools;
            for (int i=0; i<size; i++)
            {
              if (i >= firstSndSrvRank)
              {
                if (globalRank == srvGlobalRanks[i])
                {
                  serverLevel=2;
                }
                poolLeader += procsPerPool;
                if (remainder != 0)
                {
                  ++poolLeader;
                  --remainder;
                }
//*********** (2) Comment out the two lines below to set one process per pool
                if (poolLeader < size)
                  sndServerGlobalRanks.push_back(srvGlobalRanks[poolLeader]);
//*********** (3) Uncomment the line below to set one process per pool
//                sndServerGlobalRanks.push_back(srvGlobalRanks[i]);
              }
              else
              {
                if (globalRank == srvGlobalRanks[i]) serverLevel=1;
              }
            }
            if (serverLevel==2)
            {
              info(50)<<"The number of secondary server pools is "<< sndServerGlobalRanks.size() <<endl ;
              for (int i=0; i<sndServerGlobalRanks.size(); i++)
              {
                if (globalRank>= sndServerGlobalRanks[i])
                {
                  if (i == sndServerGlobalRanks.size()-1)
                  {
                    myColor = sndServerGlobalRanks[i];
                  }
                  else if (globalRank< sndServerGlobalRanks[i+1])
                  {
                    myColor = sndServerGlobalRanks[i];
                    break;
                  }
                }
              }
            }
            if (serverLevel != 2) myColor=0;
            MPI_Comm_split(localComm, myColor, rank_, &intraComm) ;
          }
        }

        string codesId=CXios::getin<string>("oasis_codes_id") ;
        vector<string> oasisCodeId=splitRegex(codesId,"\\s*,\\s*") ;
 
        vector<string>::iterator it ;

        MPI_Comm newComm ;
        int globalRank ;
        MPI_Comm_rank(CXios::globalComm,&globalRank);

//      (2) Create interComms with models
        for(it=oasisCodeId.begin();it!=oasisCodeId.end();it++)
        {
          oasis_get_intercomm(newComm,*it) ;
          if ( serverLevel == 0 || serverLevel == 1)
          {
            interCommLeft.push_back(newComm) ;
            if (rank_==0) MPI_Send(&globalRank,1,MPI_INT,0,0,newComm) ;
          }
        }

//      (3) Create interComms between primary and secondary servers
        int intraCommSize, intraCommRank ;
        MPI_Comm_size(intraComm,&intraCommSize) ;
        MPI_Comm_rank(intraComm, &intraCommRank) ;

        if (serverLevel == 1)
        {
          for (int i = 0; i < sndServerGlobalRanks.size(); ++i)
          {
            int srvSndLeader = sndServerGlobalRanks[i];
            info(50)<<"intercommCreate::client (server level 1) "<<globalRank<<" intraCommSize : "<<intraCommSize
                <<" intraCommRank :"<<intraCommRank<<"  clientLeader "<< srvSndLeader<<endl ;
            MPI_Intercomm_create(intraComm, 0, CXios::globalComm, srvSndLeader, 0, &newComm) ;
            interCommRight.push_back(newComm) ;
          }
        }
        else if (serverLevel == 2)
        {
          info(50)<<"intercommCreate::server (server level 2)"<<globalRank<<" intraCommSize : "<<intraCommSize
                   <<" intraCommRank :"<<intraCommRank<<"  clientLeader "<< srvGlobalRanks[0] <<endl ;
          MPI_Intercomm_create(intraComm, 0, CXios::globalComm, srvGlobalRanks[0], 0, &newComm) ;
          interCommLeft.push_back(newComm) ;
        }
        if (CXios::usingServer2) delete [] srvGlobalRanks ;

        bool oasisEnddef=CXios::getin<bool>("call_oasis_enddef",true) ;
        if (!oasisEnddef) oasis_enddef() ;
      }


      MPI_Comm_rank(intraComm, &rank) ;
      if (rank==0) isRoot=true;
      else isRoot=false;
      
      eventScheduler = new CEventScheduler(intraComm) ;
    }

    void CServer::finalize(void)
    {
      CTimer::get("XIOS").suspend() ;
     
      delete eventScheduler ;

      for (std::list<MPI_Comm>::iterator it = contextInterComms.begin(); it != contextInterComms.end(); it++)
        /* MPI_Comm_free(&(*it)) */; // WARNING remove freeing communicator !! --> deadlock raised, to be checked

      for (std::list<MPI_Comm>::iterator it = contextIntraComms.begin(); it != contextIntraComms.end(); it++)
        MPI_Comm_free(&(*it));

//      for (std::list<MPI_Comm>::iterator it = interComm.begin(); it != interComm.end(); it++)
//        MPI_Comm_free(&(*it));

//        for (std::list<MPI_Comm>::iterator it = interCommLeft.begin(); it != interCommLeft.end(); it++)
//          MPI_Comm_free(&(*it));

        for (std::list<MPI_Comm>::iterator it = interCommRight.begin(); it != interCommRight.end(); it++)
          /* MPI_Comm_free(&(*it)) */ ; // WARNING remove freeing communicator !! --> deadlock raised, to be checked

      MPI_Comm_free(&intraComm);

      if (!is_MPI_Initialized)
      {
        if (CXios::usingOasis) oasis_finalize();
        else MPI_Finalize() ;
      }
      report(0)<<"Performance report : Time spent for XIOS : "<<CTimer::get("XIOS server").getCumulatedTime()<<endl  ;
      report(0)<<"Performance report : Time spent in processing events : "<<CTimer::get("Process events").getCumulatedTime()<<endl  ;
      report(0)<<"Performance report : Ratio : "<<CTimer::get("Process events").getCumulatedTime()/CTimer::get("XIOS server").getCumulatedTime()*100.<<"%"<<endl  ;
      report(0)<<"Performance report : Field recv bytes : "<<CField::totalRecvBytes<<endl  ;
      report(0)<<"Performance report : Field send bytes : "<<CField::totalSendBytes<<endl  ;
      report(100)<<CTimer::getAllCumulatedTime()<<endl ;
    }

     void CServer::eventLoop(void)
     {
       bool stop=false ;

       CTimer::get("XIOS server").resume() ;
       while(!stop)
       {
         if (isRoot)
         {
           CTimer::get("root listenContext").resume();
           listenContext();
           CTimer::get("root listenContext").suspend();

           listenRootContext();

           CTimer::get("root listenOasisEnddef").resume();
           listenOasisEnddef() ;
           CTimer::get("root listenOasisEnddef").suspend();

           listenRootOasisEnddef() ;

           if (!finished) {
             CTimer::get("root listenFinalize").resume();
             listenFinalize() ;
             CTimer::get("root listenFinalize").suspend();
           }
         }
         else
         {
           listenRootContext();
           listenRootOasisEnddef() ;
           if (!finished) listenRootFinalize() ;
         }

         contextEventLoop() ;
         if (finished && contextList.empty()) stop=true ;
         eventScheduler->checkEvent() ;
       }
       CTimer::get("XIOS server").suspend() ;
     }

     void CServer::listenFinalize(void)
     {
        list<MPI_Comm>::iterator it, itr;
        int msg ;
        int flag ;

        for(it=interCommLeft.begin();it!=interCommLeft.end();it++)
        {
           MPI_Status status ;
           traceOff() ;
           MPI_Iprobe(0,0,*it,&flag,&status) ;
           traceOn() ;
           if (flag==true)
           {
              MPI_Recv(&msg,1,MPI_INT,0,0,*it,&status) ;
              info(20)<<" CServer : Receive client finalize"<<endl ;
              // Sending server finalize message to secondary servers (if any)
              for(itr=interCommRight.begin();itr!=interCommRight.end();itr++)
              {
                MPI_Send(&msg,1,MPI_INT,0,0,*itr) ;
              }
              /* MPI_Comm_free(&(*it)); */ // WARNING remove freeing communicator !! --> deadlock raised, to be checked
              interCommLeft.erase(it) ;
              break ;
            }
         }

         if (interCommLeft.empty())
         {
           int i,size ;
           MPI_Comm_size(intraComm,&size) ;
           MPI_Request* requests= new MPI_Request[size-1] ;
           MPI_Status* status= new MPI_Status[size-1] ;

           for(int i=1;i<size;i++) MPI_Isend(&msg,1,MPI_INT,i,4,intraComm,&requests[i-1]) ;
           MPI_Waitall(size-1,requests,status) ;

           finished=true ;
           delete [] requests ;
           delete [] status ;
         }
     }


     void CServer::listenRootFinalize()
     {
        int flag ;
        MPI_Status status ;
        int msg ;

        traceOff() ;
        MPI_Iprobe(0,4,intraComm, &flag, &status) ;
        traceOn() ;
        if (flag==true)
        {
           MPI_Recv(&msg,1,MPI_INT,0,4,intraComm,&status) ;
           finished=true ;
        }
      }


   /*!
    * Root process is listening for an order sent by client to call "oasis_enddef".
    * The root client of a compound send the order (tag 5). It is probed and received.
    * When the order has been received from each coumpound, the server root process ping the order to the root processes of the secondary levels of servers (if any).
    * After, it also inform (asynchronous call) other processes of the communicator that the oasis_enddef call must be done
    */
    
     void CServer::listenOasisEnddef(void)
     {
        int flag ;
        MPI_Status status ;
        list<MPI_Comm>::iterator it;
        int msg ;
        static int nbCompound=0 ;
        int size ;
        static bool sent=false ;
        static MPI_Request* allRequests ;
        static MPI_Status* allStatus ;


        if (sent)
        {
          MPI_Comm_size(intraComm,&size) ;
          MPI_Testall(size,allRequests, &flag, allStatus) ;
          if (flag==true)
          {
            delete [] allRequests ;
            delete [] allStatus ;
            sent=false ;
          }
        }
        

        for(it=interCommLeft.begin();it!=interCommLeft.end();it++)
        {
           MPI_Status status ;
           traceOff() ;
           MPI_Iprobe(0,5,*it,&flag,&status) ;  // tags oasis_endded = 5
           traceOn() ;
           if (flag==true)
           {
              MPI_Recv(&msg,1,MPI_INT,0,5,*it,&status) ; // tags oasis_endded = 5
              nbCompound++ ;
              if (nbCompound==interCommLeft.size())
              {
                for (std::list<MPI_Comm>::iterator it = interCommRight.begin(); it != interCommRight.end(); it++)
                {
                   MPI_Send(&msg,1,MPI_INT,0,5,*it) ; // tags oasis_endded = 5
                }
                MPI_Comm_size(intraComm,&size) ;
                allRequests= new MPI_Request[size] ;
                allStatus= new MPI_Status[size] ;
                for(int i=0;i<size;i++) MPI_Isend(&msg,1,MPI_INT,i,5,intraComm,&allRequests[i]) ; // tags oasis_endded = 5
                sent=true ;
              }
           }
        }
     }
     
   /*!
    * Processes probes message from root process if oasis_enddef call must be done.
    * When the order is received it is scheduled to be treated in a synchronized way by all server processes of the communicator
    */
     void CServer::listenRootOasisEnddef(void)
     {
       int flag ;
       MPI_Status status ;
       const int root=0 ;
       int msg ;
       static bool eventSent=false ;

       if (eventSent)
       {
         boost::hash<string> hashString;
         size_t hashId = hashString("oasis_enddef");
         if (eventScheduler->queryEvent(0,hashId))
         {
           oasis_enddef() ;
           eventSent=false ;
         }
       }
         
       traceOff() ;
       MPI_Iprobe(root,5,intraComm, &flag, &status) ;
       traceOn() ;
       if (flag==true)
       {
         MPI_Recv(&msg,1,MPI_INT,root,5,intraComm,&status) ; // tags oasis_endded = 5
         boost::hash<string> hashString;
         size_t hashId = hashString("oasis_enddef");
         eventScheduler->registerEvent(0,hashId);
         eventSent=true ;
       }
     }



     

     void CServer::listenContext(void)
     {

       MPI_Status status ;
       int flag ;
       static char* buffer ;
       static MPI_Request request ;
       static bool recept=false ;
       int rank ;
       int count ;

       if (recept==false)
       {
         traceOff() ;
         MPI_Iprobe(MPI_ANY_SOURCE,1,CXios::globalComm, &flag, &status) ;
         traceOn() ;
         if (flag==true)
         {
           rank=status.MPI_SOURCE ;
           MPI_Get_count(&status,MPI_CHAR,&count) ;
           buffer=new char[count] ;
           MPI_Irecv((void*)buffer,count,MPI_CHAR,rank,1,CXios::globalComm,&request) ;
           recept=true ;
         }
       }
       else
       {
         traceOff() ;
         MPI_Test(&request,&flag,&status) ;
         traceOn() ;
         if (flag==true)
         {
           rank=status.MPI_SOURCE ;
           MPI_Get_count(&status,MPI_CHAR,&count) ;
           recvContextMessage((void*)buffer,count) ;
           delete [] buffer ;
           recept=false ;
         }
       }
     }

     void CServer::recvContextMessage(void* buff,int count)
     {
       static map<string,contextMessage> recvContextId;
       map<string,contextMessage>::iterator it ;
       CBufferIn buffer(buff,count) ;
       string id ;
       int clientLeader ;
       int nbMessage ;

       buffer>>id>>nbMessage>>clientLeader ;

       it=recvContextId.find(id) ;
       if (it==recvContextId.end())
       {
         contextMessage msg={0,0} ;
         pair<map<string,contextMessage>::iterator,bool> ret ;
         ret=recvContextId.insert(pair<string,contextMessage>(id,msg)) ;
         it=ret.first ;
       }
       it->second.nbRecv+=1 ;
       it->second.leaderRank+=clientLeader ;

       if (it->second.nbRecv==nbMessage)
       {
         int size ;
         MPI_Comm_size(intraComm,&size) ;
//         MPI_Request* requests= new MPI_Request[size-1] ;
//         MPI_Status* status= new MPI_Status[size-1] ;
         MPI_Request* requests= new MPI_Request[size] ;
         MPI_Status* status= new MPI_Status[size] ;

         CMessage msg ;
         msg<<id<<it->second.leaderRank;
         int messageSize=msg.size() ;
         void * sendBuff = new char[messageSize] ;
         CBufferOut sendBuffer(sendBuff,messageSize) ;
         sendBuffer<<msg ;

         // Include root itself in order not to have a divergence
         for(int i=0; i<size; i++)
         {
           MPI_Isend(sendBuff,sendBuffer.count(),MPI_CHAR,i,2,intraComm,&requests[i]) ;
         }

         recvContextId.erase(it) ;
         delete [] requests ;
         delete [] status ;

       }
     }

     void CServer::listenRootContext(void)
     {
       MPI_Status status ;
       int flag ;
       static std::vector<void*> buffers;
       static std::vector<MPI_Request> requests ;
       static std::vector<int> counts ;
       static std::vector<bool> isEventRegistered ;
       static std::vector<bool> isEventQueued ;
       MPI_Request request;

       int rank ;
       const int root=0 ;
       boost::hash<string> hashString;
       size_t hashId = hashString("RegisterContext");

       // (1) Receive context id from the root, save it into a buffer
       traceOff() ;
       MPI_Iprobe(root,2,intraComm, &flag, &status) ;
       traceOn() ;
       if (flag==true)
       {
         counts.push_back(0);
         MPI_Get_count(&status,MPI_CHAR,&(counts.back())) ;
         buffers.push_back(new char[counts.back()]) ;
         requests.push_back(request);
         MPI_Irecv((void*)(buffers.back()),counts.back(),MPI_CHAR,root,2,intraComm,&(requests.back())) ;
         isEventRegistered.push_back(false);
         isEventQueued.push_back(false);
         nbContexts++;
       }

       for (int ctxNb = 0; ctxNb < nbContexts; ctxNb++ )
       {
         // (2) If context id is received, register an event
         MPI_Test(&requests[ctxNb],&flag,&status) ;
         if (flag==true && !isEventRegistered[ctxNb])
         {
           eventScheduler->registerEvent(ctxNb,hashId);
           isEventRegistered[ctxNb] = true;
         }
         // (3) If event has been scheduled, call register context
         if (eventScheduler->queryEvent(ctxNb,hashId) && !isEventQueued[ctxNb])
         {
           registerContext(buffers[ctxNb],counts[ctxNb]) ;
           isEventQueued[ctxNb] = true;
           delete [] buffers[ctxNb] ;
         }
       }

     }

     void CServer::registerContext(void* buff, int count, int leaderRank)
     {
       string contextId;
       CBufferIn buffer(buff, count);
//       buffer >> contextId;
       buffer >> contextId>>leaderRank;
       CContext* context;

       info(20) << "CServer : Register new Context : " << contextId << endl;

       if (contextList.find(contextId) != contextList.end())
         ERROR("void CServer::registerContext(void* buff, int count, int leaderRank)",
               << "Context '" << contextId << "' has already been registred");

       context=CContext::create(contextId);
       contextList[contextId]=context;

       // Primary or classical server: create communication channel with a client
       // (1) create interComm (with a client)
       // (2) initialize client and server (contextClient and contextServer)
       MPI_Comm inter;
       if (serverLevel < 2)
       {
         MPI_Comm contextInterComm;
         MPI_Intercomm_create(intraComm, 0, CXios::globalComm, leaderRank, 10+leaderRank, &contextInterComm);
         MPI_Intercomm_merge(contextInterComm,1,&inter);
         MPI_Barrier(inter);
         MPI_Comm_free(&inter);
         context->initServer(intraComm,contextInterComm);
         contextInterComms.push_back(contextInterComm);

       }
       // Secondary server: create communication channel with a primary server
       // (1) duplicate interComm with a primary server
       // (2) initialize client and server (contextClient and contextServer)
       // Remark: in the case of the secondary server there is no need to create an interComm calling MPI_Intercomm_create,
       //         because interComm of CContext is defined on the same processes as the interComm of CServer.
       //         So just duplicate it.
       else if (serverLevel == 2)
       {
         MPI_Comm_dup(interCommLeft.front(), &inter);
         contextInterComms.push_back(inter);
         context->initServer(intraComm, contextInterComms.back());
       }

       // Primary server:
       // (1) send create context message to secondary servers
       // (2) initialize communication channels with secondary servers (create contextClient and contextServer)
       if (serverLevel == 1)
       {
         int i = 0, size;
         MPI_Comm_size(intraComm, &size) ;
         for (std::list<MPI_Comm>::iterator it = interCommRight.begin(); it != interCommRight.end(); it++, ++i)
         {
           StdString str = contextId +"_server_" + boost::lexical_cast<string>(i);
           CMessage msg;
           int messageSize;
           msg<<str<<size<<rank_ ;
           messageSize = msg.size() ;
           buff = new char[messageSize] ;
           CBufferOut buffer(buff,messageSize) ;
           buffer<<msg ;
           MPI_Send(buff, buffer.count(), MPI_CHAR, sndServerGlobalRanks[i], 1, CXios::globalComm) ;
           MPI_Comm_dup(*it, &inter);
           contextInterComms.push_back(inter);
           MPI_Comm_dup(intraComm, &inter);
           contextIntraComms.push_back(inter);
           context->initClient(contextIntraComms.back(), contextInterComms.back()) ;
           delete [] buff ;
         }
       }
     }

     void CServer::contextEventLoop(bool enableEventsProcessing /*= true*/)
     {
       bool isFinalized ;
       map<string,CContext*>::iterator it ;

       for(it=contextList.begin();it!=contextList.end();it++)
       {
         isFinalized=it->second->isFinalized();
         if (isFinalized)
         {
           contextList.erase(it) ;
           break ;
         }
         else
           it->second->checkBuffersAndListen(enableEventsProcessing);
       }
     }

     //! Get rank of the current process in the intraComm
     int CServer::getRank()
     {
       int rank;
       MPI_Comm_rank(intraComm,&rank);
       return rank;
     }

     vector<int>& CServer::getSecondaryServerGlobalRanks()
     {
       return sndServerGlobalRanks;
     }

    /*!
    * Open a file specified by a suffix and an extension and use it for the given file buffer.
    * The file name will be suffix+rank+extension.
    * 
    * \param fileName[in] protype file name
    * \param ext [in] extension of the file
    * \param fb [in/out] the file buffer
    */
    void CServer::openStream(const StdString& fileName, const StdString& ext, std::filebuf* fb)
    {
      StdStringStream fileNameClient;
      int numDigit = 0;
      int size = 0;
      int id;
      MPI_Comm_size(CXios::globalComm, &size);
      while (size)
      {
        size /= 10;
        ++numDigit;
      }
      id = rank_; //getRank();

      fileNameClient << fileName << "_" << std::setfill('0') << std::setw(numDigit) << id << ext;
      fb->open(fileNameClient.str().c_str(), std::ios::out);
      if (!fb->is_open())
        ERROR("void CServer::openStream(const StdString& fileName, const StdString& ext, std::filebuf* fb)",
              << std::endl << "Can not open <" << fileNameClient.str() << "> file to write the server log(s).");
    }

    /*!
    * \brief Open a file stream to write the info logs
    * Open a file stream with a specific file name suffix+rank
    * to write the info logs.
    * \param fileName [in] protype file name
    */
    void CServer::openInfoStream(const StdString& fileName)
    {
      std::filebuf* fb = m_infoStream.rdbuf();
      openStream(fileName, ".out", fb);

      info.write2File(fb);
      report.write2File(fb);
    }

    //! Write the info logs to standard output
    void CServer::openInfoStream()
    {
      info.write2StdOut();
      report.write2StdOut();
    }

    //! Close the info logs file if it opens
    void CServer::closeInfoStream()
    {
      if (m_infoStream.is_open()) m_infoStream.close();
    }

    /*!
    * \brief Open a file stream to write the error log
    * Open a file stream with a specific file name suffix+rank
    * to write the error log.
    * \param fileName [in] protype file name
    */
    void CServer::openErrorStream(const StdString& fileName)
    {
      std::filebuf* fb = m_errorStream.rdbuf();
      openStream(fileName, ".err", fb);

      error.write2File(fb);
    }

    //! Write the error log to standard error output
    void CServer::openErrorStream()
    {
      error.write2StdErr();
    }

    //! Close the error log file if it opens
    void CServer::closeErrorStream()
    {
      if (m_errorStream.is_open()) m_errorStream.close();
    }
}
