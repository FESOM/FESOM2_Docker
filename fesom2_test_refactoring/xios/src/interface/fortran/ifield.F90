#include "xios_fortran_prefix.hpp"

MODULE IFIELD
   USE, INTRINSIC :: ISO_C_BINDING
   USE FIELD_INTERFACE
   USE FIELDGROUP_INTERFACE
!   USE IFIELD_ATTR
!   USE IFIELDGROUP_ATTR
   USE IDURATION
   USE IDOMAIN
   USE IAXIS
   USE ISCALAR
   
   TYPE txios(field)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(field)
   
   TYPE txios(fieldgroup)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(fieldgroup)

   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_field_handle)(idt, ret)
      IMPLICIT NONE
      CHARACTER(len = *), INTENT(IN)   :: idt      
      TYPE(txios(field)), INTENT(OUT) :: ret
      CALL cxios_field_handle_create(ret%daddr, idt, len(idt))            
   END SUBROUTINE xios(get_field_handle)
   
   SUBROUTINE xios(get_fieldgroup_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *)     , INTENT(IN) :: idt      
      TYPE(txios(fieldgroup)), INTENT(OUT):: ret

      CALL cxios_fieldgroup_handle_create(ret%daddr, idt, len(idt))            

   END SUBROUTINE xios(get_fieldgroup_handle)
   
   SUBROUTINE xios(field_id_get_domain_handle)(field_id, ret, idx)
      IMPLICIT NONE
      CHARACTER(len  = *)     , INTENT(IN)  :: field_id
      INTEGER, OPTIONAL       , INTENT(IN)  :: idx
      TYPE(txios(domain)), INTENT(OUT) :: ret
      TYPE(txios(field))      :: field_hdl
      INTEGER                 :: index
      index = 0
      IF (PRESENT(idx)) THEN
        index = idx
      ENDIF

      CALL xios(get_field_handle)(field_id,field_hdl)
      CALL xios(field_get_domain_handle(field_hdl, ret, index))
   END SUBROUTINE xios(field_id_get_domain_handle)

   SUBROUTINE xios(field_get_domain_handle)(field_hdl, ret, idx)
      IMPLICIT NONE
      TYPE(txios(field))      , INTENT(IN)  :: field_hdl
      INTEGER, OPTIONAL       , INTENT(IN)  :: idx
      TYPE(txios(domain)), INTENT(OUT) :: ret
      INTEGER :: index
      index = 0
      IF (PRESENT(idx)) THEN
        index = idx
      ENDIF
      CALL cxios_field_get_domain_handle(ret%daddr, field_hdl%daddr, index)
   END SUBROUTINE xios(field_get_domain_handle)

   SUBROUTINE xios(field_id_get_axis_handle)(field_id, ret, idx)
      IMPLICIT NONE
      CHARACTER(len  = *)   , INTENT(IN)  :: field_id
      INTEGER, OPTIONAL     , INTENT(IN)  :: idx
      TYPE(txios(axis)), INTENT(OUT) :: ret
      TYPE(txios(field))     :: field_hdl
      INTEGER                :: index
      index = 0
      IF (PRESENT(idx)) THEN
        index = idx
      ENDIF
      CALL xios(get_field_handle)(field_id,field_hdl)
      CALL xios(field_get_axis_handle(field_hdl, ret, index))
   END SUBROUTINE xios(field_id_get_axis_handle)

   SUBROUTINE xios(field_get_axis_handle)(field_hdl, ret, idx)
      IMPLICIT NONE
      TYPE(txios(field))    , INTENT(IN)  :: field_hdl
      INTEGER, OPTIONAL     , INTENT(IN)  :: idx
      TYPE(txios(axis)), INTENT(OUT) :: ret
      INTEGER :: index
      index = 0
      IF (PRESENT(idx)) THEN
        index = idx
      ENDIF
      CALL cxios_field_get_axis_handle(ret%daddr, field_hdl%daddr, index)
   END SUBROUTINE xios(field_get_axis_handle)

   SUBROUTINE xios(field_id_get_scalar_handle)(field_id, ret, idx)
      IMPLICIT NONE
      CHARACTER(len  = *)     , INTENT(IN)  :: field_id
      INTEGER, OPTIONAL       , INTENT(IN)  :: idx
      TYPE(txios(scalar)), INTENT(OUT) :: ret
      TYPE(txios(field))     :: field_hdl
      INTEGER                :: index
      index = 0
      IF (PRESENT(idx)) THEN
        index = idx
      ENDIF
      CALL xios(get_field_handle)(field_id,field_hdl)
      CALL xios(field_get_scalar_handle(field_hdl, ret, index))
   END SUBROUTINE xios(field_id_get_scalar_handle)

   SUBROUTINE xios(field_get_scalar_handle)(field_hdl, ret, idx)
      IMPLICIT NONE
      TYPE(txios(field))      , INTENT(IN)  :: field_hdl
      INTEGER, OPTIONAL       , INTENT(IN)  :: idx
      TYPE(txios(scalar)), INTENT(OUT) :: ret
      INTEGER :: index
      index = 0
      IF (PRESENT(idx)) THEN
        index = idx
      ENDIF
      CALL cxios_field_get_axis_handle(ret%daddr, field_hdl%daddr, index)
   END SUBROUTINE xios(field_get_scalar_handle)

   LOGICAL FUNCTION xios(is_valid_field)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val
      
      CALL cxios_field_valid_id(val, idt, len(idt));
      xios(is_valid_field) = val

   END FUNCTION  xios(is_valid_field)

   LOGICAL FUNCTION xios(is_valid_fieldgroup)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val
      CALL cxios_fieldgroup_valid_id(val, idt, len(idt));
      xios(is_valid_fieldgroup) = val

   END FUNCTION  xios(is_valid_fieldgroup)
   
  LOGICAL FUNCTION xios(field_is_active_id)(field_id, at_current_timestep_arg)
      IMPLICIT NONE
      CHARACTER(len  = *) , INTENT(IN) :: field_id
      LOGICAL, OPTIONAL   , INTENT(IN) :: at_current_timestep_arg
      TYPE(txios(field))               :: field_hdl

      CALL xios(get_field_handle)(field_id,field_hdl)
      xios(field_is_active_id) = xios(field_is_active_hdl)(field_hdl, at_current_timestep_arg)

   END FUNCTION xios(field_is_active_id)

   LOGICAL FUNCTION xios(field_is_active_hdl)(field_hdl, at_current_timestep_arg)
      IMPLICIT NONE
      TYPE(txios(field)) , INTENT(IN) :: field_hdl
      LOGICAL, OPTIONAL  , INTENT(IN) :: at_current_timestep_arg
      LOGICAL(kind = C_BOOL)          :: at_current_timestep
      LOGICAL(kind = C_BOOL)          :: ret

      IF (PRESENT(at_current_timestep_arg)) THEN
         at_current_timestep = at_current_timestep_arg
      ELSE
         at_current_timestep = .FALSE.
      ENDIF

      CALL cxios_field_is_active(field_hdl%daddr, at_current_timestep, ret);
      xios(field_is_active_hdl) = ret
      
   END FUNCTION xios(field_is_active_hdl)
 
END MODULE IFIELD
