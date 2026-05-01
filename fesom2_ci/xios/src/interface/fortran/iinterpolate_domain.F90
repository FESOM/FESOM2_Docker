#include "xios_fortran_prefix.hpp"

MODULE IINTERPOLATE_DOMAIN
   USE, INTRINSIC :: ISO_C_BINDING
   USE INTERPOLATE_DOMAIN_INTERFACE

   TYPE txios(interpolate_domain)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(interpolate_domain)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_interpolate_domain_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(interpolate_domain)) , INTENT(OUT):: ret
      CALL cxios_interpolate_domain_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_interpolate_domain_handle)

   LOGICAL FUNCTION xios(is_valid_interpolate_domain)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_interpolate_domain_valid_id(val, idt, len(idt))
      xios(is_valid_interpolate_domain) = val

   END FUNCTION  xios(is_valid_interpolate_domain)

END MODULE IINTERPOLATE_DOMAIN
