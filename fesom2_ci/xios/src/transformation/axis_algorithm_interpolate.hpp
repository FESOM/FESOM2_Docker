/*!
   \file axis_algorithm_interpolate.hpp
   \author Ha NGUYEN
   \since 23 June 2015
   \date 23 June 2015

   \brief Algorithm for interpolation on an axis.
 */
#ifndef __XIOS_AXIS_ALGORITHM_INTERPOLATE_HPP__
#define __XIOS_AXIS_ALGORITHM_INTERPOLATE_HPP__

#include "axis_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {

class CAxis;
class CGrid;
class CInterpolateAxis;
 
/*!
  \class CAxisAlgorithmInterpolate
  Implementing interpolation on axis
  The values on axis source are assumed monotonic
*/
class CAxisAlgorithmInterpolate : public CAxisAlgorithmTransformation
{
public:
  CAxisAlgorithmInterpolate(CAxis* axisDestination, CAxis* axisSource, CInterpolateAxis* interpAxis);

  virtual ~CAxisAlgorithmInterpolate() {}

  static bool registerTrans();

  virtual StdString getName() {return "interpolate_axis";}
  bool isInversed() {return isInversed_;}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

private:
  void retrieveAllAxisValue(const CArray<double,1>& axisValue, const CArray<bool,1>& axisMask,
                            std::vector<double>& recvBuff, std::vector<int>& indexVec);
  void computeInterpolantPoint(const std::vector<double>& recvBuff, const std::vector<int>&, int transPos = 0);
  void computeInterpolantPoint(const std::vector<double>& recvBuff, const std::vector<int>&, 
                               const std::vector<CArray<double,1>* >& dataAuxInputs, int transPos = 0);
  void computeWeightedValueAndMapping(CArray<double,1>& axisDestValue, const std::map<int, std::vector<std::pair<int,double> > >& interpolatingIndexValues, int transPos = 0);
  void fillInAxisValue(std::vector<CArray<double,1> >& vecAxisValue,
                       const std::vector<CArray<double,1>* >& dataAuxInputs);

private:
  // Interpolation order
  int order_;
  bool extrapolate_ ;
  StdString coordinate_;
  StdString coordinateDST_;
  bool isInversed_;
  std::vector<std::vector<int> > transPosition_;

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

#endif // __XIOS_AXIS_ALGORITHM_INTERPOLATE_HPP__
