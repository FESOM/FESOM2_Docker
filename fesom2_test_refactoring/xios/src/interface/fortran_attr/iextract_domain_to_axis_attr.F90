! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE iextract_domain_to_axis_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE iextract_domain_to_axis
  USE extract_domain_to_axis_interface_attr

CONTAINS

  SUBROUTINE xios(set_extract_domain_to_axis_attr)  &
    ( extract_domain_to_axis_id, direction, position )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis))  :: extract_domain_to_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::extract_domain_to_axis_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: direction
      INTEGER  , OPTIONAL, INTENT(IN) :: position

      CALL xios(get_extract_domain_to_axis_handle) &
      (extract_domain_to_axis_id,extract_domain_to_axis_hdl)
      CALL xios(set_extract_domain_to_axis_attr_hdl_)   &
      ( extract_domain_to_axis_hdl, direction, position )

  END SUBROUTINE xios(set_extract_domain_to_axis_attr)

  SUBROUTINE xios(set_extract_domain_to_axis_attr_hdl)  &
    ( extract_domain_to_axis_hdl, direction, position )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis)) , INTENT(IN) :: extract_domain_to_axis_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: direction
      INTEGER  , OPTIONAL, INTENT(IN) :: position

      CALL xios(set_extract_domain_to_axis_attr_hdl_)  &
      ( extract_domain_to_axis_hdl, direction, position )

  END SUBROUTINE xios(set_extract_domain_to_axis_attr_hdl)

  SUBROUTINE xios(set_extract_domain_to_axis_attr_hdl_)   &
    ( extract_domain_to_axis_hdl, direction_, position_ )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis)) , INTENT(IN) :: extract_domain_to_axis_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: direction_
      INTEGER  , OPTIONAL, INTENT(IN) :: position_

      IF (PRESENT(direction_)) THEN
        CALL cxios_set_extract_domain_to_axis_direction &
      (extract_domain_to_axis_hdl%daddr, direction_, len(direction_))
      ENDIF

      IF (PRESENT(position_)) THEN
        CALL cxios_set_extract_domain_to_axis_position &
      (extract_domain_to_axis_hdl%daddr, position_)
      ENDIF

  END SUBROUTINE xios(set_extract_domain_to_axis_attr_hdl_)

  SUBROUTINE xios(get_extract_domain_to_axis_attr)  &
    ( extract_domain_to_axis_id, direction, position )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis))  :: extract_domain_to_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::extract_domain_to_axis_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: direction
      INTEGER  , OPTIONAL, INTENT(OUT) :: position

      CALL xios(get_extract_domain_to_axis_handle) &
      (extract_domain_to_axis_id,extract_domain_to_axis_hdl)
      CALL xios(get_extract_domain_to_axis_attr_hdl_)   &
      ( extract_domain_to_axis_hdl, direction, position )

  END SUBROUTINE xios(get_extract_domain_to_axis_attr)

  SUBROUTINE xios(get_extract_domain_to_axis_attr_hdl)  &
    ( extract_domain_to_axis_hdl, direction, position )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis)) , INTENT(IN) :: extract_domain_to_axis_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: direction
      INTEGER  , OPTIONAL, INTENT(OUT) :: position

      CALL xios(get_extract_domain_to_axis_attr_hdl_)  &
      ( extract_domain_to_axis_hdl, direction, position )

  END SUBROUTINE xios(get_extract_domain_to_axis_attr_hdl)

  SUBROUTINE xios(get_extract_domain_to_axis_attr_hdl_)   &
    ( extract_domain_to_axis_hdl, direction_, position_ )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis)) , INTENT(IN) :: extract_domain_to_axis_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: direction_
      INTEGER  , OPTIONAL, INTENT(OUT) :: position_

      IF (PRESENT(direction_)) THEN
        CALL cxios_get_extract_domain_to_axis_direction &
      (extract_domain_to_axis_hdl%daddr, direction_, len(direction_))
      ENDIF

      IF (PRESENT(position_)) THEN
        CALL cxios_get_extract_domain_to_axis_position &
      (extract_domain_to_axis_hdl%daddr, position_)
      ENDIF

  END SUBROUTINE xios(get_extract_domain_to_axis_attr_hdl_)

  SUBROUTINE xios(is_defined_extract_domain_to_axis_attr)  &
    ( extract_domain_to_axis_id, direction, position )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis))  :: extract_domain_to_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::extract_domain_to_axis_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: direction
      LOGICAL(KIND=C_BOOL) :: direction_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: position
      LOGICAL(KIND=C_BOOL) :: position_tmp

      CALL xios(get_extract_domain_to_axis_handle) &
      (extract_domain_to_axis_id,extract_domain_to_axis_hdl)
      CALL xios(is_defined_extract_domain_to_axis_attr_hdl_)   &
      ( extract_domain_to_axis_hdl, direction, position )

  END SUBROUTINE xios(is_defined_extract_domain_to_axis_attr)

  SUBROUTINE xios(is_defined_extract_domain_to_axis_attr_hdl)  &
    ( extract_domain_to_axis_hdl, direction, position )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis)) , INTENT(IN) :: extract_domain_to_axis_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: direction
      LOGICAL(KIND=C_BOOL) :: direction_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: position
      LOGICAL(KIND=C_BOOL) :: position_tmp

      CALL xios(is_defined_extract_domain_to_axis_attr_hdl_)  &
      ( extract_domain_to_axis_hdl, direction, position )

  END SUBROUTINE xios(is_defined_extract_domain_to_axis_attr_hdl)

  SUBROUTINE xios(is_defined_extract_domain_to_axis_attr_hdl_)   &
    ( extract_domain_to_axis_hdl, direction_, position_ )

    IMPLICIT NONE
      TYPE(txios(extract_domain_to_axis)) , INTENT(IN) :: extract_domain_to_axis_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: direction_
      LOGICAL(KIND=C_BOOL) :: direction__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: position_
      LOGICAL(KIND=C_BOOL) :: position__tmp

      IF (PRESENT(direction_)) THEN
        direction__tmp = cxios_is_defined_extract_domain_to_axis_direction &
      (extract_domain_to_axis_hdl%daddr)
        direction_ = direction__tmp
      ENDIF

      IF (PRESENT(position_)) THEN
        position__tmp = cxios_is_defined_extract_domain_to_axis_position &
      (extract_domain_to_axis_hdl%daddr)
        position_ = position__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_extract_domain_to_axis_attr_hdl_)

END MODULE iextract_domain_to_axis_attr
