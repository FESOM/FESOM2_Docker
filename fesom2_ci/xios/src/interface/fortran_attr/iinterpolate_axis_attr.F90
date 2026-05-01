! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE iinterpolate_axis_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE iinterpolate_axis
  USE interpolate_axis_interface_attr

CONTAINS

  SUBROUTINE xios(set_interpolate_axis_attr)  &
    ( interpolate_axis_id, coordinate, order, type )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis))  :: interpolate_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::interpolate_axis_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: coordinate
      INTEGER  , OPTIONAL, INTENT(IN) :: order
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type

      CALL xios(get_interpolate_axis_handle) &
      (interpolate_axis_id,interpolate_axis_hdl)
      CALL xios(set_interpolate_axis_attr_hdl_)   &
      ( interpolate_axis_hdl, coordinate, order, type )

  END SUBROUTINE xios(set_interpolate_axis_attr)

  SUBROUTINE xios(set_interpolate_axis_attr_hdl)  &
    ( interpolate_axis_hdl, coordinate, order, type )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis)) , INTENT(IN) :: interpolate_axis_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: coordinate
      INTEGER  , OPTIONAL, INTENT(IN) :: order
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type

      CALL xios(set_interpolate_axis_attr_hdl_)  &
      ( interpolate_axis_hdl, coordinate, order, type )

  END SUBROUTINE xios(set_interpolate_axis_attr_hdl)

  SUBROUTINE xios(set_interpolate_axis_attr_hdl_)   &
    ( interpolate_axis_hdl, coordinate_, order_, type_ )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis)) , INTENT(IN) :: interpolate_axis_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: coordinate_
      INTEGER  , OPTIONAL, INTENT(IN) :: order_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type_

      IF (PRESENT(coordinate_)) THEN
        CALL cxios_set_interpolate_axis_coordinate &
      (interpolate_axis_hdl%daddr, coordinate_, len(coordinate_))
      ENDIF

      IF (PRESENT(order_)) THEN
        CALL cxios_set_interpolate_axis_order &
      (interpolate_axis_hdl%daddr, order_)
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_set_interpolate_axis_type &
      (interpolate_axis_hdl%daddr, type_, len(type_))
      ENDIF

  END SUBROUTINE xios(set_interpolate_axis_attr_hdl_)

  SUBROUTINE xios(get_interpolate_axis_attr)  &
    ( interpolate_axis_id, coordinate, order, type )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis))  :: interpolate_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::interpolate_axis_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: coordinate
      INTEGER  , OPTIONAL, INTENT(OUT) :: order
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type

      CALL xios(get_interpolate_axis_handle) &
      (interpolate_axis_id,interpolate_axis_hdl)
      CALL xios(get_interpolate_axis_attr_hdl_)   &
      ( interpolate_axis_hdl, coordinate, order, type )

  END SUBROUTINE xios(get_interpolate_axis_attr)

  SUBROUTINE xios(get_interpolate_axis_attr_hdl)  &
    ( interpolate_axis_hdl, coordinate, order, type )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis)) , INTENT(IN) :: interpolate_axis_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: coordinate
      INTEGER  , OPTIONAL, INTENT(OUT) :: order
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type

      CALL xios(get_interpolate_axis_attr_hdl_)  &
      ( interpolate_axis_hdl, coordinate, order, type )

  END SUBROUTINE xios(get_interpolate_axis_attr_hdl)

  SUBROUTINE xios(get_interpolate_axis_attr_hdl_)   &
    ( interpolate_axis_hdl, coordinate_, order_, type_ )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis)) , INTENT(IN) :: interpolate_axis_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: coordinate_
      INTEGER  , OPTIONAL, INTENT(OUT) :: order_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type_

      IF (PRESENT(coordinate_)) THEN
        CALL cxios_get_interpolate_axis_coordinate &
      (interpolate_axis_hdl%daddr, coordinate_, len(coordinate_))
      ENDIF

      IF (PRESENT(order_)) THEN
        CALL cxios_get_interpolate_axis_order &
      (interpolate_axis_hdl%daddr, order_)
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_get_interpolate_axis_type &
      (interpolate_axis_hdl%daddr, type_, len(type_))
      ENDIF

  END SUBROUTINE xios(get_interpolate_axis_attr_hdl_)

  SUBROUTINE xios(is_defined_interpolate_axis_attr)  &
    ( interpolate_axis_id, coordinate, order, type )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis))  :: interpolate_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::interpolate_axis_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: coordinate
      LOGICAL(KIND=C_BOOL) :: coordinate_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: order
      LOGICAL(KIND=C_BOOL) :: order_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp

      CALL xios(get_interpolate_axis_handle) &
      (interpolate_axis_id,interpolate_axis_hdl)
      CALL xios(is_defined_interpolate_axis_attr_hdl_)   &
      ( interpolate_axis_hdl, coordinate, order, type )

  END SUBROUTINE xios(is_defined_interpolate_axis_attr)

  SUBROUTINE xios(is_defined_interpolate_axis_attr_hdl)  &
    ( interpolate_axis_hdl, coordinate, order, type )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis)) , INTENT(IN) :: interpolate_axis_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: coordinate
      LOGICAL(KIND=C_BOOL) :: coordinate_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: order
      LOGICAL(KIND=C_BOOL) :: order_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp

      CALL xios(is_defined_interpolate_axis_attr_hdl_)  &
      ( interpolate_axis_hdl, coordinate, order, type )

  END SUBROUTINE xios(is_defined_interpolate_axis_attr_hdl)

  SUBROUTINE xios(is_defined_interpolate_axis_attr_hdl_)   &
    ( interpolate_axis_hdl, coordinate_, order_, type_ )

    IMPLICIT NONE
      TYPE(txios(interpolate_axis)) , INTENT(IN) :: interpolate_axis_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: coordinate_
      LOGICAL(KIND=C_BOOL) :: coordinate__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: order_
      LOGICAL(KIND=C_BOOL) :: order__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type_
      LOGICAL(KIND=C_BOOL) :: type__tmp

      IF (PRESENT(coordinate_)) THEN
        coordinate__tmp = cxios_is_defined_interpolate_axis_coordinate &
      (interpolate_axis_hdl%daddr)
        coordinate_ = coordinate__tmp
      ENDIF

      IF (PRESENT(order_)) THEN
        order__tmp = cxios_is_defined_interpolate_axis_order &
      (interpolate_axis_hdl%daddr)
        order_ = order__tmp
      ENDIF

      IF (PRESENT(type_)) THEN
        type__tmp = cxios_is_defined_interpolate_axis_type &
      (interpolate_axis_hdl%daddr)
        type_ = type__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_interpolate_axis_attr_hdl_)

END MODULE iinterpolate_axis_attr
