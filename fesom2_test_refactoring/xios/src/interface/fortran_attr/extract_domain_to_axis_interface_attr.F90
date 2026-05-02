! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE extract_domain_to_axis_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_extract_domain_to_axis_direction(extract_domain_to_axis_hdl, direction, direction_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_domain_to_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: direction
      INTEGER  (kind = C_INT)     , VALUE        :: direction_size
    END SUBROUTINE cxios_set_extract_domain_to_axis_direction

    SUBROUTINE cxios_get_extract_domain_to_axis_direction(extract_domain_to_axis_hdl, direction, direction_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_domain_to_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: direction
      INTEGER  (kind = C_INT)     , VALUE        :: direction_size
    END SUBROUTINE cxios_get_extract_domain_to_axis_direction

    FUNCTION cxios_is_defined_extract_domain_to_axis_direction(extract_domain_to_axis_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_extract_domain_to_axis_direction
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_domain_to_axis_hdl
    END FUNCTION cxios_is_defined_extract_domain_to_axis_direction


    SUBROUTINE cxios_set_extract_domain_to_axis_position(extract_domain_to_axis_hdl, position) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_domain_to_axis_hdl
      INTEGER (KIND=C_INT)      , VALUE :: position
    END SUBROUTINE cxios_set_extract_domain_to_axis_position

    SUBROUTINE cxios_get_extract_domain_to_axis_position(extract_domain_to_axis_hdl, position) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_domain_to_axis_hdl
      INTEGER (KIND=C_INT)             :: position
    END SUBROUTINE cxios_get_extract_domain_to_axis_position

    FUNCTION cxios_is_defined_extract_domain_to_axis_position(extract_domain_to_axis_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_extract_domain_to_axis_position
      INTEGER (kind = C_INTPTR_T), VALUE :: extract_domain_to_axis_hdl
    END FUNCTION cxios_is_defined_extract_domain_to_axis_position

  END INTERFACE

END MODULE extract_domain_to_axis_interface_attr
