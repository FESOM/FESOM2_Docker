#include "xios_fortran_prefix.hpp"

MODULE IZOOM_AXIS
   USE, INTRINSIC :: ISO_C_BINDING
   USE ZOOM_AXIS_INTERFACE

   TYPE txios(zoom_axis)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(zoom_axis)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_zoom_axis_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(zoom_axis)) , INTENT(OUT):: ret
      CALL cxios_zoom_axis_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_zoom_axis_handle)

   LOGICAL FUNCTION xios(is_valid_zoom_axis)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_zoom_axis_valid_id(val, idt, len(idt))
      xios(is_valid_zoom_axis) = val

   END FUNCTION  xios(is_valid_zoom_axis)

END MODULE IZOOM_AXIS
