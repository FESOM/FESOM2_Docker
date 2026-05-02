#include "xios_fortran_prefix.hpp"

MODULE IINTERPOLATE_AXIS
   USE, INTRINSIC :: ISO_C_BINDING
   USE INTERPOLATE_AXIS_INTERFACE

   TYPE txios(interpolate_axis)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(interpolate_axis)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_interpolate_axis_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(interpolate_axis)) , INTENT(OUT):: ret
      CALL cxios_interpolate_axis_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_interpolate_axis_handle)

   LOGICAL FUNCTION xios(is_valid_interpolate_axis)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_interpolate_axis_valid_id(val, idt, len(idt))
      xios(is_valid_interpolate_axis) = val

   END FUNCTION  xios(is_valid_interpolate_axis)

END MODULE IINTERPOLATE_AXIS
