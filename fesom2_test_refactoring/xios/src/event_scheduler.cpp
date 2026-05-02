#include "event_scheduler.hpp"
#include "xios_spl.hpp"
#include "mpi.hpp"
#include "tracer.hpp"
#include "timer.hpp"

namespace xios
{
 
 
  CEventScheduler::CEventScheduler(const MPI_Comm& comm) 
  {
    MPI_Comm_dup(comm, &communicator) ;
    MPI_Comm_size(communicator,&mpiSize) ;
    MPI_Comm_rank(communicator,&mpiRank);


    int maxChild=1 ;

    int m ;
    do
    {
      m=1 ;
      maxChild=maxChild+1 ;
      for(int i=0;i<maxChild;i++) m=m*maxChild ;
     } while(m<mpiSize) ;
    
    
    int maxLevel=0 ;
    for(int size=1; size<=mpiSize; size*=maxChild) maxLevel++ ; 

    int begin, end, nb ;
    int pos, n ;
 
    parent=vector<int>(maxLevel+1) ;
    child=vector<vector<int> >(maxLevel+1,vector<int>(maxChild)) ;
    nbChild=vector<int> (maxLevel+1) ;
   
    level=0 ;
    begin=0 ;
    end=mpiSize-1 ;     
    nb=end-begin+1 ;
     
    do
    {
      n=0 ;
      pos=begin ;
      nbChild[level]=0 ;
      parent[level+1]=begin ;
      for(int i=0;i<maxChild && i<nb ;i++)
      {
        if (i<nb%maxChild) n = nb/maxChild + 1 ;
        else n = nb/maxChild ;
      
        if (mpiRank>=pos && mpiRank<pos+n)
        {
          begin=pos ;
          end=pos+n-1 ;
        }
        child[level][i]=pos ;
        pos=pos+n ;
        nbChild[level]++ ;
      } 
      nb=end-begin+1 ;
      level=level+1 ;
    } while (nb>1) ;

    
  }

  CEventScheduler::~CEventScheduler()
  {

  } 

  void CEventScheduler::registerEvent(const size_t timeLine, const size_t contextHashId)
  {
    registerEvent(timeLine, contextHashId, level) ;
  }
  
  void CEventScheduler::registerEvent(const size_t timeLine, const size_t contextHashId, const size_t lev)
  {
       
    traceOff() ;
    SPendingRequest* sentRequest=new SPendingRequest ;
    sentRequest->buffer[0]=timeLine ;
    sentRequest->buffer[1]=contextHashId ;
    sentRequest->buffer[2]=lev-1 ;

    pendingSentParentRequest.push(sentRequest) ;
    MPI_Isend(sentRequest->buffer,3, MPI_UNSIGNED_LONG, parent[lev], 0, communicator, &sentRequest->request) ;
    traceOn() ;
  } 

  bool CEventScheduler::queryEvent(const size_t timeLine, const size_t contextHashId)
  {

    if (! eventStack.empty() && eventStack.front().first==timeLine && eventStack.front().second==contextHashId)
    {
      eventStack.pop() ;
      return true ;
    }
    else return false ; 
  } 
  
  void CEventScheduler::checkEvent(void)
  {
    traceOff() ;
    CTimer::get("scheduler checkChildRequest").resume();
    checkChildRequest() ;
    CTimer::get("scheduler checkChildRequest").suspend();

    CTimer::get("scheduler checkParentRequest").resume();
    checkParentRequest() ;
    CTimer::get("scheduler checkParentRequest").suspend();
    traceOn() ;

  }
  
