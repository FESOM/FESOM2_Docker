/*!
   \file axis_algorithm_transformation.hpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 29 June 2015

   \brief Interface for all axis transformation algorithms.
 */
#ifndef __XIOS_AXIS_ALGORITHM_TRANSFORMATION_HPP__
#define __XIOS_AXIS_ALGORITHM_TRANSFORMATION_HPP__

#include "generic_algorithm_transformation.hpp"
#include "grid_transformation_factory_impl.hpp"

namespace xios {

class CAxis;
class CDomain;
class CScalar;
/*!
  \class CAxisAlgorithmTransformation
  Algorithms for axis.
*/
class CAxisAlgorithmTransformation : public virtual CGenericAlgorithmTransformation
{
public:
  CAxisAlgorithmTransformation(CAxis* axisDestination, CAxis* axisSource);
  CAxisAlgorithmTransformation(CAxis* axisDestination, CDomain* domainSource);
  CAxisAlgorithmTransformation(CAxis* axisDestination, CScalar* scalarSource);

  virtual ~CAxisAlgorithmTransformation();

  virtual StdString getName() {return "Axis Transformation";}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

  virtual void computeExchangeGlobalIndex(const CArray<size_t,1>& globalAxisIndex,
                                          int elementType,
                                          CClientClientDHTInt::Index2VectorInfoTypeMap& globalDomainIndexOnProc);

protected:
  //! Global index of an axis on grid destination
  std::vector<int> axisDestGlobalIndex_;

  //! Size of
  int axisDestGlobalSize_;

    //! Axis on grid destination
  CAxis* axisDest_;

  //! Axis on grid source
  CAxis* axisSrc_;

  //! Domain on grid source
  CDomain* domainSrc_;

  //! Scalar on grid source

  CScalar* scalarSrc_;
};

}
#endif // __XIOS_AXIS_ALGORITHM_TRANSFORMATION_HPP__
