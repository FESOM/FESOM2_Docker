! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE icontext_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE icontext
  USE context_interface_attr

CONTAINS

  SUBROUTINE xios(set_context_attr)  &
    ( context_id, output_dir )

    IMPLICIT NONE
      TYPE(txios(context))  :: context_hdl
      CHARACTER(LEN=*), INTENT(IN) ::context_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: output_dir

      CALL xios(get_context_handle) &
      (context_id,context_hdl)
      CALL xios(set_context_attr_hdl_)   &
      ( context_hdl, output_dir )

  END SUBROUTINE xios(set_context_attr)

  SUBROUTINE xios(set_context_attr_hdl)  &
    ( context_hdl, output_dir )

    IMPLICIT NONE
      TYPE(txios(context)) , INTENT(IN) :: context_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: output_dir

      CALL xios(set_context_attr_hdl_)  &
      ( context_hdl, output_dir )

  END SUBROUTINE xios(set_context_attr_hdl)

  SUBROUTINE xios(set_context_attr_hdl_)   &
    ( context_hdl, output_dir_ )

    IMPLICIT NONE
      TYPE(txios(context)) , INTENT(IN) :: context_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: output_dir_

      IF (PRESENT(output_dir_)) THEN
        CALL cxios_set_context_output_dir &
      (context_hdl%daddr, output_dir_, len(output_dir_))
      ENDIF

  END SUBROUTINE xios(set_context_attr_hdl_)

  SUBROUTINE xios(get_context_attr)  &
    ( context_id, output_dir )

    IMPLICIT NONE
      TYPE(txios(context))  :: context_hdl
      CHARACTER(LEN=*), INTENT(IN) ::context_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: output_dir

      CALL xios(get_context_handle) &
      (context_id,context_hdl)
      CALL xios(get_context_attr_hdl_)   &
      ( context_hdl, output_dir )

  END SUBROUTINE xios(get_context_attr)

  SUBROUTINE xios(get_context_attr_hdl)  &
    ( context_hdl, output_dir )

    IMPLICIT NONE
      TYPE(txios(context)) , INTENT(IN) :: context_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: output_dir

      CALL xios(get_context_attr_hdl_)  &
      ( context_hdl, output_dir )

  END SUBROUTINE xios(get_context_attr_hdl)

  SUBROUTINE xios(get_context_attr_hdl_)   &
    ( context_hdl, output_dir_ )

    IMPLICIT NONE
      TYPE(txios(context)) , INTENT(IN) :: context_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: output_dir_

      IF (PRESENT(output_dir_)) THEN
        CALL cxios_get_context_output_dir &
      (context_hdl%daddr, output_dir_, len(output_dir_))
      ENDIF

  END SUBROUTINE xios(get_context_attr_hdl_)

  SUBROUTINE xios(is_defined_context_attr)  &
    ( context_id, output_dir )

    IMPLICIT NONE
      TYPE(txios(context))  :: context_hdl
      CHARACTER(LEN=*), INTENT(IN) ::context_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_dir
      LOGICAL(KIND=C_BOOL) :: output_dir_tmp

      CALL xios(get_context_handle) &
      (context_id,context_hdl)
      CALL xios(is_defined_context_attr_hdl_)   &
      ( context_hdl, output_dir )

  END SUBROUTINE xios(is_defined_context_attr)

  SUBROUTINE xios(is_defined_context_attr_hdl)  &
    ( context_hdl, output_dir )

    IMPLICIT NONE
      TYPE(txios(context)) , INTENT(IN) :: context_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_dir
      LOGICAL(KIND=C_BOOL) :: output_dir_tmp

      CALL xios(is_defined_context_attr_hdl_)  &
      ( context_hdl, output_dir )

  END SUBROUTINE xios(is_defined_context_attr_hdl)

  SUBROUTINE xios(is_defined_context_attr_hdl_)   &
    ( context_hdl, output_dir_ )

    IMPLICIT NONE
      TYPE(txios(context)) , INTENT(IN) :: context_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_dir_
      LOGICAL(KIND=C_BOOL) :: output_dir__tmp

      IF (PRESENT(output_dir_)) THEN
        output_dir__tmp = cxios_is_defined_context_output_dir &
      (context_hdl%daddr)
        output_dir_ = output_dir__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_context_attr_hdl_)

END MODULE icontext_attr
