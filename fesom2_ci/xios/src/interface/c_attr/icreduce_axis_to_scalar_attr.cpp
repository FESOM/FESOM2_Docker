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
  typedef xios::CReduceAxisToScalar* reduce_axis_to_scalar_Ptr;

  void cxios_set_reduce_axis_to_scalar_operation(reduce_axis_to_scalar_Ptr reduce_axis_to_scalar_hdl, const char * operation, int operation_size)
  {
    std::string operation_str;
    if (!cstr2string(operation, operation_size, operation_str)) return;
    CTimer::get("XIOS").resume();
    reduce_axis_to_scalar_hdl->operation.fromString(operation_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_reduce_axis_to_scalar_operation(reduce_axis_to_scalar_Ptr reduce_axis_to_scalar_hdl, char * operation, int operation_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(reduce_axis_to_scalar_hdl->operation.getInheritedStringValue(), operation, operation_size))
      ERROR("void cxios_get_reduce_axis_to_scalar_operation(reduce_axis_to_scalar_Ptr reduce_axis_to_scalar_hdl, char * operation, int operation_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_reduce_axis_to_scalar_operation(reduce_axis_to_scalar_Ptr reduce_axis_to_scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = reduce_axis_to_scalar_hdl->operation.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
