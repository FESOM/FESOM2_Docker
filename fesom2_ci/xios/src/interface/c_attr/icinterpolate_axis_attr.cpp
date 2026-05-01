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
  typedef xios::CInterpolateAxis* interpolate_axis_Ptr;

  void cxios_set_interpolate_axis_coordinate(interpolate_axis_Ptr interpolate_axis_hdl, const char * coordinate, int coordinate_size)
  {
    std::string coordinate_str;
    if (!cstr2string(coordinate, coordinate_size, coordinate_str)) return;
    CTimer::get("XIOS").resume();
    interpolate_axis_hdl->coordinate.setValue(coordinate_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_axis_coordinate(interpolate_axis_Ptr interpolate_axis_hdl, char * coordinate, int coordinate_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(interpolate_axis_hdl->coordinate.getInheritedValue(), coordinate, coordinate_size))
      ERROR("void cxios_get_interpolate_axis_coordinate(interpolate_axis_Ptr interpolate_axis_hdl, char * coordinate, int coordinate_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_axis_coordinate(interpolate_axis_Ptr interpolate_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_axis_hdl->coordinate.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_axis_order(interpolate_axis_Ptr interpolate_axis_hdl, int order)
  {
    CTimer::get("XIOS").resume();
    interpolate_axis_hdl->order.setValue(order);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_axis_order(interpolate_axis_Ptr interpolate_axis_hdl, int* order)
  {
    CTimer::get("XIOS").resume();
    *order = interpolate_axis_hdl->order.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_axis_order(interpolate_axis_Ptr interpolate_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_axis_hdl->order.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_axis_type(interpolate_axis_Ptr interpolate_axis_hdl, const char * type, int type_size)
  {
    std::string type_str;
    if (!cstr2string(type, type_size, type_str)) return;
    CTimer::get("XIOS").resume();
    interpolate_axis_hdl->type.setValue(type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_axis_type(interpolate_axis_Ptr interpolate_axis_hdl, char * type, int type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(interpolate_axis_hdl->type.getInheritedValue(), type, type_size))
      ERROR("void cxios_get_interpolate_axis_type(interpolate_axis_Ptr interpolate_axis_hdl, char * type, int type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_axis_type(interpolate_axis_Ptr interpolate_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_axis_hdl->type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
