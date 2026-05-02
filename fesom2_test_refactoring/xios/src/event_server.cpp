#include "xios_spl.hpp"
#include "buffer_in.hpp"
#include "type.hpp"
#include "event_server.hpp"
#include "buffer_server.hpp"

namespace xios
{
  void CEventServer::push(int rank, CServerBuffer* serverBuffer, char* startBuffer, int size)
  {
    CBufferIn buffer(startBuffer, size);
    size_t timeLine;
    int myClassId, myType, myNbSender;
  
    buffer >> size >> timeLine >> myNbSender >> myClassId >> myType;
  
    if (subEvents.empty())
    {  
      nbSender = myNbSender;
      classId = myClassId;
      type = myType;
    }
    else
    {
      if (classId != myClassId || type != myType || nbSender != myNbSender)
        ERROR("void CEventServer::push(int rank, CServerBuffer* serverBuffer, char* startBuffer, int size)",
              << "The callers of event " << timeLine << " are not coherent." << std::endl
              << "Received subevent: classId = " << myClassId << ", type = " << myType << ", nbSender = " << myNbSender << std::endl
              << "Expected subevent: classId = " << classId << ", type = " << type << ", nbSender = " << nbSender);
    }

    SSubEvent ev;
    ev.rank = rank;
    ev.serverBuffer = serverBuffer;
    ev.buffer = new CBufferIn(buffer.ptr(), buffer.remain());
    ev.size = size;  
    subEvents.push_back(ev);
  
    if (subEvents.size() > nbSender)
    {
        ERROR("void CEventServer::push(int rank, CServerBuffer* serverBuffer, char* startBuffer, int size)",
              << "The callers of event " << timeLine << " are not coherent." << std::endl
              << "Too many subevents have been received (" << subEvents.size() << " instead of " << nbSender << ").");
    }
  }

  bool CEventServer::isFull(void)  
  {
    return (nbSender == subEvents.size());
  }

  CEventServer::~CEventServer()
  {
    list<SSubEvent>::iterator it;
    for (it = subEvents.begin(); it != subEvents.end(); it++)
    {
      it->serverBuffer->freeBuffer(it->size);
      delete it->buffer;
    }
  }
}
