! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE interpolate_domain_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_interpolate_domain_detect_missing_value(interpolate_domain_hdl, detect_missing_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: detect_missing_value
    END SUBROUTINE cxios_set_interpolate_domain_detect_missing_value

    SUBROUTINE cxios_get_interpolate_domain_detect_missing_value(interpolate_domain_hdl, detect_missing_value) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)             :: detect_missing_value
    END SUBROUTINE cxios_get_interpolate_domain_detect_missing_value

    FUNCTION cxios_is_defined_interpolate_domain_detect_missing_value(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_detect_missing_value
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_detect_missing_value


    SUBROUTINE cxios_set_interpolate_domain_mode(interpolate_domain_hdl, mode, mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: mode
      INTEGER  (kind = C_INT)     , VALUE        :: mode_size
    END SUBROUTINE cxios_set_interpolate_domain_mode

    SUBROUTINE cxios_get_interpolate_domain_mode(interpolate_domain_hdl, mode, mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: mode
      INTEGER  (kind = C_INT)     , VALUE        :: mode_size
    END SUBROUTINE cxios_get_interpolate_domain_mode

    FUNCTION cxios_is_defined_interpolate_domain_mode(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_mode
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_mode


    SUBROUTINE cxios_set_interpolate_domain_order(interpolate_domain_hdl, order) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      INTEGER (KIND=C_INT)      , VALUE :: order
    END SUBROUTINE cxios_set_interpolate_domain_order

    SUBROUTINE cxios_get_interpolate_domain_order(interpolate_domain_hdl, order) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      INTEGER (KIND=C_INT)             :: order
    END SUBROUTINE cxios_get_interpolate_domain_order

    FUNCTION cxios_is_defined_interpolate_domain_order(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_order
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_order


    SUBROUTINE cxios_set_interpolate_domain_quantity(interpolate_domain_hdl, quantity) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: quantity
    END SUBROUTINE cxios_set_interpolate_domain_quantity

    SUBROUTINE cxios_get_interpolate_domain_quantity(interpolate_domain_hdl, quantity) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)             :: quantity
    END SUBROUTINE cxios_get_interpolate_domain_quantity

    FUNCTION cxios_is_defined_interpolate_domain_quantity(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_quantity
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_quantity


    SUBROUTINE cxios_set_interpolate_domain_read_write_convention(interpolate_domain_hdl, read_write_convention, read_write_conven&
&tion_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: read_write_convention
      INTEGER  (kind = C_INT)     , VALUE        :: read_write_convention_size
    END SUBROUTINE cxios_set_interpolate_domain_read_write_convention

    SUBROUTINE cxios_get_interpolate_domain_read_write_convention(interpolate_domain_hdl, read_write_convention, read_write_conven&
&tion_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: read_write_convention
      INTEGER  (kind = C_INT)     , VALUE        :: read_write_convention_size
    END SUBROUTINE cxios_get_interpolate_domain_read_write_convention

    FUNCTION cxios_is_defined_interpolate_domain_read_write_convention(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_read_write_convention
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_read_write_convention


    SUBROUTINE cxios_set_interpolate_domain_renormalize(interpolate_domain_hdl, renormalize) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: renormalize
    END SUBROUTINE cxios_set_interpolate_domain_renormalize

    SUBROUTINE cxios_get_interpolate_domain_renormalize(interpolate_domain_hdl, renormalize) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)             :: renormalize
    END SUBROUTINE cxios_get_interpolate_domain_renormalize

    FUNCTION cxios_is_defined_interpolate_domain_renormalize(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_renormalize
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_renormalize


    SUBROUTINE cxios_set_interpolate_domain_use_area(interpolate_domain_hdl, use_area) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: use_area
    END SUBROUTINE cxios_set_interpolate_domain_use_area

    SUBROUTINE cxios_get_interpolate_domain_use_area(interpolate_domain_hdl, use_area) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)             :: use_area
    END SUBROUTINE cxios_get_interpolate_domain_use_area

    FUNCTION cxios_is_defined_interpolate_domain_use_area(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_use_area
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_use_area


    SUBROUTINE cxios_set_interpolate_domain_weight_filename(interpolate_domain_hdl, weight_filename, weight_filename_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: weight_filename
      INTEGER  (kind = C_INT)     , VALUE        :: weight_filename_size
    END SUBROUTINE cxios_set_interpolate_domain_weight_filename

    SUBROUTINE cxios_get_interpolate_domain_weight_filename(interpolate_domain_hdl, weight_filename, weight_filename_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: weight_filename
      INTEGER  (kind = C_INT)     , VALUE        :: weight_filename_size
    END SUBROUTINE cxios_get_interpolate_domain_weight_filename

    FUNCTION cxios_is_defined_interpolate_domain_weight_filename(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_weight_filename
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_weight_filename


    SUBROUTINE cxios_set_interpolate_domain_write_weight(interpolate_domain_hdl, write_weight) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: write_weight
    END SUBROUTINE cxios_set_interpolate_domain_write_weight

    SUBROUTINE cxios_get_interpolate_domain_write_weight(interpolate_domain_hdl, write_weight) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
      LOGICAL (KIND=C_BOOL)             :: write_weight
    END SUBROUTINE cxios_get_interpolate_domain_write_weight

    FUNCTION cxios_is_defined_interpolate_domain_write_weight(interpolate_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_interpolate_domain_write_weight
      INTEGER (kind = C_INTPTR_T), VALUE :: interpolate_domain_hdl
    END FUNCTION cxios_is_defined_interpolate_domain_write_weight

  END INTERFACE

END MODULE interpolate_domain_interface_attr
