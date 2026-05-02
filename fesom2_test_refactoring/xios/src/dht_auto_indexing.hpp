/*!
   \file dht_auto_indexing.hpp
   \author Ha NGUYEN
   \since 6 Jul 2016
   \date 6 Jul 2016

   \brief Auto assign global index across processes.
 */

#ifndef __XIOS_DHT_AUTO_INDEXING_HPP__
#define __XIOS_DHT_AUTO_INDEXING_HPP__

#include "client_client_dht_template.hpp"

namespace xios
{

/*!
  \class CDHTAutoIndexing
  .
*/
class CDHTAutoIndexing: public CClientClientDHTTemplate<size_t>
{
  public:

    CDHTAutoIndexing(const CArray<size_t,1>& hashValue,
                     const MPI_Comm& clientIntraComm);

    CDHTAutoIndexing(Index2VectorInfoTypeMap& hashInitMap,
                     const MPI_Comm& clientIntraComm);

    size_t getNbIndexesGlobal() const;
    size_t getIndexStart() const;
    size_t getIndexCount() const;

    /** Default destructor */
    virtual ~CDHTAutoIndexing();

  protected:
    std::vector<size_t> globalIndex_;
    size_t nbIndexesGlobal_;
    size_t nbIndexOnProc_ ;
    size_t beginIndexOnProc_ ;
};

} // namespace xios
#endif // __XIOS_DHT_AUTO_INDEXING_HPP__
