/*!
   \file domain_algorithm_transformation.hpp
   \author Ha NGUYEN
   \since 02 Jul 2015
   \date 02 Jul 2015

   \brief Interface for all domain transformation algorithms.
 */
#ifndef __XIOS_DOMAIN_ALGORITHM_TRANSFORMATION_HPP__
#define __XIOS_DOMAIN_ALGORITHM_TRANSFORMATION_HPP__

#include "generic_algorithm_transformation.hpp"
#include "client_client_dht_template.hpp"

namespace xios {

class CDomain;
/*!
  \class CDomainAlgorithmTransformation
  Algorithms for domain.
*/
class CDomainAlgorithmTransformation : public virtual CGenericAlgorithmTransformation
{
public:
  CDomainAlgorithmTransformation(CDomain* domainDestination, CDomain* domainSource);

  virtual ~CDomainAlgorithmTransformation();

  virtual StdString getName() {return "Domain Transformation";}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >&);

  virtual void computeExchangeGlobalIndex(const CArray<size_t,1>& globalDomainIndex,
                                          int elementType,
                                          CClientClientDHTInt::Index2VectorInfoTypeMap& globalDomainIndexOnProc);

protected:
    //! Domain on grid destination
  CDomain* domainDest_;

  //! Domain on grid source
  CDomain* domainSrc_;
};

}
#endif // __XIOS_DOMAIN_ALGORITHM_TRANSFORMATION_HPP__
