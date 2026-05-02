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
  typedef xios::CInterpolateDomain* interpolate_domain_Ptr;

  void cxios_set_interpolate_domain_detect_missing_value(interpolate_domain_Ptr interpolate_domain_hdl, bool detect_missing_value)
  {
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->detect_missing_value.setValue(detect_missing_value);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_detect_missing_value(interpolate_domain_Ptr interpolate_domain_hdl, bool* detect_missing_value)
  {
    CTimer::get("XIOS").resume();
    *detect_missing_value = interpolate_domain_hdl->detect_missing_value.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_detect_missing_value(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->detect_missing_value.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_domain_mode(interpolate_domain_Ptr interpolate_domain_hdl, const char * mode, int mode_size)
  {
    std::string mode_str;
    if (!cstr2string(mode, mode_size, mode_str)) return;
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->mode.fromString(mode_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_mode(interpolate_domain_Ptr interpolate_domain_hdl, char * mode, int mode_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(interpolate_domain_hdl->mode.getInheritedStringValue(), mode, mode_size))
      ERROR("void cxios_get_interpolate_domain_mode(interpolate_domain_Ptr interpolate_domain_hdl, char * mode, int mode_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_mode(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->mode.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_domain_order(interpolate_domain_Ptr interpolate_domain_hdl, int order)
  {
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->order.setValue(order);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_order(interpolate_domain_Ptr interpolate_domain_hdl, int* order)
  {
    CTimer::get("XIOS").resume();
    *order = interpolate_domain_hdl->order.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_order(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->order.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_domain_quantity(interpolate_domain_Ptr interpolate_domain_hdl, bool quantity)
  {
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->quantity.setValue(quantity);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_quantity(interpolate_domain_Ptr interpolate_domain_hdl, bool* quantity)
  {
    CTimer::get("XIOS").resume();
    *quantity = interpolate_domain_hdl->quantity.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_quantity(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->quantity.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_domain_read_write_convention(interpolate_domain_Ptr interpolate_domain_hdl, const char * read_write_convention, int read_write_convention_size)
  {
    std::string read_write_convention_str;
    if (!cstr2string(read_write_convention, read_write_convention_size, read_write_convention_str)) return;
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->read_write_convention.fromString(read_write_convention_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_read_write_convention(interpolate_domain_Ptr interpolate_domain_hdl, char * read_write_convention, int read_write_convention_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(interpolate_domain_hdl->read_write_convention.getInheritedStringValue(), read_write_convention, read_write_convention_size))
      ERROR("void cxios_get_interpolate_domain_read_write_convention(interpolate_domain_Ptr interpolate_domain_hdl, char * read_write_convention, int read_write_convention_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_read_write_convention(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->read_write_convention.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_domain_renormalize(interpolate_domain_Ptr interpolate_domain_hdl, bool renormalize)
  {
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->renormalize.setValue(renormalize);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_renormalize(interpolate_domain_Ptr interpolate_domain_hdl, bool* renormalize)
  {
    CTimer::get("XIOS").resume();
    *renormalize = interpolate_domain_hdl->renormalize.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_renormalize(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->renormalize.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_domain_use_area(interpolate_domain_Ptr interpolate_domain_hdl, bool use_area)
  {
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->use_area.setValue(use_area);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_use_area(interpolate_domain_Ptr interpolate_domain_hdl, bool* use_area)
  {
    CTimer::get("XIOS").resume();
    *use_area = interpolate_domain_hdl->use_area.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_use_area(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->use_area.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_domain_weight_filename(interpolate_domain_Ptr interpolate_domain_hdl, const char * weight_filename, int weight_filename_size)
  {
    std::string weight_filename_str;
    if (!cstr2string(weight_filename, weight_filename_size, weight_filename_str)) return;
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->weight_filename.setValue(weight_filename_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_weight_filename(interpolate_domain_Ptr interpolate_domain_hdl, char * weight_filename, int weight_filename_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(interpolate_domain_hdl->weight_filename.getInheritedValue(), weight_filename, weight_filename_size))
      ERROR("void cxios_get_interpolate_domain_weight_filename(interpolate_domain_Ptr interpolate_domain_hdl, char * weight_filename, int weight_filename_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_weight_filename(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->weight_filename.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_interpolate_domain_write_weight(interpolate_domain_Ptr interpolate_domain_hdl, bool write_weight)
  {
    CTimer::get("XIOS").resume();
    interpolate_domain_hdl->write_weight.setValue(write_weight);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_interpolate_domain_write_weight(interpolate_domain_Ptr interpolate_domain_hdl, bool* write_weight)
  {
    CTimer::get("XIOS").resume();
    *write_weight = interpolate_domain_hdl->write_weight.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_interpolate_domain_write_weight(interpolate_domain_Ptr interpolate_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = interpolate_domain_hdl->write_weight.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
