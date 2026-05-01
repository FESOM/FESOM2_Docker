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
  typedef xios::CGridGroup* gridgroup_Ptr;

  void cxios_set_gridgroup_comment(gridgroup_Ptr gridgroup_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    gridgroup_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_comment(gridgroup_Ptr gridgroup_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(gridgroup_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_gridgroup_comment(gridgroup_Ptr gridgroup_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_comment(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_description(gridgroup_Ptr gridgroup_hdl, const char * description, int description_size)
  {
    std::string description_str;
    if (!cstr2string(description, description_size, description_str)) return;
    CTimer::get("XIOS").resume();
    gridgroup_hdl->description.setValue(description_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_description(gridgroup_Ptr gridgroup_hdl, char * description, int description_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(gridgroup_hdl->description.getInheritedValue(), description, description_size))
      ERROR("void cxios_get_gridgroup_description(gridgroup_Ptr gridgroup_hdl, char * description, int description_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_description(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->description.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_group_ref(gridgroup_Ptr gridgroup_hdl, const char * group_ref, int group_ref_size)
  {
    std::string group_ref_str;
    if (!cstr2string(group_ref, group_ref_size, group_ref_str)) return;
    CTimer::get("XIOS").resume();
    gridgroup_hdl->group_ref.setValue(group_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_group_ref(gridgroup_Ptr gridgroup_hdl, char * group_ref, int group_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(gridgroup_hdl->group_ref.getInheritedValue(), group_ref, group_ref_size))
      ERROR("void cxios_get_gridgroup_group_ref(gridgroup_Ptr gridgroup_hdl, char * group_ref, int group_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_group_ref(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->group_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_mask_0d(gridgroup_Ptr gridgroup_hdl, bool* mask_0d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_0d, shape(extent[0]), neverDeleteData);
    gridgroup_hdl->mask_0d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_mask_0d(gridgroup_Ptr gridgroup_hdl, bool* mask_0d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_0d, shape(extent[0]), neverDeleteData);
    tmp=gridgroup_hdl->mask_0d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_mask_0d(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->mask_0d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_mask_1d(gridgroup_Ptr gridgroup_hdl, bool* mask_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_1d, shape(extent[0]), neverDeleteData);
    gridgroup_hdl->mask_1d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_mask_1d(gridgroup_Ptr gridgroup_hdl, bool* mask_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_1d, shape(extent[0]), neverDeleteData);
    tmp=gridgroup_hdl->mask_1d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_mask_1d(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->mask_1d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_mask_2d(gridgroup_Ptr gridgroup_hdl, bool* mask_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,2> tmp(mask_2d, shape(extent[0], extent[1]), neverDeleteData);
    gridgroup_hdl->mask_2d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_mask_2d(gridgroup_Ptr gridgroup_hdl, bool* mask_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,2> tmp(mask_2d, shape(extent[0], extent[1]), neverDeleteData);
    tmp=gridgroup_hdl->mask_2d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_mask_2d(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->mask_2d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_mask_3d(gridgroup_Ptr gridgroup_hdl, bool* mask_3d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,3> tmp(mask_3d, shape(extent[0], extent[1], extent[2]), neverDeleteData);
    gridgroup_hdl->mask_3d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_mask_3d(gridgroup_Ptr gridgroup_hdl, bool* mask_3d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,3> tmp(mask_3d, shape(extent[0], extent[1], extent[2]), neverDeleteData);
    tmp=gridgroup_hdl->mask_3d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_mask_3d(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->mask_3d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_mask_4d(gridgroup_Ptr gridgroup_hdl, bool* mask_4d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,4> tmp(mask_4d, shape(extent[0], extent[1], extent[2], extent[3]), neverDeleteData);
    gridgroup_hdl->mask_4d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_mask_4d(gridgroup_Ptr gridgroup_hdl, bool* mask_4d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,4> tmp(mask_4d, shape(extent[0], extent[1], extent[2], extent[3]), neverDeleteData);
    tmp=gridgroup_hdl->mask_4d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_mask_4d(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->mask_4d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_mask_5d(gridgroup_Ptr gridgroup_hdl, bool* mask_5d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,5> tmp(mask_5d, shape(extent[0], extent[1], extent[2], extent[3], extent[4]), neverDeleteData);
    gridgroup_hdl->mask_5d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_mask_5d(gridgroup_Ptr gridgroup_hdl, bool* mask_5d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,5> tmp(mask_5d, shape(extent[0], extent[1], extent[2], extent[3], extent[4]), neverDeleteData);
    tmp=gridgroup_hdl->mask_5d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_mask_5d(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->mask_5d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_mask_6d(gridgroup_Ptr gridgroup_hdl, bool* mask_6d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,6> tmp(mask_6d, shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]), neverDeleteData);
    gridgroup_hdl->mask_6d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_mask_6d(gridgroup_Ptr gridgroup_hdl, bool* mask_6d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,6> tmp(mask_6d, shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]), neverDeleteData);
    tmp=gridgroup_hdl->mask_6d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_mask_6d(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->mask_6d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_mask_7d(gridgroup_Ptr gridgroup_hdl, bool* mask_7d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,7> tmp(mask_7d, shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5], extent[6]), neverDeleteData);
    gridgroup_hdl->mask_7d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_mask_7d(gridgroup_Ptr gridgroup_hdl, bool* mask_7d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,7> tmp(mask_7d, shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5], extent[6]), neverDeleteData);
    tmp=gridgroup_hdl->mask_7d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_mask_7d(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->mask_7d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_gridgroup_name(gridgroup_Ptr gridgroup_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    gridgroup_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_gridgroup_name(gridgroup_Ptr gridgroup_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(gridgroup_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_gridgroup_name(gridgroup_Ptr gridgroup_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_gridgroup_name(gridgroup_Ptr gridgroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = gridgroup_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
