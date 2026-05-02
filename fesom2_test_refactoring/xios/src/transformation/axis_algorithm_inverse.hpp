/*!
   \file axis_algorithm_inverse.hpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 09 June 2015

   \brief Algorithm for inversing an axis..
 */
#ifndef __XIOS_AXIS_ALGORITHM_INVERSE_HPP__
#define __XIOS_AXIS_ALGORITHM_INVERSE_HPP__

#include "axis_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {

class CAxis;
class CInverseAxis;

/*!
  \class CAxisAlgorithmInverse
  Inversing an axis
*/
class CAxisAlgorithmInverse : public CAxisAlgorithmTransformation
{
public:
  CAxisAlgorithmInverse(CAxis* axisDestination, CAxis* axisSource, CInverseAxis* inverseAxis);

  virtual ~CAxisAlgorithmInverse() {}

  static bool registerTrans();

  virtual StdString getName() {return "inverse_axis";}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

private:
  void updateAxisValue();

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
#endif // __XIOS_AXIS_ALGORITHM_INVERSE_HPP__
