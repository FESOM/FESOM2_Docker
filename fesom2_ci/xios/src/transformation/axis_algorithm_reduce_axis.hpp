/*!
   \file axis_algorithm_reduce_axis.hpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Algorithm for reduce an axis to a axis
 */
#ifndef __XIOS_AXIS_ALGORITHM_REDUCE_AXIS_HPP__
#define __XIOS_AXIS_ALGORITHM_REDUCE_AXIS_HPP__

#include "axis_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {

class CAxis;
class CReduceAxisToAxis;
class CReductionAlgorithm;

/*!
  \class CAxisAlgorithmReduceAxis
  Reduce a axis to an axis
*/
class CAxisAlgorithmReduceAxis : public CAxisAlgorithmTransformation
{
public:
  CAxisAlgorithmReduceAxis(CAxis* axisDestination, CAxis* axisSource, CReduceAxisToAxis* algo);

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass);

  virtual void updateData(CArray<double,1>& dataOut);
  
  virtual ~CAxisAlgorithmReduceAxis();

  static bool registerTrans();

  virtual StdString getName() {return "reduce_axis";}
protected:
  
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
#endif // __XIOS_AXIS_ALGORITHM_REDUCE_AXIS_HPP__
