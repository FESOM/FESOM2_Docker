! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE iinterpolate_domain_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE iinterpolate_domain
  USE interpolate_domain_interface_attr

CONTAINS

  SUBROUTINE xios(set_interpolate_domain_attr)  &
    ( interpolate_domain_id, detect_missing_value, mode, order, quantity, read_write_convention  &
    , renormalize, use_area, weight_filename, write_weight )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain))  :: interpolate_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::interpolate_domain_id
      LOGICAL  , OPTIONAL, INTENT(IN) :: detect_missing_value
      LOGICAL (KIND=C_BOOL) :: detect_missing_value_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: mode
      INTEGER  , OPTIONAL, INTENT(IN) :: order
      LOGICAL  , OPTIONAL, INTENT(IN) :: quantity
      LOGICAL (KIND=C_BOOL) :: quantity_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: read_write_convention
      LOGICAL  , OPTIONAL, INTENT(IN) :: renormalize
      LOGICAL (KIND=C_BOOL) :: renormalize_tmp
      LOGICAL  , OPTIONAL, INTENT(IN) :: use_area
      LOGICAL (KIND=C_BOOL) :: use_area_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: weight_filename
      LOGICAL  , OPTIONAL, INTENT(IN) :: write_weight
      LOGICAL (KIND=C_BOOL) :: write_weight_tmp

      CALL xios(get_interpolate_domain_handle) &
      (interpolate_domain_id,interpolate_domain_hdl)
      CALL xios(set_interpolate_domain_attr_hdl_)   &
      ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
      , renormalize, use_area, weight_filename, write_weight )

  END SUBROUTINE xios(set_interpolate_domain_attr)

  SUBROUTINE xios(set_interpolate_domain_attr_hdl)  &
    ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
    , renormalize, use_area, weight_filename, write_weight )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain)) , INTENT(IN) :: interpolate_domain_hdl
      LOGICAL  , OPTIONAL, INTENT(IN) :: detect_missing_value
      LOGICAL (KIND=C_BOOL) :: detect_missing_value_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: mode
      INTEGER  , OPTIONAL, INTENT(IN) :: order
      LOGICAL  , OPTIONAL, INTENT(IN) :: quantity
      LOGICAL (KIND=C_BOOL) :: quantity_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: read_write_convention
      LOGICAL  , OPTIONAL, INTENT(IN) :: renormalize
      LOGICAL (KIND=C_BOOL) :: renormalize_tmp
      LOGICAL  , OPTIONAL, INTENT(IN) :: use_area
      LOGICAL (KIND=C_BOOL) :: use_area_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: weight_filename
      LOGICAL  , OPTIONAL, INTENT(IN) :: write_weight
      LOGICAL (KIND=C_BOOL) :: write_weight_tmp

      CALL xios(set_interpolate_domain_attr_hdl_)  &
      ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
      , renormalize, use_area, weight_filename, write_weight )

  END SUBROUTINE xios(set_interpolate_domain_attr_hdl)

  SUBROUTINE xios(set_interpolate_domain_attr_hdl_)   &
    ( interpolate_domain_hdl, detect_missing_value_, mode_, order_, quantity_, read_write_convention_  &
    , renormalize_, use_area_, weight_filename_, write_weight_ )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain)) , INTENT(IN) :: interpolate_domain_hdl
      LOGICAL  , OPTIONAL, INTENT(IN) :: detect_missing_value_
      LOGICAL (KIND=C_BOOL) :: detect_missing_value__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: mode_
      INTEGER  , OPTIONAL, INTENT(IN) :: order_
      LOGICAL  , OPTIONAL, INTENT(IN) :: quantity_
      LOGICAL (KIND=C_BOOL) :: quantity__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: read_write_convention_
      LOGICAL  , OPTIONAL, INTENT(IN) :: renormalize_
      LOGICAL (KIND=C_BOOL) :: renormalize__tmp
      LOGICAL  , OPTIONAL, INTENT(IN) :: use_area_
      LOGICAL (KIND=C_BOOL) :: use_area__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: weight_filename_
      LOGICAL  , OPTIONAL, INTENT(IN) :: write_weight_
      LOGICAL (KIND=C_BOOL) :: write_weight__tmp

      IF (PRESENT(detect_missing_value_)) THEN
        detect_missing_value__tmp = detect_missing_value_
        CALL cxios_set_interpolate_domain_detect_missing_value &
      (interpolate_domain_hdl%daddr, detect_missing_value__tmp)
      ENDIF

      IF (PRESENT(mode_)) THEN
        CALL cxios_set_interpolate_domain_mode &
      (interpolate_domain_hdl%daddr, mode_, len(mode_))
      ENDIF

      IF (PRESENT(order_)) THEN
        CALL cxios_set_interpolate_domain_order &
      (interpolate_domain_hdl%daddr, order_)
      ENDIF

      IF (PRESENT(quantity_)) THEN
        quantity__tmp = quantity_
        CALL cxios_set_interpolate_domain_quantity &
      (interpolate_domain_hdl%daddr, quantity__tmp)
      ENDIF

      IF (PRESENT(read_write_convention_)) THEN
        CALL cxios_set_interpolate_domain_read_write_convention &
      (interpolate_domain_hdl%daddr, read_write_convention_, len(read_write_convention_))
      ENDIF

      IF (PRESENT(renormalize_)) THEN
        renormalize__tmp = renormalize_
        CALL cxios_set_interpolate_domain_renormalize &
      (interpolate_domain_hdl%daddr, renormalize__tmp)
      ENDIF

      IF (PRESENT(use_area_)) THEN
        use_area__tmp = use_area_
        CALL cxios_set_interpolate_domain_use_area &
      (interpolate_domain_hdl%daddr, use_area__tmp)
      ENDIF

      IF (PRESENT(weight_filename_)) THEN
        CALL cxios_set_interpolate_domain_weight_filename &
      (interpolate_domain_hdl%daddr, weight_filename_, len(weight_filename_))
      ENDIF

      IF (PRESENT(write_weight_)) THEN
        write_weight__tmp = write_weight_
        CALL cxios_set_interpolate_domain_write_weight &
      (interpolate_domain_hdl%daddr, write_weight__tmp)
      ENDIF

  END SUBROUTINE xios(set_interpolate_domain_attr_hdl_)

  SUBROUTINE xios(get_interpolate_domain_attr)  &
    ( interpolate_domain_id, detect_missing_value, mode, order, quantity, read_write_convention  &
    , renormalize, use_area, weight_filename, write_weight )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain))  :: interpolate_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::interpolate_domain_id
      LOGICAL  , OPTIONAL, INTENT(OUT) :: detect_missing_value
      LOGICAL (KIND=C_BOOL) :: detect_missing_value_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: mode
      INTEGER  , OPTIONAL, INTENT(OUT) :: order
      LOGICAL  , OPTIONAL, INTENT(OUT) :: quantity
      LOGICAL (KIND=C_BOOL) :: quantity_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: read_write_convention
      LOGICAL  , OPTIONAL, INTENT(OUT) :: renormalize
      LOGICAL (KIND=C_BOOL) :: renormalize_tmp
      LOGICAL  , OPTIONAL, INTENT(OUT) :: use_area
      LOGICAL (KIND=C_BOOL) :: use_area_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: weight_filename
      LOGICAL  , OPTIONAL, INTENT(OUT) :: write_weight
      LOGICAL (KIND=C_BOOL) :: write_weight_tmp

      CALL xios(get_interpolate_domain_handle) &
      (interpolate_domain_id,interpolate_domain_hdl)
      CALL xios(get_interpolate_domain_attr_hdl_)   &
      ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
      , renormalize, use_area, weight_filename, write_weight )

  END SUBROUTINE xios(get_interpolate_domain_attr)

  SUBROUTINE xios(get_interpolate_domain_attr_hdl)  &
    ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
    , renormalize, use_area, weight_filename, write_weight )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain)) , INTENT(IN) :: interpolate_domain_hdl
      LOGICAL  , OPTIONAL, INTENT(OUT) :: detect_missing_value
      LOGICAL (KIND=C_BOOL) :: detect_missing_value_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: mode
      INTEGER  , OPTIONAL, INTENT(OUT) :: order
      LOGICAL  , OPTIONAL, INTENT(OUT) :: quantity
      LOGICAL (KIND=C_BOOL) :: quantity_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: read_write_convention
      LOGICAL  , OPTIONAL, INTENT(OUT) :: renormalize
      LOGICAL (KIND=C_BOOL) :: renormalize_tmp
      LOGICAL  , OPTIONAL, INTENT(OUT) :: use_area
      LOGICAL (KIND=C_BOOL) :: use_area_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: weight_filename
      LOGICAL  , OPTIONAL, INTENT(OUT) :: write_weight
      LOGICAL (KIND=C_BOOL) :: write_weight_tmp

      CALL xios(get_interpolate_domain_attr_hdl_)  &
      ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
      , renormalize, use_area, weight_filename, write_weight )

  END SUBROUTINE xios(get_interpolate_domain_attr_hdl)

  SUBROUTINE xios(get_interpolate_domain_attr_hdl_)   &
    ( interpolate_domain_hdl, detect_missing_value_, mode_, order_, quantity_, read_write_convention_  &
    , renormalize_, use_area_, weight_filename_, write_weight_ )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain)) , INTENT(IN) :: interpolate_domain_hdl
      LOGICAL  , OPTIONAL, INTENT(OUT) :: detect_missing_value_
      LOGICAL (KIND=C_BOOL) :: detect_missing_value__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: mode_
      INTEGER  , OPTIONAL, INTENT(OUT) :: order_
      LOGICAL  , OPTIONAL, INTENT(OUT) :: quantity_
      LOGICAL (KIND=C_BOOL) :: quantity__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: read_write_convention_
      LOGICAL  , OPTIONAL, INTENT(OUT) :: renormalize_
      LOGICAL (KIND=C_BOOL) :: renormalize__tmp
      LOGICAL  , OPTIONAL, INTENT(OUT) :: use_area_
      LOGICAL (KIND=C_BOOL) :: use_area__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: weight_filename_
      LOGICAL  , OPTIONAL, INTENT(OUT) :: write_weight_
      LOGICAL (KIND=C_BOOL) :: write_weight__tmp

      IF (PRESENT(detect_missing_value_)) THEN
        CALL cxios_get_interpolate_domain_detect_missing_value &
      (interpolate_domain_hdl%daddr, detect_missing_value__tmp)
        detect_missing_value_ = detect_missing_value__tmp
      ENDIF

      IF (PRESENT(mode_)) THEN
        CALL cxios_get_interpolate_domain_mode &
      (interpolate_domain_hdl%daddr, mode_, len(mode_))
      ENDIF

      IF (PRESENT(order_)) THEN
        CALL cxios_get_interpolate_domain_order &
      (interpolate_domain_hdl%daddr, order_)
      ENDIF

      IF (PRESENT(quantity_)) THEN
        CALL cxios_get_interpolate_domain_quantity &
      (interpolate_domain_hdl%daddr, quantity__tmp)
        quantity_ = quantity__tmp
      ENDIF

      IF (PRESENT(read_write_convention_)) THEN
        CALL cxios_get_interpolate_domain_read_write_convention &
      (interpolate_domain_hdl%daddr, read_write_convention_, len(read_write_convention_))
      ENDIF

      IF (PRESENT(renormalize_)) THEN
        CALL cxios_get_interpolate_domain_renormalize &
      (interpolate_domain_hdl%daddr, renormalize__tmp)
        renormalize_ = renormalize__tmp
      ENDIF

      IF (PRESENT(use_area_)) THEN
        CALL cxios_get_interpolate_domain_use_area &
      (interpolate_domain_hdl%daddr, use_area__tmp)
        use_area_ = use_area__tmp
      ENDIF

      IF (PRESENT(weight_filename_)) THEN
        CALL cxios_get_interpolate_domain_weight_filename &
      (interpolate_domain_hdl%daddr, weight_filename_, len(weight_filename_))
      ENDIF

      IF (PRESENT(write_weight_)) THEN
        CALL cxios_get_interpolate_domain_write_weight &
      (interpolate_domain_hdl%daddr, write_weight__tmp)
        write_weight_ = write_weight__tmp
      ENDIF

  END SUBROUTINE xios(get_interpolate_domain_attr_hdl_)

  SUBROUTINE xios(is_defined_interpolate_domain_attr)  &
    ( interpolate_domain_id, detect_missing_value, mode, order, quantity, read_write_convention  &
    , renormalize, use_area, weight_filename, write_weight )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain))  :: interpolate_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::interpolate_domain_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: detect_missing_value
      LOGICAL(KIND=C_BOOL) :: detect_missing_value_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mode
      LOGICAL(KIND=C_BOOL) :: mode_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: order
      LOGICAL(KIND=C_BOOL) :: order_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: quantity
      LOGICAL(KIND=C_BOOL) :: quantity_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: read_write_convention
      LOGICAL(KIND=C_BOOL) :: read_write_convention_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: renormalize
      LOGICAL(KIND=C_BOOL) :: renormalize_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: use_area
      LOGICAL(KIND=C_BOOL) :: use_area_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: weight_filename
      LOGICAL(KIND=C_BOOL) :: weight_filename_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: write_weight
      LOGICAL(KIND=C_BOOL) :: write_weight_tmp

      CALL xios(get_interpolate_domain_handle) &
      (interpolate_domain_id,interpolate_domain_hdl)
      CALL xios(is_defined_interpolate_domain_attr_hdl_)   &
      ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
      , renormalize, use_area, weight_filename, write_weight )

  END SUBROUTINE xios(is_defined_interpolate_domain_attr)

  SUBROUTINE xios(is_defined_interpolate_domain_attr_hdl)  &
    ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
    , renormalize, use_area, weight_filename, write_weight )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain)) , INTENT(IN) :: interpolate_domain_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: detect_missing_value
      LOGICAL(KIND=C_BOOL) :: detect_missing_value_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mode
      LOGICAL(KIND=C_BOOL) :: mode_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: order
      LOGICAL(KIND=C_BOOL) :: order_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: quantity
      LOGICAL(KIND=C_BOOL) :: quantity_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: read_write_convention
      LOGICAL(KIND=C_BOOL) :: read_write_convention_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: renormalize
      LOGICAL(KIND=C_BOOL) :: renormalize_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: use_area
      LOGICAL(KIND=C_BOOL) :: use_area_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: weight_filename
      LOGICAL(KIND=C_BOOL) :: weight_filename_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: write_weight
      LOGICAL(KIND=C_BOOL) :: write_weight_tmp

      CALL xios(is_defined_interpolate_domain_attr_hdl_)  &
      ( interpolate_domain_hdl, detect_missing_value, mode, order, quantity, read_write_convention  &
      , renormalize, use_area, weight_filename, write_weight )

  END SUBROUTINE xios(is_defined_interpolate_domain_attr_hdl)

  SUBROUTINE xios(is_defined_interpolate_domain_attr_hdl_)   &
    ( interpolate_domain_hdl, detect_missing_value_, mode_, order_, quantity_, read_write_convention_  &
    , renormalize_, use_area_, weight_filename_, write_weight_ )

    IMPLICIT NONE
      TYPE(txios(interpolate_domain)) , INTENT(IN) :: interpolate_domain_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: detect_missing_value_
      LOGICAL(KIND=C_BOOL) :: detect_missing_value__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mode_
      LOGICAL(KIND=C_BOOL) :: mode__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: order_
      LOGICAL(KIND=C_BOOL) :: order__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: quantity_
      LOGICAL(KIND=C_BOOL) :: quantity__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: read_write_convention_
      LOGICAL(KIND=C_BOOL) :: read_write_convention__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: renormalize_
      LOGICAL(KIND=C_BOOL) :: renormalize__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: use_area_
      LOGICAL(KIND=C_BOOL) :: use_area__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: weight_filename_
      LOGICAL(KIND=C_BOOL) :: weight_filename__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: write_weight_
      LOGICAL(KIND=C_BOOL) :: write_weight__tmp

      IF (PRESENT(detect_missing_value_)) THEN
        detect_missing_value__tmp = cxios_is_defined_interpolate_domain_detect_missing_value &
      (interpolate_domain_hdl%daddr)
        detect_missing_value_ = detect_missing_value__tmp
      ENDIF

      IF (PRESENT(mode_)) THEN
        mode__tmp = cxios_is_defined_interpolate_domain_mode &
      (interpolate_domain_hdl%daddr)
        mode_ = mode__tmp
      ENDIF

      IF (PRESENT(order_)) THEN
        order__tmp = cxios_is_defined_interpolate_domain_order &
      (interpolate_domain_hdl%daddr)
        order_ = order__tmp
      ENDIF

      IF (PRESENT(quantity_)) THEN
        quantity__tmp = cxios_is_defined_interpolate_domain_quantity &
      (interpolate_domain_hdl%daddr)
        quantity_ = quantity__tmp
      ENDIF

      IF (PRESENT(read_write_convention_)) THEN
        read_write_convention__tmp = cxios_is_defined_interpolate_domain_read_write_convention &
      (interpolate_domain_hdl%daddr)
        read_write_convention_ = read_write_convention__tmp
      ENDIF

      IF (PRESENT(renormalize_)) THEN
        renormalize__tmp = cxios_is_defined_interpolate_domain_renormalize &
      (interpolate_domain_hdl%daddr)
        renormalize_ = renormalize__tmp
      ENDIF

      IF (PRESENT(use_area_)) THEN
        use_area__tmp = cxios_is_defined_interpolate_domain_use_area &
      (interpolate_domain_hdl%daddr)
        use_area_ = use_area__tmp
      ENDIF

      IF (PRESENT(weight_filename_)) THEN
        weight_filename__tmp = cxios_is_defined_interpolate_domain_weight_filename &
      (interpolate_domain_hdl%daddr)
        weight_filename_ = weight_filename__tmp
      ENDIF

      IF (PRESENT(write_weight_)) THEN
        write_weight__tmp = cxios_is_defined_interpolate_domain_write_weight &
      (interpolate_domain_hdl%daddr)
        write_weight_ = write_weight__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_interpolate_domain_attr_hdl_)

END MODULE iinterpolate_domain_attr
