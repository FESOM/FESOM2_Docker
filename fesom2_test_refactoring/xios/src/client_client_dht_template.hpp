/*!
   \file client_client_dht_template.hpp
   \author Ha NGUYEN
   \since 01 Oct 2015
   \date 15 April 2016

   \brief Distributed hashed table implementation.
 */

#ifndef __XIOS_CLIENT_CLIENT_DHT_TEMPLATE_HPP__
#define __XIOS_CLIENT_CLIENT_DHT_TEMPLATE_HPP__

#include "xios_spl.hpp"
#include "array_new.hpp"
#include "mpi.hpp"
#include "policy.hpp"
#include  <unordered_map>
#include "dht_data_types.hpp"

namespace xios
{
template<typename T, class HierarchyPolicy = DivideAdaptiveComm> class CClientClientDHTTemplate;

/*!
  \class CClientClientDHTTemplate
  This class provides the similar features like \class CClientServerMappingDistributed,
which implements a simple distributed hashed table; Moreover, by extending with hierarchical structure,
it allows to reduce greatly the number of communication among processes.
*/
template<typename T, typename HierarchyPolicy>
class CClientClientDHTTemplate: public HierarchyPolicy
{
  public:
    typedef T InfoType;
    static const int infoTypeSize = sizeof(InfoType);
//    typedef typename std::unordered_map<InfoType, std::vector<size_t> > InfoType2IndexMap;
    typedef typename std::unordered_map<size_t,InfoType> Index2InfoTypeMap;
    typedef typename std::unordered_map<size_t,std::vector<InfoType> > Index2VectorInfoTypeMap;

  public:
    CClientClientDHTTemplate(const Index2InfoTypeMap& indexInfoInitMap,
                             const MPI_Comm& clientIntraComm);

    CClientClientDHTTemplate(const Index2VectorInfoTypeMap& indexInfoInitMap,
                             const MPI_Comm& clientIntraComm);

    void computeIndexInfoMapping(const CArray<size_t,1>& indices);

    const Index2VectorInfoTypeMap& getInfoIndexMap() const {return indexToInfoMappingLevel_; }
    Index2VectorInfoTypeMap& getInfoIndexMap() {return indexToInfoMappingLevel_; }
    int getNbClient() { return nbClient_; }

    /** Default destructor */
    virtual ~CClientClientDHTTemplate();

  protected:
    CClientClientDHTTemplate(const MPI_Comm& clientIntraComm);

  protected:


    // Redistribute index and info among clients
    void computeDistributedIndex(const Index2InfoTypeMap& indexInfoInitMap,
                                 const MPI_Comm& intraCommLevel,
                                 int level);

    void computeDistributedIndex(const Index2VectorInfoTypeMap& indexInfoInitMap,
                                 const MPI_Comm& intraCommLevel,
                                 int level);


    void computeHashIndex(std::vector<size_t>& indexClientHash, int nbClient);

    void computeIndexInfoMappingLevel(const CArray<size_t,1>& indices,
                                      const MPI_Comm& intraCommLevel,
                                      int level);

    void computeSendRecvRank(int level, int rank);

    void sendRecvRank(int level,
                      const std::vector<int>& sendNbRank, const std::vector<int>& sendNbElements,
                      std::vector<int>& recvNbRank, std::vector<int>& recvNbElements);

  protected:
    // Send information to clients
    void sendInfoToClients(int clientDestRank, unsigned char* info, int infoSize,
                           const MPI_Comm& clientIntraComm,
                           std::vector<MPI_Request>& requestSendInfo);

    void recvInfoFromClients(int clientSrcRank, unsigned char* info, int infoSize,
                            const MPI_Comm& clientIntraComm,
                            std::vector<MPI_Request>& requestRecvInfo);

    // Send global index to clients
    void sendIndexToClients(int clientDestRank, size_t* indices, size_t indiceSize,
                            const MPI_Comm& clientIntraComm,
                            std::vector<MPI_Request>& requestSendIndexGlobal);

    void recvIndexFromClients(int clientSrcRank, size_t* indices, size_t indiceSize,
                             const MPI_Comm& clientIntraComm,
                             std::vector<MPI_Request>& requestRecvIndex);

    void sendRecvOnReturn(const std::vector<int>& sendNbRank, std::vector<int>& sendNbElements,
                          const std::vector<int>& recvNbRank, std::vector<int>& recvNbElements);

  protected:
    //! Mapping of global index to the corresponding client
    Index2VectorInfoTypeMap index2InfoMapping_;

    //! A mapping of index to the corresponding information in each level of hierarchy
    Index2VectorInfoTypeMap indexToInfoMappingLevel_;

    //! Rank of client to send on each DHT level
    std::vector<std::vector<int> > sendRank_;

    //! Rank of client to receive on each DHT level
    std::vector<std::vector<int> > recvRank_;

    //! Flag to specify whether data is distributed or not
    bool isDataDistributed_;

    //! Number of client
    int nbClient_;
};

typedef CClientClientDHTTemplate<int> CClientClientDHTInt;
typedef CClientClientDHTTemplate<size_t> CClientClientDHTSizet;
typedef CClientClientDHTTemplate<double> CClientClientDHTDouble;
typedef CClientClientDHTTemplate<PairIntInt> CClientClientDHTPairIntInt;

} // namespace xios
#endif // __XIOS_CLIENT_CLIENT_DHT_TEMPLATE_HPP__
