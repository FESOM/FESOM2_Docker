#include "xios_spl.hpp"
#include "event_client.hpp"
#include "buffer_out.hpp"
#include "message.hpp"
#include "type.hpp"
#include "mpi.hpp"
#include "cxios.hpp"

namespace xios
{
   const size_t CEventClient::headerSize = sizeof(int) + sizeof(size_t) + sizeof(int) + sizeof(int) + sizeof(int); // The two last one signify sizeof(classId) and sizeof(typeId)


   CEventClient::CEventClient(int classId_, int typeId_)
   {
     classId = classId_;
     typeId = typeId_;
   }

   void CEventClient::push(int rank, int nbSender, CMessage& msg)
   {
     nbSenders.push_back(nbSender);
     ranks.push_back(rank);
     messages.push_back(&msg);
   }

   bool CEventClient::isEmpty(void)
   {
     return ranks.empty();
   }

   std::list<int> CEventClient::getRanks(void)
   {
     return ranks;
   }

   std::list<int> CEventClient::getSizes(void)
   {
     std::list<CMessage*>::iterator it;
     std::list<int> sizes;

     for (it = messages.begin(); it != messages.end(); ++it) sizes.push_back((*it)->size() + headerSize);
     return sizes;
   }

   void CEventClient::send(size_t timeLine, const std::list<int>& sizes, std::list<CBufferOut*>& buffers)
   {
     std::list<CBufferOut*>::iterator itBuff = buffers.begin();
     std::list<int>::const_iterator itSizes = sizes.begin(), itSenders = nbSenders.begin();
     std::list<CMessage*>::iterator itMsg = messages.begin();

     if (CXios::checkEventSync) info(100)<<"Send event "<<timeLine<<" classId : "<<classId<<"  typeId : "<<typeId<<endl ;
     for (; itBuff != buffers.end(); ++itBuff, ++itSizes, ++itSenders, ++itMsg)
     {
       **itBuff << *itSizes << timeLine << *itSenders << classId << typeId << **itMsg;
     }
   }
}
