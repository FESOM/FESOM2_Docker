/*!
   \file domain_algorithm_transformation.hpp
   \author Ha NGUYEN
   \since 02 Jul 2015
   \date 02 Jul 2015

   \brief Interface for all domain transformation algorithms.
 */

#include "domain_algorithm_transformation.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "domain.hpp"

namespace xios {

CDomainAlgorithmTransformation::CDomainAlgorithmTransformation(CDomain* domainDestination, CDomain* domainSource)
 : CGenericAlgorithmTransformation(), domainDest_(domainDestination), domainSrc_(domainSource)
{
}

CDomainAlgorithmTransformation::~CDomainAlgorithmTransformation()
{
}

void CDomainAlgorithmTransformation::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
}

/*!
  Compute global index of domain on different processes
  \param [in] globalDomainIndex global index of domain source
  \param [out] globalDomainIndexOnProc processes which contain the corresponding global index of domain source
*/
void CDomainAlgorithmTransformation::computeExchangeGlobalIndex(const CArray<size_t,1>& globalDomainIndex,
                                                                int elementType,
                                                                CClientClientDHTInt::Index2VectorInfoTypeMap& globalDomainIndexOnProc)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int clientSize = client->clientSize;

  int niGlob = domainSrc_->ni_glo.getValue();
  int njGlob = domainSrc_->nj_glo.getValue();
  size_t globalIndex;
  int nIndexSize = domainSrc_->i_index.numElements(), i_ind, j_ind;
  CClientClientDHTInt::Index2VectorInfoTypeMap globalIndex2ProcRank;
  globalIndex2ProcRank.rehash(std::ceil(nIndexSize/globalIndex2ProcRank.max_load_factor()));
  CArray<bool,1>& localMask=domainSrc_->localMask ;
  for (int idx = 0; idx < nIndexSize; ++idx)
  {
    if (localMask(idx))
    {
      i_ind=domainSrc_->i_index(idx) ;
      j_ind=domainSrc_->j_index(idx) ;

      globalIndex = i_ind + j_ind * niGlob;
      globalIndex2ProcRank[globalIndex].push_back(clientRank);
    }
  }

  CClientClientDHTInt dhtIndexProcRank(globalIndex2ProcRank, client->intraComm);
  dhtIndexProcRank.computeIndexInfoMapping(globalDomainIndex);
  globalDomainIndexOnProc = dhtIndexProcRank.getInfoIndexMap();
}
CATCH

}
