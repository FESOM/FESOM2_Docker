#include "xios_fortran_prefix.hpp"

MODULE IDURATION
   USE, INTRINSIC :: ISO_C_BINDING
   USE DURATION_INTERFACE

   TYPE(txios(duration)), PARAMETER :: xios(year) = txios(duration)(1, 0, 0, 0, 0, 0, 0)
   TYPE(txios(duration)), PARAMETER :: xios(month) = txios(duration)(0, 1, 0, 0, 0, 0, 0)
   TYPE(txios(duration)), PARAMETER :: xios(day) = txios(duration)(0, 0, 1, 0, 0, 0, 0)
   TYPE(txios(duration)), PARAMETER :: xios(hour) = txios(duration)(0, 0, 0, 1, 0, 0, 0)
   TYPE(txios(duration)), PARAMETER :: xios(minute) = txios(duration)(0, 0, 0, 0, 1, 0, 0)
   TYPE(txios(duration)), PARAMETER :: xios(second) = txios(duration)(0, 0, 0, 0, 0, 1, 0)
   TYPE(txios(duration)), PARAMETER :: xios(timestep) = txios(duration)(0, 0, 0, 0, 0, 0, 1)

   INTERFACE OPERATOR(+)
      MODULE PROCEDURE xios(duration_add)
   END INTERFACE

   INTERFACE OPERATOR(-)
      MODULE PROCEDURE xios(duration_sub)
      MODULE PROCEDURE xios(duration_neg)
   END INTERFACE

   INTERFACE OPERATOR(*)
      MODULE PROCEDURE xios(real4_duration_mult)
      MODULE PROCEDURE xios(duration_real4_mult)
      MODULE PROCEDURE xios(real8_duration_mult)
      MODULE PROCEDURE xios(duration_real8_mult)
      MODULE PROCEDURE xios(int_duration_mult)
      MODULE PROCEDURE xios(duration_int_mult)
   END INTERFACE

   INTERFACE xios(duration_mult)
      MODULE PROCEDURE xios(real4_duration_mult)
      MODULE PROCEDURE xios(duration_real4_mult)
      MODULE PROCEDURE xios(real8_duration_mult)
      MODULE PROCEDURE xios(duration_real8_mult)
      MODULE PROCEDURE xios(int_duration_mult)
      MODULE PROCEDURE xios(duration_int_mult)
   END INTERFACE

   INTERFACE OPERATOR(==)
      MODULE PROCEDURE xios(duration_eq)
   END INTERFACE

   INTERFACE OPERATOR(/=)
      MODULE PROCEDURE xios(duration_neq)
   END INTERFACE

   CONTAINS

   ! Conversion function

   SUBROUTINE xios(duration_convert_to_string)(dur, str)
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur
      CHARACTER(len = *), INTENT(OUT) :: str

      CALL cxios_duration_convert_to_string(dur, str, len(str))
   END SUBROUTINE xios(duration_convert_to_string)

   FUNCTION xios(duration_convert_from_string)(str) RESULT(res)
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: str
      TYPE(txios(duration)) :: res

      res = cxios_duration_convert_from_string(str, len(str))
   END FUNCTION xios(duration_convert_from_string)

   ! Addition

   FUNCTION xios(duration_add)(dur1, dur2) RESULT(res)
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur1, dur2
      TYPE(txios(duration)) :: res

      res = cxios_duration_add(dur1, dur2)
   END FUNCTION xios(duration_add)

   ! Subtraction

   FUNCTION xios(duration_sub)(dur1, dur2) RESULT(res)
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur1, dur2
      TYPE(txios(duration)) :: res

      res = cxios_duration_sub(dur1, dur2)
   END FUNCTION xios(duration_sub)

   ! Multiplication by a scalar
   
   FUNCTION xios(real4_duration_mult)(val, dur) RESULT(res)
      USE ISO_C_BINDING
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      REAL(kind = C_FLOAT), INTENT(IN) :: val
      TYPE(txios(duration)), INTENT(IN) :: dur
      TYPE(txios(duration)) :: res

      res = cxios_duration_mult(REAL(val, C_DOUBLE), dur)
   END FUNCTION xios(real4_duration_mult)
   
   FUNCTION xios(duration_real4_mult)(dur, val2) RESULT(res)
      USE ISO_C_BINDING
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur
      REAL(kind = C_FLOAT), INTENT(IN) :: val2
      TYPE(txios(duration)) :: res

      res = cxios_duration_mult(REAL(val2, C_DOUBLE), dur)
   END FUNCTION xios(duration_real4_mult)
   
   FUNCTION xios(real8_duration_mult)(val, dur) RESULT(res)
      USE ISO_C_BINDING
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      REAL(kind = C_DOUBLE), INTENT(IN) :: val
      TYPE(txios(duration)), INTENT(IN) :: dur
      TYPE(txios(duration)) :: res

      res = cxios_duration_mult(val, dur)
   END FUNCTION xios(real8_duration_mult)
   
   FUNCTION xios(duration_real8_mult)(dur, val2) RESULT(res)
      USE ISO_C_BINDING
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur
      REAL(kind = C_DOUBLE), INTENT(IN) :: val2
      TYPE(txios(duration)) :: res

      res = cxios_duration_mult(val2, dur)
   END FUNCTION xios(duration_real8_mult)
   
   FUNCTION xios(int_duration_mult)(val, dur) RESULT(res)
      USE ISO_C_BINDING
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      INTEGER, INTENT(IN) :: val
      TYPE(txios(duration)), INTENT(IN) :: dur
      TYPE(txios(duration)) :: res

      res = cxios_duration_mult(REAL(val, C_DOUBLE), dur)
   END FUNCTION xios(int_duration_mult)
   
   FUNCTION xios(duration_int_mult)(dur, val2) RESULT(res)
      USE ISO_C_BINDING
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur
      INTEGER, INTENT(IN) :: val2
      TYPE(txios(duration)) :: res

      res = cxios_duration_mult(REAL(val2, C_DOUBLE), dur)
   END FUNCTION xios(duration_int_mult)

   ! Negation

   FUNCTION xios(duration_neg)(dur) RESULT(res)
      USE DURATION_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur
      TYPE(txios(duration)) :: res

      res = cxios_duration_neg(dur)
   END FUNCTION xios(duration_neg)

   FUNCTION xios(duration_eq)(dur1, dur2) RESULT(res)
      USE duration_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur1, dur2
      LOGICAL :: res

      res = cxios_duration_eq(dur1, dur2)
   END FUNCTION xios(duration_eq)

   FUNCTION xios(duration_neq)(dur1, dur2) RESULT(res)
      USE duration_INTERFACE, only : txios(duration)
      IMPLICIT NONE
      TYPE(txios(duration)), INTENT(IN) :: dur1, dur2
      LOGICAL :: res

      res = cxios_duration_neq(dur1, dur2)
   END FUNCTION xios(duration_neq)

END MODULE IDURATION
