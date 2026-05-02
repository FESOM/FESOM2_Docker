#include "xios_spl.hpp"
#include "context_client.hpp"
#include "context_server.hpp"
#include "event_client.hpp"
#include "buffer_out.hpp"
#include "buffer_client.hpp"
#include "type.hpp"
#include "event_client.hpp"
#include "context.hpp"
#include "mpi.hpp"
#include "timer.hpp"
#include "cxios.hpp"
#include "server.hpp"

namespace xios
{
    /*!
    \param [in] parent Pointer to context on client side
    \param [in] intraComm_ communicator of group client
    \param [in] interComm_ communicator of group server
    \cxtSer [in] cxtSer Pointer to context of server side. (It is only used in case of attached mode).
    */
    CContextClient::CContextClient(CContext* parent, MPI_Comm intraComm_, MPI_Comm interComm_, CContext* cxtSer)
     : mapBufferSize_(), parentServer(cxtSer), maxBufferedEvents(4)
    {
      context = parent;
      intraComm = intraComm_;
      interComm = interComm_;
      MPI_Comm_rank(intraComm, &clientRank);
      MPI_Comm_size(intraComm, &clientSize);

      int flag;
      MPI_Comm_test_inter(interComm, &flag);
      if (flag) MPI_Comm_remote_size(interComm, &serverSize);
      else  MPI_Comm_size(interComm, &serverSize);

      computeLeader(clientRank, clientSize, serverSize, ranksServerLeader, ranksServerNotLeader);

      timeLine = 0;
    }

    void CContextClient::computeLeader(int clientRank, int clientSize, int serverSize,
                                       std::list<int>& rankRecvLeader,
                                       std::list<int>& rankRecvNotLeader)
    {
      if ((0 == clientSize) || (0 == serverSize)) return;

      if (clientSize < serverSize)
      {
        int serverByClient = serverSize / clientSize;
        int remain = serverSize % clientSize;
        int rankStart = serverByClient * clientRank;

        if (clientRank < remain)
        {
          serverByClient++;
          rankStart += clientRank;
        }
        else
          rankStart += remain;

        for (int i = 0; i < serverByClient; i++)
          rankRecvLeader.push_back(rankStart + i);

        rankRecvNotLeader.resize(0);
      }
      else
      {
        int clientByServer = clientSize / serverSize;
        int remain = clientSize % serverSize;

        if (clientRank < (clientByServer + 1) * remain)
        {
          if (clientRank % (clientByServer + 1) == 0)
            rankRecvLeader.push_back(clientRank / (clientByServer + 1));
          else
            rankRecvNotLeader.push_back(clientRank / (clientByServer + 1));
        }
        else
        {
          int rank = clientRank - (clientByServer + 1) * remain;
          if (rank % clientByServer == 0)
            rankRecvLeader.push_back(remain + rank / clientByServer);
          else
            rankRecvNotLeader.push_back(remain + rank / clientByServer);
        }
      }
    }

