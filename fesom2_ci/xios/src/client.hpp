#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "xios_spl.hpp"
#include "mpi.hpp"

namespace xios
{
    class CClient
    {
      public:
        static void initialize(const string& codeId, MPI_Comm& localComm, MPI_Comm& returnComm);
        static void finalize(void);
        static void registerContext(const string& id, MPI_Comm contextComm);
        static void callOasisEnddef(void) ;

        static MPI_Comm intraComm;
        static MPI_Comm interComm;
        static std::list<MPI_Comm> contextInterComms;
        static int serverLeader;
        static bool is_MPI_Initialized ;

        static MPI_Comm& getInterComm();

        //! Get global rank without oasis and current rank in model intraComm in case of oasis
        static int getRank();

        //! Open a file stream to write the info logs
        static void openInfoStream(const StdString& fileName);
        //! Write the info logs to standard output
        static void openInfoStream();
        //! Close the info logs file if it opens
        static void closeInfoStream();

        //! Open a file stream to write the error log
        static void openErrorStream(const StdString& fileName);
        //! Write the error log to standard error output
        static void openErrorStream();
        //! Close the error log file if it opens
        static void closeErrorStream();

      protected:
        static int rank_;                 //!< Rank in model intraComm
        static StdOFStream m_infoStream;
        static StdOFStream m_errorStream;

        static void openStream(const StdString& fileName, const StdString& ext, std::filebuf* fb);
    };
}

#endif
