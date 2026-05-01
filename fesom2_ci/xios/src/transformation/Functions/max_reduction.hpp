/*!
   \file max.hpp
   \author Ha NGUYEN
   \since 27 June 2016
   \date 27 June 2016

   \brief Max reduction
 */
#ifndef __XIOS_REDUCTION_MAX_ALGORITHM_HPP__
#define __XIOS_REDUCTION_MAX_ALGORITHM_HPP__

#include "reduction.hpp"

namespace xios {

/*!
  \class CMaxReductionAlgorithm
  Interface for all reduction alogrithms.
*/
class CMaxReductionAlgorithm : public CReductionAlgorithm
{
public:
  CMaxReductionAlgorithm();

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,
                     bool ignoreMissingValue, bool firstPass);

  virtual ~CMaxReductionAlgorithm() {}

  virtual StdString getName() {return "Max reduction";}

public:
  static bool registerTrans();

protected:
  static CReductionAlgorithm* create();
};

}
#endif // __XIOS_REDUCTION_MAX_ALGORITHM_HPP__
