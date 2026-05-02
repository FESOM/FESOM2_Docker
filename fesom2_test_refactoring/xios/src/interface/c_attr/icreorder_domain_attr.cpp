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
  typedef xios::CReorderDomain* reorder_domain_Ptr;

  void cxios_set_reorder_domain_invert_lat(reorder_domain_Ptr reorder_domain_hdl, bool invert_lat)
  {
    CTimer::get("XIOS").resume();
    reorder_domain_hdl->invert_lat.setValue(invert_lat);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_reorder_domain_invert_lat(reorder_domain_Ptr reorder_domain_hdl, bool* invert_lat)
  {
    CTimer::get("XIOS").resume();
    *invert_lat = reorder_domain_hdl->invert_lat.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_reorder_domain_invert_lat(reorder_domain_Ptr reorder_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = reorder_domain_hdl->invert_lat.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_reorder_domain_max_lon(reorder_domain_Ptr reorder_domain_hdl, double max_lon)
  {
    CTimer::get("XIOS").resume();
    reorder_domain_hdl->max_lon.setValue(max_lon);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_reorder_domain_max_lon(reorder_domain_Ptr reorder_domain_hdl, double* max_lon)
  {
    CTimer::get("XIOS").resume();
    *max_lon = reorder_domain_hdl->max_lon.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_reorder_domain_max_lon(reorder_domain_Ptr reorder_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = reorder_domain_hdl->max_lon.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_reorder_domain_min_lon(reorder_domain_Ptr reorder_domain_hdl, double min_lon)
  {
    CTimer::get("XIOS").resume();
    reorder_domain_hdl->min_lon.setValue(min_lon);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_reorder_domain_min_lon(reorder_domain_Ptr reorder_domain_hdl, double* min_lon)
  {
    CTimer::get("XIOS").resume();
    *min_lon = reorder_domain_hdl->min_lon.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_reorder_domain_min_lon(reorder_domain_Ptr reorder_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = reorder_domain_hdl->min_lon.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_reorder_domain_shift_lon_fraction(reorder_domain_Ptr reorder_domain_hdl, double shift_lon_fraction)
  {
    CTimer::get("XIOS").resume();
    reorder_domain_hdl->shift_lon_fraction.setValue(shift_lon_fraction);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_reorder_domain_shift_lon_fraction(reorder_domain_Ptr reorder_domain_hdl, double* shift_lon_fraction)
  {
    CTimer::get("XIOS").resume();
    *shift_lon_fraction = reorder_domain_hdl->shift_lon_fraction.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_reorder_domain_shift_lon_fraction(reorder_domain_Ptr reorder_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = reorder_domain_hdl->shift_lon_fraction.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
