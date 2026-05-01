! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE ireduce_scalar_to_scalar_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE ireduce_scalar_to_scalar
  USE reduce_scalar_to_scalar_interface_attr

CONTAINS

  SUBROUTINE xios(set_reduce_scalar_to_scalar_attr)  &
    ( reduce_scalar_to_scalar_id, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar))  :: reduce_scalar_to_scalar_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reduce_scalar_to_scalar_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: operation

      CALL xios(get_reduce_scalar_to_scalar_handle) &
      (reduce_scalar_to_scalar_id,reduce_scalar_to_scalar_hdl)
      CALL xios(set_reduce_scalar_to_scalar_attr_hdl_)   &
      ( reduce_scalar_to_scalar_hdl, operation )

  END SUBROUTINE xios(set_reduce_scalar_to_scalar_attr)

  SUBROUTINE xios(set_reduce_scalar_to_scalar_attr_hdl)  &
    ( reduce_scalar_to_scalar_hdl, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar)) , INTENT(IN) :: reduce_scalar_to_scalar_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: operation

      CALL xios(set_reduce_scalar_to_scalar_attr_hdl_)  &
      ( reduce_scalar_to_scalar_hdl, operation )

  END SUBROUTINE xios(set_reduce_scalar_to_scalar_attr_hdl)

  SUBROUTINE xios(set_reduce_scalar_to_scalar_attr_hdl_)   &
    ( reduce_scalar_to_scalar_hdl, operation_ )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar)) , INTENT(IN) :: reduce_scalar_to_scalar_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: operation_

      IF (PRESENT(operation_)) THEN
        CALL cxios_set_reduce_scalar_to_scalar_operation &
      (reduce_scalar_to_scalar_hdl%daddr, operation_, len(operation_))
      ENDIF

  END SUBROUTINE xios(set_reduce_scalar_to_scalar_attr_hdl_)

  SUBROUTINE xios(get_reduce_scalar_to_scalar_attr)  &
    ( reduce_scalar_to_scalar_id, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar))  :: reduce_scalar_to_scalar_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reduce_scalar_to_scalar_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: operation

      CALL xios(get_reduce_scalar_to_scalar_handle) &
      (reduce_scalar_to_scalar_id,reduce_scalar_to_scalar_hdl)
      CALL xios(get_reduce_scalar_to_scalar_attr_hdl_)   &
      ( reduce_scalar_to_scalar_hdl, operation )

  END SUBROUTINE xios(get_reduce_scalar_to_scalar_attr)

  SUBROUTINE xios(get_reduce_scalar_to_scalar_attr_hdl)  &
    ( reduce_scalar_to_scalar_hdl, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar)) , INTENT(IN) :: reduce_scalar_to_scalar_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: operation

      CALL xios(get_reduce_scalar_to_scalar_attr_hdl_)  &
      ( reduce_scalar_to_scalar_hdl, operation )

  END SUBROUTINE xios(get_reduce_scalar_to_scalar_attr_hdl)

  SUBROUTINE xios(get_reduce_scalar_to_scalar_attr_hdl_)   &
    ( reduce_scalar_to_scalar_hdl, operation_ )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar)) , INTENT(IN) :: reduce_scalar_to_scalar_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: operation_

      IF (PRESENT(operation_)) THEN
        CALL cxios_get_reduce_scalar_to_scalar_operation &
      (reduce_scalar_to_scalar_hdl%daddr, operation_, len(operation_))
      ENDIF

  END SUBROUTINE xios(get_reduce_scalar_to_scalar_attr_hdl_)

  SUBROUTINE xios(is_defined_reduce_scalar_to_scalar_attr)  &
    ( reduce_scalar_to_scalar_id, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar))  :: reduce_scalar_to_scalar_hdl
      CHARACTER(LEN=*), INTENT(IN) ::reduce_scalar_to_scalar_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: operation
      LOGICAL(KIND=C_BOOL) :: operation_tmp

      CALL xios(get_reduce_scalar_to_scalar_handle) &
      (reduce_scalar_to_scalar_id,reduce_scalar_to_scalar_hdl)
      CALL xios(is_defined_reduce_scalar_to_scalar_attr_hdl_)   &
      ( reduce_scalar_to_scalar_hdl, operation )

  END SUBROUTINE xios(is_defined_reduce_scalar_to_scalar_attr)

  SUBROUTINE xios(is_defined_reduce_scalar_to_scalar_attr_hdl)  &
    ( reduce_scalar_to_scalar_hdl, operation )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar)) , INTENT(IN) :: reduce_scalar_to_scalar_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: operation
      LOGICAL(KIND=C_BOOL) :: operation_tmp

      CALL xios(is_defined_reduce_scalar_to_scalar_attr_hdl_)  &
      ( reduce_scalar_to_scalar_hdl, operation )

  END SUBROUTINE xios(is_defined_reduce_scalar_to_scalar_attr_hdl)

  SUBROUTINE xios(is_defined_reduce_scalar_to_scalar_attr_hdl_)   &
    ( reduce_scalar_to_scalar_hdl, operation_ )

    IMPLICIT NONE
      TYPE(txios(reduce_scalar_to_scalar)) , INTENT(IN) :: reduce_scalar_to_scalar_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: operation_
      LOGICAL(KIND=C_BOOL) :: operation__tmp

      IF (PRESENT(operation_)) THEN
        operation__tmp = cxios_is_defined_reduce_scalar_to_scalar_operation &
      (reduce_scalar_to_scalar_hdl%daddr)
        operation_ = operation__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_reduce_scalar_to_scalar_attr_hdl_)

END MODULE ireduce_scalar_to_scalar_attr
