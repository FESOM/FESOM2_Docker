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
  typedef xios::CField* field_Ptr;

  void cxios_set_field_add_offset(field_Ptr field_hdl, double add_offset)
  {
    CTimer::get("XIOS").resume();
    field_hdl->add_offset.setValue(add_offset);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_add_offset(field_Ptr field_hdl, double* add_offset)
  {
    CTimer::get("XIOS").resume();
    *add_offset = field_hdl->add_offset.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_add_offset(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->add_offset.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_axis_ref(field_Ptr field_hdl, const char * axis_ref, int axis_ref_size)
  {
    std::string axis_ref_str;
    if (!cstr2string(axis_ref, axis_ref_size, axis_ref_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->axis_ref.setValue(axis_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_axis_ref(field_Ptr field_hdl, char * axis_ref, int axis_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->axis_ref.getInheritedValue(), axis_ref, axis_ref_size))
      ERROR("void cxios_get_field_axis_ref(field_Ptr field_hdl, char * axis_ref, int axis_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_axis_ref(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->axis_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_cell_methods(field_Ptr field_hdl, const char * cell_methods, int cell_methods_size)
  {
    std::string cell_methods_str;
    if (!cstr2string(cell_methods, cell_methods_size, cell_methods_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->cell_methods.setValue(cell_methods_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_cell_methods(field_Ptr field_hdl, char * cell_methods, int cell_methods_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->cell_methods.getInheritedValue(), cell_methods, cell_methods_size))
      ERROR("void cxios_get_field_cell_methods(field_Ptr field_hdl, char * cell_methods, int cell_methods_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_cell_methods(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->cell_methods.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_cell_methods_mode(field_Ptr field_hdl, const char * cell_methods_mode, int cell_methods_mode_size)
  {
    std::string cell_methods_mode_str;
    if (!cstr2string(cell_methods_mode, cell_methods_mode_size, cell_methods_mode_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->cell_methods_mode.fromString(cell_methods_mode_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_cell_methods_mode(field_Ptr field_hdl, char * cell_methods_mode, int cell_methods_mode_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->cell_methods_mode.getInheritedStringValue(), cell_methods_mode, cell_methods_mode_size))
      ERROR("void cxios_get_field_cell_methods_mode(field_Ptr field_hdl, char * cell_methods_mode, int cell_methods_mode_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_cell_methods_mode(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->cell_methods_mode.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_check_if_active(field_Ptr field_hdl, bool check_if_active)
  {
    CTimer::get("XIOS").resume();
    field_hdl->check_if_active.setValue(check_if_active);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_check_if_active(field_Ptr field_hdl, bool* check_if_active)
  {
    CTimer::get("XIOS").resume();
    *check_if_active = field_hdl->check_if_active.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_check_if_active(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->check_if_active.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_comment(field_Ptr field_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_comment(field_Ptr field_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_field_comment(field_Ptr field_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_comment(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_compression_level(field_Ptr field_hdl, int compression_level)
  {
    CTimer::get("XIOS").resume();
    field_hdl->compression_level.setValue(compression_level);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_compression_level(field_Ptr field_hdl, int* compression_level)
  {
    CTimer::get("XIOS").resume();
    *compression_level = field_hdl->compression_level.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_compression_level(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->compression_level.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_default_value(field_Ptr field_hdl, double default_value)
  {
    CTimer::get("XIOS").resume();
    field_hdl->default_value.setValue(default_value);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_default_value(field_Ptr field_hdl, double* default_value)
  {
    CTimer::get("XIOS").resume();
    *default_value = field_hdl->default_value.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_default_value(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->default_value.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_detect_missing_value(field_Ptr field_hdl, bool detect_missing_value)
  {
    CTimer::get("XIOS").resume();
    field_hdl->detect_missing_value.setValue(detect_missing_value);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_detect_missing_value(field_Ptr field_hdl, bool* detect_missing_value)
  {
    CTimer::get("XIOS").resume();
    *detect_missing_value = field_hdl->detect_missing_value.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_detect_missing_value(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->detect_missing_value.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_domain_ref(field_Ptr field_hdl, const char * domain_ref, int domain_ref_size)
  {
    std::string domain_ref_str;
    if (!cstr2string(domain_ref, domain_ref_size, domain_ref_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->domain_ref.setValue(domain_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_domain_ref(field_Ptr field_hdl, char * domain_ref, int domain_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->domain_ref.getInheritedValue(), domain_ref, domain_ref_size))
      ERROR("void cxios_get_field_domain_ref(field_Ptr field_hdl, char * domain_ref, int domain_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_domain_ref(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->domain_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_enabled(field_Ptr field_hdl, bool enabled)
  {
    CTimer::get("XIOS").resume();
    field_hdl->enabled.setValue(enabled);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_enabled(field_Ptr field_hdl, bool* enabled)
  {
    CTimer::get("XIOS").resume();
    *enabled = field_hdl->enabled.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_enabled(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->enabled.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_expr(field_Ptr field_hdl, const char * expr, int expr_size)
  {
    std::string expr_str;
    if (!cstr2string(expr, expr_size, expr_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->expr.setValue(expr_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_expr(field_Ptr field_hdl, char * expr, int expr_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->expr.getInheritedValue(), expr, expr_size))
      ERROR("void cxios_get_field_expr(field_Ptr field_hdl, char * expr, int expr_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_expr(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->expr.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_field_ref(field_Ptr field_hdl, const char * field_ref, int field_ref_size)
  {
    std::string field_ref_str;
    if (!cstr2string(field_ref, field_ref_size, field_ref_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->field_ref.setValue(field_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_field_ref(field_Ptr field_hdl, char * field_ref, int field_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->field_ref.getInheritedValue(), field_ref, field_ref_size))
      ERROR("void cxios_get_field_field_ref(field_Ptr field_hdl, char * field_ref, int field_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_field_ref(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->field_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_freq_offset(field_Ptr field_hdl, cxios_duration freq_offset_c)
  {
    CTimer::get("XIOS").resume();
    field_hdl->freq_offset.allocate();
    CDuration& freq_offset = field_hdl->freq_offset.get();
    freq_offset.year = freq_offset_c.year;
    freq_offset.month = freq_offset_c.month;
    freq_offset.day = freq_offset_c.day;
    freq_offset.hour = freq_offset_c.hour;
    freq_offset.minute = freq_offset_c.minute;
    freq_offset.second = freq_offset_c.second;
    freq_offset.timestep = freq_offset_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_freq_offset(field_Ptr field_hdl, cxios_duration* freq_offset_c)
  {
    CTimer::get("XIOS").resume();
    CDuration freq_offset = field_hdl->freq_offset.getInheritedValue();
    freq_offset_c->year = freq_offset.year;
    freq_offset_c->month = freq_offset.month;
    freq_offset_c->day = freq_offset.day;
    freq_offset_c->hour = freq_offset.hour;
    freq_offset_c->minute = freq_offset.minute;
    freq_offset_c->second = freq_offset.second;
    freq_offset_c->timestep = freq_offset.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_freq_offset(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->freq_offset.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_freq_op(field_Ptr field_hdl, cxios_duration freq_op_c)
  {
    CTimer::get("XIOS").resume();
    field_hdl->freq_op.allocate();
    CDuration& freq_op = field_hdl->freq_op.get();
    freq_op.year = freq_op_c.year;
    freq_op.month = freq_op_c.month;
    freq_op.day = freq_op_c.day;
    freq_op.hour = freq_op_c.hour;
    freq_op.minute = freq_op_c.minute;
    freq_op.second = freq_op_c.second;
    freq_op.timestep = freq_op_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_freq_op(field_Ptr field_hdl, cxios_duration* freq_op_c)
  {
    CTimer::get("XIOS").resume();
    CDuration freq_op = field_hdl->freq_op.getInheritedValue();
    freq_op_c->year = freq_op.year;
    freq_op_c->month = freq_op.month;
    freq_op_c->day = freq_op.day;
    freq_op_c->hour = freq_op.hour;
    freq_op_c->minute = freq_op.minute;
    freq_op_c->second = freq_op.second;
    freq_op_c->timestep = freq_op.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_freq_op(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->freq_op.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_grid_path(field_Ptr field_hdl, const char * grid_path, int grid_path_size)
  {
    std::string grid_path_str;
    if (!cstr2string(grid_path, grid_path_size, grid_path_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->grid_path.setValue(grid_path_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_grid_path(field_Ptr field_hdl, char * grid_path, int grid_path_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->grid_path.getInheritedValue(), grid_path, grid_path_size))
      ERROR("void cxios_get_field_grid_path(field_Ptr field_hdl, char * grid_path, int grid_path_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_grid_path(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->grid_path.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_grid_ref(field_Ptr field_hdl, const char * grid_ref, int grid_ref_size)
  {
    std::string grid_ref_str;
    if (!cstr2string(grid_ref, grid_ref_size, grid_ref_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->grid_ref.setValue(grid_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_grid_ref(field_Ptr field_hdl, char * grid_ref, int grid_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->grid_ref.getInheritedValue(), grid_ref, grid_ref_size))
      ERROR("void cxios_get_field_grid_ref(field_Ptr field_hdl, char * grid_ref, int grid_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_grid_ref(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->grid_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_indexed_output(field_Ptr field_hdl, bool indexed_output)
  {
    CTimer::get("XIOS").resume();
    field_hdl->indexed_output.setValue(indexed_output);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_indexed_output(field_Ptr field_hdl, bool* indexed_output)
  {
    CTimer::get("XIOS").resume();
    *indexed_output = field_hdl->indexed_output.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_indexed_output(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->indexed_output.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_level(field_Ptr field_hdl, int level)
  {
    CTimer::get("XIOS").resume();
    field_hdl->level.setValue(level);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_level(field_Ptr field_hdl, int* level)
  {
    CTimer::get("XIOS").resume();
    *level = field_hdl->level.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_level(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->level.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_long_name(field_Ptr field_hdl, const char * long_name, int long_name_size)
  {
    std::string long_name_str;
    if (!cstr2string(long_name, long_name_size, long_name_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->long_name.setValue(long_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_long_name(field_Ptr field_hdl, char * long_name, int long_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->long_name.getInheritedValue(), long_name, long_name_size))
      ERROR("void cxios_get_field_long_name(field_Ptr field_hdl, char * long_name, int long_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_long_name(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->long_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_name(field_Ptr field_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_name(field_Ptr field_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_field_name(field_Ptr field_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_name(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_operation(field_Ptr field_hdl, const char * operation, int operation_size)
  {
    std::string operation_str;
    if (!cstr2string(operation, operation_size, operation_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->operation.setValue(operation_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_operation(field_Ptr field_hdl, char * operation, int operation_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->operation.getInheritedValue(), operation, operation_size))
      ERROR("void cxios_get_field_operation(field_Ptr field_hdl, char * operation, int operation_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_operation(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->operation.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_prec(field_Ptr field_hdl, int prec)
  {
    CTimer::get("XIOS").resume();
    field_hdl->prec.setValue(prec);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_prec(field_Ptr field_hdl, int* prec)
  {
    CTimer::get("XIOS").resume();
    *prec = field_hdl->prec.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_prec(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->prec.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_read_access(field_Ptr field_hdl, bool read_access)
  {
    CTimer::get("XIOS").resume();
    field_hdl->read_access.setValue(read_access);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_read_access(field_Ptr field_hdl, bool* read_access)
  {
    CTimer::get("XIOS").resume();
    *read_access = field_hdl->read_access.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_read_access(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->read_access.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_scalar_ref(field_Ptr field_hdl, const char * scalar_ref, int scalar_ref_size)
  {
    std::string scalar_ref_str;
    if (!cstr2string(scalar_ref, scalar_ref_size, scalar_ref_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->scalar_ref.setValue(scalar_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_scalar_ref(field_Ptr field_hdl, char * scalar_ref, int scalar_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->scalar_ref.getInheritedValue(), scalar_ref, scalar_ref_size))
      ERROR("void cxios_get_field_scalar_ref(field_Ptr field_hdl, char * scalar_ref, int scalar_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_scalar_ref(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->scalar_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_scale_factor(field_Ptr field_hdl, double scale_factor)
  {
    CTimer::get("XIOS").resume();
    field_hdl->scale_factor.setValue(scale_factor);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_scale_factor(field_Ptr field_hdl, double* scale_factor)
  {
    CTimer::get("XIOS").resume();
    *scale_factor = field_hdl->scale_factor.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_scale_factor(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->scale_factor.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_standard_name(field_Ptr field_hdl, const char * standard_name, int standard_name_size)
  {
    std::string standard_name_str;
    if (!cstr2string(standard_name, standard_name_size, standard_name_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->standard_name.setValue(standard_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_standard_name(field_Ptr field_hdl, char * standard_name, int standard_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->standard_name.getInheritedValue(), standard_name, standard_name_size))
      ERROR("void cxios_get_field_standard_name(field_Ptr field_hdl, char * standard_name, int standard_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_standard_name(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->standard_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_ts_enabled(field_Ptr field_hdl, bool ts_enabled)
  {
    CTimer::get("XIOS").resume();
    field_hdl->ts_enabled.setValue(ts_enabled);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_ts_enabled(field_Ptr field_hdl, bool* ts_enabled)
  {
    CTimer::get("XIOS").resume();
    *ts_enabled = field_hdl->ts_enabled.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_ts_enabled(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->ts_enabled.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_ts_split_freq(field_Ptr field_hdl, cxios_duration ts_split_freq_c)
  {
    CTimer::get("XIOS").resume();
    field_hdl->ts_split_freq.allocate();
    CDuration& ts_split_freq = field_hdl->ts_split_freq.get();
    ts_split_freq.year = ts_split_freq_c.year;
    ts_split_freq.month = ts_split_freq_c.month;
    ts_split_freq.day = ts_split_freq_c.day;
    ts_split_freq.hour = ts_split_freq_c.hour;
    ts_split_freq.minute = ts_split_freq_c.minute;
    ts_split_freq.second = ts_split_freq_c.second;
    ts_split_freq.timestep = ts_split_freq_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_ts_split_freq(field_Ptr field_hdl, cxios_duration* ts_split_freq_c)
  {
    CTimer::get("XIOS").resume();
    CDuration ts_split_freq = field_hdl->ts_split_freq.getInheritedValue();
    ts_split_freq_c->year = ts_split_freq.year;
    ts_split_freq_c->month = ts_split_freq.month;
    ts_split_freq_c->day = ts_split_freq.day;
    ts_split_freq_c->hour = ts_split_freq.hour;
    ts_split_freq_c->minute = ts_split_freq.minute;
    ts_split_freq_c->second = ts_split_freq.second;
    ts_split_freq_c->timestep = ts_split_freq.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_ts_split_freq(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->ts_split_freq.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_unit(field_Ptr field_hdl, const char * unit, int unit_size)
  {
    std::string unit_str;
    if (!cstr2string(unit, unit_size, unit_str)) return;
    CTimer::get("XIOS").resume();
    field_hdl->unit.setValue(unit_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_unit(field_Ptr field_hdl, char * unit, int unit_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(field_hdl->unit.getInheritedValue(), unit, unit_size))
      ERROR("void cxios_get_field_unit(field_Ptr field_hdl, char * unit, int unit_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_unit(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->unit.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_valid_max(field_Ptr field_hdl, double valid_max)
  {
    CTimer::get("XIOS").resume();
    field_hdl->valid_max.setValue(valid_max);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_valid_max(field_Ptr field_hdl, double* valid_max)
  {
    CTimer::get("XIOS").resume();
    *valid_max = field_hdl->valid_max.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_valid_max(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->valid_max.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_field_valid_min(field_Ptr field_hdl, double valid_min)
  {
    CTimer::get("XIOS").resume();
    field_hdl->valid_min.setValue(valid_min);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_field_valid_min(field_Ptr field_hdl, double* valid_min)
  {
    CTimer::get("XIOS").resume();
    *valid_min = field_hdl->valid_min.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_field_valid_min(field_Ptr field_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = field_hdl->valid_min.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
