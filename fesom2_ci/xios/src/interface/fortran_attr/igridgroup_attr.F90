! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE igridgroup_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE igrid
  USE gridgroup_interface_attr

CONTAINS

  SUBROUTINE xios(set_gridgroup_attr)  &
    ( gridgroup_id, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
    , mask_5d, mask_6d, mask_7d, name )

    IMPLICIT NONE
      TYPE(txios(gridgroup))  :: gridgroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::gridgroup_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: description
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_0d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_0d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_1d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_2d(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d_tmp(:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_3d(:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_3d_tmp(:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_4d(:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_4d_tmp(:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_5d(:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_5d_tmp(:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_6d(:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_6d_tmp(:,:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_7d(:,:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_7d_tmp(:,:,:,:,:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name

      CALL xios(get_gridgroup_handle) &
      (gridgroup_id,gridgroup_hdl)
      CALL xios(set_gridgroup_attr_hdl_)   &
      ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
      , mask_5d, mask_6d, mask_7d, name )

  END SUBROUTINE xios(set_gridgroup_attr)

  SUBROUTINE xios(set_gridgroup_attr_hdl)  &
    ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
    , mask_5d, mask_6d, mask_7d, name )

    IMPLICIT NONE
      TYPE(txios(gridgroup)) , INTENT(IN) :: gridgroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: description
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_0d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_0d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_1d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_2d(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d_tmp(:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_3d(:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_3d_tmp(:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_4d(:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_4d_tmp(:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_5d(:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_5d_tmp(:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_6d(:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_6d_tmp(:,:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_7d(:,:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_7d_tmp(:,:,:,:,:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name

      CALL xios(set_gridgroup_attr_hdl_)  &
      ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
      , mask_5d, mask_6d, mask_7d, name )

  END SUBROUTINE xios(set_gridgroup_attr_hdl)

  SUBROUTINE xios(set_gridgroup_attr_hdl_)   &
    ( gridgroup_hdl, comment_, description_, group_ref_, mask_0d_, mask_1d_, mask_2d_, mask_3d_  &
    , mask_4d_, mask_5d_, mask_6d_, mask_7d_, name_ )

    IMPLICIT NONE
      TYPE(txios(gridgroup)) , INTENT(IN) :: gridgroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: description_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref_
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_0d_(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_0d__tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_1d_(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d__tmp(:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_2d_(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d__tmp(:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_3d_(:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_3d__tmp(:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_4d_(:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_4d__tmp(:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_5d_(:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_5d__tmp(:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_6d_(:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_6d__tmp(:,:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(IN) :: mask_7d_(:,:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_7d__tmp(:,:,:,:,:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_

      IF (PRESENT(comment_)) THEN
        CALL cxios_set_gridgroup_comment &
      (gridgroup_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(description_)) THEN
        CALL cxios_set_gridgroup_description &
      (gridgroup_hdl%daddr, description_, len(description_))
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        CALL cxios_set_gridgroup_group_ref &
      (gridgroup_hdl%daddr, group_ref_, len(group_ref_))
      ENDIF

      IF (PRESENT(mask_0d_)) THEN
        ALLOCATE(mask_0d__tmp(SIZE(mask_0d_,1)))
        mask_0d__tmp = mask_0d_
        CALL cxios_set_gridgroup_mask_0d &
      (gridgroup_hdl%daddr, mask_0d__tmp, SHAPE(mask_0d_))
      ENDIF

      IF (PRESENT(mask_1d_)) THEN
        ALLOCATE(mask_1d__tmp(SIZE(mask_1d_,1)))
        mask_1d__tmp = mask_1d_
        CALL cxios_set_gridgroup_mask_1d &
      (gridgroup_hdl%daddr, mask_1d__tmp, SHAPE(mask_1d_))
      ENDIF

      IF (PRESENT(mask_2d_)) THEN
        ALLOCATE(mask_2d__tmp(SIZE(mask_2d_,1), SIZE(mask_2d_,2)))
        mask_2d__tmp = mask_2d_
        CALL cxios_set_gridgroup_mask_2d &
      (gridgroup_hdl%daddr, mask_2d__tmp, SHAPE(mask_2d_))
      ENDIF

      IF (PRESENT(mask_3d_)) THEN
        ALLOCATE(mask_3d__tmp(SIZE(mask_3d_,1), SIZE(mask_3d_,2), SIZE(mask_3d_,3)))
        mask_3d__tmp = mask_3d_
        CALL cxios_set_gridgroup_mask_3d &
      (gridgroup_hdl%daddr, mask_3d__tmp, SHAPE(mask_3d_))
      ENDIF

      IF (PRESENT(mask_4d_)) THEN
        ALLOCATE(mask_4d__tmp(SIZE(mask_4d_,1), SIZE(mask_4d_,2), SIZE(mask_4d_,3), &
       SIZE(mask_4d_,4)))
        mask_4d__tmp = mask_4d_
        CALL cxios_set_gridgroup_mask_4d &
      (gridgroup_hdl%daddr, mask_4d__tmp, SHAPE(mask_4d_))
      ENDIF

      IF (PRESENT(mask_5d_)) THEN
        ALLOCATE(mask_5d__tmp(SIZE(mask_5d_,1), SIZE(mask_5d_,2), SIZE(mask_5d_,3), &
       SIZE(mask_5d_,4), SIZE(mask_5d_,5)))
        mask_5d__tmp = mask_5d_
        CALL cxios_set_gridgroup_mask_5d &
      (gridgroup_hdl%daddr, mask_5d__tmp, SHAPE(mask_5d_))
      ENDIF

      IF (PRESENT(mask_6d_)) THEN
        ALLOCATE(mask_6d__tmp(SIZE(mask_6d_,1), SIZE(mask_6d_,2), SIZE(mask_6d_,3), &
       SIZE(mask_6d_,4), SIZE(mask_6d_,5), SIZE(mask_6d_,6)))
        mask_6d__tmp = mask_6d_
        CALL cxios_set_gridgroup_mask_6d &
      (gridgroup_hdl%daddr, mask_6d__tmp, SHAPE(mask_6d_))
      ENDIF

      IF (PRESENT(mask_7d_)) THEN
        ALLOCATE(mask_7d__tmp(SIZE(mask_7d_,1), SIZE(mask_7d_,2), SIZE(mask_7d_,3), &
       SIZE(mask_7d_,4), SIZE(mask_7d_,5), SIZE(mask_7d_,6), &
       SIZE(mask_7d_,7)))
        mask_7d__tmp = mask_7d_
        CALL cxios_set_gridgroup_mask_7d &
      (gridgroup_hdl%daddr, mask_7d__tmp, SHAPE(mask_7d_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_set_gridgroup_name &
      (gridgroup_hdl%daddr, name_, len(name_))
      ENDIF

  END SUBROUTINE xios(set_gridgroup_attr_hdl_)

  SUBROUTINE xios(get_gridgroup_attr)  &
    ( gridgroup_id, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
    , mask_5d, mask_6d, mask_7d, name )

    IMPLICIT NONE
      TYPE(txios(gridgroup))  :: gridgroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::gridgroup_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: description
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_0d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_0d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_1d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_2d(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d_tmp(:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_3d(:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_3d_tmp(:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_4d(:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_4d_tmp(:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_5d(:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_5d_tmp(:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_6d(:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_6d_tmp(:,:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_7d(:,:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_7d_tmp(:,:,:,:,:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name

      CALL xios(get_gridgroup_handle) &
      (gridgroup_id,gridgroup_hdl)
      CALL xios(get_gridgroup_attr_hdl_)   &
      ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
      , mask_5d, mask_6d, mask_7d, name )

  END SUBROUTINE xios(get_gridgroup_attr)

  SUBROUTINE xios(get_gridgroup_attr_hdl)  &
    ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
    , mask_5d, mask_6d, mask_7d, name )

    IMPLICIT NONE
      TYPE(txios(gridgroup)) , INTENT(IN) :: gridgroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: description
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_0d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_0d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_1d(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d_tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_2d(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d_tmp(:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_3d(:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_3d_tmp(:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_4d(:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_4d_tmp(:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_5d(:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_5d_tmp(:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_6d(:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_6d_tmp(:,:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_7d(:,:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_7d_tmp(:,:,:,:,:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name

      CALL xios(get_gridgroup_attr_hdl_)  &
      ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
      , mask_5d, mask_6d, mask_7d, name )

  END SUBROUTINE xios(get_gridgroup_attr_hdl)

  SUBROUTINE xios(get_gridgroup_attr_hdl_)   &
    ( gridgroup_hdl, comment_, description_, group_ref_, mask_0d_, mask_1d_, mask_2d_, mask_3d_  &
    , mask_4d_, mask_5d_, mask_6d_, mask_7d_, name_ )

    IMPLICIT NONE
      TYPE(txios(gridgroup)) , INTENT(IN) :: gridgroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: description_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref_
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_0d_(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_0d__tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_1d_(:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_1d__tmp(:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_2d_(:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_2d__tmp(:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_3d_(:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_3d__tmp(:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_4d_(:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_4d__tmp(:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_5d_(:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_5d__tmp(:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_6d_(:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_6d__tmp(:,:,:,:,:,:)
      LOGICAL  , OPTIONAL, INTENT(OUT) :: mask_7d_(:,:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL) , ALLOCATABLE :: mask_7d__tmp(:,:,:,:,:,:,:)
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_

      IF (PRESENT(comment_)) THEN
        CALL cxios_get_gridgroup_comment &
      (gridgroup_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(description_)) THEN
        CALL cxios_get_gridgroup_description &
      (gridgroup_hdl%daddr, description_, len(description_))
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        CALL cxios_get_gridgroup_group_ref &
      (gridgroup_hdl%daddr, group_ref_, len(group_ref_))
      ENDIF

      IF (PRESENT(mask_0d_)) THEN
        ALLOCATE(mask_0d__tmp(SIZE(mask_0d_,1)))
        CALL cxios_get_gridgroup_mask_0d &
      (gridgroup_hdl%daddr, mask_0d__tmp, SHAPE(mask_0d_))
        mask_0d_ = mask_0d__tmp
      ENDIF

      IF (PRESENT(mask_1d_)) THEN
        ALLOCATE(mask_1d__tmp(SIZE(mask_1d_,1)))
        CALL cxios_get_gridgroup_mask_1d &
      (gridgroup_hdl%daddr, mask_1d__tmp, SHAPE(mask_1d_))
        mask_1d_ = mask_1d__tmp
      ENDIF

      IF (PRESENT(mask_2d_)) THEN
        ALLOCATE(mask_2d__tmp(SIZE(mask_2d_,1), SIZE(mask_2d_,2)))
        CALL cxios_get_gridgroup_mask_2d &
      (gridgroup_hdl%daddr, mask_2d__tmp, SHAPE(mask_2d_))
        mask_2d_ = mask_2d__tmp
      ENDIF

      IF (PRESENT(mask_3d_)) THEN
        ALLOCATE(mask_3d__tmp(SIZE(mask_3d_,1), SIZE(mask_3d_,2), SIZE(mask_3d_,3)))
        CALL cxios_get_gridgroup_mask_3d &
      (gridgroup_hdl%daddr, mask_3d__tmp, SHAPE(mask_3d_))
        mask_3d_ = mask_3d__tmp
      ENDIF

      IF (PRESENT(mask_4d_)) THEN
        ALLOCATE(mask_4d__tmp(SIZE(mask_4d_,1), SIZE(mask_4d_,2), SIZE(mask_4d_,3), &
       SIZE(mask_4d_,4)))
        CALL cxios_get_gridgroup_mask_4d &
      (gridgroup_hdl%daddr, mask_4d__tmp, SHAPE(mask_4d_))
        mask_4d_ = mask_4d__tmp
      ENDIF

      IF (PRESENT(mask_5d_)) THEN
        ALLOCATE(mask_5d__tmp(SIZE(mask_5d_,1), SIZE(mask_5d_,2), SIZE(mask_5d_,3), &
       SIZE(mask_5d_,4), SIZE(mask_5d_,5)))
        CALL cxios_get_gridgroup_mask_5d &
      (gridgroup_hdl%daddr, mask_5d__tmp, SHAPE(mask_5d_))
        mask_5d_ = mask_5d__tmp
      ENDIF

      IF (PRESENT(mask_6d_)) THEN
        ALLOCATE(mask_6d__tmp(SIZE(mask_6d_,1), SIZE(mask_6d_,2), SIZE(mask_6d_,3), &
       SIZE(mask_6d_,4), SIZE(mask_6d_,5), SIZE(mask_6d_,6)))
        CALL cxios_get_gridgroup_mask_6d &
      (gridgroup_hdl%daddr, mask_6d__tmp, SHAPE(mask_6d_))
        mask_6d_ = mask_6d__tmp
      ENDIF

      IF (PRESENT(mask_7d_)) THEN
        ALLOCATE(mask_7d__tmp(SIZE(mask_7d_,1), SIZE(mask_7d_,2), SIZE(mask_7d_,3), &
       SIZE(mask_7d_,4), SIZE(mask_7d_,5), SIZE(mask_7d_,6), &
       SIZE(mask_7d_,7)))
        CALL cxios_get_gridgroup_mask_7d &
      (gridgroup_hdl%daddr, mask_7d__tmp, SHAPE(mask_7d_))
        mask_7d_ = mask_7d__tmp
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_get_gridgroup_name &
      (gridgroup_hdl%daddr, name_, len(name_))
      ENDIF

  END SUBROUTINE xios(get_gridgroup_attr_hdl_)

  SUBROUTINE xios(is_defined_gridgroup_attr)  &
    ( gridgroup_id, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
    , mask_5d, mask_6d, mask_7d, name )

    IMPLICIT NONE
      TYPE(txios(gridgroup))  :: gridgroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::gridgroup_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: description
      LOGICAL(KIND=C_BOOL) :: description_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL(KIND=C_BOOL) :: group_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_0d
      LOGICAL(KIND=C_BOOL) :: mask_0d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_1d
      LOGICAL(KIND=C_BOOL) :: mask_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_2d
      LOGICAL(KIND=C_BOOL) :: mask_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_3d
      LOGICAL(KIND=C_BOOL) :: mask_3d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_4d
      LOGICAL(KIND=C_BOOL) :: mask_4d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_5d
      LOGICAL(KIND=C_BOOL) :: mask_5d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_6d
      LOGICAL(KIND=C_BOOL) :: mask_6d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_7d
      LOGICAL(KIND=C_BOOL) :: mask_7d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp

      CALL xios(get_gridgroup_handle) &
      (gridgroup_id,gridgroup_hdl)
      CALL xios(is_defined_gridgroup_attr_hdl_)   &
      ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
      , mask_5d, mask_6d, mask_7d, name )

  END SUBROUTINE xios(is_defined_gridgroup_attr)

  SUBROUTINE xios(is_defined_gridgroup_attr_hdl)  &
    ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
    , mask_5d, mask_6d, mask_7d, name )

    IMPLICIT NONE
      TYPE(txios(gridgroup)) , INTENT(IN) :: gridgroup_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: description
      LOGICAL(KIND=C_BOOL) :: description_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL(KIND=C_BOOL) :: group_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_0d
      LOGICAL(KIND=C_BOOL) :: mask_0d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_1d
      LOGICAL(KIND=C_BOOL) :: mask_1d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_2d
      LOGICAL(KIND=C_BOOL) :: mask_2d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_3d
      LOGICAL(KIND=C_BOOL) :: mask_3d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_4d
      LOGICAL(KIND=C_BOOL) :: mask_4d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_5d
      LOGICAL(KIND=C_BOOL) :: mask_5d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_6d
      LOGICAL(KIND=C_BOOL) :: mask_6d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_7d
      LOGICAL(KIND=C_BOOL) :: mask_7d_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp

      CALL xios(is_defined_gridgroup_attr_hdl_)  &
      ( gridgroup_hdl, comment, description, group_ref, mask_0d, mask_1d, mask_2d, mask_3d, mask_4d  &
      , mask_5d, mask_6d, mask_7d, name )

  END SUBROUTINE xios(is_defined_gridgroup_attr_hdl)

  SUBROUTINE xios(is_defined_gridgroup_attr_hdl_)   &
    ( gridgroup_hdl, comment_, description_, group_ref_, mask_0d_, mask_1d_, mask_2d_, mask_3d_  &
    , mask_4d_, mask_5d_, mask_6d_, mask_7d_, name_ )

    IMPLICIT NONE
      TYPE(txios(gridgroup)) , INTENT(IN) :: gridgroup_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment_
      LOGICAL(KIND=C_BOOL) :: comment__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: description_
      LOGICAL(KIND=C_BOOL) :: description__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref_
      LOGICAL(KIND=C_BOOL) :: group_ref__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_0d_
      LOGICAL(KIND=C_BOOL) :: mask_0d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_1d_
      LOGICAL(KIND=C_BOOL) :: mask_1d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_2d_
      LOGICAL(KIND=C_BOOL) :: mask_2d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_3d_
      LOGICAL(KIND=C_BOOL) :: mask_3d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_4d_
      LOGICAL(KIND=C_BOOL) :: mask_4d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_5d_
      LOGICAL(KIND=C_BOOL) :: mask_5d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_6d_
      LOGICAL(KIND=C_BOOL) :: mask_6d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mask_7d_
      LOGICAL(KIND=C_BOOL) :: mask_7d__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_
      LOGICAL(KIND=C_BOOL) :: name__tmp

      IF (PRESENT(comment_)) THEN
        comment__tmp = cxios_is_defined_gridgroup_comment &
      (gridgroup_hdl%daddr)
        comment_ = comment__tmp
      ENDIF

      IF (PRESENT(description_)) THEN
        description__tmp = cxios_is_defined_gridgroup_description &
      (gridgroup_hdl%daddr)
        description_ = description__tmp
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        group_ref__tmp = cxios_is_defined_gridgroup_group_ref &
      (gridgroup_hdl%daddr)
        group_ref_ = group_ref__tmp
      ENDIF

      IF (PRESENT(mask_0d_)) THEN
        mask_0d__tmp = cxios_is_defined_gridgroup_mask_0d &
      (gridgroup_hdl%daddr)
        mask_0d_ = mask_0d__tmp
      ENDIF

      IF (PRESENT(mask_1d_)) THEN
        mask_1d__tmp = cxios_is_defined_gridgroup_mask_1d &
      (gridgroup_hdl%daddr)
        mask_1d_ = mask_1d__tmp
      ENDIF

      IF (PRESENT(mask_2d_)) THEN
        mask_2d__tmp = cxios_is_defined_gridgroup_mask_2d &
      (gridgroup_hdl%daddr)
        mask_2d_ = mask_2d__tmp
      ENDIF

      IF (PRESENT(mask_3d_)) THEN
        mask_3d__tmp = cxios_is_defined_gridgroup_mask_3d &
      (gridgroup_hdl%daddr)
        mask_3d_ = mask_3d__tmp
      ENDIF

      IF (PRESENT(mask_4d_)) THEN
        mask_4d__tmp = cxios_is_defined_gridgroup_mask_4d &
      (gridgroup_hdl%daddr)
        mask_4d_ = mask_4d__tmp
      ENDIF

      IF (PRESENT(mask_5d_)) THEN
        mask_5d__tmp = cxios_is_defined_gridgroup_mask_5d &
      (gridgroup_hdl%daddr)
        mask_5d_ = mask_5d__tmp
      ENDIF

      IF (PRESENT(mask_6d_)) THEN
        mask_6d__tmp = cxios_is_defined_gridgroup_mask_6d &
      (gridgroup_hdl%daddr)
        mask_6d_ = mask_6d__tmp
      ENDIF

      IF (PRESENT(mask_7d_)) THEN
        mask_7d__tmp = cxios_is_defined_gridgroup_mask_7d &
      (gridgroup_hdl%daddr)
        mask_7d_ = mask_7d__tmp
      ENDIF

      IF (PRESENT(name_)) THEN
        name__tmp = cxios_is_defined_gridgroup_name &
      (gridgroup_hdl%daddr)
        name_ = name__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_gridgroup_attr_hdl_)

END MODULE igridgroup_attr
