#include "xios_fortran_prefix.hpp"

MODULE ICOMPUTE_CONNECTIVITY_DOMAIN
   USE, INTRINSIC :: ISO_C_BINDING
   USE COMPUTE_CONNECTIVITY_DOMAIN_INTERFACE

   TYPE txios(compute_connectivity_domain)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(compute_connectivity_domain)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_compute_connectivity_domain_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(compute_connectivity_domain)) , INTENT(OUT):: ret
      CALL cxios_compute_connectivity_domain_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_compute_connectivity_domain_handle)

   LOGICAL FUNCTION xios(is_valid_compute_connectivity_domain)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_compute_connectivity_domain_valid_id(val, idt, len(idt))
      xios(is_valid_compute_connectivity_domain) = val

   END FUNCTION  xios(is_valid_compute_connectivity_domain)

END MODULE ICOMPUTE_CONNECTIVITY_DOMAIN
