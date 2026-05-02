! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE compute_connectivity_domain_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_compute_connectivity_domain_local_neighbor(compute_connectivity_domain_hdl, local_neighbor, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: compute_connectivity_domain_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: local_neighbor
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_compute_connectivity_domain_local_neighbor

    SUBROUTINE cxios_get_compute_connectivity_domain_local_neighbor(compute_connectivity_domain_hdl, local_neighbor, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: compute_connectivity_domain_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: local_neighbor
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_compute_connectivity_domain_local_neighbor

    FUNCTION cxios_is_defined_compute_connectivity_domain_local_neighbor(compute_connectivity_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_compute_connectivity_domain_local_neighbor
      INTEGER (kind = C_INTPTR_T), VALUE :: compute_connectivity_domain_hdl
    END FUNCTION cxios_is_defined_compute_connectivity_domain_local_neighbor


    SUBROUTINE cxios_set_compute_connectivity_domain_n_neighbor(compute_connectivity_domain_hdl, n_neighbor, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: compute_connectivity_domain_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: n_neighbor
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_compute_connectivity_domain_n_neighbor

    SUBROUTINE cxios_get_compute_connectivity_domain_n_neighbor(compute_connectivity_domain_hdl, n_neighbor, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: compute_connectivity_domain_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: n_neighbor
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_compute_connectivity_domain_n_neighbor

    FUNCTION cxios_is_defined_compute_connectivity_domain_n_neighbor(compute_connectivity_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_compute_connectivity_domain_n_neighbor
      INTEGER (kind = C_INTPTR_T), VALUE :: compute_connectivity_domain_hdl
    END FUNCTION cxios_is_defined_compute_connectivity_domain_n_neighbor


    SUBROUTINE cxios_set_compute_connectivity_domain_n_neighbor_max(compute_connectivity_domain_hdl, n_neighbor_max) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: compute_connectivity_domain_hdl
      INTEGER (KIND=C_INT)      , VALUE :: n_neighbor_max
    END SUBROUTINE cxios_set_compute_connectivity_domain_n_neighbor_max

    SUBROUTINE cxios_get_compute_connectivity_domain_n_neighbor_max(compute_connectivity_domain_hdl, n_neighbor_max) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: compute_connectivity_domain_hdl
      INTEGER (KIND=C_INT)             :: n_neighbor_max
    END SUBROUTINE cxios_get_compute_connectivity_domain_n_neighbor_max

    FUNCTION cxios_is_defined_compute_connectivity_domain_n_neighbor_max(compute_connectivity_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_compute_connectivity_domain_n_neighbor_max
      INTEGER (kind = C_INTPTR_T), VALUE :: compute_connectivity_domain_hdl
    END FUNCTION cxios_is_defined_compute_connectivity_domain_n_neighbor_max


    SUBROUTINE cxios_set_compute_connectivity_domain_type(compute_connectivity_domain_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: compute_connectivity_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_compute_connectivity_domain_type

    SUBROUTINE cxios_get_compute_connectivity_domain_type(compute_connectivity_domain_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: compute_connectivity_domain_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_compute_connectivity_domain_type

    FUNCTION cxios_is_defined_compute_connectivity_domain_type(compute_connectivity_domain_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_compute_connectivity_domain_type
      INTEGER (kind = C_INTPTR_T), VALUE :: compute_connectivity_domain_hdl
    END FUNCTION cxios_is_defined_compute_connectivity_domain_type

  END INTERFACE

END MODULE compute_connectivity_domain_interface_attr
