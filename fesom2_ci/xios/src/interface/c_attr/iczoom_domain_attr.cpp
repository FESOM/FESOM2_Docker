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
  typedef xios::CZoomDomain* zoom_domain_Ptr;

  void cxios_set_zoom_domain_ibegin(zoom_domain_Ptr zoom_domain_hdl, int ibegin)
  {
    CTimer::get("XIOS").resume();
    zoom_domain_hdl->ibegin.setValue(ibegin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_zoom_domain_ibegin(zoom_domain_Ptr zoom_domain_hdl, int* ibegin)
  {
    CTimer::get("XIOS").resume();
    *ibegin = zoom_domain_hdl->ibegin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_zoom_domain_ibegin(zoom_domain_Ptr zoom_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = zoom_domain_hdl->ibegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_zoom_domain_jbegin(zoom_domain_Ptr zoom_domain_hdl, int jbegin)
  {
    CTimer::get("XIOS").resume();
    zoom_domain_hdl->jbegin.setValue(jbegin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_zoom_domain_jbegin(zoom_domain_Ptr zoom_domain_hdl, int* jbegin)
  {
    CTimer::get("XIOS").resume();
    *jbegin = zoom_domain_hdl->jbegin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_zoom_domain_jbegin(zoom_domain_Ptr zoom_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = zoom_domain_hdl->jbegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_zoom_domain_ni(zoom_domain_Ptr zoom_domain_hdl, int ni)
  {
    CTimer::get("XIOS").resume();
    zoom_domain_hdl->ni.setValue(ni);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_zoom_domain_ni(zoom_domain_Ptr zoom_domain_hdl, int* ni)
  {
    CTimer::get("XIOS").resume();
    *ni = zoom_domain_hdl->ni.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_zoom_domain_ni(zoom_domain_Ptr zoom_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = zoom_domain_hdl->ni.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_zoom_domain_nj(zoom_domain_Ptr zoom_domain_hdl, int nj)
  {
    CTimer::get("XIOS").resume();
    zoom_domain_hdl->nj.setValue(nj);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_zoom_domain_nj(zoom_domain_Ptr zoom_domain_hdl, int* nj)
  {
    CTimer::get("XIOS").resume();
    *nj = zoom_domain_hdl->nj.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_zoom_domain_nj(zoom_domain_Ptr zoom_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = zoom_domain_hdl->nj.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
