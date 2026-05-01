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
  typedef xios::CScalarGroup* scalargroup_Ptr;

  void cxios_set_scalargroup_axis_type(scalargroup_Ptr scalargroup_hdl, const char * axis_type, int axis_type_size)
  {
    std::string axis_type_str;
    if (!cstr2string(axis_type, axis_type_size, axis_type_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->axis_type.fromString(axis_type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_axis_type(scalargroup_Ptr scalargroup_hdl, char * axis_type, int axis_type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->axis_type.getInheritedStringValue(), axis_type, axis_type_size))
      ERROR("void cxios_get_scalargroup_axis_type(scalargroup_Ptr scalargroup_hdl, char * axis_type, int axis_type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_axis_type(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->axis_type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_bounds(scalargroup_Ptr scalargroup_hdl, double* bounds, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(bounds, shape(extent[0]), neverDeleteData);
    scalargroup_hdl->bounds.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_bounds(scalargroup_Ptr scalargroup_hdl, double* bounds, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(bounds, shape(extent[0]), neverDeleteData);
    tmp=scalargroup_hdl->bounds.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_bounds(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->bounds.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_bounds_name(scalargroup_Ptr scalargroup_hdl, const char * bounds_name, int bounds_name_size)
  {
    std::string bounds_name_str;
    if (!cstr2string(bounds_name, bounds_name_size, bounds_name_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->bounds_name.setValue(bounds_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_bounds_name(scalargroup_Ptr scalargroup_hdl, char * bounds_name, int bounds_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->bounds_name.getInheritedValue(), bounds_name, bounds_name_size))
      ERROR("void cxios_get_scalargroup_bounds_name(scalargroup_Ptr scalargroup_hdl, char * bounds_name, int bounds_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_bounds_name(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->bounds_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_comment(scalargroup_Ptr scalargroup_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_comment(scalargroup_Ptr scalargroup_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_scalargroup_comment(scalargroup_Ptr scalargroup_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_comment(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_group_ref(scalargroup_Ptr scalargroup_hdl, const char * group_ref, int group_ref_size)
  {
    std::string group_ref_str;
    if (!cstr2string(group_ref, group_ref_size, group_ref_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->group_ref.setValue(group_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_group_ref(scalargroup_Ptr scalargroup_hdl, char * group_ref, int group_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->group_ref.getInheritedValue(), group_ref, group_ref_size))
      ERROR("void cxios_get_scalargroup_group_ref(scalargroup_Ptr scalargroup_hdl, char * group_ref, int group_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_group_ref(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->group_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_label(scalargroup_Ptr scalargroup_hdl, const char * label, int label_size)
  {
    std::string label_str;
    if (!cstr2string(label, label_size, label_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->label.setValue(label_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_label(scalargroup_Ptr scalargroup_hdl, char * label, int label_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->label.getInheritedValue(), label, label_size))
      ERROR("void cxios_get_scalargroup_label(scalargroup_Ptr scalargroup_hdl, char * label, int label_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_label(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->label.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_long_name(scalargroup_Ptr scalargroup_hdl, const char * long_name, int long_name_size)
  {
    std::string long_name_str;
    if (!cstr2string(long_name, long_name_size, long_name_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->long_name.setValue(long_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_long_name(scalargroup_Ptr scalargroup_hdl, char * long_name, int long_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->long_name.getInheritedValue(), long_name, long_name_size))
      ERROR("void cxios_get_scalargroup_long_name(scalargroup_Ptr scalargroup_hdl, char * long_name, int long_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_long_name(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->long_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_name(scalargroup_Ptr scalargroup_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_name(scalargroup_Ptr scalargroup_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_scalargroup_name(scalargroup_Ptr scalargroup_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_name(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_positive(scalargroup_Ptr scalargroup_hdl, const char * positive, int positive_size)
  {
    std::string positive_str;
    if (!cstr2string(positive, positive_size, positive_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->positive.fromString(positive_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_positive(scalargroup_Ptr scalargroup_hdl, char * positive, int positive_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->positive.getInheritedStringValue(), positive, positive_size))
      ERROR("void cxios_get_scalargroup_positive(scalargroup_Ptr scalargroup_hdl, char * positive, int positive_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_positive(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->positive.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_prec(scalargroup_Ptr scalargroup_hdl, int prec)
  {
    CTimer::get("XIOS").resume();
    scalargroup_hdl->prec.setValue(prec);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_prec(scalargroup_Ptr scalargroup_hdl, int* prec)
  {
    CTimer::get("XIOS").resume();
    *prec = scalargroup_hdl->prec.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_prec(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->prec.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_scalar_ref(scalargroup_Ptr scalargroup_hdl, const char * scalar_ref, int scalar_ref_size)
  {
    std::string scalar_ref_str;
    if (!cstr2string(scalar_ref, scalar_ref_size, scalar_ref_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->scalar_ref.setValue(scalar_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_scalar_ref(scalargroup_Ptr scalargroup_hdl, char * scalar_ref, int scalar_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->scalar_ref.getInheritedValue(), scalar_ref, scalar_ref_size))
      ERROR("void cxios_get_scalargroup_scalar_ref(scalargroup_Ptr scalargroup_hdl, char * scalar_ref, int scalar_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_scalar_ref(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->scalar_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_standard_name(scalargroup_Ptr scalargroup_hdl, const char * standard_name, int standard_name_size)
  {
    std::string standard_name_str;
    if (!cstr2string(standard_name, standard_name_size, standard_name_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->standard_name.setValue(standard_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_standard_name(scalargroup_Ptr scalargroup_hdl, char * standard_name, int standard_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->standard_name.getInheritedValue(), standard_name, standard_name_size))
      ERROR("void cxios_get_scalargroup_standard_name(scalargroup_Ptr scalargroup_hdl, char * standard_name, int standard_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_standard_name(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->standard_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_unit(scalargroup_Ptr scalargroup_hdl, const char * unit, int unit_size)
  {
    std::string unit_str;
    if (!cstr2string(unit, unit_size, unit_str)) return;
    CTimer::get("XIOS").resume();
    scalargroup_hdl->unit.setValue(unit_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_unit(scalargroup_Ptr scalargroup_hdl, char * unit, int unit_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalargroup_hdl->unit.getInheritedValue(), unit, unit_size))
      ERROR("void cxios_get_scalargroup_unit(scalargroup_Ptr scalargroup_hdl, char * unit, int unit_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_unit(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->unit.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalargroup_value(scalargroup_Ptr scalargroup_hdl, double value)
  {
    CTimer::get("XIOS").resume();
    scalargroup_hdl->value.setValue(value);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalargroup_value(scalargroup_Ptr scalargroup_hdl, double* value)
  {
    CTimer::get("XIOS").resume();
    *value = scalargroup_hdl->value.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalargroup_value(scalargroup_Ptr scalargroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalargroup_hdl->value.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
