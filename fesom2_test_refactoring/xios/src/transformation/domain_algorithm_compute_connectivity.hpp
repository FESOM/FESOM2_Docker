/*!
   \file domain_algorithm_compute_connectivity.hpp
   \author Ha NGUYEN
   \since 03 June 2015
   \date 12 June 2015

   \brief Algorithm for compute_connectivitying on an domain.
 */
#ifndef __XIOS_DOMAIN_ALGORITHM_COMPUTE_CONNECTIVITY_HPP__
#define __XIOS_DOMAIN_ALGORITHM_COMPUTE_CONNECTIVITY_HPP__

#include "domain_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {
class CDomain;
class CComputeConnectivityDomain;

/*!
  \class CDomainAlgorithmComputeConnectivity
*/
class CDomainAlgorithmComputeConnectivity : public CDomainAlgorithmTransformation
{
public:
  CDomainAlgorithmComputeConnectivity(CDomain* domainDestination, CDomain* domainSource, CComputeConnectivityDomain* compute_connectivityDomain);

  virtual ~CDomainAlgorithmComputeConnectivity() {}

  static bool registerTrans();

  virtual StdString getName() {return "compute_connectivity_domain";}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

protected:
  void computeLocalConnectivity(int type,
                                CDomain* domain,
                                int& nbConnectivityMax,
                                CArray<int,1>& nbConnectivity,
                                CArray<int,2>& localConnectivity);

private:
  static CGenericAlgorithmTransformation* create(CGrid* gridDst, CGrid* gridSrc,
                                                CTransformation<CDomain>* transformation,
                                                int elementPositionInGrid,
                                                std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                std::map<int, int>& elementPositionInGridDst2DomainPosition);
};

}
#endif // __XIOS_DOMAIN_ALGORITHM_COMPUTE_CONNECTIVITY_HPP__
