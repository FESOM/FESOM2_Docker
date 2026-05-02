#include "../fortran/xios_fortran_prefix.hpp"

MODULE CALENDAR_WRAPPER_INTERFACE
   USE, INTRINSIC :: ISO_C_BINDING

   INTERFACE ! Ne pas appeler directement/Interface FORTRAN 2003 <-> C99

      SUBROUTINE cxios_calendar_wrapper_handle_create(ret, idt, idt_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T)               :: ret
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: idt
         INTEGER  (kind = C_INT)     , VALUE        :: idt_size
      END SUBROUTINE cxios_calendar_wrapper_handle_create

      SUBROUTINE cxios_get_current_calendar_wrapper(ret) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T)               :: ret
      END SUBROUTINE cxios_get_current_calendar_wrapper

      SUBROUTINE cxios_calendar_wrapper_valid_id(ret, idt, idt_size) BIND(C)
         USE ISO_C_BINDING
         LOGICAL  (kind = C_BOOL)                   :: ret
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: idt
         INTEGER  (kind = C_INT)     , VALUE        :: idt_size
      END SUBROUTINE cxios_calendar_wrapper_valid_id

      SUBROUTINE cxios_create_calendar(hdl) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: hdl
      END SUBROUTINE cxios_create_calendar

      SUBROUTINE cxios_update_calendar_timestep(hdl) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: hdl
      END SUBROUTINE cxios_update_calendar_timestep

      SUBROUTINE cxios_set_calendar_wrapper_date_start_date(hdl, start_date) BIND(C)
         USE ISO_C_BINDING
         USE IDATE
         INTEGER (kind = C_INTPTR_T), VALUE :: hdl
         TYPE(txios(date)), VALUE           :: start_date
      END SUBROUTINE cxios_set_calendar_wrapper_date_start_date

      SUBROUTINE cxios_get_calendar_wrapper_date_start_date(hdl, start_date) BIND(C)
         USE ISO_C_BINDING
         USE IDATE
         INTEGER (kind = C_INTPTR_T), VALUE :: hdl
         TYPE(txios(date))                  :: start_date
      END SUBROUTINE cxios_get_calendar_wrapper_date_start_date

      SUBROUTINE cxios_set_calendar_wrapper_date_time_origin(hdl, time_origin) BIND(C)
         USE ISO_C_BINDING
         USE IDATE
         INTEGER (kind = C_INTPTR_T), VALUE :: hdl
         TYPE(txios(date)), VALUE           :: time_origin
      END SUBROUTINE cxios_set_calendar_wrapper_date_time_origin

      SUBROUTINE cxios_get_calendar_wrapper_date_time_origin(hdl, time_origin) BIND(C)
         USE ISO_C_BINDING
         USE IDATE
         INTEGER (kind = C_INTPTR_T), VALUE :: hdl
         TYPE(txios(date))                  :: time_origin
      END SUBROUTINE cxios_get_calendar_wrapper_date_time_origin

   END INTERFACE

END MODULE CALENDAR_WRAPPER_INTERFACE
