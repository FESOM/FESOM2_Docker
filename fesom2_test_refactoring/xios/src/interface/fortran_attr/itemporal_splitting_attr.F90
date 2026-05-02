! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE itemporal_splitting_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE itemporal_splitting
  USE temporal_splitting_interface_attr

CONTAINS

  SUBROUTINE xios(set_temporal_splitting_attr)  &
    ( temporal_splitting_id )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting))  :: temporal_splitting_hdl
      CHARACTER(LEN=*), INTENT(IN) ::temporal_splitting_id

      CALL xios(get_temporal_splitting_handle) &
      (temporal_splitting_id,temporal_splitting_hdl)
      CALL xios(set_temporal_splitting_attr_hdl_)   &
      ( temporal_splitting_hdl )

  END SUBROUTINE xios(set_temporal_splitting_attr)

  SUBROUTINE xios(set_temporal_splitting_attr_hdl)  &
    ( temporal_splitting_hdl )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting)) , INTENT(IN) :: temporal_splitting_hdl

      CALL xios(set_temporal_splitting_attr_hdl_)  &
      ( temporal_splitting_hdl )

  END SUBROUTINE xios(set_temporal_splitting_attr_hdl)

  SUBROUTINE xios(set_temporal_splitting_attr_hdl_)   &
    ( temporal_splitting_hdl )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting)) , INTENT(IN) :: temporal_splitting_hdl

  END SUBROUTINE xios(set_temporal_splitting_attr_hdl_)

  SUBROUTINE xios(get_temporal_splitting_attr)  &
    ( temporal_splitting_id )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting))  :: temporal_splitting_hdl
      CHARACTER(LEN=*), INTENT(IN) ::temporal_splitting_id

      CALL xios(get_temporal_splitting_handle) &
      (temporal_splitting_id,temporal_splitting_hdl)
      CALL xios(get_temporal_splitting_attr_hdl_)   &
      ( temporal_splitting_hdl )

  END SUBROUTINE xios(get_temporal_splitting_attr)

  SUBROUTINE xios(get_temporal_splitting_attr_hdl)  &
    ( temporal_splitting_hdl )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting)) , INTENT(IN) :: temporal_splitting_hdl

      CALL xios(get_temporal_splitting_attr_hdl_)  &
      ( temporal_splitting_hdl )

  END SUBROUTINE xios(get_temporal_splitting_attr_hdl)

  SUBROUTINE xios(get_temporal_splitting_attr_hdl_)   &
    ( temporal_splitting_hdl )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting)) , INTENT(IN) :: temporal_splitting_hdl

  END SUBROUTINE xios(get_temporal_splitting_attr_hdl_)

  SUBROUTINE xios(is_defined_temporal_splitting_attr)  &
    ( temporal_splitting_id )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting))  :: temporal_splitting_hdl
      CHARACTER(LEN=*), INTENT(IN) ::temporal_splitting_id

      CALL xios(get_temporal_splitting_handle) &
      (temporal_splitting_id,temporal_splitting_hdl)
      CALL xios(is_defined_temporal_splitting_attr_hdl_)   &
      ( temporal_splitting_hdl )

  END SUBROUTINE xios(is_defined_temporal_splitting_attr)

  SUBROUTINE xios(is_defined_temporal_splitting_attr_hdl)  &
    ( temporal_splitting_hdl )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting)) , INTENT(IN) :: temporal_splitting_hdl

      CALL xios(is_defined_temporal_splitting_attr_hdl_)  &
      ( temporal_splitting_hdl )

  END SUBROUTINE xios(is_defined_temporal_splitting_attr_hdl)

  SUBROUTINE xios(is_defined_temporal_splitting_attr_hdl_)   &
    ( temporal_splitting_hdl )

    IMPLICIT NONE
      TYPE(txios(temporal_splitting)) , INTENT(IN) :: temporal_splitting_hdl

  END SUBROUTINE xios(is_defined_temporal_splitting_attr_hdl_)

END MODULE itemporal_splitting_attr
