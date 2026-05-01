! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE iduplicate_scalar_to_axis_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE iduplicate_scalar_to_axis
  USE duplicate_scalar_to_axis_interface_attr

CONTAINS

  SUBROUTINE xios(set_duplicate_scalar_to_axis_attr)  &
    ( duplicate_scalar_to_axis_id )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis))  :: duplicate_scalar_to_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::duplicate_scalar_to_axis_id

      CALL xios(get_duplicate_scalar_to_axis_handle) &
      (duplicate_scalar_to_axis_id,duplicate_scalar_to_axis_hdl)
      CALL xios(set_duplicate_scalar_to_axis_attr_hdl_)   &
      ( duplicate_scalar_to_axis_hdl )

  END SUBROUTINE xios(set_duplicate_scalar_to_axis_attr)

  SUBROUTINE xios(set_duplicate_scalar_to_axis_attr_hdl)  &
    ( duplicate_scalar_to_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis)) , INTENT(IN) :: duplicate_scalar_to_axis_hdl

      CALL xios(set_duplicate_scalar_to_axis_attr_hdl_)  &
      ( duplicate_scalar_to_axis_hdl )

  END SUBROUTINE xios(set_duplicate_scalar_to_axis_attr_hdl)

  SUBROUTINE xios(set_duplicate_scalar_to_axis_attr_hdl_)   &
    ( duplicate_scalar_to_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis)) , INTENT(IN) :: duplicate_scalar_to_axis_hdl

  END SUBROUTINE xios(set_duplicate_scalar_to_axis_attr_hdl_)

  SUBROUTINE xios(get_duplicate_scalar_to_axis_attr)  &
    ( duplicate_scalar_to_axis_id )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis))  :: duplicate_scalar_to_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::duplicate_scalar_to_axis_id

      CALL xios(get_duplicate_scalar_to_axis_handle) &
      (duplicate_scalar_to_axis_id,duplicate_scalar_to_axis_hdl)
      CALL xios(get_duplicate_scalar_to_axis_attr_hdl_)   &
      ( duplicate_scalar_to_axis_hdl )

  END SUBROUTINE xios(get_duplicate_scalar_to_axis_attr)

  SUBROUTINE xios(get_duplicate_scalar_to_axis_attr_hdl)  &
    ( duplicate_scalar_to_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis)) , INTENT(IN) :: duplicate_scalar_to_axis_hdl

      CALL xios(get_duplicate_scalar_to_axis_attr_hdl_)  &
      ( duplicate_scalar_to_axis_hdl )

  END SUBROUTINE xios(get_duplicate_scalar_to_axis_attr_hdl)

  SUBROUTINE xios(get_duplicate_scalar_to_axis_attr_hdl_)   &
    ( duplicate_scalar_to_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis)) , INTENT(IN) :: duplicate_scalar_to_axis_hdl

  END SUBROUTINE xios(get_duplicate_scalar_to_axis_attr_hdl_)

  SUBROUTINE xios(is_defined_duplicate_scalar_to_axis_attr)  &
    ( duplicate_scalar_to_axis_id )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis))  :: duplicate_scalar_to_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::duplicate_scalar_to_axis_id

      CALL xios(get_duplicate_scalar_to_axis_handle) &
      (duplicate_scalar_to_axis_id,duplicate_scalar_to_axis_hdl)
      CALL xios(is_defined_duplicate_scalar_to_axis_attr_hdl_)   &
      ( duplicate_scalar_to_axis_hdl )

  END SUBROUTINE xios(is_defined_duplicate_scalar_to_axis_attr)

  SUBROUTINE xios(is_defined_duplicate_scalar_to_axis_attr_hdl)  &
    ( duplicate_scalar_to_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis)) , INTENT(IN) :: duplicate_scalar_to_axis_hdl

      CALL xios(is_defined_duplicate_scalar_to_axis_attr_hdl_)  &
      ( duplicate_scalar_to_axis_hdl )

  END SUBROUTINE xios(is_defined_duplicate_scalar_to_axis_attr_hdl)

  SUBROUTINE xios(is_defined_duplicate_scalar_to_axis_attr_hdl_)   &
    ( duplicate_scalar_to_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(duplicate_scalar_to_axis)) , INTENT(IN) :: duplicate_scalar_to_axis_hdl

  END SUBROUTINE xios(is_defined_duplicate_scalar_to_axis_attr_hdl_)

END MODULE iduplicate_scalar_to_axis_attr
