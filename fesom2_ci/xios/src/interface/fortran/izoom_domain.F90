#include "xios_fortran_prefix.hpp"

MODULE IZOOM_DOMAIN
   USE, INTRINSIC :: ISO_C_BINDING
   USE ZOOM_DOMAIN_INTERFACE

   TYPE txios(zoom_domain)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(zoom_domain)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_zoom_domain_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(zoom_domain)) , INTENT(OUT):: ret
      CALL cxios_zoom_domain_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_zoom_domain_handle)

   LOGICAL FUNCTION xios(is_valid_zoom_domain)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_zoom_domain_valid_id(val, idt, len(idt))
      xios(is_valid_zoom_domain) = val

   END FUNCTION  xios(is_valid_zoom_domain)

END MODULE IZOOM_DOMAIN
