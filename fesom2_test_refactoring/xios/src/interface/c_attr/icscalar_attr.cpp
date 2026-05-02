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
  typedef xios::CScalar* scalar_Ptr;

  void cxios_set_scalar_axis_type(scalar_Ptr scalar_hdl, const char * axis_type, int axis_type_size)
  {
    std::string axis_type_str;
    if (!cstr2string(axis_type, axis_type_size, axis_type_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->axis_type.fromString(axis_type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_axis_type(scalar_Ptr scalar_hdl, char * axis_type, int axis_type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->axis_type.getInheritedStringValue(), axis_type, axis_type_size))
      ERROR("void cxios_get_scalar_axis_type(scalar_Ptr scalar_hdl, char * axis_type, int axis_type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_axis_type(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->axis_type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_bounds(scalar_Ptr scalar_hdl, double* bounds, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(bounds, shape(extent[0]), neverDeleteData);
    scalar_hdl->bounds.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_bounds(scalar_Ptr scalar_hdl, double* bounds, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(bounds, shape(extent[0]), neverDeleteData);
    tmp=scalar_hdl->bounds.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_bounds(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->bounds.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_bounds_name(scalar_Ptr scalar_hdl, const char * bounds_name, int bounds_name_size)
  {
    std::string bounds_name_str;
    if (!cstr2string(bounds_name, bounds_name_size, bounds_name_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->bounds_name.setValue(bounds_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_bounds_name(scalar_Ptr scalar_hdl, char * bounds_name, int bounds_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->bounds_name.getInheritedValue(), bounds_name, bounds_name_size))
      ERROR("void cxios_get_scalar_bounds_name(scalar_Ptr scalar_hdl, char * bounds_name, int bounds_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_bounds_name(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->bounds_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_comment(scalar_Ptr scalar_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_comment(scalar_Ptr scalar_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_scalar_comment(scalar_Ptr scalar_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_comment(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_label(scalar_Ptr scalar_hdl, const char * label, int label_size)
  {
    std::string label_str;
    if (!cstr2string(label, label_size, label_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->label.setValue(label_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_label(scalar_Ptr scalar_hdl, char * label, int label_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->label.getInheritedValue(), label, label_size))
      ERROR("void cxios_get_scalar_label(scalar_Ptr scalar_hdl, char * label, int label_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_label(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->label.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_long_name(scalar_Ptr scalar_hdl, const char * long_name, int long_name_size)
  {
    std::string long_name_str;
    if (!cstr2string(long_name, long_name_size, long_name_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->long_name.setValue(long_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_long_name(scalar_Ptr scalar_hdl, char * long_name, int long_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->long_name.getInheritedValue(), long_name, long_name_size))
      ERROR("void cxios_get_scalar_long_name(scalar_Ptr scalar_hdl, char * long_name, int long_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_long_name(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->long_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_name(scalar_Ptr scalar_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_name(scalar_Ptr scalar_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_scalar_name(scalar_Ptr scalar_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_name(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_positive(scalar_Ptr scalar_hdl, const char * positive, int positive_size)
  {
    std::string positive_str;
    if (!cstr2string(positive, positive_size, positive_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->positive.fromString(positive_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_positive(scalar_Ptr scalar_hdl, char * positive, int positive_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->positive.getInheritedStringValue(), positive, positive_size))
      ERROR("void cxios_get_scalar_positive(scalar_Ptr scalar_hdl, char * positive, int positive_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_positive(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->positive.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_prec(scalar_Ptr scalar_hdl, int prec)
  {
    CTimer::get("XIOS").resume();
    scalar_hdl->prec.setValue(prec);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_prec(scalar_Ptr scalar_hdl, int* prec)
  {
    CTimer::get("XIOS").resume();
    *prec = scalar_hdl->prec.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_prec(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->prec.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_scalar_ref(scalar_Ptr scalar_hdl, const char * scalar_ref, int scalar_ref_size)
  {
    std::string scalar_ref_str;
    if (!cstr2string(scalar_ref, scalar_ref_size, scalar_ref_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->scalar_ref.setValue(scalar_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_scalar_ref(scalar_Ptr scalar_hdl, char * scalar_ref, int scalar_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->scalar_ref.getInheritedValue(), scalar_ref, scalar_ref_size))
      ERROR("void cxios_get_scalar_scalar_ref(scalar_Ptr scalar_hdl, char * scalar_ref, int scalar_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_scalar_ref(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->scalar_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_standard_name(scalar_Ptr scalar_hdl, const char * standard_name, int standard_name_size)
  {
    std::string standard_name_str;
    if (!cstr2string(standard_name, standard_name_size, standard_name_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->standard_name.setValue(standard_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_standard_name(scalar_Ptr scalar_hdl, char * standard_name, int standard_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->standard_name.getInheritedValue(), standard_name, standard_name_size))
      ERROR("void cxios_get_scalar_standard_name(scalar_Ptr scalar_hdl, char * standard_name, int standard_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_standard_name(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->standard_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_unit(scalar_Ptr scalar_hdl, const char * unit, int unit_size)
  {
    std::string unit_str;
    if (!cstr2string(unit, unit_size, unit_str)) return;
    CTimer::get("XIOS").resume();
    scalar_hdl->unit.setValue(unit_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_unit(scalar_Ptr scalar_hdl, char * unit, int unit_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(scalar_hdl->unit.getInheritedValue(), unit, unit_size))
      ERROR("void cxios_get_scalar_unit(scalar_Ptr scalar_hdl, char * unit, int unit_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_unit(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->unit.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_scalar_value(scalar_Ptr scalar_hdl, double value)
  {
    CTimer::get("XIOS").resume();
    scalar_hdl->value.setValue(value);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_scalar_value(scalar_Ptr scalar_hdl, double* value)
  {
    CTimer::get("XIOS").resume();
    *value = scalar_hdl->value.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_scalar_value(scalar_Ptr scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = scalar_hdl->value.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
