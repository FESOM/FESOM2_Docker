! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE izoom_axis_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE izoom_axis
  USE zoom_axis_interface_attr

CONTAINS

  SUBROUTINE xios(set_zoom_axis_attr)  &
    ( zoom_axis_id, begin, index, n )

    IMPLICIT NONE
      TYPE(txios(zoom_axis))  :: zoom_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::zoom_axis_id
      INTEGER  , OPTIONAL, INTENT(IN) :: begin
      INTEGER  , OPTIONAL, INTENT(IN) :: index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: n

      CALL xios(get_zoom_axis_handle) &
      (zoom_axis_id,zoom_axis_hdl)
      CALL xios(set_zoom_axis_attr_hdl_)   &
      ( zoom_axis_hdl, begin, index, n )

  END SUBROUTINE xios(set_zoom_axis_attr)

  SUBROUTINE xios(set_zoom_axis_attr_hdl)  &
    ( zoom_axis_hdl, begin, index, n )

    IMPLICIT NONE
      TYPE(txios(zoom_axis)) , INTENT(IN) :: zoom_axis_hdl
      INTEGER  , OPTIONAL, INTENT(IN) :: begin
      INTEGER  , OPTIONAL, INTENT(IN) :: index(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: n

      CALL xios(set_zoom_axis_attr_hdl_)  &
      ( zoom_axis_hdl, begin, index, n )

  END SUBROUTINE xios(set_zoom_axis_attr_hdl)

  SUBROUTINE xios(set_zoom_axis_attr_hdl_)   &
    ( zoom_axis_hdl, begin_, index_, n_ )

    IMPLICIT NONE
      TYPE(txios(zoom_axis)) , INTENT(IN) :: zoom_axis_hdl
      INTEGER  , OPTIONAL, INTENT(IN) :: begin_
      INTEGER  , OPTIONAL, INTENT(IN) :: index_(:)
      INTEGER  , OPTIONAL, INTENT(IN) :: n_

      IF (PRESENT(begin_)) THEN
        CALL cxios_set_zoom_axis_begin &
      (zoom_axis_hdl%daddr, begin_)
      ENDIF

      IF (PRESENT(index_)) THEN
        CALL cxios_set_zoom_axis_index &
      (zoom_axis_hdl%daddr, index_, SHAPE(index_))
      ENDIF

      IF (PRESENT(n_)) THEN
        CALL cxios_set_zoom_axis_n &
      (zoom_axis_hdl%daddr, n_)
      ENDIF

  END SUBROUTINE xios(set_zoom_axis_attr_hdl_)

  SUBROUTINE xios(get_zoom_axis_attr)  &
    ( zoom_axis_id, begin, index, n )

    IMPLICIT NONE
      TYPE(txios(zoom_axis))  :: zoom_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::zoom_axis_id
      INTEGER  , OPTIONAL, INTENT(OUT) :: begin
      INTEGER  , OPTIONAL, INTENT(OUT) :: index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: n

      CALL xios(get_zoom_axis_handle) &
      (zoom_axis_id,zoom_axis_hdl)
      CALL xios(get_zoom_axis_attr_hdl_)   &
      ( zoom_axis_hdl, begin, index, n )

  END SUBROUTINE xios(get_zoom_axis_attr)

  SUBROUTINE xios(get_zoom_axis_attr_hdl)  &
    ( zoom_axis_hdl, begin, index, n )

    IMPLICIT NONE
      TYPE(txios(zoom_axis)) , INTENT(IN) :: zoom_axis_hdl
      INTEGER  , OPTIONAL, INTENT(OUT) :: begin
      INTEGER  , OPTIONAL, INTENT(OUT) :: index(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: n

      CALL xios(get_zoom_axis_attr_hdl_)  &
      ( zoom_axis_hdl, begin, index, n )

  END SUBROUTINE xios(get_zoom_axis_attr_hdl)

  SUBROUTINE xios(get_zoom_axis_attr_hdl_)   &
    ( zoom_axis_hdl, begin_, index_, n_ )

    IMPLICIT NONE
      TYPE(txios(zoom_axis)) , INTENT(IN) :: zoom_axis_hdl
      INTEGER  , OPTIONAL, INTENT(OUT) :: begin_
      INTEGER  , OPTIONAL, INTENT(OUT) :: index_(:)
      INTEGER  , OPTIONAL, INTENT(OUT) :: n_

      IF (PRESENT(begin_)) THEN
        CALL cxios_get_zoom_axis_begin &
      (zoom_axis_hdl%daddr, begin_)
      ENDIF

      IF (PRESENT(index_)) THEN
        CALL cxios_get_zoom_axis_index &
      (zoom_axis_hdl%daddr, index_, SHAPE(index_))
      ENDIF

      IF (PRESENT(n_)) THEN
        CALL cxios_get_zoom_axis_n &
      (zoom_axis_hdl%daddr, n_)
      ENDIF

  END SUBROUTINE xios(get_zoom_axis_attr_hdl_)

  SUBROUTINE xios(is_defined_zoom_axis_attr)  &
    ( zoom_axis_id, begin, index, n )

    IMPLICIT NONE
      TYPE(txios(zoom_axis))  :: zoom_axis_hdl
      CHARACTER(LEN=*), INTENT(IN) ::zoom_axis_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: begin
      LOGICAL(KIND=C_BOOL) :: begin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: index
      LOGICAL(KIND=C_BOOL) :: index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: n
      LOGICAL(KIND=C_BOOL) :: n_tmp

      CALL xios(get_zoom_axis_handle) &
      (zoom_axis_id,zoom_axis_hdl)
      CALL xios(is_defined_zoom_axis_attr_hdl_)   &
      ( zoom_axis_hdl, begin, index, n )

  END SUBROUTINE xios(is_defined_zoom_axis_attr)

  SUBROUTINE xios(is_defined_zoom_axis_attr_hdl)  &
    ( zoom_axis_hdl, begin, index, n )

    IMPLICIT NONE
      TYPE(txios(zoom_axis)) , INTENT(IN) :: zoom_axis_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: begin
      LOGICAL(KIND=C_BOOL) :: begin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: index
      LOGICAL(KIND=C_BOOL) :: index_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: n
      LOGICAL(KIND=C_BOOL) :: n_tmp

      CALL xios(is_defined_zoom_axis_attr_hdl_)  &
      ( zoom_axis_hdl, begin, index, n )

  END SUBROUTINE xios(is_defined_zoom_axis_attr_hdl)

  SUBROUTINE xios(is_defined_zoom_axis_attr_hdl_)   &
    ( zoom_axis_hdl, begin_, index_, n_ )

    IMPLICIT NONE
      TYPE(txios(zoom_axis)) , INTENT(IN) :: zoom_axis_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: begin_
      LOGICAL(KIND=C_BOOL) :: begin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: index_
      LOGICAL(KIND=C_BOOL) :: index__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: n_
      LOGICAL(KIND=C_BOOL) :: n__tmp

      IF (PRESENT(begin_)) THEN
        begin__tmp = cxios_is_defined_zoom_axis_begin &
      (zoom_axis_hdl%daddr)
        begin_ = begin__tmp
      ENDIF

      IF (PRESENT(index_)) THEN
        index__tmp = cxios_is_defined_zoom_axis_index &
      (zoom_axis_hdl%daddr)
        index_ = index__tmp
      ENDIF

      IF (PRESENT(n_)) THEN
        n__tmp = cxios_is_defined_zoom_axis_n &
      (zoom_axis_hdl%daddr)
        n_ = n__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_zoom_axis_attr_hdl_)

END MODULE izoom_axis_attr
