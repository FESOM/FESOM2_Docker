#ifndef __EVENT_CLIENT_HPP__
#define __EVENT_CLIENT_HPP__

#include "xios_spl.hpp"
#include "buffer_out.hpp"
#include "message.hpp"

namespace xios
{
  class CEventClient
  {
    public:
      static const size_t headerSize;

      CEventClient(int classId, int typeId);

      void push(int rank, int nbSender, CMessage& msg);
      void send(size_t timeLine, const std::list<int>& sizes, std::list<CBufferOut*>&); 

      bool isEmpty(void);
      std::list<int> getRanks(void);
      std::list<int> getSizes(void);
      int getClassId(void) { return classId; }
      int getTypeId(void) { return typeId; }
      
    private:
      int classId;
      int typeId;
      std::list<int> ranks;
      std::list<int> nbSenders;
      std::list<CMessage*> messages;
  };
}

#endif
