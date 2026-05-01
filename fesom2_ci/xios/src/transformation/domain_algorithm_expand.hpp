/*!
   \file domain_algorithm_expand.hpp
   \author Ha NGUYEN
   \since 08 Aug 2016
   \date 08 Aug 2016

   \brief Algorithm for expanding an domain.
 */
#ifndef __XIOS_DOMAIN_ALGORITHM_EXPAND_HPP__
#define __XIOS_DOMAIN_ALGORITHM_EXPAND_HPP__

#include "domain_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {
class CDomain;
class CExpandDomain;

/*!
  \class CDomainAlgorithmExpand
*/
class CDomainAlgorithmExpand : public CDomainAlgorithmTransformation
{
public:
  CDomainAlgorithmExpand(CDomain* domainDestination, CDomain* domainSource, CExpandDomain* expandDomain);

  virtual ~CDomainAlgorithmExpand() {}

  static bool registerTrans();

  virtual StdString getName() {return "expand_domain";}

protected:
  bool isXPeriodic_; // Flag to determine the periodicity of expansion (only for rectilinear)
  bool isYPeriodic_; // Flag to determine the periodicity of expansion (only for rectilinear)

protected:
  void expandDomainEdgeConnectivity(CDomain* domainDestination, CDomain* domainSource);
  void expandDomainNodeConnectivity(CDomain* domainDestination, CDomain* domainSource);
  void updateRectilinearDomainAttributes(CDomain* domainDestination,
                                         CDomain* domainSource,
                                         CArray<int,2>& neighborsDomainSrc);

  void updateUnstructuredDomainAttributes(CDomain* domainDestination,
                                          CDomain* domainSource,
                                          CArray<int,2>& neighborsDomainSrc);

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

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
#endif // __XIOS_DOMAIN_ALGORITHM_EXPAND_HPP__
