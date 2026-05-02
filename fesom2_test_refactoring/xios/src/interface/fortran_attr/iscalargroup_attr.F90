! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE iscalargroup_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE iscalar
  USE scalargroup_interface_attr

CONTAINS

  SUBROUTINE xios(set_scalargroup_attr)  &
    ( scalargroup_id, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
    , positive, prec, scalar_ref, standard_name, unit, value )

    IMPLICIT NONE
      TYPE(txios(scalargroup))  :: scalargroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::scalargroup_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: axis_type
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: label
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: positive
      INTEGER  , OPTIONAL, INTENT(IN) :: prec
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: scalar_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: unit
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: value

      CALL xios(get_scalargroup_handle) &
      (scalargroup_id,scalargroup_hdl)
      CALL xios(set_scalargroup_attr_hdl_)   &
      ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
      , positive, prec, scalar_ref, standard_name, unit, value )

  END SUBROUTINE xios(set_scalargroup_attr)

  SUBROUTINE xios(set_scalargroup_attr_hdl)  &
    ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
    , positive, prec, scalar_ref, standard_name, unit, value )

    IMPLICIT NONE
      TYPE(txios(scalargroup)) , INTENT(IN) :: scalargroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: axis_type
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: label
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: positive
      INTEGER  , OPTIONAL, INTENT(IN) :: prec
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: scalar_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: unit
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: value

      CALL xios(set_scalargroup_attr_hdl_)  &
      ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
      , positive, prec, scalar_ref, standard_name, unit, value )

  END SUBROUTINE xios(set_scalargroup_attr_hdl)

  SUBROUTINE xios(set_scalargroup_attr_hdl_)   &
    ( scalargroup_hdl, axis_type_, bounds_, bounds_name_, comment_, group_ref_, label_, long_name_  &
    , name_, positive_, prec_, scalar_ref_, standard_name_, unit_, value_ )

    IMPLICIT NONE
      TYPE(txios(scalargroup)) , INTENT(IN) :: scalargroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: axis_type_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: label_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: positive_
      INTEGER  , OPTIONAL, INTENT(IN) :: prec_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: scalar_ref_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: unit_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: value_

      IF (PRESENT(axis_type_)) THEN
        CALL cxios_set_scalargroup_axis_type &
      (scalargroup_hdl%daddr, axis_type_, len(axis_type_))
      ENDIF

      IF (PRESENT(bounds_)) THEN
        CALL cxios_set_scalargroup_bounds &
      (scalargroup_hdl%daddr, bounds_, SHAPE(bounds_))
      ENDIF

      IF (PRESENT(bounds_name_)) THEN
        CALL cxios_set_scalargroup_bounds_name &
      (scalargroup_hdl%daddr, bounds_name_, len(bounds_name_))
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_set_scalargroup_comment &
      (scalargroup_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        CALL cxios_set_scalargroup_group_ref &
      (scalargroup_hdl%daddr, group_ref_, len(group_ref_))
      ENDIF

      IF (PRESENT(label_)) THEN
        CALL cxios_set_scalargroup_label &
      (scalargroup_hdl%daddr, label_, len(label_))
      ENDIF

      IF (PRESENT(long_name_)) THEN
        CALL cxios_set_scalargroup_long_name &
      (scalargroup_hdl%daddr, long_name_, len(long_name_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_set_scalargroup_name &
      (scalargroup_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(positive_)) THEN
        CALL cxios_set_scalargroup_positive &
      (scalargroup_hdl%daddr, positive_, len(positive_))
      ENDIF

      IF (PRESENT(prec_)) THEN
        CALL cxios_set_scalargroup_prec &
      (scalargroup_hdl%daddr, prec_)
      ENDIF

      IF (PRESENT(scalar_ref_)) THEN
        CALL cxios_set_scalargroup_scalar_ref &
      (scalargroup_hdl%daddr, scalar_ref_, len(scalar_ref_))
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        CALL cxios_set_scalargroup_standard_name &
      (scalargroup_hdl%daddr, standard_name_, len(standard_name_))
      ENDIF

      IF (PRESENT(unit_)) THEN
        CALL cxios_set_scalargroup_unit &
      (scalargroup_hdl%daddr, unit_, len(unit_))
      ENDIF

      IF (PRESENT(value_)) THEN
        CALL cxios_set_scalargroup_value &
      (scalargroup_hdl%daddr, value_)
      ENDIF

  END SUBROUTINE xios(set_scalargroup_attr_hdl_)

  SUBROUTINE xios(get_scalargroup_attr)  &
    ( scalargroup_id, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
    , positive, prec, scalar_ref, standard_name, unit, value )

    IMPLICIT NONE
      TYPE(txios(scalargroup))  :: scalargroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::scalargroup_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: axis_type
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: label
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: positive
      INTEGER  , OPTIONAL, INTENT(OUT) :: prec
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: scalar_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: unit
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: value

      CALL xios(get_scalargroup_handle) &
      (scalargroup_id,scalargroup_hdl)
      CALL xios(get_scalargroup_attr_hdl_)   &
      ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
      , positive, prec, scalar_ref, standard_name, unit, value )

  END SUBROUTINE xios(get_scalargroup_attr)

  SUBROUTINE xios(get_scalargroup_attr_hdl)  &
    ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
    , positive, prec, scalar_ref, standard_name, unit, value )

    IMPLICIT NONE
      TYPE(txios(scalargroup)) , INTENT(IN) :: scalargroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: axis_type
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: label
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: positive
      INTEGER  , OPTIONAL, INTENT(OUT) :: prec
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: scalar_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: unit
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: value

      CALL xios(get_scalargroup_attr_hdl_)  &
      ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
      , positive, prec, scalar_ref, standard_name, unit, value )

  END SUBROUTINE xios(get_scalargroup_attr_hdl)

  SUBROUTINE xios(get_scalargroup_attr_hdl_)   &
    ( scalargroup_hdl, axis_type_, bounds_, bounds_name_, comment_, group_ref_, label_, long_name_  &
    , name_, positive_, prec_, scalar_ref_, standard_name_, unit_, value_ )

    IMPLICIT NONE
      TYPE(txios(scalargroup)) , INTENT(IN) :: scalargroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: axis_type_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: label_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: positive_
      INTEGER  , OPTIONAL, INTENT(OUT) :: prec_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: scalar_ref_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: unit_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: value_

      IF (PRESENT(axis_type_)) THEN
        CALL cxios_get_scalargroup_axis_type &
      (scalargroup_hdl%daddr, axis_type_, len(axis_type_))
      ENDIF

      IF (PRESENT(bounds_)) THEN
        CALL cxios_get_scalargroup_bounds &
      (scalargroup_hdl%daddr, bounds_, SHAPE(bounds_))
      ENDIF

      IF (PRESENT(bounds_name_)) THEN
        CALL cxios_get_scalargroup_bounds_name &
      (scalargroup_hdl%daddr, bounds_name_, len(bounds_name_))
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_get_scalargroup_comment &
      (scalargroup_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        CALL cxios_get_scalargroup_group_ref &
      (scalargroup_hdl%daddr, group_ref_, len(group_ref_))
      ENDIF

      IF (PRESENT(label_)) THEN
        CALL cxios_get_scalargroup_label &
      (scalargroup_hdl%daddr, label_, len(label_))
      ENDIF

      IF (PRESENT(long_name_)) THEN
        CALL cxios_get_scalargroup_long_name &
      (scalargroup_hdl%daddr, long_name_, len(long_name_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_get_scalargroup_name &
      (scalargroup_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(positive_)) THEN
        CALL cxios_get_scalargroup_positive &
      (scalargroup_hdl%daddr, positive_, len(positive_))
      ENDIF

      IF (PRESENT(prec_)) THEN
        CALL cxios_get_scalargroup_prec &
      (scalargroup_hdl%daddr, prec_)
      ENDIF

      IF (PRESENT(scalar_ref_)) THEN
        CALL cxios_get_scalargroup_scalar_ref &
      (scalargroup_hdl%daddr, scalar_ref_, len(scalar_ref_))
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        CALL cxios_get_scalargroup_standard_name &
      (scalargroup_hdl%daddr, standard_name_, len(standard_name_))
      ENDIF

      IF (PRESENT(unit_)) THEN
        CALL cxios_get_scalargroup_unit &
      (scalargroup_hdl%daddr, unit_, len(unit_))
      ENDIF

      IF (PRESENT(value_)) THEN
        CALL cxios_get_scalargroup_value &
      (scalargroup_hdl%daddr, value_)
      ENDIF

  END SUBROUTINE xios(get_scalargroup_attr_hdl_)

  SUBROUTINE xios(is_defined_scalargroup_attr)  &
    ( scalargroup_id, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
    , positive, prec, scalar_ref, standard_name, unit, value )

    IMPLICIT NONE
      TYPE(txios(scalargroup))  :: scalargroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::scalargroup_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: axis_type
      LOGICAL(KIND=C_BOOL) :: axis_type_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds
      LOGICAL(KIND=C_BOOL) :: bounds_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_name
      LOGICAL(KIND=C_BOOL) :: bounds_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL(KIND=C_BOOL) :: group_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: label
      LOGICAL(KIND=C_BOOL) :: label_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name
      LOGICAL(KIND=C_BOOL) :: long_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: positive
      LOGICAL(KIND=C_BOOL) :: positive_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: prec
      LOGICAL(KIND=C_BOOL) :: prec_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: scalar_ref
      LOGICAL(KIND=C_BOOL) :: scalar_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name
      LOGICAL(KIND=C_BOOL) :: standard_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: unit
      LOGICAL(KIND=C_BOOL) :: unit_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: value
      LOGICAL(KIND=C_BOOL) :: value_tmp

      CALL xios(get_scalargroup_handle) &
      (scalargroup_id,scalargroup_hdl)
      CALL xios(is_defined_scalargroup_attr_hdl_)   &
      ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
      , positive, prec, scalar_ref, standard_name, unit, value )

  END SUBROUTINE xios(is_defined_scalargroup_attr)

  SUBROUTINE xios(is_defined_scalargroup_attr_hdl)  &
    ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
    , positive, prec, scalar_ref, standard_name, unit, value )

    IMPLICIT NONE
      TYPE(txios(scalargroup)) , INTENT(IN) :: scalargroup_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: axis_type
      LOGICAL(KIND=C_BOOL) :: axis_type_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds
      LOGICAL(KIND=C_BOOL) :: bounds_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_name
      LOGICAL(KIND=C_BOOL) :: bounds_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL(KIND=C_BOOL) :: group_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: label
      LOGICAL(KIND=C_BOOL) :: label_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name
      LOGICAL(KIND=C_BOOL) :: long_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: positive
      LOGICAL(KIND=C_BOOL) :: positive_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: prec
      LOGICAL(KIND=C_BOOL) :: prec_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: scalar_ref
      LOGICAL(KIND=C_BOOL) :: scalar_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name
      LOGICAL(KIND=C_BOOL) :: standard_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: unit
      LOGICAL(KIND=C_BOOL) :: unit_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: value
      LOGICAL(KIND=C_BOOL) :: value_tmp

      CALL xios(is_defined_scalargroup_attr_hdl_)  &
      ( scalargroup_hdl, axis_type, bounds, bounds_name, comment, group_ref, label, long_name, name  &
      , positive, prec, scalar_ref, standard_name, unit, value )

  END SUBROUTINE xios(is_defined_scalargroup_attr_hdl)

  SUBROUTINE xios(is_defined_scalargroup_attr_hdl_)   &
    ( scalargroup_hdl, axis_type_, bounds_, bounds_name_, comment_, group_ref_, label_, long_name_  &
    , name_, positive_, prec_, scalar_ref_, standard_name_, unit_, value_ )

    IMPLICIT NONE
      TYPE(txios(scalargroup)) , INTENT(IN) :: scalargroup_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: axis_type_
      LOGICAL(KIND=C_BOOL) :: axis_type__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_
      LOGICAL(KIND=C_BOOL) :: bounds__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_name_
      LOGICAL(KIND=C_BOOL) :: bounds_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment_
      LOGICAL(KIND=C_BOOL) :: comment__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref_
      LOGICAL(KIND=C_BOOL) :: group_ref__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: label_
      LOGICAL(KIND=C_BOOL) :: label__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name_
      LOGICAL(KIND=C_BOOL) :: long_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_
      LOGICAL(KIND=C_BOOL) :: name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: positive_
      LOGICAL(KIND=C_BOOL) :: positive__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: prec_
      LOGICAL(KIND=C_BOOL) :: prec__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: scalar_ref_
      LOGICAL(KIND=C_BOOL) :: scalar_ref__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name_
      LOGICAL(KIND=C_BOOL) :: standard_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: unit_
      LOGICAL(KIND=C_BOOL) :: unit__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: value_
      LOGICAL(KIND=C_BOOL) :: value__tmp

      IF (PRESENT(axis_type_)) THEN
        axis_type__tmp = cxios_is_defined_scalargroup_axis_type &
      (scalargroup_hdl%daddr)
        axis_type_ = axis_type__tmp
      ENDIF

      IF (PRESENT(bounds_)) THEN
        bounds__tmp = cxios_is_defined_scalargroup_bounds &
      (scalargroup_hdl%daddr)
        bounds_ = bounds__tmp
      ENDIF

      IF (PRESENT(bounds_name_)) THEN
        bounds_name__tmp = cxios_is_defined_scalargroup_bounds_name &
      (scalargroup_hdl%daddr)
        bounds_name_ = bounds_name__tmp
      ENDIF

      IF (PRESENT(comment_)) THEN
        comment__tmp = cxios_is_defined_scalargroup_comment &
      (scalargroup_hdl%daddr)
        comment_ = comment__tmp
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        group_ref__tmp = cxios_is_defined_scalargroup_group_ref &
      (scalargroup_hdl%daddr)
        group_ref_ = group_ref__tmp
      ENDIF

      IF (PRESENT(label_)) THEN
        label__tmp = cxios_is_defined_scalargroup_label &
      (scalargroup_hdl%daddr)
        label_ = label__tmp
      ENDIF

      IF (PRESENT(long_name_)) THEN
        long_name__tmp = cxios_is_defined_scalargroup_long_name &
      (scalargroup_hdl%daddr)
        long_name_ = long_name__tmp
      ENDIF

      IF (PRESENT(name_)) THEN
        name__tmp = cxios_is_defined_scalargroup_name &
      (scalargroup_hdl%daddr)
        name_ = name__tmp
      ENDIF

      IF (PRESENT(positive_)) THEN
        positive__tmp = cxios_is_defined_scalargroup_positive &
      (scalargroup_hdl%daddr)
        positive_ = positive__tmp
      ENDIF

      IF (PRESENT(prec_)) THEN
        prec__tmp = cxios_is_defined_scalargroup_prec &
      (scalargroup_hdl%daddr)
        prec_ = prec__tmp
      ENDIF

      IF (PRESENT(scalar_ref_)) THEN
        scalar_ref__tmp = cxios_is_defined_scalargroup_scalar_ref &
      (scalargroup_hdl%daddr)
        scalar_ref_ = scalar_ref__tmp
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        standard_name__tmp = cxios_is_defined_scalargroup_standard_name &
      (scalargroup_hdl%daddr)
        standard_name_ = standard_name__tmp
      ENDIF

      IF (PRESENT(unit_)) THEN
        unit__tmp = cxios_is_defined_scalargroup_unit &
      (scalargroup_hdl%daddr)
        unit_ = unit__tmp
      ENDIF

      IF (PRESENT(value_)) THEN
        value__tmp = cxios_is_defined_scalargroup_value &
      (scalargroup_hdl%daddr)
        value_ = value__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_scalargroup_attr_hdl_)

END MODULE iscalargroup_attr
