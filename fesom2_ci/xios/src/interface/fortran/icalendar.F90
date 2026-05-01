#include "xios_fortran_prefix.hpp"
MODULE ICALENDAR
   USE, INTRINSIC :: ISO_C_BINDING
   USE CALENDAR_INTERFACE
   USE ICALENDAR_WRAPPER
   USE IDATE
   USE IDURATION

   ! enum XCalendarType
   INTEGER(kind = C_INT), PARAMETER :: D360 = 0 , ALLLEAP = 1 , NOLEAP = 2 , JULIAN = 3 , GREGORIAN = 4

   INTERFACE xios(set_start_date)
      MODULE PROCEDURE xios(set_start_date_date), xios(set_start_date_dur)
   END INTERFACE xios(set_start_date)

   INTERFACE xios(set_time_origin)
      MODULE PROCEDURE xios(set_time_origin_date), xios(set_time_origin_dur)
   END INTERFACE xios(set_time_origin)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(define_calendar)(type, timestep, start_date, time_origin, &
                                    day_length, month_lengths, year_length, &
                                    leap_year_month, leap_year_drift, leap_year_drift_offset)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE icalendar_wrapper_attr, ONLY : xios(set_calendar_wrapper_attr_hdl)
      USE IDURATION, ONLY : txios(duration)
      USE IDATE, ONLY : txios(date)
      IMPLICIT NONE
      CHARACTER(len = *),              INTENT(IN) :: type
      TYPE(txios(duration)), OPTIONAL, INTENT(IN) :: timestep
      TYPE(txios(date)),     OPTIONAL, INTENT(IN) :: start_date
      TYPE(txios(date)),     OPTIONAL, INTENT(IN) :: time_origin
      INTEGER,               OPTIONAL, INTENT(IN) :: day_length
      INTEGER,               OPTIONAL, INTENT(IN) :: month_lengths(:)
      INTEGER,               OPTIONAL, INTENT(IN) :: year_length
      REAL (KIND=8),         OPTIONAL, INTENT(IN) :: leap_year_drift
      REAL (KIND=8),         OPTIONAL, INTENT(IN) :: leap_year_drift_offset
      INTEGER,               OPTIONAL, INTENT(IN) :: leap_year_month
      TYPE(txios(calendar_wrapper)) :: calendar_wrapper

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, type=type)
      IF (PRESENT(timestep)) THEN
         CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, timestep=timestep)
      END IF
      IF (PRESENT(day_length)) THEN
         CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, day_length=day_length)
      END IF
      IF (PRESENT(month_lengths)) THEN
         CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, month_lengths=month_lengths)
      END IF
      IF (PRESENT(year_length)) THEN
         CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, year_length=year_length)
      END IF
      IF (PRESENT(leap_year_month)) THEN
         CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, leap_year_month=leap_year_month)
      END IF
      IF (PRESENT(leap_year_drift)) THEN
         CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, leap_year_drift=leap_year_drift)
      END IF
      IF (PRESENT(leap_year_drift_offset)) THEN
         CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, leap_year_drift_offset=leap_year_drift_offset)
      END IF

      CALL xios(create_calendar)(calendar_wrapper)

      IF (PRESENT(start_date)) THEN
         CALL xios(set_start_date_hdl)(calendar_wrapper, start_date=start_date)
      END IF
      IF (PRESENT(time_origin)) THEN
         CALL xios(set_time_origin_hdl)(calendar_wrapper, time_origin=time_origin)
      END IF
   END SUBROUTINE xios(define_calendar)

   SUBROUTINE xios(get_calendar_type)(calendar_type)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE icalendar_wrapper_attr, ONLY : xios(get_calendar_wrapper_attr_hdl)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(OUT) :: calendar_type
      TYPE(txios(calendar_wrapper))   :: calendar_wrapper

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      CALL xios(get_calendar_wrapper_attr_hdl)(calendar_wrapper, type=calendar_type)
   END SUBROUTINE xios(get_calendar_type)

   SUBROUTINE xios(set_timestep)(timestep)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE icalendar_wrapper_attr, ONLY : xios(set_calendar_wrapper_attr_hdl)
      USE IDURATION, ONLY : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: timestep
      TYPE(txios(calendar_wrapper))     :: calendar_wrapper

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      CALL xios(set_calendar_wrapper_attr_hdl)(calendar_wrapper, timestep=timestep)

      CALL xios(update_calendar_timestep)(calendar_wrapper)
   END SUBROUTINE xios(set_timestep)

   SUBROUTINE xios(get_timestep)(timestep)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE icalendar_wrapper_attr, ONLY : xios(get_calendar_wrapper_attr_hdl)
      USE IDURATION, ONLY : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(OUT) :: timestep
      TYPE(txios(calendar_wrapper))      :: calendar_wrapper

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      CALL xios(get_calendar_wrapper_attr_hdl)(calendar_wrapper, timestep=timestep)
   END SUBROUTINE xios(get_timestep)

   SUBROUTINE xios(set_start_date_date)(start_date)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE IDATE, ONLY : txios(date)
      IMPLICIT NONE
      TYPE(txios(date)), INTENT(IN) :: start_date
      TYPE(txios(calendar_wrapper)) :: calendar_wrapper

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      CALL xios(set_start_date_hdl)(calendar_wrapper, start_date)
   END SUBROUTINE xios(set_start_date_date)

   SUBROUTINE xios(set_start_date_dur)(start_date)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE IDURATION, ONLY : txios(duration)
      USE IDATE, ONLY : txios(date)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: start_date
      TYPE(txios(calendar_wrapper))     :: calendar_wrapper
      TYPE(txios(date))                 :: start_date_date

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      start_date_date = start_date
      CALL xios(set_start_date_hdl)(calendar_wrapper, start_date_date)
   END SUBROUTINE xios(set_start_date_dur)

   SUBROUTINE xios(get_start_date)(start_date)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE IDATE, ONLY : txios(date)
      IMPLICIT NONE
      TYPE(txios(date)), INTENT(OUT) :: start_date
      TYPE(txios(calendar_wrapper))  :: calendar_wrapper

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      CALL xios(get_start_date_hdl)(calendar_wrapper, start_date)
   END SUBROUTINE xios(get_start_date)

   SUBROUTINE xios(set_time_origin_date)(time_origin)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE IDATE, ONLY : txios(date)
      IMPLICIT NONE
      TYPE(txios(date)), INTENT(IN) :: time_origin
      TYPE(txios(calendar_wrapper)) :: calendar_wrapper

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      CALL xios(set_time_origin_hdl)(calendar_wrapper, time_origin)
   END SUBROUTINE xios(set_time_origin_date)

   SUBROUTINE xios(set_time_origin_dur)(time_origin)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE IDURATION, ONLY : txios(duration)
      USE IDATE, ONLY : txios(date)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: time_origin
      TYPE(txios(calendar_wrapper))     :: calendar_wrapper
      TYPE(txios(date))                 :: time_origin_date

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      time_origin_date = time_origin
      CALL xios(set_time_origin_hdl)(calendar_wrapper, time_origin_date)
   END SUBROUTINE xios(set_time_origin_dur)

   SUBROUTINE xios(get_time_origin)(time_origin)
      USE ICALENDAR_WRAPPER, ONLY : txios(calendar_wrapper), xios(get_default_calendar_wrapper_handle)
      USE IDATE, ONLY : txios(date)
      IMPLICIT NONE
      TYPE(txios(date)), INTENT(OUT) :: time_origin
      TYPE(txios(calendar_wrapper))  :: calendar_wrapper

      CALL xios(get_default_calendar_wrapper_handle)(calendar_wrapper)

      CALL xios(get_time_origin_hdl)(calendar_wrapper, time_origin)
   END SUBROUTINE xios(get_time_origin)

   SUBROUTINE xios(update_calendar)(step)
      IMPLICIT NONE
      INTEGER, INTENT(IN) :: step

      IF (step < 0) THEN
         PRINT *, "L'argument 'step' ne peut être négatif"
         STOP
      END IF
      CALL cxios_update_calendar(step)
   END SUBROUTINE xios(update_calendar)

   SUBROUTINE xios(get_current_date)(current_date)
      USE IDATE, ONLY : txios(date)
      IMPLICIT NONE
      TYPE(txios(date)), INTENT(OUT) :: current_date

      CALL cxios_get_current_date(current_date)
   END SUBROUTINE xios(get_current_date)

   FUNCTION xios(get_year_length_in_seconds)(year) RESULT(res)
      IMPLICIT NONE
      INTEGER(kind = C_INT), INTENT(IN) :: year
      INTEGER(kind = C_INT) :: res

      res = cxios_get_year_length_in_seconds(year)
   END FUNCTION xios(get_year_length_in_seconds)

   FUNCTION xios(get_day_length_in_seconds)() RESULT(res)
      IMPLICIT NONE
      INTEGER(kind = C_INT) :: res

      res = cxios_get_day_length_in_seconds()
   END FUNCTION xios(get_day_length_in_seconds)

END MODULE ICALENDAR
