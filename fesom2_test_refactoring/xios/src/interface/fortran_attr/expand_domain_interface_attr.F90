! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE expand_domain_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_expand_domain_i_periodic(expand_domain_hdl, i_periodic) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: i_periodic
    END SUBROUTINE cxios_set_expand_domain_i_periodic

    SUBROUTINE cxios_get_expand_domain_i_periodic(expand_domain_hdl, i_periodic) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
      LOGICAL (KIND=C_BOOL)             :: i_periodic
    END SUBROUTINE cxios_get_expand_domain_i_periodic

    FUNCTION cxios_is_defined_expand_domain_i_periodic(expand_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_expand_domain_i_periodic
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
    END FUNCTION cxios_is_defined_expand_domain_i_periodic


    SUBROUTINE cxios_set_expand_domain_j_periodic(expand_domain_hdl, j_periodic) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: j_periodic
    END SUBROUTINE cxios_set_expand_domain_j_periodic

    SUBROUTINE cxios_get_expand_domain_j_periodic(expand_domain_hdl, j_periodic) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
      LOGICAL (KIND=C_BOOL)             :: j_periodic
    END SUBROUTINE cxios_get_expand_domain_j_periodic

    FUNCTION cxios_is_defined_expand_domain_j_periodic(expand_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_expand_domain_j_periodic
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
    END FUNCTION cxios_is_defined_expand_domain_j_periodic


    SUBROUTINE cxios_set_expand_domain_order(expand_domain_hdl, order) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
      INTEGER (KIND=C_INT)      , VALUE :: order
    END SUBROUTINE cxios_set_expand_domain_order

    SUBROUTINE cxios_get_expand_domain_order(expand_domain_hdl, order) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
      INTEGER (KIND=C_INT)             :: order
    END SUBROUTINE cxios_get_expand_domain_order

    FUNCTION cxios_is_defined_expand_domain_order(expand_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_expand_domain_order
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
    END FUNCTION cxios_is_defined_expand_domain_order


    SUBROUTINE cxios_set_expand_domain_type(expand_domain_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_expand_domain_type

    SUBROUTINE cxios_get_expand_domain_type(expand_domain_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_expand_domain_type

    FUNCTION cxios_is_defined_expand_domain_type(expand_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_expand_domain_type
      INTEGER (kind = C_INTPTR_T), VALUE :: expand_domain_hdl
    END FUNCTION cxios_is_defined_expand_domain_type

  END INTERFACE

END MODULE expand_domain_interface_attr
