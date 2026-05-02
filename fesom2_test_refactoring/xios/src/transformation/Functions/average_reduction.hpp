/*!
   \file average.hpp
   \author Ha NGUYEN
   \since 8 Sep 2016
   \date 8 Sep 2016

   \brief Average reduction
 */
#ifndef __XIOS_REDUCTION_AVERAGE_ALGORITHM_HPP__
#define __XIOS_REDUCTION_AVERAGE_ALGORITHM_HPP__

#include "reduction.hpp"

namespace xios {

/*!
  \class CAverageReductionAlgorithm
  Interface for all reduction alogrithms.
*/
class CAverageReductionAlgorithm : public CReductionAlgorithm
{
public:
  CAverageReductionAlgorithm();

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass);

  virtual void updateData(CArray<double,1>& dataOut);

  virtual ~CAverageReductionAlgorithm() {}

  virtual StdString getName() {return "Average reduction";}

protected:
  CArray<double,1> weights_;
  bool resetWeight_;

public:
  static bool registerTrans();

protected:
  static CReductionAlgorithm* create();
};

}
#endif // __XIOS_REDUCTION_AVERAGE_ALGORITHM_HPP__
