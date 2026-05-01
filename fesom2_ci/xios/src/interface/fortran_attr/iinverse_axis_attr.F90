! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE iinverse_axis_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE iinverse_axis
  USE inverse_axis_interface_attr

CONTAINS

  SUBROUTINE xios(set_inverse_axis_attr)  &
    ( inverse_axis_id )

    IMPLICIT NONE
      TYPE(txios(inverse_axis))  :: inverse_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::inverse_axis_id

      CALL xios(get_inverse_axis_handle) &
      (inverse_axis_id,inverse_axis_hdl)
      CALL xios(set_inverse_axis_attr_hdl_)   &
      ( inverse_axis_hdl )

  END SUBROUTINE xios(set_inverse_axis_attr)

  SUBROUTINE xios(set_inverse_axis_attr_hdl)  &
    ( inverse_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(inverse_axis)) , INTENT(IN) :: inverse_axis_hdl

      CALL xios(set_inverse_axis_attr_hdl_)  &
      ( inverse_axis_hdl )

  END SUBROUTINE xios(set_inverse_axis_attr_hdl)

  SUBROUTINE xios(set_inverse_axis_attr_hdl_)   &
    ( inverse_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(inverse_axis)) , INTENT(IN) :: inverse_axis_hdl

  END SUBROUTINE xios(set_inverse_axis_attr_hdl_)

  SUBROUTINE xios(get_inverse_axis_attr)  &
    ( inverse_axis_id )

    IMPLICIT NONE
      TYPE(txios(inverse_axis))  :: inverse_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::inverse_axis_id

      CALL xios(get_inverse_axis_handle) &
      (inverse_axis_id,inverse_axis_hdl)
      CALL xios(get_inverse_axis_attr_hdl_)   &
      ( inverse_axis_hdl )

  END SUBROUTINE xios(get_inverse_axis_attr)

  SUBROUTINE xios(get_inverse_axis_attr_hdl)  &
    ( inverse_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(inverse_axis)) , INTENT(IN) :: inverse_axis_hdl

      CALL xios(get_inverse_axis_attr_hdl_)  &
      ( inverse_axis_hdl )

  END SUBROUTINE xios(get_inverse_axis_attr_hdl)

  SUBROUTINE xios(get_inverse_axis_attr_hdl_)   &
    ( inverse_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(inverse_axis)) , INTENT(IN) :: inverse_axis_hdl

  END SUBROUTINE xios(get_inverse_axis_attr_hdl_)

  SUBROUTINE xios(is_defined_inverse_axis_attr)  &
    ( inverse_axis_id )

    IMPLICIT NONE
      TYPE(txios(inverse_axis))  :: inverse_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::inverse_axis_id

      CALL xios(get_inverse_axis_handle) &
      (inverse_axis_id,inverse_axis_hdl)
      CALL xios(is_defined_inverse_axis_attr_hdl_)   &
      ( inverse_axis_hdl )

  END SUBROUTINE xios(is_defined_inverse_axis_attr)

  SUBROUTINE xios(is_defined_inverse_axis_attr_hdl)  &
    ( inverse_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(inverse_axis)) , INTENT(IN) :: inverse_axis_hdl

      CALL xios(is_defined_inverse_axis_attr_hdl_)  &
      ( inverse_axis_hdl )

  END SUBROUTINE xios(is_defined_inverse_axis_attr_hdl)

  SUBROUTINE xios(is_defined_inverse_axis_attr_hdl_)   &
    ( inverse_axis_hdl )

    IMPLICIT NONE
      TYPE(txios(inverse_axis)) , INTENT(IN) :: inverse_axis_hdl

  END SUBROUTINE xios(is_defined_inverse_axis_attr_hdl_)

END MODULE iinverse_axis_attr
