#ifndef __XIOS_TRANSFORMATION_ENUM__
#define __XIOS_TRANSFORMATION_ENUM__

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///
      typedef enum transformation_type
      {
        TRANS_ZOOM_AXIS = 0,
        TRANS_INVERSE_AXIS = 1,
        TRANS_INTERPOLATE_AXIS = 2,
        TRANS_ZOOM_DOMAIN = 3,
        TRANS_INTERPOLATE_DOMAIN = 4,
        TRANS_GENERATE_RECTILINEAR_DOMAIN = 5,
        TRANS_REDUCE_AXIS_TO_SCALAR = 6,
        TRANS_REDUCE_DOMAIN_TO_AXIS = 7,
        TRANS_EXTRACT_DOMAIN_TO_AXIS = 8,
        TRANS_COMPUTE_CONNECTIVITY_DOMAIN = 9,
        TRANS_EXPAND_DOMAIN = 10,
        TRANS_EXTRACT_AXIS_TO_SCALAR = 11,
        TRANS_REDUCE_DOMAIN_TO_SCALAR = 12,
        TRANS_TEMPORAL_SPLITTING = 13,
        TRANS_REDUCE_AXIS_TO_AXIS = 14,
        TRANS_DUPLICATE_SCALAR_TO_AXIS = 15,
        TRANS_REDUCE_SCALAR_TO_SCALAR = 16,
        TRANS_REORDER_DOMAIN = 17,
        TRANS_EXTRACT_DOMAIN = 18,
        TRANS_EXTRACT_AXIS = 19
      } ETranformationType;

} // namespace xios

#endif // __XIOS_TRANSFORMATION_ENUM__
