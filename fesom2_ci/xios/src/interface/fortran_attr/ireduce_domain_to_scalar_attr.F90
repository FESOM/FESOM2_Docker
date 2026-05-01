! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE ireduce_domain_to_scalar_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE ireduce_domain_to_scalar
  USE reduce_domain_to_scalar_interface_attr

CONTAINS

  SUBROUTINE xios(set_reduce_domain_to_scalar_attr)  &
    ( reduce_domain_to_scalar_id, local, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar))  :: reduce_domain_to_scalar_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reduce_domain_to_scalar_id
      LOGICAL  , OPTIONAL, INTENT(IN) :: local
      LOGICAL (KIND=C_BOOL) :: local_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: operation

      CALL xios(get_reduce_domain_to_scalar_handle) &
      (reduce_domain_to_scalar_id,reduce_domain_to_scalar_hdl)
      CALL xios(set_reduce_domain_to_scalar_attr_hdl_)   &
      ( reduce_domain_to_scalar_hdl, local, operation )

  END SUBROUTINE xios(set_reduce_domain_to_scalar_attr)

  SUBROUTINE xios(set_reduce_domain_to_scalar_attr_hdl)  &
    ( reduce_domain_to_scalar_hdl, local, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar)) , INTENT(IN) :: reduce_domain_to_scalar_hdl
      LOGICAL  , OPTIONAL, INTENT(IN) :: local
      LOGICAL (KIND=C_BOOL) :: local_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: operation

      CALL xios(set_reduce_domain_to_scalar_attr_hdl_)  &
      ( reduce_domain_to_scalar_hdl, local, operation )

  END SUBROUTINE xios(set_reduce_domain_to_scalar_attr_hdl)

  SUBROUTINE xios(set_reduce_domain_to_scalar_attr_hdl_)   &
    ( reduce_domain_to_scalar_hdl, local_, operation_ )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar)) , INTENT(IN) :: reduce_domain_to_scalar_hdl
      LOGICAL  , OPTIONAL, INTENT(IN) :: local_
      LOGICAL (KIND=C_BOOL) :: local__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: operation_

      IF (PRESENT(local_)) THEN
        local__tmp = local_
        CALL cxios_set_reduce_domain_to_scalar_local &
      (reduce_domain_to_scalar_hdl%daddr, local__tmp)
      ENDIF

      IF (PRESENT(operation_)) THEN
        CALL cxios_set_reduce_domain_to_scalar_operation &
      (reduce_domain_to_scalar_hdl%daddr, operation_, len(operation_))
      ENDIF

  END SUBROUTINE xios(set_reduce_domain_to_scalar_attr_hdl_)

  SUBROUTINE xios(get_reduce_domain_to_scalar_attr)  &
    ( reduce_domain_to_scalar_id, local, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar))  :: reduce_domain_to_scalar_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reduce_domain_to_scalar_id
      LOGICAL  , OPTIONAL, INTENT(OUT) :: local
      LOGICAL (KIND=C_BOOL) :: local_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: operation

      CALL xios(get_reduce_domain_to_scalar_handle) &
      (reduce_domain_to_scalar_id,reduce_domain_to_scalar_hdl)
      CALL xios(get_reduce_domain_to_scalar_attr_hdl_)   &
      ( reduce_domain_to_scalar_hdl, local, operation )

  END SUBROUTINE xios(get_reduce_domain_to_scalar_attr)

  SUBROUTINE xios(get_reduce_domain_to_scalar_attr_hdl)  &
    ( reduce_domain_to_scalar_hdl, local, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar)) , INTENT(IN) :: reduce_domain_to_scalar_hdl
      LOGICAL  , OPTIONAL, INTENT(OUT) :: local
      LOGICAL (KIND=C_BOOL) :: local_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: operation

      CALL xios(get_reduce_domain_to_scalar_attr_hdl_)  &
      ( reduce_domain_to_scalar_hdl, local, operation )

  END SUBROUTINE xios(get_reduce_domain_to_scalar_attr_hdl)

  SUBROUTINE xios(get_reduce_domain_to_scalar_attr_hdl_)   &
    ( reduce_domain_to_scalar_hdl, local_, operation_ )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar)) , INTENT(IN) :: reduce_domain_to_scalar_hdl
      LOGICAL  , OPTIONAL, INTENT(OUT) :: local_
      LOGICAL (KIND=C_BOOL) :: local__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: operation_

      IF (PRESENT(local_)) THEN
        CALL cxios_get_reduce_domain_to_scalar_local &
      (reduce_domain_to_scalar_hdl%daddr, local__tmp)
        local_ = local__tmp
      ENDIF

      IF (PRESENT(operation_)) THEN
        CALL cxios_get_reduce_domain_to_scalar_operation &
      (reduce_domain_to_scalar_hdl%daddr, operation_, len(operation_))
      ENDIF

  END SUBROUTINE xios(get_reduce_domain_to_scalar_attr_hdl_)

  SUBROUTINE xios(is_defined_reduce_domain_to_scalar_attr)  &
    ( reduce_domain_to_scalar_id, local, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar))  :: reduce_domain_to_scalar_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reduce_domain_to_scalar_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: local
      LOGICAL(KIND=C_BOOL) :: local_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: operation
      LOGICAL(KIND=C_BOOL) :: operation_tmp

      CALL xios(get_reduce_domain_to_scalar_handle) &
      (reduce_domain_to_scalar_id,reduce_domain_to_scalar_hdl)
      CALL xios(is_defined_reduce_domain_to_scalar_attr_hdl_)   &
      ( reduce_domain_to_scalar_hdl, local, operation )

  END SUBROUTINE xios(is_defined_reduce_domain_to_scalar_attr)

  SUBROUTINE xios(is_defined_reduce_domain_to_scalar_attr_hdl)  &
    ( reduce_domain_to_scalar_hdl, local, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar)) , INTENT(IN) :: reduce_domain_to_scalar_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: local
      LOGICAL(KIND=C_BOOL) :: local_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: operation
      LOGICAL(KIND=C_BOOL) :: operation_tmp

      CALL xios(is_defined_reduce_domain_to_scalar_attr_hdl_)  &
      ( reduce_domain_to_scalar_hdl, local, operation )

  END SUBROUTINE xios(is_defined_reduce_domain_to_scalar_attr_hdl)

  SUBROUTINE xios(is_defined_reduce_domain_to_scalar_attr_hdl_)   &
    ( reduce_domain_to_scalar_hdl, local_, operation_ )

    IMPLICIT NONE
      TYPE(txios(reduce_domain_to_scalar)) , INTENT(IN) :: reduce_domain_to_scalar_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: local_
      LOGICAL(KIND=C_BOOL) :: local__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: operation_
      LOGICAL(KIND=C_BOOL) :: operation__tmp

      IF (PRESENT(local_)) THEN
        local__tmp = cxios_is_defined_reduce_domain_to_scalar_local &
      (reduce_domain_to_scalar_hdl%daddr)
        local_ = local__tmp
      ENDIF

      IF (PRESENT(operation_)) THEN
        operation__tmp = cxios_is_defined_reduce_domain_to_scalar_operation &
      (reduce_domain_to_scalar_hdl%daddr)
        operation_ = operation__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_reduce_domain_to_scalar_attr_hdl_)

END MODULE ireduce_domain_to_scalar_attr
