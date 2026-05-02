! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE scalar_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_scalar_axis_type(scalar_hdl, axis_type, axis_type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_type
      INTEGER  (kind = C_INT)     , VALUE        :: axis_type_size
    END SUBROUTINE cxios_set_scalar_axis_type

    SUBROUTINE cxios_get_scalar_axis_type(scalar_hdl, axis_type, axis_type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: axis_type
      INTEGER  (kind = C_INT)     , VALUE        :: axis_type_size
    END SUBROUTINE cxios_get_scalar_axis_type

    FUNCTION cxios_is_defined_scalar_axis_type(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_axis_type
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_axis_type


    SUBROUTINE cxios_set_scalar_bounds(scalar_hdl, bounds, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: scalar_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_scalar_bounds

    SUBROUTINE cxios_get_scalar_bounds(scalar_hdl, bounds, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: scalar_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_scalar_bounds

    FUNCTION cxios_is_defined_scalar_bounds(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_bounds
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_bounds


    SUBROUTINE cxios_set_scalar_bounds_name(scalar_hdl, bounds_name, bounds_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: bounds_name
      INTEGER  (kind = C_INT)     , VALUE        :: bounds_name_size
    END SUBROUTINE cxios_set_scalar_bounds_name

    SUBROUTINE cxios_get_scalar_bounds_name(scalar_hdl, bounds_name, bounds_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: bounds_name
      INTEGER  (kind = C_INT)     , VALUE        :: bounds_name_size
    END SUBROUTINE cxios_get_scalar_bounds_name

    FUNCTION cxios_is_defined_scalar_bounds_name(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_bounds_name
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_bounds_name


    SUBROUTINE cxios_set_scalar_comment(scalar_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_scalar_comment

    SUBROUTINE cxios_get_scalar_comment(scalar_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_scalar_comment

    FUNCTION cxios_is_defined_scalar_comment(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_comment


    SUBROUTINE cxios_set_scalar_label(scalar_hdl, label, label_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: label
      INTEGER  (kind = C_INT)     , VALUE        :: label_size
    END SUBROUTINE cxios_set_scalar_label

    SUBROUTINE cxios_get_scalar_label(scalar_hdl, label, label_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: label
      INTEGER  (kind = C_INT)     , VALUE        :: label_size
    END SUBROUTINE cxios_get_scalar_label

    FUNCTION cxios_is_defined_scalar_label(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_label
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_label


    SUBROUTINE cxios_set_scalar_long_name(scalar_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_set_scalar_long_name

    SUBROUTINE cxios_get_scalar_long_name(scalar_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_get_scalar_long_name

    FUNCTION cxios_is_defined_scalar_long_name(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_long_name
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_long_name


    SUBROUTINE cxios_set_scalar_name(scalar_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_scalar_name

    SUBROUTINE cxios_get_scalar_name(scalar_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_scalar_name

    FUNCTION cxios_is_defined_scalar_name(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_name
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_name


    SUBROUTINE cxios_set_scalar_positive(scalar_hdl, positive, positive_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: positive
      INTEGER  (kind = C_INT)     , VALUE        :: positive_size
    END SUBROUTINE cxios_set_scalar_positive

    SUBROUTINE cxios_get_scalar_positive(scalar_hdl, positive, positive_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: positive
      INTEGER  (kind = C_INT)     , VALUE        :: positive_size
    END SUBROUTINE cxios_get_scalar_positive

    FUNCTION cxios_is_defined_scalar_positive(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_positive
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_positive


    SUBROUTINE cxios_set_scalar_prec(scalar_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      INTEGER (KIND=C_INT)      , VALUE :: prec
    END SUBROUTINE cxios_set_scalar_prec

    SUBROUTINE cxios_get_scalar_prec(scalar_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      INTEGER (KIND=C_INT)             :: prec
    END SUBROUTINE cxios_get_scalar_prec

    FUNCTION cxios_is_defined_scalar_prec(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_prec
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_prec


    SUBROUTINE cxios_set_scalar_scalar_ref(scalar_hdl, scalar_ref, scalar_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: scalar_ref
      INTEGER  (kind = C_INT)     , VALUE        :: scalar_ref_size
    END SUBROUTINE cxios_set_scalar_scalar_ref

    SUBROUTINE cxios_get_scalar_scalar_ref(scalar_hdl, scalar_ref, scalar_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: scalar_ref
      INTEGER  (kind = C_INT)     , VALUE        :: scalar_ref_size
    END SUBROUTINE cxios_get_scalar_scalar_ref

    FUNCTION cxios_is_defined_scalar_scalar_ref(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_scalar_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_scalar_ref


    SUBROUTINE cxios_set_scalar_standard_name(scalar_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_set_scalar_standard_name

    SUBROUTINE cxios_get_scalar_standard_name(scalar_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_get_scalar_standard_name

    FUNCTION cxios_is_defined_scalar_standard_name(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_standard_name
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_standard_name


    SUBROUTINE cxios_set_scalar_unit(scalar_hdl, unit, unit_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: unit
      INTEGER  (kind = C_INT)     , VALUE        :: unit_size
    END SUBROUTINE cxios_set_scalar_unit

    SUBROUTINE cxios_get_scalar_unit(scalar_hdl, unit, unit_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: unit
      INTEGER  (kind = C_INT)     , VALUE        :: unit_size
    END SUBROUTINE cxios_get_scalar_unit

    FUNCTION cxios_is_defined_scalar_unit(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_unit
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_unit


    SUBROUTINE cxios_set_scalar_value(scalar_hdl, value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: value
    END SUBROUTINE cxios_set_scalar_value

    SUBROUTINE cxios_get_scalar_value(scalar_hdl, value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
      REAL (KIND=C_DOUBLE)             :: value
    END SUBROUTINE cxios_get_scalar_value

    FUNCTION cxios_is_defined_scalar_value(scalar_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_scalar_value
      INTEGER (kind = C_INTPTR_T), VALUE :: scalar_hdl
    END FUNCTION cxios_is_defined_scalar_value

  END INTERFACE

END MODULE scalar_interface_attr
