/*!
   \file reduction.hpp
   \author Ha NGUYEN
   \since 27 June 2016
   \date 27 June 2016

   \brief Parent class for all reduction
 */
#ifndef __XIOS_REDUCTION_ALGORITHM_HPP__
#define __XIOS_REDUCTION_ALGORITHM_HPP__

#include <vector>
#include "array_new.hpp"
#include "reduction_types.hpp"

namespace xios {

/*!
  \class CReductionAlgorithm
  Interface for all reduction alogrithms.
*/
class CReductionAlgorithm
{
public:
  static std::map<StdString,EReductionType> ReductionOperations;

public:
  CReductionAlgorithm() {}

  /*!
    Create an operation (sum, max, min) based on type
    \param [in] reduceType type to create
    return pointer to base class
  */
  static CReductionAlgorithm* createOperation(EReductionType reduceType);

  /*!
    Apply a reduction operation on local data.
    \param [in] localIndex vector contains local index of local data output and the corresponding weight
    \param [in] dataInput Pointer to the first element of data input array (in form of buffer)
    \param [in/out] dataOut Array contains local data
    \param [in/out] flagInitial vector of boolean to mark the local index already initialized. True means there is a need for initialization
    \param [in] firstPass indicate if it is the first time the apply funtion is called for a same transformation, in order to make a clean initialization 
  */
  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass) = 0;
  /*!
    Update local data 
    In some case (e.g average) we need global information (e.g weights) then update data with this information
    \param [in] dataOut local data output
  */
  virtual void updateData(CArray<double,1>& dataOut) {}

  virtual ~CReductionAlgorithm() {}

  virtual StdString getName() {return "Reduction";}

protected:
  typedef CReductionAlgorithm* (*CreateOperationCallBack)();
  typedef std::map<EReductionType, CreateOperationCallBack> CallBackMap;
  static CallBackMap* reductionCreationCallBacks_;

  static bool registerOperation(EReductionType reduceType, CreateOperationCallBack createFn);
  static bool unregisterOperation(EReductionType reduceType);

protected:
  static bool initReductionOperation(std::map<StdString,EReductionType>& m);
  static bool _dummyInit;
};

}
#endif // __XIOS_REDUCTION_ALGORITHM_HPP__
