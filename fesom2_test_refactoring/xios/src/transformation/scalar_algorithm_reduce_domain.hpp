/*!
   \file scalar_algorithm_reduce_scalar.hpp
   \author Ha NGUYEN
   \since 13 Oct 2016
   \date 13 Oct 2016

   \brief Algorithm for reduce an DOMAIN to a scalar
 */
#ifndef __XIOS_SCALAR_ALGORITHM_REDUCE_DOMAIN_HPP__
#define __XIOS_SCALAR_ALGORITHM_REDUCE_DOMAIN_HPP__

#include "scalar_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {

class CScalar;
class CDomain;
class CReduceDomainToScalar;
class CReductionAlgorithm;

/*!
  \class CScalarAlgorithmReduceDomain
  Reducing an DOMAIN to a scalar
*/
class CScalarAlgorithmReduceDomain : public CScalarAlgorithmTransformation
{
public:
  CScalarAlgorithmReduceDomain(CScalar* scalarDestination, CDomain* domainSource, CReduceDomainToScalar* algo);

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass);

  virtual void updateData(CArray<double,1>& dataOut);
  
  virtual ~CScalarAlgorithmReduceDomain();

  static bool registerTrans();

  virtual StdString getName() {return "reduce_domain";}

protected:
  bool local ;
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

protected:
  CReductionAlgorithm* reduction_;

private:

  static CGenericAlgorithmTransformation* create(CGrid* gridDst, CGrid* gridSrc,
                                                CTransformation<CScalar>* transformation,
                                                int elementPositionInGrid,
                                                std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridSrc2DOMAINPosition,
                                                std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridDst2DOMAINPosition,
                                                std::map<int, int>& elementPositionInGridDst2DomainPosition);
};

}
#endif // __XIOS_SCALAR_ALGORITHM_REDUCE_DOMAIN_HPP__
