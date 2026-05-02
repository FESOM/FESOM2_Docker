#include "globalScopeData.hpp"
#include "xios_spl.hpp"
#include "cxios.hpp"
#include "client.hpp"
#include <boost/functional/hash.hpp>
#include "type.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "oasis_cinterface.hpp"
#include "mpi.hpp"
#include "timer.hpp"
#include "buffer_client.hpp"
#include "string_tools.hpp"
#include "temporal_filter.hpp"
#include "source_filter.hpp"

namespace xios
{

    MPI_Comm CClient::intraComm ;
    MPI_Comm CClient::interComm ;
    std::list<MPI_Comm> CClient::contextInterComms;
    int CClient::serverLeader ;
    bool CClient::is_MPI_Initialized ;
    int CClient::rank_ = INVALID_RANK;
    StdOFStream CClient::m_infoStream;
    StdOFStream CClient::m_errorStream;
    MPI_Comm& CClient::getInterComm(void)   { return (interComm); }
     
///---------------------------------------------------------------
/*!
 * \fn void CClient::initialize(const string& codeId, MPI_Comm& localComm, MPI_Comm& returnComm)
 * Function creates intraComm (CClient::intraComm) for client group with id=codeId and interComm (CClient::interComm) between client and server groups.
 * \param [in] codeId identity of context.
 * \param [in/out] localComm local communicator.
 * \param [in/out] returnComm (intra)communicator of client group.
 */

