/*!
   \file client_server_mapping.hpp
   \author Ha NGUYEN
   \since 27 Feb 2015
   \date 09 Mars 2015

   \brief Mapping between index client and server.
   Clients pre-calculate all information of server distribution.
 */

#ifndef __XIOS_CLIENT_SERVER_MAPPING_DISTRIBUTED_HPP__
#define __XIOS_CLIENT_SERVER_MAPPING_DISTRIBUTED_HPP__

#include <client_server_mapping.hpp>
#include "xios_spl.hpp"
#include "array_new.hpp"
#include "mpi.hpp"
#include <unordered_map>
#include "client_client_dht_template.hpp"

namespace xios
{
/*!
  \class CClientServerMappingDistributed
  This class computes index of data which are sent to server as well as index of data
on server side with a distributed alogrithm. Each client has a piece of information about the distribution
of servers. To find out all these info, first of all, all client join a discovering process in which each client
announces the others about the info they have as well as demand others info they are lacked of. After this process,
each client has enough info to decide to which client it need to send a demand for corresponding server of a global index.
The alogrithm depends on hashed index.
*/
class CClientServerMappingDistributed : public CClientServerMapping
{
  public:
    /** Default constructor */
    CClientServerMappingDistributed(const std::unordered_map<size_t,int>& globalIndexOfServer,
                                    const MPI_Comm& clientIntraComm,
                                    bool isDataDistributed = true);

    virtual void computeServerIndexMapping(const CArray<size_t,1>& globalIndexOnClientSendToServer, int nbServer);

    /** Default destructor */
    virtual ~CClientServerMappingDistributed();

  protected:
    CClientClientDHTInt* ccDHT_;
};

} // namespace xios
#endif // __XIOS_CLIENT_SERVER_MAPPING_DISTRIBUTED_HPP__
