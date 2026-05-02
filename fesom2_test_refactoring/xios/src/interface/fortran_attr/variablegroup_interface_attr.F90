! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE variablegroup_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_variablegroup_group_ref(variablegroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_set_variablegroup_group_ref

    SUBROUTINE cxios_get_variablegroup_group_ref(variablegroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_get_variablegroup_group_ref

    FUNCTION cxios_is_defined_variablegroup_group_ref(variablegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_variablegroup_group_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
    END FUNCTION cxios_is_defined_variablegroup_group_ref


    SUBROUTINE cxios_set_variablegroup_name(variablegroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_variablegroup_name

    SUBROUTINE cxios_get_variablegroup_name(variablegroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_variablegroup_name

    FUNCTION cxios_is_defined_variablegroup_name(variablegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_variablegroup_name
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
    END FUNCTION cxios_is_defined_variablegroup_name


    SUBROUTINE cxios_set_variablegroup_ts_target(variablegroup_hdl, ts_target, ts_target_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: ts_target
      INTEGER  (kind = C_INT)     , VALUE        :: ts_target_size
    END SUBROUTINE cxios_set_variablegroup_ts_target

    SUBROUTINE cxios_get_variablegroup_ts_target(variablegroup_hdl, ts_target, ts_target_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: ts_target
      INTEGER  (kind = C_INT)     , VALUE        :: ts_target_size
    END SUBROUTINE cxios_get_variablegroup_ts_target

    FUNCTION cxios_is_defined_variablegroup_ts_target(variablegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_variablegroup_ts_target
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
    END FUNCTION cxios_is_defined_variablegroup_ts_target


    SUBROUTINE cxios_set_variablegroup_type(variablegroup_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_variablegroup_type

    SUBROUTINE cxios_get_variablegroup_type(variablegroup_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_variablegroup_type

    FUNCTION cxios_is_defined_variablegroup_type(variablegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_variablegroup_type
      INTEGER (kind = C_INTPTR_T), VALUE :: variablegroup_hdl
    END FUNCTION cxios_is_defined_variablegroup_type

  END INTERFACE

END MODULE variablegroup_interface_attr
