! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE file_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_file_append(file_hdl, append) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: append
    END SUBROUTINE cxios_set_file_append

    SUBROUTINE cxios_get_file_append(file_hdl, append) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      LOGICAL (KIND=C_BOOL)             :: append
    END SUBROUTINE cxios_get_file_append

    FUNCTION cxios_is_defined_file_append(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_append
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_append


    SUBROUTINE cxios_set_file_comment(file_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_file_comment

    SUBROUTINE cxios_get_file_comment(file_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_file_comment

    FUNCTION cxios_is_defined_file_comment(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_comment


    SUBROUTINE cxios_set_file_compression_level(file_hdl, compression_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      INTEGER (KIND=C_INT)      , VALUE :: compression_level
    END SUBROUTINE cxios_set_file_compression_level

    SUBROUTINE cxios_get_file_compression_level(file_hdl, compression_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      INTEGER (KIND=C_INT)             :: compression_level
    END SUBROUTINE cxios_get_file_compression_level

    FUNCTION cxios_is_defined_file_compression_level(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_compression_level
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_compression_level


    SUBROUTINE cxios_set_file_convention(file_hdl, convention, convention_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: convention
      INTEGER  (kind = C_INT)     , VALUE        :: convention_size
    END SUBROUTINE cxios_set_file_convention

    SUBROUTINE cxios_get_file_convention(file_hdl, convention, convention_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: convention
      INTEGER  (kind = C_INT)     , VALUE        :: convention_size
    END SUBROUTINE cxios_get_file_convention

    FUNCTION cxios_is_defined_file_convention(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_convention
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_convention


    SUBROUTINE cxios_set_file_convention_str(file_hdl, convention_str, convention_str_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: convention_str
      INTEGER  (kind = C_INT)     , VALUE        :: convention_str_size
    END SUBROUTINE cxios_set_file_convention_str

    SUBROUTINE cxios_get_file_convention_str(file_hdl, convention_str, convention_str_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: convention_str
      INTEGER  (kind = C_INT)     , VALUE        :: convention_str_size
    END SUBROUTINE cxios_get_file_convention_str

    FUNCTION cxios_is_defined_file_convention_str(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_convention_str
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_convention_str


    SUBROUTINE cxios_set_file_cyclic(file_hdl, cyclic) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: cyclic
    END SUBROUTINE cxios_set_file_cyclic

    SUBROUTINE cxios_get_file_cyclic(file_hdl, cyclic) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      LOGICAL (KIND=C_BOOL)             :: cyclic
    END SUBROUTINE cxios_get_file_cyclic

    FUNCTION cxios_is_defined_file_cyclic(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_cyclic
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_cyclic


    SUBROUTINE cxios_set_file_description(file_hdl, description, description_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: description
      INTEGER  (kind = C_INT)     , VALUE        :: description_size
    END SUBROUTINE cxios_set_file_description

    SUBROUTINE cxios_get_file_description(file_hdl, description, description_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: description
      INTEGER  (kind = C_INT)     , VALUE        :: description_size
    END SUBROUTINE cxios_get_file_description

    FUNCTION cxios_is_defined_file_description(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_description
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_description


    SUBROUTINE cxios_set_file_enabled(file_hdl, enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: enabled
    END SUBROUTINE cxios_set_file_enabled

    SUBROUTINE cxios_get_file_enabled(file_hdl, enabled) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      LOGICAL (KIND=C_BOOL)             :: enabled
    END SUBROUTINE cxios_get_file_enabled

    FUNCTION cxios_is_defined_file_enabled(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_enabled
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_enabled


    SUBROUTINE cxios_set_file_format(file_hdl, format, format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: format
      INTEGER  (kind = C_INT)     , VALUE        :: format_size
    END SUBROUTINE cxios_set_file_format

    SUBROUTINE cxios_get_file_format(file_hdl, format, format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: format
      INTEGER  (kind = C_INT)     , VALUE        :: format_size
    END SUBROUTINE cxios_get_file_format

    FUNCTION cxios_is_defined_file_format(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_format
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_format


    SUBROUTINE cxios_set_file_min_digits(file_hdl, min_digits) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      INTEGER (KIND=C_INT)      , VALUE :: min_digits
    END SUBROUTINE cxios_set_file_min_digits

    SUBROUTINE cxios_get_file_min_digits(file_hdl, min_digits) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      INTEGER (KIND=C_INT)             :: min_digits
    END SUBROUTINE cxios_get_file_min_digits

    FUNCTION cxios_is_defined_file_min_digits(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_min_digits
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_min_digits


    SUBROUTINE cxios_set_file_mode(file_hdl, mode, mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: mode
      INTEGER  (kind = C_INT)     , VALUE        :: mode_size
    END SUBROUTINE cxios_set_file_mode

    SUBROUTINE cxios_get_file_mode(file_hdl, mode, mode_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: mode
      INTEGER  (kind = C_INT)     , VALUE        :: mode_size
    END SUBROUTINE cxios_get_file_mode

    FUNCTION cxios_is_defined_file_mode(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_mode
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_mode


    SUBROUTINE cxios_set_file_name(file_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_file_name

    SUBROUTINE cxios_get_file_name(file_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_file_name

    FUNCTION cxios_is_defined_file_name(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_name
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_name


    SUBROUTINE cxios_set_file_name_suffix(file_hdl, name_suffix, name_suffix_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name_suffix
      INTEGER  (kind = C_INT)     , VALUE        :: name_suffix_size
    END SUBROUTINE cxios_set_file_name_suffix

    SUBROUTINE cxios_get_file_name_suffix(file_hdl, name_suffix, name_suffix_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name_suffix
      INTEGER  (kind = C_INT)     , VALUE        :: name_suffix_size
    END SUBROUTINE cxios_get_file_name_suffix

    FUNCTION cxios_is_defined_file_name_suffix(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_name_suffix
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_name_suffix


    SUBROUTINE cxios_set_file_output_freq(file_hdl, output_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)), VALUE :: output_freq
    END SUBROUTINE cxios_set_file_output_freq

    SUBROUTINE cxios_get_file_output_freq(file_hdl, output_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)) :: output_freq
    END SUBROUTINE cxios_get_file_output_freq

    FUNCTION cxios_is_defined_file_output_freq(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_output_freq
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_output_freq


    SUBROUTINE cxios_set_file_output_level(file_hdl, output_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      INTEGER (KIND=C_INT)      , VALUE :: output_level
    END SUBROUTINE cxios_set_file_output_level

    SUBROUTINE cxios_get_file_output_level(file_hdl, output_level) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      INTEGER (KIND=C_INT)             :: output_level
    END SUBROUTINE cxios_get_file_output_level

    FUNCTION cxios_is_defined_file_output_level(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_output_level
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_output_level


    SUBROUTINE cxios_set_file_par_access(file_hdl, par_access, par_access_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: par_access
      INTEGER  (kind = C_INT)     , VALUE        :: par_access_size
    END SUBROUTINE cxios_set_file_par_access

    SUBROUTINE cxios_get_file_par_access(file_hdl, par_access, par_access_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: par_access
      INTEGER  (kind = C_INT)     , VALUE        :: par_access_size
    END SUBROUTINE cxios_get_file_par_access

    FUNCTION cxios_is_defined_file_par_access(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_par_access
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_par_access


    SUBROUTINE cxios_set_file_read_metadata_par(file_hdl, read_metadata_par) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      LOGICAL (KIND=C_BOOL)      , VALUE :: read_metadata_par
    END SUBROUTINE cxios_set_file_read_metadata_par

    SUBROUTINE cxios_get_file_read_metadata_par(file_hdl, read_metadata_par) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      LOGICAL (KIND=C_BOOL)             :: read_metadata_par
    END SUBROUTINE cxios_get_file_read_metadata_par

    FUNCTION cxios_is_defined_file_read_metadata_par(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_read_metadata_par
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_read_metadata_par


    SUBROUTINE cxios_set_file_record_offset(file_hdl, record_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      INTEGER (KIND=C_INT)      , VALUE :: record_offset
    END SUBROUTINE cxios_set_file_record_offset

    SUBROUTINE cxios_get_file_record_offset(file_hdl, record_offset) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      INTEGER (KIND=C_INT)             :: record_offset
    END SUBROUTINE cxios_get_file_record_offset

    FUNCTION cxios_is_defined_file_record_offset(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_record_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_record_offset


    SUBROUTINE cxios_set_file_split_end_offset(file_hdl, split_end_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)), VALUE :: split_end_offset
    END SUBROUTINE cxios_set_file_split_end_offset

    SUBROUTINE cxios_get_file_split_end_offset(file_hdl, split_end_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)) :: split_end_offset
    END SUBROUTINE cxios_get_file_split_end_offset

    FUNCTION cxios_is_defined_file_split_end_offset(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_split_end_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_split_end_offset


    SUBROUTINE cxios_set_file_split_freq(file_hdl, split_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)), VALUE :: split_freq
    END SUBROUTINE cxios_set_file_split_freq

    SUBROUTINE cxios_get_file_split_freq(file_hdl, split_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)) :: split_freq
    END SUBROUTINE cxios_get_file_split_freq

    FUNCTION cxios_is_defined_file_split_freq(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_split_freq
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_split_freq


    SUBROUTINE cxios_set_file_split_freq_format(file_hdl, split_freq_format, split_freq_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: split_freq_format
      INTEGER  (kind = C_INT)     , VALUE        :: split_freq_format_size
    END SUBROUTINE cxios_set_file_split_freq_format

    SUBROUTINE cxios_get_file_split_freq_format(file_hdl, split_freq_format, split_freq_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: split_freq_format
      INTEGER  (kind = C_INT)     , VALUE        :: split_freq_format_size
    END SUBROUTINE cxios_get_file_split_freq_format

    FUNCTION cxios_is_defined_file_split_freq_format(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_split_freq_format
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_split_freq_format


    SUBROUTINE cxios_set_file_split_last_date(file_hdl, split_last_date, split_last_date_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: split_last_date
      INTEGER  (kind = C_INT)     , VALUE        :: split_last_date_size
    END SUBROUTINE cxios_set_file_split_last_date

    SUBROUTINE cxios_get_file_split_last_date(file_hdl, split_last_date, split_last_date_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: split_last_date
      INTEGER  (kind = C_INT)     , VALUE        :: split_last_date_size
    END SUBROUTINE cxios_get_file_split_last_date

    FUNCTION cxios_is_defined_file_split_last_date(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_split_last_date
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_split_last_date


    SUBROUTINE cxios_set_file_split_start_offset(file_hdl, split_start_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)), VALUE :: split_start_offset
    END SUBROUTINE cxios_set_file_split_start_offset

    SUBROUTINE cxios_get_file_split_start_offset(file_hdl, split_start_offset) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)) :: split_start_offset
    END SUBROUTINE cxios_get_file_split_start_offset

    FUNCTION cxios_is_defined_file_split_start_offset(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_split_start_offset
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_split_start_offset


    SUBROUTINE cxios_set_file_sync_freq(file_hdl, sync_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)), VALUE :: sync_freq
    END SUBROUTINE cxios_set_file_sync_freq

    SUBROUTINE cxios_get_file_sync_freq(file_hdl, sync_freq) BIND(C)
      USE ISO_C_BINDING
      USE IDURATION
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      TYPE(txios(duration)) :: sync_freq
    END SUBROUTINE cxios_get_file_sync_freq

    FUNCTION cxios_is_defined_file_sync_freq(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_sync_freq
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_sync_freq


    SUBROUTINE cxios_set_file_time_counter(file_hdl, time_counter, time_counter_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_counter
      INTEGER  (kind = C_INT)     , VALUE        :: time_counter_size
    END SUBROUTINE cxios_set_file_time_counter

    SUBROUTINE cxios_get_file_time_counter(file_hdl, time_counter, time_counter_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_counter
      INTEGER  (kind = C_INT)     , VALUE        :: time_counter_size
    END SUBROUTINE cxios_get_file_time_counter

    FUNCTION cxios_is_defined_file_time_counter(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_time_counter
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_time_counter


    SUBROUTINE cxios_set_file_time_counter_name(file_hdl, time_counter_name, time_counter_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_counter_name
      INTEGER  (kind = C_INT)     , VALUE        :: time_counter_name_size
    END SUBROUTINE cxios_set_file_time_counter_name

    SUBROUTINE cxios_get_file_time_counter_name(file_hdl, time_counter_name, time_counter_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_counter_name
      INTEGER  (kind = C_INT)     , VALUE        :: time_counter_name_size
    END SUBROUTINE cxios_get_file_time_counter_name

    FUNCTION cxios_is_defined_file_time_counter_name(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_time_counter_name
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_time_counter_name


    SUBROUTINE cxios_set_file_time_stamp_format(file_hdl, time_stamp_format, time_stamp_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_stamp_format
      INTEGER  (kind = C_INT)     , VALUE        :: time_stamp_format_size
    END SUBROUTINE cxios_set_file_time_stamp_format

    SUBROUTINE cxios_get_file_time_stamp_format(file_hdl, time_stamp_format, time_stamp_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_stamp_format
      INTEGER  (kind = C_INT)     , VALUE        :: time_stamp_format_size
    END SUBROUTINE cxios_get_file_time_stamp_format

    FUNCTION cxios_is_defined_file_time_stamp_format(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_time_stamp_format
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_time_stamp_format


    SUBROUTINE cxios_set_file_time_stamp_name(file_hdl, time_stamp_name, time_stamp_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_stamp_name
      INTEGER  (kind = C_INT)     , VALUE        :: time_stamp_name_size
    END SUBROUTINE cxios_set_file_time_stamp_name

    SUBROUTINE cxios_get_file_time_stamp_name(file_hdl, time_stamp_name, time_stamp_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_stamp_name
      INTEGER  (kind = C_INT)     , VALUE        :: time_stamp_name_size
    END SUBROUTINE cxios_get_file_time_stamp_name

    FUNCTION cxios_is_defined_file_time_stamp_name(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_time_stamp_name
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_time_stamp_name


    SUBROUTINE cxios_set_file_time_units(file_hdl, time_units, time_units_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_units
      INTEGER  (kind = C_INT)     , VALUE        :: time_units_size
    END SUBROUTINE cxios_set_file_time_units

    SUBROUTINE cxios_get_file_time_units(file_hdl, time_units, time_units_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: time_units
      INTEGER  (kind = C_INT)     , VALUE        :: time_units_size
    END SUBROUTINE cxios_get_file_time_units

    FUNCTION cxios_is_defined_file_time_units(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_time_units
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_time_units


    SUBROUTINE cxios_set_file_timeseries(file_hdl, timeseries, timeseries_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: timeseries
      INTEGER  (kind = C_INT)     , VALUE        :: timeseries_size
    END SUBROUTINE cxios_set_file_timeseries

    SUBROUTINE cxios_get_file_timeseries(file_hdl, timeseries, timeseries_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: timeseries
      INTEGER  (kind = C_INT)     , VALUE        :: timeseries_size
    END SUBROUTINE cxios_get_file_timeseries

    FUNCTION cxios_is_defined_file_timeseries(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_timeseries
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_timeseries


    SUBROUTINE cxios_set_file_ts_prefix(file_hdl, ts_prefix, ts_prefix_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: ts_prefix
      INTEGER  (kind = C_INT)     , VALUE        :: ts_prefix_size
    END SUBROUTINE cxios_set_file_ts_prefix

    SUBROUTINE cxios_get_file_ts_prefix(file_hdl, ts_prefix, ts_prefix_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: ts_prefix
      INTEGER  (kind = C_INT)     , VALUE        :: ts_prefix_size
    END SUBROUTINE cxios_get_file_ts_prefix

    FUNCTION cxios_is_defined_file_ts_prefix(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_ts_prefix
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_ts_prefix


    SUBROUTINE cxios_set_file_type(file_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_set_file_type

    SUBROUTINE cxios_get_file_type(file_hdl, type, type_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: type
      INTEGER  (kind = C_INT)     , VALUE        :: type_size
    END SUBROUTINE cxios_get_file_type

    FUNCTION cxios_is_defined_file_type(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_type
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_type


    SUBROUTINE cxios_set_file_uuid_format(file_hdl, uuid_format, uuid_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: uuid_format
      INTEGER  (kind = C_INT)     , VALUE        :: uuid_format_size
    END SUBROUTINE cxios_set_file_uuid_format

    SUBROUTINE cxios_get_file_uuid_format(file_hdl, uuid_format, uuid_format_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: uuid_format
      INTEGER  (kind = C_INT)     , VALUE        :: uuid_format_size
    END SUBROUTINE cxios_get_file_uuid_format

    FUNCTION cxios_is_defined_file_uuid_format(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_uuid_format
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_uuid_format


    SUBROUTINE cxios_set_file_uuid_name(file_hdl, uuid_name, uuid_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: uuid_name
      INTEGER  (kind = C_INT)     , VALUE        :: uuid_name_size
    END SUBROUTINE cxios_set_file_uuid_name

    SUBROUTINE cxios_get_file_uuid_name(file_hdl, uuid_name, uuid_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: uuid_name
      INTEGER  (kind = C_INT)     , VALUE        :: uuid_name_size
    END SUBROUTINE cxios_get_file_uuid_name

    FUNCTION cxios_is_defined_file_uuid_name(file_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_file_uuid_name
      INTEGER (kind = C_INTPTR_T), VALUE :: file_hdl
    END FUNCTION cxios_is_defined_file_uuid_name

  END INTERFACE

END MODULE file_interface_attr
