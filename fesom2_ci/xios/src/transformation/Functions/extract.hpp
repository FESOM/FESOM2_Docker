/*!
   \file extract.hpp
   \author Ha NGUYEN
   \since 27 June 2016
   \date 27 June 2016

   \brief Min reduction
 */
#ifndef __XIOS_REDUCTION_EXTRACT_ALGORITHM_HPP__
#define __XIOS_REDUCTION_EXTRACT_ALGORITHM_HPP__

#include "reduction.hpp"

namespace xios {

/*!
  \class CExtractReductionAlgorithm
  Interface for all reduction alogrithms.
*/
class CExtractReductionAlgorithm : public CReductionAlgorithm
{
public:
  CExtractReductionAlgorithm();

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,
                     bool ignoreMissingValue, bool firstPass);

  virtual ~CExtractReductionAlgorithm() {}

  virtual StdString getName() {return "Extract reduction";}

public:
  static bool registerTrans();

protected:
  static CReductionAlgorithm* create();
};

}
#endif // __XIOS_REDUCTION_EXTRACT_ALGORITHM_HPP__
