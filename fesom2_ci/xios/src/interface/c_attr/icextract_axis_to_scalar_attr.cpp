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
  typedef xios::CExtractAxisToScalar* extract_axis_to_scalar_Ptr;

  void cxios_set_extract_axis_to_scalar_position(extract_axis_to_scalar_Ptr extract_axis_to_scalar_hdl, int position)
  {
    CTimer::get("XIOS").resume();
    extract_axis_to_scalar_hdl->position.setValue(position);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_extract_axis_to_scalar_position(extract_axis_to_scalar_Ptr extract_axis_to_scalar_hdl, int* position)
  {
    CTimer::get("XIOS").resume();
    *position = extract_axis_to_scalar_hdl->position.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_extract_axis_to_scalar_position(extract_axis_to_scalar_Ptr extract_axis_to_scalar_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = extract_axis_to_scalar_hdl->position.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
