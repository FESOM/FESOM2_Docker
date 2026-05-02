#ifndef __BUFFER_CLIENT_HPP__
#define __BUFFER_CLIENT_HPP__

#include "xios_spl.hpp"
#include "buffer_out.hpp"
#include "mpi.hpp"
#include "cxios.hpp"

namespace xios
{
  class CClientBuffer
  {
    public:
      static size_t maxRequestSize;

      CClientBuffer(MPI_Comm intercomm, int serverRank, StdSize bufferSize, StdSize estimatedMaxEventSize, StdSize maxBufferedEvents);
      ~CClientBuffer();

      bool isBufferFree(StdSize size);
      CBufferOut* getBuffer(StdSize size);
      bool checkBuffer(void);
      bool hasPendingRequest(void);
      StdSize remain(void);

    private:
      char* buffer[2];

      int current;

      StdSize count;
      StdSize bufferedEvents;
      StdSize maxEventSize;
      const StdSize maxBufferedEvents;
      const StdSize bufferSize;
      const StdSize estimatedMaxEventSize;


      const int serverRank;
      bool pending;

      MPI_Request request;

      CBufferOut* retBuffer;
      const MPI_Comm interComm;
  };
}
#endif
