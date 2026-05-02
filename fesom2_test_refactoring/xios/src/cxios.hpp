#ifndef __XIOS_HPP__
#define __XIOS_HPP__

#include "xios_spl.hpp"
#include "mpi.hpp"
#include "registry.hpp"

namespace xios
{
  /*!
  \class CXios
  */
  class CXios
  {
    public:
     static void initialize(void) ;
     static void initClientSide(const string & codeId, MPI_Comm& localComm, MPI_Comm& returnComm) ;
     static void initServerSide(void) ;
     static void clientFinalize(void) ;
     static void parseFile(const string& filename) ;

     template <typename T>
     static T getin(const string& id,const T& defaultValue) ;

     template <typename T>
     static T getin(const string& id) ;

    public:
     static string rootFile ; //!< Configuration filename
     static string xiosCodeId ; //!< Identity for XIOS
     static string clientFile;        //!< Filename template for client
     static string serverFile;        //!< Filename template for server
     static string serverPrmFile;  //!< Filename template for primary server in case of two server levels
     static string serverSndFile;  //!< Filename template for secondary server in case of two server levels

     static bool xiosStack;    //!< Exception handling
     static bool systemStack;  //!< Exception handling

     static bool isClient ; //!< Check if xios is client
     static bool isServer ; //!< Check if xios is server

     static MPI_Comm globalComm ; //!< Global communicator

     static bool printLogs2Files; //!< Printing out logs into files
     static bool usingOasis ;     //!< Using Oasis
     static bool usingServer ;    //!< Using server (server mode)
     static bool usingServer2 ;   //!< Using secondary server (server mode). IMPORTANT: Use this variable ONLY in CServer::initialize().
     static int ratioServer2 ;    //!< Percentage of server processors dedicated to secondary server
     static int nbPoolsServer2 ;  //!< Number of pools created on the secondary server
     static double bufferSizeFactor; //!< Factor used to tune the buffer size
     static const double defaultBufferSizeFactor; //!< Default factor value
     static StdSize minBufferSize; //!< Minimum buffer size
     static StdSize maxBufferSize; //!< Maximum buffer size
     static bool isOptPerformance; //!< Check if buffer size is for performance (as large as possible)
     static CRegistry* globalRegistry ; //!< global registry which is wrote by the root process of the servers
     static double recvFieldTimeout; //!< Time to wait for data before issuing an error when receiving a field
     static bool checkEventSync; //!< For debuuging, check if event are coherent and synchrone on client side

    public:
     //! Setting xios to use server mode
     static void setUsingServer();

     //! Setting xios NOT to use server mode
     static void setNotUsingServer();

     //! Initialize server (if any)
     static  void initServer();

    private:
      //! Parse only Xios part of configuration file
      static void parseXiosConfig();
  } ;
}

//#include "cxios_impl.hpp"
#endif // __XIOS_HPP__
