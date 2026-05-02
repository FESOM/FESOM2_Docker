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
  typedef xios::CZoomAxis* zoom_axis_Ptr;

  void cxios_set_zoom_axis_begin(zoom_axis_Ptr zoom_axis_hdl, int begin)
  {
    CTimer::get("XIOS").resume();
    zoom_axis_hdl->begin.setValue(begin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_zoom_axis_begin(zoom_axis_Ptr zoom_axis_hdl, int* begin)
  {
    CTimer::get("XIOS").resume();
    *begin = zoom_axis_hdl->begin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_zoom_axis_begin(zoom_axis_Ptr zoom_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = zoom_axis_hdl->begin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_zoom_axis_index(zoom_axis_Ptr zoom_axis_hdl, int* index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(index, shape(extent[0]), neverDeleteData);
    zoom_axis_hdl->index.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_zoom_axis_index(zoom_axis_Ptr zoom_axis_hdl, int* index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(index, shape(extent[0]), neverDeleteData);
    tmp=zoom_axis_hdl->index.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_zoom_axis_index(zoom_axis_Ptr zoom_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = zoom_axis_hdl->index.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_zoom_axis_n(zoom_axis_Ptr zoom_axis_hdl, int n)
  {
    CTimer::get("XIOS").resume();
    zoom_axis_hdl->n.setValue(n);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_zoom_axis_n(zoom_axis_Ptr zoom_axis_hdl, int* n)
  {
    CTimer::get("XIOS").resume();
    *n = zoom_axis_hdl->n.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_zoom_axis_n(zoom_axis_Ptr zoom_axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = zoom_axis_hdl->n.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
