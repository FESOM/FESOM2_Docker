/*!
   \file scalar_algorithm_transformation.hpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 Oct 2016

   \brief Interface for all scalar transformation algorithms.
 */

#include "scalar_algorithm_transformation.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "client_client_dht_template.hpp"
#include "domain.hpp"
#include "axis.hpp"
#include "scalar.hpp"

namespace xios {

CScalarAlgorithmTransformation::CScalarAlgorithmTransformation(CScalar* scalarDestination, CScalar* scalarSource)
 : CGenericAlgorithmTransformation(),
   scalarDest_(scalarDestination),
   scalarSrc_(scalarSource), axisSrc_(0), domainSrc_(0)
{
}

CScalarAlgorithmTransformation::CScalarAlgorithmTransformation(CScalar* scalarDestination, CAxis* axisSource)
 : CGenericAlgorithmTransformation(),
   scalarDest_(scalarDestination),
   scalarSrc_(0), axisSrc_(axisSource), domainSrc_(0)
{
}

CScalarAlgorithmTransformation::CScalarAlgorithmTransformation(CScalar* scalarDestination, CDomain* domainSource)
 : CGenericAlgorithmTransformation(),
   scalarDest_(scalarDestination),
   scalarSrc_(0), axisSrc_(0), domainSrc_(domainSource)
{
}

CScalarAlgorithmTransformation::~CScalarAlgorithmTransformation()
{
}

void CScalarAlgorithmTransformation::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
}

/*!
  Compute global index of element source on different processes on knowing the global index source of transformation

  \param [in] globalIndexElementSource global index source of transformation (represented in the transformation mapping)
  \param [in] elementSourceType type of element source
  \param [out] globalIndexElementSourceOnProc processes which contain the corresponding global index of scalar source
*/
void CScalarAlgorithmTransformation::computeExchangeGlobalIndex(const CArray<size_t,1>& globalIndexElementSource,
                                                                int elementSourceType,
                                                                CClientClientDHTInt::Index2VectorInfoTypeMap& globalIndexElementSourceOnProc)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int clientSize = client->clientSize;

  if (2 == elementSourceType) // Source is a domain
  {
    size_t globalIndex;
    int nIndexSize = domainSrc_->i_index.numElements();
    CArray<int,1>& iIndex = domainSrc_->i_index;
    CArray<int,1>& jIndex = domainSrc_->j_index;
    int niGlo = domainSrc_->ni_glo;
    CArray<bool,1>& localMask = domainSrc_ -> localMask ;
    CClientClientDHTInt::Index2VectorInfoTypeMap globalIndex2ProcRank;
    globalIndex2ProcRank.rehash(std::ceil(nIndexSize/globalIndex2ProcRank.max_load_factor()));
    for (int idx = 0; idx < nIndexSize; ++idx)
    {
      if (localMask(idx))
      {
        globalIndex = jIndex(idx) * niGlo + iIndex(idx);
        globalIndex2ProcRank[globalIndex].resize(1);
        globalIndex2ProcRank[globalIndex][0] = clientRank;
      }
    }

    CClientClientDHTInt dhtIndexProcRank(globalIndex2ProcRank, client->intraComm);
    dhtIndexProcRank.computeIndexInfoMapping(globalIndexElementSource);
    globalIndexElementSourceOnProc = dhtIndexProcRank.getInfoIndexMap();
  }
  else if (1 == elementSourceType) // Source is an axis
  {
    size_t globalIndex;
    int nIndexSize = axisSrc_->index.numElements();
    CClientClientDHTInt::Index2VectorInfoTypeMap globalIndex2ProcRank;
    globalIndex2ProcRank.rehash(std::ceil(nIndexSize/globalIndex2ProcRank.max_load_factor()));
    CArray<bool,1>& localMask = axisSrc_ -> mask ;
   
    for (int idx = 0; idx < nIndexSize; ++idx)
    {
      if (localMask(idx))
      {
        globalIndex = axisSrc_->index(idx);
        globalIndex2ProcRank[globalIndex].resize(1);
        globalIndex2ProcRank[globalIndex][0] = clientRank;
      }
    }

    CClientClientDHTInt dhtIndexProcRank(globalIndex2ProcRank, client->intraComm);
    dhtIndexProcRank.computeIndexInfoMapping(globalIndexElementSource);
    globalIndexElementSourceOnProc = dhtIndexProcRank.getInfoIndexMap();
  }
  else // scalar
  {
    size_t globalIndex = 0;    
    CClientClientDHTInt::Index2VectorInfoTypeMap globalIndex2ProcRank;
    globalIndex2ProcRank[globalIndex].resize(1);
    globalIndex2ProcRank[globalIndex][0] = clientRank;

    CClientClientDHTInt dhtIndexProcRank(globalIndex2ProcRank, client->intraComm);
    dhtIndexProcRank.computeIndexInfoMapping(globalIndexElementSource);
    globalIndexElementSourceOnProc = dhtIndexProcRank.getInfoIndexMap();
  }
}
CATCH
}
