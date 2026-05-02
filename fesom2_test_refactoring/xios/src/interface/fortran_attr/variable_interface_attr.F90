! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE variable_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_variable_name(variable_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_variable_name

    SUBROUTINE cxios_get_variable_name(variable_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_variable_name

    FUNCTION cxios_is_defined_variable_name(variable_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_variable_name
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
    END FUNCTION cxios_is_defined_variable_name


    SUBROUTINE cxios_set_variable_ts_target(variable_hdl, ts_target, ts_target_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: ts_target
      INTEGER  (kind = C_INT)     , VALUE        :: ts_target_size
    END SUBROUTINE cxios_set_variable_ts_target

    SUBROUTINE cxios_get_variable_ts_target(variable_hdl, ts_target, ts_target_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: ts_target
      INTEGER  (kind = C_INT)     , VALUE        :: ts_target_size
    END SUBROUTINE cxios_get_variable_ts_target

    FUNCTION cxios_is_defined_variable_ts_target(variable_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_variable_ts_target
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
    END FUNCTION cxios_is_defined_variable_ts_target


    SUBROUTINE cxios_set_variable_type(variable_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_variable_type

    SUBROUTINE cxios_get_variable_type(variable_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_variable_type

    FUNCTION cxios_is_defined_variable_type(variable_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_variable_type
      INTEGER (kind = C_INTPTR_T), VALUE :: variable_hdl
    END FUNCTION cxios_is_defined_variable_type

  END INTERFACE

END MODULE variable_interface_attr
