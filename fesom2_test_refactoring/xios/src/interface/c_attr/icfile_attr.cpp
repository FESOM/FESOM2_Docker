/* ************************************************************************** *
 *               Interface auto generated - do not modify                     *
 * ************************************************************************** */

#include <boost/multi_array.hpp>
#include "xios.hpp"
#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"
#include "icutil.hpp"
#include "icdate.hpp"
#include "timer.hpp"
#include "node_type.hpp"

extern "C"
{
  typedef xios::CFile* file_Ptr;

  void cxios_set_file_append(file_Ptr file_hdl, bool append)
  {
    CTimer::get("XIOS").resume();
    file_hdl->append.setValue(append);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_append(file_Ptr file_hdl, bool* append)
  {
    CTimer::get("XIOS").resume();
    *append = file_hdl->append.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_append(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->append.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_comment(file_Ptr file_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_comment(file_Ptr file_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_file_comment(file_Ptr file_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_comment(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_compression_level(file_Ptr file_hdl, int compression_level)
  {
    CTimer::get("XIOS").resume();
    file_hdl->compression_level.setValue(compression_level);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_compression_level(file_Ptr file_hdl, int* compression_level)
  {
    CTimer::get("XIOS").resume();
    *compression_level = file_hdl->compression_level.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_compression_level(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->compression_level.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_convention(file_Ptr file_hdl, const char * convention, int convention_size)
  {
    std::string convention_str;
    if (!cstr2string(convention, convention_size, convention_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->convention.fromString(convention_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_convention(file_Ptr file_hdl, char * convention, int convention_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->convention.getInheritedStringValue(), convention, convention_size))
      ERROR("void cxios_get_file_convention(file_Ptr file_hdl, char * convention, int convention_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_convention(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->convention.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_convention_str(file_Ptr file_hdl, const char * convention_str, int convention_str_size)
  {
    std::string convention_str_str;
    if (!cstr2string(convention_str, convention_str_size, convention_str_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->convention_str.setValue(convention_str_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_convention_str(file_Ptr file_hdl, char * convention_str, int convention_str_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->convention_str.getInheritedValue(), convention_str, convention_str_size))
      ERROR("void cxios_get_file_convention_str(file_Ptr file_hdl, char * convention_str, int convention_str_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_convention_str(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->convention_str.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_cyclic(file_Ptr file_hdl, bool cyclic)
  {
    CTimer::get("XIOS").resume();
    file_hdl->cyclic.setValue(cyclic);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_cyclic(file_Ptr file_hdl, bool* cyclic)
  {
    CTimer::get("XIOS").resume();
    *cyclic = file_hdl->cyclic.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_cyclic(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->cyclic.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_description(file_Ptr file_hdl, const char * description, int description_size)
  {
    std::string description_str;
    if (!cstr2string(description, description_size, description_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->description.setValue(description_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_description(file_Ptr file_hdl, char * description, int description_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->description.getInheritedValue(), description, description_size))
      ERROR("void cxios_get_file_description(file_Ptr file_hdl, char * description, int description_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_description(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->description.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_enabled(file_Ptr file_hdl, bool enabled)
  {
    CTimer::get("XIOS").resume();
    file_hdl->enabled.setValue(enabled);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_enabled(file_Ptr file_hdl, bool* enabled)
  {
    CTimer::get("XIOS").resume();
    *enabled = file_hdl->enabled.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_enabled(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->enabled.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_format(file_Ptr file_hdl, const char * format, int format_size)
  {
    std::string format_str;
    if (!cstr2string(format, format_size, format_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->format.fromString(format_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_format(file_Ptr file_hdl, char * format, int format_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->format.getInheritedStringValue(), format, format_size))
      ERROR("void cxios_get_file_format(file_Ptr file_hdl, char * format, int format_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_format(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->format.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_min_digits(file_Ptr file_hdl, int min_digits)
  {
    CTimer::get("XIOS").resume();
    file_hdl->min_digits.setValue(min_digits);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_min_digits(file_Ptr file_hdl, int* min_digits)
  {
    CTimer::get("XIOS").resume();
    *min_digits = file_hdl->min_digits.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_min_digits(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->min_digits.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_mode(file_Ptr file_hdl, const char * mode, int mode_size)
  {
    std::string mode_str;
    if (!cstr2string(mode, mode_size, mode_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->mode.fromString(mode_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_mode(file_Ptr file_hdl, char * mode, int mode_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->mode.getInheritedStringValue(), mode, mode_size))
      ERROR("void cxios_get_file_mode(file_Ptr file_hdl, char * mode, int mode_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_mode(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->mode.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_name(file_Ptr file_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_name(file_Ptr file_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_file_name(file_Ptr file_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_name(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_name_suffix(file_Ptr file_hdl, const char * name_suffix, int name_suffix_size)
  {
    std::string name_suffix_str;
    if (!cstr2string(name_suffix, name_suffix_size, name_suffix_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->name_suffix.setValue(name_suffix_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_name_suffix(file_Ptr file_hdl, char * name_suffix, int name_suffix_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->name_suffix.getInheritedValue(), name_suffix, name_suffix_size))
      ERROR("void cxios_get_file_name_suffix(file_Ptr file_hdl, char * name_suffix, int name_suffix_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_name_suffix(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->name_suffix.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_output_freq(file_Ptr file_hdl, cxios_duration output_freq_c)
  {
    CTimer::get("XIOS").resume();
    file_hdl->output_freq.allocate();
    CDuration& output_freq = file_hdl->output_freq.get();
    output_freq.year = output_freq_c.year;
    output_freq.month = output_freq_c.month;
    output_freq.day = output_freq_c.day;
    output_freq.hour = output_freq_c.hour;
    output_freq.minute = output_freq_c.minute;
    output_freq.second = output_freq_c.second;
    output_freq.timestep = output_freq_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_output_freq(file_Ptr file_hdl, cxios_duration* output_freq_c)
  {
    CTimer::get("XIOS").resume();
    CDuration output_freq = file_hdl->output_freq.getInheritedValue();
    output_freq_c->year = output_freq.year;
    output_freq_c->month = output_freq.month;
    output_freq_c->day = output_freq.day;
    output_freq_c->hour = output_freq.hour;
    output_freq_c->minute = output_freq.minute;
    output_freq_c->second = output_freq.second;
    output_freq_c->timestep = output_freq.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_output_freq(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->output_freq.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_output_level(file_Ptr file_hdl, int output_level)
  {
    CTimer::get("XIOS").resume();
    file_hdl->output_level.setValue(output_level);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_output_level(file_Ptr file_hdl, int* output_level)
  {
    CTimer::get("XIOS").resume();
    *output_level = file_hdl->output_level.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_output_level(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->output_level.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_par_access(file_Ptr file_hdl, const char * par_access, int par_access_size)
  {
    std::string par_access_str;
    if (!cstr2string(par_access, par_access_size, par_access_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->par_access.fromString(par_access_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_par_access(file_Ptr file_hdl, char * par_access, int par_access_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->par_access.getInheritedStringValue(), par_access, par_access_size))
      ERROR("void cxios_get_file_par_access(file_Ptr file_hdl, char * par_access, int par_access_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_par_access(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->par_access.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_read_metadata_par(file_Ptr file_hdl, bool read_metadata_par)
  {
    CTimer::get("XIOS").resume();
    file_hdl->read_metadata_par.setValue(read_metadata_par);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_read_metadata_par(file_Ptr file_hdl, bool* read_metadata_par)
  {
    CTimer::get("XIOS").resume();
    *read_metadata_par = file_hdl->read_metadata_par.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_read_metadata_par(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->read_metadata_par.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_record_offset(file_Ptr file_hdl, int record_offset)
  {
    CTimer::get("XIOS").resume();
    file_hdl->record_offset.setValue(record_offset);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_record_offset(file_Ptr file_hdl, int* record_offset)
  {
    CTimer::get("XIOS").resume();
    *record_offset = file_hdl->record_offset.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_record_offset(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->record_offset.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_split_end_offset(file_Ptr file_hdl, cxios_duration split_end_offset_c)
  {
    CTimer::get("XIOS").resume();
    file_hdl->split_end_offset.allocate();
    CDuration& split_end_offset = file_hdl->split_end_offset.get();
    split_end_offset.year = split_end_offset_c.year;
    split_end_offset.month = split_end_offset_c.month;
    split_end_offset.day = split_end_offset_c.day;
    split_end_offset.hour = split_end_offset_c.hour;
    split_end_offset.minute = split_end_offset_c.minute;
    split_end_offset.second = split_end_offset_c.second;
    split_end_offset.timestep = split_end_offset_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_split_end_offset(file_Ptr file_hdl, cxios_duration* split_end_offset_c)
  {
    CTimer::get("XIOS").resume();
    CDuration split_end_offset = file_hdl->split_end_offset.getInheritedValue();
    split_end_offset_c->year = split_end_offset.year;
    split_end_offset_c->month = split_end_offset.month;
    split_end_offset_c->day = split_end_offset.day;
    split_end_offset_c->hour = split_end_offset.hour;
    split_end_offset_c->minute = split_end_offset.minute;
    split_end_offset_c->second = split_end_offset.second;
    split_end_offset_c->timestep = split_end_offset.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_split_end_offset(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->split_end_offset.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_split_freq(file_Ptr file_hdl, cxios_duration split_freq_c)
  {
    CTimer::get("XIOS").resume();
    file_hdl->split_freq.allocate();
    CDuration& split_freq = file_hdl->split_freq.get();
    split_freq.year = split_freq_c.year;
    split_freq.month = split_freq_c.month;
    split_freq.day = split_freq_c.day;
    split_freq.hour = split_freq_c.hour;
    split_freq.minute = split_freq_c.minute;
    split_freq.second = split_freq_c.second;
    split_freq.timestep = split_freq_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_split_freq(file_Ptr file_hdl, cxios_duration* split_freq_c)
  {
    CTimer::get("XIOS").resume();
    CDuration split_freq = file_hdl->split_freq.getInheritedValue();
    split_freq_c->year = split_freq.year;
    split_freq_c->month = split_freq.month;
    split_freq_c->day = split_freq.day;
    split_freq_c->hour = split_freq.hour;
    split_freq_c->minute = split_freq.minute;
    split_freq_c->second = split_freq.second;
    split_freq_c->timestep = split_freq.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_split_freq(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->split_freq.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_split_freq_format(file_Ptr file_hdl, const char * split_freq_format, int split_freq_format_size)
  {
    std::string split_freq_format_str;
    if (!cstr2string(split_freq_format, split_freq_format_size, split_freq_format_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->split_freq_format.setValue(split_freq_format_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_split_freq_format(file_Ptr file_hdl, char * split_freq_format, int split_freq_format_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->split_freq_format.getInheritedValue(), split_freq_format, split_freq_format_size))
      ERROR("void cxios_get_file_split_freq_format(file_Ptr file_hdl, char * split_freq_format, int split_freq_format_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_split_freq_format(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->split_freq_format.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_split_last_date(file_Ptr file_hdl, const char * split_last_date, int split_last_date_size)
  {
    std::string split_last_date_str;
    if (!cstr2string(split_last_date, split_last_date_size, split_last_date_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->split_last_date.setValue(split_last_date_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_split_last_date(file_Ptr file_hdl, char * split_last_date, int split_last_date_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->split_last_date.getInheritedValue(), split_last_date, split_last_date_size))
      ERROR("void cxios_get_file_split_last_date(file_Ptr file_hdl, char * split_last_date, int split_last_date_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_split_last_date(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->split_last_date.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_split_start_offset(file_Ptr file_hdl, cxios_duration split_start_offset_c)
  {
    CTimer::get("XIOS").resume();
    file_hdl->split_start_offset.allocate();
    CDuration& split_start_offset = file_hdl->split_start_offset.get();
    split_start_offset.year = split_start_offset_c.year;
    split_start_offset.month = split_start_offset_c.month;
    split_start_offset.day = split_start_offset_c.day;
    split_start_offset.hour = split_start_offset_c.hour;
    split_start_offset.minute = split_start_offset_c.minute;
    split_start_offset.second = split_start_offset_c.second;
    split_start_offset.timestep = split_start_offset_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_split_start_offset(file_Ptr file_hdl, cxios_duration* split_start_offset_c)
  {
    CTimer::get("XIOS").resume();
    CDuration split_start_offset = file_hdl->split_start_offset.getInheritedValue();
    split_start_offset_c->year = split_start_offset.year;
    split_start_offset_c->month = split_start_offset.month;
    split_start_offset_c->day = split_start_offset.day;
    split_start_offset_c->hour = split_start_offset.hour;
    split_start_offset_c->minute = split_start_offset.minute;
    split_start_offset_c->second = split_start_offset.second;
    split_start_offset_c->timestep = split_start_offset.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_split_start_offset(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->split_start_offset.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_sync_freq(file_Ptr file_hdl, cxios_duration sync_freq_c)
  {
    CTimer::get("XIOS").resume();
    file_hdl->sync_freq.allocate();
    CDuration& sync_freq = file_hdl->sync_freq.get();
    sync_freq.year = sync_freq_c.year;
    sync_freq.month = sync_freq_c.month;
    sync_freq.day = sync_freq_c.day;
    sync_freq.hour = sync_freq_c.hour;
    sync_freq.minute = sync_freq_c.minute;
    sync_freq.second = sync_freq_c.second;
    sync_freq.timestep = sync_freq_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_sync_freq(file_Ptr file_hdl, cxios_duration* sync_freq_c)
  {
    CTimer::get("XIOS").resume();
    CDuration sync_freq = file_hdl->sync_freq.getInheritedValue();
    sync_freq_c->year = sync_freq.year;
    sync_freq_c->month = sync_freq.month;
    sync_freq_c->day = sync_freq.day;
    sync_freq_c->hour = sync_freq.hour;
    sync_freq_c->minute = sync_freq.minute;
    sync_freq_c->second = sync_freq.second;
    sync_freq_c->timestep = sync_freq.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_sync_freq(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->sync_freq.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_time_counter(file_Ptr file_hdl, const char * time_counter, int time_counter_size)
  {
    std::string time_counter_str;
    if (!cstr2string(time_counter, time_counter_size, time_counter_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->time_counter.fromString(time_counter_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_time_counter(file_Ptr file_hdl, char * time_counter, int time_counter_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->time_counter.getInheritedStringValue(), time_counter, time_counter_size))
      ERROR("void cxios_get_file_time_counter(file_Ptr file_hdl, char * time_counter, int time_counter_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_time_counter(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->time_counter.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_time_counter_name(file_Ptr file_hdl, const char * time_counter_name, int time_counter_name_size)
  {
    std::string time_counter_name_str;
    if (!cstr2string(time_counter_name, time_counter_name_size, time_counter_name_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->time_counter_name.setValue(time_counter_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_time_counter_name(file_Ptr file_hdl, char * time_counter_name, int time_counter_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->time_counter_name.getInheritedValue(), time_counter_name, time_counter_name_size))
      ERROR("void cxios_get_file_time_counter_name(file_Ptr file_hdl, char * time_counter_name, int time_counter_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_time_counter_name(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->time_counter_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_time_stamp_format(file_Ptr file_hdl, const char * time_stamp_format, int time_stamp_format_size)
  {
    std::string time_stamp_format_str;
    if (!cstr2string(time_stamp_format, time_stamp_format_size, time_stamp_format_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->time_stamp_format.setValue(time_stamp_format_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_time_stamp_format(file_Ptr file_hdl, char * time_stamp_format, int time_stamp_format_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->time_stamp_format.getInheritedValue(), time_stamp_format, time_stamp_format_size))
      ERROR("void cxios_get_file_time_stamp_format(file_Ptr file_hdl, char * time_stamp_format, int time_stamp_format_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_time_stamp_format(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->time_stamp_format.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_time_stamp_name(file_Ptr file_hdl, const char * time_stamp_name, int time_stamp_name_size)
  {
    std::string time_stamp_name_str;
    if (!cstr2string(time_stamp_name, time_stamp_name_size, time_stamp_name_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->time_stamp_name.setValue(time_stamp_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_time_stamp_name(file_Ptr file_hdl, char * time_stamp_name, int time_stamp_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->time_stamp_name.getInheritedValue(), time_stamp_name, time_stamp_name_size))
      ERROR("void cxios_get_file_time_stamp_name(file_Ptr file_hdl, char * time_stamp_name, int time_stamp_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_time_stamp_name(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->time_stamp_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_time_units(file_Ptr file_hdl, const char * time_units, int time_units_size)
  {
    std::string time_units_str;
    if (!cstr2string(time_units, time_units_size, time_units_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->time_units.fromString(time_units_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_time_units(file_Ptr file_hdl, char * time_units, int time_units_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->time_units.getInheritedStringValue(), time_units, time_units_size))
      ERROR("void cxios_get_file_time_units(file_Ptr file_hdl, char * time_units, int time_units_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_time_units(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->time_units.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_timeseries(file_Ptr file_hdl, const char * timeseries, int timeseries_size)
  {
    std::string timeseries_str;
    if (!cstr2string(timeseries, timeseries_size, timeseries_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->timeseries.fromString(timeseries_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_timeseries(file_Ptr file_hdl, char * timeseries, int timeseries_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->timeseries.getInheritedStringValue(), timeseries, timeseries_size))
      ERROR("void cxios_get_file_timeseries(file_Ptr file_hdl, char * timeseries, int timeseries_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_timeseries(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->timeseries.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_ts_prefix(file_Ptr file_hdl, const char * ts_prefix, int ts_prefix_size)
  {
    std::string ts_prefix_str;
    if (!cstr2string(ts_prefix, ts_prefix_size, ts_prefix_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->ts_prefix.setValue(ts_prefix_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_ts_prefix(file_Ptr file_hdl, char * ts_prefix, int ts_prefix_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->ts_prefix.getInheritedValue(), ts_prefix, ts_prefix_size))
      ERROR("void cxios_get_file_ts_prefix(file_Ptr file_hdl, char * ts_prefix, int ts_prefix_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_ts_prefix(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->ts_prefix.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_type(file_Ptr file_hdl, const char * type, int type_size)
  {
    std::string type_str;
    if (!cstr2string(type, type_size, type_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->type.fromString(type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_type(file_Ptr file_hdl, char * type, int type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->type.getInheritedStringValue(), type, type_size))
      ERROR("void cxios_get_file_type(file_Ptr file_hdl, char * type, int type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_type(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_uuid_format(file_Ptr file_hdl, const char * uuid_format, int uuid_format_size)
  {
    std::string uuid_format_str;
    if (!cstr2string(uuid_format, uuid_format_size, uuid_format_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->uuid_format.setValue(uuid_format_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_uuid_format(file_Ptr file_hdl, char * uuid_format, int uuid_format_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->uuid_format.getInheritedValue(), uuid_format, uuid_format_size))
      ERROR("void cxios_get_file_uuid_format(file_Ptr file_hdl, char * uuid_format, int uuid_format_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_uuid_format(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->uuid_format.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_file_uuid_name(file_Ptr file_hdl, const char * uuid_name, int uuid_name_size)
  {
    std::string uuid_name_str;
    if (!cstr2string(uuid_name, uuid_name_size, uuid_name_str)) return;
    CTimer::get("XIOS").resume();
    file_hdl->uuid_name.setValue(uuid_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_file_uuid_name(file_Ptr file_hdl, char * uuid_name, int uuid_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(file_hdl->uuid_name.getInheritedValue(), uuid_name, uuid_name_size))
      ERROR("void cxios_get_file_uuid_name(file_Ptr file_hdl, char * uuid_name, int uuid_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_file_uuid_name(file_Ptr file_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = file_hdl->uuid_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
