! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE ivariable_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE ivariable
  USE variable_interface_attr

CONTAINS

  SUBROUTINE xios(set_variable_attr)  &
    ( variable_id, name, ts_target, type )

    IMPLICIT NONE
      TYPE(txios(variable))  :: variable_hdl
      CHARACTER(LEN=*), INTENT(IN) ::variable_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: ts_target
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type

      CALL xios(get_variable_handle) &
      (variable_id,variable_hdl)
      CALL xios(set_variable_attr_hdl_)   &
      ( variable_hdl, name, ts_target, type )

  END SUBROUTINE xios(set_variable_attr)

  SUBROUTINE xios(set_variable_attr_hdl)  &
    ( variable_hdl, name, ts_target, type )

    IMPLICIT NONE
      TYPE(txios(variable)) , INTENT(IN) :: variable_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: ts_target
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type

      CALL xios(set_variable_attr_hdl_)  &
      ( variable_hdl, name, ts_target, type )

  END SUBROUTINE xios(set_variable_attr_hdl)

  SUBROUTINE xios(set_variable_attr_hdl_)   &
    ( variable_hdl, name_, ts_target_, type_ )

    IMPLICIT NONE
      TYPE(txios(variable)) , INTENT(IN) :: variable_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: ts_target_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type_

      IF (PRESENT(name_)) THEN
        CALL cxios_set_variable_name &
      (variable_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(ts_target_)) THEN
        CALL cxios_set_variable_ts_target &
      (variable_hdl%daddr, ts_target_, len(ts_target_))
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_set_variable_type &
      (variable_hdl%daddr, type_, len(type_))
      ENDIF

  END SUBROUTINE xios(set_variable_attr_hdl_)

  SUBROUTINE xios(get_variable_attr)  &
    ( variable_id, name, ts_target, type )

    IMPLICIT NONE
      TYPE(txios(variable))  :: variable_hdl
      CHARACTER(LEN=*), INTENT(IN) ::variable_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: ts_target
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type

      CALL xios(get_variable_handle) &
      (variable_id,variable_hdl)
      CALL xios(get_variable_attr_hdl_)   &
      ( variable_hdl, name, ts_target, type )

  END SUBROUTINE xios(get_variable_attr)

  SUBROUTINE xios(get_variable_attr_hdl)  &
    ( variable_hdl, name, ts_target, type )

    IMPLICIT NONE
      TYPE(txios(variable)) , INTENT(IN) :: variable_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: ts_target
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type

      CALL xios(get_variable_attr_hdl_)  &
      ( variable_hdl, name, ts_target, type )

  END SUBROUTINE xios(get_variable_attr_hdl)

  SUBROUTINE xios(get_variable_attr_hdl_)   &
    ( variable_hdl, name_, ts_target_, type_ )

    IMPLICIT NONE
      TYPE(txios(variable)) , INTENT(IN) :: variable_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: ts_target_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type_

      IF (PRESENT(name_)) THEN
        CALL cxios_get_variable_name &
      (variable_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(ts_target_)) THEN
        CALL cxios_get_variable_ts_target &
      (variable_hdl%daddr, ts_target_, len(ts_target_))
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_get_variable_type &
      (variable_hdl%daddr, type_, len(type_))
      ENDIF

  END SUBROUTINE xios(get_variable_attr_hdl_)

  SUBROUTINE xios(is_defined_variable_attr)  &
    ( variable_id, name, ts_target, type )

    IMPLICIT NONE
      TYPE(txios(variable))  :: variable_hdl
      CHARACTER(LEN=*), INTENT(IN) ::variable_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ts_target
      LOGICAL(KIND=C_BOOL) :: ts_target_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp

      CALL xios(get_variable_handle) &
      (variable_id,variable_hdl)
      CALL xios(is_defined_variable_attr_hdl_)   &
      ( variable_hdl, name, ts_target, type )

  END SUBROUTINE xios(is_defined_variable_attr)

  SUBROUTINE xios(is_defined_variable_attr_hdl)  &
    ( variable_hdl, name, ts_target, type )

    IMPLICIT NONE
      TYPE(txios(variable)) , INTENT(IN) :: variable_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ts_target
      LOGICAL(KIND=C_BOOL) :: ts_target_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp

      CALL xios(is_defined_variable_attr_hdl_)  &
      ( variable_hdl, name, ts_target, type )

  END SUBROUTINE xios(is_defined_variable_attr_hdl)

  SUBROUTINE xios(is_defined_variable_attr_hdl_)   &
    ( variable_hdl, name_, ts_target_, type_ )

    IMPLICIT NONE
      TYPE(txios(variable)) , INTENT(IN) :: variable_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_
      LOGICAL(KIND=C_BOOL) :: name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ts_target_
      LOGICAL(KIND=C_BOOL) :: ts_target__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type_
      LOGICAL(KIND=C_BOOL) :: type__tmp

      IF (PRESENT(name_)) THEN
        name__tmp = cxios_is_defined_variable_name &
      (variable_hdl%daddr)
        name_ = name__tmp
      ENDIF

      IF (PRESENT(ts_target_)) THEN
        ts_target__tmp = cxios_is_defined_variable_ts_target &
      (variable_hdl%daddr)
        ts_target_ = ts_target__tmp
      ENDIF

      IF (PRESENT(type_)) THEN
        type__tmp = cxios_is_defined_variable_type &
      (variable_hdl%daddr)
        type_ = type__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_variable_attr_hdl_)

END MODULE ivariable_attr
