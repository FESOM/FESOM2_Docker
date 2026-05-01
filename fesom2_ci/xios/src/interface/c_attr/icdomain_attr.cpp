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
  typedef xios::CDomain* domain_Ptr;

  void cxios_set_domain_area(domain_Ptr domain_hdl, double* area, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(area, shape(extent[0], extent[1]), neverDeleteData);
    domain_hdl->area.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_area(domain_Ptr domain_hdl, double* area, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(area, shape(extent[0], extent[1]), neverDeleteData);
    tmp=domain_hdl->area.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_area(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->area.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_bounds_lat_1d(domain_Ptr domain_hdl, double* bounds_lat_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(bounds_lat_1d, shape(extent[0], extent[1]), neverDeleteData);
    domain_hdl->bounds_lat_1d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_bounds_lat_1d(domain_Ptr domain_hdl, double* bounds_lat_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(bounds_lat_1d, shape(extent[0], extent[1]), neverDeleteData);
    tmp=domain_hdl->bounds_lat_1d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_bounds_lat_1d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->bounds_lat_1d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_bounds_lat_2d(domain_Ptr domain_hdl, double* bounds_lat_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,3> tmp(bounds_lat_2d, shape(extent[0], extent[1], extent[2]), neverDeleteData);
    domain_hdl->bounds_lat_2d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_bounds_lat_2d(domain_Ptr domain_hdl, double* bounds_lat_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,3> tmp(bounds_lat_2d, shape(extent[0], extent[1], extent[2]), neverDeleteData);
    tmp=domain_hdl->bounds_lat_2d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_bounds_lat_2d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->bounds_lat_2d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_bounds_lat_name(domain_Ptr domain_hdl, const char * bounds_lat_name, int bounds_lat_name_size)
  {
    std::string bounds_lat_name_str;
    if (!cstr2string(bounds_lat_name, bounds_lat_name_size, bounds_lat_name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->bounds_lat_name.setValue(bounds_lat_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_bounds_lat_name(domain_Ptr domain_hdl, char * bounds_lat_name, int bounds_lat_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->bounds_lat_name.getInheritedValue(), bounds_lat_name, bounds_lat_name_size))
      ERROR("void cxios_get_domain_bounds_lat_name(domain_Ptr domain_hdl, char * bounds_lat_name, int bounds_lat_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_bounds_lat_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->bounds_lat_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_bounds_lon_1d(domain_Ptr domain_hdl, double* bounds_lon_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(bounds_lon_1d, shape(extent[0], extent[1]), neverDeleteData);
    domain_hdl->bounds_lon_1d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_bounds_lon_1d(domain_Ptr domain_hdl, double* bounds_lon_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(bounds_lon_1d, shape(extent[0], extent[1]), neverDeleteData);
    tmp=domain_hdl->bounds_lon_1d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_bounds_lon_1d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->bounds_lon_1d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_bounds_lon_2d(domain_Ptr domain_hdl, double* bounds_lon_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,3> tmp(bounds_lon_2d, shape(extent[0], extent[1], extent[2]), neverDeleteData);
    domain_hdl->bounds_lon_2d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_bounds_lon_2d(domain_Ptr domain_hdl, double* bounds_lon_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,3> tmp(bounds_lon_2d, shape(extent[0], extent[1], extent[2]), neverDeleteData);
    tmp=domain_hdl->bounds_lon_2d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_bounds_lon_2d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->bounds_lon_2d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_bounds_lon_name(domain_Ptr domain_hdl, const char * bounds_lon_name, int bounds_lon_name_size)
  {
    std::string bounds_lon_name_str;
    if (!cstr2string(bounds_lon_name, bounds_lon_name_size, bounds_lon_name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->bounds_lon_name.setValue(bounds_lon_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_bounds_lon_name(domain_Ptr domain_hdl, char * bounds_lon_name, int bounds_lon_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->bounds_lon_name.getInheritedValue(), bounds_lon_name, bounds_lon_name_size))
      ERROR("void cxios_get_domain_bounds_lon_name(domain_Ptr domain_hdl, char * bounds_lon_name, int bounds_lon_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_bounds_lon_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->bounds_lon_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_comment(domain_Ptr domain_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_comment(domain_Ptr domain_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_domain_comment(domain_Ptr domain_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_comment(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_data_dim(domain_Ptr domain_hdl, int data_dim)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->data_dim.setValue(data_dim);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_data_dim(domain_Ptr domain_hdl, int* data_dim)
  {
    CTimer::get("XIOS").resume();
    *data_dim = domain_hdl->data_dim.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_data_dim(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->data_dim.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_data_i_index(domain_Ptr domain_hdl, int* data_i_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(data_i_index, shape(extent[0]), neverDeleteData);
    domain_hdl->data_i_index.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_data_i_index(domain_Ptr domain_hdl, int* data_i_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(data_i_index, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->data_i_index.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_data_i_index(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->data_i_index.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_data_ibegin(domain_Ptr domain_hdl, int data_ibegin)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->data_ibegin.setValue(data_ibegin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_data_ibegin(domain_Ptr domain_hdl, int* data_ibegin)
  {
    CTimer::get("XIOS").resume();
    *data_ibegin = domain_hdl->data_ibegin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_data_ibegin(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->data_ibegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_data_j_index(domain_Ptr domain_hdl, int* data_j_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(data_j_index, shape(extent[0]), neverDeleteData);
    domain_hdl->data_j_index.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_data_j_index(domain_Ptr domain_hdl, int* data_j_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(data_j_index, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->data_j_index.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_data_j_index(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->data_j_index.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_data_jbegin(domain_Ptr domain_hdl, int data_jbegin)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->data_jbegin.setValue(data_jbegin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_data_jbegin(domain_Ptr domain_hdl, int* data_jbegin)
  {
    CTimer::get("XIOS").resume();
    *data_jbegin = domain_hdl->data_jbegin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_data_jbegin(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->data_jbegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_data_ni(domain_Ptr domain_hdl, int data_ni)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->data_ni.setValue(data_ni);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_data_ni(domain_Ptr domain_hdl, int* data_ni)
  {
    CTimer::get("XIOS").resume();
    *data_ni = domain_hdl->data_ni.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_data_ni(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->data_ni.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_data_nj(domain_Ptr domain_hdl, int data_nj)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->data_nj.setValue(data_nj);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_data_nj(domain_Ptr domain_hdl, int* data_nj)
  {
    CTimer::get("XIOS").resume();
    *data_nj = domain_hdl->data_nj.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_data_nj(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->data_nj.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_dim_i_name(domain_Ptr domain_hdl, const char * dim_i_name, int dim_i_name_size)
  {
    std::string dim_i_name_str;
    if (!cstr2string(dim_i_name, dim_i_name_size, dim_i_name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->dim_i_name.setValue(dim_i_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_dim_i_name(domain_Ptr domain_hdl, char * dim_i_name, int dim_i_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->dim_i_name.getInheritedValue(), dim_i_name, dim_i_name_size))
      ERROR("void cxios_get_domain_dim_i_name(domain_Ptr domain_hdl, char * dim_i_name, int dim_i_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_dim_i_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->dim_i_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_dim_j_name(domain_Ptr domain_hdl, const char * dim_j_name, int dim_j_name_size)
  {
    std::string dim_j_name_str;
    if (!cstr2string(dim_j_name, dim_j_name_size, dim_j_name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->dim_j_name.setValue(dim_j_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_dim_j_name(domain_Ptr domain_hdl, char * dim_j_name, int dim_j_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->dim_j_name.getInheritedValue(), dim_j_name, dim_j_name_size))
      ERROR("void cxios_get_domain_dim_j_name(domain_Ptr domain_hdl, char * dim_j_name, int dim_j_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_dim_j_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->dim_j_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_domain_ref(domain_Ptr domain_hdl, const char * domain_ref, int domain_ref_size)
  {
    std::string domain_ref_str;
    if (!cstr2string(domain_ref, domain_ref_size, domain_ref_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->domain_ref.setValue(domain_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_domain_ref(domain_Ptr domain_hdl, char * domain_ref, int domain_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->domain_ref.getInheritedValue(), domain_ref, domain_ref_size))
      ERROR("void cxios_get_domain_domain_ref(domain_Ptr domain_hdl, char * domain_ref, int domain_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_domain_ref(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->domain_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_i_index(domain_Ptr domain_hdl, int* i_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(i_index, shape(extent[0]), neverDeleteData);
    domain_hdl->i_index.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_i_index(domain_Ptr domain_hdl, int* i_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(i_index, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->i_index.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_i_index(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->i_index.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_ibegin(domain_Ptr domain_hdl, int ibegin)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->ibegin.setValue(ibegin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_ibegin(domain_Ptr domain_hdl, int* ibegin)
  {
    CTimer::get("XIOS").resume();
    *ibegin = domain_hdl->ibegin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_ibegin(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->ibegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_j_index(domain_Ptr domain_hdl, int* j_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(j_index, shape(extent[0]), neverDeleteData);
    domain_hdl->j_index.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_j_index(domain_Ptr domain_hdl, int* j_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(j_index, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->j_index.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_j_index(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->j_index.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_jbegin(domain_Ptr domain_hdl, int jbegin)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->jbegin.setValue(jbegin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_jbegin(domain_Ptr domain_hdl, int* jbegin)
  {
    CTimer::get("XIOS").resume();
    *jbegin = domain_hdl->jbegin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_jbegin(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->jbegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_lat_name(domain_Ptr domain_hdl, const char * lat_name, int lat_name_size)
  {
    std::string lat_name_str;
    if (!cstr2string(lat_name, lat_name_size, lat_name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->lat_name.setValue(lat_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_lat_name(domain_Ptr domain_hdl, char * lat_name, int lat_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->lat_name.getInheritedValue(), lat_name, lat_name_size))
      ERROR("void cxios_get_domain_lat_name(domain_Ptr domain_hdl, char * lat_name, int lat_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_lat_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->lat_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_latvalue_1d(domain_Ptr domain_hdl, double* latvalue_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(latvalue_1d, shape(extent[0]), neverDeleteData);
    domain_hdl->latvalue_1d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_latvalue_1d(domain_Ptr domain_hdl, double* latvalue_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(latvalue_1d, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->latvalue_1d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_latvalue_1d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->latvalue_1d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_latvalue_2d(domain_Ptr domain_hdl, double* latvalue_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(latvalue_2d, shape(extent[0], extent[1]), neverDeleteData);
    domain_hdl->latvalue_2d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_latvalue_2d(domain_Ptr domain_hdl, double* latvalue_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(latvalue_2d, shape(extent[0], extent[1]), neverDeleteData);
    tmp=domain_hdl->latvalue_2d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_latvalue_2d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->latvalue_2d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_lon_name(domain_Ptr domain_hdl, const char * lon_name, int lon_name_size)
  {
    std::string lon_name_str;
    if (!cstr2string(lon_name, lon_name_size, lon_name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->lon_name.setValue(lon_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_lon_name(domain_Ptr domain_hdl, char * lon_name, int lon_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->lon_name.getInheritedValue(), lon_name, lon_name_size))
      ERROR("void cxios_get_domain_lon_name(domain_Ptr domain_hdl, char * lon_name, int lon_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_lon_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->lon_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_long_name(domain_Ptr domain_hdl, const char * long_name, int long_name_size)
  {
    std::string long_name_str;
    if (!cstr2string(long_name, long_name_size, long_name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->long_name.setValue(long_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_long_name(domain_Ptr domain_hdl, char * long_name, int long_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->long_name.getInheritedValue(), long_name, long_name_size))
      ERROR("void cxios_get_domain_long_name(domain_Ptr domain_hdl, char * long_name, int long_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_long_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->long_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_lonvalue_1d(domain_Ptr domain_hdl, double* lonvalue_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(lonvalue_1d, shape(extent[0]), neverDeleteData);
    domain_hdl->lonvalue_1d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_lonvalue_1d(domain_Ptr domain_hdl, double* lonvalue_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(lonvalue_1d, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->lonvalue_1d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_lonvalue_1d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->lonvalue_1d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_lonvalue_2d(domain_Ptr domain_hdl, double* lonvalue_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(lonvalue_2d, shape(extent[0], extent[1]), neverDeleteData);
    domain_hdl->lonvalue_2d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_lonvalue_2d(domain_Ptr domain_hdl, double* lonvalue_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(lonvalue_2d, shape(extent[0], extent[1]), neverDeleteData);
    tmp=domain_hdl->lonvalue_2d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_lonvalue_2d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->lonvalue_2d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_mask_1d(domain_Ptr domain_hdl, bool* mask_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_1d, shape(extent[0]), neverDeleteData);
    domain_hdl->mask_1d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_mask_1d(domain_Ptr domain_hdl, bool* mask_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_1d, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->mask_1d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_mask_1d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->mask_1d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_mask_2d(domain_Ptr domain_hdl, bool* mask_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,2> tmp(mask_2d, shape(extent[0], extent[1]), neverDeleteData);
    domain_hdl->mask_2d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_mask_2d(domain_Ptr domain_hdl, bool* mask_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,2> tmp(mask_2d, shape(extent[0], extent[1]), neverDeleteData);
    tmp=domain_hdl->mask_2d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_mask_2d(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->mask_2d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_name(domain_Ptr domain_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_name(domain_Ptr domain_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_domain_name(domain_Ptr domain_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_ni(domain_Ptr domain_hdl, int ni)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->ni.setValue(ni);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_ni(domain_Ptr domain_hdl, int* ni)
  {
    CTimer::get("XIOS").resume();
    *ni = domain_hdl->ni.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_ni(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->ni.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_ni_glo(domain_Ptr domain_hdl, int ni_glo)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->ni_glo.setValue(ni_glo);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_ni_glo(domain_Ptr domain_hdl, int* ni_glo)
  {
    CTimer::get("XIOS").resume();
    *ni_glo = domain_hdl->ni_glo.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_ni_glo(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->ni_glo.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_nj(domain_Ptr domain_hdl, int nj)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->nj.setValue(nj);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_nj(domain_Ptr domain_hdl, int* nj)
  {
    CTimer::get("XIOS").resume();
    *nj = domain_hdl->nj.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_nj(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->nj.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_nj_glo(domain_Ptr domain_hdl, int nj_glo)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->nj_glo.setValue(nj_glo);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_nj_glo(domain_Ptr domain_hdl, int* nj_glo)
  {
    CTimer::get("XIOS").resume();
    *nj_glo = domain_hdl->nj_glo.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_nj_glo(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->nj_glo.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_ntiles(domain_Ptr domain_hdl, int ntiles)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->ntiles.setValue(ntiles);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_ntiles(domain_Ptr domain_hdl, int* ntiles)
  {
    CTimer::get("XIOS").resume();
    *ntiles = domain_hdl->ntiles.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_ntiles(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->ntiles.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_nvertex(domain_Ptr domain_hdl, int nvertex)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->nvertex.setValue(nvertex);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_nvertex(domain_Ptr domain_hdl, int* nvertex)
  {
    CTimer::get("XIOS").resume();
    *nvertex = domain_hdl->nvertex.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_nvertex(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->nvertex.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_prec(domain_Ptr domain_hdl, int prec)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->prec.setValue(prec);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_prec(domain_Ptr domain_hdl, int* prec)
  {
    CTimer::get("XIOS").resume();
    *prec = domain_hdl->prec.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_prec(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->prec.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_radius(domain_Ptr domain_hdl, double radius)
  {
    CTimer::get("XIOS").resume();
    domain_hdl->radius.setValue(radius);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_radius(domain_Ptr domain_hdl, double* radius)
  {
    CTimer::get("XIOS").resume();
    *radius = domain_hdl->radius.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_radius(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->radius.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_standard_name(domain_Ptr domain_hdl, const char * standard_name, int standard_name_size)
  {
    std::string standard_name_str;
    if (!cstr2string(standard_name, standard_name_size, standard_name_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->standard_name.setValue(standard_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_standard_name(domain_Ptr domain_hdl, char * standard_name, int standard_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->standard_name.getInheritedValue(), standard_name, standard_name_size))
      ERROR("void cxios_get_domain_standard_name(domain_Ptr domain_hdl, char * standard_name, int standard_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_standard_name(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->standard_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_tile_data_ibegin(domain_Ptr domain_hdl, int* tile_data_ibegin, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_data_ibegin, shape(extent[0]), neverDeleteData);
    domain_hdl->tile_data_ibegin.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_tile_data_ibegin(domain_Ptr domain_hdl, int* tile_data_ibegin, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_data_ibegin, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->tile_data_ibegin.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_tile_data_ibegin(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->tile_data_ibegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_tile_data_jbegin(domain_Ptr domain_hdl, int* tile_data_jbegin, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_data_jbegin, shape(extent[0]), neverDeleteData);
    domain_hdl->tile_data_jbegin.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_tile_data_jbegin(domain_Ptr domain_hdl, int* tile_data_jbegin, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_data_jbegin, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->tile_data_jbegin.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_tile_data_jbegin(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->tile_data_jbegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_tile_data_ni(domain_Ptr domain_hdl, int* tile_data_ni, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_data_ni, shape(extent[0]), neverDeleteData);
    domain_hdl->tile_data_ni.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_tile_data_ni(domain_Ptr domain_hdl, int* tile_data_ni, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_data_ni, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->tile_data_ni.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_tile_data_ni(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->tile_data_ni.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_tile_data_nj(domain_Ptr domain_hdl, int* tile_data_nj, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_data_nj, shape(extent[0]), neverDeleteData);
    domain_hdl->tile_data_nj.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_tile_data_nj(domain_Ptr domain_hdl, int* tile_data_nj, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_data_nj, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->tile_data_nj.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_tile_data_nj(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->tile_data_nj.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_tile_ibegin(domain_Ptr domain_hdl, int* tile_ibegin, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_ibegin, shape(extent[0]), neverDeleteData);
    domain_hdl->tile_ibegin.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_tile_ibegin(domain_Ptr domain_hdl, int* tile_ibegin, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_ibegin, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->tile_ibegin.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_tile_ibegin(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->tile_ibegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_tile_jbegin(domain_Ptr domain_hdl, int* tile_jbegin, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_jbegin, shape(extent[0]), neverDeleteData);
    domain_hdl->tile_jbegin.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_tile_jbegin(domain_Ptr domain_hdl, int* tile_jbegin, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_jbegin, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->tile_jbegin.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_tile_jbegin(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->tile_jbegin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_tile_ni(domain_Ptr domain_hdl, int* tile_ni, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_ni, shape(extent[0]), neverDeleteData);
    domain_hdl->tile_ni.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_tile_ni(domain_Ptr domain_hdl, int* tile_ni, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_ni, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->tile_ni.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_tile_ni(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->tile_ni.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_tile_nj(domain_Ptr domain_hdl, int* tile_nj, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_nj, shape(extent[0]), neverDeleteData);
    domain_hdl->tile_nj.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_tile_nj(domain_Ptr domain_hdl, int* tile_nj, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(tile_nj, shape(extent[0]), neverDeleteData);
    tmp=domain_hdl->tile_nj.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_tile_nj(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->tile_nj.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_domain_type(domain_Ptr domain_hdl, const char * type, int type_size)
  {
    std::string type_str;
    if (!cstr2string(type, type_size, type_str)) return;
    CTimer::get("XIOS").resume();
    domain_hdl->type.fromString(type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_domain_type(domain_Ptr domain_hdl, char * type, int type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(domain_hdl->type.getInheritedStringValue(), type, type_size))
      ERROR("void cxios_get_domain_type(domain_Ptr domain_hdl, char * type, int type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_domain_type(domain_Ptr domain_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = domain_hdl->type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
