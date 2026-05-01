! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE extract_axis_to_scalar_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_extract_axis_to_scalar_position(extract_axis_to_scalar_hdl, position) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_axis_to_scalar_hdl
      INTEGER (KIND=C_INT)      , VALUE :: position
    END SUBROUTINE cxios_set_extract_axis_to_scalar_position

    SUBROUTINE cxios_get_extract_axis_to_scalar_position(extract_axis_to_scalar_hdl, position) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_axis_to_scalar_hdl
      INTEGER (KIND=C_INT)             :: position
    END SUBROUTINE cxios_get_extract_axis_to_scalar_position

    FUNCTION cxios_is_defined_extract_axis_to_scalar_position(extract_axis_to_scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_extract_axis_to_scalar_position
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_axis_to_scalar_hdl
    END FUNCTION cxios_is_defined_extract_axis_to_scalar_position

  END INTERFACE

END MODULE extract_axis_to_scalar_interface_attr
