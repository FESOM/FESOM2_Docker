/*!
   \file domain_algorithm_compute_connectivity.cpp
   \author Ha NGUYEN
   \since 15 Jul 2016
   \date 15 Jul 2016

   \brief Algorithm for compute_connectivity on an domain.
 */
#include "domain_algorithm_compute_connectivity.hpp"
#include "compute_connectivity_domain.hpp"
#include "mesh.hpp"
#include "domain.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"

namespace xios {
CGenericAlgorithmTransformation* CDomainAlgorithmComputeConnectivity::create(CGrid* gridDst, CGrid* gridSrc,
                                                                     CTransformation<CDomain>* transformation,
                                                                     int elementPositionInGrid,
                                                                     std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CDomain*> domainListDestP = gridDst->getDomains();
  std::vector<CDomain*> domainListSrcP  = gridSrc->getDomains();

  CComputeConnectivityDomain* compute_connectivityDomain = dynamic_cast<CComputeConnectivityDomain*> (transformation);
  int domainDstIndex = elementPositionInGridDst2DomainPosition[elementPositionInGrid];
  int domainSrcIndex = elementPositionInGridSrc2DomainPosition[elementPositionInGrid];

  return (new CDomainAlgorithmComputeConnectivity(domainListDestP[domainDstIndex], domainListSrcP[domainSrcIndex], compute_connectivityDomain));
}
CATCH

bool CDomainAlgorithmComputeConnectivity::registerTrans()
TRY
{
  return CGridTransformationFactory<CDomain>::registerTransformation(TRANS_COMPUTE_CONNECTIVITY_DOMAIN, create);
}
CATCH

CDomainAlgorithmComputeConnectivity::CDomainAlgorithmComputeConnectivity(CDomain* domainDestination, CDomain* domainSource,
                                                                         CComputeConnectivityDomain* compute_connectivityDomain)
: CDomainAlgorithmTransformation(domainDestination, domainSource)
TRY
{
  this->type_ = (ELEMENT_NO_MODIFICATION_WITHOUT_DATA);
  compute_connectivityDomain->checkValid(domainDestination);
  int& nbNeighborMax = compute_connectivityDomain->n_neighbor_max;
  CArray<int,1>& nbNeighbor = compute_connectivityDomain->n_neighbor;
  CArray<int,2>& localNeighbors = compute_connectivityDomain->local_neighbor;
  int type = 1; // Edge type
  switch (compute_connectivityDomain->type)
  {
    case CComputeConnectivityDomain::type_attr::node :
      type = 0;
      break;
    case CComputeConnectivityDomain::type_attr::edge :
      type = 1;
      break;
    default:
      break;
  }

  computeLocalConnectivity(type, domainDestination, nbNeighborMax, nbNeighbor, localNeighbors);
}
CATCH

/*!
 *  Compute local connectivity of a domain
 *  \param[in] type type of connectivity (node or edge)
 *  \param[in] domain domain on which we calculate local connectivity
 *  \param[in/out] nbConnectivityMax maximum number of neighbor a cell of domain has
 *  \param[in/out] nbConnectivity number of neighbor a cell has
 *  \param[in/out] localConnectivity localConnectivity local index of neighbor of a cell
 */
void CDomainAlgorithmComputeConnectivity::computeLocalConnectivity(int type,
                                                                  CDomain* domain,
                                                                  int& nbConnectivityMax,
                                                                  CArray<int,1>& nbConnectivity,
                                                                  CArray<int,2>& localConnectivity)
TRY
{

  CMesh mesh;

  CArray<double,2>& bounds_lon = domain->bounds_lon_1d;
  CArray<double,2>& bounds_lat = domain->bounds_lat_1d;
  int ncell = bounds_lon.shape()[1];
  CArray<int,1> localIndex(ncell);
  for (int idx = 0; idx <ncell; ++idx) localIndex(idx) = idx;

  mesh.getLocalNghbFaces(type, localIndex, bounds_lon, bounds_lat, localConnectivity, nbConnectivity);
  nbConnectivityMax = 0;
  for (int idx =0; idx < nbConnectivity.numElements(); ++idx)
    if (nbConnectivityMax < nbConnectivity(idx)) nbConnectivityMax = nbConnectivity(idx);
}
CATCH

/*!
  Compute the index mapping between domain on grid source and one on grid destination
*/
void CDomainAlgorithmComputeConnectivity::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
{
}

}
