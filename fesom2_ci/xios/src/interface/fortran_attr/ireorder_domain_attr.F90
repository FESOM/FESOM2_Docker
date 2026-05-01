! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE ireorder_domain_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE ireorder_domain
  USE reorder_domain_interface_attr

CONTAINS

  SUBROUTINE xios(set_reorder_domain_attr)  &
    ( reorder_domain_id, invert_lat, max_lon, min_lon, shift_lon_fraction )

    IMPLICIT NONE
      TYPE(txios(reorder_domain))  :: reorder_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reorder_domain_id
      LOGICAL  , OPTIONAL, INTENT(IN) :: invert_lat
      LOGICAL (KIND=C_BOOL) :: invert_lat_tmp
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: max_lon
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: min_lon
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: shift_lon_fraction

      CALL xios(get_reorder_domain_handle) &
      (reorder_domain_id,reorder_domain_hdl)
      CALL xios(set_reorder_domain_attr_hdl_)   &
      ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

  END SUBROUTINE xios(set_reorder_domain_attr)

  SUBROUTINE xios(set_reorder_domain_attr_hdl)  &
    ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

    IMPLICIT NONE
      TYPE(txios(reorder_domain)) , INTENT(IN) :: reorder_domain_hdl
      LOGICAL  , OPTIONAL, INTENT(IN) :: invert_lat
      LOGICAL (KIND=C_BOOL) :: invert_lat_tmp
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: max_lon
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: min_lon
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: shift_lon_fraction

      CALL xios(set_reorder_domain_attr_hdl_)  &
      ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

  END SUBROUTINE xios(set_reorder_domain_attr_hdl)

  SUBROUTINE xios(set_reorder_domain_attr_hdl_)   &
    ( reorder_domain_hdl, invert_lat_, max_lon_, min_lon_, shift_lon_fraction_ )

    IMPLICIT NONE
      TYPE(txios(reorder_domain)) , INTENT(IN) :: reorder_domain_hdl
      LOGICAL  , OPTIONAL, INTENT(IN) :: invert_lat_
      LOGICAL (KIND=C_BOOL) :: invert_lat__tmp
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: max_lon_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: min_lon_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: shift_lon_fraction_

      IF (PRESENT(invert_lat_)) THEN
        invert_lat__tmp = invert_lat_
        CALL cxios_set_reorder_domain_invert_lat &
      (reorder_domain_hdl%daddr, invert_lat__tmp)
      ENDIF

      IF (PRESENT(max_lon_)) THEN
        CALL cxios_set_reorder_domain_max_lon &
      (reorder_domain_hdl%daddr, max_lon_)
      ENDIF

      IF (PRESENT(min_lon_)) THEN
        CALL cxios_set_reorder_domain_min_lon &
      (reorder_domain_hdl%daddr, min_lon_)
      ENDIF

      IF (PRESENT(shift_lon_fraction_)) THEN
        CALL cxios_set_reorder_domain_shift_lon_fraction &
      (reorder_domain_hdl%daddr, shift_lon_fraction_)
      ENDIF

  END SUBROUTINE xios(set_reorder_domain_attr_hdl_)

  SUBROUTINE xios(get_reorder_domain_attr)  &
    ( reorder_domain_id, invert_lat, max_lon, min_lon, shift_lon_fraction )

    IMPLICIT NONE
      TYPE(txios(reorder_domain))  :: reorder_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reorder_domain_id
      LOGICAL  , OPTIONAL, INTENT(OUT) :: invert_lat
      LOGICAL (KIND=C_BOOL) :: invert_lat_tmp
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: max_lon
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: min_lon
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: shift_lon_fraction

      CALL xios(get_reorder_domain_handle) &
      (reorder_domain_id,reorder_domain_hdl)
      CALL xios(get_reorder_domain_attr_hdl_)   &
      ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

  END SUBROUTINE xios(get_reorder_domain_attr)

  SUBROUTINE xios(get_reorder_domain_attr_hdl)  &
    ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

    IMPLICIT NONE
      TYPE(txios(reorder_domain)) , INTENT(IN) :: reorder_domain_hdl
      LOGICAL  , OPTIONAL, INTENT(OUT) :: invert_lat
      LOGICAL (KIND=C_BOOL) :: invert_lat_tmp
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: max_lon
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: min_lon
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: shift_lon_fraction

      CALL xios(get_reorder_domain_attr_hdl_)  &
      ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

  END SUBROUTINE xios(get_reorder_domain_attr_hdl)

  SUBROUTINE xios(get_reorder_domain_attr_hdl_)   &
    ( reorder_domain_hdl, invert_lat_, max_lon_, min_lon_, shift_lon_fraction_ )

    IMPLICIT NONE
      TYPE(txios(reorder_domain)) , INTENT(IN) :: reorder_domain_hdl
      LOGICAL  , OPTIONAL, INTENT(OUT) :: invert_lat_
      LOGICAL (KIND=C_BOOL) :: invert_lat__tmp
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: max_lon_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: min_lon_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: shift_lon_fraction_

      IF (PRESENT(invert_lat_)) THEN
        CALL cxios_get_reorder_domain_invert_lat &
      (reorder_domain_hdl%daddr, invert_lat__tmp)
        invert_lat_ = invert_lat__tmp
      ENDIF

      IF (PRESENT(max_lon_)) THEN
        CALL cxios_get_reorder_domain_max_lon &
      (reorder_domain_hdl%daddr, max_lon_)
      ENDIF

      IF (PRESENT(min_lon_)) THEN
        CALL cxios_get_reorder_domain_min_lon &
      (reorder_domain_hdl%daddr, min_lon_)
      ENDIF

      IF (PRESENT(shift_lon_fraction_)) THEN
        CALL cxios_get_reorder_domain_shift_lon_fraction &
      (reorder_domain_hdl%daddr, shift_lon_fraction_)
      ENDIF

  END SUBROUTINE xios(get_reorder_domain_attr_hdl_)

  SUBROUTINE xios(is_defined_reorder_domain_attr)  &
    ( reorder_domain_id, invert_lat, max_lon, min_lon, shift_lon_fraction )

    IMPLICIT NONE
      TYPE(txios(reorder_domain))  :: reorder_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reorder_domain_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: invert_lat
      LOGICAL(KIND=C_BOOL) :: invert_lat_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: max_lon
      LOGICAL(KIND=C_BOOL) :: max_lon_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: min_lon
      LOGICAL(KIND=C_BOOL) :: min_lon_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: shift_lon_fraction
      LOGICAL(KIND=C_BOOL) :: shift_lon_fraction_tmp

      CALL xios(get_reorder_domain_handle) &
      (reorder_domain_id,reorder_domain_hdl)
      CALL xios(is_defined_reorder_domain_attr_hdl_)   &
      ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

  END SUBROUTINE xios(is_defined_reorder_domain_attr)

  SUBROUTINE xios(is_defined_reorder_domain_attr_hdl)  &
    ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

    IMPLICIT NONE
      TYPE(txios(reorder_domain)) , INTENT(IN) :: reorder_domain_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: invert_lat
      LOGICAL(KIND=C_BOOL) :: invert_lat_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: max_lon
      LOGICAL(KIND=C_BOOL) :: max_lon_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: min_lon
      LOGICAL(KIND=C_BOOL) :: min_lon_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: shift_lon_fraction
      LOGICAL(KIND=C_BOOL) :: shift_lon_fraction_tmp

      CALL xios(is_defined_reorder_domain_attr_hdl_)  &
      ( reorder_domain_hdl, invert_lat, max_lon, min_lon, shift_lon_fraction )

  END SUBROUTINE xios(is_defined_reorder_domain_attr_hdl)

  SUBROUTINE xios(is_defined_reorder_domain_attr_hdl_)   &
    ( reorder_domain_hdl, invert_lat_, max_lon_, min_lon_, shift_lon_fraction_ )

    IMPLICIT NONE
      TYPE(txios(reorder_domain)) , INTENT(IN) :: reorder_domain_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: invert_lat_
      LOGICAL(KIND=C_BOOL) :: invert_lat__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: max_lon_
      LOGICAL(KIND=C_BOOL) :: max_lon__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: min_lon_
      LOGICAL(KIND=C_BOOL) :: min_lon__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: shift_lon_fraction_
      LOGICAL(KIND=C_BOOL) :: shift_lon_fraction__tmp

      IF (PRESENT(invert_lat_)) THEN
        invert_lat__tmp = cxios_is_defined_reorder_domain_invert_lat &
      (reorder_domain_hdl%daddr)
        invert_lat_ = invert_lat__tmp
      ENDIF

      IF (PRESENT(max_lon_)) THEN
        max_lon__tmp = cxios_is_defined_reorder_domain_max_lon &
      (reorder_domain_hdl%daddr)
        max_lon_ = max_lon__tmp
      ENDIF

      IF (PRESENT(min_lon_)) THEN
        min_lon__tmp = cxios_is_defined_reorder_domain_min_lon &
      (reorder_domain_hdl%daddr)
        min_lon_ = min_lon__tmp
      ENDIF

      IF (PRESENT(shift_lon_fraction_)) THEN
        shift_lon_fraction__tmp = cxios_is_defined_reorder_domain_shift_lon_fraction &
      (reorder_domain_hdl%daddr)
        shift_lon_fraction_ = shift_lon_fraction__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_reorder_domain_attr_hdl_)

END MODULE ireorder_domain_attr
