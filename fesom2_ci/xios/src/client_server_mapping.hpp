/*!
   \file client_server_mapping.hpp
   \author Ha NGUYEN
   \since 04 Feb 2015
   \date 09 Mars 2015

   \brief Mapping between index client and server.
 */
#ifndef __XIOS_CLIENT_SERVER_MAPPING_HPP__
#define __XIOS_CLIENT_SERVER_MAPPING_HPP__

#include "xios_spl.hpp"
#include "array_new.hpp"
#include "mpi.hpp"
#include <unordered_map>

namespace xios {

/*!
  \class CClientServerMapping
  This class computes index of data which are sent to server as well as index of data
on server side.
*/
class CClientServerMapping
{
public:
  typedef std::unordered_map<int, std::vector<size_t> > GlobalIndexMap;
  public:
    /** Default constructor */
    CClientServerMapping();

    /** Default destructor */
    virtual ~CClientServerMapping();

    // Only need global index on client to calculate mapping (supposed client has info of distribution)
    virtual void computeServerIndexMapping(const CArray<size_t,1>& globalIndexOnClient, int nbServer) = 0;

    static std::map<int,int> computeConnectedClients(int nbServer, int nbClient,
                                                     MPI_Comm& clientIntraComm,
                                                     const std::vector<int>& connectedServerRank);

    const GlobalIndexMap& getGlobalIndexOnServer() const;

    GlobalIndexMap& getGlobalIndexOnServer();

  protected:
    //! Global index of data on SERVER, which are calculated by client(s)
    GlobalIndexMap indexGlobalOnServer_;
};

} // namespace xios
#endif // __XIOS_CLIENT_SERVER_MAPPING_HPP__
