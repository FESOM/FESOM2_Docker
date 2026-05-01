! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE gridgroup_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_gridgroup_comment(gridgroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_gridgroup_comment

    SUBROUTINE cxios_get_gridgroup_comment(gridgroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_gridgroup_comment

    FUNCTION cxios_is_defined_gridgroup_comment(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_comment


    SUBROUTINE cxios_set_gridgroup_description(gridgroup_hdl, description, description_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: description
      INTEGER  (kind = C_INT)     , VALUE        :: description_size
    END SUBROUTINE cxios_set_gridgroup_description

    SUBROUTINE cxios_get_gridgroup_description(gridgroup_hdl, description, description_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: description
      INTEGER  (kind = C_INT)     , VALUE        :: description_size
    END SUBROUTINE cxios_get_gridgroup_description

    FUNCTION cxios_is_defined_gridgroup_description(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_description
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_description


    SUBROUTINE cxios_set_gridgroup_group_ref(gridgroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_set_gridgroup_group_ref

    SUBROUTINE cxios_get_gridgroup_group_ref(gridgroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_get_gridgroup_group_ref

    FUNCTION cxios_is_defined_gridgroup_group_ref(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_group_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_group_ref


    SUBROUTINE cxios_set_gridgroup_mask_0d(gridgroup_hdl, mask_0d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_0d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_gridgroup_mask_0d

    SUBROUTINE cxios_get_gridgroup_mask_0d(gridgroup_hdl, mask_0d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_0d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_gridgroup_mask_0d

    FUNCTION cxios_is_defined_gridgroup_mask_0d(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_mask_0d
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_mask_0d


    SUBROUTINE cxios_set_gridgroup_mask_1d(gridgroup_hdl, mask_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_gridgroup_mask_1d

    SUBROUTINE cxios_get_gridgroup_mask_1d(gridgroup_hdl, mask_1d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_1d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_gridgroup_mask_1d

    FUNCTION cxios_is_defined_gridgroup_mask_1d(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_mask_1d
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_mask_1d


    SUBROUTINE cxios_set_gridgroup_mask_2d(gridgroup_hdl, mask_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_gridgroup_mask_2d

    SUBROUTINE cxios_get_gridgroup_mask_2d(gridgroup_hdl, mask_2d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_2d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_gridgroup_mask_2d

    FUNCTION cxios_is_defined_gridgroup_mask_2d(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_mask_2d
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_mask_2d


    SUBROUTINE cxios_set_gridgroup_mask_3d(gridgroup_hdl, mask_3d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_3d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_gridgroup_mask_3d

    SUBROUTINE cxios_get_gridgroup_mask_3d(gridgroup_hdl, mask_3d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_3d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_gridgroup_mask_3d

    FUNCTION cxios_is_defined_gridgroup_mask_3d(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_mask_3d
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_mask_3d


    SUBROUTINE cxios_set_gridgroup_mask_4d(gridgroup_hdl, mask_4d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_4d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_gridgroup_mask_4d

    SUBROUTINE cxios_get_gridgroup_mask_4d(gridgroup_hdl, mask_4d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_4d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_gridgroup_mask_4d

    FUNCTION cxios_is_defined_gridgroup_mask_4d(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_mask_4d
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_mask_4d


    SUBROUTINE cxios_set_gridgroup_mask_5d(gridgroup_hdl, mask_5d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_5d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_gridgroup_mask_5d

    SUBROUTINE cxios_get_gridgroup_mask_5d(gridgroup_hdl, mask_5d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_5d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_gridgroup_mask_5d

    FUNCTION cxios_is_defined_gridgroup_mask_5d(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_mask_5d
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_mask_5d


    SUBROUTINE cxios_set_gridgroup_mask_6d(gridgroup_hdl, mask_6d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_6d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_gridgroup_mask_6d

    SUBROUTINE cxios_get_gridgroup_mask_6d(gridgroup_hdl, mask_6d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_6d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_gridgroup_mask_6d

    FUNCTION cxios_is_defined_gridgroup_mask_6d(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_mask_6d
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_mask_6d


    SUBROUTINE cxios_set_gridgroup_mask_7d(gridgroup_hdl, mask_7d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_7d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_set_gridgroup_mask_7d

    SUBROUTINE cxios_get_gridgroup_mask_7d(gridgroup_hdl, mask_7d, extent) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE       :: gridgroup_hdl
      LOGICAL (KIND=C_BOOL)     , DIMENSION(*) :: mask_7d
      INTEGER (kind = C_INT), DIMENSION(*)     :: extent
    END SUBROUTINE cxios_get_gridgroup_mask_7d

    FUNCTION cxios_is_defined_gridgroup_mask_7d(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_mask_7d
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_mask_7d


    SUBROUTINE cxios_set_gridgroup_name(gridgroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_gridgroup_name

    SUBROUTINE cxios_get_gridgroup_name(gridgroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_gridgroup_name

    FUNCTION cxios_is_defined_gridgroup_name(gridgroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_gridgroup_name
      INTEGER (kind = C_INTPTR_T), VALUE :: gridgroup_hdl
    END FUNCTION cxios_is_defined_gridgroup_name

  END INTERFACE

END MODULE gridgroup_interface_attr
