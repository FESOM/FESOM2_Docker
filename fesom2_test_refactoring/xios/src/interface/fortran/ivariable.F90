#include "xios_fortran_prefix.hpp"

MODULE IVARIABLE
   USE, INTRINSIC :: ISO_C_BINDING
   USE VARIABLE_INTERFACE
   USE VARIABLEGROUP_INTERFACE
   
   TYPE txios(variable)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(variable)
   
   TYPE txios(variablegroup)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(variablegroup)
   

         
   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_variable_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN) :: idt      
      TYPE(txios(variable)) , INTENT(OUT):: ret
      CALL cxios_variable_handle_create(ret%daddr, idt, len(idt))            
   END SUBROUTINE xios(get_variable_handle)
   
   SUBROUTINE xios(get_variablegroup_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *)    , INTENT(IN) :: idt      
      TYPE(txios(variablegroup)), INTENT(OUT):: ret

      CALL cxios_variablegroup_handle_create(ret%daddr, idt, len(idt))            

   END SUBROUTINE xios(get_variablegroup_handle)

   LOGICAL FUNCTION xios(is_valid_variable)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val
      
      CALL cxios_variable_valid_id(val, idt, len(idt))
      xios(is_valid_variable) = val

   END FUNCTION  xios(is_valid_variable)

   LOGICAL FUNCTION xios(is_valid_variablegroup)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_variablegroup_valid_id(val, idt, len(idt))
      xios(is_valid_variablegroup) = val

   END FUNCTION  xios(is_valid_variablegroup)

END MODULE IVARIABLE