    void CClient::initialize(const string& codeId, MPI_Comm& localComm, MPI_Comm& returnComm)
    {
      int initialized ;
      MPI_Initialized(&initialized) ;
      if (initialized) is_MPI_Initialized=true ;
      else is_MPI_Initialized=false ;
      int rank ;

// don't use OASIS
      if (!CXios::usingOasis)
      {
// localComm isn't given
        if (localComm == MPI_COMM_NULL)
        {
          if (!is_MPI_Initialized)
          {
            MPI_Init(NULL, NULL);
          }
          CTimer::get("XIOS").resume() ;
          CTimer::get("XIOS init/finalize").resume() ;
          boost::hash<string> hashString ;

          unsigned long hashClient=hashString(codeId) ;
          unsigned long hashServer=hashString(CXios::xiosCodeId) ;
          unsigned long* hashAll ;
          int size ;
          int myColor ;
          int i,c ;
          MPI_Comm newComm ;

          MPI_Comm_size(CXios::globalComm,&size) ;
          MPI_Comm_rank(CXios::globalComm,&rank_);

          hashAll=new unsigned long[size] ;

          MPI_Allgather(&hashClient,1,MPI_LONG,hashAll,1,MPI_LONG,CXios::globalComm) ;

          map<unsigned long, int> colors ;
          map<unsigned long, int> leaders ;

          for(i=0,c=0;i<size;i++)
          {
            if (colors.find(hashAll[i])==colors.end())
            {
              colors[hashAll[i]] =c ;
              leaders[hashAll[i]]=i ;
              c++ ;
            }
          }

          // Verify whether we are on server mode or not
          CXios::setNotUsingServer();
          for (i=0; i < size; ++i)
          {
            if (hashServer == hashAll[i])
            {
              CXios::setUsingServer();
              break;
            }
          }

          myColor=colors[hashClient];
          MPI_Comm_split(CXios::globalComm,myColor,rank_,&intraComm) ;

          if (CXios::usingServer)
          {
            int clientLeader=leaders[hashClient] ;
            serverLeader=leaders[hashServer] ;
            int intraCommSize, intraCommRank ;
            MPI_Comm_size(intraComm,&intraCommSize) ;
            MPI_Comm_rank(intraComm,&intraCommRank) ;
            info(50)<<"intercommCreate::client "<<rank_<<" intraCommSize : "<<intraCommSize
                   <<" intraCommRank :"<<intraCommRank<<"  clientLeader "<< serverLeader<<endl ;
             MPI_Intercomm_create(intraComm, 0, CXios::globalComm, serverLeader, 0, &interComm) ;
             //rank_ = intraCommRank;
          }
          else
          {
            MPI_Comm_dup(intraComm,&interComm) ;
          }
          delete [] hashAll ;
        }
        // localComm argument is given
        else
        {
          if (CXios::usingServer)
          {
            //ERROR("void CClient::initialize(const string& codeId,MPI_Comm& localComm,MPI_Comm& returnComm)", << " giving a local communictor is not compatible with using server mode") ;
          }
          else
          {
            MPI_Comm_dup(localComm,&intraComm) ;
            MPI_Comm_dup(intraComm,&interComm) ;
          }
        }
      }
      // using OASIS
      else
      {
        // localComm isn't given
        if (localComm == MPI_COMM_NULL)
        {
          if (!is_MPI_Initialized) oasis_init(codeId) ;
          oasis_get_localcomm(localComm) ;
        }
        MPI_Comm_dup(localComm,&intraComm) ;

        CTimer::get("XIOS").resume() ;
        CTimer::get("XIOS init/finalize").resume() ;

        if (CXios::usingServer)
        {
          MPI_Status status ;
          MPI_Comm_rank(intraComm,&rank_) ;

          oasis_get_intercomm(interComm,CXios::xiosCodeId) ;
          if (rank_==0) MPI_Recv(&serverLeader,1, MPI_INT, 0, 0, interComm, &status) ;
          MPI_Bcast(&serverLeader,1,MPI_INT,0,intraComm) ;
        }
        else MPI_Comm_dup(intraComm,&interComm) ;
      }

      MPI_Comm_dup(intraComm,&returnComm) ;
    }

///---------------------------------------------------------------
/*!
 * \fn void CClient::registerContext(const string& id, MPI_Comm contextComm)
 * \brief Sends a request to create a context to server. Creates client/server contexts.
 * \param [in] id id of context.
 * \param [in] contextComm.
 * Function is only called by client.
 */
    void CClient::registerContext(const string& id, MPI_Comm contextComm)
    {
      CContext::setCurrent(id) ;
      CContext* context=CContext::create(id);
      StdString idServer(id);
      idServer += "_server";

      if (CXios::isServer && !context->hasServer)
      // Attached mode
      {
        MPI_Comm contextInterComm ;
        MPI_Comm_dup(contextComm,&contextInterComm) ;
        CContext* contextServer = CContext::create(idServer);

        // Firstly, initialize context on client side
        context->initClient(contextComm,contextInterComm, contextServer);

        // Secondly, initialize context on server side
        contextServer->initServer(contextComm,contextInterComm, context);

        // Finally, we should return current context to context client
        CContext::setCurrent(id);

        contextInterComms.push_back(contextInterComm);
      }
      else
      {
        int size,rank,globalRank ;
        size_t message_size ;
        int leaderRank ;
        MPI_Comm contextInterComm ;

        MPI_Comm_size(contextComm,&size) ;
        MPI_Comm_rank(contextComm,&rank) ;
        MPI_Comm_rank(CXios::globalComm,&globalRank) ;
        if (rank!=0) globalRank=0 ;

        CMessage msg ;
        msg<<idServer<<size<<globalRank ;
//        msg<<id<<size<<globalRank ;

        int messageSize=msg.size() ;
        char * buff = new char[messageSize] ;
        CBufferOut buffer((void*)buff,messageSize) ;
        buffer<<msg ;

        MPI_Send((void*)buff,buffer.count(),MPI_CHAR,serverLeader,1,CXios::globalComm) ;

        MPI_Intercomm_create(contextComm,0,CXios::globalComm,serverLeader,10+globalRank,&contextInterComm) ;
        info(10)<<"Register new Context : "<<id<<endl ;
        MPI_Comm inter ;
        MPI_Intercomm_merge(contextInterComm,0,&inter) ;
        MPI_Barrier(inter) ;
        MPI_Comm_free(&inter);

        context->initClient(contextComm,contextInterComm) ;

        contextInterComms.push_back(contextInterComm);
        delete [] buff ;

      }
    }

/*!
 * \fn void CClient::callOasisEnddef(void)
 * \brief Send the order to the servers to call "oasis_enddef". It must be done by each compound of models before calling oasis_enddef on client side
 * Function is only called by client.
 */
    void CClient::callOasisEnddef(void)
    {
      bool oasisEnddef=CXios::getin<bool>("call_oasis_enddef",true) ;
      if (!oasisEnddef) ERROR("void CClient::callOasisEnddef(void)", <<"Function xios_oasis_enddef called but variable <call_oasis_enddef> is set to false."<<endl
                                                                     <<"Variable <call_oasis_enddef> must be set to true"<<endl) ;
      if (CXios::isServer)
      // Attached mode
      {
        // nothing to do   
      }
      else
      {
        int rank ;
        int msg=0 ;

        MPI_Comm_rank(intraComm,&rank) ;
        if (rank==0) 
        {
          MPI_Send(&msg,1,MPI_INT,0,5,interComm) ; // tags oasis_endded = 5
        }

      }
    }


