! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE axisgroup_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_axisgroup_axis_ref(axisgroup_hdl, axis_ref, axis_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_ref
      INTEGER  (kind = C_INT)     , VALUE        :: axis_ref_size
    END SUBROUTINE cxios_set_axisgroup_axis_ref

    SUBROUTINE cxios_get_axisgroup_axis_ref(axisgroup_hdl, axis_ref, axis_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_ref
      INTEGER  (kind = C_INT)     , VALUE        :: axis_ref_size
    END SUBROUTINE cxios_get_axisgroup_axis_ref

    FUNCTION cxios_is_defined_axisgroup_axis_ref(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_axis_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_axis_ref


    SUBROUTINE cxios_set_axisgroup_axis_type(axisgroup_hdl, axis_type, axis_type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_type
      INTEGER  (kind = C_INT)     , VALUE        :: axis_type_size
    END SUBROUTINE cxios_set_axisgroup_axis_type

    SUBROUTINE cxios_get_axisgroup_axis_type(axisgroup_hdl, axis_type, axis_type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_type
      INTEGER  (kind = C_INT)     , VALUE        :: axis_type_size
    END SUBROUTINE cxios_get_axisgroup_axis_type

    FUNCTION cxios_is_defined_axisgroup_axis_type(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_axis_type
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_axis_type


    SUBROUTINE cxios_set_axisgroup_begin(axisgroup_hdl, begin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: begin
    END SUBROUTINE cxios_set_axisgroup_begin

    SUBROUTINE cxios_get_axisgroup_begin(axisgroup_hdl, begin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)             :: begin
    END SUBROUTINE cxios_get_axisgroup_begin

    FUNCTION cxios_is_defined_axisgroup_begin(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_begin
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_begin


    SUBROUTINE cxios_set_axisgroup_bounds(axisgroup_hdl, bounds, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_axisgroup_bounds

    SUBROUTINE cxios_get_axisgroup_bounds(axisgroup_hdl, bounds, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_axisgroup_bounds

    FUNCTION cxios_is_defined_axisgroup_bounds(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_bounds
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_bounds


    SUBROUTINE cxios_set_axisgroup_bounds_name(axisgroup_hdl, bounds_name, bounds_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: bounds_name
      INTEGER  (kind = C_INT)     , VALUE        :: bounds_name_size
    END SUBROUTINE cxios_set_axisgroup_bounds_name

    SUBROUTINE cxios_get_axisgroup_bounds_name(axisgroup_hdl, bounds_name, bounds_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: bounds_name
      INTEGER  (kind = C_INT)     , VALUE        :: bounds_name_size
    END SUBROUTINE cxios_get_axisgroup_bounds_name

    FUNCTION cxios_is_defined_axisgroup_bounds_name(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_bounds_name
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_bounds_name


    SUBROUTINE cxios_set_axisgroup_comment(axisgroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_axisgroup_comment

    SUBROUTINE cxios_get_axisgroup_comment(axisgroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_axisgroup_comment

    FUNCTION cxios_is_defined_axisgroup_comment(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_comment


    SUBROUTINE cxios_set_axisgroup_data_begin(axisgroup_hdl, data_begin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: data_begin
    END SUBROUTINE cxios_set_axisgroup_data_begin

    SUBROUTINE cxios_get_axisgroup_data_begin(axisgroup_hdl, data_begin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)             :: data_begin
    END SUBROUTINE cxios_get_axisgroup_data_begin

    FUNCTION cxios_is_defined_axisgroup_data_begin(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_data_begin
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_data_begin


    SUBROUTINE cxios_set_axisgroup_data_index(axisgroup_hdl, data_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: data_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_axisgroup_data_index

    SUBROUTINE cxios_get_axisgroup_data_index(axisgroup_hdl, data_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: data_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_axisgroup_data_index

    FUNCTION cxios_is_defined_axisgroup_data_index(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_data_index
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_data_index


    SUBROUTINE cxios_set_axisgroup_data_n(axisgroup_hdl, data_n) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: data_n
    END SUBROUTINE cxios_set_axisgroup_data_n

    SUBROUTINE cxios_get_axisgroup_data_n(axisgroup_hdl, data_n) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)             :: data_n
    END SUBROUTINE cxios_get_axisgroup_data_n

    FUNCTION cxios_is_defined_axisgroup_data_n(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_data_n
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_data_n


    SUBROUTINE cxios_set_axisgroup_dim_name(axisgroup_hdl, dim_name, dim_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: dim_name
      INTEGER  (kind = C_INT)     , VALUE        :: dim_name_size
    END SUBROUTINE cxios_set_axisgroup_dim_name

    SUBROUTINE cxios_get_axisgroup_dim_name(axisgroup_hdl, dim_name, dim_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: dim_name
      INTEGER  (kind = C_INT)     , VALUE        :: dim_name_size
    END SUBROUTINE cxios_get_axisgroup_dim_name

    FUNCTION cxios_is_defined_axisgroup_dim_name(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_dim_name
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_dim_name


    SUBROUTINE cxios_set_axisgroup_formula(axisgroup_hdl, formula, formula_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: formula
      INTEGER  (kind = C_INT)     , VALUE        :: formula_size
    END SUBROUTINE cxios_set_axisgroup_formula

    SUBROUTINE cxios_get_axisgroup_formula(axisgroup_hdl, formula, formula_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: formula
      INTEGER  (kind = C_INT)     , VALUE        :: formula_size
    END SUBROUTINE cxios_get_axisgroup_formula

    FUNCTION cxios_is_defined_axisgroup_formula(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_formula
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_formula


    SUBROUTINE cxios_set_axisgroup_formula_bounds(axisgroup_hdl, formula_bounds, formula_bounds_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: formula_bounds
      INTEGER  (kind = C_INT)     , VALUE        :: formula_bounds_size
    END SUBROUTINE cxios_set_axisgroup_formula_bounds

    SUBROUTINE cxios_get_axisgroup_formula_bounds(axisgroup_hdl, formula_bounds, formula_bounds_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: formula_bounds
      INTEGER  (kind = C_INT)     , VALUE        :: formula_bounds_size
    END SUBROUTINE cxios_get_axisgroup_formula_bounds

    FUNCTION cxios_is_defined_axisgroup_formula_bounds(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_formula_bounds
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_formula_bounds


    SUBROUTINE cxios_set_axisgroup_formula_term(axisgroup_hdl, formula_term, formula_term_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: formula_term
      INTEGER  (kind = C_INT)     , VALUE        :: formula_term_size
    END SUBROUTINE cxios_set_axisgroup_formula_term

    SUBROUTINE cxios_get_axisgroup_formula_term(axisgroup_hdl, formula_term, formula_term_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: formula_term
      INTEGER  (kind = C_INT)     , VALUE        :: formula_term_size
    END SUBROUTINE cxios_get_axisgroup_formula_term

    FUNCTION cxios_is_defined_axisgroup_formula_term(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_formula_term
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_formula_term


    SUBROUTINE cxios_set_axisgroup_formula_term_bounds(axisgroup_hdl, formula_term_bounds, formula_term_bounds_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: formula_term_bounds
      INTEGER  (kind = C_INT)     , VALUE        :: formula_term_bounds_size
    END SUBROUTINE cxios_set_axisgroup_formula_term_bounds

    SUBROUTINE cxios_get_axisgroup_formula_term_bounds(axisgroup_hdl, formula_term_bounds, formula_term_bounds_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: formula_term_bounds
      INTEGER  (kind = C_INT)     , VALUE        :: formula_term_bounds_size
    END SUBROUTINE cxios_get_axisgroup_formula_term_bounds

    FUNCTION cxios_is_defined_axisgroup_formula_term_bounds(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_formula_term_bounds
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_formula_term_bounds


    SUBROUTINE cxios_set_axisgroup_group_ref(axisgroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_set_axisgroup_group_ref

    SUBROUTINE cxios_get_axisgroup_group_ref(axisgroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_get_axisgroup_group_ref

    FUNCTION cxios_is_defined_axisgroup_group_ref(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_group_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_group_ref


    SUBROUTINE cxios_set_axisgroup_index(axisgroup_hdl, index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_axisgroup_index

    SUBROUTINE cxios_get_axisgroup_index(axisgroup_hdl, index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_axisgroup_index

    FUNCTION cxios_is_defined_axisgroup_index(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_index
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_index


    SUBROUTINE cxios_set_axisgroup_label(axisgroup_hdl, label, str_len, str_size, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      CHARACTER (KIND=C_CHAR), DIMENSION(*)    :: label
      INTEGER (kind = C_INT), VALUE            :: str_len
      INTEGER (kind = C_INT), DIMENSION(*)     :: str_size
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_axisgroup_label

    SUBROUTINE cxios_get_axisgroup_label(axisgroup_hdl, label, str_size, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      CHARACTER (KIND=C_CHAR), DIMENSION(*)    :: label
      INTEGER (kind = C_INT), VALUE            :: str_size
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_axisgroup_label

    FUNCTION cxios_is_defined_axisgroup_label(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_label
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_label


    SUBROUTINE cxios_set_axisgroup_long_name(axisgroup_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_set_axisgroup_long_name

    SUBROUTINE cxios_get_axisgroup_long_name(axisgroup_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_get_axisgroup_long_name

    FUNCTION cxios_is_defined_axisgroup_long_name(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_long_name
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_long_name


    SUBROUTINE cxios_set_axisgroup_mask(axisgroup_hdl, mask, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_axisgroup_mask

    SUBROUTINE cxios_get_axisgroup_mask(axisgroup_hdl, mask, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_axisgroup_mask

    FUNCTION cxios_is_defined_axisgroup_mask(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_mask
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_mask


    SUBROUTINE cxios_set_axisgroup_n(axisgroup_hdl, n) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: n
    END SUBROUTINE cxios_set_axisgroup_n

    SUBROUTINE cxios_get_axisgroup_n(axisgroup_hdl, n) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)             :: n
    END SUBROUTINE cxios_get_axisgroup_n

    FUNCTION cxios_is_defined_axisgroup_n(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_n
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_n


    SUBROUTINE cxios_set_axisgroup_n_distributed_partition(axisgroup_hdl, n_distributed_partition) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: n_distributed_partition
    END SUBROUTINE cxios_set_axisgroup_n_distributed_partition

    SUBROUTINE cxios_get_axisgroup_n_distributed_partition(axisgroup_hdl, n_distributed_partition) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)             :: n_distributed_partition
    END SUBROUTINE cxios_get_axisgroup_n_distributed_partition

    FUNCTION cxios_is_defined_axisgroup_n_distributed_partition(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_n_distributed_partition
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_n_distributed_partition


    SUBROUTINE cxios_set_axisgroup_n_glo(axisgroup_hdl, n_glo) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: n_glo
    END SUBROUTINE cxios_set_axisgroup_n_glo

    SUBROUTINE cxios_get_axisgroup_n_glo(axisgroup_hdl, n_glo) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)             :: n_glo
    END SUBROUTINE cxios_get_axisgroup_n_glo

    FUNCTION cxios_is_defined_axisgroup_n_glo(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_n_glo
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_n_glo


    SUBROUTINE cxios_set_axisgroup_name(axisgroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_axisgroup_name

    SUBROUTINE cxios_get_axisgroup_name(axisgroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_axisgroup_name

    FUNCTION cxios_is_defined_axisgroup_name(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_name
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_name


    SUBROUTINE cxios_set_axisgroup_positive(axisgroup_hdl, positive, positive_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: positive
      INTEGER  (kind = C_INT)     , VALUE        :: positive_size
    END SUBROUTINE cxios_set_axisgroup_positive

    SUBROUTINE cxios_get_axisgroup_positive(axisgroup_hdl, positive, positive_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: positive
      INTEGER  (kind = C_INT)     , VALUE        :: positive_size
    END SUBROUTINE cxios_get_axisgroup_positive

    FUNCTION cxios_is_defined_axisgroup_positive(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_positive
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_positive


    SUBROUTINE cxios_set_axisgroup_prec(axisgroup_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: prec
    END SUBROUTINE cxios_set_axisgroup_prec

    SUBROUTINE cxios_get_axisgroup_prec(axisgroup_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      INTEGER (KIND=C_INT)             :: prec
    END SUBROUTINE cxios_get_axisgroup_prec

    FUNCTION cxios_is_defined_axisgroup_prec(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_prec
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_prec


    SUBROUTINE cxios_set_axisgroup_standard_name(axisgroup_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_set_axisgroup_standard_name

    SUBROUTINE cxios_get_axisgroup_standard_name(axisgroup_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_get_axisgroup_standard_name

    FUNCTION cxios_is_defined_axisgroup_standard_name(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_standard_name
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_standard_name


    SUBROUTINE cxios_set_axisgroup_unit(axisgroup_hdl, unit, unit_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: unit
      INTEGER  (kind = C_INT)     , VALUE        :: unit_size
    END SUBROUTINE cxios_set_axisgroup_unit

    SUBROUTINE cxios_get_axisgroup_unit(axisgroup_hdl, unit, unit_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: unit
      INTEGER  (kind = C_INT)     , VALUE        :: unit_size
    END SUBROUTINE cxios_get_axisgroup_unit

    FUNCTION cxios_is_defined_axisgroup_unit(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_unit
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_unit


    SUBROUTINE cxios_set_axisgroup_value(axisgroup_hdl, value, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: value
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_axisgroup_value

    SUBROUTINE cxios_get_axisgroup_value(axisgroup_hdl, value, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: axisgroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: value
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_axisgroup_value

    FUNCTION cxios_is_defined_axisgroup_value(axisgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_axisgroup_value
      INTEGER (kind = C_INTPTR_T), VALUE :: axisgroup_hdl
    END FUNCTION cxios_is_defined_axisgroup_value

  END INTERFACE

END MODULE axisgroup_interface_attr