    /*!
    In case of attached mode, the current context must be reset to context for client
    \param [in] event Event sent to server
    */
    void CContextClient::sendEvent(CEventClient& event)
    {
      list<int> ranks = event.getRanks();
      info(100)<<"Event "<<timeLine<<" of context "<<context->getId()<<endl ;
      if (CXios::checkEventSync)
      {
        int typeId, classId, typeId_in, classId_in ;
        size_t timeLine_out;
        typeId_in=event.getTypeId() ;
        classId_in=event.getClassId() ;
//        MPI_Allreduce(&timeLine,&timeLine_out, 1, MPI_UINT64_T, MPI_SUM, intraComm) ; // MPI_UINT64_T standardized by MPI 3
        MPI_Allreduce(&timeLine,&timeLine_out, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, intraComm) ; 
        MPI_Allreduce(&typeId_in,&typeId, 1, MPI_INT, MPI_SUM, intraComm) ;
        MPI_Allreduce(&classId_in,&classId, 1, MPI_INT, MPI_SUM, intraComm) ;
        if (typeId/clientSize!=event.getTypeId() || classId/clientSize!=event.getClassId() || timeLine_out/clientSize!=timeLine)
        {
           ERROR("void CContextClient::sendEvent(CEventClient& event)",
               << "Event are not coherent between client.");
        }
      }

      if (!event.isEmpty())
      {
        list<int> sizes = event.getSizes();

        // We force the getBuffers call to be non-blocking on classical servers
        list<CBufferOut*> buffList;
        bool couldBuffer = getBuffers(ranks, sizes, buffList, (!CXios::isClient && (CServer::serverLevel == 0) ));
//        bool couldBuffer = getBuffers(ranks, sizes, buffList, CXios::isServer );

        if (couldBuffer)
        {
          event.send(timeLine, sizes, buffList);
          info(100)<<"Event "<<timeLine<<" of context "<<context->getId()<<"  sent"<<endl ;

          checkBuffers(ranks);

          if (isAttachedModeEnabled()) // couldBuffer is always true in attached mode
          {
            waitEvent(ranks);
            CContext::setCurrent(context->getId());
          }
        }
        else
        {
          tmpBufferedEvent.ranks = ranks;
          tmpBufferedEvent.sizes = sizes;

          for (list<int>::const_iterator it = sizes.begin(); it != sizes.end(); it++)
            tmpBufferedEvent.buffers.push_back(new CBufferOut(*it));
          info(100)<<"DEBUG : temporaly event created : timeline "<<timeLine<<endl ;
          event.send(timeLine, tmpBufferedEvent.sizes, tmpBufferedEvent.buffers);
          info(100)<<"Event "<<timeLine<<" of context "<<context->getId()<<"  sent"<<endl ;
        }
      }

      timeLine++;
    }

    /*!
     * Send the temporarily buffered event (if any).
     *
     * \return true if a temporarily buffered event could be sent, false otherwise 
     */
    bool CContextClient::sendTemporarilyBufferedEvent()
    {
      bool couldSendTmpBufferedEvent = false;

      if (hasTemporarilyBufferedEvent())
      {
        list<CBufferOut*> buffList;
        if (getBuffers(tmpBufferedEvent.ranks, tmpBufferedEvent.sizes, buffList, true)) // Non-blocking call
        {
          list<CBufferOut*>::iterator it, itBuffer;

          for (it = tmpBufferedEvent.buffers.begin(), itBuffer = buffList.begin(); it != tmpBufferedEvent.buffers.end(); it++, itBuffer++)
            (*itBuffer)->put((char*)(*it)->start(), (*it)->count());

          info(100)<<"DEBUG : temporaly event sent "<<endl ;
          checkBuffers(tmpBufferedEvent.ranks);

          tmpBufferedEvent.clear();

          couldSendTmpBufferedEvent = true;
        }
      }

      return couldSendTmpBufferedEvent;
    }

    /*!
    If client is also server (attached mode), after sending event, it should process right away
    the incoming event.
    \param [in] ranks list rank of server connected this client
    */
    void CContextClient::waitEvent(list<int>& ranks)
    {
      parentServer->server->setPendingEvent();
      while (checkBuffers(ranks))
      {
        parentServer->server->listen();
        parentServer->server->checkPendingRequest();
      }

      while (parentServer->server->hasPendingEvent())
      {
       parentServer->server->eventLoop();
      }
    }

    /*!
     * Get buffers for each connection to the servers. This function blocks until there is enough room in the buffers unless
     * it is explicitly requested to be non-blocking.
     *
     * \param [in] serverList list of rank of connected server
     * \param [in] sizeList size of message corresponding to each connection
     * \param [out] retBuffers list of buffers that can be used to store an event
     * \param [in] nonBlocking whether this function should be non-blocking
     * \return whether the already allocated buffers could be used
    */
    bool CContextClient::getBuffers(const list<int>& serverList, const list<int>& sizeList, list<CBufferOut*>& retBuffers,
                                    bool nonBlocking /*= false*/)
    {
      list<int>::const_iterator itServer, itSize;
      list<CClientBuffer*> bufferList;
      map<int,CClientBuffer*>::const_iterator it;
      list<CClientBuffer*>::iterator itBuffer;
      bool areBuffersFree;

      for (itServer = serverList.begin(); itServer != serverList.end(); itServer++)
      {
        it = buffers.find(*itServer);
        if (it == buffers.end())
        {
          newBuffer(*itServer);
          it = buffers.find(*itServer);
        }
        bufferList.push_back(it->second);
      }

      CTimer::get("Blocking time").resume();
      do
      {
        areBuffersFree = true;
        for (itBuffer = bufferList.begin(), itSize = sizeList.begin(); itBuffer != bufferList.end(); itBuffer++, itSize++)
          areBuffersFree &= (*itBuffer)->isBufferFree(*itSize);

        if (!areBuffersFree)
        {
          checkBuffers();
          if (CServer::serverLevel == 0)
            context->server->listen();

          else if (CServer::serverLevel == 1)
          {
            context->server->listen();
            for (int i = 0; i < context->serverPrimServer.size(); ++i)
              context->serverPrimServer[i]->listen();
            CServer::contextEventLoop(false) ; // avoid dead-lock at finalize...
          }

          else if (CServer::serverLevel == 2)
            context->server->listen();

        }
      } while (!areBuffersFree && !nonBlocking);

      CTimer::get("Blocking time").suspend();

      if (areBuffersFree)
      {
        for (itBuffer = bufferList.begin(), itSize = sizeList.begin(); itBuffer != bufferList.end(); itBuffer++, itSize++)
          retBuffers.push_back((*itBuffer)->getBuffer(*itSize));
      }

      return areBuffersFree;
   }

