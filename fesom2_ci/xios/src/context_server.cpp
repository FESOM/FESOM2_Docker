#include "context_server.hpp"
#include "buffer_in.hpp"
#include "type.hpp"
#include "context.hpp"
#include "object_template.hpp"
#include "group_template.hpp"
#include "attribute_template.hpp"
#include "domain.hpp"
#include "field.hpp"
#include "file.hpp"
#include "grid.hpp"
#include "mpi.hpp"
#include "tracer.hpp"
#include "timer.hpp"
#include "cxios.hpp"
#include "event_scheduler.hpp"
#include "server.hpp"
#include <boost/functional/hash.hpp>



namespace xios
{

  CContextServer::CContextServer(CContext* parent,MPI_Comm intraComm_,MPI_Comm interComm_)
  {
    context=parent;
    intraComm=intraComm_;
    MPI_Comm_size(intraComm,&intraCommSize);
    MPI_Comm_rank(intraComm,&intraCommRank);

    interComm=interComm_;
    int flag;
    MPI_Comm_test_inter(interComm,&flag);
    if (flag) MPI_Comm_remote_size(interComm,&commSize);
    else  MPI_Comm_size(interComm,&commSize);

    currentTimeLine=0;
    scheduled=false;
    finished=false;
    boost::hash<string> hashString;
    if (CServer::serverLevel == 1)
      hashId=hashString(context->getId() + boost::lexical_cast<string>(context->clientPrimServer.size()));
    else
      hashId=hashString(context->getId());
  }

  void CContextServer::setPendingEvent(void)
  {
    pendingEvent=true;
  }

  bool CContextServer::hasPendingEvent(void)
  {
    return pendingEvent;
  }

  bool CContextServer::hasFinished(void)
  {
    return finished;
  }

  bool CContextServer::eventLoop(bool enableEventsProcessing /*= true*/)
  {
    listen();
    checkPendingRequest();
    if (enableEventsProcessing)
      processEvents();
    return finished;
  }

  void CContextServer::listen(void)
  {
    int rank;
    int flag;
    int count;
    char * addr;
    MPI_Status status;
    map<int,CServerBuffer*>::iterator it;
    bool okLoop;

    traceOff();
    MPI_Iprobe(MPI_ANY_SOURCE, 20,interComm,&flag,&status);
    traceOn();

    if (flag==true)
    {
      rank=status.MPI_SOURCE ;
      okLoop = true;
      if (pendingRequest.find(rank)==pendingRequest.end())
        okLoop = !listenPendingRequest(status) ;
      if (okLoop)
      {
        for(rank=0;rank<commSize;rank++)
        {
          if (pendingRequest.find(rank)==pendingRequest.end())
          {

            traceOff();
            MPI_Iprobe(rank, 20,interComm,&flag,&status);
            traceOn();
            if (flag==true) listenPendingRequest(status) ;
          }
        }
      }
    }
  }

  bool CContextServer::listenPendingRequest(MPI_Status& status)
  {
    int count;
    char * addr;
    map<int,CServerBuffer*>::iterator it;
    int rank=status.MPI_SOURCE ;

    it=buffers.find(rank);
    if (it==buffers.end()) // Receive the buffer size and allocate the buffer
    {
       StdSize buffSize = 0;
       MPI_Recv(&buffSize, 1, MPI_LONG, rank, 20, interComm, &status);
       mapBufferSize_.insert(std::make_pair(rank, buffSize));
       it=(buffers.insert(pair<int,CServerBuffer*>(rank,new CServerBuffer(buffSize)))).first;
       return true;
    }
    else
    {
      MPI_Get_count(&status,MPI_CHAR,&count);
      if (it->second->isBufferFree(count))
      {
         addr=(char*)it->second->getBuffer(count);
         MPI_Irecv(addr,count,MPI_CHAR,rank,20,interComm,&pendingRequest[rank]);
         bufferRequest[rank]=addr;
         return true;
       }
      else
        return false;
    }
  }


  void CContextServer::checkPendingRequest(void)
  {
    map<int,MPI_Request>::iterator it;
    list<int> recvRequest;
    list<int>::iterator itRecv;
    int rank;
    int flag;
    int count;
    MPI_Status status;

    for(it=pendingRequest.begin();it!=pendingRequest.end();it++)
    {
      rank=it->first;
      traceOff();
      MPI_Test(& it->second, &flag, &status);
      traceOn();
      if (flag==true)
      {
        recvRequest.push_back(rank);
        MPI_Get_count(&status,MPI_CHAR,&count);
        processRequest(rank,bufferRequest[rank],count);
      }
    }

    for(itRecv=recvRequest.begin();itRecv!=recvRequest.end();itRecv++)
    {
      pendingRequest.erase(*itRecv);
      bufferRequest.erase(*itRecv);
    }
  }

