! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE interpolate_axis_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_interpolate_axis_coordinate(interpolate_axis_hdl, coordinate, coordinate_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: coordinate
      INTEGER  (kind = C_INT)     , VALUE        :: coordinate_size
    END SUBROUTINE cxios_set_interpolate_axis_coordinate

    SUBROUTINE cxios_get_interpolate_axis_coordinate(interpolate_axis_hdl, coordinate, coordinate_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: coordinate
      INTEGER  (kind = C_INT)     , VALUE        :: coordinate_size
    END SUBROUTINE cxios_get_interpolate_axis_coordinate

    FUNCTION cxios_is_defined_interpolate_axis_coordinate(interpolate_axis_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_axis_coordinate
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
    END FUNCTION cxios_is_defined_interpolate_axis_coordinate


    SUBROUTINE cxios_set_interpolate_axis_order(interpolate_axis_hdl, order) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
      INTEGER (KIND=C_INT)      , VALUE :: order
    END SUBROUTINE cxios_set_interpolate_axis_order

    SUBROUTINE cxios_get_interpolate_axis_order(interpolate_axis_hdl, order) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
      INTEGER (KIND=C_INT)             :: order
    END SUBROUTINE cxios_get_interpolate_axis_order

    FUNCTION cxios_is_defined_interpolate_axis_order(interpolate_axis_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_axis_order
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
    END FUNCTION cxios_is_defined_interpolate_axis_order


    SUBROUTINE cxios_set_interpolate_axis_type(interpolate_axis_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_interpolate_axis_type

    SUBROUTINE cxios_get_interpolate_axis_type(interpolate_axis_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_interpolate_axis_type

    FUNCTION cxios_is_defined_interpolate_axis_type(interpolate_axis_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_axis_type
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_axis_hdl
    END FUNCTION cxios_is_defined_interpolate_axis_type

  END INTERFACE

END MODULE interpolate_axis_interface_attr
