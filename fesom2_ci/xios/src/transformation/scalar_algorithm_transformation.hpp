/*!
   \file scalar_algorithm_transformation.hpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Interface for all scalar transformation algorithms.
 */
#ifndef __XIOS_SCALAR_ALGORITHM_TRANSFORMATION_HPP__
#define __XIOS_SCALAR_ALGORITHM_TRANSFORMATION_HPP__

#include "generic_algorithm_transformation.hpp"

namespace xios {

class CScalar;
class CAxis;
class CDomain;

/*!
  \class CScalarAlgorithmTransformation
  Algorithms for scalar.
*/
class CScalarAlgorithmTransformation : public virtual CGenericAlgorithmTransformation
{
public:
  CScalarAlgorithmTransformation(CScalar* scalarDestination, CScalar* scalarSource);
  CScalarAlgorithmTransformation(CScalar* scalarDestination, CAxis* axisSource);
  CScalarAlgorithmTransformation(CScalar* scalarDestination, CDomain* domainSource);

  virtual ~CScalarAlgorithmTransformation();

  virtual StdString getName() {return "Scalar Transformation";}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

  virtual void computeExchangeGlobalIndex(const CArray<size_t,1>& globalScalarIndex,
                                          int elementType,
                                          CClientClientDHTInt::Index2VectorInfoTypeMap& globalScalarIndexOnProc);

protected:
  //! Global index of an scalar on grid destination
  std::vector<int> scalarDestGlobalIndex_;

  //! Size of
  int scalarDestGlobalSize_;

    //! Scalar on grid destination
  CScalar* scalarDest_;

  //! Scalar on grid source
  CScalar* scalarSrc_;
  //! Axis source
  CAxis* axisSrc_;
  //! Domain source
  CDomain* domainSrc_;
};

}
#endif // __XIOS_SCALAR_ALGORITHM_TRANSFORMATION_HPP__
