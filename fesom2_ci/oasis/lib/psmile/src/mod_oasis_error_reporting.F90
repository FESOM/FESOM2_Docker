!> OASIS enhanced error reporting module

MODULE mod_oasis_error_reporting

    use mod_oasis_kinds
    use mod_oasis_data
    use mod_oasis_parameters
    use mod_oasis_var
    use mod_oasis_sys

    implicit none
    private

    public oasis_abort_with_field_info

CONTAINS

!> Enhanced abort routine that includes field information in error messages
!> This is a wrapper around oasis_abort that adds field info to the error message
SUBROUTINE oasis_abort_with_field_info(var_id, file, line, extra_message)
    IMPLICIT none
    !-------------------------------------
    integer(kind=ip_i4_p), intent(in) :: var_id      !< variable id
    character(len=*), intent(in) :: file             !< file where error occurred
    integer, intent(in) :: line                      !< line where error occurred
    character(len=*), intent(in), optional :: extra_message !< optional extra message
    !-------------------------------------
    character(len=256) :: field_info                 !< field information string
    character(len=256) :: error_message              !< combined error message
    character(len=*), parameter :: subname = '(oasis_abort_with_field_info)'
    !-------------------------------------

    ! Build information about the field
    field_info = 'Field name: ' // trim(prism_var(var_id)%name) // &
                 ', Field operation: ' // trim(get_op_name(prism_var(var_id)%ops))

    ! Add extra message if provided
    if (present(extra_message)) then
        error_message = trim(extra_message) // ' - ' // trim(field_info)
    else
        error_message = 'Failed field exchange - ' // trim(field_info)
    endif

    ! Call the original abort with enhanced error information
    call oasis_abort(file=file, line=line, cd_message=error_message)

END SUBROUTINE oasis_abort_with_field_info

!> Helper function to get operation name as string
FUNCTION get_op_name(op_code) RESULT(op_name)
    INTEGER(kind=ip_i4_p), intent(in) :: op_code  !< operation code
    CHARACTER(len=10) :: op_name                  !< operation name

    select case(op_code)
        case(OASIS_IN)
            op_name = 'INPUT'
        case(OASIS_OUT)
            op_name = 'OUTPUT'
        case default
            op_name = 'UNKNOWN'
    end select

END FUNCTION get_op_name

END MODULE mod_oasis_error_reporting
