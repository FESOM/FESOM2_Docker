#include "../fortran/xios_fortran_prefix.hpp"

MODULE DATE_INTERFACE
   USE, INTRINSIC :: ISO_C_BINDING
   USE IDURATION, only : txios(duration)

   TYPE, BIND(C) :: txios(date)
      INTEGER(kind = C_INT) :: year, month, day, hour, minute, second
   END TYPE txios(date)

   PRIVATE :: txios(duration)

   INTERFACE ! Ne pas appeler directement/Interface FORTRAN 2003 <-> C99

      INTEGER(kind = C_LONG_LONG) FUNCTION cxios_date_convert_to_seconds(date) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date
      END FUNCTION cxios_date_convert_to_seconds

      SUBROUTINE cxios_date_convert_to_string(date, str, str_size) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date
         CHARACTER(kind = C_CHAR), DIMENSION(*) :: str
         INTEGER(kind = C_INT), VALUE :: str_size
      END SUBROUTINE cxios_date_convert_to_string

      TYPE(txios(date)) FUNCTION cxios_date_convert_from_string(str, str_size) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         CHARACTER(kind = C_CHAR), DIMENSION(*) :: str
         INTEGER(kind = C_INT), VALUE :: str_size
      END FUNCTION cxios_date_convert_from_string

      TYPE(txios(date)) FUNCTION cxios_date_add_duration(date, dur) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         IMPORT :: txios(duration)
         TYPE(txios(date)), VALUE :: date
         TYPE(txios(duration)), VALUE :: dur
      END FUNCTION cxios_date_add_duration

      TYPE(txios(date)) FUNCTION cxios_date_sub_duration(date, dur) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         IMPORT :: txios(duration)
         TYPE(txios(date)), VALUE :: date
         TYPE(txios(duration)), VALUE :: dur
      END FUNCTION cxios_date_sub_duration

      TYPE(txios(duration)) FUNCTION cxios_date_sub(date1, date2) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         IMPORT :: txios(duration)
         TYPE(txios(date)), VALUE :: date1, date2
      END FUNCTION cxios_date_sub

      LOGICAL(kind = C_BOOL) FUNCTION cxios_date_eq(date1, date2) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date1, date2
      END FUNCTION cxios_date_eq

      LOGICAL(kind = C_BOOL) FUNCTION cxios_date_neq(date1, date2) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date1, date2
      END FUNCTION cxios_date_neq

      LOGICAL(kind = C_BOOL) FUNCTION cxios_date_lt(date1, date2) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date1, date2
      END FUNCTION cxios_date_lt

      LOGICAL(kind = C_BOOL) FUNCTION cxios_date_le(date1, date2) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date1, date2
      END FUNCTION cxios_date_le

      LOGICAL(kind = C_BOOL) FUNCTION cxios_date_gt(date1, date2) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date1, date2
      END FUNCTION cxios_date_gt

      LOGICAL(kind = C_BOOL) FUNCTION cxios_date_ge(date1, date2) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date1, date2
      END FUNCTION cxios_date_ge

      INTEGER(kind = C_INT) FUNCTION cxios_date_get_second_of_year(date) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date
      END FUNCTION cxios_date_get_second_of_year

      REAL(kind = C_DOUBLE) FUNCTION cxios_date_get_day_of_year(date) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date
      END FUNCTION cxios_date_get_day_of_year

      REAL(kind = C_DOUBLE) FUNCTION cxios_date_get_fraction_of_year(date) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date
      END FUNCTION cxios_date_get_fraction_of_year

      INTEGER(kind = C_INT) FUNCTION cxios_date_get_second_of_day(date) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date
      END FUNCTION cxios_date_get_second_of_day

      REAL(kind = C_DOUBLE) FUNCTION cxios_date_get_fraction_of_day(date) BIND(C)
         USE ISO_C_BINDING
         IMPORT :: txios(date)
         TYPE(txios(date)), VALUE :: date
      END FUNCTION cxios_date_get_fraction_of_day

   END INTERFACE

END MODULE DATE_INTERFACE
