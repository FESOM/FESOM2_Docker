! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE ifilegroup_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE ifile
  USE filegroup_interface_attr

CONTAINS

  SUBROUTINE xios(set_filegroup_attr)  &
    ( filegroup_id, append, comment, compression_level, convention, convention_str, cyclic, description  &
    , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
    , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
    , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
    , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

    IMPLICIT NONE
      TYPE(txios(filegroup))  :: filegroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::filegroup_id
      LOGICAL  , OPTIONAL, INTENT(IN) :: append
      LOGICAL (KIND=C_BOOL) :: append_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      INTEGER  , OPTIONAL, INTENT(IN) :: compression_level
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: convention
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: convention_str
      LOGICAL  , OPTIONAL, INTENT(IN) :: cyclic
      LOGICAL (KIND=C_BOOL) :: cyclic_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: description
      LOGICAL  , OPTIONAL, INTENT(IN) :: enabled
      LOGICAL (KIND=C_BOOL) :: enabled_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: format
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref
      INTEGER  , OPTIONAL, INTENT(IN) :: min_digits
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: mode
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_suffix
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: output_freq
      INTEGER  , OPTIONAL, INTENT(IN) :: output_level
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: par_access
      LOGICAL  , OPTIONAL, INTENT(IN) :: read_metadata_par
      LOGICAL (KIND=C_BOOL) :: read_metadata_par_tmp
      INTEGER  , OPTIONAL, INTENT(IN) :: record_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_end_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_freq
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: split_freq_format
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: split_last_date
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_start_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: sync_freq
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_counter
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_counter_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_stamp_format
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_stamp_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_units
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: timeseries
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: ts_prefix
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: uuid_format
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: uuid_name

      CALL xios(get_filegroup_handle) &
      (filegroup_id,filegroup_hdl)
      CALL xios(set_filegroup_attr_hdl_)   &
      ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
      , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
      , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
      , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
      , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

  END SUBROUTINE xios(set_filegroup_attr)

  SUBROUTINE xios(set_filegroup_attr_hdl)  &
    ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
    , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
    , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
    , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
    , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

    IMPLICIT NONE
      TYPE(txios(filegroup)) , INTENT(IN) :: filegroup_hdl
      LOGICAL  , OPTIONAL, INTENT(IN) :: append
      LOGICAL (KIND=C_BOOL) :: append_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      INTEGER  , OPTIONAL, INTENT(IN) :: compression_level
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: convention
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: convention_str
      LOGICAL  , OPTIONAL, INTENT(IN) :: cyclic
      LOGICAL (KIND=C_BOOL) :: cyclic_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: description
      LOGICAL  , OPTIONAL, INTENT(IN) :: enabled
      LOGICAL (KIND=C_BOOL) :: enabled_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: format
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref
      INTEGER  , OPTIONAL, INTENT(IN) :: min_digits
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: mode
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_suffix
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: output_freq
      INTEGER  , OPTIONAL, INTENT(IN) :: output_level
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: par_access
      LOGICAL  , OPTIONAL, INTENT(IN) :: read_metadata_par
      LOGICAL (KIND=C_BOOL) :: read_metadata_par_tmp
      INTEGER  , OPTIONAL, INTENT(IN) :: record_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_end_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_freq
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: split_freq_format
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: split_last_date
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_start_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: sync_freq
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_counter
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_counter_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_stamp_format
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_stamp_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_units
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: timeseries
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: ts_prefix
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: uuid_format
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: uuid_name

      CALL xios(set_filegroup_attr_hdl_)  &
      ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
      , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
      , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
      , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
      , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

  END SUBROUTINE xios(set_filegroup_attr_hdl)

  SUBROUTINE xios(set_filegroup_attr_hdl_)   &
    ( filegroup_hdl, append_, comment_, compression_level_, convention_, convention_str_, cyclic_  &
    , description_, enabled_, format_, group_ref_, min_digits_, mode_, name_, name_suffix_, output_freq_  &
    , output_level_, par_access_, read_metadata_par_, record_offset_, split_end_offset_, split_freq_  &
    , split_freq_format_, split_last_date_, split_start_offset_, sync_freq_, time_counter_, time_counter_name_  &
    , time_stamp_format_, time_stamp_name_, time_units_, timeseries_, ts_prefix_, type_, uuid_format_  &
    , uuid_name_ )

    IMPLICIT NONE
      TYPE(txios(filegroup)) , INTENT(IN) :: filegroup_hdl
      LOGICAL  , OPTIONAL, INTENT(IN) :: append_
      LOGICAL (KIND=C_BOOL) :: append__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment_
      INTEGER  , OPTIONAL, INTENT(IN) :: compression_level_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: convention_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: convention_str_
      LOGICAL  , OPTIONAL, INTENT(IN) :: cyclic_
      LOGICAL (KIND=C_BOOL) :: cyclic__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: description_
      LOGICAL  , OPTIONAL, INTENT(IN) :: enabled_
      LOGICAL (KIND=C_BOOL) :: enabled__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: format_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref_
      INTEGER  , OPTIONAL, INTENT(IN) :: min_digits_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: mode_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_suffix_
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: output_freq_
      INTEGER  , OPTIONAL, INTENT(IN) :: output_level_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: par_access_
      LOGICAL  , OPTIONAL, INTENT(IN) :: read_metadata_par_
      LOGICAL (KIND=C_BOOL) :: read_metadata_par__tmp
      INTEGER  , OPTIONAL, INTENT(IN) :: record_offset_
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_end_offset_
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_freq_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: split_freq_format_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: split_last_date_
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: split_start_offset_
      TYPE(txios(duration))  , OPTIONAL, INTENT(IN) :: sync_freq_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_counter_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_counter_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_stamp_format_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_stamp_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: time_units_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: timeseries_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: ts_prefix_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: type_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: uuid_format_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: uuid_name_

      IF (PRESENT(append_)) THEN
        append__tmp = append_
        CALL cxios_set_filegroup_append &
      (filegroup_hdl%daddr, append__tmp)
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_set_filegroup_comment &
      (filegroup_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(compression_level_)) THEN
        CALL cxios_set_filegroup_compression_level &
      (filegroup_hdl%daddr, compression_level_)
      ENDIF

      IF (PRESENT(convention_)) THEN
        CALL cxios_set_filegroup_convention &
      (filegroup_hdl%daddr, convention_, len(convention_))
      ENDIF

      IF (PRESENT(convention_str_)) THEN
        CALL cxios_set_filegroup_convention_str &
      (filegroup_hdl%daddr, convention_str_, len(convention_str_))
      ENDIF

      IF (PRESENT(cyclic_)) THEN
        cyclic__tmp = cyclic_
        CALL cxios_set_filegroup_cyclic &
      (filegroup_hdl%daddr, cyclic__tmp)
      ENDIF

      IF (PRESENT(description_)) THEN
        CALL cxios_set_filegroup_description &
      (filegroup_hdl%daddr, description_, len(description_))
      ENDIF

      IF (PRESENT(enabled_)) THEN
        enabled__tmp = enabled_
        CALL cxios_set_filegroup_enabled &
      (filegroup_hdl%daddr, enabled__tmp)
      ENDIF

      IF (PRESENT(format_)) THEN
        CALL cxios_set_filegroup_format &
      (filegroup_hdl%daddr, format_, len(format_))
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        CALL cxios_set_filegroup_group_ref &
      (filegroup_hdl%daddr, group_ref_, len(group_ref_))
      ENDIF

      IF (PRESENT(min_digits_)) THEN
        CALL cxios_set_filegroup_min_digits &
      (filegroup_hdl%daddr, min_digits_)
      ENDIF

      IF (PRESENT(mode_)) THEN
        CALL cxios_set_filegroup_mode &
      (filegroup_hdl%daddr, mode_, len(mode_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_set_filegroup_name &
      (filegroup_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(name_suffix_)) THEN
        CALL cxios_set_filegroup_name_suffix &
      (filegroup_hdl%daddr, name_suffix_, len(name_suffix_))
      ENDIF

      IF (PRESENT(output_freq_)) THEN
        CALL cxios_set_filegroup_output_freq &
      (filegroup_hdl%daddr, output_freq_)
      ENDIF

      IF (PRESENT(output_level_)) THEN
        CALL cxios_set_filegroup_output_level &
      (filegroup_hdl%daddr, output_level_)
      ENDIF

      IF (PRESENT(par_access_)) THEN
        CALL cxios_set_filegroup_par_access &
      (filegroup_hdl%daddr, par_access_, len(par_access_))
      ENDIF

      IF (PRESENT(read_metadata_par_)) THEN
        read_metadata_par__tmp = read_metadata_par_
        CALL cxios_set_filegroup_read_metadata_par &
      (filegroup_hdl%daddr, read_metadata_par__tmp)
      ENDIF

      IF (PRESENT(record_offset_)) THEN
        CALL cxios_set_filegroup_record_offset &
      (filegroup_hdl%daddr, record_offset_)
      ENDIF

      IF (PRESENT(split_end_offset_)) THEN
        CALL cxios_set_filegroup_split_end_offset &
      (filegroup_hdl%daddr, split_end_offset_)
      ENDIF

      IF (PRESENT(split_freq_)) THEN
        CALL cxios_set_filegroup_split_freq &
      (filegroup_hdl%daddr, split_freq_)
      ENDIF

      IF (PRESENT(split_freq_format_)) THEN
        CALL cxios_set_filegroup_split_freq_format &
      (filegroup_hdl%daddr, split_freq_format_, len(split_freq_format_))
      ENDIF

      IF (PRESENT(split_last_date_)) THEN
        CALL cxios_set_filegroup_split_last_date &
      (filegroup_hdl%daddr, split_last_date_, len(split_last_date_))
      ENDIF

      IF (PRESENT(split_start_offset_)) THEN
        CALL cxios_set_filegroup_split_start_offset &
      (filegroup_hdl%daddr, split_start_offset_)
      ENDIF

      IF (PRESENT(sync_freq_)) THEN
        CALL cxios_set_filegroup_sync_freq &
      (filegroup_hdl%daddr, sync_freq_)
      ENDIF

      IF (PRESENT(time_counter_)) THEN
        CALL cxios_set_filegroup_time_counter &
      (filegroup_hdl%daddr, time_counter_, len(time_counter_))
      ENDIF

      IF (PRESENT(time_counter_name_)) THEN
        CALL cxios_set_filegroup_time_counter_name &
      (filegroup_hdl%daddr, time_counter_name_, len(time_counter_name_))
      ENDIF

      IF (PRESENT(time_stamp_format_)) THEN
        CALL cxios_set_filegroup_time_stamp_format &
      (filegroup_hdl%daddr, time_stamp_format_, len(time_stamp_format_))
      ENDIF

      IF (PRESENT(time_stamp_name_)) THEN
        CALL cxios_set_filegroup_time_stamp_name &
      (filegroup_hdl%daddr, time_stamp_name_, len(time_stamp_name_))
      ENDIF

      IF (PRESENT(time_units_)) THEN
        CALL cxios_set_filegroup_time_units &
      (filegroup_hdl%daddr, time_units_, len(time_units_))
      ENDIF

      IF (PRESENT(timeseries_)) THEN
        CALL cxios_set_filegroup_timeseries &
      (filegroup_hdl%daddr, timeseries_, len(timeseries_))
      ENDIF

      IF (PRESENT(ts_prefix_)) THEN
        CALL cxios_set_filegroup_ts_prefix &
      (filegroup_hdl%daddr, ts_prefix_, len(ts_prefix_))
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_set_filegroup_type &
      (filegroup_hdl%daddr, type_, len(type_))
      ENDIF

      IF (PRESENT(uuid_format_)) THEN
        CALL cxios_set_filegroup_uuid_format &
      (filegroup_hdl%daddr, uuid_format_, len(uuid_format_))
      ENDIF

      IF (PRESENT(uuid_name_)) THEN
        CALL cxios_set_filegroup_uuid_name &
      (filegroup_hdl%daddr, uuid_name_, len(uuid_name_))
      ENDIF

  END SUBROUTINE xios(set_filegroup_attr_hdl_)

  SUBROUTINE xios(get_filegroup_attr)  &
    ( filegroup_id, append, comment, compression_level, convention, convention_str, cyclic, description  &
    , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
    , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
    , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
    , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

    IMPLICIT NONE
      TYPE(txios(filegroup))  :: filegroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::filegroup_id
      LOGICAL  , OPTIONAL, INTENT(OUT) :: append
      LOGICAL (KIND=C_BOOL) :: append_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      INTEGER  , OPTIONAL, INTENT(OUT) :: compression_level
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: convention
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: convention_str
      LOGICAL  , OPTIONAL, INTENT(OUT) :: cyclic
      LOGICAL (KIND=C_BOOL) :: cyclic_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: description
      LOGICAL  , OPTIONAL, INTENT(OUT) :: enabled
      LOGICAL (KIND=C_BOOL) :: enabled_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: format
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref
      INTEGER  , OPTIONAL, INTENT(OUT) :: min_digits
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: mode
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_suffix
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: output_freq
      INTEGER  , OPTIONAL, INTENT(OUT) :: output_level
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: par_access
      LOGICAL  , OPTIONAL, INTENT(OUT) :: read_metadata_par
      LOGICAL (KIND=C_BOOL) :: read_metadata_par_tmp
      INTEGER  , OPTIONAL, INTENT(OUT) :: record_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_end_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_freq
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: split_freq_format
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: split_last_date
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_start_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: sync_freq
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_counter
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_counter_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_stamp_format
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_stamp_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_units
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: timeseries
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: ts_prefix
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: uuid_format
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: uuid_name

      CALL xios(get_filegroup_handle) &
      (filegroup_id,filegroup_hdl)
      CALL xios(get_filegroup_attr_hdl_)   &
      ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
      , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
      , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
      , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
      , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

  END SUBROUTINE xios(get_filegroup_attr)

  SUBROUTINE xios(get_filegroup_attr_hdl)  &
    ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
    , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
    , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
    , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
    , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

    IMPLICIT NONE
      TYPE(txios(filegroup)) , INTENT(IN) :: filegroup_hdl
      LOGICAL  , OPTIONAL, INTENT(OUT) :: append
      LOGICAL (KIND=C_BOOL) :: append_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      INTEGER  , OPTIONAL, INTENT(OUT) :: compression_level
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: convention
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: convention_str
      LOGICAL  , OPTIONAL, INTENT(OUT) :: cyclic
      LOGICAL (KIND=C_BOOL) :: cyclic_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: description
      LOGICAL  , OPTIONAL, INTENT(OUT) :: enabled
      LOGICAL (KIND=C_BOOL) :: enabled_tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: format
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref
      INTEGER  , OPTIONAL, INTENT(OUT) :: min_digits
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: mode
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_suffix
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: output_freq
      INTEGER  , OPTIONAL, INTENT(OUT) :: output_level
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: par_access
      LOGICAL  , OPTIONAL, INTENT(OUT) :: read_metadata_par
      LOGICAL (KIND=C_BOOL) :: read_metadata_par_tmp
      INTEGER  , OPTIONAL, INTENT(OUT) :: record_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_end_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_freq
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: split_freq_format
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: split_last_date
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_start_offset
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: sync_freq
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_counter
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_counter_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_stamp_format
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_stamp_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_units
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: timeseries
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: ts_prefix
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: uuid_format
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: uuid_name

      CALL xios(get_filegroup_attr_hdl_)  &
      ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
      , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
      , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
      , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
      , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

  END SUBROUTINE xios(get_filegroup_attr_hdl)

  SUBROUTINE xios(get_filegroup_attr_hdl_)   &
    ( filegroup_hdl, append_, comment_, compression_level_, convention_, convention_str_, cyclic_  &
    , description_, enabled_, format_, group_ref_, min_digits_, mode_, name_, name_suffix_, output_freq_  &
    , output_level_, par_access_, read_metadata_par_, record_offset_, split_end_offset_, split_freq_  &
    , split_freq_format_, split_last_date_, split_start_offset_, sync_freq_, time_counter_, time_counter_name_  &
    , time_stamp_format_, time_stamp_name_, time_units_, timeseries_, ts_prefix_, type_, uuid_format_  &
    , uuid_name_ )

    IMPLICIT NONE
      TYPE(txios(filegroup)) , INTENT(IN) :: filegroup_hdl
      LOGICAL  , OPTIONAL, INTENT(OUT) :: append_
      LOGICAL (KIND=C_BOOL) :: append__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment_
      INTEGER  , OPTIONAL, INTENT(OUT) :: compression_level_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: convention_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: convention_str_
      LOGICAL  , OPTIONAL, INTENT(OUT) :: cyclic_
      LOGICAL (KIND=C_BOOL) :: cyclic__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: description_
      LOGICAL  , OPTIONAL, INTENT(OUT) :: enabled_
      LOGICAL (KIND=C_BOOL) :: enabled__tmp
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: format_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref_
      INTEGER  , OPTIONAL, INTENT(OUT) :: min_digits_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: mode_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_suffix_
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: output_freq_
      INTEGER  , OPTIONAL, INTENT(OUT) :: output_level_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: par_access_
      LOGICAL  , OPTIONAL, INTENT(OUT) :: read_metadata_par_
      LOGICAL (KIND=C_BOOL) :: read_metadata_par__tmp
      INTEGER  , OPTIONAL, INTENT(OUT) :: record_offset_
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_end_offset_
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_freq_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: split_freq_format_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: split_last_date_
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: split_start_offset_
      TYPE(txios(duration))  , OPTIONAL, INTENT(OUT) :: sync_freq_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_counter_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_counter_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_stamp_format_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_stamp_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: time_units_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: timeseries_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: ts_prefix_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: type_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: uuid_format_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: uuid_name_

      IF (PRESENT(append_)) THEN
        CALL cxios_get_filegroup_append &
      (filegroup_hdl%daddr, append__tmp)
        append_ = append__tmp
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_get_filegroup_comment &
      (filegroup_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(compression_level_)) THEN
        CALL cxios_get_filegroup_compression_level &
      (filegroup_hdl%daddr, compression_level_)
      ENDIF

      IF (PRESENT(convention_)) THEN
        CALL cxios_get_filegroup_convention &
      (filegroup_hdl%daddr, convention_, len(convention_))
      ENDIF

      IF (PRESENT(convention_str_)) THEN
        CALL cxios_get_filegroup_convention_str &
      (filegroup_hdl%daddr, convention_str_, len(convention_str_))
      ENDIF

      IF (PRESENT(cyclic_)) THEN
        CALL cxios_get_filegroup_cyclic &
      (filegroup_hdl%daddr, cyclic__tmp)
        cyclic_ = cyclic__tmp
      ENDIF

      IF (PRESENT(description_)) THEN
        CALL cxios_get_filegroup_description &
      (filegroup_hdl%daddr, description_, len(description_))
      ENDIF

      IF (PRESENT(enabled_)) THEN
        CALL cxios_get_filegroup_enabled &
      (filegroup_hdl%daddr, enabled__tmp)
        enabled_ = enabled__tmp
      ENDIF

      IF (PRESENT(format_)) THEN
        CALL cxios_get_filegroup_format &
      (filegroup_hdl%daddr, format_, len(format_))
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        CALL cxios_get_filegroup_group_ref &
      (filegroup_hdl%daddr, group_ref_, len(group_ref_))
      ENDIF

      IF (PRESENT(min_digits_)) THEN
        CALL cxios_get_filegroup_min_digits &
      (filegroup_hdl%daddr, min_digits_)
      ENDIF

      IF (PRESENT(mode_)) THEN
        CALL cxios_get_filegroup_mode &
      (filegroup_hdl%daddr, mode_, len(mode_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_get_filegroup_name &
      (filegroup_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(name_suffix_)) THEN
        CALL cxios_get_filegroup_name_suffix &
      (filegroup_hdl%daddr, name_suffix_, len(name_suffix_))
      ENDIF

      IF (PRESENT(output_freq_)) THEN
        CALL cxios_get_filegroup_output_freq &
      (filegroup_hdl%daddr, output_freq_)
      ENDIF

      IF (PRESENT(output_level_)) THEN
        CALL cxios_get_filegroup_output_level &
      (filegroup_hdl%daddr, output_level_)
      ENDIF

      IF (PRESENT(par_access_)) THEN
        CALL cxios_get_filegroup_par_access &
      (filegroup_hdl%daddr, par_access_, len(par_access_))
      ENDIF

      IF (PRESENT(read_metadata_par_)) THEN
        CALL cxios_get_filegroup_read_metadata_par &
      (filegroup_hdl%daddr, read_metadata_par__tmp)
        read_metadata_par_ = read_metadata_par__tmp
      ENDIF

      IF (PRESENT(record_offset_)) THEN
        CALL cxios_get_filegroup_record_offset &
      (filegroup_hdl%daddr, record_offset_)
      ENDIF

      IF (PRESENT(split_end_offset_)) THEN
        CALL cxios_get_filegroup_split_end_offset &
      (filegroup_hdl%daddr, split_end_offset_)
      ENDIF

      IF (PRESENT(split_freq_)) THEN
        CALL cxios_get_filegroup_split_freq &
      (filegroup_hdl%daddr, split_freq_)
      ENDIF

      IF (PRESENT(split_freq_format_)) THEN
        CALL cxios_get_filegroup_split_freq_format &
      (filegroup_hdl%daddr, split_freq_format_, len(split_freq_format_))
      ENDIF

      IF (PRESENT(split_last_date_)) THEN
        CALL cxios_get_filegroup_split_last_date &
      (filegroup_hdl%daddr, split_last_date_, len(split_last_date_))
      ENDIF

      IF (PRESENT(split_start_offset_)) THEN
        CALL cxios_get_filegroup_split_start_offset &
      (filegroup_hdl%daddr, split_start_offset_)
      ENDIF

      IF (PRESENT(sync_freq_)) THEN
        CALL cxios_get_filegroup_sync_freq &
      (filegroup_hdl%daddr, sync_freq_)
      ENDIF

      IF (PRESENT(time_counter_)) THEN
        CALL cxios_get_filegroup_time_counter &
      (filegroup_hdl%daddr, time_counter_, len(time_counter_))
      ENDIF

      IF (PRESENT(time_counter_name_)) THEN
        CALL cxios_get_filegroup_time_counter_name &
      (filegroup_hdl%daddr, time_counter_name_, len(time_counter_name_))
      ENDIF

      IF (PRESENT(time_stamp_format_)) THEN
        CALL cxios_get_filegroup_time_stamp_format &
      (filegroup_hdl%daddr, time_stamp_format_, len(time_stamp_format_))
      ENDIF

      IF (PRESENT(time_stamp_name_)) THEN
        CALL cxios_get_filegroup_time_stamp_name &
      (filegroup_hdl%daddr, time_stamp_name_, len(time_stamp_name_))
      ENDIF

      IF (PRESENT(time_units_)) THEN
        CALL cxios_get_filegroup_time_units &
      (filegroup_hdl%daddr, time_units_, len(time_units_))
      ENDIF

      IF (PRESENT(timeseries_)) THEN
        CALL cxios_get_filegroup_timeseries &
      (filegroup_hdl%daddr, timeseries_, len(timeseries_))
      ENDIF

      IF (PRESENT(ts_prefix_)) THEN
        CALL cxios_get_filegroup_ts_prefix &
      (filegroup_hdl%daddr, ts_prefix_, len(ts_prefix_))
      ENDIF

      IF (PRESENT(type_)) THEN
        CALL cxios_get_filegroup_type &
      (filegroup_hdl%daddr, type_, len(type_))
      ENDIF

      IF (PRESENT(uuid_format_)) THEN
        CALL cxios_get_filegroup_uuid_format &
      (filegroup_hdl%daddr, uuid_format_, len(uuid_format_))
      ENDIF

      IF (PRESENT(uuid_name_)) THEN
        CALL cxios_get_filegroup_uuid_name &
      (filegroup_hdl%daddr, uuid_name_, len(uuid_name_))
      ENDIF

  END SUBROUTINE xios(get_filegroup_attr_hdl_)

  SUBROUTINE xios(is_defined_filegroup_attr)  &
    ( filegroup_id, append, comment, compression_level, convention, convention_str, cyclic, description  &
    , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
    , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
    , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
    , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

    IMPLICIT NONE
      TYPE(txios(filegroup))  :: filegroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::filegroup_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: append
      LOGICAL(KIND=C_BOOL) :: append_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: compression_level
      LOGICAL(KIND=C_BOOL) :: compression_level_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: convention
      LOGICAL(KIND=C_BOOL) :: convention_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: convention_str
      LOGICAL(KIND=C_BOOL) :: convention_str_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: cyclic
      LOGICAL(KIND=C_BOOL) :: cyclic_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: description
      LOGICAL(KIND=C_BOOL) :: description_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: enabled
      LOGICAL(KIND=C_BOOL) :: enabled_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: format
      LOGICAL(KIND=C_BOOL) :: format_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL(KIND=C_BOOL) :: group_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: min_digits
      LOGICAL(KIND=C_BOOL) :: min_digits_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mode
      LOGICAL(KIND=C_BOOL) :: mode_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_suffix
      LOGICAL(KIND=C_BOOL) :: name_suffix_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_freq
      LOGICAL(KIND=C_BOOL) :: output_freq_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_level
      LOGICAL(KIND=C_BOOL) :: output_level_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: par_access
      LOGICAL(KIND=C_BOOL) :: par_access_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: read_metadata_par
      LOGICAL(KIND=C_BOOL) :: read_metadata_par_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: record_offset
      LOGICAL(KIND=C_BOOL) :: record_offset_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_end_offset
      LOGICAL(KIND=C_BOOL) :: split_end_offset_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_freq
      LOGICAL(KIND=C_BOOL) :: split_freq_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_freq_format
      LOGICAL(KIND=C_BOOL) :: split_freq_format_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_last_date
      LOGICAL(KIND=C_BOOL) :: split_last_date_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_start_offset
      LOGICAL(KIND=C_BOOL) :: split_start_offset_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: sync_freq
      LOGICAL(KIND=C_BOOL) :: sync_freq_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_counter
      LOGICAL(KIND=C_BOOL) :: time_counter_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_counter_name
      LOGICAL(KIND=C_BOOL) :: time_counter_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_stamp_format
      LOGICAL(KIND=C_BOOL) :: time_stamp_format_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_stamp_name
      LOGICAL(KIND=C_BOOL) :: time_stamp_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_units
      LOGICAL(KIND=C_BOOL) :: time_units_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: timeseries
      LOGICAL(KIND=C_BOOL) :: timeseries_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ts_prefix
      LOGICAL(KIND=C_BOOL) :: ts_prefix_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: uuid_format
      LOGICAL(KIND=C_BOOL) :: uuid_format_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: uuid_name
      LOGICAL(KIND=C_BOOL) :: uuid_name_tmp

      CALL xios(get_filegroup_handle) &
      (filegroup_id,filegroup_hdl)
      CALL xios(is_defined_filegroup_attr_hdl_)   &
      ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
      , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
      , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
      , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
      , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

  END SUBROUTINE xios(is_defined_filegroup_attr)

  SUBROUTINE xios(is_defined_filegroup_attr_hdl)  &
    ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
    , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
    , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
    , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
    , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

    IMPLICIT NONE
      TYPE(txios(filegroup)) , INTENT(IN) :: filegroup_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: append
      LOGICAL(KIND=C_BOOL) :: append_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: compression_level
      LOGICAL(KIND=C_BOOL) :: compression_level_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: convention
      LOGICAL(KIND=C_BOOL) :: convention_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: convention_str
      LOGICAL(KIND=C_BOOL) :: convention_str_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: cyclic
      LOGICAL(KIND=C_BOOL) :: cyclic_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: description
      LOGICAL(KIND=C_BOOL) :: description_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: enabled
      LOGICAL(KIND=C_BOOL) :: enabled_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: format
      LOGICAL(KIND=C_BOOL) :: format_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL(KIND=C_BOOL) :: group_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: min_digits
      LOGICAL(KIND=C_BOOL) :: min_digits_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mode
      LOGICAL(KIND=C_BOOL) :: mode_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_suffix
      LOGICAL(KIND=C_BOOL) :: name_suffix_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_freq
      LOGICAL(KIND=C_BOOL) :: output_freq_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_level
      LOGICAL(KIND=C_BOOL) :: output_level_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: par_access
      LOGICAL(KIND=C_BOOL) :: par_access_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: read_metadata_par
      LOGICAL(KIND=C_BOOL) :: read_metadata_par_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: record_offset
      LOGICAL(KIND=C_BOOL) :: record_offset_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_end_offset
      LOGICAL(KIND=C_BOOL) :: split_end_offset_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_freq
      LOGICAL(KIND=C_BOOL) :: split_freq_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_freq_format
      LOGICAL(KIND=C_BOOL) :: split_freq_format_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_last_date
      LOGICAL(KIND=C_BOOL) :: split_last_date_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_start_offset
      LOGICAL(KIND=C_BOOL) :: split_start_offset_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: sync_freq
      LOGICAL(KIND=C_BOOL) :: sync_freq_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_counter
      LOGICAL(KIND=C_BOOL) :: time_counter_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_counter_name
      LOGICAL(KIND=C_BOOL) :: time_counter_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_stamp_format
      LOGICAL(KIND=C_BOOL) :: time_stamp_format_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_stamp_name
      LOGICAL(KIND=C_BOOL) :: time_stamp_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_units
      LOGICAL(KIND=C_BOOL) :: time_units_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: timeseries
      LOGICAL(KIND=C_BOOL) :: timeseries_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ts_prefix
      LOGICAL(KIND=C_BOOL) :: ts_prefix_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type
      LOGICAL(KIND=C_BOOL) :: type_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: uuid_format
      LOGICAL(KIND=C_BOOL) :: uuid_format_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: uuid_name
      LOGICAL(KIND=C_BOOL) :: uuid_name_tmp

      CALL xios(is_defined_filegroup_attr_hdl_)  &
      ( filegroup_hdl, append, comment, compression_level, convention, convention_str, cyclic, description  &
      , enabled, format, group_ref, min_digits, mode, name, name_suffix, output_freq, output_level  &
      , par_access, read_metadata_par, record_offset, split_end_offset, split_freq, split_freq_format  &
      , split_last_date, split_start_offset, sync_freq, time_counter, time_counter_name, time_stamp_format  &
      , time_stamp_name, time_units, timeseries, ts_prefix, type, uuid_format, uuid_name )

  END SUBROUTINE xios(is_defined_filegroup_attr_hdl)

  SUBROUTINE xios(is_defined_filegroup_attr_hdl_)   &
    ( filegroup_hdl, append_, comment_, compression_level_, convention_, convention_str_, cyclic_  &
    , description_, enabled_, format_, group_ref_, min_digits_, mode_, name_, name_suffix_, output_freq_  &
    , output_level_, par_access_, read_metadata_par_, record_offset_, split_end_offset_, split_freq_  &
    , split_freq_format_, split_last_date_, split_start_offset_, sync_freq_, time_counter_, time_counter_name_  &
    , time_stamp_format_, time_stamp_name_, time_units_, timeseries_, ts_prefix_, type_, uuid_format_  &
    , uuid_name_ )

    IMPLICIT NONE
      TYPE(txios(filegroup)) , INTENT(IN) :: filegroup_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: append_
      LOGICAL(KIND=C_BOOL) :: append__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment_
      LOGICAL(KIND=C_BOOL) :: comment__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: compression_level_
      LOGICAL(KIND=C_BOOL) :: compression_level__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: convention_
      LOGICAL(KIND=C_BOOL) :: convention__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: convention_str_
      LOGICAL(KIND=C_BOOL) :: convention_str__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: cyclic_
      LOGICAL(KIND=C_BOOL) :: cyclic__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: description_
      LOGICAL(KIND=C_BOOL) :: description__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: enabled_
      LOGICAL(KIND=C_BOOL) :: enabled__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: format_
      LOGICAL(KIND=C_BOOL) :: format__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref_
      LOGICAL(KIND=C_BOOL) :: group_ref__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: min_digits_
      LOGICAL(KIND=C_BOOL) :: min_digits__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: mode_
      LOGICAL(KIND=C_BOOL) :: mode__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_
      LOGICAL(KIND=C_BOOL) :: name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_suffix_
      LOGICAL(KIND=C_BOOL) :: name_suffix__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_freq_
      LOGICAL(KIND=C_BOOL) :: output_freq__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: output_level_
      LOGICAL(KIND=C_BOOL) :: output_level__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: par_access_
      LOGICAL(KIND=C_BOOL) :: par_access__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: read_metadata_par_
      LOGICAL(KIND=C_BOOL) :: read_metadata_par__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: record_offset_
      LOGICAL(KIND=C_BOOL) :: record_offset__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_end_offset_
      LOGICAL(KIND=C_BOOL) :: split_end_offset__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_freq_
      LOGICAL(KIND=C_BOOL) :: split_freq__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_freq_format_
      LOGICAL(KIND=C_BOOL) :: split_freq_format__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_last_date_
      LOGICAL(KIND=C_BOOL) :: split_last_date__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: split_start_offset_
      LOGICAL(KIND=C_BOOL) :: split_start_offset__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: sync_freq_
      LOGICAL(KIND=C_BOOL) :: sync_freq__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_counter_
      LOGICAL(KIND=C_BOOL) :: time_counter__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_counter_name_
      LOGICAL(KIND=C_BOOL) :: time_counter_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_stamp_format_
      LOGICAL(KIND=C_BOOL) :: time_stamp_format__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_stamp_name_
      LOGICAL(KIND=C_BOOL) :: time_stamp_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: time_units_
      LOGICAL(KIND=C_BOOL) :: time_units__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: timeseries_
      LOGICAL(KIND=C_BOOL) :: timeseries__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: ts_prefix_
      LOGICAL(KIND=C_BOOL) :: ts_prefix__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: type_
      LOGICAL(KIND=C_BOOL) :: type__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: uuid_format_
      LOGICAL(KIND=C_BOOL) :: uuid_format__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: uuid_name_
      LOGICAL(KIND=C_BOOL) :: uuid_name__tmp

      IF (PRESENT(append_)) THEN
        append__tmp = cxios_is_defined_filegroup_append &
      (filegroup_hdl%daddr)
        append_ = append__tmp
      ENDIF

      IF (PRESENT(comment_)) THEN
        comment__tmp = cxios_is_defined_filegroup_comment &
      (filegroup_hdl%daddr)
        comment_ = comment__tmp
      ENDIF

      IF (PRESENT(compression_level_)) THEN
        compression_level__tmp = cxios_is_defined_filegroup_compression_level &
      (filegroup_hdl%daddr)
        compression_level_ = compression_level__tmp
      ENDIF

      IF (PRESENT(convention_)) THEN
        convention__tmp = cxios_is_defined_filegroup_convention &
      (filegroup_hdl%daddr)
        convention_ = convention__tmp
      ENDIF

      IF (PRESENT(convention_str_)) THEN
        convention_str__tmp = cxios_is_defined_filegroup_convention_str &
      (filegroup_hdl%daddr)
        convention_str_ = convention_str__tmp
      ENDIF

      IF (PRESENT(cyclic_)) THEN
        cyclic__tmp = cxios_is_defined_filegroup_cyclic &
      (filegroup_hdl%daddr)
        cyclic_ = cyclic__tmp
      ENDIF

      IF (PRESENT(description_)) THEN
        description__tmp = cxios_is_defined_filegroup_description &
      (filegroup_hdl%daddr)
        description_ = description__tmp
      ENDIF

      IF (PRESENT(enabled_)) THEN
        enabled__tmp = cxios_is_defined_filegroup_enabled &
      (filegroup_hdl%daddr)
        enabled_ = enabled__tmp
      ENDIF

      IF (PRESENT(format_)) THEN
        format__tmp = cxios_is_defined_filegroup_format &
      (filegroup_hdl%daddr)
        format_ = format__tmp
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        group_ref__tmp = cxios_is_defined_filegroup_group_ref &
      (filegroup_hdl%daddr)
        group_ref_ = group_ref__tmp
      ENDIF

      IF (PRESENT(min_digits_)) THEN
        min_digits__tmp = cxios_is_defined_filegroup_min_digits &
      (filegroup_hdl%daddr)
        min_digits_ = min_digits__tmp
      ENDIF

      IF (PRESENT(mode_)) THEN
        mode__tmp = cxios_is_defined_filegroup_mode &
      (filegroup_hdl%daddr)
        mode_ = mode__tmp
      ENDIF

      IF (PRESENT(name_)) THEN
        name__tmp = cxios_is_defined_filegroup_name &
      (filegroup_hdl%daddr)
        name_ = name__tmp
      ENDIF

      IF (PRESENT(name_suffix_)) THEN
        name_suffix__tmp = cxios_is_defined_filegroup_name_suffix &
      (filegroup_hdl%daddr)
        name_suffix_ = name_suffix__tmp
      ENDIF

      IF (PRESENT(output_freq_)) THEN
        output_freq__tmp = cxios_is_defined_filegroup_output_freq &
      (filegroup_hdl%daddr)
        output_freq_ = output_freq__tmp
      ENDIF

      IF (PRESENT(output_level_)) THEN
        output_level__tmp = cxios_is_defined_filegroup_output_level &
      (filegroup_hdl%daddr)
        output_level_ = output_level__tmp
      ENDIF

      IF (PRESENT(par_access_)) THEN
        par_access__tmp = cxios_is_defined_filegroup_par_access &
      (filegroup_hdl%daddr)
        par_access_ = par_access__tmp
      ENDIF

      IF (PRESENT(read_metadata_par_)) THEN
        read_metadata_par__tmp = cxios_is_defined_filegroup_read_metadata_par &
      (filegroup_hdl%daddr)
        read_metadata_par_ = read_metadata_par__tmp
      ENDIF

      IF (PRESENT(record_offset_)) THEN
        record_offset__tmp = cxios_is_defined_filegroup_record_offset &
      (filegroup_hdl%daddr)
        record_offset_ = record_offset__tmp
      ENDIF

      IF (PRESENT(split_end_offset_)) THEN
        split_end_offset__tmp = cxios_is_defined_filegroup_split_end_offset &
      (filegroup_hdl%daddr)
        split_end_offset_ = split_end_offset__tmp
      ENDIF

      IF (PRESENT(split_freq_)) THEN
        split_freq__tmp = cxios_is_defined_filegroup_split_freq &
      (filegroup_hdl%daddr)
        split_freq_ = split_freq__tmp
      ENDIF

      IF (PRESENT(split_freq_format_)) THEN
        split_freq_format__tmp = cxios_is_defined_filegroup_split_freq_format &
      (filegroup_hdl%daddr)
        split_freq_format_ = split_freq_format__tmp
      ENDIF

      IF (PRESENT(split_last_date_)) THEN
        split_last_date__tmp = cxios_is_defined_filegroup_split_last_date &
      (filegroup_hdl%daddr)
        split_last_date_ = split_last_date__tmp
      ENDIF

      IF (PRESENT(split_start_offset_)) THEN
        split_start_offset__tmp = cxios_is_defined_filegroup_split_start_offset &
      (filegroup_hdl%daddr)
        split_start_offset_ = split_start_offset__tmp
      ENDIF

      IF (PRESENT(sync_freq_)) THEN
        sync_freq__tmp = cxios_is_defined_filegroup_sync_freq &
      (filegroup_hdl%daddr)
        sync_freq_ = sync_freq__tmp
      ENDIF

      IF (PRESENT(time_counter_)) THEN
        time_counter__tmp = cxios_is_defined_filegroup_time_counter &
      (filegroup_hdl%daddr)
        time_counter_ = time_counter__tmp
      ENDIF

      IF (PRESENT(time_counter_name_)) THEN
        time_counter_name__tmp = cxios_is_defined_filegroup_time_counter_name &
      (filegroup_hdl%daddr)
        time_counter_name_ = time_counter_name__tmp
      ENDIF

      IF (PRESENT(time_stamp_format_)) THEN
        time_stamp_format__tmp = cxios_is_defined_filegroup_time_stamp_format &
      (filegroup_hdl%daddr)
        time_stamp_format_ = time_stamp_format__tmp
      ENDIF

      IF (PRESENT(time_stamp_name_)) THEN
        time_stamp_name__tmp = cxios_is_defined_filegroup_time_stamp_name &
      (filegroup_hdl%daddr)
        time_stamp_name_ = time_stamp_name__tmp
      ENDIF

      IF (PRESENT(time_units_)) THEN
        time_units__tmp = cxios_is_defined_filegroup_time_units &
      (filegroup_hdl%daddr)
        time_units_ = time_units__tmp
      ENDIF

      IF (PRESENT(timeseries_)) THEN
        timeseries__tmp = cxios_is_defined_filegroup_timeseries &
      (filegroup_hdl%daddr)
        timeseries_ = timeseries__tmp
      ENDIF

      IF (PRESENT(ts_prefix_)) THEN
        ts_prefix__tmp = cxios_is_defined_filegroup_ts_prefix &
      (filegroup_hdl%daddr)
        ts_prefix_ = ts_prefix__tmp
      ENDIF

      IF (PRESENT(type_)) THEN
        type__tmp = cxios_is_defined_filegroup_type &
      (filegroup_hdl%daddr)
        type_ = type__tmp
      ENDIF

      IF (PRESENT(uuid_format_)) THEN
        uuid_format__tmp = cxios_is_defined_filegroup_uuid_format &
      (filegroup_hdl%daddr)
        uuid_format_ = uuid_format__tmp
      ENDIF

      IF (PRESENT(uuid_name_)) THEN
        uuid_name__tmp = cxios_is_defined_filegroup_uuid_name &
      (filegroup_hdl%daddr)
        uuid_name_ = uuid_name__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_filegroup_attr_hdl_)

END MODULE ifilegroup_attr
