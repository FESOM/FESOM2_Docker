! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE reduce_domain_to_axis_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_reduce_domain_to_axis_direction(reduce_domain_to_axis_hdl, direction, direction_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: direction
      INTEGER  (kind = C_INT)     , VALUE        :: direction_size
    END SUBROUTINE cxios_set_reduce_domain_to_axis_direction

    SUBROUTINE cxios_get_reduce_domain_to_axis_direction(reduce_domain_to_axis_hdl, direction, direction_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: direction
      INTEGER  (kind = C_INT)     , VALUE        :: direction_size
    END SUBROUTINE cxios_get_reduce_domain_to_axis_direction

    FUNCTION cxios_is_defined_reduce_domain_to_axis_direction(reduce_domain_to_axis_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_reduce_domain_to_axis_direction
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
    END FUNCTION cxios_is_defined_reduce_domain_to_axis_direction


    SUBROUTINE cxios_set_reduce_domain_to_axis_local(reduce_domain_to_axis_hdl, local) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: local
    END SUBROUTINE cxios_set_reduce_domain_to_axis_local

    SUBROUTINE cxios_get_reduce_domain_to_axis_local(reduce_domain_to_axis_hdl, local) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
      LOGICAL (KIND=C_BOOL)             :: local
    END SUBROUTINE cxios_get_reduce_domain_to_axis_local

    FUNCTION cxios_is_defined_reduce_domain_to_axis_local(reduce_domain_to_axis_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_reduce_domain_to_axis_local
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
    END FUNCTION cxios_is_defined_reduce_domain_to_axis_local


    SUBROUTINE cxios_set_reduce_domain_to_axis_operation(reduce_domain_to_axis_hdl, operation, operation_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: operation
      INTEGER  (kind = C_INT)     , VALUE        :: operation_size
    END SUBROUTINE cxios_set_reduce_domain_to_axis_operation

    SUBROUTINE cxios_get_reduce_domain_to_axis_operation(reduce_domain_to_axis_hdl, operation, operation_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: operation
      INTEGER  (kind = C_INT)     , VALUE        :: operation_size
    END SUBROUTINE cxios_get_reduce_domain_to_axis_operation

    FUNCTION cxios_is_defined_reduce_domain_to_axis_operation(reduce_domain_to_axis_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_reduce_domain_to_axis_operation
      INTEGER (kind = C_INTPTR_T), VALUE :: reduce_domain_to_axis_hdl
    END FUNCTION cxios_is_defined_reduce_domain_to_axis_operation

  END INTERFACE

END MODULE reduce_domain_to_axis_interface_attr
