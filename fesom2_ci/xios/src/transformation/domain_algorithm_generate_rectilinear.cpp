/*!
   \file domain_algorithm_generate_rectilinear.cpp
   \author Ha NGUYEN
   \since 31 Aug 2015
   \date 31 Aug 2015

   \brief Algorithm for automatic generation of rectilinear domain.
 */
#include "domain_algorithm_generate_rectilinear.hpp"
#include "grid.hpp"
#include "domain.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "generate_rectilinear_domain.hpp"

namespace xios {

CDomainAlgorithmGenerateRectilinear::CDomainAlgorithmGenerateRectilinear(CDomain* domainDestination, CDomain* domainSource,
                                                                         CGrid* gridDest, CGrid* gridSource,
                                                                         CGenerateRectilinearDomain* genRectDomain)
: CDomainAlgorithmTransformation(domainDestination, domainSource), nbDomainDistributedPart_(0)
TRY
{
  type_ = ELEMENT_GENERATION;
  genRectDomain->checkValid(domainDestination);
  if (0 != gridSource) computeDistributionGridSource(gridSource);
  else
  {
    computeDistributionGridDestination(gridDest);
  }
  fillInAttributesDomainDestination();
}
CATCH

/*!
  Compute the index mapping between domain on grid source and one on grid destination
*/
void CDomainAlgorithmGenerateRectilinear::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
 /* Nothing to do */
}

/*!
  Calculate the number of distributed parts on domain source
*/
void CDomainAlgorithmGenerateRectilinear::computeDistributionGridSource(CGrid* gridSrc)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client = context->client;

  std::vector<CDomain*> domListSrcP = gridSrc->getDomains();
  std::vector<CAxis*> axisListSrcP = gridSrc->getAxis();

  for (int i = 0; i < domListSrcP.size(); ++i) // support we have only domain, more than one, for now, dont know how to process
  {
    // First, find (roundly) distribution of associated axis (if any)
    if (axisListSrcP.empty()) nbDomainDistributedPart_ = client->clientSize;
    else
    {
      gridSrc->solveAxisRef(false);
      int nbAxis = axisListSrcP.size();
      std::vector<int> nbLocalAxis(nbAxis, 0);
      for (int j = 0; j < nbAxis; ++j)
      {
        std::vector<int> globalAxisIndex(axisListSrcP[j]->n);
        for (int idx = 0; idx < axisListSrcP[j]->n; ++idx)
          globalAxisIndex[idx] = axisListSrcP[j]->begin + idx;
        HashXIOS<int> hashFunc;
        StdSize hashValue = hashFunc.hashVec(globalAxisIndex);
        std::vector<StdSize> recvBuff(client->clientSize);
        MPI_Gather(&hashValue, 1, MPI_UNSIGNED_LONG,
                   &recvBuff[0], 1, MPI_UNSIGNED_LONG,
                   0,
                   client->intraComm);
        if (0 == client->clientRank)
        {
          std::set<StdSize> setTmp;
          for (int k = 0; k < recvBuff.size(); ++k)
          {
            if (setTmp.end() == setTmp.find(recvBuff[k]))
            {
              ++nbLocalAxis[j];
              setTmp.insert(recvBuff[k]);
            }
          }
        }

        MPI_Bcast(&nbLocalAxis[0], nbAxis, MPI_INT,
                  0, client->intraComm);
      }

      int nbAxisDistributedPart = 1;
      for (int j = 0; j < nbAxis; ++j) nbAxisDistributedPart *= nbLocalAxis[j];
      nbDomainDistributedPart_ = client->clientSize/nbAxisDistributedPart;
    }
  }
}
CATCH

/*!
  Compute the distribution of the domain destination by using available information provided by user such as n_distributed_partition of axis
*/
void CDomainAlgorithmGenerateRectilinear::computeDistributionGridDestination(CGrid* gridDest)
TRY
{
  // For now, just suppose that the grid contains only one domain
  std::vector<CAxis*> axisListDestP = gridDest->getAxis();
  int nbPartition = 1, idx = 0;
  for (int i = 0; i < gridDest->axis_domain_order.numElements(); ++i)
  {
    if (false == (gridDest->axis_domain_order)(i))
    {
      nbPartition *= (axisListDestP[idx]->n_distributed_partition.isEmpty()) ? 1: (axisListDestP[idx]->n_distributed_partition.getValue());
      ++idx;
    }
  }

  CContext* context = CContext::getCurrent();
  CContextClient* client = context->client;
  int modPart = (client->clientSize) % nbPartition;
  if (0 != modPart)
    ERROR("CDomainAlgorithmGenerateRectilinear::computeDistributionGridDestination(CGrid* gridDest)",
       << "The grid " <<gridDest->getId() << " is not well-distributed. There is an incompatibility between distribution of axis and domain.");
  nbDomainDistributedPart_ = client->clientSize/nbPartition;

}
CATCH

/*!
  Fill in all necessary attributes of domain destination and their values
*/
void CDomainAlgorithmGenerateRectilinear::fillInAttributesDomainDestination()
TRY
{
  if (!domainDest_->distributionAttributesHaveValue())
    domainDest_->redistribute(nbDomainDistributedPart_);
  domainDest_->fillInLonLat();
}
CATCH
}
