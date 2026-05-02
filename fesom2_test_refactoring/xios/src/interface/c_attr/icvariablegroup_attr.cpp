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
  typedef xios::CVariableGroup* variablegroup_Ptr;

  void cxios_set_variablegroup_group_ref(variablegroup_Ptr variablegroup_hdl, const char * group_ref, int group_ref_size)
  {
    std::string group_ref_str;
    if (!cstr2string(group_ref, group_ref_size, group_ref_str)) return;
    CTimer::get("XIOS").resume();
    variablegroup_hdl->group_ref.setValue(group_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_variablegroup_group_ref(variablegroup_Ptr variablegroup_hdl, char * group_ref, int group_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(variablegroup_hdl->group_ref.getInheritedValue(), group_ref, group_ref_size))
      ERROR("void cxios_get_variablegroup_group_ref(variablegroup_Ptr variablegroup_hdl, char * group_ref, int group_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_variablegroup_group_ref(variablegroup_Ptr variablegroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = variablegroup_hdl->group_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_variablegroup_name(variablegroup_Ptr variablegroup_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    variablegroup_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_variablegroup_name(variablegroup_Ptr variablegroup_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(variablegroup_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_variablegroup_name(variablegroup_Ptr variablegroup_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_variablegroup_name(variablegroup_Ptr variablegroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = variablegroup_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_variablegroup_ts_target(variablegroup_Ptr variablegroup_hdl, const char * ts_target, int ts_target_size)
  {
    std::string ts_target_str;
    if (!cstr2string(ts_target, ts_target_size, ts_target_str)) return;
    CTimer::get("XIOS").resume();
    variablegroup_hdl->ts_target.fromString(ts_target_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_variablegroup_ts_target(variablegroup_Ptr variablegroup_hdl, char * ts_target, int ts_target_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(variablegroup_hdl->ts_target.getInheritedStringValue(), ts_target, ts_target_size))
      ERROR("void cxios_get_variablegroup_ts_target(variablegroup_Ptr variablegroup_hdl, char * ts_target, int ts_target_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_variablegroup_ts_target(variablegroup_Ptr variablegroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = variablegroup_hdl->ts_target.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_variablegroup_type(variablegroup_Ptr variablegroup_hdl, const char * type, int type_size)
  {
    std::string type_str;
    if (!cstr2string(type, type_size, type_str)) return;
    CTimer::get("XIOS").resume();
    variablegroup_hdl->type.fromString(type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_variablegroup_type(variablegroup_Ptr variablegroup_hdl, char * type, int type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(variablegroup_hdl->type.getInheritedStringValue(), type, type_size))
      ERROR("void cxios_get_variablegroup_type(variablegroup_Ptr variablegroup_hdl, char * type, int type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_variablegroup_type(variablegroup_Ptr variablegroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = variablegroup_hdl->type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