   /*!
   Make a new buffer for a certain connection to server with specific rank
   \param [in] rank rank of connected server
   */
   void CContextClient::newBuffer(int rank)
   {
      if (!mapBufferSize_.count(rank))
      {
        error(0) << "WARNING: Unexpected request for buffer to communicate with server " << rank << std::endl;
        mapBufferSize_[rank] = CXios::minBufferSize;
        maxEventSizes[rank] = CXios::minBufferSize;
      }
      CClientBuffer* buffer = buffers[rank] = new CClientBuffer(interComm, rank, mapBufferSize_[rank], maxEventSizes[rank], maxBufferedEvents);
      // Notify the server
      CBufferOut* bufOut = buffer->getBuffer(sizeof(StdSize));
      bufOut->put(mapBufferSize_[rank]); // Stupid C++
      buffer->checkBuffer();
   }

   /*!
   Verify state of buffers. Buffer is under pending state if there is no message on it
   \return state of buffers, pending(true), ready(false)
   */
   bool CContextClient::checkBuffers(void)
   {
      map<int,CClientBuffer*>::iterator itBuff;
      bool pending = false;
      for (itBuff = buffers.begin(); itBuff != buffers.end(); itBuff++)
        pending |= itBuff->second->checkBuffer();
      return pending;
   }

   //! Release all buffers
   void CContextClient::releaseBuffers()
   {
      map<int,CClientBuffer*>::iterator itBuff;
      for (itBuff = buffers.begin(); itBuff != buffers.end(); itBuff++)
      {
          delete itBuff->second;
      }
      buffers.clear();
   }

   /*!
   Verify state of buffers corresponding to a connection
   \param [in] ranks list rank of server to which client connects to
   \return state of buffers, pending(true), ready(false)
   */
   bool CContextClient::checkBuffers(list<int>& ranks)
   {
      list<int>::iterator it;
      bool pending = false;
      for (it = ranks.begin(); it != ranks.end(); it++) pending |= buffers[*it]->checkBuffer();
      return pending;
   }

   /*!
    * Set the buffer size for each connection. Warning: This function is collective.
    *
    * \param [in] mapSize maps the rank of the connected servers to the size of the correspoinding buffer
    * \param [in] maxEventSize maps the rank of the connected servers to the size of the biggest event
   */
   void CContextClient::setBufferSize(const std::map<int,StdSize>& mapSize, const std::map<int,StdSize>& maxEventSize)
   {
     mapBufferSize_ = mapSize;
     maxEventSizes = maxEventSize;

     // Compute the maximum number of events that can be safely buffered.
     double minBufferSizeEventSizeRatio = std::numeric_limits<double>::max();
     for (std::map<int,StdSize>::const_iterator it = mapSize.begin(), ite = mapSize.end(); it != ite; ++it)
     {
       double ratio = double(it->second) / maxEventSizes[it->first];
       if (ratio < minBufferSizeEventSizeRatio) minBufferSizeEventSizeRatio = ratio;
     }
     MPI_Allreduce(MPI_IN_PLACE, &minBufferSizeEventSizeRatio, 1, MPI_DOUBLE, MPI_MIN, intraComm);

     if (minBufferSizeEventSizeRatio < 1.0)
     {
       ERROR("void CContextClient::setBufferSize(const std::map<int,StdSize>& mapSize, const std::map<int,StdSize>& maxEventSize)",
             << "The buffer sizes and the maximum events sizes are incoherent.");
     }
     else if (minBufferSizeEventSizeRatio == std::numeric_limits<double>::max())
       minBufferSizeEventSizeRatio = 1.0; // In this case, maxBufferedEvents will never be used but we want to avoid any floating point exception

     maxBufferedEvents = size_t(2 * minBufferSizeEventSizeRatio) // there is room for two local buffers on the server
                          + size_t(minBufferSizeEventSizeRatio)  // one local buffer can always be fully used
                          + 1;                                   // the other local buffer might contain only one event
   }

