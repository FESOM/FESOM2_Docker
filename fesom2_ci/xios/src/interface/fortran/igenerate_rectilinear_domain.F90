#include "xios_fortran_prefix.hpp"

MODULE IGENERATE_RECTILINEAR_DOMAIN
   USE, INTRINSIC :: ISO_C_BINDING
   USE GENERATE_RECTILINEAR_DOMAIN_INTERFACE

   TYPE txios(generate_rectilinear_domain)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(generate_rectilinear_domain)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_generate_rectilinear_domain_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(generate_rectilinear_domain)) , INTENT(OUT):: ret
      CALL cxios_generate_rectilinear_domain_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_generate_rectilinear_domain_handle)

   LOGICAL FUNCTION xios(is_valid_generate_rectilinear_domain)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_generate_rectilinear_domain_valid_id(val, idt, len(idt))
      xios(is_valid_generate_rectilinear_domain) = val

   END FUNCTION  xios(is_valid_generate_rectilinear_domain)

END MODULE IGENERATE_RECTILINEAR_DOMAIN
