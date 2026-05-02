#ifndef __CONTEXT_CLIENT_HPP__
#define __CONTEXT_CLIENT_HPP__

#include "xios_spl.hpp"
#include "buffer_out.hpp"
#include "buffer_in.hpp"
#include "buffer_client.hpp"
#include "event_client.hpp"
#include "event_server.hpp"
#include "mpi.hpp"
#include "registry.hpp"

namespace xios
{
  class CContext;

  /*!
  \class CContextClient
  A context can be both on client and on server side. In order to differenciate the role of
  context on each side, e.x client sending events, server receiving and processing events, there is a need of
  concrete "context" classes for both sides.
  CContextClient processes and sends events from client to server where CContextServer receives these events
  and processes them.
  */
  class CContextClient
  {
    public:
      // Contructor
      CContextClient(CContext* parent, MPI_Comm intraComm, MPI_Comm interComm, CContext* parentServer = 0);

      // Send event to server
      void sendEvent(CEventClient& event);
      bool sendTemporarilyBufferedEvent();
      void waitEvent(list<int>& ranks);

      // Functions to set/get buffers
      bool getBuffers(const list<int>& serverList, const list<int>& sizeList, list<CBufferOut*>& retBuffers, bool nonBlocking = false);
      void newBuffer(int rank);
      bool checkBuffers(list<int>& ranks);
      bool checkBuffers(void);
      void releaseBuffers(void);
      bool havePendingRequests(void);

      bool isServerLeader(void) const;
      bool isServerNotLeader(void) const;
      const std::list<int>& getRanksServerLeader(void) const;
      const std::list<int>& getRanksServerNotLeader(void) const;

      bool isAttachedModeEnabled() const;
      bool hasTemporarilyBufferedEvent() const { return !tmpBufferedEvent.isEmpty(); };

      static void computeLeader(int clientRank, int clientSize, int serverSize,
                                std::list<int>& rankRecvLeader,
                                std::list<int>& rankRecvNotLeader);

      // Close and finalize context client
//      void closeContext(void);  Never been implemented.
      void finalize(void);

      void setBufferSize(const std::map<int,StdSize>& mapSize, const std::map<int,StdSize>& maxEventSize);

    public:
      CContext* context; //!< Context for client

      size_t timeLine; //!< Timeline of each event

      int clientRank; //!< Rank of current client

      int clientSize; //!< Size of client group

      int serverSize; //!< Size of server group

      MPI_Comm interComm; //!< Communicator of server group

      MPI_Comm intraComm; //!< Communicator of client group

      map<int,CClientBuffer*> buffers; //!< Buffers for connection to servers

    private:
      //! Mapping of server and buffer size for each connection to server
      std::map<int,StdSize> mapBufferSize_;
      //! Maximum event sizes estimated for each connection to server
      std::map<int,StdSize> maxEventSizes;
      //! Maximum number of events that can be buffered
      StdSize maxBufferedEvents;

      struct {
        std::list<int> ranks, sizes;
        std::list<CBufferOut*> buffers;

        bool isEmpty() const { return ranks.empty(); };
        void clear() {
          ranks.clear();
          sizes.clear();

          for (std::list<CBufferOut*>::iterator it = buffers.begin(); it != buffers.end(); it++)
            delete *it;

          buffers.clear();
        };
      } tmpBufferedEvent; //! Event temporarily buffered (used only on the server)

      //! Context for server (Only used in attached mode)
      CContext* parentServer;

      //! List of server ranks for which the client is leader
      std::list<int> ranksServerLeader;

      //! List of server ranks for which the client is not leader
      std::list<int> ranksServerNotLeader;

  };
}

#endif // __CONTEXT_CLIENT_HPP__