  void CEventScheduler::checkParentRequest(void)
  {
    int completed ;
    MPI_Status status ;
    int received ;
    SPendingRequest* recvRequest ;
    completed=true ;
    
    // check sent request to parent
    while (! pendingSentParentRequest.empty() && completed)
    {
      MPI_Test( & pendingSentParentRequest.front()->request, &completed, &status) ;
      if (completed) 
      {
        delete pendingSentParentRequest.front() ;
        pendingSentParentRequest.pop() ;
      }
    }
    
    // probe if a message is coming from parent
    received=true ;
    while(received)
    {
      MPI_Iprobe(MPI_ANY_SOURCE,1,communicator,&received, &status) ;
      if (received)
      {
        recvRequest=new SPendingRequest ;
        MPI_Irecv(recvRequest->buffer, 3, MPI_UNSIGNED_LONG, MPI_ANY_SOURCE, 1, communicator, &(recvRequest->request)) ;
        pendingRecvParentRequest.push(recvRequest) ;
      }
    }
    
     // check sent request from parent
    completed=true ;
    while (! pendingRecvParentRequest.empty() && completed)
    {
      recvRequest=pendingRecvParentRequest.front() ;
      MPI_Test( &(recvRequest->request), &completed, &status) ;
      if (completed) 
      {
        size_t timeLine=recvRequest->buffer[0] ;
        size_t hashId=recvRequest->buffer[1] ;
        size_t lev=recvRequest->buffer[2] ;
        delete recvRequest ;
        pendingRecvParentRequest.pop() ;       
 
        if (lev==level) eventStack.push(pair<size_t,size_t>(timeLine,hashId)) ;
        else  bcastEvent(timeLine, hashId, lev) ;
      }
    }   
    
  }

  void CEventScheduler::checkChildRequest(void)
  {
// function call only by parent mpi process

    MPI_Status status ; 
    int received ;
    received=true ;
    SPendingRequest* recvRequest ;
    
    // check for posted requests and make the corresponding receive
    while(received)
    {
      MPI_Iprobe(MPI_ANY_SOURCE,0,communicator,&received, &status) ;
      if (received)
      {
        recvRequest=new SPendingRequest ;
        MPI_Irecv(recvRequest->buffer, 3, MPI_UNSIGNED_LONG, MPI_ANY_SOURCE, 0, communicator, &recvRequest->request) ;
        pendingRecvChildRequest.push_back(recvRequest) ;
      }
    }
    
    // check if receive request is achieved
    
    for(list<SPendingRequest*>::iterator it=pendingRecvChildRequest.begin(); it!=pendingRecvChildRequest.end() ; )
    {
      MPI_Test(&((*it)->request),&received,&status) ;
      if (received)
      {
        size_t timeLine=(*it)->buffer[0] ;
        size_t hashId=(*it)->buffer[1] ;
        size_t lev=(*it)->buffer[2] ;
        
        SEvent event={timeLine,hashId,lev} ;
        delete *it ; // free mem
        it=pendingRecvChildRequest.erase(it) ; // get out of the list
        
        map< SEvent,int>::iterator itEvent=recvEvent.find(event) ;
        if (itEvent==recvEvent.end()) 
        {
          itEvent=(recvEvent.insert(pair< SEvent ,int > (event,1))).first ;
 
        }
        else (itEvent->second)++ ;
        if (itEvent->second==nbChild[lev])
        {
          if (lev==0)
          {
            bcastEvent(timeLine,hashId,lev) ;
            recvEvent.erase(itEvent) ;
          }
          else
          {
            registerEvent( timeLine,hashId,lev) ;
          }
        }
      }
      else ++it ;
    }
    
    // check if bcast request is achieved

    for(list<SPendingRequest*>::iterator it=pendingSentChildRequest.begin(); it!=pendingSentChildRequest.end() ; )
    {
      MPI_Test(&(*it)->request,&received,&status) ;
      if (received)
      {
        delete *it ;    // free memory
        it = pendingSentChildRequest.erase(it) ;          // get out of the list

      }
      else ++it ;
        
    }
  }
  
  void CEventScheduler::bcastEvent(const size_t timeLine, const size_t contextHashId, const size_t lev)
  {
    SPendingRequest* sentRequest ;
     
    
    for(int i=0; i<nbChild[lev];i++)
    {
      sentRequest=new SPendingRequest ;
      sentRequest->buffer[0]=timeLine ;
      sentRequest->buffer[1]=contextHashId ;
      sentRequest->buffer[2]=lev+1 ;
      MPI_Isend(sentRequest->buffer,3, MPI_UNSIGNED_LONG, child[lev][i], 1, communicator, & sentRequest->request) ;
      pendingSentChildRequest.push_back(sentRequest) ;
    }
  }
   

}
