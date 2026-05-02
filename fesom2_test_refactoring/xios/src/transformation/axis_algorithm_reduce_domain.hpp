/*!
   \file axis_algorithm_reduce_domain.hpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Algorithm for reduce an axis to a axis
 */
#ifndef __XIOS_AXIS_ALGORITHM_REDUCE_DOMAIN_HPP__
#define __XIOS_AXIS_ALGORITHM_REDUCE_DOMAIN_HPP__

#include "axis_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {

class CAxis;
class CDomain;
class CReduceDomainToAxis;
class CReductionAlgorithm;

/*!
  \class CAxisAlgorithmReduceDomain
  Reduce a domain to an axis
*/
class CAxisAlgorithmReduceDomain : public CAxisAlgorithmTransformation
{
public:
  CAxisAlgorithmReduceDomain(CAxis* axisDestination, CDomain* domainSource, CReduceDomainToAxis* algo);

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass);

  virtual void updateData(CArray<double,1>& dataOut);
  
  virtual ~CAxisAlgorithmReduceDomain();

  static bool registerTrans();

  virtual StdString getName() {return "reduce_domain";}

protected:
  enum ReduceDirection {
    undefined = 0,
    iDir = 1,
    jDir = 2
  };
  
  ReduceDirection dir_;
  bool local ;
  
protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs); 
  
protected:
  CReductionAlgorithm* reduction_;

private:
  static CGenericAlgorithmTransformation* create(CGrid* gridDst, CGrid* gridSrc,
                                                CTransformation<CAxis>* transformation,
                                                int elementPositionInGrid,
                                                std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                std::map<int, int>& elementPositionInGridDst2DomainPosition);
};

}
#endif // __XIOS_AXIS_ALGORITHM_REDUCE_DOMAIN_HPP__
