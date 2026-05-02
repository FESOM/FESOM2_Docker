! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE domaingroup_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_domaingroup_area(domaingroup_hdl, area, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: area
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_area

    SUBROUTINE cxios_get_domaingroup_area(domaingroup_hdl, area, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: area
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_area

    FUNCTION cxios_is_defined_domaingroup_area(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_area
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_area


    SUBROUTINE cxios_set_domaingroup_bounds_lat_1d(domaingroup_hdl, bounds_lat_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds_lat_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_bounds_lat_1d

    SUBROUTINE cxios_get_domaingroup_bounds_lat_1d(domaingroup_hdl, bounds_lat_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds_lat_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_bounds_lat_1d

    FUNCTION cxios_is_defined_domaingroup_bounds_lat_1d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_bounds_lat_1d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_bounds_lat_1d


    SUBROUTINE cxios_set_domaingroup_bounds_lat_2d(domaingroup_hdl, bounds_lat_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds_lat_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_bounds_lat_2d

    SUBROUTINE cxios_get_domaingroup_bounds_lat_2d(domaingroup_hdl, bounds_lat_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds_lat_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_bounds_lat_2d

    FUNCTION cxios_is_defined_domaingroup_bounds_lat_2d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_bounds_lat_2d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_bounds_lat_2d


    SUBROUTINE cxios_set_domaingroup_bounds_lat_name(domaingroup_hdl, bounds_lat_name, bounds_lat_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: bounds_lat_name
      INTEGER  (kind = C_INT)     , VALUE        :: bounds_lat_name_size
    END SUBROUTINE cxios_set_domaingroup_bounds_lat_name

    SUBROUTINE cxios_get_domaingroup_bounds_lat_name(domaingroup_hdl, bounds_lat_name, bounds_lat_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: bounds_lat_name
      INTEGER  (kind = C_INT)     , VALUE        :: bounds_lat_name_size
    END SUBROUTINE cxios_get_domaingroup_bounds_lat_name

    FUNCTION cxios_is_defined_domaingroup_bounds_lat_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_bounds_lat_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_bounds_lat_name


    SUBROUTINE cxios_set_domaingroup_bounds_lon_1d(domaingroup_hdl, bounds_lon_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds_lon_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_bounds_lon_1d

    SUBROUTINE cxios_get_domaingroup_bounds_lon_1d(domaingroup_hdl, bounds_lon_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds_lon_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_bounds_lon_1d

    FUNCTION cxios_is_defined_domaingroup_bounds_lon_1d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_bounds_lon_1d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_bounds_lon_1d


    SUBROUTINE cxios_set_domaingroup_bounds_lon_2d(domaingroup_hdl, bounds_lon_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds_lon_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_bounds_lon_2d

    SUBROUTINE cxios_get_domaingroup_bounds_lon_2d(domaingroup_hdl, bounds_lon_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: bounds_lon_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_bounds_lon_2d

    FUNCTION cxios_is_defined_domaingroup_bounds_lon_2d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_bounds_lon_2d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_bounds_lon_2d


    SUBROUTINE cxios_set_domaingroup_bounds_lon_name(domaingroup_hdl, bounds_lon_name, bounds_lon_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: bounds_lon_name
      INTEGER  (kind = C_INT)     , VALUE        :: bounds_lon_name_size
    END SUBROUTINE cxios_set_domaingroup_bounds_lon_name

    SUBROUTINE cxios_get_domaingroup_bounds_lon_name(domaingroup_hdl, bounds_lon_name, bounds_lon_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: bounds_lon_name
      INTEGER  (kind = C_INT)     , VALUE        :: bounds_lon_name_size
    END SUBROUTINE cxios_get_domaingroup_bounds_lon_name

    FUNCTION cxios_is_defined_domaingroup_bounds_lon_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_bounds_lon_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_bounds_lon_name


    SUBROUTINE cxios_set_domaingroup_comment(domaingroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_domaingroup_comment

    SUBROUTINE cxios_get_domaingroup_comment(domaingroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_domaingroup_comment

    FUNCTION cxios_is_defined_domaingroup_comment(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_comment


    SUBROUTINE cxios_set_domaingroup_data_dim(domaingroup_hdl, data_dim) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: data_dim
    END SUBROUTINE cxios_set_domaingroup_data_dim

    SUBROUTINE cxios_get_domaingroup_data_dim(domaingroup_hdl, data_dim) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: data_dim
    END SUBROUTINE cxios_get_domaingroup_data_dim

    FUNCTION cxios_is_defined_domaingroup_data_dim(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_data_dim
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_data_dim


    SUBROUTINE cxios_set_domaingroup_data_i_index(domaingroup_hdl, data_i_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: data_i_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_data_i_index

    SUBROUTINE cxios_get_domaingroup_data_i_index(domaingroup_hdl, data_i_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: data_i_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_data_i_index

    FUNCTION cxios_is_defined_domaingroup_data_i_index(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_data_i_index
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_data_i_index


    SUBROUTINE cxios_set_domaingroup_data_ibegin(domaingroup_hdl, data_ibegin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: data_ibegin
    END SUBROUTINE cxios_set_domaingroup_data_ibegin

    SUBROUTINE cxios_get_domaingroup_data_ibegin(domaingroup_hdl, data_ibegin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: data_ibegin
    END SUBROUTINE cxios_get_domaingroup_data_ibegin

    FUNCTION cxios_is_defined_domaingroup_data_ibegin(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_data_ibegin
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_data_ibegin


    SUBROUTINE cxios_set_domaingroup_data_j_index(domaingroup_hdl, data_j_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: data_j_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_data_j_index

    SUBROUTINE cxios_get_domaingroup_data_j_index(domaingroup_hdl, data_j_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: data_j_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_data_j_index

    FUNCTION cxios_is_defined_domaingroup_data_j_index(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_data_j_index
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_data_j_index


    SUBROUTINE cxios_set_domaingroup_data_jbegin(domaingroup_hdl, data_jbegin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: data_jbegin
    END SUBROUTINE cxios_set_domaingroup_data_jbegin

    SUBROUTINE cxios_get_domaingroup_data_jbegin(domaingroup_hdl, data_jbegin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: data_jbegin
    END SUBROUTINE cxios_get_domaingroup_data_jbegin

    FUNCTION cxios_is_defined_domaingroup_data_jbegin(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_data_jbegin
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_data_jbegin


    SUBROUTINE cxios_set_domaingroup_data_ni(domaingroup_hdl, data_ni) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: data_ni
    END SUBROUTINE cxios_set_domaingroup_data_ni

    SUBROUTINE cxios_get_domaingroup_data_ni(domaingroup_hdl, data_ni) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: data_ni
    END SUBROUTINE cxios_get_domaingroup_data_ni

    FUNCTION cxios_is_defined_domaingroup_data_ni(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_data_ni
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_data_ni


    SUBROUTINE cxios_set_domaingroup_data_nj(domaingroup_hdl, data_nj) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: data_nj
    END SUBROUTINE cxios_set_domaingroup_data_nj

    SUBROUTINE cxios_get_domaingroup_data_nj(domaingroup_hdl, data_nj) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: data_nj
    END SUBROUTINE cxios_get_domaingroup_data_nj

    FUNCTION cxios_is_defined_domaingroup_data_nj(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_data_nj
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_data_nj


    SUBROUTINE cxios_set_domaingroup_dim_i_name(domaingroup_hdl, dim_i_name, dim_i_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: dim_i_name
      INTEGER  (kind = C_INT)     , VALUE        :: dim_i_name_size
    END SUBROUTINE cxios_set_domaingroup_dim_i_name

    SUBROUTINE cxios_get_domaingroup_dim_i_name(domaingroup_hdl, dim_i_name, dim_i_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: dim_i_name
      INTEGER  (kind = C_INT)     , VALUE        :: dim_i_name_size
    END SUBROUTINE cxios_get_domaingroup_dim_i_name

    FUNCTION cxios_is_defined_domaingroup_dim_i_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_dim_i_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_dim_i_name


    SUBROUTINE cxios_set_domaingroup_dim_j_name(domaingroup_hdl, dim_j_name, dim_j_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: dim_j_name
      INTEGER  (kind = C_INT)     , VALUE        :: dim_j_name_size
    END SUBROUTINE cxios_set_domaingroup_dim_j_name

    SUBROUTINE cxios_get_domaingroup_dim_j_name(domaingroup_hdl, dim_j_name, dim_j_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: dim_j_name
      INTEGER  (kind = C_INT)     , VALUE        :: dim_j_name_size
    END SUBROUTINE cxios_get_domaingroup_dim_j_name

    FUNCTION cxios_is_defined_domaingroup_dim_j_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_dim_j_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_dim_j_name


    SUBROUTINE cxios_set_domaingroup_domain_ref(domaingroup_hdl, domain_ref, domain_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: domain_ref
      INTEGER  (kind = C_INT)     , VALUE        :: domain_ref_size
    END SUBROUTINE cxios_set_domaingroup_domain_ref

    SUBROUTINE cxios_get_domaingroup_domain_ref(domaingroup_hdl, domain_ref, domain_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: domain_ref
      INTEGER  (kind = C_INT)     , VALUE        :: domain_ref_size
    END SUBROUTINE cxios_get_domaingroup_domain_ref

    FUNCTION cxios_is_defined_domaingroup_domain_ref(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_domain_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_domain_ref


    SUBROUTINE cxios_set_domaingroup_group_ref(domaingroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_set_domaingroup_group_ref

    SUBROUTINE cxios_get_domaingroup_group_ref(domaingroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_get_domaingroup_group_ref

    FUNCTION cxios_is_defined_domaingroup_group_ref(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_group_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_group_ref


    SUBROUTINE cxios_set_domaingroup_i_index(domaingroup_hdl, i_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: i_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_i_index

    SUBROUTINE cxios_get_domaingroup_i_index(domaingroup_hdl, i_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: i_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_i_index

    FUNCTION cxios_is_defined_domaingroup_i_index(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_i_index
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_i_index


    SUBROUTINE cxios_set_domaingroup_ibegin(domaingroup_hdl, ibegin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: ibegin
    END SUBROUTINE cxios_set_domaingroup_ibegin

    SUBROUTINE cxios_get_domaingroup_ibegin(domaingroup_hdl, ibegin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: ibegin
    END SUBROUTINE cxios_get_domaingroup_ibegin

    FUNCTION cxios_is_defined_domaingroup_ibegin(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_ibegin
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_ibegin


    SUBROUTINE cxios_set_domaingroup_j_index(domaingroup_hdl, j_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: j_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_j_index

    SUBROUTINE cxios_get_domaingroup_j_index(domaingroup_hdl, j_index, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: j_index
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_j_index

    FUNCTION cxios_is_defined_domaingroup_j_index(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_j_index
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_j_index


    SUBROUTINE cxios_set_domaingroup_jbegin(domaingroup_hdl, jbegin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: jbegin
    END SUBROUTINE cxios_set_domaingroup_jbegin

    SUBROUTINE cxios_get_domaingroup_jbegin(domaingroup_hdl, jbegin) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: jbegin
    END SUBROUTINE cxios_get_domaingroup_jbegin

    FUNCTION cxios_is_defined_domaingroup_jbegin(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_jbegin
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_jbegin


    SUBROUTINE cxios_set_domaingroup_lat_name(domaingroup_hdl, lat_name, lat_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: lat_name
      INTEGER  (kind = C_INT)     , VALUE        :: lat_name_size
    END SUBROUTINE cxios_set_domaingroup_lat_name

    SUBROUTINE cxios_get_domaingroup_lat_name(domaingroup_hdl, lat_name, lat_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: lat_name
      INTEGER  (kind = C_INT)     , VALUE        :: lat_name_size
    END SUBROUTINE cxios_get_domaingroup_lat_name

    FUNCTION cxios_is_defined_domaingroup_lat_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_lat_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_lat_name


    SUBROUTINE cxios_set_domaingroup_latvalue_1d(domaingroup_hdl, latvalue_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: latvalue_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_latvalue_1d

    SUBROUTINE cxios_get_domaingroup_latvalue_1d(domaingroup_hdl, latvalue_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: latvalue_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_latvalue_1d

    FUNCTION cxios_is_defined_domaingroup_latvalue_1d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_latvalue_1d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_latvalue_1d


    SUBROUTINE cxios_set_domaingroup_latvalue_2d(domaingroup_hdl, latvalue_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: latvalue_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_latvalue_2d

    SUBROUTINE cxios_get_domaingroup_latvalue_2d(domaingroup_hdl, latvalue_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: latvalue_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_latvalue_2d

    FUNCTION cxios_is_defined_domaingroup_latvalue_2d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_latvalue_2d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_latvalue_2d


    SUBROUTINE cxios_set_domaingroup_lon_name(domaingroup_hdl, lon_name, lon_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: lon_name
      INTEGER  (kind = C_INT)     , VALUE        :: lon_name_size
    END SUBROUTINE cxios_set_domaingroup_lon_name

    SUBROUTINE cxios_get_domaingroup_lon_name(domaingroup_hdl, lon_name, lon_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: lon_name
      INTEGER  (kind = C_INT)     , VALUE        :: lon_name_size
    END SUBROUTINE cxios_get_domaingroup_lon_name

    FUNCTION cxios_is_defined_domaingroup_lon_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_lon_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_lon_name


    SUBROUTINE cxios_set_domaingroup_long_name(domaingroup_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_set_domaingroup_long_name

    SUBROUTINE cxios_get_domaingroup_long_name(domaingroup_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_get_domaingroup_long_name

    FUNCTION cxios_is_defined_domaingroup_long_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_long_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_long_name


    SUBROUTINE cxios_set_domaingroup_lonvalue_1d(domaingroup_hdl, lonvalue_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: lonvalue_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_lonvalue_1d

    SUBROUTINE cxios_get_domaingroup_lonvalue_1d(domaingroup_hdl, lonvalue_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: lonvalue_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_lonvalue_1d

    FUNCTION cxios_is_defined_domaingroup_lonvalue_1d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_lonvalue_1d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_lonvalue_1d


    SUBROUTINE cxios_set_domaingroup_lonvalue_2d(domaingroup_hdl, lonvalue_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: lonvalue_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_lonvalue_2d

    SUBROUTINE cxios_get_domaingroup_lonvalue_2d(domaingroup_hdl, lonvalue_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)     , DIMENSION(*) :: lonvalue_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_lonvalue_2d

    FUNCTION cxios_is_defined_domaingroup_lonvalue_2d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_lonvalue_2d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_lonvalue_2d


    SUBROUTINE cxios_set_domaingroup_mask_1d(domaingroup_hdl, mask_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_mask_1d

    SUBROUTINE cxios_get_domaingroup_mask_1d(domaingroup_hdl, mask_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_mask_1d

    FUNCTION cxios_is_defined_domaingroup_mask_1d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_mask_1d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_mask_1d


    SUBROUTINE cxios_set_domaingroup_mask_2d(domaingroup_hdl, mask_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_mask_2d

    SUBROUTINE cxios_get_domaingroup_mask_2d(domaingroup_hdl, mask_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_mask_2d

    FUNCTION cxios_is_defined_domaingroup_mask_2d(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_mask_2d
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_mask_2d


    SUBROUTINE cxios_set_domaingroup_name(domaingroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_domaingroup_name

    SUBROUTINE cxios_get_domaingroup_name(domaingroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_domaingroup_name

    FUNCTION cxios_is_defined_domaingroup_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_name


    SUBROUTINE cxios_set_domaingroup_ni(domaingroup_hdl, ni) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: ni
    END SUBROUTINE cxios_set_domaingroup_ni

    SUBROUTINE cxios_get_domaingroup_ni(domaingroup_hdl, ni) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: ni
    END SUBROUTINE cxios_get_domaingroup_ni

    FUNCTION cxios_is_defined_domaingroup_ni(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_ni
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_ni


    SUBROUTINE cxios_set_domaingroup_ni_glo(domaingroup_hdl, ni_glo) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: ni_glo
    END SUBROUTINE cxios_set_domaingroup_ni_glo

    SUBROUTINE cxios_get_domaingroup_ni_glo(domaingroup_hdl, ni_glo) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: ni_glo
    END SUBROUTINE cxios_get_domaingroup_ni_glo

    FUNCTION cxios_is_defined_domaingroup_ni_glo(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_ni_glo
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_ni_glo


    SUBROUTINE cxios_set_domaingroup_nj(domaingroup_hdl, nj) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: nj
    END SUBROUTINE cxios_set_domaingroup_nj

    SUBROUTINE cxios_get_domaingroup_nj(domaingroup_hdl, nj) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: nj
    END SUBROUTINE cxios_get_domaingroup_nj

    FUNCTION cxios_is_defined_domaingroup_nj(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_nj
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_nj


    SUBROUTINE cxios_set_domaingroup_nj_glo(domaingroup_hdl, nj_glo) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: nj_glo
    END SUBROUTINE cxios_set_domaingroup_nj_glo

    SUBROUTINE cxios_get_domaingroup_nj_glo(domaingroup_hdl, nj_glo) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: nj_glo
    END SUBROUTINE cxios_get_domaingroup_nj_glo

    FUNCTION cxios_is_defined_domaingroup_nj_glo(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_nj_glo
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_nj_glo


    SUBROUTINE cxios_set_domaingroup_ntiles(domaingroup_hdl, ntiles) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: ntiles
    END SUBROUTINE cxios_set_domaingroup_ntiles

    SUBROUTINE cxios_get_domaingroup_ntiles(domaingroup_hdl, ntiles) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: ntiles
    END SUBROUTINE cxios_get_domaingroup_ntiles

    FUNCTION cxios_is_defined_domaingroup_ntiles(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_ntiles
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_ntiles


    SUBROUTINE cxios_set_domaingroup_nvertex(domaingroup_hdl, nvertex) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: nvertex
    END SUBROUTINE cxios_set_domaingroup_nvertex

    SUBROUTINE cxios_get_domaingroup_nvertex(domaingroup_hdl, nvertex) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: nvertex
    END SUBROUTINE cxios_get_domaingroup_nvertex

    FUNCTION cxios_is_defined_domaingroup_nvertex(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_nvertex
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_nvertex


    SUBROUTINE cxios_set_domaingroup_prec(domaingroup_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: prec
    END SUBROUTINE cxios_set_domaingroup_prec

    SUBROUTINE cxios_get_domaingroup_prec(domaingroup_hdl, prec) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      INTEGER (KIND=C_INT)             :: prec
    END SUBROUTINE cxios_get_domaingroup_prec

    FUNCTION cxios_is_defined_domaingroup_prec(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_prec
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_prec


    SUBROUTINE cxios_set_domaingroup_radius(domaingroup_hdl, radius) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)      , VALUE :: radius
    END SUBROUTINE cxios_set_domaingroup_radius

    SUBROUTINE cxios_get_domaingroup_radius(domaingroup_hdl, radius) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      REAL (KIND=C_DOUBLE)             :: radius
    END SUBROUTINE cxios_get_domaingroup_radius

    FUNCTION cxios_is_defined_domaingroup_radius(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_radius
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_radius


    SUBROUTINE cxios_set_domaingroup_standard_name(domaingroup_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_set_domaingroup_standard_name

    SUBROUTINE cxios_get_domaingroup_standard_name(domaingroup_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_get_domaingroup_standard_name

    FUNCTION cxios_is_defined_domaingroup_standard_name(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_standard_name
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_standard_name


    SUBROUTINE cxios_set_domaingroup_tile_data_ibegin(domaingroup_hdl, tile_data_ibegin, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_data_ibegin
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_tile_data_ibegin

    SUBROUTINE cxios_get_domaingroup_tile_data_ibegin(domaingroup_hdl, tile_data_ibegin, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_data_ibegin
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_tile_data_ibegin

    FUNCTION cxios_is_defined_domaingroup_tile_data_ibegin(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_tile_data_ibegin
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_tile_data_ibegin


    SUBROUTINE cxios_set_domaingroup_tile_data_jbegin(domaingroup_hdl, tile_data_jbegin, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_data_jbegin
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_tile_data_jbegin

    SUBROUTINE cxios_get_domaingroup_tile_data_jbegin(domaingroup_hdl, tile_data_jbegin, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_data_jbegin
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_tile_data_jbegin

    FUNCTION cxios_is_defined_domaingroup_tile_data_jbegin(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_tile_data_jbegin
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_tile_data_jbegin


    SUBROUTINE cxios_set_domaingroup_tile_data_ni(domaingroup_hdl, tile_data_ni, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_data_ni
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_tile_data_ni

    SUBROUTINE cxios_get_domaingroup_tile_data_ni(domaingroup_hdl, tile_data_ni, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_data_ni
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_tile_data_ni

    FUNCTION cxios_is_defined_domaingroup_tile_data_ni(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_tile_data_ni
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_tile_data_ni


    SUBROUTINE cxios_set_domaingroup_tile_data_nj(domaingroup_hdl, tile_data_nj, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_data_nj
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_tile_data_nj

    SUBROUTINE cxios_get_domaingroup_tile_data_nj(domaingroup_hdl, tile_data_nj, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_data_nj
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_tile_data_nj

    FUNCTION cxios_is_defined_domaingroup_tile_data_nj(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_tile_data_nj
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_tile_data_nj


    SUBROUTINE cxios_set_domaingroup_tile_ibegin(domaingroup_hdl, tile_ibegin, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_ibegin
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_tile_ibegin

    SUBROUTINE cxios_get_domaingroup_tile_ibegin(domaingroup_hdl, tile_ibegin, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_ibegin
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_tile_ibegin

    FUNCTION cxios_is_defined_domaingroup_tile_ibegin(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_tile_ibegin
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_tile_ibegin


    SUBROUTINE cxios_set_domaingroup_tile_jbegin(domaingroup_hdl, tile_jbegin, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_jbegin
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_tile_jbegin

    SUBROUTINE cxios_get_domaingroup_tile_jbegin(domaingroup_hdl, tile_jbegin, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_jbegin
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_tile_jbegin

    FUNCTION cxios_is_defined_domaingroup_tile_jbegin(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_tile_jbegin
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_tile_jbegin


    SUBROUTINE cxios_set_domaingroup_tile_ni(domaingroup_hdl, tile_ni, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_ni
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_tile_ni

    SUBROUTINE cxios_get_domaingroup_tile_ni(domaingroup_hdl, tile_ni, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_ni
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_tile_ni

    FUNCTION cxios_is_defined_domaingroup_tile_ni(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_tile_ni
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_tile_ni


    SUBROUTINE cxios_set_domaingroup_tile_nj(domaingroup_hdl, tile_nj, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_nj
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_domaingroup_tile_nj

    SUBROUTINE cxios_get_domaingroup_tile_nj(domaingroup_hdl, tile_nj, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: domaingroup_hdl
      INTEGER (KIND=C_INT)     , DIMENSION(*) :: tile_nj
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_domaingroup_tile_nj

    FUNCTION cxios_is_defined_domaingroup_tile_nj(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_tile_nj
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_tile_nj


    SUBROUTINE cxios_set_domaingroup_type(domaingroup_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_domaingroup_type

    SUBROUTINE cxios_get_domaingroup_type(domaingroup_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_domaingroup_type

    FUNCTION cxios_is_defined_domaingroup_type(domaingroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_domaingroup_type
      INTEGER (kind = C_INTPTR_T), VALUE :: domaingroup_hdl
    END FUNCTION cxios_is_defined_domaingroup_type

  END INTERFACE

END MODULE domaingroup_interface_attr
