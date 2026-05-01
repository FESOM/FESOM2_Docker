! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE igenerate_rectilinear_domain_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE igenerate_rectilinear_domain
  USE generate_rectilinear_domain_interface_attr

CONTAINS

  SUBROUTINE xios(set_generate_rectilinear_domain_attr)  &
    ( generate_rectilinear_domain_id, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
    , lat_end, lat_start, lon_end, lon_start )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain))  :: generate_rectilinear_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::generate_rectilinear_domain_id
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_end
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_start
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_end
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_start
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lat_end
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lat_start
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lon_end
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lon_start

      CALL xios(get_generate_rectilinear_domain_handle) &
      (generate_rectilinear_domain_id,generate_rectilinear_domain_hdl)
      CALL xios(set_generate_rectilinear_domain_attr_hdl_)   &
      ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
      , lat_end, lat_start, lon_end, lon_start )

  END SUBROUTINE xios(set_generate_rectilinear_domain_attr)

  SUBROUTINE xios(set_generate_rectilinear_domain_attr_hdl)  &
    ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
    , lat_end, lat_start, lon_end, lon_start )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain)) , INTENT(IN) :: generate_rectilinear_domain_hdl
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_end
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_start
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_end
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_start
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lat_end
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lat_start
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lon_end
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lon_start

      CALL xios(set_generate_rectilinear_domain_attr_hdl_)  &
      ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
      , lat_end, lat_start, lon_end, lon_start )

  END SUBROUTINE xios(set_generate_rectilinear_domain_attr_hdl)

  SUBROUTINE xios(set_generate_rectilinear_domain_attr_hdl_)   &
    ( generate_rectilinear_domain_hdl, bounds_lat_end_, bounds_lat_start_, bounds_lon_end_, bounds_lon_start_  &
    , lat_end_, lat_start_, lon_end_, lon_start_ )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain)) , INTENT(IN) :: generate_rectilinear_domain_hdl
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_end_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_start_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_end_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_start_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lat_end_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lat_start_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lon_end_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lon_start_

      IF (PRESENT(bounds_lat_end_)) THEN
        CALL cxios_set_generate_rectilinear_domain_bounds_lat_end &
      (generate_rectilinear_domain_hdl%daddr, bounds_lat_end_)
      ENDIF

      IF (PRESENT(bounds_lat_start_)) THEN
        CALL cxios_set_generate_rectilinear_domain_bounds_lat_start &
      (generate_rectilinear_domain_hdl%daddr, bounds_lat_start_)
      ENDIF

      IF (PRESENT(bounds_lon_end_)) THEN
        CALL cxios_set_generate_rectilinear_domain_bounds_lon_end &
      (generate_rectilinear_domain_hdl%daddr, bounds_lon_end_)
      ENDIF

      IF (PRESENT(bounds_lon_start_)) THEN
        CALL cxios_set_generate_rectilinear_domain_bounds_lon_start &
      (generate_rectilinear_domain_hdl%daddr, bounds_lon_start_)
      ENDIF

      IF (PRESENT(lat_end_)) THEN
        CALL cxios_set_generate_rectilinear_domain_lat_end &
      (generate_rectilinear_domain_hdl%daddr, lat_end_)
      ENDIF

      IF (PRESENT(lat_start_)) THEN
        CALL cxios_set_generate_rectilinear_domain_lat_start &
      (generate_rectilinear_domain_hdl%daddr, lat_start_)
      ENDIF

      IF (PRESENT(lon_end_)) THEN
        CALL cxios_set_generate_rectilinear_domain_lon_end &
      (generate_rectilinear_domain_hdl%daddr, lon_end_)
      ENDIF

      IF (PRESENT(lon_start_)) THEN
        CALL cxios_set_generate_rectilinear_domain_lon_start &
      (generate_rectilinear_domain_hdl%daddr, lon_start_)
      ENDIF

  END SUBROUTINE xios(set_generate_rectilinear_domain_attr_hdl_)

  SUBROUTINE xios(get_generate_rectilinear_domain_attr)  &
    ( generate_rectilinear_domain_id, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
    , lat_end, lat_start, lon_end, lon_start )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain))  :: generate_rectilinear_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::generate_rectilinear_domain_id
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_end
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_start
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_end
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_start
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lat_end
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lat_start
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lon_end
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lon_start

      CALL xios(get_generate_rectilinear_domain_handle) &
      (generate_rectilinear_domain_id,generate_rectilinear_domain_hdl)
      CALL xios(get_generate_rectilinear_domain_attr_hdl_)   &
      ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
      , lat_end, lat_start, lon_end, lon_start )

  END SUBROUTINE xios(get_generate_rectilinear_domain_attr)

  SUBROUTINE xios(get_generate_rectilinear_domain_attr_hdl)  &
    ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
    , lat_end, lat_start, lon_end, lon_start )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain)) , INTENT(IN) :: generate_rectilinear_domain_hdl
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_end
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_start
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_end
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_start
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lat_end
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lat_start
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lon_end
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lon_start

      CALL xios(get_generate_rectilinear_domain_attr_hdl_)  &
      ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
      , lat_end, lat_start, lon_end, lon_start )

  END SUBROUTINE xios(get_generate_rectilinear_domain_attr_hdl)

  SUBROUTINE xios(get_generate_rectilinear_domain_attr_hdl_)   &
    ( generate_rectilinear_domain_hdl, bounds_lat_end_, bounds_lat_start_, bounds_lon_end_, bounds_lon_start_  &
    , lat_end_, lat_start_, lon_end_, lon_start_ )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain)) , INTENT(IN) :: generate_rectilinear_domain_hdl
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_end_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_start_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_end_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_start_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lat_end_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lat_start_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lon_end_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lon_start_

      IF (PRESENT(bounds_lat_end_)) THEN
        CALL cxios_get_generate_rectilinear_domain_bounds_lat_end &
      (generate_rectilinear_domain_hdl%daddr, bounds_lat_end_)
      ENDIF

      IF (PRESENT(bounds_lat_start_)) THEN
        CALL cxios_get_generate_rectilinear_domain_bounds_lat_start &
      (generate_rectilinear_domain_hdl%daddr, bounds_lat_start_)
      ENDIF

      IF (PRESENT(bounds_lon_end_)) THEN
        CALL cxios_get_generate_rectilinear_domain_bounds_lon_end &
      (generate_rectilinear_domain_hdl%daddr, bounds_lon_end_)
      ENDIF

      IF (PRESENT(bounds_lon_start_)) THEN
        CALL cxios_get_generate_rectilinear_domain_bounds_lon_start &
      (generate_rectilinear_domain_hdl%daddr, bounds_lon_start_)
      ENDIF

      IF (PRESENT(lat_end_)) THEN
        CALL cxios_get_generate_rectilinear_domain_lat_end &
      (generate_rectilinear_domain_hdl%daddr, lat_end_)
      ENDIF

      IF (PRESENT(lat_start_)) THEN
        CALL cxios_get_generate_rectilinear_domain_lat_start &
      (generate_rectilinear_domain_hdl%daddr, lat_start_)
      ENDIF

      IF (PRESENT(lon_end_)) THEN
        CALL cxios_get_generate_rectilinear_domain_lon_end &
      (generate_rectilinear_domain_hdl%daddr, lon_end_)
      ENDIF

      IF (PRESENT(lon_start_)) THEN
        CALL cxios_get_generate_rectilinear_domain_lon_start &
      (generate_rectilinear_domain_hdl%daddr, lon_start_)
      ENDIF

  END SUBROUTINE xios(get_generate_rectilinear_domain_attr_hdl_)

  SUBROUTINE xios(is_defined_generate_rectilinear_domain_attr)  &
    ( generate_rectilinear_domain_id, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
    , lat_end, lat_start, lon_end, lon_start )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain))  :: generate_rectilinear_domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::generate_rectilinear_domain_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_end
      LOGICAL(KIND=C_BOOL) :: bounds_lat_end_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_start
      LOGICAL(KIND=C_BOOL) :: bounds_lat_start_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_end
      LOGICAL(KIND=C_BOOL) :: bounds_lon_end_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_start
      LOGICAL(KIND=C_BOOL) :: bounds_lon_start_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_end
      LOGICAL(KIND=C_BOOL) :: lat_end_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_start
      LOGICAL(KIND=C_BOOL) :: lat_start_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_end
      LOGICAL(KIND=C_BOOL) :: lon_end_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_start
      LOGICAL(KIND=C_BOOL) :: lon_start_tmp

      CALL xios(get_generate_rectilinear_domain_handle) &
      (generate_rectilinear_domain_id,generate_rectilinear_domain_hdl)
      CALL xios(is_defined_generate_rectilinear_domain_attr_hdl_)   &
      ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
      , lat_end, lat_start, lon_end, lon_start )

  END SUBROUTINE xios(is_defined_generate_rectilinear_domain_attr)

  SUBROUTINE xios(is_defined_generate_rectilinear_domain_attr_hdl)  &
    ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
    , lat_end, lat_start, lon_end, lon_start )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain)) , INTENT(IN) :: generate_rectilinear_domain_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_end
      LOGICAL(KIND=C_BOOL) :: bounds_lat_end_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_start
      LOGICAL(KIND=C_BOOL) :: bounds_lat_start_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_end
      LOGICAL(KIND=C_BOOL) :: bounds_lon_end_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_start
      LOGICAL(KIND=C_BOOL) :: bounds_lon_start_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_end
      LOGICAL(KIND=C_BOOL) :: lat_end_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_start
      LOGICAL(KIND=C_BOOL) :: lat_start_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_end
      LOGICAL(KIND=C_BOOL) :: lon_end_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_start
      LOGICAL(KIND=C_BOOL) :: lon_start_tmp

      CALL xios(is_defined_generate_rectilinear_domain_attr_hdl_)  &
      ( generate_rectilinear_domain_hdl, bounds_lat_end, bounds_lat_start, bounds_lon_end, bounds_lon_start  &
      , lat_end, lat_start, lon_end, lon_start )

  END SUBROUTINE xios(is_defined_generate_rectilinear_domain_attr_hdl)

  SUBROUTINE xios(is_defined_generate_rectilinear_domain_attr_hdl_)   &
    ( generate_rectilinear_domain_hdl, bounds_lat_end_, bounds_lat_start_, bounds_lon_end_, bounds_lon_start_  &
    , lat_end_, lat_start_, lon_end_, lon_start_ )

    IMPLICIT NONE
      TYPE(txios(generate_rectilinear_domain)) , INTENT(IN) :: generate_rectilinear_domain_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_end_
      LOGICAL(KIND=C_BOOL) :: bounds_lat_end__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_start_
      LOGICAL(KIND=C_BOOL) :: bounds_lat_start__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_end_
      LOGICAL(KIND=C_BOOL) :: bounds_lon_end__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_start_
      LOGICAL(KIND=C_BOOL) :: bounds_lon_start__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_end_
      LOGICAL(KIND=C_BOOL) :: lat_end__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_start_
      LOGICAL(KIND=C_BOOL) :: lat_start__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_end_
      LOGICAL(KIND=C_BOOL) :: lon_end__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_start_
      LOGICAL(KIND=C_BOOL) :: lon_start__tmp

      IF (PRESENT(bounds_lat_end_)) THEN
        bounds_lat_end__tmp = cxios_is_defined_generate_rectilinear_domain_bounds_lat_end &
      (generate_rectilinear_domain_hdl%daddr)
        bounds_lat_end_ = bounds_lat_end__tmp
      ENDIF

      IF (PRESENT(bounds_lat_start_)) THEN
        bounds_lat_start__tmp = cxios_is_defined_generate_rectilinear_domain_bounds_lat_start &
      (generate_rectilinear_domain_hdl%daddr)
        bounds_lat_start_ = bounds_lat_start__tmp
      ENDIF

      IF (PRESENT(bounds_lon_end_)) THEN
        bounds_lon_end__tmp = cxios_is_defined_generate_rectilinear_domain_bounds_lon_end &
      (generate_rectilinear_domain_hdl%daddr)
        bounds_lon_end_ = bounds_lon_end__tmp
      ENDIF

      IF (PRESENT(bounds_lon_start_)) THEN
        bounds_lon_start__tmp = cxios_is_defined_generate_rectilinear_domain_bounds_lon_start &
      (generate_rectilinear_domain_hdl%daddr)
        bounds_lon_start_ = bounds_lon_start__tmp
      ENDIF

      IF (PRESENT(lat_end_)) THEN
        lat_end__tmp = cxios_is_defined_generate_rectilinear_domain_lat_end &
      (generate_rectilinear_domain_hdl%daddr)
        lat_end_ = lat_end__tmp
      ENDIF

      IF (PRESENT(lat_start_)) THEN
        lat_start__tmp = cxios_is_defined_generate_rectilinear_domain_lat_start &
      (generate_rectilinear_domain_hdl%daddr)
        lat_start_ = lat_start__tmp
      ENDIF

      IF (PRESENT(lon_end_)) THEN
        lon_end__tmp = cxios_is_defined_generate_rectilinear_domain_lon_end &
      (generate_rectilinear_domain_hdl%daddr)
        lon_end_ = lon_end__tmp
      ENDIF

      IF (PRESENT(lon_start_)) THEN
        lon_start__tmp = cxios_is_defined_generate_rectilinear_domain_lon_start &
      (generate_rectilinear_domain_hdl%daddr)
        lon_start_ = lon_start__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_generate_rectilinear_domain_attr_hdl_)

END MODULE igenerate_rectilinear_domain_attr
