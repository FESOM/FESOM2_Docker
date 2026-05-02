! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE calendar_wrapper_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_calendar_wrapper_comment(calendar_wrapper_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_calendar_wrapper_comment

    SUBROUTINE cxios_get_calendar_wrapper_comment(calendar_wrapper_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_calendar_wrapper_comment

    FUNCTION cxios_is_defined_calendar_wrapper_comment(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_comment


    SUBROUTINE cxios_set_calendar_wrapper_day_length(calendar_wrapper_hdl, day_length) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      INTEGER (KIND=C_INT)      , VALUE :: day_length
    END SUBROUTINE cxios_set_calendar_wrapper_day_length

    SUBROUTINE cxios_get_calendar_wrapper_day_length(calendar_wrapper_hdl, day_length) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      INTEGER (KIND=C_INT)             :: day_length
    END SUBROUTINE cxios_get_calendar_wrapper_day_length

    FUNCTION cxios_is_defined_calendar_wrapper_day_length(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_day_length
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_day_length


    SUBROUTINE cxios_set_calendar_wrapper_leap_year_drift(calendar_wrapper_hdl, leap_year_drift) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: leap_year_drift
    END SUBROUTINE cxios_set_calendar_wrapper_leap_year_drift

    SUBROUTINE cxios_get_calendar_wrapper_leap_year_drift(calendar_wrapper_hdl, leap_year_drift) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      REAL (KIND=C_DOUBLE)             :: leap_year_drift
    END SUBROUTINE cxios_get_calendar_wrapper_leap_year_drift

    FUNCTION cxios_is_defined_calendar_wrapper_leap_year_drift(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_leap_year_drift
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_leap_year_drift


    SUBROUTINE cxios_set_calendar_wrapper_leap_year_drift_offset(calendar_wrapper_hdl, leap_year_drift_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: leap_year_drift_offset
    END SUBROUTINE cxios_set_calendar_wrapper_leap_year_drift_offset

    SUBROUTINE cxios_get_calendar_wrapper_leap_year_drift_offset(calendar_wrapper_hdl, leap_year_drift_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      REAL (KIND=C_DOUBLE)             :: leap_year_drift_offset
    END SUBROUTINE cxios_get_calendar_wrapper_leap_year_drift_offset

    FUNCTION cxios_is_defined_calendar_wrapper_leap_year_drift_offset(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_leap_year_drift_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_leap_year_drift_offset


    SUBROUTINE cxios_set_calendar_wrapper_leap_year_month(calendar_wrapper_hdl, leap_year_month) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      INTEGER (KIND=C_INT)      , VALUE :: leap_year_month
    END SUBROUTINE cxios_set_calendar_wrapper_leap_year_month

    SUBROUTINE cxios_get_calendar_wrapper_leap_year_month(calendar_wrapper_hdl, leap_year_month) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      INTEGER (KIND=C_INT)             :: leap_year_month
    END SUBROUTINE cxios_get_calendar_wrapper_leap_year_month

    FUNCTION cxios_is_defined_calendar_wrapper_leap_year_month(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_leap_year_month
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_leap_year_month


    SUBROUTINE cxios_set_calendar_wrapper_month_lengths(calendar_wrapper_hdl, month_lengths, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: calendar_wrapper_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: month_lengths
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_calendar_wrapper_month_lengths

    SUBROUTINE cxios_get_calendar_wrapper_month_lengths(calendar_wrapper_hdl, month_lengths, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: calendar_wrapper_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: month_lengths
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_calendar_wrapper_month_lengths

    FUNCTION cxios_is_defined_calendar_wrapper_month_lengths(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_month_lengths
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_month_lengths


    SUBROUTINE cxios_set_calendar_wrapper_start_date(calendar_wrapper_hdl, start_date, start_date_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: start_date
      INTEGER  (kind = C_INT)     , VALUE        :: start_date_size
    END SUBROUTINE cxios_set_calendar_wrapper_start_date

    SUBROUTINE cxios_get_calendar_wrapper_start_date(calendar_wrapper_hdl, start_date, start_date_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: start_date
      INTEGER  (kind = C_INT)     , VALUE        :: start_date_size
    END SUBROUTINE cxios_get_calendar_wrapper_start_date

    FUNCTION cxios_is_defined_calendar_wrapper_start_date(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_start_date
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_start_date


    SUBROUTINE cxios_set_calendar_wrapper_time_origin(calendar_wrapper_hdl, time_origin, time_origin_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_origin
      INTEGER  (kind = C_INT)     , VALUE        :: time_origin_size
    END SUBROUTINE cxios_set_calendar_wrapper_time_origin

    SUBROUTINE cxios_get_calendar_wrapper_time_origin(calendar_wrapper_hdl, time_origin, time_origin_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_origin
      INTEGER  (kind = C_INT)     , VALUE        :: time_origin_size
    END SUBROUTINE cxios_get_calendar_wrapper_time_origin

    FUNCTION cxios_is_defined_calendar_wrapper_time_origin(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_time_origin
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_time_origin


    SUBROUTINE cxios_set_calendar_wrapper_timestep(calendar_wrapper_hdl, timestep) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      TYPE(txios(duration)), VALUE :: timestep
    END SUBROUTINE cxios_set_calendar_wrapper_timestep

    SUBROUTINE cxios_get_calendar_wrapper_timestep(calendar_wrapper_hdl, timestep) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      TYPE(txios(duration)) :: timestep
    END SUBROUTINE cxios_get_calendar_wrapper_timestep

    FUNCTION cxios_is_defined_calendar_wrapper_timestep(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_timestep
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_timestep


    SUBROUTINE cxios_set_calendar_wrapper_type(calendar_wrapper_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_calendar_wrapper_type

    SUBROUTINE cxios_get_calendar_wrapper_type(calendar_wrapper_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_calendar_wrapper_type

    FUNCTION cxios_is_defined_calendar_wrapper_type(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_type
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_type


    SUBROUTINE cxios_set_calendar_wrapper_year_length(calendar_wrapper_hdl, year_length) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      INTEGER (KIND=C_INT)      , VALUE :: year_length
    END SUBROUTINE cxios_set_calendar_wrapper_year_length

    SUBROUTINE cxios_get_calendar_wrapper_year_length(calendar_wrapper_hdl, year_length) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
      INTEGER (KIND=C_INT)             :: year_length
    END SUBROUTINE cxios_get_calendar_wrapper_year_length

    FUNCTION cxios_is_defined_calendar_wrapper_year_length(calendar_wrapper_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_calendar_wrapper_year_length
      INTEGER (kind = C_INTPTR_T), VALUE :: calendar_wrapper_hdl
    END FUNCTION cxios_is_defined_calendar_wrapper_year_length

  END INTERFACE

END MODULE calendar_wrapper_interface_attr
