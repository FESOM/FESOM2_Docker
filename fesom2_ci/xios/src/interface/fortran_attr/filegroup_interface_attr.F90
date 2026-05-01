! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE filegroup_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_filegroup_append(filegroup_hdl, append) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: append
    END SUBROUTINE cxios_set_filegroup_append

    SUBROUTINE cxios_get_filegroup_append(filegroup_hdl, append) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      LOGICAL (KIND=C_BOOL)             :: append
    END SUBROUTINE cxios_get_filegroup_append

    FUNCTION cxios_is_defined_filegroup_append(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_append
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_append


    SUBROUTINE cxios_set_filegroup_comment(filegroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_filegroup_comment

    SUBROUTINE cxios_get_filegroup_comment(filegroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_filegroup_comment

    FUNCTION cxios_is_defined_filegroup_comment(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_comment


    SUBROUTINE cxios_set_filegroup_compression_level(filegroup_hdl, compression_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: compression_level
    END SUBROUTINE cxios_set_filegroup_compression_level

    SUBROUTINE cxios_get_filegroup_compression_level(filegroup_hdl, compression_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      INTEGER (KIND=C_INT)             :: compression_level
    END SUBROUTINE cxios_get_filegroup_compression_level

    FUNCTION cxios_is_defined_filegroup_compression_level(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_compression_level
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_compression_level


    SUBROUTINE cxios_set_filegroup_convention(filegroup_hdl, convention, convention_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: convention
      INTEGER  (kind = C_INT)     , VALUE        :: convention_size
    END SUBROUTINE cxios_set_filegroup_convention

    SUBROUTINE cxios_get_filegroup_convention(filegroup_hdl, convention, convention_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: convention
      INTEGER  (kind = C_INT)     , VALUE        :: convention_size
    END SUBROUTINE cxios_get_filegroup_convention

    FUNCTION cxios_is_defined_filegroup_convention(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_convention
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_convention


    SUBROUTINE cxios_set_filegroup_convention_str(filegroup_hdl, convention_str, convention_str_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: convention_str
      INTEGER  (kind = C_INT)     , VALUE        :: convention_str_size
    END SUBROUTINE cxios_set_filegroup_convention_str

    SUBROUTINE cxios_get_filegroup_convention_str(filegroup_hdl, convention_str, convention_str_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: convention_str
      INTEGER  (kind = C_INT)     , VALUE        :: convention_str_size
    END SUBROUTINE cxios_get_filegroup_convention_str

    FUNCTION cxios_is_defined_filegroup_convention_str(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_convention_str
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_convention_str


    SUBROUTINE cxios_set_filegroup_cyclic(filegroup_hdl, cyclic) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: cyclic
    END SUBROUTINE cxios_set_filegroup_cyclic

    SUBROUTINE cxios_get_filegroup_cyclic(filegroup_hdl, cyclic) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      LOGICAL (KIND=C_BOOL)             :: cyclic
    END SUBROUTINE cxios_get_filegroup_cyclic

    FUNCTION cxios_is_defined_filegroup_cyclic(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_cyclic
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_cyclic


    SUBROUTINE cxios_set_filegroup_description(filegroup_hdl, description, description_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: description
      INTEGER  (kind = C_INT)     , VALUE        :: description_size
    END SUBROUTINE cxios_set_filegroup_description

    SUBROUTINE cxios_get_filegroup_description(filegroup_hdl, description, description_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: description
      INTEGER  (kind = C_INT)     , VALUE        :: description_size
    END SUBROUTINE cxios_get_filegroup_description

    FUNCTION cxios_is_defined_filegroup_description(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_description
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_description


    SUBROUTINE cxios_set_filegroup_enabled(filegroup_hdl, enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: enabled
    END SUBROUTINE cxios_set_filegroup_enabled

    SUBROUTINE cxios_get_filegroup_enabled(filegroup_hdl, enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      LOGICAL (KIND=C_BOOL)             :: enabled
    END SUBROUTINE cxios_get_filegroup_enabled

    FUNCTION cxios_is_defined_filegroup_enabled(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_enabled
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_enabled


    SUBROUTINE cxios_set_filegroup_format(filegroup_hdl, format, format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: format
      INTEGER  (kind = C_INT)     , VALUE        :: format_size
    END SUBROUTINE cxios_set_filegroup_format

    SUBROUTINE cxios_get_filegroup_format(filegroup_hdl, format, format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: format
      INTEGER  (kind = C_INT)     , VALUE        :: format_size
    END SUBROUTINE cxios_get_filegroup_format

    FUNCTION cxios_is_defined_filegroup_format(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_format
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_format


    SUBROUTINE cxios_set_filegroup_group_ref(filegroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_set_filegroup_group_ref

    SUBROUTINE cxios_get_filegroup_group_ref(filegroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_get_filegroup_group_ref

    FUNCTION cxios_is_defined_filegroup_group_ref(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_group_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_group_ref


    SUBROUTINE cxios_set_filegroup_min_digits(filegroup_hdl, min_digits) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: min_digits
    END SUBROUTINE cxios_set_filegroup_min_digits

    SUBROUTINE cxios_get_filegroup_min_digits(filegroup_hdl, min_digits) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      INTEGER (KIND=C_INT)             :: min_digits
    END SUBROUTINE cxios_get_filegroup_min_digits

    FUNCTION cxios_is_defined_filegroup_min_digits(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_min_digits
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_min_digits


    SUBROUTINE cxios_set_filegroup_mode(filegroup_hdl, mode, mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: mode
      INTEGER  (kind = C_INT)     , VALUE        :: mode_size
    END SUBROUTINE cxios_set_filegroup_mode

    SUBROUTINE cxios_get_filegroup_mode(filegroup_hdl, mode, mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: mode
      INTEGER  (kind = C_INT)     , VALUE        :: mode_size
    END SUBROUTINE cxios_get_filegroup_mode

    FUNCTION cxios_is_defined_filegroup_mode(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_mode
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_mode


    SUBROUTINE cxios_set_filegroup_name(filegroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_filegroup_name

    SUBROUTINE cxios_get_filegroup_name(filegroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_filegroup_name

    FUNCTION cxios_is_defined_filegroup_name(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_name
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_name


    SUBROUTINE cxios_set_filegroup_name_suffix(filegroup_hdl, name_suffix, name_suffix_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name_suffix
      INTEGER  (kind = C_INT)     , VALUE        :: name_suffix_size
    END SUBROUTINE cxios_set_filegroup_name_suffix

    SUBROUTINE cxios_get_filegroup_name_suffix(filegroup_hdl, name_suffix, name_suffix_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name_suffix
      INTEGER  (kind = C_INT)     , VALUE        :: name_suffix_size
    END SUBROUTINE cxios_get_filegroup_name_suffix

    FUNCTION cxios_is_defined_filegroup_name_suffix(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_name_suffix
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_name_suffix


    SUBROUTINE cxios_set_filegroup_output_freq(filegroup_hdl, output_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)), VALUE :: output_freq
    END SUBROUTINE cxios_set_filegroup_output_freq

    SUBROUTINE cxios_get_filegroup_output_freq(filegroup_hdl, output_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)) :: output_freq
    END SUBROUTINE cxios_get_filegroup_output_freq

    FUNCTION cxios_is_defined_filegroup_output_freq(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_output_freq
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_output_freq


    SUBROUTINE cxios_set_filegroup_output_level(filegroup_hdl, output_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: output_level
    END SUBROUTINE cxios_set_filegroup_output_level

    SUBROUTINE cxios_get_filegroup_output_level(filegroup_hdl, output_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      INTEGER (KIND=C_INT)             :: output_level
    END SUBROUTINE cxios_get_filegroup_output_level

    FUNCTION cxios_is_defined_filegroup_output_level(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_output_level
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_output_level


    SUBROUTINE cxios_set_filegroup_par_access(filegroup_hdl, par_access, par_access_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: par_access
      INTEGER  (kind = C_INT)     , VALUE        :: par_access_size
    END SUBROUTINE cxios_set_filegroup_par_access

    SUBROUTINE cxios_get_filegroup_par_access(filegroup_hdl, par_access, par_access_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: par_access
      INTEGER  (kind = C_INT)     , VALUE        :: par_access_size
    END SUBROUTINE cxios_get_filegroup_par_access

    FUNCTION cxios_is_defined_filegroup_par_access(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_par_access
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_par_access


    SUBROUTINE cxios_set_filegroup_read_metadata_par(filegroup_hdl, read_metadata_par) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: read_metadata_par
    END SUBROUTINE cxios_set_filegroup_read_metadata_par

    SUBROUTINE cxios_get_filegroup_read_metadata_par(filegroup_hdl, read_metadata_par) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      LOGICAL (KIND=C_BOOL)             :: read_metadata_par
    END SUBROUTINE cxios_get_filegroup_read_metadata_par

    FUNCTION cxios_is_defined_filegroup_read_metadata_par(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_read_metadata_par
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_read_metadata_par


    SUBROUTINE cxios_set_filegroup_record_offset(filegroup_hdl, record_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      INTEGER (KIND=C_INT)      , VALUE :: record_offset
    END SUBROUTINE cxios_set_filegroup_record_offset

    SUBROUTINE cxios_get_filegroup_record_offset(filegroup_hdl, record_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      INTEGER (KIND=C_INT)             :: record_offset
    END SUBROUTINE cxios_get_filegroup_record_offset

    FUNCTION cxios_is_defined_filegroup_record_offset(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_record_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_record_offset


    SUBROUTINE cxios_set_filegroup_split_end_offset(filegroup_hdl, split_end_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)), VALUE :: split_end_offset
    END SUBROUTINE cxios_set_filegroup_split_end_offset

    SUBROUTINE cxios_get_filegroup_split_end_offset(filegroup_hdl, split_end_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)) :: split_end_offset
    END SUBROUTINE cxios_get_filegroup_split_end_offset

    FUNCTION cxios_is_defined_filegroup_split_end_offset(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_split_end_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_split_end_offset


    SUBROUTINE cxios_set_filegroup_split_freq(filegroup_hdl, split_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)), VALUE :: split_freq
    END SUBROUTINE cxios_set_filegroup_split_freq

    SUBROUTINE cxios_get_filegroup_split_freq(filegroup_hdl, split_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)) :: split_freq
    END SUBROUTINE cxios_get_filegroup_split_freq

    FUNCTION cxios_is_defined_filegroup_split_freq(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_split_freq
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_split_freq


    SUBROUTINE cxios_set_filegroup_split_freq_format(filegroup_hdl, split_freq_format, split_freq_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: split_freq_format
      INTEGER  (kind = C_INT)     , VALUE        :: split_freq_format_size
    END SUBROUTINE cxios_set_filegroup_split_freq_format

    SUBROUTINE cxios_get_filegroup_split_freq_format(filegroup_hdl, split_freq_format, split_freq_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: split_freq_format
      INTEGER  (kind = C_INT)     , VALUE        :: split_freq_format_size
    END SUBROUTINE cxios_get_filegroup_split_freq_format

    FUNCTION cxios_is_defined_filegroup_split_freq_format(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_split_freq_format
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_split_freq_format


    SUBROUTINE cxios_set_filegroup_split_last_date(filegroup_hdl, split_last_date, split_last_date_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: split_last_date
      INTEGER  (kind = C_INT)     , VALUE        :: split_last_date_size
    END SUBROUTINE cxios_set_filegroup_split_last_date

    SUBROUTINE cxios_get_filegroup_split_last_date(filegroup_hdl, split_last_date, split_last_date_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: split_last_date
      INTEGER  (kind = C_INT)     , VALUE        :: split_last_date_size
    END SUBROUTINE cxios_get_filegroup_split_last_date

    FUNCTION cxios_is_defined_filegroup_split_last_date(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_split_last_date
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_split_last_date


    SUBROUTINE cxios_set_filegroup_split_start_offset(filegroup_hdl, split_start_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)), VALUE :: split_start_offset
    END SUBROUTINE cxios_set_filegroup_split_start_offset

    SUBROUTINE cxios_get_filegroup_split_start_offset(filegroup_hdl, split_start_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)) :: split_start_offset
    END SUBROUTINE cxios_get_filegroup_split_start_offset

    FUNCTION cxios_is_defined_filegroup_split_start_offset(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_split_start_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_split_start_offset


    SUBROUTINE cxios_set_filegroup_sync_freq(filegroup_hdl, sync_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)), VALUE :: sync_freq
    END SUBROUTINE cxios_set_filegroup_sync_freq

    SUBROUTINE cxios_get_filegroup_sync_freq(filegroup_hdl, sync_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      TYPE(txios(duration)) :: sync_freq
    END SUBROUTINE cxios_get_filegroup_sync_freq

    FUNCTION cxios_is_defined_filegroup_sync_freq(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_sync_freq
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_sync_freq


    SUBROUTINE cxios_set_filegroup_time_counter(filegroup_hdl, time_counter, time_counter_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_counter
      INTEGER  (kind = C_INT)     , VALUE        :: time_counter_size
    END SUBROUTINE cxios_set_filegroup_time_counter

    SUBROUTINE cxios_get_filegroup_time_counter(filegroup_hdl, time_counter, time_counter_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_counter
      INTEGER  (kind = C_INT)     , VALUE        :: time_counter_size
    END SUBROUTINE cxios_get_filegroup_time_counter

    FUNCTION cxios_is_defined_filegroup_time_counter(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_time_counter
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_time_counter


    SUBROUTINE cxios_set_filegroup_time_counter_name(filegroup_hdl, time_counter_name, time_counter_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_counter_name
      INTEGER  (kind = C_INT)     , VALUE        :: time_counter_name_size
    END SUBROUTINE cxios_set_filegroup_time_counter_name

    SUBROUTINE cxios_get_filegroup_time_counter_name(filegroup_hdl, time_counter_name, time_counter_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_counter_name
      INTEGER  (kind = C_INT)     , VALUE        :: time_counter_name_size
    END SUBROUTINE cxios_get_filegroup_time_counter_name

    FUNCTION cxios_is_defined_filegroup_time_counter_name(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_time_counter_name
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_time_counter_name


    SUBROUTINE cxios_set_filegroup_time_stamp_format(filegroup_hdl, time_stamp_format, time_stamp_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_stamp_format
      INTEGER  (kind = C_INT)     , VALUE        :: time_stamp_format_size
    END SUBROUTINE cxios_set_filegroup_time_stamp_format

    SUBROUTINE cxios_get_filegroup_time_stamp_format(filegroup_hdl, time_stamp_format, time_stamp_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_stamp_format
      INTEGER  (kind = C_INT)     , VALUE        :: time_stamp_format_size
    END SUBROUTINE cxios_get_filegroup_time_stamp_format

    FUNCTION cxios_is_defined_filegroup_time_stamp_format(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_time_stamp_format
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_time_stamp_format


    SUBROUTINE cxios_set_filegroup_time_stamp_name(filegroup_hdl, time_stamp_name, time_stamp_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_stamp_name
      INTEGER  (kind = C_INT)     , VALUE        :: time_stamp_name_size
    END SUBROUTINE cxios_set_filegroup_time_stamp_name

    SUBROUTINE cxios_get_filegroup_time_stamp_name(filegroup_hdl, time_stamp_name, time_stamp_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_stamp_name
      INTEGER  (kind = C_INT)     , VALUE        :: time_stamp_name_size
    END SUBROUTINE cxios_get_filegroup_time_stamp_name

    FUNCTION cxios_is_defined_filegroup_time_stamp_name(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_time_stamp_name
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_time_stamp_name


    SUBROUTINE cxios_set_filegroup_time_units(filegroup_hdl, time_units, time_units_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_units
      INTEGER  (kind = C_INT)     , VALUE        :: time_units_size
    END SUBROUTINE cxios_set_filegroup_time_units

    SUBROUTINE cxios_get_filegroup_time_units(filegroup_hdl, time_units, time_units_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_units
      INTEGER  (kind = C_INT)     , VALUE        :: time_units_size
    END SUBROUTINE cxios_get_filegroup_time_units

    FUNCTION cxios_is_defined_filegroup_time_units(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_time_units
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_time_units


    SUBROUTINE cxios_set_filegroup_timeseries(filegroup_hdl, timeseries, timeseries_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: timeseries
      INTEGER  (kind = C_INT)     , VALUE        :: timeseries_size
    END SUBROUTINE cxios_set_filegroup_timeseries

    SUBROUTINE cxios_get_filegroup_timeseries(filegroup_hdl, timeseries, timeseries_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: timeseries
      INTEGER  (kind = C_INT)     , VALUE        :: timeseries_size
    END SUBROUTINE cxios_get_filegroup_timeseries

    FUNCTION cxios_is_defined_filegroup_timeseries(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_timeseries
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_timeseries


    SUBROUTINE cxios_set_filegroup_ts_prefix(filegroup_hdl, ts_prefix, ts_prefix_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: ts_prefix
      INTEGER  (kind = C_INT)     , VALUE        :: ts_prefix_size
    END SUBROUTINE cxios_set_filegroup_ts_prefix

    SUBROUTINE cxios_get_filegroup_ts_prefix(filegroup_hdl, ts_prefix, ts_prefix_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: ts_prefix
      INTEGER  (kind = C_INT)     , VALUE        :: ts_prefix_size
    END SUBROUTINE cxios_get_filegroup_ts_prefix

    FUNCTION cxios_is_defined_filegroup_ts_prefix(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_ts_prefix
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_ts_prefix


    SUBROUTINE cxios_set_filegroup_type(filegroup_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_filegroup_type

    SUBROUTINE cxios_get_filegroup_type(filegroup_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_filegroup_type

    FUNCTION cxios_is_defined_filegroup_type(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_type
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_type


    SUBROUTINE cxios_set_filegroup_uuid_format(filegroup_hdl, uuid_format, uuid_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: uuid_format
      INTEGER  (kind = C_INT)     , VALUE        :: uuid_format_size
    END SUBROUTINE cxios_set_filegroup_uuid_format

    SUBROUTINE cxios_get_filegroup_uuid_format(filegroup_hdl, uuid_format, uuid_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: uuid_format
      INTEGER  (kind = C_INT)     , VALUE        :: uuid_format_size
    END SUBROUTINE cxios_get_filegroup_uuid_format

    FUNCTION cxios_is_defined_filegroup_uuid_format(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_uuid_format
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_uuid_format


    SUBROUTINE cxios_set_filegroup_uuid_name(filegroup_hdl, uuid_name, uuid_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: uuid_name
      INTEGER  (kind = C_INT)     , VALUE        :: uuid_name_size
    END SUBROUTINE cxios_set_filegroup_uuid_name

    SUBROUTINE cxios_get_filegroup_uuid_name(filegroup_hdl, uuid_name, uuid_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: uuid_name
      INTEGER  (kind = C_INT)     , VALUE        :: uuid_name_size
    END SUBROUTINE cxios_get_filegroup_uuid_name

    FUNCTION cxios_is_defined_filegroup_uuid_name(filegroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_filegroup_uuid_name
      INTEGER (kind = C_INTPTR_T), VALUE :: filegroup_hdl
    END FUNCTION cxios_is_defined_filegroup_uuid_name

  END INTERFACE

END MODULE filegroup_interface_attr
