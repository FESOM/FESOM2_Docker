/*!
   \file client_server_mapping.hpp
   \author Ha NGUYEN
   \since 04 Feb 2015
   \date 09 Mars 2015

   \brief Mapping between index client and server.
 */
#include "client_server_mapping.hpp"

namespace xios {

CClientServerMapping::CClientServerMapping()
  : indexGlobalOnServer_()
{
}

CClientServerMapping::~CClientServerMapping()
{
}

/*!
  Compute how many clients each server will receive data from
  On client can send data to several servers as well as one server can receive data originated from
some clients. In order to write data correctly, each server must know from how many clients it receives data
  \param [in] nbServer number of servers
  \param [in] nClient number of clients
  \param [in] clientIntraComm MPI communication of clients
  \param [in] connectedServerRank Rank of servers connected to one client
*/
std::map<int,int> CClientServerMapping::computeConnectedClients(int nbServer, int nbClient,
                                                                MPI_Comm& clientIntraComm,
                                                                const std::vector<int>& connectedServerRank)
{
  std::map<int, int> connectedClients; // number of clients connected to a server

  std::vector<int>::const_iterator itbVec, iteVec, it;
  itbVec = it = connectedServerRank.begin();
  iteVec = connectedServerRank.end();

  std::vector<int> connectedServer;
  std::vector<bool> isConnected(nbServer,false);

  for (it = itbVec; it != iteVec; ++it)
  {
    for (int serverNum = 0; serverNum < nbServer; ++serverNum)
      if (*it == serverNum) isConnected[serverNum] = true;
  }

  for(int serverNum = 0; serverNum<nbServer; ++serverNum)
    if (isConnected[serverNum])
      connectedServer.push_back(serverNum);


  int nbConnectedServer=connectedServer.size();
  int* recvCount=new int[nbClient];
  int* displ=new int[nbClient];
  int* sendBuff=new int[nbConnectedServer];
  valarray<int> clientRes(0,nbServer);

  for(int n=0;n<nbConnectedServer;n++) sendBuff[n]=connectedServer[n] ;

  // get connected server for everybody
  MPI_Allgather(&nbConnectedServer,1,MPI_INT,recvCount,1,MPI_INT,clientIntraComm) ;

  displ[0]=0 ;
  for(int n=1;n<nbClient;n++) displ[n]=displ[n-1]+recvCount[n-1] ;
  int recvSize=displ[nbClient-1]+recvCount[nbClient-1] ;
  int* recvBuff=new int[recvSize] ;


  MPI_Allgatherv(sendBuff,nbConnectedServer,MPI_INT,recvBuff,recvCount,displ,MPI_INT,clientIntraComm) ;
  for(int n=0;n<recvSize;n++) clientRes[recvBuff[n]]++ ;

  for(int n=0;n<nbConnectedServer;n++)
  {
    connectedClients[connectedServer[n]] = clientRes[connectedServer[n]];
  }

  delete [] recvCount ;
  delete [] displ ;
  delete [] sendBuff ;
  delete [] recvBuff ;

  return connectedClients;
}

/*!
  Return global index of data on each connected server.
  On receiving data sent from client(s), each server with this global index, is able to
know where the data should be written.
  \return mapping of server rank and its global index.
*/
const CClientServerMapping::GlobalIndexMap& CClientServerMapping::getGlobalIndexOnServer() const
{
  return indexGlobalOnServer_;
}

CClientServerMapping::GlobalIndexMap& CClientServerMapping::getGlobalIndexOnServer()
{
  return indexGlobalOnServer_;
}

} //namespace xios
