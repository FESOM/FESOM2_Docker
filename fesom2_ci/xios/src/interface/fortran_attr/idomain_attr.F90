! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE idomain_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE idomain
  USE domain_interface_attr

CONTAINS

  SUBROUTINE xios(set_domain_attr)  &
    ( domain_id, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
    , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
    , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
    , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
    , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
    , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

    IMPLICIT NONE
      TYPE(txios(domain))  :: domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::domain_id
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: area(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_1d(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_2d(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_lat_name
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_1d(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_2d(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_lon_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      INTEGER  , OPTIONAL, INTENT(IN) :: data_dim
      INTEGER  , OPTIONAL, INTENT(IN) :: data_i_index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: data_ibegin
      INTEGER  , OPTIONAL, INTENT(IN) :: data_j_index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: data_jbegin
      INTEGER  , OPTIONAL, INTENT(IN) :: data_ni
      INTEGER  , OPTIONAL, INTENT(IN) :: data_nj
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: dim_i_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: dim_j_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: domain_ref
      INTEGER  , OPTIONAL, INTENT(IN) :: i_index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: ibegin
      INTEGER  , OPTIONAL, INTENT(IN) :: j_index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: jbegin
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: lat_name
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: latvalue_1d(:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: latvalue_2d(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: lon_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lonvalue_1d(:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lonvalue_2d(:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_1d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_2d(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d_tmp(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      INTEGER  , OPTIONAL, INTENT(IN) :: ni
      INTEGER  , OPTIONAL, INTENT(IN) :: ni_glo
      INTEGER  , OPTIONAL, INTENT(IN) :: nj
      INTEGER  , OPTIONAL, INTENT(IN) :: nj_glo
      INTEGER  , OPTIONAL, INTENT(IN) :: ntiles
      INTEGER  , OPTIONAL, INTENT(IN) :: nvertex
      INTEGER  , OPTIONAL, INTENT(IN) :: prec
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: radius
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_ibegin(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_jbegin(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_ni(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_nj(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_ibegin(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_jbegin(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_ni(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_nj(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type

      CALL xios(get_domain_handle) &
      (domain_id,domain_hdl)
      CALL xios(set_domain_attr_hdl_)   &
      ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
      , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
      , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
      , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
      , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
      , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

  END SUBROUTINE xios(set_domain_attr)

  SUBROUTINE xios(set_domain_attr_hdl)  &
    ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
    , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
    , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
    , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
    , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
    , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

    IMPLICIT NONE
      TYPE(txios(domain)) , INTENT(IN) :: domain_hdl
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: area(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_1d(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_2d(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_lat_name
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_1d(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_2d(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_lon_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      INTEGER  , OPTIONAL, INTENT(IN) :: data_dim
      INTEGER  , OPTIONAL, INTENT(IN) :: data_i_index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: data_ibegin
      INTEGER  , OPTIONAL, INTENT(IN) :: data_j_index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: data_jbegin
      INTEGER  , OPTIONAL, INTENT(IN) :: data_ni
      INTEGER  , OPTIONAL, INTENT(IN) :: data_nj
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: dim_i_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: dim_j_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: domain_ref
      INTEGER  , OPTIONAL, INTENT(IN) :: i_index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: ibegin
      INTEGER  , OPTIONAL, INTENT(IN) :: j_index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: jbegin
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: lat_name
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: latvalue_1d(:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: latvalue_2d(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: lon_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lonvalue_1d(:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lonvalue_2d(:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_1d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_2d(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d_tmp(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      INTEGER  , OPTIONAL, INTENT(IN) :: ni
      INTEGER  , OPTIONAL, INTENT(IN) :: ni_glo
      INTEGER  , OPTIONAL, INTENT(IN) :: nj
      INTEGER  , OPTIONAL, INTENT(IN) :: nj_glo
      INTEGER  , OPTIONAL, INTENT(IN) :: ntiles
      INTEGER  , OPTIONAL, INTENT(IN) :: nvertex
      INTEGER  , OPTIONAL, INTENT(IN) :: prec
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: radius
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_ibegin(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_jbegin(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_ni(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_nj(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_ibegin(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_jbegin(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_ni(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_nj(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type

      CALL xios(set_domain_attr_hdl_)  &
      ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
      , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
      , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
      , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
      , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
      , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

  END SUBROUTINE xios(set_domain_attr_hdl)

  SUBROUTINE xios(set_domain_attr_hdl_)   &
    ( domain_hdl, area_, bounds_lat_1d_, bounds_lat_2d_, bounds_lat_name_, bounds_lon_1d_, bounds_lon_2d_  &
    , bounds_lon_name_, comment_, data_dim_, data_i_index_, data_ibegin_, data_j_index_, data_jbegin_  &
    , data_ni_, data_nj_, dim_i_name_, dim_j_name_, domain_ref_, i_index_, ibegin_, j_index_, jbegin_  &
    , lat_name_, latvalue_1d_, latvalue_2d_, lon_name_, long_name_, lonvalue_1d_, lonvalue_2d_, mask_1d_  &
    , mask_2d_, name_, ni_, ni_glo_, nj_, nj_glo_, ntiles_, nvertex_, prec_, radius_, standard_name_  &
    , tile_data_ibegin_, tile_data_jbegin_, tile_data_ni_, tile_data_nj_, tile_ibegin_, tile_jbegin_  &
    , tile_ni_, tile_nj_, type_ )

    IMPLICIT NONE
      TYPE(txios(domain)) , INTENT(IN) :: domain_hdl
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: area_(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_1d_(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lat_2d_(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_lat_name_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_1d_(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: bounds_lon_2d_(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: bounds_lon_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment_
      INTEGER  , OPTIONAL, INTENT(IN) :: data_dim_
      INTEGER  , OPTIONAL, INTENT(IN) :: data_i_index_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: data_ibegin_
      INTEGER  , OPTIONAL, INTENT(IN) :: data_j_index_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: data_jbegin_
      INTEGER  , OPTIONAL, INTENT(IN) :: data_ni_
      INTEGER  , OPTIONAL, INTENT(IN) :: data_nj_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: dim_i_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: dim_j_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: domain_ref_
      INTEGER  , OPTIONAL, INTENT(IN) :: i_index_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: ibegin_
      INTEGER  , OPTIONAL, INTENT(IN) :: j_index_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: jbegin_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: lat_name_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: latvalue_1d_(:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: latvalue_2d_(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: lon_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lonvalue_1d_(:)
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: lonvalue_2d_(:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_1d_(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d__tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_2d_(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d__tmp(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_
      INTEGER  , OPTIONAL, INTENT(IN) :: ni_
      INTEGER  , OPTIONAL, INTENT(IN) :: ni_glo_
      INTEGER  , OPTIONAL, INTENT(IN) :: nj_
      INTEGER  , OPTIONAL, INTENT(IN) :: nj_glo_
      INTEGER  , OPTIONAL, INTENT(IN) :: ntiles_
      INTEGER  , OPTIONAL, INTENT(IN) :: nvertex_
      INTEGER  , OPTIONAL, INTENT(IN) :: prec_
      REAL (KIND=8) , OPTIONAL, INTENT(IN) :: radius_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name_
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_ibegin_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_jbegin_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_ni_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_data_nj_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_ibegin_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_jbegin_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_ni_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: tile_nj_(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type_

      IF (PRESENT(area_)) THEN
        CALL cxios_set_domain_area &
      (domain_hdl%daddr, area_, SHAPE(area_))
      ENDIF

      IF (PRESENT(bounds_lat_1d_)) THEN
        CALL cxios_set_domain_bounds_lat_1d &
      (domain_hdl%daddr, bounds_lat_1d_, SHAPE(bounds_lat_1d_))
      ENDIF

      IF (PRESENT(bounds_lat_2d_)) THEN
        CALL cxios_set_domain_bounds_lat_2d &
      (domain_hdl%daddr, bounds_lat_2d_, SHAPE(bounds_lat_2d_))
      ENDIF

      IF (PRESENT(bounds_lat_name_)) THEN
        CALL cxios_set_domain_bounds_lat_name &
      (domain_hdl%daddr, bounds_lat_name_, len(bounds_lat_name_))
      ENDIF

      IF (PRESENT(bounds_lon_1d_)) THEN
        CALL cxios_set_domain_bounds_lon_1d &
      (domain_hdl%daddr, bounds_lon_1d_, SHAPE(bounds_lon_1d_))
      ENDIF

      IF (PRESENT(bounds_lon_2d_)) THEN
        CALL cxios_set_domain_bounds_lon_2d &
      (domain_hdl%daddr, bounds_lon_2d_, SHAPE(bounds_lon_2d_))
      ENDIF

      IF (PRESENT(bounds_lon_name_)) THEN
        CALL cxios_set_domain_bounds_lon_name &
      (domain_hdl%daddr, bounds_lon_name_, len(bounds_lon_name_))
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_set_domain_comment &
      (domain_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(data_dim_)) THEN
        CALL cxios_set_domain_data_dim &
      (domain_hdl%daddr, data_dim_)
      ENDIF

      IF (PRESENT(data_i_index_)) THEN
        CALL cxios_set_domain_data_i_index &
      (domain_hdl%daddr, data_i_index_, SHAPE(data_i_index_))
      ENDIF

      IF (PRESENT(data_ibegin_)) THEN
        CALL cxios_set_domain_data_ibegin &
      (domain_hdl%daddr, data_ibegin_)
      ENDIF

      IF (PRESENT(data_j_index_)) THEN
        CALL cxios_set_domain_data_j_index &
      (domain_hdl%daddr, data_j_index_, SHAPE(data_j_index_))
      ENDIF

      IF (PRESENT(data_jbegin_)) THEN
        CALL cxios_set_domain_data_jbegin &
      (domain_hdl%daddr, data_jbegin_)
      ENDIF

      IF (PRESENT(data_ni_)) THEN
        CALL cxios_set_domain_data_ni &
      (domain_hdl%daddr, data_ni_)
      ENDIF

      IF (PRESENT(data_nj_)) THEN
        CALL cxios_set_domain_data_nj &
      (domain_hdl%daddr, data_nj_)
      ENDIF

      IF (PRESENT(dim_i_name_)) THEN
        CALL cxios_set_domain_dim_i_name &
      (domain_hdl%daddr, dim_i_name_, len(dim_i_name_))
      ENDIF

      IF (PRESENT(dim_j_name_)) THEN
        CALL cxios_set_domain_dim_j_name &
      (domain_hdl%daddr, dim_j_name_, len(dim_j_name_))
      ENDIF

      IF (PRESENT(domain_ref_)) THEN
        CALL cxios_set_domain_domain_ref &
      (domain_hdl%daddr, domain_ref_, len(domain_ref_))
      ENDIF

      IF (PRESENT(i_index_)) THEN
        CALL cxios_set_domain_i_index &
      (domain_hdl%daddr, i_index_, SHAPE(i_index_))
      ENDIF

      IF (PRESENT(ibegin_)) THEN
        CALL cxios_set_domain_ibegin &
      (domain_hdl%daddr, ibegin_)
      ENDIF

      IF (PRESENT(j_index_)) THEN
        CALL cxios_set_domain_j_index &
      (domain_hdl%daddr, j_index_, SHAPE(j_index_))
      ENDIF

      IF (PRESENT(jbegin_)) THEN
        CALL cxios_set_domain_jbegin &
      (domain_hdl%daddr, jbegin_)
      ENDIF

      IF (PRESENT(lat_name_)) THEN
        CALL cxios_set_domain_lat_name &
      (domain_hdl%daddr, lat_name_, len(lat_name_))
      ENDIF

      IF (PRESENT(latvalue_1d_)) THEN
        CALL cxios_set_domain_latvalue_1d &
      (domain_hdl%daddr, latvalue_1d_, SHAPE(latvalue_1d_))
      ENDIF

      IF (PRESENT(latvalue_2d_)) THEN
        CALL cxios_set_domain_latvalue_2d &
      (domain_hdl%daddr, latvalue_2d_, SHAPE(latvalue_2d_))
      ENDIF

      IF (PRESENT(lon_name_)) THEN
        CALL cxios_set_domain_lon_name &
      (domain_hdl%daddr, lon_name_, len(lon_name_))
      ENDIF

      IF (PRESENT(long_name_)) THEN
        CALL cxios_set_domain_long_name &
      (domain_hdl%daddr, long_name_, len(long_name_))
      ENDIF

      IF (PRESENT(lonvalue_1d_)) THEN
        CALL cxios_set_domain_lonvalue_1d &
      (domain_hdl%daddr, lonvalue_1d_, SHAPE(lonvalue_1d_))
      ENDIF

      IF (PRESENT(lonvalue_2d_)) THEN
        CALL cxios_set_domain_lonvalue_2d &
      (domain_hdl%daddr, lonvalue_2d_, SHAPE(lonvalue_2d_))
      ENDIF

      IF (PRESENT(mask_1d_)) THEN
        ALLOCATE(mask_1d__tmp(SIZE(mask_1d_,1)))
        mask_1d__tmp = mask_1d_
        CALL cxios_set_domain_mask_1d &
      (domain_hdl%daddr, mask_1d__tmp, SHAPE(mask_1d_))
      ENDIF

      IF (PRESENT(mask_2d_)) THEN
        ALLOCATE(mask_2d__tmp(SIZE(mask_2d_,1), SIZE(mask_2d_,2)))
        mask_2d__tmp = mask_2d_
        CALL cxios_set_domain_mask_2d &
      (domain_hdl%daddr, mask_2d__tmp, SHAPE(mask_2d_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_set_domain_name &
      (domain_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(ni_)) THEN
        CALL cxios_set_domain_ni &
      (domain_hdl%daddr, ni_)
      ENDIF

      IF (PRESENT(ni_glo_)) THEN
        CALL cxios_set_domain_ni_glo &
      (domain_hdl%daddr, ni_glo_)
      ENDIF

      IF (PRESENT(nj_)) THEN
        CALL cxios_set_domain_nj &
      (domain_hdl%daddr, nj_)
      ENDIF

      IF (PRESENT(nj_glo_)) THEN
        CALL cxios_set_domain_nj_glo &
      (domain_hdl%daddr, nj_glo_)
      ENDIF

      IF (PRESENT(ntiles_)) THEN
        CALL cxios_set_domain_ntiles &
      (domain_hdl%daddr, ntiles_)
      ENDIF

      IF (PRESENT(nvertex_)) THEN
        CALL cxios_set_domain_nvertex &
      (domain_hdl%daddr, nvertex_)
      ENDIF

      IF (PRESENT(prec_)) THEN
        CALL cxios_set_domain_prec &
      (domain_hdl%daddr, prec_)
      ENDIF

      IF (PRESENT(radius_)) THEN
        CALL cxios_set_domain_radius &
      (domain_hdl%daddr, radius_)
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        CALL cxios_set_domain_standard_name &
      (domain_hdl%daddr, standard_name_, len(standard_name_))
      ENDIF

      IF (PRESENT(tile_data_ibegin_)) THEN
        CALL cxios_set_domain_tile_data_ibegin &
      (domain_hdl%daddr, tile_data_ibegin_, SHAPE(tile_data_ibegin_))
      ENDIF

      IF (PRESENT(tile_data_jbegin_)) THEN
        CALL cxios_set_domain_tile_data_jbegin &
      (domain_hdl%daddr, tile_data_jbegin_, SHAPE(tile_data_jbegin_))
      ENDIF

      IF (PRESENT(tile_data_ni_)) THEN
        CALL cxios_set_domain_tile_data_ni &
      (domain_hdl%daddr, tile_data_ni_, SHAPE(tile_data_ni_))
      ENDIF

      IF (PRESENT(tile_data_nj_)) THEN
        CALL cxios_set_domain_tile_data_nj &
      (domain_hdl%daddr, tile_data_nj_, SHAPE(tile_data_nj_))
      ENDIF

      IF (PRESENT(tile_ibegin_)) THEN
        CALL cxios_set_domain_tile_ibegin &
      (domain_hdl%daddr, tile_ibegin_, SHAPE(tile_ibegin_))
      ENDIF

      IF (PRESENT(tile_jbegin_)) THEN
        CALL cxios_set_domain_tile_jbegin &
      (domain_hdl%daddr, tile_jbegin_, SHAPE(tile_jbegin_))
      ENDIF

      IF (PRESENT(tile_ni_)) THEN
        CALL cxios_set_domain_tile_ni &
      (domain_hdl%daddr, tile_ni_, SHAPE(tile_ni_))
      ENDIF

      IF (PRESENT(tile_nj_)) THEN
        CALL cxios_set_domain_tile_nj &
      (domain_hdl%daddr, tile_nj_, SHAPE(tile_nj_))
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_set_domain_type &
      (domain_hdl%daddr, type_, len(type_))
      ENDIF

  END SUBROUTINE xios(set_domain_attr_hdl_)

  SUBROUTINE xios(get_domain_attr)  &
    ( domain_id, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
    , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
    , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
    , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
    , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
    , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

    IMPLICIT NONE
      TYPE(txios(domain))  :: domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::domain_id
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: area(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_1d(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_2d(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_lat_name
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_1d(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_2d(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_lon_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_dim
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_i_index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_ibegin
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_j_index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_jbegin
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_ni
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_nj
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: dim_i_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: dim_j_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: domain_ref
      INTEGER  , OPTIONAL, INTENT(OUT) :: i_index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: ibegin
      INTEGER  , OPTIONAL, INTENT(OUT) :: j_index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: jbegin
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: lat_name
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: latvalue_1d(:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: latvalue_2d(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: lon_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lonvalue_1d(:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lonvalue_2d(:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_1d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_2d(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d_tmp(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      INTEGER  , OPTIONAL, INTENT(OUT) :: ni
      INTEGER  , OPTIONAL, INTENT(OUT) :: ni_glo
      INTEGER  , OPTIONAL, INTENT(OUT) :: nj
      INTEGER  , OPTIONAL, INTENT(OUT) :: nj_glo
      INTEGER  , OPTIONAL, INTENT(OUT) :: ntiles
      INTEGER  , OPTIONAL, INTENT(OUT) :: nvertex
      INTEGER  , OPTIONAL, INTENT(OUT) :: prec
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: radius
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_ibegin(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_jbegin(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_ni(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_nj(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_ibegin(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_jbegin(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_ni(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_nj(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type

      CALL xios(get_domain_handle) &
      (domain_id,domain_hdl)
      CALL xios(get_domain_attr_hdl_)   &
      ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
      , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
      , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
      , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
      , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
      , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

  END SUBROUTINE xios(get_domain_attr)

  SUBROUTINE xios(get_domain_attr_hdl)  &
    ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
    , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
    , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
    , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
    , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
    , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

    IMPLICIT NONE
      TYPE(txios(domain)) , INTENT(IN) :: domain_hdl
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: area(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_1d(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_2d(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_lat_name
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_1d(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_2d(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_lon_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_dim
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_i_index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_ibegin
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_j_index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_jbegin
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_ni
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_nj
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: dim_i_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: dim_j_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: domain_ref
      INTEGER  , OPTIONAL, INTENT(OUT) :: i_index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: ibegin
      INTEGER  , OPTIONAL, INTENT(OUT) :: j_index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: jbegin
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: lat_name
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: latvalue_1d(:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: latvalue_2d(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: lon_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lonvalue_1d(:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lonvalue_2d(:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_1d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_2d(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d_tmp(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      INTEGER  , OPTIONAL, INTENT(OUT) :: ni
      INTEGER  , OPTIONAL, INTENT(OUT) :: ni_glo
      INTEGER  , OPTIONAL, INTENT(OUT) :: nj
      INTEGER  , OPTIONAL, INTENT(OUT) :: nj_glo
      INTEGER  , OPTIONAL, INTENT(OUT) :: ntiles
      INTEGER  , OPTIONAL, INTENT(OUT) :: nvertex
      INTEGER  , OPTIONAL, INTENT(OUT) :: prec
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: radius
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_ibegin(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_jbegin(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_ni(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_nj(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_ibegin(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_jbegin(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_ni(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_nj(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type

      CALL xios(get_domain_attr_hdl_)  &
      ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
      , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
      , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
      , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
      , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
      , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

  END SUBROUTINE xios(get_domain_attr_hdl)

  SUBROUTINE xios(get_domain_attr_hdl_)   &
    ( domain_hdl, area_, bounds_lat_1d_, bounds_lat_2d_, bounds_lat_name_, bounds_lon_1d_, bounds_lon_2d_  &
    , bounds_lon_name_, comment_, data_dim_, data_i_index_, data_ibegin_, data_j_index_, data_jbegin_  &
    , data_ni_, data_nj_, dim_i_name_, dim_j_name_, domain_ref_, i_index_, ibegin_, j_index_, jbegin_  &
    , lat_name_, latvalue_1d_, latvalue_2d_, lon_name_, long_name_, lonvalue_1d_, lonvalue_2d_, mask_1d_  &
    , mask_2d_, name_, ni_, ni_glo_, nj_, nj_glo_, ntiles_, nvertex_, prec_, radius_, standard_name_  &
    , tile_data_ibegin_, tile_data_jbegin_, tile_data_ni_, tile_data_nj_, tile_ibegin_, tile_jbegin_  &
    , tile_ni_, tile_nj_, type_ )

    IMPLICIT NONE
      TYPE(txios(domain)) , INTENT(IN) :: domain_hdl
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: area_(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_1d_(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lat_2d_(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_lat_name_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_1d_(:,:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: bounds_lon_2d_(:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: bounds_lon_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment_
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_dim_
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_i_index_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_ibegin_
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_j_index_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_jbegin_
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_ni_
      INTEGER  , OPTIONAL, INTENT(OUT) :: data_nj_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: dim_i_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: dim_j_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: domain_ref_
      INTEGER  , OPTIONAL, INTENT(OUT) :: i_index_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: ibegin_
      INTEGER  , OPTIONAL, INTENT(OUT) :: j_index_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: jbegin_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: lat_name_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: latvalue_1d_(:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: latvalue_2d_(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: lon_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lonvalue_1d_(:)
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: lonvalue_2d_(:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_1d_(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d__tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_2d_(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d__tmp(:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_
      INTEGER  , OPTIONAL, INTENT(OUT) :: ni_
      INTEGER  , OPTIONAL, INTENT(OUT) :: ni_glo_
      INTEGER  , OPTIONAL, INTENT(OUT) :: nj_
      INTEGER  , OPTIONAL, INTENT(OUT) :: nj_glo_
      INTEGER  , OPTIONAL, INTENT(OUT) :: ntiles_
      INTEGER  , OPTIONAL, INTENT(OUT) :: nvertex_
      INTEGER  , OPTIONAL, INTENT(OUT) :: prec_
      REAL (KIND=8) , OPTIONAL, INTENT(OUT) :: radius_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name_
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_ibegin_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_jbegin_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_ni_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_data_nj_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_ibegin_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_jbegin_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_ni_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: tile_nj_(:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type_

      IF (PRESENT(area_)) THEN
        CALL cxios_get_domain_area &
      (domain_hdl%daddr, area_, SHAPE(area_))
      ENDIF

      IF (PRESENT(bounds_lat_1d_)) THEN
        CALL cxios_get_domain_bounds_lat_1d &
      (domain_hdl%daddr, bounds_lat_1d_, SHAPE(bounds_lat_1d_))
      ENDIF

      IF (PRESENT(bounds_lat_2d_)) THEN
        CALL cxios_get_domain_bounds_lat_2d &
      (domain_hdl%daddr, bounds_lat_2d_, SHAPE(bounds_lat_2d_))
      ENDIF

      IF (PRESENT(bounds_lat_name_)) THEN
        CALL cxios_get_domain_bounds_lat_name &
      (domain_hdl%daddr, bounds_lat_name_, len(bounds_lat_name_))
      ENDIF

      IF (PRESENT(bounds_lon_1d_)) THEN
        CALL cxios_get_domain_bounds_lon_1d &
      (domain_hdl%daddr, bounds_lon_1d_, SHAPE(bounds_lon_1d_))
      ENDIF

      IF (PRESENT(bounds_lon_2d_)) THEN
        CALL cxios_get_domain_bounds_lon_2d &
      (domain_hdl%daddr, bounds_lon_2d_, SHAPE(bounds_lon_2d_))
      ENDIF

      IF (PRESENT(bounds_lon_name_)) THEN
        CALL cxios_get_domain_bounds_lon_name &
      (domain_hdl%daddr, bounds_lon_name_, len(bounds_lon_name_))
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_get_domain_comment &
      (domain_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(data_dim_)) THEN
        CALL cxios_get_domain_data_dim &
      (domain_hdl%daddr, data_dim_)
      ENDIF

      IF (PRESENT(data_i_index_)) THEN
        CALL cxios_get_domain_data_i_index &
      (domain_hdl%daddr, data_i_index_, SHAPE(data_i_index_))
      ENDIF

      IF (PRESENT(data_ibegin_)) THEN
        CALL cxios_get_domain_data_ibegin &
      (domain_hdl%daddr, data_ibegin_)
      ENDIF

      IF (PRESENT(data_j_index_)) THEN
        CALL cxios_get_domain_data_j_index &
      (domain_hdl%daddr, data_j_index_, SHAPE(data_j_index_))
      ENDIF

      IF (PRESENT(data_jbegin_)) THEN
        CALL cxios_get_domain_data_jbegin &
      (domain_hdl%daddr, data_jbegin_)
      ENDIF

      IF (PRESENT(data_ni_)) THEN
        CALL cxios_get_domain_data_ni &
      (domain_hdl%daddr, data_ni_)
      ENDIF

      IF (PRESENT(data_nj_)) THEN
        CALL cxios_get_domain_data_nj &
      (domain_hdl%daddr, data_nj_)
      ENDIF

      IF (PRESENT(dim_i_name_)) THEN
        CALL cxios_get_domain_dim_i_name &
      (domain_hdl%daddr, dim_i_name_, len(dim_i_name_))
      ENDIF

      IF (PRESENT(dim_j_name_)) THEN
        CALL cxios_get_domain_dim_j_name &
      (domain_hdl%daddr, dim_j_name_, len(dim_j_name_))
      ENDIF

      IF (PRESENT(domain_ref_)) THEN
        CALL cxios_get_domain_domain_ref &
      (domain_hdl%daddr, domain_ref_, len(domain_ref_))
      ENDIF

      IF (PRESENT(i_index_)) THEN
        CALL cxios_get_domain_i_index &
      (domain_hdl%daddr, i_index_, SHAPE(i_index_))
      ENDIF

      IF (PRESENT(ibegin_)) THEN
        CALL cxios_get_domain_ibegin &
      (domain_hdl%daddr, ibegin_)
      ENDIF

      IF (PRESENT(j_index_)) THEN
        CALL cxios_get_domain_j_index &
      (domain_hdl%daddr, j_index_, SHAPE(j_index_))
      ENDIF

      IF (PRESENT(jbegin_)) THEN
        CALL cxios_get_domain_jbegin &
      (domain_hdl%daddr, jbegin_)
      ENDIF

      IF (PRESENT(lat_name_)) THEN
        CALL cxios_get_domain_lat_name &
      (domain_hdl%daddr, lat_name_, len(lat_name_))
      ENDIF

      IF (PRESENT(latvalue_1d_)) THEN
        CALL cxios_get_domain_latvalue_1d &
      (domain_hdl%daddr, latvalue_1d_, SHAPE(latvalue_1d_))
      ENDIF

      IF (PRESENT(latvalue_2d_)) THEN
        CALL cxios_get_domain_latvalue_2d &
      (domain_hdl%daddr, latvalue_2d_, SHAPE(latvalue_2d_))
      ENDIF

      IF (PRESENT(lon_name_)) THEN
        CALL cxios_get_domain_lon_name &
      (domain_hdl%daddr, lon_name_, len(lon_name_))
      ENDIF

      IF (PRESENT(long_name_)) THEN
        CALL cxios_get_domain_long_name &
      (domain_hdl%daddr, long_name_, len(long_name_))
      ENDIF

      IF (PRESENT(lonvalue_1d_)) THEN
        CALL cxios_get_domain_lonvalue_1d &
      (domain_hdl%daddr, lonvalue_1d_, SHAPE(lonvalue_1d_))
      ENDIF

      IF (PRESENT(lonvalue_2d_)) THEN
        CALL cxios_get_domain_lonvalue_2d &
      (domain_hdl%daddr, lonvalue_2d_, SHAPE(lonvalue_2d_))
      ENDIF

      IF (PRESENT(mask_1d_)) THEN
        ALLOCATE(mask_1d__tmp(SIZE(mask_1d_,1)))
        CALL cxios_get_domain_mask_1d &
      (domain_hdl%daddr, mask_1d__tmp, SHAPE(mask_1d_))
        mask_1d_ = mask_1d__tmp
      ENDIF

      IF (PRESENT(mask_2d_)) THEN
        ALLOCATE(mask_2d__tmp(SIZE(mask_2d_,1), SIZE(mask_2d_,2)))
        CALL cxios_get_domain_mask_2d &
      (domain_hdl%daddr, mask_2d__tmp, SHAPE(mask_2d_))
        mask_2d_ = mask_2d__tmp
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_get_domain_name &
      (domain_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(ni_)) THEN
        CALL cxios_get_domain_ni &
      (domain_hdl%daddr, ni_)
      ENDIF

      IF (PRESENT(ni_glo_)) THEN
        CALL cxios_get_domain_ni_glo &
      (domain_hdl%daddr, ni_glo_)
      ENDIF

      IF (PRESENT(nj_)) THEN
        CALL cxios_get_domain_nj &
      (domain_hdl%daddr, nj_)
      ENDIF

      IF (PRESENT(nj_glo_)) THEN
        CALL cxios_get_domain_nj_glo &
      (domain_hdl%daddr, nj_glo_)
      ENDIF

      IF (PRESENT(ntiles_)) THEN
        CALL cxios_get_domain_ntiles &
      (domain_hdl%daddr, ntiles_)
      ENDIF

      IF (PRESENT(nvertex_)) THEN
        CALL cxios_get_domain_nvertex &
      (domain_hdl%daddr, nvertex_)
      ENDIF

      IF (PRESENT(prec_)) THEN
        CALL cxios_get_domain_prec &
      (domain_hdl%daddr, prec_)
      ENDIF

      IF (PRESENT(radius_)) THEN
        CALL cxios_get_domain_radius &
      (domain_hdl%daddr, radius_)
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        CALL cxios_get_domain_standard_name &
      (domain_hdl%daddr, standard_name_, len(standard_name_))
      ENDIF

      IF (PRESENT(tile_data_ibegin_)) THEN
        CALL cxios_get_domain_tile_data_ibegin &
      (domain_hdl%daddr, tile_data_ibegin_, SHAPE(tile_data_ibegin_))
      ENDIF

      IF (PRESENT(tile_data_jbegin_)) THEN
        CALL cxios_get_domain_tile_data_jbegin &
      (domain_hdl%daddr, tile_data_jbegin_, SHAPE(tile_data_jbegin_))
      ENDIF

      IF (PRESENT(tile_data_ni_)) THEN
        CALL cxios_get_domain_tile_data_ni &
      (domain_hdl%daddr, tile_data_ni_, SHAPE(tile_data_ni_))
      ENDIF

      IF (PRESENT(tile_data_nj_)) THEN
        CALL cxios_get_domain_tile_data_nj &
      (domain_hdl%daddr, tile_data_nj_, SHAPE(tile_data_nj_))
      ENDIF

      IF (PRESENT(tile_ibegin_)) THEN
        CALL cxios_get_domain_tile_ibegin &
      (domain_hdl%daddr, tile_ibegin_, SHAPE(tile_ibegin_))
      ENDIF

      IF (PRESENT(tile_jbegin_)) THEN
        CALL cxios_get_domain_tile_jbegin &
      (domain_hdl%daddr, tile_jbegin_, SHAPE(tile_jbegin_))
      ENDIF

      IF (PRESENT(tile_ni_)) THEN
        CALL cxios_get_domain_tile_ni &
      (domain_hdl%daddr, tile_ni_, SHAPE(tile_ni_))
      ENDIF

      IF (PRESENT(tile_nj_)) THEN
        CALL cxios_get_domain_tile_nj &
      (domain_hdl%daddr, tile_nj_, SHAPE(tile_nj_))
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_get_domain_type &
      (domain_hdl%daddr, type_, len(type_))
      ENDIF

  END SUBROUTINE xios(get_domain_attr_hdl_)

  SUBROUTINE xios(is_defined_domain_attr)  &
    ( domain_id, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
    , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
    , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
    , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
    , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
    , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

    IMPLICIT NONE
      TYPE(txios(domain))  :: domain_hdl
      CHARACTER(LEN=*), INTENT(IN) ::domain_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: area
      LOGICAL(KIND=C_BOOL) :: area_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_1d
      LOGICAL(KIND=C_BOOL) :: bounds_lat_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_2d
      LOGICAL(KIND=C_BOOL) :: bounds_lat_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_name
      LOGICAL(KIND=C_BOOL) :: bounds_lat_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_1d
      LOGICAL(KIND=C_BOOL) :: bounds_lon_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_2d
      LOGICAL(KIND=C_BOOL) :: bounds_lon_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_name
      LOGICAL(KIND=C_BOOL) :: bounds_lon_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_dim
      LOGICAL(KIND=C_BOOL) :: data_dim_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_i_index
      LOGICAL(KIND=C_BOOL) :: data_i_index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_ibegin
      LOGICAL(KIND=C_BOOL) :: data_ibegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_j_index
      LOGICAL(KIND=C_BOOL) :: data_j_index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_jbegin
      LOGICAL(KIND=C_BOOL) :: data_jbegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_ni
      LOGICAL(KIND=C_BOOL) :: data_ni_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_nj
      LOGICAL(KIND=C_BOOL) :: data_nj_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: dim_i_name
      LOGICAL(KIND=C_BOOL) :: dim_i_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: dim_j_name
      LOGICAL(KIND=C_BOOL) :: dim_j_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: domain_ref
      LOGICAL(KIND=C_BOOL) :: domain_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: i_index
      LOGICAL(KIND=C_BOOL) :: i_index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ibegin
      LOGICAL(KIND=C_BOOL) :: ibegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: j_index
      LOGICAL(KIND=C_BOOL) :: j_index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: jbegin
      LOGICAL(KIND=C_BOOL) :: jbegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_name
      LOGICAL(KIND=C_BOOL) :: lat_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: latvalue_1d
      LOGICAL(KIND=C_BOOL) :: latvalue_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: latvalue_2d
      LOGICAL(KIND=C_BOOL) :: latvalue_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_name
      LOGICAL(KIND=C_BOOL) :: lon_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name
      LOGICAL(KIND=C_BOOL) :: long_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lonvalue_1d
      LOGICAL(KIND=C_BOOL) :: lonvalue_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lonvalue_2d
      LOGICAL(KIND=C_BOOL) :: lonvalue_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_1d
      LOGICAL(KIND=C_BOOL) :: mask_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_2d
      LOGICAL(KIND=C_BOOL) :: mask_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ni
      LOGICAL(KIND=C_BOOL) :: ni_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ni_glo
      LOGICAL(KIND=C_BOOL) :: ni_glo_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nj
      LOGICAL(KIND=C_BOOL) :: nj_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nj_glo
      LOGICAL(KIND=C_BOOL) :: nj_glo_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ntiles
      LOGICAL(KIND=C_BOOL) :: ntiles_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nvertex
      LOGICAL(KIND=C_BOOL) :: nvertex_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: prec
      LOGICAL(KIND=C_BOOL) :: prec_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: radius
      LOGICAL(KIND=C_BOOL) :: radius_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name
      LOGICAL(KIND=C_BOOL) :: standard_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_ibegin
      LOGICAL(KIND=C_BOOL) :: tile_data_ibegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_jbegin
      LOGICAL(KIND=C_BOOL) :: tile_data_jbegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_ni
      LOGICAL(KIND=C_BOOL) :: tile_data_ni_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_nj
      LOGICAL(KIND=C_BOOL) :: tile_data_nj_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_ibegin
      LOGICAL(KIND=C_BOOL) :: tile_ibegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_jbegin
      LOGICAL(KIND=C_BOOL) :: tile_jbegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_ni
      LOGICAL(KIND=C_BOOL) :: tile_ni_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_nj
      LOGICAL(KIND=C_BOOL) :: tile_nj_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp

      CALL xios(get_domain_handle) &
      (domain_id,domain_hdl)
      CALL xios(is_defined_domain_attr_hdl_)   &
      ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
      , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
      , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
      , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
      , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
      , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

  END SUBROUTINE xios(is_defined_domain_attr)

  SUBROUTINE xios(is_defined_domain_attr_hdl)  &
    ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
    , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
    , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
    , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
    , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
    , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

    IMPLICIT NONE
      TYPE(txios(domain)) , INTENT(IN) :: domain_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: area
      LOGICAL(KIND=C_BOOL) :: area_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_1d
      LOGICAL(KIND=C_BOOL) :: bounds_lat_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_2d
      LOGICAL(KIND=C_BOOL) :: bounds_lat_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_name
      LOGICAL(KIND=C_BOOL) :: bounds_lat_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_1d
      LOGICAL(KIND=C_BOOL) :: bounds_lon_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_2d
      LOGICAL(KIND=C_BOOL) :: bounds_lon_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_name
      LOGICAL(KIND=C_BOOL) :: bounds_lon_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_dim
      LOGICAL(KIND=C_BOOL) :: data_dim_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_i_index
      LOGICAL(KIND=C_BOOL) :: data_i_index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_ibegin
      LOGICAL(KIND=C_BOOL) :: data_ibegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_j_index
      LOGICAL(KIND=C_BOOL) :: data_j_index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_jbegin
      LOGICAL(KIND=C_BOOL) :: data_jbegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_ni
      LOGICAL(KIND=C_BOOL) :: data_ni_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_nj
      LOGICAL(KIND=C_BOOL) :: data_nj_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: dim_i_name
      LOGICAL(KIND=C_BOOL) :: dim_i_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: dim_j_name
      LOGICAL(KIND=C_BOOL) :: dim_j_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: domain_ref
      LOGICAL(KIND=C_BOOL) :: domain_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: i_index
      LOGICAL(KIND=C_BOOL) :: i_index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ibegin
      LOGICAL(KIND=C_BOOL) :: ibegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: j_index
      LOGICAL(KIND=C_BOOL) :: j_index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: jbegin
      LOGICAL(KIND=C_BOOL) :: jbegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_name
      LOGICAL(KIND=C_BOOL) :: lat_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: latvalue_1d
      LOGICAL(KIND=C_BOOL) :: latvalue_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: latvalue_2d
      LOGICAL(KIND=C_BOOL) :: latvalue_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_name
      LOGICAL(KIND=C_BOOL) :: lon_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name
      LOGICAL(KIND=C_BOOL) :: long_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lonvalue_1d
      LOGICAL(KIND=C_BOOL) :: lonvalue_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lonvalue_2d
      LOGICAL(KIND=C_BOOL) :: lonvalue_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_1d
      LOGICAL(KIND=C_BOOL) :: mask_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_2d
      LOGICAL(KIND=C_BOOL) :: mask_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ni
      LOGICAL(KIND=C_BOOL) :: ni_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ni_glo
      LOGICAL(KIND=C_BOOL) :: ni_glo_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nj
      LOGICAL(KIND=C_BOOL) :: nj_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nj_glo
      LOGICAL(KIND=C_BOOL) :: nj_glo_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ntiles
      LOGICAL(KIND=C_BOOL) :: ntiles_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nvertex
      LOGICAL(KIND=C_BOOL) :: nvertex_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: prec
      LOGICAL(KIND=C_BOOL) :: prec_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: radius
      LOGICAL(KIND=C_BOOL) :: radius_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name
      LOGICAL(KIND=C_BOOL) :: standard_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_ibegin
      LOGICAL(KIND=C_BOOL) :: tile_data_ibegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_jbegin
      LOGICAL(KIND=C_BOOL) :: tile_data_jbegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_ni
      LOGICAL(KIND=C_BOOL) :: tile_data_ni_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_nj
      LOGICAL(KIND=C_BOOL) :: tile_data_nj_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_ibegin
      LOGICAL(KIND=C_BOOL) :: tile_ibegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_jbegin
      LOGICAL(KIND=C_BOOL) :: tile_jbegin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_ni
      LOGICAL(KIND=C_BOOL) :: tile_ni_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_nj
      LOGICAL(KIND=C_BOOL) :: tile_nj_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp

      CALL xios(is_defined_domain_attr_hdl_)  &
      ( domain_hdl, area, bounds_lat_1d, bounds_lat_2d, bounds_lat_name, bounds_lon_1d, bounds_lon_2d  &
      , bounds_lon_name, comment, data_dim, data_i_index, data_ibegin, data_j_index, data_jbegin, data_ni  &
      , data_nj, dim_i_name, dim_j_name, domain_ref, i_index, ibegin, j_index, jbegin, lat_name, latvalue_1d  &
      , latvalue_2d, lon_name, long_name, lonvalue_1d, lonvalue_2d, mask_1d, mask_2d, name, ni, ni_glo  &
      , nj, nj_glo, ntiles, nvertex, prec, radius, standard_name, tile_data_ibegin, tile_data_jbegin  &
      , tile_data_ni, tile_data_nj, tile_ibegin, tile_jbegin, tile_ni, tile_nj, type )

  END SUBROUTINE xios(is_defined_domain_attr_hdl)

  SUBROUTINE xios(is_defined_domain_attr_hdl_)   &
    ( domain_hdl, area_, bounds_lat_1d_, bounds_lat_2d_, bounds_lat_name_, bounds_lon_1d_, bounds_lon_2d_  &
    , bounds_lon_name_, comment_, data_dim_, data_i_index_, data_ibegin_, data_j_index_, data_jbegin_  &
    , data_ni_, data_nj_, dim_i_name_, dim_j_name_, domain_ref_, i_index_, ibegin_, j_index_, jbegin_  &
    , lat_name_, latvalue_1d_, latvalue_2d_, lon_name_, long_name_, lonvalue_1d_, lonvalue_2d_, mask_1d_  &
    , mask_2d_, name_, ni_, ni_glo_, nj_, nj_glo_, ntiles_, nvertex_, prec_, radius_, standard_name_  &
    , tile_data_ibegin_, tile_data_jbegin_, tile_data_ni_, tile_data_nj_, tile_ibegin_, tile_jbegin_  &
    , tile_ni_, tile_nj_, type_ )

    IMPLICIT NONE
      TYPE(txios(domain)) , INTENT(IN) :: domain_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: area_
      LOGICAL(KIND=C_BOOL) :: area__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_1d_
      LOGICAL(KIND=C_BOOL) :: bounds_lat_1d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_2d_
      LOGICAL(KIND=C_BOOL) :: bounds_lat_2d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lat_name_
      LOGICAL(KIND=C_BOOL) :: bounds_lat_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_1d_
      LOGICAL(KIND=C_BOOL) :: bounds_lon_1d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_2d_
      LOGICAL(KIND=C_BOOL) :: bounds_lon_2d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: bounds_lon_name_
      LOGICAL(KIND=C_BOOL) :: bounds_lon_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment_
      LOGICAL(KIND=C_BOOL) :: comment__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_dim_
      LOGICAL(KIND=C_BOOL) :: data_dim__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_i_index_
      LOGICAL(KIND=C_BOOL) :: data_i_index__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_ibegin_
      LOGICAL(KIND=C_BOOL) :: data_ibegin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_j_index_
      LOGICAL(KIND=C_BOOL) :: data_j_index__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_jbegin_
      LOGICAL(KIND=C_BOOL) :: data_jbegin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_ni_
      LOGICAL(KIND=C_BOOL) :: data_ni__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: data_nj_
      LOGICAL(KIND=C_BOOL) :: data_nj__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: dim_i_name_
      LOGICAL(KIND=C_BOOL) :: dim_i_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: dim_j_name_
      LOGICAL(KIND=C_BOOL) :: dim_j_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: domain_ref_
      LOGICAL(KIND=C_BOOL) :: domain_ref__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: i_index_
      LOGICAL(KIND=C_BOOL) :: i_index__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ibegin_
      LOGICAL(KIND=C_BOOL) :: ibegin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: j_index_
      LOGICAL(KIND=C_BOOL) :: j_index__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: jbegin_
      LOGICAL(KIND=C_BOOL) :: jbegin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lat_name_
      LOGICAL(KIND=C_BOOL) :: lat_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: latvalue_1d_
      LOGICAL(KIND=C_BOOL) :: latvalue_1d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: latvalue_2d_
      LOGICAL(KIND=C_BOOL) :: latvalue_2d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lon_name_
      LOGICAL(KIND=C_BOOL) :: lon_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name_
      LOGICAL(KIND=C_BOOL) :: long_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lonvalue_1d_
      LOGICAL(KIND=C_BOOL) :: lonvalue_1d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: lonvalue_2d_
      LOGICAL(KIND=C_BOOL) :: lonvalue_2d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_1d_
      LOGICAL(KIND=C_BOOL) :: mask_1d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_2d_
      LOGICAL(KIND=C_BOOL) :: mask_2d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_
      LOGICAL(KIND=C_BOOL) :: name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ni_
      LOGICAL(KIND=C_BOOL) :: ni__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ni_glo_
      LOGICAL(KIND=C_BOOL) :: ni_glo__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nj_
      LOGICAL(KIND=C_BOOL) :: nj__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nj_glo_
      LOGICAL(KIND=C_BOOL) :: nj_glo__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ntiles_
      LOGICAL(KIND=C_BOOL) :: ntiles__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: nvertex_
      LOGICAL(KIND=C_BOOL) :: nvertex__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: prec_
      LOGICAL(KIND=C_BOOL) :: prec__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: radius_
      LOGICAL(KIND=C_BOOL) :: radius__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name_
      LOGICAL(KIND=C_BOOL) :: standard_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_ibegin_
      LOGICAL(KIND=C_BOOL) :: tile_data_ibegin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_jbegin_
      LOGICAL(KIND=C_BOOL) :: tile_data_jbegin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_ni_
      LOGICAL(KIND=C_BOOL) :: tile_data_ni__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_data_nj_
      LOGICAL(KIND=C_BOOL) :: tile_data_nj__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_ibegin_
      LOGICAL(KIND=C_BOOL) :: tile_ibegin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_jbegin_
      LOGICAL(KIND=C_BOOL) :: tile_jbegin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_ni_
      LOGICAL(KIND=C_BOOL) :: tile_ni__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: tile_nj_
      LOGICAL(KIND=C_BOOL) :: tile_nj__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type_
      LOGICAL(KIND=C_BOOL) :: type__tmp

      IF (PRESENT(area_)) THEN
        area__tmp = cxios_is_defined_domain_area &
      (domain_hdl%daddr)
        area_ = area__tmp
      ENDIF

      IF (PRESENT(bounds_lat_1d_)) THEN
        bounds_lat_1d__tmp = cxios_is_defined_domain_bounds_lat_1d &
      (domain_hdl%daddr)
        bounds_lat_1d_ = bounds_lat_1d__tmp
      ENDIF

      IF (PRESENT(bounds_lat_2d_)) THEN
        bounds_lat_2d__tmp = cxios_is_defined_domain_bounds_lat_2d &
      (domain_hdl%daddr)
        bounds_lat_2d_ = bounds_lat_2d__tmp
      ENDIF

      IF (PRESENT(bounds_lat_name_)) THEN
        bounds_lat_name__tmp = cxios_is_defined_domain_bounds_lat_name &
      (domain_hdl%daddr)
        bounds_lat_name_ = bounds_lat_name__tmp
      ENDIF

      IF (PRESENT(bounds_lon_1d_)) THEN
        bounds_lon_1d__tmp = cxios_is_defined_domain_bounds_lon_1d &
      (domain_hdl%daddr)
        bounds_lon_1d_ = bounds_lon_1d__tmp
      ENDIF

      IF (PRESENT(bounds_lon_2d_)) THEN
        bounds_lon_2d__tmp = cxios_is_defined_domain_bounds_lon_2d &
      (domain_hdl%daddr)
        bounds_lon_2d_ = bounds_lon_2d__tmp
      ENDIF

      IF (PRESENT(bounds_lon_name_)) THEN
        bounds_lon_name__tmp = cxios_is_defined_domain_bounds_lon_name &
      (domain_hdl%daddr)
        bounds_lon_name_ = bounds_lon_name__tmp
      ENDIF

      IF (PRESENT(comment_)) THEN
        comment__tmp = cxios_is_defined_domain_comment &
      (domain_hdl%daddr)
        comment_ = comment__tmp
      ENDIF

      IF (PRESENT(data_dim_)) THEN
        data_dim__tmp = cxios_is_defined_domain_data_dim &
      (domain_hdl%daddr)
        data_dim_ = data_dim__tmp
      ENDIF

      IF (PRESENT(data_i_index_)) THEN
        data_i_index__tmp = cxios_is_defined_domain_data_i_index &
      (domain_hdl%daddr)
        data_i_index_ = data_i_index__tmp
      ENDIF

      IF (PRESENT(data_ibegin_)) THEN
        data_ibegin__tmp = cxios_is_defined_domain_data_ibegin &
      (domain_hdl%daddr)
        data_ibegin_ = data_ibegin__tmp
      ENDIF

      IF (PRESENT(data_j_index_)) THEN
        data_j_index__tmp = cxios_is_defined_domain_data_j_index &
      (domain_hdl%daddr)
        data_j_index_ = data_j_index__tmp
      ENDIF

      IF (PRESENT(data_jbegin_)) THEN
        data_jbegin__tmp = cxios_is_defined_domain_data_jbegin &
      (domain_hdl%daddr)
        data_jbegin_ = data_jbegin__tmp
      ENDIF

      IF (PRESENT(data_ni_)) THEN
        data_ni__tmp = cxios_is_defined_domain_data_ni &
      (domain_hdl%daddr)
        data_ni_ = data_ni__tmp
      ENDIF

      IF (PRESENT(data_nj_)) THEN
        data_nj__tmp = cxios_is_defined_domain_data_nj &
      (domain_hdl%daddr)
        data_nj_ = data_nj__tmp
      ENDIF

      IF (PRESENT(dim_i_name_)) THEN
        dim_i_name__tmp = cxios_is_defined_domain_dim_i_name &
      (domain_hdl%daddr)
        dim_i_name_ = dim_i_name__tmp
      ENDIF

      IF (PRESENT(dim_j_name_)) THEN
        dim_j_name__tmp = cxios_is_defined_domain_dim_j_name &
      (domain_hdl%daddr)
        dim_j_name_ = dim_j_name__tmp
      ENDIF

      IF (PRESENT(domain_ref_)) THEN
        domain_ref__tmp = cxios_is_defined_domain_domain_ref &
      (domain_hdl%daddr)
        domain_ref_ = domain_ref__tmp
      ENDIF

      IF (PRESENT(i_index_)) THEN
        i_index__tmp = cxios_is_defined_domain_i_index &
      (domain_hdl%daddr)
        i_index_ = i_index__tmp
      ENDIF

      IF (PRESENT(ibegin_)) THEN
        ibegin__tmp = cxios_is_defined_domain_ibegin &
      (domain_hdl%daddr)
        ibegin_ = ibegin__tmp
      ENDIF

      IF (PRESENT(j_index_)) THEN
        j_index__tmp = cxios_is_defined_domain_j_index &
      (domain_hdl%daddr)
        j_index_ = j_index__tmp
      ENDIF

      IF (PRESENT(jbegin_)) THEN
        jbegin__tmp = cxios_is_defined_domain_jbegin &
      (domain_hdl%daddr)
        jbegin_ = jbegin__tmp
      ENDIF

      IF (PRESENT(lat_name_)) THEN
        lat_name__tmp = cxios_is_defined_domain_lat_name &
      (domain_hdl%daddr)
        lat_name_ = lat_name__tmp
      ENDIF

      IF (PRESENT(latvalue_1d_)) THEN
        latvalue_1d__tmp = cxios_is_defined_domain_latvalue_1d &
      (domain_hdl%daddr)
        latvalue_1d_ = latvalue_1d__tmp
      ENDIF

      IF (PRESENT(latvalue_2d_)) THEN
        latvalue_2d__tmp = cxios_is_defined_domain_latvalue_2d &
      (domain_hdl%daddr)
        latvalue_2d_ = latvalue_2d__tmp
      ENDIF

      IF (PRESENT(lon_name_)) THEN
        lon_name__tmp = cxios_is_defined_domain_lon_name &
      (domain_hdl%daddr)
        lon_name_ = lon_name__tmp
      ENDIF

      IF (PRESENT(long_name_)) THEN
        long_name__tmp = cxios_is_defined_domain_long_name &
      (domain_hdl%daddr)
        long_name_ = long_name__tmp
      ENDIF

      IF (PRESENT(lonvalue_1d_)) THEN
        lonvalue_1d__tmp = cxios_is_defined_domain_lonvalue_1d &
      (domain_hdl%daddr)
        lonvalue_1d_ = lonvalue_1d__tmp
      ENDIF

      IF (PRESENT(lonvalue_2d_)) THEN
        lonvalue_2d__tmp = cxios_is_defined_domain_lonvalue_2d &
      (domain_hdl%daddr)
        lonvalue_2d_ = lonvalue_2d__tmp
      ENDIF

      IF (PRESENT(mask_1d_)) THEN
        mask_1d__tmp = cxios_is_defined_domain_mask_1d &
      (domain_hdl%daddr)
        mask_1d_ = mask_1d__tmp
      ENDIF

      IF (PRESENT(mask_2d_)) THEN
        mask_2d__tmp = cxios_is_defined_domain_mask_2d &
      (domain_hdl%daddr)
        mask_2d_ = mask_2d__tmp
      ENDIF

      IF (PRESENT(name_)) THEN
        name__tmp = cxios_is_defined_domain_name &
      (domain_hdl%daddr)
        name_ = name__tmp
      ENDIF

      IF (PRESENT(ni_)) THEN
        ni__tmp = cxios_is_defined_domain_ni &
      (domain_hdl%daddr)
        ni_ = ni__tmp
      ENDIF

      IF (PRESENT(ni_glo_)) THEN
        ni_glo__tmp = cxios_is_defined_domain_ni_glo &
      (domain_hdl%daddr)
        ni_glo_ = ni_glo__tmp
      ENDIF

      IF (PRESENT(nj_)) THEN
        nj__tmp = cxios_is_defined_domain_nj &
      (domain_hdl%daddr)
        nj_ = nj__tmp
      ENDIF

      IF (PRESENT(nj_glo_)) THEN
        nj_glo__tmp = cxios_is_defined_domain_nj_glo &
      (domain_hdl%daddr)
        nj_glo_ = nj_glo__tmp
      ENDIF

      IF (PRESENT(ntiles_)) THEN
        ntiles__tmp = cxios_is_defined_domain_ntiles &
      (domain_hdl%daddr)
        ntiles_ = ntiles__tmp
      ENDIF

      IF (PRESENT(nvertex_)) THEN
        nvertex__tmp = cxios_is_defined_domain_nvertex &
      (domain_hdl%daddr)
        nvertex_ = nvertex__tmp
      ENDIF

      IF (PRESENT(prec_)) THEN
        prec__tmp = cxios_is_defined_domain_prec &
      (domain_hdl%daddr)
        prec_ = prec__tmp
      ENDIF

      IF (PRESENT(radius_)) THEN
        radius__tmp = cxios_is_defined_domain_radius &
      (domain_hdl%daddr)
        radius_ = radius__tmp
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        standard_name__tmp = cxios_is_defined_domain_standard_name &
      (domain_hdl%daddr)
        standard_name_ = standard_name__tmp
      ENDIF

      IF (PRESENT(tile_data_ibegin_)) THEN
        tile_data_ibegin__tmp = cxios_is_defined_domain_tile_data_ibegin &
      (domain_hdl%daddr)
        tile_data_ibegin_ = tile_data_ibegin__tmp
      ENDIF

      IF (PRESENT(tile_data_jbegin_)) THEN
        tile_data_jbegin__tmp = cxios_is_defined_domain_tile_data_jbegin &
      (domain_hdl%daddr)
        tile_data_jbegin_ = tile_data_jbegin__tmp
      ENDIF

      IF (PRESENT(tile_data_ni_)) THEN
        tile_data_ni__tmp = cxios_is_defined_domain_tile_data_ni &
      (domain_hdl%daddr)
        tile_data_ni_ = tile_data_ni__tmp
      ENDIF

      IF (PRESENT(tile_data_nj_)) THEN
        tile_data_nj__tmp = cxios_is_defined_domain_tile_data_nj &
      (domain_hdl%daddr)
        tile_data_nj_ = tile_data_nj__tmp
      ENDIF

      IF (PRESENT(tile_ibegin_)) THEN
        tile_ibegin__tmp = cxios_is_defined_domain_tile_ibegin &
      (domain_hdl%daddr)
        tile_ibegin_ = tile_ibegin__tmp
      ENDIF

      IF (PRESENT(tile_jbegin_)) THEN
        tile_jbegin__tmp = cxios_is_defined_domain_tile_jbegin &
      (domain_hdl%daddr)
        tile_jbegin_ = tile_jbegin__tmp
      ENDIF

      IF (PRESENT(tile_ni_)) THEN
        tile_ni__tmp = cxios_is_defined_domain_tile_ni &
      (domain_hdl%daddr)
        tile_ni_ = tile_ni__tmp
      ENDIF

      IF (PRESENT(tile_nj_)) THEN
        tile_nj__tmp = cxios_is_defined_domain_tile_nj &
      (domain_hdl%daddr)
        tile_nj_ = tile_nj__tmp
      ENDIF

      IF (PRESENT(type_)) THEN
        type__tmp = cxios_is_defined_domain_type &
      (domain_hdl%daddr)
        type_ = type__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_domain_attr_hdl_)

END MODULE idomain_attr
