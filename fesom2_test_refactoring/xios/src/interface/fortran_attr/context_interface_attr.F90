! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE context_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_context_output_dir(context_hdl, output_dir, output_dir_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: context_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: output_dir
      INTEGER  (kind = C_INT)     , VALUE        :: output_dir_size
    END SUBROUTINE cxios_set_context_output_dir

    SUBROUTINE cxios_get_context_output_dir(context_hdl, output_dir, output_dir_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: context_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: output_dir
      INTEGER  (kind = C_INT)     , VALUE        :: output_dir_size
    END SUBROUTINE cxios_get_context_output_dir

    FUNCTION cxios_is_defined_context_output_dir(context_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_context_output_dir
      INTEGER (kind = C_INTPTR_T), VALUE :: context_hdl
    END FUNCTION cxios_is_defined_context_output_dir

  END INTERFACE

END MODULE context_interface_attr
