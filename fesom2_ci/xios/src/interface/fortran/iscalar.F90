#include "xios_fortran_prefix.hpp"

MODULE ISCALAR
   USE, INTRINSIC :: ISO_C_BINDING
   USE SCALAR_INTERFACE
   USE SCALARGROUP_INTERFACE

   TYPE txios(scalar)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(scalar)

   TYPE txios(scalargroup)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(scalargroup)



   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_scalar_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt
      TYPE(txios(scalar)) , INTENT(OUT):: ret
      CALL cxios_scalar_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_scalar_handle)

   SUBROUTINE xios(get_scalargroup_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *)    , INTENT(IN) :: idt
      TYPE(txios(scalargroup)), INTENT(OUT):: ret

      CALL cxios_scalargroup_handle_create(ret%daddr, idt, len(idt))

   END SUBROUTINE xios(get_scalargroup_handle)

   LOGICAL FUNCTION xios(is_valid_scalar)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_scalar_valid_id(val, idt, len(idt))
      xios(is_valid_scalar) = val

   END FUNCTION  xios(is_valid_scalar)

   LOGICAL FUNCTION xios(is_valid_scalargroup)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_scalargroup_valid_id(val, idt, len(idt))
      xios(is_valid_scalargroup) = val

   END FUNCTION  xios(is_valid_scalargroup)

END MODULE ISCALAR
