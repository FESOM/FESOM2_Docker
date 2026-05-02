#include "xios_fortran_prefix.hpp"

MODULE ITIMER
   USE, INTRINSIC :: ISO_C_BINDING
   USE TIMER_INTERFACE

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(timer_resume)(timer_id, trace)
      IMPLICIT NONE
      CHARACTER(len = *) , INTENT(IN) :: timer_id
      LOGICAL, OPTIONAL,INTENT(IN)    :: trace
      LOGICAL (KIND=C_BOOL)           :: trace_           

      trace_=.TRUE.
      IF (PRESENT(trace)) trace_ = trace
      CALL cxios_timer_resume(timer_id, len(timer_id),trace_)            

   END SUBROUTINE xios(timer_resume)

   SUBROUTINE xios(timer_suspend)(timer_id, trace)
      IMPLICIT NONE
      CHARACTER(len = *) , INTENT(IN) :: timer_id
      LOGICAL, OPTIONAL,INTENT(IN)    :: trace
      LOGICAL (KIND=C_BOOL)           :: trace_               

      trace_=.TRUE.
      IF (PRESENT(trace)) trace_ = trace
      CALL cxios_timer_suspend(timer_id, len(timer_id),trace_)            

   END SUBROUTINE xios(timer_suspend)

   SUBROUTINE xios(timer_reset)(timer_id)
      IMPLICIT NONE
      CHARACTER(len = *) , INTENT(IN) :: timer_id

      CALL cxios_timer_reset(timer_id, len(timer_id))            

   END SUBROUTINE xios(timer_reset)

   FUNCTION xios(timer_get_time)(timer_id) RESULT(time)
      IMPLICIT NONE
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: timer_id
      REAL                                      :: time
      REAL(KIND=C_DOUBLE)                         :: time_
      
      IF (PRESENT(timer_id)) THEN
         CALL cxios_timer_get_cumulated_time(timer_id, len(timer_id),time_) 
      ELSE
         CALL cxios_timer_get_time(time_)
      ENDIF      
      time=time_
   END FUNCTION xios(timer_get_time)
 
END MODULE ITIMER
