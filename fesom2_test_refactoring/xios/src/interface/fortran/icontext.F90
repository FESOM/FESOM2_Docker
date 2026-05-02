#include "xios_fortran_prefix.hpp"

MODULE ICONTEXT
   USE, INTRINSIC :: ISO_C_BINDING
   USE CONTEXT_INTERFACE
   USE IDATE
   USE IDURATION
!   USE icontext_attr


   TYPE txios(context)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(context)

   INTERFACE xios(set_current_context)
      MODULE PROCEDURE xios(set_current_context_hdl), xios(set_current_context_id)
   END INTERFACE xios(set_current_context)

   INTERFACE xios(get_current_context)
      MODULE PROCEDURE xios(get_current_context_hdl), xios(get_current_context_id)
   END INTERFACE xios(get_current_context)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_context_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *)  , INTENT(IN)  :: idt
      TYPE(txios(context)), INTENT(OUT):: ret

      CALL cxios_context_handle_create(ret%daddr, idt, len(idt))
   END SUBROUTINE xios(get_context_handle)

   SUBROUTINE xios(get_current_context_hdl)(context)
      IMPLICIT NONE

      TYPE(txios(context)), INTENT(OUT) :: context

      CALL cxios_context_get_current(context%daddr)

   END SUBROUTINE xios(get_current_context_hdl)

   SUBROUTINE xios(get_current_context_id)(idt)
      IMPLICIT NONE
      CHARACTER(len = *) , INTENT(OUT) :: idt
      TYPE(txios(context)) :: context

      CALL cxios_context_get_current(context%daddr)
      CALL cxios_context_get_id(context%daddr, idt, len(idt))

   END SUBROUTINE xios(get_current_context_id)
   
   SUBROUTINE xios(set_current_context_hdl)(context, withswap)
      IMPLICIT NONE

      TYPE(txios(context))          , INTENT(IN) :: context
      LOGICAL             , OPTIONAL, INTENT(IN) :: withswap
      LOGICAL (kind = 1)                         :: wswap

      IF (PRESENT(withswap)) THEN
         wswap = withswap
      ELSE
         wswap = .FALSE.
      END IF
      CALL cxios_context_set_current(context%daddr, wswap)

   END SUBROUTINE xios(set_current_context_hdl)

   SUBROUTINE xios(set_current_context_id)(idt)
      IMPLICIT NONE

      CHARACTER(len = *) , INTENT(IN) :: idt
      LOGICAL           :: withswap
      TYPE(xios_context):: ret

      CALL xios(get_context_handle)(idt,ret)
      CALL xios(set_current_context_hdl)(ret, withswap)
    END SUBROUTINE xios(set_current_context_id)

   LOGICAL FUNCTION xios(is_valid_context)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_context_valid_id(val, idt, len(idt));
      xios(is_valid_context) = val

   END FUNCTION  xios(is_valid_context)


END MODULE ICONTEXT
