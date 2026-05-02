/*!
   \file min.hpp
   \author Ha NGUYEN
   \since 27 June 2016
   \date 27 June 2016

   \brief Min reduction
 */
#ifndef __XIOS_REDUCTION_MIN_ALGORITHM_HPP__
#define __XIOS_REDUCTION_MIN_ALGORITHM_HPP__

#include "reduction.hpp"

namespace xios {

/*!
  \class CMinReductionAlgorithm
  Interface for all reduction alogrithms.
*/
class CMinReductionAlgorithm : public CReductionAlgorithm
{
public:
  CMinReductionAlgorithm();

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass);

  virtual ~CMinReductionAlgorithm() {}

  virtual StdString getName() {return "Min reduction";}

public:
  static bool registerTrans();

protected:
  static CReductionAlgorithm* create();
};

}
#endif // __XIOS_REDUCTION_MIN_ALGORITHM_HPP__
