/*!
   \file axis_algorithm_transformation.hpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 29 June 2015

   \brief Interface for all axis transformation algorithms.
 */

#include "axis_algorithm_transformation.hpp"
#include "axis_algorithm_inverse.hpp"
#include "axis_algorithm_zoom.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "client_client_dht_template.hpp"
#include "axis.hpp"

namespace xios {

CAxisAlgorithmTransformation::CAxisAlgorithmTransformation(CAxis* axisDestination, CAxis* axisSource)
 : CGenericAlgorithmTransformation(), axisDest_(axisDestination), axisSrc_(axisSource), domainSrc_(0),scalarSrc_(0)
TRY
{
  axisDestGlobalSize_ = axisDestination->n_glo.getValue();
  int niDest = axisDestination->n.getValue();
  int ibeginDest = axisDestination->begin.getValue();

  for (int idx = 0; idx < niDest; ++idx)
    if ((axisDestination->mask)(idx)) axisDestGlobalIndex_.push_back(ibeginDest+idx);
}
CATCH

CAxisAlgorithmTransformation::CAxisAlgorithmTransformation(CAxis* axisDestination, CDomain* domainSource)
 : CGenericAlgorithmTransformation(), axisDest_(axisDestination), axisSrc_(0), domainSrc_(domainSource),scalarSrc_(0)
TRY
{
  axisDestGlobalSize_ = axisDestination->n_glo.getValue();
  int niDest = axisDestination->n.getValue();
  int ibeginDest = axisDestination->begin.getValue();

  for (int idx = 0; idx < niDest; ++idx)
    if ((axisDestination->mask)(idx)) axisDestGlobalIndex_.push_back(ibeginDest+idx);
}
CATCH

CAxisAlgorithmTransformation::CAxisAlgorithmTransformation(CAxis* axisDestination, CScalar* scalarSource)
 : CGenericAlgorithmTransformation(), axisDest_(axisDestination), axisSrc_(0), domainSrc_(0), scalarSrc_(scalarSource)
TRY
{
  axisDestGlobalSize_ = axisDestination->n_glo.getValue();
  int niDest = axisDestination->n.getValue();
  int ibeginDest = axisDestination->begin.getValue();

  for (int idx = 0; idx < niDest; ++idx)
    if ((axisDestination->mask)(idx)) axisDestGlobalIndex_.push_back(ibeginDest+idx);
}
CATCH

CAxisAlgorithmTransformation::~CAxisAlgorithmTransformation()
{
}

void CAxisAlgorithmTransformation::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
}

/*!
  Compute global index of axis on different processes
  \param [in] globalAxisIndex global index of axis source
  \param [out] globalAxisIndexOnProc processes which contain the corresponding global index of axis source
*/
void CAxisAlgorithmTransformation::computeExchangeGlobalIndex(const CArray<size_t,1>& globalAxisIndex,
                                                              int elementType,
                                                              CClientClientDHTInt::Index2VectorInfoTypeMap& globalAxisIndexOnProc)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int clientSize = client->clientSize;

  size_t globalIndex;
  int nIndexSize = 0;
  CArray<bool,1>* ptLocalMask ;
  CArray<bool,1> scalarMask(1) ;
  scalarMask=true ;
  
  if (2 == elementType) 
  {
    nIndexSize = domainSrc_->i_index.numElements();
    ptLocalMask=&(domainSrc_->localMask) ;
  }
  else if (1 == elementType)
  {
     nIndexSize = axisSrc_->index.numElements();
     ptLocalMask=&(axisSrc_->mask) ;
  }
  else
  {
     nIndexSize=1  ; //  scalar
     ptLocalMask=&scalarMask ;
  }
  CArray<bool,1>& localMask=*ptLocalMask ;
  
  CClientClientDHTInt::Index2VectorInfoTypeMap globalIndex2ProcRank;
  globalIndex2ProcRank.rehash(std::ceil(nIndexSize/globalIndex2ProcRank.max_load_factor()));
  for (int idx = 0; idx < nIndexSize; ++idx)
  {
    if (localMask(idx))
    {
      if (2 == elementType) // domain
      {
       globalIndex = domainSrc_->i_index(idx) + domainSrc_->j_index(idx) * domainSrc_->ni_glo;
      }
      else if (1 == elementType) // axis
      {
        globalIndex = axisSrc_->index(idx);
      }
      else // scalar
      {
        globalIndex = 0;
      }
     
      globalIndex2ProcRank[globalIndex].resize(1);
      globalIndex2ProcRank[globalIndex][0] = clientRank;
    }
  }

  CClientClientDHTInt dhtIndexProcRank(globalIndex2ProcRank, client->intraComm);
  dhtIndexProcRank.computeIndexInfoMapping(globalAxisIndex);

  globalAxisIndexOnProc = dhtIndexProcRank.getInfoIndexMap();
}
CATCH

}
