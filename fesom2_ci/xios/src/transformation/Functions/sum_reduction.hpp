/*!
   \file sum.hpp
   \author Ha NGUYEN
   \since 27 June 2016
   \date 27 June 2016

   \brief Sum reduction
 */
#ifndef __XIOS_REDUCTION_SUM_ALGORITHM_HPP__
#define __XIOS_REDUCTION_SUM_ALGORITHM_HPP__

#include "reduction.hpp"

namespace xios {

/*!
  \class CSumReductionAlgorithm
  Interface for all reduction alogrithms.
*/
class CSumReductionAlgorithm : public CReductionAlgorithm
{
public:
  CSumReductionAlgorithm();

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,
                     bool ignoreMissingValue, bool firstPass);

  virtual ~CSumReductionAlgorithm() {}

  virtual StdString getName() {return "Sum reduction";}

public:
  static bool registerTrans();

protected:
  static CReductionAlgorithm* create();
};

}
#endif // __XIOS_REDUCTION_SUM_ALGORITHM_HPP__