  void CContextServer::processRequest(int rank, char* buff,int count)
  {

    CBufferIn buffer(buff,count);
    char* startBuffer,endBuffer;
    int size, offset;
    size_t timeLine;
    map<size_t,CEventServer*>::iterator it;

    CTimer::get("Process request").resume();
    while(count>0)
    {
      char* startBuffer=(char*)buffer.ptr();
      CBufferIn newBuffer(startBuffer,buffer.remain());
      newBuffer>>size>>timeLine;

      it=events.find(timeLine);
      if (it==events.end()) it=events.insert(pair<int,CEventServer*>(timeLine,new CEventServer)).first;
      it->second->push(rank,buffers[rank],startBuffer,size);

      buffer.advance(size);
      count=buffer.remain();
    }
    CTimer::get("Process request").suspend();
  }

  void CContextServer::processEvents(void)
  {
    map<size_t,CEventServer*>::iterator it;
    CEventServer* event;

    it=events.find(currentTimeLine);
    if (it!=events.end())
    {
      event=it->second;

      if (event->isFull())
      {
        if (!scheduled && CServer::eventScheduler) // Skip event scheduling for attached mode and reception on client side
        {
          CServer::eventScheduler->registerEvent(currentTimeLine,hashId);
          scheduled=true;
        }
        else if (!CServer::eventScheduler || CServer::eventScheduler->queryEvent(currentTimeLine,hashId) )
        {
         // When using attached mode, synchronise the processes to avoid that differents event be scheduled by differents processes
         // The best way to properly solve this problem will be to use the event scheduler also in attached mode
         // for now just set up a MPI barrier
         if (!CServer::eventScheduler && CXios::isServer) MPI_Barrier(intraComm) ;

         CTimer::get("Process events").resume();
         dispatchEvent(*event);
         CTimer::get("Process events").suspend();
         pendingEvent=false;
         delete event;
         events.erase(it);
         currentTimeLine++;
         scheduled = false;
        }
      }
    }
  }

  CContextServer::~CContextServer()
  {
    map<int,CServerBuffer*>::iterator it;
    for(it=buffers.begin();it!=buffers.end();++it) delete it->second;
  }

  void CContextServer::dispatchEvent(CEventServer& event)
  {
    string contextName;
    string buff;
    int MsgSize;
    int rank;
    list<CEventServer::SSubEvent>::iterator it;
    StdString ctxId = context->getId();
    CContext::setCurrent(ctxId);
    StdSize totalBuf = 0;

    if (event.classId==CContext::GetType() && event.type==CContext::EVENT_ID_CONTEXT_FINALIZE)
    {
      finished=true;
      info(20)<<" CContextServer: Receive context <"<<context->getId()<<"> finalize."<<endl;
      context->finalize();
      std::map<int, StdSize>::const_iterator itbMap = mapBufferSize_.begin(),
                           iteMap = mapBufferSize_.end(), itMap;
      for (itMap = itbMap; itMap != iteMap; ++itMap)
      {
        rank = itMap->first;
        report(10)<< " Memory report : Context <"<<ctxId<<"> : server side : memory used for buffer of each connection to client" << endl
            << "  +) With client of rank " << rank << " : " << itMap->second << " bytes " << endl;
        totalBuf += itMap->second;
      }
      report(0)<< " Memory report : Context <"<<ctxId<<"> : server side : total memory used for buffer "<<totalBuf<<" bytes"<<endl;
    }
    else if (event.classId==CContext::GetType()) CContext::dispatchEvent(event);
    else if (event.classId==CContextGroup::GetType()) CContextGroup::dispatchEvent(event);
    else if (event.classId==CCalendarWrapper::GetType()) CCalendarWrapper::dispatchEvent(event);
    else if (event.classId==CDomain::GetType()) CDomain::dispatchEvent(event);
    else if (event.classId==CDomainGroup::GetType()) CDomainGroup::dispatchEvent(event);
    else if (event.classId==CAxis::GetType()) CAxis::dispatchEvent(event);
    else if (event.classId==CAxisGroup::GetType()) CAxisGroup::dispatchEvent(event);
    else if (event.classId==CScalar::GetType()) CScalar::dispatchEvent(event);
    else if (event.classId==CScalarGroup::GetType()) CScalarGroup::dispatchEvent(event);
    else if (event.classId==CGrid::GetType()) CGrid::dispatchEvent(event);
    else if (event.classId==CGridGroup::GetType()) CGridGroup::dispatchEvent(event);
    else if (event.classId==CField::GetType()) CField::dispatchEvent(event);
    else if (event.classId==CFieldGroup::GetType()) CFieldGroup::dispatchEvent(event);
    else if (event.classId==CFile::GetType()) CFile::dispatchEvent(event);
    else if (event.classId==CFileGroup::GetType()) CFileGroup::dispatchEvent(event);
    else if (event.classId==CVariable::GetType()) CVariable::dispatchEvent(event);
    else
    {
      ERROR("void CContextServer::dispatchEvent(CEventServer& event)",<<" Bad event class Id"<<endl);
    }
  }
}
