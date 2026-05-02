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
  typedef xios::CComputeConnectivityDomain* compute_connectivity_domain_Ptr;

  void cxios_set_compute_connectivity_domain_local_neighbor(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, int* local_neighbor, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,2> tmp(local_neighbor, shape(extent[0], extent[1]), neverDeleteData);
    compute_connectivity_domain_hdl->local_neighbor.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_compute_connectivity_domain_local_neighbor(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, int* local_neighbor, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,2> tmp(local_neighbor, shape(extent[0], extent[1]), neverDeleteData);
    tmp=compute_connectivity_domain_hdl->local_neighbor.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_compute_connectivity_domain_local_neighbor(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = compute_connectivity_domain_hdl->local_neighbor.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_compute_connectivity_domain_n_neighbor(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, int* n_neighbor, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(n_neighbor, shape(extent[0]), neverDeleteData);
    compute_connectivity_domain_hdl->n_neighbor.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_compute_connectivity_domain_n_neighbor(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, int* n_neighbor, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(n_neighbor, shape(extent[0]), neverDeleteData);
    tmp=compute_connectivity_domain_hdl->n_neighbor.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_compute_connectivity_domain_n_neighbor(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = compute_connectivity_domain_hdl->n_neighbor.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_compute_connectivity_domain_n_neighbor_max(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, int n_neighbor_max)
  {
    CTimer::get("XIOS").resume();
    compute_connectivity_domain_hdl->n_neighbor_max.setValue(n_neighbor_max);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_compute_connectivity_domain_n_neighbor_max(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, int* n_neighbor_max)
  {
    CTimer::get("XIOS").resume();
    *n_neighbor_max = compute_connectivity_domain_hdl->n_neighbor_max.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_compute_connectivity_domain_n_neighbor_max(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = compute_connectivity_domain_hdl->n_neighbor_max.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_compute_connectivity_domain_type(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, const char * type, int type_size)
  {
    std::string type_str;
    if (!cstr2string(type, type_size, type_str)) return;
    CTimer::get("XIOS").resume();
    compute_connectivity_domain_hdl->type.fromString(type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_compute_connectivity_domain_type(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, char * type, int type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(compute_connectivity_domain_hdl->type.getInheritedStringValue(), type, type_size))
      ERROR("void cxios_get_compute_connectivity_domain_type(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl, char * type, int type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_compute_connectivity_domain_type(compute_connectivity_domain_Ptr compute_connectivity_domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = compute_connectivity_domain_hdl->type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
