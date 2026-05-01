#include "xios_fortran_prefix.hpp"

MODULE CALENDAR_INTERFACE
   USE, INTRINSIC :: ISO_C_BINDING

   INTERFACE ! Ne pas appeler directement/Interface FORTRAN 2003 <-> C99

      SUBROUTINE cxios_update_calendar(step) BIND(C)
         IMPORT C_INT
         INTEGER (kind = C_INT), VALUE :: step
      END SUBROUTINE cxios_update_calendar

      SUBROUTINE cxios_get_current_date(current_date) BIND(C)
         USE IDATE
         TYPE(txios(date))             :: current_date
      END SUBROUTINE cxios_get_current_date

      INTEGER(kind = C_INT) FUNCTION cxios_get_year_length_in_seconds(year) BIND(C)
         USE ISO_C_BINDING
         INTEGER(kind = C_INT), VALUE :: year
      END FUNCTION cxios_get_year_length_in_seconds

      INTEGER(kind = C_INT) FUNCTION cxios_get_day_length_in_seconds() BIND(C)
         USE ISO_C_BINDING
      END FUNCTION cxios_get_day_length_in_seconds

   END INTERFACE

END MODULE CALENDAR_INTERFACE
