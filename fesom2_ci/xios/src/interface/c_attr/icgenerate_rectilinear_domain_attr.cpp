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
  typedef xios::CGenerateRectilinearDomain* generate_rectilinear_domain_Ptr;

  void cxios_set_generate_rectilinear_domain_bounds_lat_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double bounds_lat_end)
  {
    CTimer::get("XIOS").resume();
    generate_rectilinear_domain_hdl->bounds_lat_end.setValue(bounds_lat_end);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_generate_rectilinear_domain_bounds_lat_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double* bounds_lat_end)
  {
    CTimer::get("XIOS").resume();
    *bounds_lat_end = generate_rectilinear_domain_hdl->bounds_lat_end.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_generate_rectilinear_domain_bounds_lat_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = generate_rectilinear_domain_hdl->bounds_lat_end.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_generate_rectilinear_domain_bounds_lat_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double bounds_lat_start)
  {
    CTimer::get("XIOS").resume();
    generate_rectilinear_domain_hdl->bounds_lat_start.setValue(bounds_lat_start);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_generate_rectilinear_domain_bounds_lat_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double* bounds_lat_start)
  {
    CTimer::get("XIOS").resume();
    *bounds_lat_start = generate_rectilinear_domain_hdl->bounds_lat_start.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_generate_rectilinear_domain_bounds_lat_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = generate_rectilinear_domain_hdl->bounds_lat_start.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_generate_rectilinear_domain_bounds_lon_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double bounds_lon_end)
  {
    CTimer::get("XIOS").resume();
    generate_rectilinear_domain_hdl->bounds_lon_end.setValue(bounds_lon_end);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_generate_rectilinear_domain_bounds_lon_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double* bounds_lon_end)
  {
    CTimer::get("XIOS").resume();
    *bounds_lon_end = generate_rectilinear_domain_hdl->bounds_lon_end.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_generate_rectilinear_domain_bounds_lon_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = generate_rectilinear_domain_hdl->bounds_lon_end.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_generate_rectilinear_domain_bounds_lon_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double bounds_lon_start)
  {
    CTimer::get("XIOS").resume();
    generate_rectilinear_domain_hdl->bounds_lon_start.setValue(bounds_lon_start);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_generate_rectilinear_domain_bounds_lon_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double* bounds_lon_start)
  {
    CTimer::get("XIOS").resume();
    *bounds_lon_start = generate_rectilinear_domain_hdl->bounds_lon_start.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_generate_rectilinear_domain_bounds_lon_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = generate_rectilinear_domain_hdl->bounds_lon_start.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_generate_rectilinear_domain_lat_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double lat_end)
  {
    CTimer::get("XIOS").resume();
    generate_rectilinear_domain_hdl->lat_end.setValue(lat_end);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_generate_rectilinear_domain_lat_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double* lat_end)
  {
    CTimer::get("XIOS").resume();
    *lat_end = generate_rectilinear_domain_hdl->lat_end.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_generate_rectilinear_domain_lat_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = generate_rectilinear_domain_hdl->lat_end.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_generate_rectilinear_domain_lat_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double lat_start)
  {
    CTimer::get("XIOS").resume();
    generate_rectilinear_domain_hdl->lat_start.setValue(lat_start);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_generate_rectilinear_domain_lat_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double* lat_start)
  {
    CTimer::get("XIOS").resume();
    *lat_start = generate_rectilinear_domain_hdl->lat_start.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_generate_rectilinear_domain_lat_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = generate_rectilinear_domain_hdl->lat_start.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_generate_rectilinear_domain_lon_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double lon_end)
  {
    CTimer::get("XIOS").resume();
    generate_rectilinear_domain_hdl->lon_end.setValue(lon_end);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_generate_rectilinear_domain_lon_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double* lon_end)
  {
    CTimer::get("XIOS").resume();
    *lon_end = generate_rectilinear_domain_hdl->lon_end.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_generate_rectilinear_domain_lon_end(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = generate_rectilinear_domain_hdl->lon_end.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_generate_rectilinear_domain_lon_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double lon_start)
  {
    CTimer::get("XIOS").resume();
    generate_rectilinear_domain_hdl->lon_start.setValue(lon_start);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_generate_rectilinear_domain_lon_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl, double* lon_start)
  {
    CTimer::get("XIOS").resume();
    *lon_start = generate_rectilinear_domain_hdl->lon_start.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_generate_rectilinear_domain_lon_start(generate_rectilinear_domain_Ptr generate_rectilinear_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = generate_rectilinear_domain_hdl->lon_start.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
