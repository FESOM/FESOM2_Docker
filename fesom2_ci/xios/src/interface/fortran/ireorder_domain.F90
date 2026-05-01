#include "xios_fortran_prefix.hpp"

MODULE IREORDER_DOMAIN
   USE, INTRINSIC :: ISO_C_BINDING
   USE REORDER_DOMAIN_INTERFACE

   TYPE txios(reorder_domain)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(reorder_domain)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_reorder_domain_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(reorder_domain)) , INTENT(OUT):: ret
      CALL cxios_reorder_domain_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_reorder_domain_handle)

   LOGICAL FUNCTION xios(is_valid_reorder_domain)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_reorder_domain_valid_id(val, idt, len(idt))
      xios(is_valid_reorder_domain) = val

   END FUNCTION  xios(is_valid_reorder_domain)

END MODULE IREORDER_DOMAIN
