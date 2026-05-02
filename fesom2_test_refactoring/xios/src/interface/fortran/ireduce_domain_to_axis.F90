#include "xios_fortran_prefix.hpp"

MODULE IREDUCE_DOMAIN_TO_AXIS
   USE, INTRINSIC :: ISO_C_BINDING
   USE REDUCE_DOMAIN_TO_AXIS_INTERFACE

   TYPE txios(reduce_domain_to_axis)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(reduce_domain_to_axis)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_reduce_domain_to_axis_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(reduce_domain_to_axis)) , INTENT(OUT):: ret
      CALL cxios_reduce_domain_to_axis_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_reduce_domain_to_axis_handle)

   LOGICAL FUNCTION xios(is_valid_reduce_domain_to_axis)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_reduce_domain_to_axis_valid_id(val, idt, len(idt))
      xios(is_valid_reduce_domain_to_axis) = val

   END FUNCTION  xios(is_valid_reduce_domain_to_axis)

END MODULE IREDUCE_DOMAIN_TO_AXIS
