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
  typedef xios::CExtractDomainToAxis* extract_domain_to_axis_Ptr;

  void cxios_set_extract_domain_to_axis_direction(extract_domain_to_axis_Ptr extract_domain_to_axis_hdl, const char * direction, int direction_size)
  {
    std::string direction_str;
    if (!cstr2string(direction, direction_size, direction_str)) return;
    CTimer::get("XIOS").resume();
    extract_domain_to_axis_hdl->direction.fromString(direction_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_extract_domain_to_axis_direction(extract_domain_to_axis_Ptr extract_domain_to_axis_hdl, char * direction, int direction_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(extract_domain_to_axis_hdl->direction.getInheritedStringValue(), direction, direction_size))
      ERROR("void cxios_get_extract_domain_to_axis_direction(extract_domain_to_axis_Ptr extract_domain_to_axis_hdl, char * direction, int direction_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_extract_domain_to_axis_direction(extract_domain_to_axis_Ptr extract_domain_to_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = extract_domain_to_axis_hdl->direction.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_extract_domain_to_axis_position(extract_domain_to_axis_Ptr extract_domain_to_axis_hdl, int position)
  {
    CTimer::get("XIOS").resume();
    extract_domain_to_axis_hdl->position.setValue(position);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_extract_domain_to_axis_position(extract_domain_to_axis_Ptr extract_domain_to_axis_hdl, int* position)
  {
    CTimer::get("XIOS").resume();
    *position = extract_domain_to_axis_hdl->position.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_extract_domain_to_axis_position(extract_domain_to_axis_Ptr extract_domain_to_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = extract_domain_to_axis_hdl->position.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