  /*!
  Get leading server in the group of connected server
  \return ranks of leading servers
  */
  const std::list<int>& CContextClient::getRanksServerNotLeader(void) const
  {
    return ranksServerNotLeader;
  }

  /*!
  Check if client connects to leading server
  \return connected(true), not connected (false)
  */
  bool CContextClient::isServerNotLeader(void) const
  {
    return !ranksServerNotLeader.empty();
  }

  /*!
  Get leading server in the group of connected server
  \return ranks of leading servers
  */
  const std::list<int>& CContextClient::getRanksServerLeader(void) const
  {
    return ranksServerLeader;
  }

  /*!
  Check if client connects to leading server
  \return connected(true), not connected (false)
  */
  bool CContextClient::isServerLeader(void) const
  {
    return !ranksServerLeader.empty();
  }

  /*!
   * Check if the attached mode is used.
   *
   * \return true if and only if attached mode is used
   */
  bool CContextClient::isAttachedModeEnabled() const
  {
    return (parentServer != 0);
  }

   /*!
   * Finalize context client and do some reports. Function is non-blocking.
   */
  void CContextClient::finalize(void)
  {
    map<int,CClientBuffer*>::iterator itBuff;
    bool stop = false;

    CTimer::get("Blocking time").resume();
    while (hasTemporarilyBufferedEvent())
    {
      checkBuffers();
      sendTemporarilyBufferedEvent();
    }
    CTimer::get("Blocking time").suspend();

    CEventClient event(CContext::GetType(), CContext::EVENT_ID_CONTEXT_FINALIZE);
    if (isServerLeader())
    {
      CMessage msg;
      const std::list<int>& ranks = getRanksServerLeader();
      for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
      {
        info(100)<<"DEBUG : Sent context Finalize event to rank "<<*itRank<<endl ;
        event.push(*itRank, 1, msg);
      }
      sendEvent(event);
    }
    else sendEvent(event);

    CTimer::get("Blocking time").resume();
//    while (!stop)
    {
      checkBuffers();
      if (hasTemporarilyBufferedEvent())
        sendTemporarilyBufferedEvent();

      stop = true;
//      for (itBuff = buffers.begin(); itBuff != buffers.end(); itBuff++) stop &= !itBuff->second->hasPendingRequest();
    }
    CTimer::get("Blocking time").suspend();

    std::map<int,StdSize>::const_iterator itbMap = mapBufferSize_.begin(),
                                          iteMap = mapBufferSize_.end(), itMap;

    StdSize totalBuf = 0;
    for (itMap = itbMap; itMap != iteMap; ++itMap)
    {
      report(10) << " Memory report : Context <" << context->getId() << "> : client side : memory used for buffer of each connection to server" << endl
                 << "  +) To server with rank " << itMap->first << " : " << itMap->second << " bytes " << endl;
      totalBuf += itMap->second;
    }
    report(0) << " Memory report : Context <" << context->getId() << "> : client side : total memory used for buffer " << totalBuf << " bytes" << endl;

    //releaseBuffers(); // moved to CContext::finalize()
  }


  /*!
  */
  bool CContextClient::havePendingRequests(void)
  {
    bool pending = false;
    map<int,CClientBuffer*>::iterator itBuff;
    for (itBuff = buffers.begin(); itBuff != buffers.end(); itBuff++)
      pending |= itBuff->second->hasPendingRequest();
    return pending;
  }


}
