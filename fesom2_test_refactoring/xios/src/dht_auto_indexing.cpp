/*!
   \file dht_auto_indexing.cpp
   \author Ha NGUYEN
   \since 6 Jul 2016
   \date 6 Jul 2016

   \brief Auto assign global index across processes.
 */
#include "dht_auto_indexing.hpp"

namespace xios
{

  CDHTAutoIndexing::~CDHTAutoIndexing()
  {
  }

  /*!
    \param [in]
    \param [in]
  */

  CDHTAutoIndexing::CDHTAutoIndexing(const CArray<size_t,1>& hashValue,
                                     const MPI_Comm& clientIntraComm)
    : CClientClientDHTTemplate<size_t>(clientIntraComm)
  {

    nbIndexOnProc_ = hashValue.size();
    size_t nbIndexAccum;
    MPI_Scan(&nbIndexOnProc_, &nbIndexAccum, 1, MPI_UNSIGNED_LONG, MPI_SUM, clientIntraComm);

    // Broadcasting the total number of indexes
    int rank, size;
    MPI_Comm_rank(clientIntraComm, &rank);
    MPI_Comm_size(clientIntraComm, &size);
    if (rank == (size-1)) nbIndexesGlobal_ = nbIndexAccum;
    MPI_Bcast(&nbIndexesGlobal_, 1, MPI_UNSIGNED_LONG, size-1, clientIntraComm);

    CArray<size_t,1>::const_iterator itbIdx = hashValue.begin(), itIdx,
                                     iteIdx = hashValue.end();

    size_t idx = 0;
    beginIndexOnProc_ = nbIndexAccum - nbIndexOnProc_;
    globalIndex_.resize(nbIndexOnProc_);
    for (itIdx = itbIdx; itIdx != iteIdx; ++itIdx)
    {
      globalIndex_[idx] = beginIndexOnProc_ + idx;
      ++idx ;
    }
  }

  /*!
   * \fn void CDHTAutoIndexing::CDHTAutoIndexing(Index2VectorInfoTypeMap& hashInitMap, const MPI_Comm& clientIntraComm)
   * Assigns a global index to unique input indexes.
   * The returned map has unique indexes as a key and global indexes as a mapped value.
   * \param [in] hashInitMap map<size_t, vector<size_t>> is a map of unique indexes.
   * \param [in] clientIntraComm
  */
  CDHTAutoIndexing::CDHTAutoIndexing(Index2VectorInfoTypeMap& hashInitMap,
                                     const MPI_Comm& clientIntraComm)
    : CClientClientDHTTemplate<size_t>(clientIntraComm)
  {

    nbIndexOnProc_ = hashInitMap.size();
    size_t nbIndexAccum;
    MPI_Scan(&nbIndexOnProc_, &nbIndexAccum, 1, MPI_UNSIGNED_LONG, MPI_SUM, clientIntraComm);

    int rank, size;
    MPI_Comm_rank(clientIntraComm, &rank);
    MPI_Comm_size(clientIntraComm, &size);
    if (rank == (size-1)) nbIndexesGlobal_ = nbIndexAccum;
    MPI_Bcast(&nbIndexesGlobal_, 1, MPI_UNSIGNED_LONG, size-1, clientIntraComm);

    Index2VectorInfoTypeMap::iterator itbIdx = hashInitMap.begin(), itIdx,
                                      iteIdx = hashInitMap.end();
    size_t idx = 0;
    beginIndexOnProc_ = nbIndexAccum - nbIndexOnProc_;
    globalIndex_.resize(nbIndexOnProc_);
    for (itIdx = itbIdx; itIdx != iteIdx; ++itIdx)
    {
//      (itIdx->second)[0] = beginIndexOnProc_ + idx;
      (itIdx->second)[1] = beginIndexOnProc_ + idx;
      globalIndex_[idx] = beginIndexOnProc_ + idx;
      ++idx ;
    }
  }

  /*!
   * \fn size_t CDHTAutoIndexing::getNbIndexesGlobal() const
   * Returns the total number of global indexes.
  */
  size_t CDHTAutoIndexing::getNbIndexesGlobal() const
  {
    return nbIndexesGlobal_;
  }

  /*!
   * \fn size_t CDHTAutoIndexing::getIndexStart() const
   * Returns the starting global index for a proc.
  */
  size_t CDHTAutoIndexing::getIndexStart() const
  {
    return beginIndexOnProc_;
  }

  /*!
   * \fn size_t CDHTAutoIndexing::getIndexCount() const
   * Returns the number of global indexes on a proc.
  */
  size_t CDHTAutoIndexing::getIndexCount() const
  {
    return nbIndexOnProc_;
  }

}
