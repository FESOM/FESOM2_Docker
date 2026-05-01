! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE field_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_field_add_offset(field_hdl, add_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: add_offset
    END SUBROUTINE cxios_set_field_add_offset

    SUBROUTINE cxios_get_field_add_offset(field_hdl, add_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)             :: add_offset
    END SUBROUTINE cxios_get_field_add_offset

    FUNCTION cxios_is_defined_field_add_offset(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_add_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_add_offset


    SUBROUTINE cxios_set_field_axis_ref(field_hdl, axis_ref, axis_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_ref
      INTEGER  (kind = C_INT)     , VALUE        :: axis_ref_size
    END SUBROUTINE cxios_set_field_axis_ref

    SUBROUTINE cxios_get_field_axis_ref(field_hdl, axis_ref, axis_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_ref
      INTEGER  (kind = C_INT)     , VALUE        :: axis_ref_size
    END SUBROUTINE cxios_get_field_axis_ref

    FUNCTION cxios_is_defined_field_axis_ref(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_axis_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_axis_ref


    SUBROUTINE cxios_set_field_cell_methods(field_hdl, cell_methods, cell_methods_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: cell_methods
      INTEGER  (kind = C_INT)     , VALUE        :: cell_methods_size
    END SUBROUTINE cxios_set_field_cell_methods

    SUBROUTINE cxios_get_field_cell_methods(field_hdl, cell_methods, cell_methods_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: cell_methods
      INTEGER  (kind = C_INT)     , VALUE        :: cell_methods_size
    END SUBROUTINE cxios_get_field_cell_methods

    FUNCTION cxios_is_defined_field_cell_methods(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_cell_methods
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_cell_methods


    SUBROUTINE cxios_set_field_cell_methods_mode(field_hdl, cell_methods_mode, cell_methods_mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: cell_methods_mode
      INTEGER  (kind = C_INT)     , VALUE        :: cell_methods_mode_size
    END SUBROUTINE cxios_set_field_cell_methods_mode

    SUBROUTINE cxios_get_field_cell_methods_mode(field_hdl, cell_methods_mode, cell_methods_mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: cell_methods_mode
      INTEGER  (kind = C_INT)     , VALUE        :: cell_methods_mode_size
    END SUBROUTINE cxios_get_field_cell_methods_mode

    FUNCTION cxios_is_defined_field_cell_methods_mode(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_cell_methods_mode
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_cell_methods_mode


    SUBROUTINE cxios_set_field_check_if_active(field_hdl, check_if_active) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: check_if_active
    END SUBROUTINE cxios_set_field_check_if_active

    SUBROUTINE cxios_get_field_check_if_active(field_hdl, check_if_active) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)             :: check_if_active
    END SUBROUTINE cxios_get_field_check_if_active

    FUNCTION cxios_is_defined_field_check_if_active(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_check_if_active
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_check_if_active


    SUBROUTINE cxios_set_field_comment(field_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_field_comment

    SUBROUTINE cxios_get_field_comment(field_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_field_comment

    FUNCTION cxios_is_defined_field_comment(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_comment


    SUBROUTINE cxios_set_field_compression_level(field_hdl, compression_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      INTEGER (KIND=C_INT)      , VALUE :: compression_level
    END SUBROUTINE cxios_set_field_compression_level

    SUBROUTINE cxios_get_field_compression_level(field_hdl, compression_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      INTEGER (KIND=C_INT)             :: compression_level
    END SUBROUTINE cxios_get_field_compression_level

    FUNCTION cxios_is_defined_field_compression_level(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_compression_level
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_compression_level


    SUBROUTINE cxios_set_field_default_value(field_hdl, default_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: default_value
    END SUBROUTINE cxios_set_field_default_value

    SUBROUTINE cxios_get_field_default_value(field_hdl, default_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)             :: default_value
    END SUBROUTINE cxios_get_field_default_value

    FUNCTION cxios_is_defined_field_default_value(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_default_value
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_default_value


    SUBROUTINE cxios_set_field_detect_missing_value(field_hdl, detect_missing_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: detect_missing_value
    END SUBROUTINE cxios_set_field_detect_missing_value

    SUBROUTINE cxios_get_field_detect_missing_value(field_hdl, detect_missing_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)             :: detect_missing_value
    END SUBROUTINE cxios_get_field_detect_missing_value

    FUNCTION cxios_is_defined_field_detect_missing_value(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_detect_missing_value
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_detect_missing_value


    SUBROUTINE cxios_set_field_domain_ref(field_hdl, domain_ref, domain_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: domain_ref
      INTEGER  (kind = C_INT)     , VALUE        :: domain_ref_size
    END SUBROUTINE cxios_set_field_domain_ref

    SUBROUTINE cxios_get_field_domain_ref(field_hdl, domain_ref, domain_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: domain_ref
      INTEGER  (kind = C_INT)     , VALUE        :: domain_ref_size
    END SUBROUTINE cxios_get_field_domain_ref

    FUNCTION cxios_is_defined_field_domain_ref(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_domain_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_domain_ref


    SUBROUTINE cxios_set_field_enabled(field_hdl, enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: enabled
    END SUBROUTINE cxios_set_field_enabled

    SUBROUTINE cxios_get_field_enabled(field_hdl, enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)             :: enabled
    END SUBROUTINE cxios_get_field_enabled

    FUNCTION cxios_is_defined_field_enabled(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_enabled
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_enabled


    SUBROUTINE cxios_set_field_expr(field_hdl, expr, expr_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: expr
      INTEGER  (kind = C_INT)     , VALUE        :: expr_size
    END SUBROUTINE cxios_set_field_expr

    SUBROUTINE cxios_get_field_expr(field_hdl, expr, expr_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: expr
      INTEGER  (kind = C_INT)     , VALUE        :: expr_size
    END SUBROUTINE cxios_get_field_expr

    FUNCTION cxios_is_defined_field_expr(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_expr
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_expr


    SUBROUTINE cxios_set_field_field_ref(field_hdl, field_ref, field_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: field_ref
      INTEGER  (kind = C_INT)     , VALUE        :: field_ref_size
    END SUBROUTINE cxios_set_field_field_ref

    SUBROUTINE cxios_get_field_field_ref(field_hdl, field_ref, field_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: field_ref
      INTEGER  (kind = C_INT)     , VALUE        :: field_ref_size
    END SUBROUTINE cxios_get_field_field_ref

    FUNCTION cxios_is_defined_field_field_ref(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_field_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_field_ref


    SUBROUTINE cxios_set_field_freq_offset(field_hdl, freq_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      TYPE(txios(duration)), VALUE :: freq_offset
    END SUBROUTINE cxios_set_field_freq_offset

    SUBROUTINE cxios_get_field_freq_offset(field_hdl, freq_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      TYPE(txios(duration)) :: freq_offset
    END SUBROUTINE cxios_get_field_freq_offset

    FUNCTION cxios_is_defined_field_freq_offset(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_freq_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_freq_offset


    SUBROUTINE cxios_set_field_freq_op(field_hdl, freq_op) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      TYPE(txios(duration)), VALUE :: freq_op
    END SUBROUTINE cxios_set_field_freq_op

    SUBROUTINE cxios_get_field_freq_op(field_hdl, freq_op) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      TYPE(txios(duration)) :: freq_op
    END SUBROUTINE cxios_get_field_freq_op

    FUNCTION cxios_is_defined_field_freq_op(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_freq_op
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_freq_op


    SUBROUTINE cxios_set_field_grid_path(field_hdl, grid_path, grid_path_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: grid_path
      INTEGER  (kind = C_INT)     , VALUE        :: grid_path_size
    END SUBROUTINE cxios_set_field_grid_path

    SUBROUTINE cxios_get_field_grid_path(field_hdl, grid_path, grid_path_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: grid_path
      INTEGER  (kind = C_INT)     , VALUE        :: grid_path_size
    END SUBROUTINE cxios_get_field_grid_path

    FUNCTION cxios_is_defined_field_grid_path(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_grid_path
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_grid_path


    SUBROUTINE cxios_set_field_grid_ref(field_hdl, grid_ref, grid_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: grid_ref
      INTEGER  (kind = C_INT)     , VALUE        :: grid_ref_size
    END SUBROUTINE cxios_set_field_grid_ref

    SUBROUTINE cxios_get_field_grid_ref(field_hdl, grid_ref, grid_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: grid_ref
      INTEGER  (kind = C_INT)     , VALUE        :: grid_ref_size
    END SUBROUTINE cxios_get_field_grid_ref

    FUNCTION cxios_is_defined_field_grid_ref(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_grid_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_grid_ref


    SUBROUTINE cxios_set_field_indexed_output(field_hdl, indexed_output) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: indexed_output
    END SUBROUTINE cxios_set_field_indexed_output

    SUBROUTINE cxios_get_field_indexed_output(field_hdl, indexed_output) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)             :: indexed_output
    END SUBROUTINE cxios_get_field_indexed_output

    FUNCTION cxios_is_defined_field_indexed_output(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_indexed_output
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_indexed_output


    SUBROUTINE cxios_set_field_level(field_hdl, level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      INTEGER (KIND=C_INT)      , VALUE :: level
    END SUBROUTINE cxios_set_field_level

    SUBROUTINE cxios_get_field_level(field_hdl, level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      INTEGER (KIND=C_INT)             :: level
    END SUBROUTINE cxios_get_field_level

    FUNCTION cxios_is_defined_field_level(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_level
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_level


    SUBROUTINE cxios_set_field_long_name(field_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_set_field_long_name

    SUBROUTINE cxios_get_field_long_name(field_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_get_field_long_name

    FUNCTION cxios_is_defined_field_long_name(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_long_name
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_long_name


    SUBROUTINE cxios_set_field_name(field_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_field_name

    SUBROUTINE cxios_get_field_name(field_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_field_name

    FUNCTION cxios_is_defined_field_name(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_name
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_name


    SUBROUTINE cxios_set_field_operation(field_hdl, operation, operation_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: operation
      INTEGER  (kind = C_INT)     , VALUE        :: operation_size
    END SUBROUTINE cxios_set_field_operation

    SUBROUTINE cxios_get_field_operation(field_hdl, operation, operation_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: operation
      INTEGER  (kind = C_INT)     , VALUE        :: operation_size
    END SUBROUTINE cxios_get_field_operation

    FUNCTION cxios_is_defined_field_operation(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_operation
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_operation


    SUBROUTINE cxios_set_field_prec(field_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      INTEGER (KIND=C_INT)      , VALUE :: prec
    END SUBROUTINE cxios_set_field_prec

    SUBROUTINE cxios_get_field_prec(field_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      INTEGER (KIND=C_INT)             :: prec
    END SUBROUTINE cxios_get_field_prec

    FUNCTION cxios_is_defined_field_prec(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_prec
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_prec


    SUBROUTINE cxios_set_field_read_access(field_hdl, read_access) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: read_access
    END SUBROUTINE cxios_set_field_read_access

    SUBROUTINE cxios_get_field_read_access(field_hdl, read_access) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)             :: read_access
    END SUBROUTINE cxios_get_field_read_access

    FUNCTION cxios_is_defined_field_read_access(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_read_access
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_read_access


    SUBROUTINE cxios_set_field_scalar_ref(field_hdl, scalar_ref, scalar_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: scalar_ref
      INTEGER  (kind = C_INT)     , VALUE        :: scalar_ref_size
    END SUBROUTINE cxios_set_field_scalar_ref

    SUBROUTINE cxios_get_field_scalar_ref(field_hdl, scalar_ref, scalar_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: scalar_ref
      INTEGER  (kind = C_INT)     , VALUE        :: scalar_ref_size
    END SUBROUTINE cxios_get_field_scalar_ref

    FUNCTION cxios_is_defined_field_scalar_ref(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_scalar_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_scalar_ref


    SUBROUTINE cxios_set_field_scale_factor(field_hdl, scale_factor) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: scale_factor
    END SUBROUTINE cxios_set_field_scale_factor

    SUBROUTINE cxios_get_field_scale_factor(field_hdl, scale_factor) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)             :: scale_factor
    END SUBROUTINE cxios_get_field_scale_factor

    FUNCTION cxios_is_defined_field_scale_factor(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_scale_factor
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_scale_factor


    SUBROUTINE cxios_set_field_standard_name(field_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_set_field_standard_name

    SUBROUTINE cxios_get_field_standard_name(field_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_get_field_standard_name

    FUNCTION cxios_is_defined_field_standard_name(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_standard_name
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_standard_name


    SUBROUTINE cxios_set_field_ts_enabled(field_hdl, ts_enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: ts_enabled
    END SUBROUTINE cxios_set_field_ts_enabled

    SUBROUTINE cxios_get_field_ts_enabled(field_hdl, ts_enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      LOGICAL (KIND=C_BOOL)             :: ts_enabled
    END SUBROUTINE cxios_get_field_ts_enabled

    FUNCTION cxios_is_defined_field_ts_enabled(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_ts_enabled
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_ts_enabled


    SUBROUTINE cxios_set_field_ts_split_freq(field_hdl, ts_split_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      TYPE(txios(duration)), VALUE :: ts_split_freq
    END SUBROUTINE cxios_set_field_ts_split_freq

    SUBROUTINE cxios_get_field_ts_split_freq(field_hdl, ts_split_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      TYPE(txios(duration)) :: ts_split_freq
    END SUBROUTINE cxios_get_field_ts_split_freq

    FUNCTION cxios_is_defined_field_ts_split_freq(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_ts_split_freq
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_ts_split_freq


    SUBROUTINE cxios_set_field_unit(field_hdl, unit, unit_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: unit
      INTEGER  (kind = C_INT)     , VALUE        :: unit_size
    END SUBROUTINE cxios_set_field_unit

    SUBROUTINE cxios_get_field_unit(field_hdl, unit, unit_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: unit
      INTEGER  (kind = C_INT)     , VALUE        :: unit_size
    END SUBROUTINE cxios_get_field_unit

    FUNCTION cxios_is_defined_field_unit(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_unit
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_unit


    SUBROUTINE cxios_set_field_valid_max(field_hdl, valid_max) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: valid_max
    END SUBROUTINE cxios_set_field_valid_max

    SUBROUTINE cxios_get_field_valid_max(field_hdl, valid_max) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)             :: valid_max
    END SUBROUTINE cxios_get_field_valid_max

    FUNCTION cxios_is_defined_field_valid_max(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_valid_max
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_valid_max


    SUBROUTINE cxios_set_field_valid_min(field_hdl, valid_min) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: valid_min
    END SUBROUTINE cxios_set_field_valid_min

    SUBROUTINE cxios_get_field_valid_min(field_hdl, valid_min) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
      REAL (KIND=C_DOUBLE)             :: valid_min
    END SUBROUTINE cxios_get_field_valid_min

    FUNCTION cxios_is_defined_field_valid_min(field_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_field_valid_min
      INTEGER (kind = C_INTPTR_T), VALUE :: field_hdl
    END FUNCTION cxios_is_defined_field_valid_min

  END INTERFACE

END MODULE field_interface_attr
