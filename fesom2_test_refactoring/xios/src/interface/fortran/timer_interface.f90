MODULE TIMER_INTERFACE
   USE, INTRINSIC :: ISO_C_BINDING
       
   INTERFACE ! Ne pas appeler directement/Interface FORTRAN 2003 <-> C99
 
      SUBROUTINE cxios_timer_resume(timer_id, len_timer_id, trace) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: timer_id
         INTEGER(kind = C_INT)       , VALUE        :: len_timer_id
         LOGICAL  (kind = C_BOOL)    , VALUE        :: trace
         
      END SUBROUTINE cxios_timer_resume
   
      SUBROUTINE cxios_timer_suspend(timer_id, len_timer_id, trace) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: timer_id
         INTEGER(kind = C_INT)       , VALUE        :: len_timer_id
         LOGICAL  (kind = C_BOOL)    , VALUE        :: trace
      END SUBROUTINE cxios_timer_suspend


      SUBROUTINE cxios_timer_reset(timer_id, len_timer_id) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: timer_id
         INTEGER(kind = C_INT)       , VALUE        :: len_timer_id
      END SUBROUTINE cxios_timer_reset

      SUBROUTINE cxios_timer_get_time(time) BIND(C)
         USE ISO_C_BINDING
         REAL  (kind = C_DOUBLE)                   :: time
      END SUBROUTINE cxios_timer_get_time
 
      SUBROUTINE cxios_timer_get_cumulated_time(timer_id, len_timer_id, time) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: timer_id
         INTEGER(kind = C_INT)       , VALUE        :: len_timer_id
         REAL  (kind = C_DOUBLE)                    :: time
       END SUBROUTINE cxios_timer_get_cumulated_time

   END INTERFACE
       
END MODULE TIMER_INTERFACE