#include "xios_fortran_prefix.hpp"

MODULE IINVERSE_AXIS
   USE, INTRINSIC :: ISO_C_BINDING
   USE INVERSE_AXIS_INTERFACE

   TYPE txios(inverse_axis)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(inverse_axis)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_inverse_axis_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(inverse_axis)) , INTENT(OUT):: ret
      CALL cxios_inverse_axis_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_inverse_axis_handle)

   LOGICAL FUNCTION xios(is_valid_inverse_axis)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_inverse_axis_valid_id(val, idt, len(idt))
      xios(is_valid_inverse_axis) = val

   END FUNCTION  xios(is_valid_inverse_axis)

END MODULE IINVERSE_AXIS
