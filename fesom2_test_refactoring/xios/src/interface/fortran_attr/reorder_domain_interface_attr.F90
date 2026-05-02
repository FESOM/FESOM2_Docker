! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE reorder_domain_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_reorder_domain_invert_lat(reorder_domain_hdl, invert_lat) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: invert_lat
    END SUBROUTINE cxios_set_reorder_domain_invert_lat

    SUBROUTINE cxios_get_reorder_domain_invert_lat(reorder_domain_hdl, invert_lat) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
      LOGICAL (KIND=C_BOOL)             :: invert_lat
    END SUBROUTINE cxios_get_reorder_domain_invert_lat

    FUNCTION cxios_is_defined_reorder_domain_invert_lat(reorder_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_reorder_domain_invert_lat
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
    END FUNCTION cxios_is_defined_reorder_domain_invert_lat


    SUBROUTINE cxios_set_reorder_domain_max_lon(reorder_domain_hdl, max_lon) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: max_lon
    END SUBROUTINE cxios_set_reorder_domain_max_lon

    SUBROUTINE cxios_get_reorder_domain_max_lon(reorder_domain_hdl, max_lon) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
      REAL (KIND=C_DOUBLE)             :: max_lon
    END SUBROUTINE cxios_get_reorder_domain_max_lon

    FUNCTION cxios_is_defined_reorder_domain_max_lon(reorder_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_reorder_domain_max_lon
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
    END FUNCTION cxios_is_defined_reorder_domain_max_lon


    SUBROUTINE cxios_set_reorder_domain_min_lon(reorder_domain_hdl, min_lon) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: min_lon
    END SUBROUTINE cxios_set_reorder_domain_min_lon

    SUBROUTINE cxios_get_reorder_domain_min_lon(reorder_domain_hdl, min_lon) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
      REAL (KIND=C_DOUBLE)             :: min_lon
    END SUBROUTINE cxios_get_reorder_domain_min_lon

    FUNCTION cxios_is_defined_reorder_domain_min_lon(reorder_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_reorder_domain_min_lon
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
    END FUNCTION cxios_is_defined_reorder_domain_min_lon


    SUBROUTINE cxios_set_reorder_domain_shift_lon_fraction(reorder_domain_hdl, shift_lon_fraction) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: shift_lon_fraction
    END SUBROUTINE cxios_set_reorder_domain_shift_lon_fraction

    SUBROUTINE cxios_get_reorder_domain_shift_lon_fraction(reorder_domain_hdl, shift_lon_fraction) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
      REAL (KIND=C_DOUBLE)             :: shift_lon_fraction
    END SUBROUTINE cxios_get_reorder_domain_shift_lon_fraction

    FUNCTION cxios_is_defined_reorder_domain_shift_lon_fraction(reorder_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_reorder_domain_shift_lon_fraction
      INTEGER (kind = C_INTPTR_T), VALUE :: reorder_domain_hdl
    END FUNCTION cxios_is_defined_reorder_domain_shift_lon_fraction

  END INTERFACE

END MODULE reorder_domain_interface_attr
