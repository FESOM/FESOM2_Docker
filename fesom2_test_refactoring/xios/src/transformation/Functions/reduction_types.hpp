/*!
   \file reduction_types.hpp
   \author Ha NGUYEN
   \since 27 June 2016
   \date 27 June 2016

   \brief Different reduction types
 */
#ifndef __XIOS_REDUCTION_TYPES_HPP__
#define __XIOS_REDUCTION_TYPES_HPP__

namespace xios {

  typedef enum reduction_alogirthm_type
  {
    TRANS_REDUCE_SUM = 0,
    TRANS_REDUCE_MIN = 1,
    TRANS_REDUCE_MAX = 2,
    TRANS_REDUCE_EXTRACT = 3,
    TRANS_REDUCE_AVERAGE = 4
  } EReductionType;

}
#endif // __XIOS_REDUCTION_TYPES_HPP__