    void CClient::finalize(void)
    {
      int rank ;
      int msg=0 ;

      MPI_Comm_rank(intraComm,&rank) ;
 
      if (!CXios::isServer)
      {
        MPI_Comm_rank(intraComm,&rank) ;
        if (rank==0)
        {
          MPI_Send(&msg,1,MPI_INT,0,0,interComm) ;
        }
      }


      /* MPI_Comm_free(&interComm); */ // WARNING remove freeing communicator !! --> deadlock raised, to be checked
      for (std::list<MPI_Comm>::iterator it = contextInterComms.begin(); it != contextInterComms.end(); it++)
        /* MPI_Comm_free(&(*it)) */ ; // WARNING remove freeing communicator !! --> deadlock raised, to be checked
      MPI_Comm_free(&intraComm);

      CTimer::get("XIOS init/finalize").suspend() ;
      CTimer::get("XIOS").suspend() ;

      if (!is_MPI_Initialized)
      {
        if (CXios::usingOasis) oasis_finalize();
        else MPI_Finalize() ;
      }
      
      info(20) << "Client side context is finalized"<<endl ;
      report(0) <<" Performance report : Whole time from XIOS init and finalize: "<< CTimer::get("XIOS init/finalize").getCumulatedTime()<<" s"<<endl ;
      report(0) <<" Performance report : total time spent for XIOS : "<< CTimer::get("XIOS").getCumulatedTime()<<" s"<<endl ;
      report(0)<< " Performance report : time spent for waiting free buffer : "<< CTimer::get("Blocking time").getCumulatedTime()<<" s"<<endl ;
      report(0)<< " Performance report : Ratio : "<< CTimer::get("Blocking time").getCumulatedTime()/CTimer::get("XIOS init/finalize").getCumulatedTime()*100.<<" %"<<endl ;
      report(0)<< " Performance report : This ratio must be close to zero. Otherwise it may be usefull to increase buffer size or numbers of server"<<endl ;
//      report(0)<< " Memory report : Current buffer_size : "<<CXios::bufferSize<<endl ;
      report(0)<< " Memory report : Minimum buffer size required : " << CClientBuffer::maxRequestSize << " bytes" << endl ;
      report(0)<< " Memory report : increasing it by a factor will increase performance, depending of the volume of data wrote in file at each time step of the file"<<endl ;
      // Per-rank filter-instance / call-count diagnostic. Free counters,
      // gated to log level >100 so production logs stay clean.
      if (info.getLevel() > 100)
      {
        CTemporalFilter::reportWindowStats();
        CSourceFilter::reportInstanceStats();
      }
      report(100)<<CTimer::getAllCumulatedTime()<<endl ;
   }

    /*!
    * Return global rank without oasis and current rank in model intraComm in case of oasis
    */
   int CClient::getRank()
   {
     return rank_;
   }

    /*!
    * Open a file specified by a suffix and an extension and use it for the given file buffer.
    * The file name will be suffix+rank+extension.
    * 
    * \param fileName[in] protype file name
    * \param ext [in] extension of the file
    * \param fb [in/out] the file buffer
    */
    void CClient::openStream(const StdString& fileName, const StdString& ext, std::filebuf* fb)
    {
      StdStringStream fileNameClient;
      int numDigit = 0;
      int size = 0;
      int rank;
      MPI_Comm_size(CXios::globalComm, &size);
      while (size)
      {
        size /= 10;
        ++numDigit;
      }

      if (CXios::usingOasis)
      {
        MPI_Comm_rank(CXios::globalComm,&rank);
        fileNameClient << fileName << "_" << std::setfill('0') << std::setw(numDigit) << rank << ext;
      }
      else
        fileNameClient << fileName << "_" << std::setfill('0') << std::setw(numDigit) << getRank() << ext;


      fb->open(fileNameClient.str().c_str(), std::ios::out);
      if (!fb->is_open())
        ERROR("void CClient::openStream(const StdString& fileName, const StdString& ext, std::filebuf* fb)",
              << std::endl << "Can not open <" << fileNameClient.str() << "> file to write the client log(s).");
    }

    /*!
    * \brief Open a file stream to write the info logs
    * Open a file stream with a specific file name suffix+rank
    * to write the info logs.
    * \param fileName [in] protype file name
    */
    void CClient::openInfoStream(const StdString& fileName)
    {
      std::filebuf* fb = m_infoStream.rdbuf();
      openStream(fileName, ".out", fb);

      info.write2File(fb);
      report.write2File(fb);
    }

    //! Write the info logs to standard output
    void CClient::openInfoStream()
    {
      info.write2StdOut();
      report.write2StdOut();
    }

    //! Close the info logs file if it opens
    void CClient::closeInfoStream()
    {
      if (m_infoStream.is_open()) m_infoStream.close();
    }

    /*!
    * \brief Open a file stream to write the error log
    * Open a file stream with a specific file name suffix+rank
    * to write the error log.
    * \param fileName [in] protype file name
    */
    void CClient::openErrorStream(const StdString& fileName)
    {
      std::filebuf* fb = m_errorStream.rdbuf();
      openStream(fileName, ".err", fb);

      error.write2File(fb);
    }

    //! Write the error log to standard error output
    void CClient::openErrorStream()
    {
      error.write2StdErr();
    }

    //! Close the error log file if it opens
    void CClient::closeErrorStream()
    {
      if (m_errorStream.is_open()) m_errorStream.close();
    }
}
