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
  typedef xios::CReduceDomainToAxis* reduce_domain_to_axis_Ptr;

  void cxios_set_reduce_domain_to_axis_direction(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl, const char * direction, int direction_size)
  {
    std::string direction_str;
    if (!cstr2string(direction, direction_size, direction_str)) return;
    CTimer::get("XIOS").resume();
    reduce_domain_to_axis_hdl->direction.fromString(direction_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_reduce_domain_to_axis_direction(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl, char * direction, int direction_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(reduce_domain_to_axis_hdl->direction.getInheritedStringValue(), direction, direction_size))
      ERROR("void cxios_get_reduce_domain_to_axis_direction(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl, char * direction, int direction_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_reduce_domain_to_axis_direction(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = reduce_domain_to_axis_hdl->direction.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_reduce_domain_to_axis_local(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl, bool local)
  {
    CTimer::get("XIOS").resume();
    reduce_domain_to_axis_hdl->local.setValue(local);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_reduce_domain_to_axis_local(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl, bool* local)
  {
    CTimer::get("XIOS").resume();
    *local = reduce_domain_to_axis_hdl->local.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_reduce_domain_to_axis_local(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = reduce_domain_to_axis_hdl->local.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_reduce_domain_to_axis_operation(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl, const char * operation, int operation_size)
  {
    std::string operation_str;
    if (!cstr2string(operation, operation_size, operation_str)) return;
    CTimer::get("XIOS").resume();
    reduce_domain_to_axis_hdl->operation.fromString(operation_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_reduce_domain_to_axis_operation(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl, char * operation, int operation_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(reduce_domain_to_axis_hdl->operation.getInheritedStringValue(), operation, operation_size))
      ERROR("void cxios_get_reduce_domain_to_axis_operation(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl, char * operation, int operation_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_reduce_domain_to_axis_operation(reduce_domain_to_axis_Ptr reduce_domain_to_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = reduce_domain_to_axis_hdl->operation.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
