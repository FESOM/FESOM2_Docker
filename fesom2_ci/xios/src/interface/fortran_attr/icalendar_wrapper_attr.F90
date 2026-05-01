! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE icalendar_wrapper_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE icalendar_wrapper
  USE calendar_wrapper_interface_attr

CONTAINS

  SUBROUTINE xios(set_calendar_wrapper_attr)  &
    ( calendar_wrapper_id, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
    , month_lengths, start_date, time_origin, timestep, type, year_length )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper))  :: calendar_wrapper_hdl
      CHARACTER(LEN=*), INTENT(IN) ::calendar_wrapper_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      INTEGER  , OPTIONAL, INTENT(IN) :: day_length
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: leap_year_drift
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: leap_year_drift_offset
      INTEGER  , OPTIONAL, INTENT(IN) :: leap_year_month
      INTEGER  , OPTIONAL, INTENT(IN) :: month_lengths(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: start_date
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_origin
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: timestep
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type
      INTEGER  , OPTIONAL, INTENT(IN) :: year_length

      CALL xios(get_calendar_wrapper_handle) &
      (calendar_wrapper_id,calendar_wrapper_hdl)
      CALL xios(set_calendar_wrapper_attr_hdl_)   &
      ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
      , month_lengths, start_date, time_origin, timestep, type, year_length )

  END SUBROUTINE xios(set_calendar_wrapper_attr)

  SUBROUTINE xios(set_calendar_wrapper_attr_hdl)  &
    ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
    , month_lengths, start_date, time_origin, timestep, type, year_length )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper)) , INTENT(IN) :: calendar_wrapper_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      INTEGER  , OPTIONAL, INTENT(IN) :: day_length
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: leap_year_drift
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: leap_year_drift_offset
      INTEGER  , OPTIONAL, INTENT(IN) :: leap_year_month
      INTEGER  , OPTIONAL, INTENT(IN) :: month_lengths(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: start_date
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_origin
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: timestep
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type
      INTEGER  , OPTIONAL, INTENT(IN) :: year_length

      CALL xios(set_calendar_wrapper_attr_hdl_)  &
      ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
      , month_lengths, start_date, time_origin, timestep, type, year_length )

  END SUBROUTINE xios(set_calendar_wrapper_attr_hdl)

  SUBROUTINE xios(set_calendar_wrapper_attr_hdl_)   &
    ( calendar_wrapper_hdl, comment_, day_length_, leap_year_drift_, leap_year_drift_offset_, leap_year_month_  &
    , month_lengths_, start_date_, time_origin_, timestep_, type_, year_length_ )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper)) , INTENT(IN) :: calendar_wrapper_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment_
      INTEGER  , OPTIONAL, INTENT(IN) :: day_length_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: leap_year_drift_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: leap_year_drift_offset_
      INTEGER  , OPTIONAL, INTENT(IN) :: leap_year_month_
      INTEGER  , OPTIONAL, INTENT(IN) :: month_lengths_(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: start_date_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_origin_
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: timestep_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type_
      INTEGER  , OPTIONAL, INTENT(IN) :: year_length_

      IF (PRESENT(comment_)) THEN
        CALL cxios_set_calendar_wrapper_comment &
      (calendar_wrapper_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(day_length_)) THEN
        CALL cxios_set_calendar_wrapper_day_length &
      (calendar_wrapper_hdl%daddr, day_length_)
      ENDIF

      IF (PRESENT(leap_year_drift_)) THEN
        CALL cxios_set_calendar_wrapper_leap_year_drift &
      (calendar_wrapper_hdl%daddr, leap_year_drift_)
      ENDIF

      IF (PRESENT(leap_year_drift_offset_)) THEN
        CALL cxios_set_calendar_wrapper_leap_year_drift_offset &
      (calendar_wrapper_hdl%daddr, leap_year_drift_offset_)
      ENDIF

      IF (PRESENT(leap_year_month_)) THEN
        CALL cxios_set_calendar_wrapper_leap_year_month &
      (calendar_wrapper_hdl%daddr, leap_year_month_)
      ENDIF

      IF (PRESENT(month_lengths_)) THEN
        CALL cxios_set_calendar_wrapper_month_lengths &
      (calendar_wrapper_hdl%daddr, month_lengths_, SHAPE(month_lengths_))
      ENDIF

      IF (PRESENT(start_date_)) THEN
        CALL cxios_set_calendar_wrapper_start_date &
      (calendar_wrapper_hdl%daddr, start_date_, len(start_date_))
      ENDIF

      IF (PRESENT(time_origin_)) THEN
        CALL cxios_set_calendar_wrapper_time_origin &
      (calendar_wrapper_hdl%daddr, time_origin_, len(time_origin_))
      ENDIF

      IF (PRESENT(timestep_)) THEN
        CALL cxios_set_calendar_wrapper_timestep &
      (calendar_wrapper_hdl%daddr, timestep_)
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_set_calendar_wrapper_type &
      (calendar_wrapper_hdl%daddr, type_, len(type_))
      ENDIF

      IF (PRESENT(year_length_)) THEN
        CALL cxios_set_calendar_wrapper_year_length &
      (calendar_wrapper_hdl%daddr, year_length_)
      ENDIF

  END SUBROUTINE xios(set_calendar_wrapper_attr_hdl_)

  SUBROUTINE xios(get_calendar_wrapper_attr)  &
    ( calendar_wrapper_id, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
    , month_lengths, start_date, time_origin, timestep, type, year_length )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper))  :: calendar_wrapper_hdl
      CHARACTER(LEN=*), INTENT(IN) ::calendar_wrapper_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      INTEGER  , OPTIONAL, INTENT(OUT) :: day_length
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: leap_year_drift
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: leap_year_drift_offset
      INTEGER  , OPTIONAL, INTENT(OUT) :: leap_year_month
      INTEGER  , OPTIONAL, INTENT(OUT) :: month_lengths(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: start_date
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_origin
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: timestep
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type
      INTEGER  , OPTIONAL, INTENT(OUT) :: year_length

      CALL xios(get_calendar_wrapper_handle) &
      (calendar_wrapper_id,calendar_wrapper_hdl)
      CALL xios(get_calendar_wrapper_attr_hdl_)   &
      ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
      , month_lengths, start_date, time_origin, timestep, type, year_length )

  END SUBROUTINE xios(get_calendar_wrapper_attr)

  SUBROUTINE xios(get_calendar_wrapper_attr_hdl)  &
    ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
    , month_lengths, start_date, time_origin, timestep, type, year_length )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper)) , INTENT(IN) :: calendar_wrapper_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      INTEGER  , OPTIONAL, INTENT(OUT) :: day_length
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: leap_year_drift
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: leap_year_drift_offset
      INTEGER  , OPTIONAL, INTENT(OUT) :: leap_year_month
      INTEGER  , OPTIONAL, INTENT(OUT) :: month_lengths(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: start_date
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_origin
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: timestep
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type
      INTEGER  , OPTIONAL, INTENT(OUT) :: year_length

      CALL xios(get_calendar_wrapper_attr_hdl_)  &
      ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
      , month_lengths, start_date, time_origin, timestep, type, year_length )

  END SUBROUTINE xios(get_calendar_wrapper_attr_hdl)

  SUBROUTINE xios(get_calendar_wrapper_attr_hdl_)   &
    ( calendar_wrapper_hdl, comment_, day_length_, leap_year_drift_, leap_year_drift_offset_, leap_year_month_  &
    , month_lengths_, start_date_, time_origin_, timestep_, type_, year_length_ )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper)) , INTENT(IN) :: calendar_wrapper_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment_
      INTEGER  , OPTIONAL, INTENT(OUT) :: day_length_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: leap_year_drift_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: leap_year_drift_offset_
      INTEGER  , OPTIONAL, INTENT(OUT) :: leap_year_month_
      INTEGER  , OPTIONAL, INTENT(OUT) :: month_lengths_(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: start_date_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_origin_
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: timestep_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type_
      INTEGER  , OPTIONAL, INTENT(OUT) :: year_length_

      IF (PRESENT(comment_)) THEN
        CALL cxios_get_calendar_wrapper_comment &
      (calendar_wrapper_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(day_length_)) THEN
        CALL cxios_get_calendar_wrapper_day_length &
      (calendar_wrapper_hdl%daddr, day_length_)
      ENDIF

      IF (PRESENT(leap_year_drift_)) THEN
        CALL cxios_get_calendar_wrapper_leap_year_drift &
      (calendar_wrapper_hdl%daddr, leap_year_drift_)
      ENDIF

      IF (PRESENT(leap_year_drift_offset_)) THEN
        CALL cxios_get_calendar_wrapper_leap_year_drift_offset &
      (calendar_wrapper_hdl%daddr, leap_year_drift_offset_)
      ENDIF

      IF (PRESENT(leap_year_month_)) THEN
        CALL cxios_get_calendar_wrapper_leap_year_month &
      (calendar_wrapper_hdl%daddr, leap_year_month_)
      ENDIF

      IF (PRESENT(month_lengths_)) THEN
        CALL cxios_get_calendar_wrapper_month_lengths &
      (calendar_wrapper_hdl%daddr, month_lengths_, SHAPE(month_lengths_))
      ENDIF

      IF (PRESENT(start_date_)) THEN
        CALL cxios_get_calendar_wrapper_start_date &
      (calendar_wrapper_hdl%daddr, start_date_, len(start_date_))
      ENDIF

      IF (PRESENT(time_origin_)) THEN
        CALL cxios_get_calendar_wrapper_time_origin &
      (calendar_wrapper_hdl%daddr, time_origin_, len(time_origin_))
      ENDIF

      IF (PRESENT(timestep_)) THEN
        CALL cxios_get_calendar_wrapper_timestep &
      (calendar_wrapper_hdl%daddr, timestep_)
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_get_calendar_wrapper_type &
      (calendar_wrapper_hdl%daddr, type_, len(type_))
      ENDIF

      IF (PRESENT(year_length_)) THEN
        CALL cxios_get_calendar_wrapper_year_length &
      (calendar_wrapper_hdl%daddr, year_length_)
      ENDIF

  END SUBROUTINE xios(get_calendar_wrapper_attr_hdl_)

  SUBROUTINE xios(is_defined_calendar_wrapper_attr)  &
    ( calendar_wrapper_id, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
    , month_lengths, start_date, time_origin, timestep, type, year_length )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper))  :: calendar_wrapper_hdl
      CHARACTER(LEN=*), INTENT(IN) ::calendar_wrapper_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: day_length
      LOGICAL(KIND=C_BOOL) :: day_length_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_drift
      LOGICAL(KIND=C_BOOL) :: leap_year_drift_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_drift_offset
      LOGICAL(KIND=C_BOOL) :: leap_year_drift_offset_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_month
      LOGICAL(KIND=C_BOOL) :: leap_year_month_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: month_lengths
      LOGICAL(KIND=C_BOOL) :: month_lengths_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: start_date
      LOGICAL(KIND=C_BOOL) :: start_date_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_origin
      LOGICAL(KIND=C_BOOL) :: time_origin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: timestep
      LOGICAL(KIND=C_BOOL) :: timestep_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: year_length
      LOGICAL(KIND=C_BOOL) :: year_length_tmp

      CALL xios(get_calendar_wrapper_handle) &
      (calendar_wrapper_id,calendar_wrapper_hdl)
      CALL xios(is_defined_calendar_wrapper_attr_hdl_)   &
      ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
      , month_lengths, start_date, time_origin, timestep, type, year_length )

  END SUBROUTINE xios(is_defined_calendar_wrapper_attr)

  SUBROUTINE xios(is_defined_calendar_wrapper_attr_hdl)  &
    ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
    , month_lengths, start_date, time_origin, timestep, type, year_length )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper)) , INTENT(IN) :: calendar_wrapper_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: day_length
      LOGICAL(KIND=C_BOOL) :: day_length_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_drift
      LOGICAL(KIND=C_BOOL) :: leap_year_drift_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_drift_offset
      LOGICAL(KIND=C_BOOL) :: leap_year_drift_offset_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_month
      LOGICAL(KIND=C_BOOL) :: leap_year_month_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: month_lengths
      LOGICAL(KIND=C_BOOL) :: month_lengths_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: start_date
      LOGICAL(KIND=C_BOOL) :: start_date_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_origin
      LOGICAL(KIND=C_BOOL) :: time_origin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: timestep
      LOGICAL(KIND=C_BOOL) :: timestep_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: year_length
      LOGICAL(KIND=C_BOOL) :: year_length_tmp

      CALL xios(is_defined_calendar_wrapper_attr_hdl_)  &
      ( calendar_wrapper_hdl, comment, day_length, leap_year_drift, leap_year_drift_offset, leap_year_month  &
      , month_lengths, start_date, time_origin, timestep, type, year_length )

  END SUBROUTINE xios(is_defined_calendar_wrapper_attr_hdl)

  SUBROUTINE xios(is_defined_calendar_wrapper_attr_hdl_)   &
    ( calendar_wrapper_hdl, comment_, day_length_, leap_year_drift_, leap_year_drift_offset_, leap_year_month_  &
    , month_lengths_, start_date_, time_origin_, timestep_, type_, year_length_ )

    IMPLICIT NONE
      TYPE(txios(calendar_wrapper)) , INTENT(IN) :: calendar_wrapper_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment_
      LOGICAL(KIND=C_BOOL) :: comment__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: day_length_
      LOGICAL(KIND=C_BOOL) :: day_length__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_drift_
      LOGICAL(KIND=C_BOOL) :: leap_year_drift__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_drift_offset_
      LOGICAL(KIND=C_BOOL) :: leap_year_drift_offset__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: leap_year_month_
      LOGICAL(KIND=C_BOOL) :: leap_year_month__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: month_lengths_
      LOGICAL(KIND=C_BOOL) :: month_lengths__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: start_date_
      LOGICAL(KIND=C_BOOL) :: start_date__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_origin_
      LOGICAL(KIND=C_BOOL) :: time_origin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: timestep_
      LOGICAL(KIND=C_BOOL) :: timestep__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type_
      LOGICAL(KIND=C_BOOL) :: type__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: year_length_
      LOGICAL(KIND=C_BOOL) :: year_length__tmp

      IF (PRESENT(comment_)) THEN
        comment__tmp = cxios_is_defined_calendar_wrapper_comment &
      (calendar_wrapper_hdl%daddr)
        comment_ = comment__tmp
      ENDIF

      IF (PRESENT(day_length_)) THEN
        day_length__tmp = cxios_is_defined_calendar_wrapper_day_length &
      (calendar_wrapper_hdl%daddr)
        day_length_ = day_length__tmp
      ENDIF

      IF (PRESENT(leap_year_drift_)) THEN
        leap_year_drift__tmp = cxios_is_defined_calendar_wrapper_leap_year_drift &
      (calendar_wrapper_hdl%daddr)
        leap_year_drift_ = leap_year_drift__tmp
      ENDIF

      IF (PRESENT(leap_year_drift_offset_)) THEN
        leap_year_drift_offset__tmp = cxios_is_defined_calendar_wrapper_leap_year_drift_offset &
      (calendar_wrapper_hdl%daddr)
        leap_year_drift_offset_ = leap_year_drift_offset__tmp
      ENDIF

      IF (PRESENT(leap_year_month_)) THEN
        leap_year_month__tmp = cxios_is_defined_calendar_wrapper_leap_year_month &
      (calendar_wrapper_hdl%daddr)
        leap_year_month_ = leap_year_month__tmp
      ENDIF

      IF (PRESENT(month_lengths_)) THEN
        month_lengths__tmp = cxios_is_defined_calendar_wrapper_month_lengths &
      (calendar_wrapper_hdl%daddr)
        month_lengths_ = month_lengths__tmp
      ENDIF

      IF (PRESENT(start_date_)) THEN
        start_date__tmp = cxios_is_defined_calendar_wrapper_start_date &
      (calendar_wrapper_hdl%daddr)
        start_date_ = start_date__tmp
      ENDIF

      IF (PRESENT(time_origin_)) THEN
        time_origin__tmp = cxios_is_defined_calendar_wrapper_time_origin &
      (calendar_wrapper_hdl%daddr)
        time_origin_ = time_origin__tmp
      ENDIF

      IF (PRESENT(timestep_)) THEN
        timestep__tmp = cxios_is_defined_calendar_wrapper_timestep &
      (calendar_wrapper_hdl%daddr)
        timestep_ = timestep__tmp
      ENDIF

      IF (PRESENT(type_)) THEN
        type__tmp = cxios_is_defined_calendar_wrapper_type &
      (calendar_wrapper_hdl%daddr)
        type_ = type__tmp
      ENDIF

      IF (PRESENT(year_length_)) THEN
        year_length__tmp = cxios_is_defined_calendar_wrapper_year_length &
      (calendar_wrapper_hdl%daddr)
        year_length_ = year_length__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_calendar_wrapper_attr_hdl_)

END MODULE icalendar_wrapper_attr
