! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE fieldgroup_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_fieldgroup_add_offset(fieldgroup_hdl, add_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: add_offset
    END SUBROUTINE cxios_set_fieldgroup_add_offset

    SUBROUTINE cxios_get_fieldgroup_add_offset(fieldgroup_hdl, add_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)             :: add_offset
    END SUBROUTINE cxios_get_fieldgroup_add_offset

    FUNCTION cxios_is_defined_fieldgroup_add_offset(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_add_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_add_offset


    SUBROUTINE cxios_set_fieldgroup_axis_ref(fieldgroup_hdl, axis_ref, axis_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_ref
      INTEGER  (kind = C_INT)     , VALUE        :: axis_ref_size
    END SUBROUTINE cxios_set_fieldgroup_axis_ref

    SUBROUTINE cxios_get_fieldgroup_axis_ref(fieldgroup_hdl, axis_ref, axis_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_ref
      INTEGER  (kind = C_INT)     , VALUE        :: axis_ref_size
    END SUBROUTINE cxios_get_fieldgroup_axis_ref

    FUNCTION cxios_is_defined_fieldgroup_axis_ref(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_axis_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_axis_ref


    SUBROUTINE cxios_set_fieldgroup_cell_methods(fieldgroup_hdl, cell_methods, cell_methods_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: cell_methods
      INTEGER  (kind = C_INT)     , VALUE        :: cell_methods_size
    END SUBROUTINE cxios_set_fieldgroup_cell_methods

    SUBROUTINE cxios_get_fieldgroup_cell_methods(fieldgroup_hdl, cell_methods, cell_methods_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: cell_methods
      INTEGER  (kind = C_INT)     , VALUE        :: cell_methods_size
    END SUBROUTINE cxios_get_fieldgroup_cell_methods

    FUNCTION cxios_is_defined_fieldgroup_cell_methods(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_cell_methods
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_cell_methods


    SUBROUTINE cxios_set_fieldgroup_cell_methods_mode(fieldgroup_hdl, cell_methods_mode, cell_methods_mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: cell_methods_mode
      INTEGER  (kind = C_INT)     , VALUE        :: cell_methods_mode_size
    END SUBROUTINE cxios_set_fieldgroup_cell_methods_mode

    SUBROUTINE cxios_get_fieldgroup_cell_methods_mode(fieldgroup_hdl, cell_methods_mode, cell_methods_mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: cell_methods_mode
      INTEGER  (kind = C_INT)     , VALUE        :: cell_methods_mode_size
    END SUBROUTINE cxios_get_fieldgroup_cell_methods_mode

    FUNCTION cxios_is_defined_fieldgroup_cell_methods_mode(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_cell_methods_mode
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_cell_methods_mode


    SUBROUTINE cxios_set_fieldgroup_check_if_active(fieldgroup_hdl, check_if_active) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: check_if_active
    END SUBROUTINE cxios_set_fieldgroup_check_if_active

    SUBROUTINE cxios_get_fieldgroup_check_if_active(fieldgroup_hdl, check_if_active) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)             :: check_if_active
    END SUBROUTINE cxios_get_fieldgroup_check_if_active

    FUNCTION cxios_is_defined_fieldgroup_check_if_active(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_check_if_active
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_check_if_active


    SUBROUTINE cxios_set_fieldgroup_comment(fieldgroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_fieldgroup_comment

    SUBROUTINE cxios_get_fieldgroup_comment(fieldgroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_fieldgroup_comment

    FUNCTION cxios_is_defined_fieldgroup_comment(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_comment


    SUBROUTINE cxios_set_fieldgroup_compression_level(fieldgroup_hdl, compression_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: compression_level
    END SUBROUTINE cxios_set_fieldgroup_compression_level

    SUBROUTINE cxios_get_fieldgroup_compression_level(fieldgroup_hdl, compression_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      INTEGER (KIND=C_INT)             :: compression_level
    END SUBROUTINE cxios_get_fieldgroup_compression_level

    FUNCTION cxios_is_defined_fieldgroup_compression_level(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_compression_level
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_compression_level


    SUBROUTINE cxios_set_fieldgroup_default_value(fieldgroup_hdl, default_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: default_value
    END SUBROUTINE cxios_set_fieldgroup_default_value

    SUBROUTINE cxios_get_fieldgroup_default_value(fieldgroup_hdl, default_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)             :: default_value
    END SUBROUTINE cxios_get_fieldgroup_default_value

    FUNCTION cxios_is_defined_fieldgroup_default_value(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_default_value
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_default_value


    SUBROUTINE cxios_set_fieldgroup_detect_missing_value(fieldgroup_hdl, detect_missing_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: detect_missing_value
    END SUBROUTINE cxios_set_fieldgroup_detect_missing_value

    SUBROUTINE cxios_get_fieldgroup_detect_missing_value(fieldgroup_hdl, detect_missing_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)             :: detect_missing_value
    END SUBROUTINE cxios_get_fieldgroup_detect_missing_value

    FUNCTION cxios_is_defined_fieldgroup_detect_missing_value(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_detect_missing_value
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_detect_missing_value


    SUBROUTINE cxios_set_fieldgroup_domain_ref(fieldgroup_hdl, domain_ref, domain_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: domain_ref
      INTEGER  (kind = C_INT)     , VALUE        :: domain_ref_size
    END SUBROUTINE cxios_set_fieldgroup_domain_ref

    SUBROUTINE cxios_get_fieldgroup_domain_ref(fieldgroup_hdl, domain_ref, domain_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: domain_ref
      INTEGER  (kind = C_INT)     , VALUE        :: domain_ref_size
    END SUBROUTINE cxios_get_fieldgroup_domain_ref

    FUNCTION cxios_is_defined_fieldgroup_domain_ref(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_domain_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_domain_ref


    SUBROUTINE cxios_set_fieldgroup_enabled(fieldgroup_hdl, enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: enabled
    END SUBROUTINE cxios_set_fieldgroup_enabled

    SUBROUTINE cxios_get_fieldgroup_enabled(fieldgroup_hdl, enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)             :: enabled
    END SUBROUTINE cxios_get_fieldgroup_enabled

    FUNCTION cxios_is_defined_fieldgroup_enabled(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_enabled
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_enabled


    SUBROUTINE cxios_set_fieldgroup_expr(fieldgroup_hdl, expr, expr_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: expr
      INTEGER  (kind = C_INT)     , VALUE        :: expr_size
    END SUBROUTINE cxios_set_fieldgroup_expr

    SUBROUTINE cxios_get_fieldgroup_expr(fieldgroup_hdl, expr, expr_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: expr
      INTEGER  (kind = C_INT)     , VALUE        :: expr_size
    END SUBROUTINE cxios_get_fieldgroup_expr

    FUNCTION cxios_is_defined_fieldgroup_expr(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_expr
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_expr


    SUBROUTINE cxios_set_fieldgroup_field_ref(fieldgroup_hdl, field_ref, field_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: field_ref
      INTEGER  (kind = C_INT)     , VALUE        :: field_ref_size
    END SUBROUTINE cxios_set_fieldgroup_field_ref

    SUBROUTINE cxios_get_fieldgroup_field_ref(fieldgroup_hdl, field_ref, field_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: field_ref
      INTEGER  (kind = C_INT)     , VALUE        :: field_ref_size
    END SUBROUTINE cxios_get_fieldgroup_field_ref

    FUNCTION cxios_is_defined_fieldgroup_field_ref(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_field_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_field_ref


    SUBROUTINE cxios_set_fieldgroup_freq_offset(fieldgroup_hdl, freq_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      TYPE(txios(duration)), VALUE :: freq_offset
    END SUBROUTINE cxios_set_fieldgroup_freq_offset

    SUBROUTINE cxios_get_fieldgroup_freq_offset(fieldgroup_hdl, freq_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      TYPE(txios(duration)) :: freq_offset
    END SUBROUTINE cxios_get_fieldgroup_freq_offset

    FUNCTION cxios_is_defined_fieldgroup_freq_offset(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_freq_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_freq_offset


    SUBROUTINE cxios_set_fieldgroup_freq_op(fieldgroup_hdl, freq_op) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      TYPE(txios(duration)), VALUE :: freq_op
    END SUBROUTINE cxios_set_fieldgroup_freq_op

    SUBROUTINE cxios_get_fieldgroup_freq_op(fieldgroup_hdl, freq_op) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      TYPE(txios(duration)) :: freq_op
    END SUBROUTINE cxios_get_fieldgroup_freq_op

    FUNCTION cxios_is_defined_fieldgroup_freq_op(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_freq_op
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_freq_op


    SUBROUTINE cxios_set_fieldgroup_grid_path(fieldgroup_hdl, grid_path, grid_path_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: grid_path
      INTEGER  (kind = C_INT)     , VALUE        :: grid_path_size
    END SUBROUTINE cxios_set_fieldgroup_grid_path

    SUBROUTINE cxios_get_fieldgroup_grid_path(fieldgroup_hdl, grid_path, grid_path_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: grid_path
      INTEGER  (kind = C_INT)     , VALUE        :: grid_path_size
    END SUBROUTINE cxios_get_fieldgroup_grid_path

    FUNCTION cxios_is_defined_fieldgroup_grid_path(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_grid_path
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_grid_path


    SUBROUTINE cxios_set_fieldgroup_grid_ref(fieldgroup_hdl, grid_ref, grid_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: grid_ref
      INTEGER  (kind = C_INT)     , VALUE        :: grid_ref_size
    END SUBROUTINE cxios_set_fieldgroup_grid_ref

    SUBROUTINE cxios_get_fieldgroup_grid_ref(fieldgroup_hdl, grid_ref, grid_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: grid_ref
      INTEGER  (kind = C_INT)     , VALUE        :: grid_ref_size
    END SUBROUTINE cxios_get_fieldgroup_grid_ref

    FUNCTION cxios_is_defined_fieldgroup_grid_ref(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_grid_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_grid_ref


    SUBROUTINE cxios_set_fieldgroup_group_ref(fieldgroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_set_fieldgroup_group_ref

    SUBROUTINE cxios_get_fieldgroup_group_ref(fieldgroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_get_fieldgroup_group_ref

    FUNCTION cxios_is_defined_fieldgroup_group_ref(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_group_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_group_ref


    SUBROUTINE cxios_set_fieldgroup_indexed_output(fieldgroup_hdl, indexed_output) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: indexed_output
    END SUBROUTINE cxios_set_fieldgroup_indexed_output

    SUBROUTINE cxios_get_fieldgroup_indexed_output(fieldgroup_hdl, indexed_output) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)             :: indexed_output
    END SUBROUTINE cxios_get_fieldgroup_indexed_output

    FUNCTION cxios_is_defined_fieldgroup_indexed_output(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_indexed_output
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_indexed_output


    SUBROUTINE cxios_set_fieldgroup_level(fieldgroup_hdl, level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: level
    END SUBROUTINE cxios_set_fieldgroup_level

    SUBROUTINE cxios_get_fieldgroup_level(fieldgroup_hdl, level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      INTEGER (KIND=C_INT)             :: level
    END SUBROUTINE cxios_get_fieldgroup_level

    FUNCTION cxios_is_defined_fieldgroup_level(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_level
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_level


    SUBROUTINE cxios_set_fieldgroup_long_name(fieldgroup_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_set_fieldgroup_long_name

    SUBROUTINE cxios_get_fieldgroup_long_name(fieldgroup_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_get_fieldgroup_long_name

    FUNCTION cxios_is_defined_fieldgroup_long_name(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_long_name
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_long_name


    SUBROUTINE cxios_set_fieldgroup_name(fieldgroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_fieldgroup_name

    SUBROUTINE cxios_get_fieldgroup_name(fieldgroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_fieldgroup_name

    FUNCTION cxios_is_defined_fieldgroup_name(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_name
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_name


    SUBROUTINE cxios_set_fieldgroup_operation(fieldgroup_hdl, operation, operation_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: operation
      INTEGER  (kind = C_INT)     , VALUE        :: operation_size
    END SUBROUTINE cxios_set_fieldgroup_operation

    SUBROUTINE cxios_get_fieldgroup_operation(fieldgroup_hdl, operation, operation_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: operation
      INTEGER  (kind = C_INT)     , VALUE        :: operation_size
    END SUBROUTINE cxios_get_fieldgroup_operation

    FUNCTION cxios_is_defined_fieldgroup_operation(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_operation
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_operation


    SUBROUTINE cxios_set_fieldgroup_prec(fieldgroup_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: prec
    END SUBROUTINE cxios_set_fieldgroup_prec

    SUBROUTINE cxios_get_fieldgroup_prec(fieldgroup_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      INTEGER (KIND=C_INT)             :: prec
    END SUBROUTINE cxios_get_fieldgroup_prec

    FUNCTION cxios_is_defined_fieldgroup_prec(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_prec
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_prec


    SUBROUTINE cxios_set_fieldgroup_read_access(fieldgroup_hdl, read_access) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: read_access
    END SUBROUTINE cxios_set_fieldgroup_read_access

    SUBROUTINE cxios_get_fieldgroup_read_access(fieldgroup_hdl, read_access) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)             :: read_access
    END SUBROUTINE cxios_get_fieldgroup_read_access

    FUNCTION cxios_is_defined_fieldgroup_read_access(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_read_access
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_read_access


    SUBROUTINE cxios_set_fieldgroup_scalar_ref(fieldgroup_hdl, scalar_ref, scalar_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: scalar_ref
      INTEGER  (kind = C_INT)     , VALUE        :: scalar_ref_size
    END SUBROUTINE cxios_set_fieldgroup_scalar_ref

    SUBROUTINE cxios_get_fieldgroup_scalar_ref(fieldgroup_hdl, scalar_ref, scalar_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: scalar_ref
      INTEGER  (kind = C_INT)     , VALUE        :: scalar_ref_size
    END SUBROUTINE cxios_get_fieldgroup_scalar_ref

    FUNCTION cxios_is_defined_fieldgroup_scalar_ref(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_scalar_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_scalar_ref


    SUBROUTINE cxios_set_fieldgroup_scale_factor(fieldgroup_hdl, scale_factor) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: scale_factor
    END SUBROUTINE cxios_set_fieldgroup_scale_factor

    SUBROUTINE cxios_get_fieldgroup_scale_factor(fieldgroup_hdl, scale_factor) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)             :: scale_factor
    END SUBROUTINE cxios_get_fieldgroup_scale_factor

    FUNCTION cxios_is_defined_fieldgroup_scale_factor(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_scale_factor
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_scale_factor


    SUBROUTINE cxios_set_fieldgroup_standard_name(fieldgroup_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_set_fieldgroup_standard_name

    SUBROUTINE cxios_get_fieldgroup_standard_name(fieldgroup_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_get_fieldgroup_standard_name

    FUNCTION cxios_is_defined_fieldgroup_standard_name(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_standard_name
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_standard_name


    SUBROUTINE cxios_set_fieldgroup_ts_enabled(fieldgroup_hdl, ts_enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: ts_enabled
    END SUBROUTINE cxios_set_fieldgroup_ts_enabled

    SUBROUTINE cxios_get_fieldgroup_ts_enabled(fieldgroup_hdl, ts_enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      LOGICAL (KIND=C_BOOL)             :: ts_enabled
    END SUBROUTINE cxios_get_fieldgroup_ts_enabled

    FUNCTION cxios_is_defined_fieldgroup_ts_enabled(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_ts_enabled
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_ts_enabled


    SUBROUTINE cxios_set_fieldgroup_ts_split_freq(fieldgroup_hdl, ts_split_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      TYPE(txios(duration)), VALUE :: ts_split_freq
    END SUBROUTINE cxios_set_fieldgroup_ts_split_freq

    SUBROUTINE cxios_get_fieldgroup_ts_split_freq(fieldgroup_hdl, ts_split_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      TYPE(txios(duration)) :: ts_split_freq
    END SUBROUTINE cxios_get_fieldgroup_ts_split_freq

    FUNCTION cxios_is_defined_fieldgroup_ts_split_freq(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_ts_split_freq
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_ts_split_freq


    SUBROUTINE cxios_set_fieldgroup_unit(fieldgroup_hdl, unit, unit_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: unit
      INTEGER  (kind = C_INT)     , VALUE        :: unit_size
    END SUBROUTINE cxios_set_fieldgroup_unit

    SUBROUTINE cxios_get_fieldgroup_unit(fieldgroup_hdl, unit, unit_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: unit
      INTEGER  (kind = C_INT)     , VALUE        :: unit_size
    END SUBROUTINE cxios_get_fieldgroup_unit

    FUNCTION cxios_is_defined_fieldgroup_unit(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_unit
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_unit


    SUBROUTINE cxios_set_fieldgroup_valid_max(fieldgroup_hdl, valid_max) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: valid_max
    END SUBROUTINE cxios_set_fieldgroup_valid_max

    SUBROUTINE cxios_get_fieldgroup_valid_max(fieldgroup_hdl, valid_max) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)             :: valid_max
    END SUBROUTINE cxios_get_fieldgroup_valid_max

    FUNCTION cxios_is_defined_fieldgroup_valid_max(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_valid_max
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_valid_max


    SUBROUTINE cxios_set_fieldgroup_valid_min(fieldgroup_hdl, valid_min) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: valid_min
    END SUBROUTINE cxios_set_fieldgroup_valid_min

    SUBROUTINE cxios_get_fieldgroup_valid_min(fieldgroup_hdl, valid_min) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
      REAL (KIND=C_DOUBLE)             :: valid_min
    END SUBROUTINE cxios_get_fieldgroup_valid_min

    FUNCTION cxios_is_defined_fieldgroup_valid_min(fieldgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_fieldgroup_valid_min
      INTEGER (kind = C_INTPTR_T), VALUE :: fieldgroup_hdl
    END FUNCTION cxios_is_defined_fieldgroup_valid_min

  END INTERFACE

END MODULE fieldgroup_interface_attr
