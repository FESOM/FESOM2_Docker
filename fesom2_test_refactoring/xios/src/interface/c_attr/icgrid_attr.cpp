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
  typedef xios::CGrid* grid_Ptr;

  void cxios_set_grid_comment(grid_Ptr grid_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    grid_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_comment(grid_Ptr grid_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(grid_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_grid_comment(grid_Ptr grid_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_comment(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_description(grid_Ptr grid_hdl, const char * description, int description_size)
  {
    std::string description_str;
    if (!cstr2string(description, description_size, description_str)) return;
    CTimer::get("XIOS").resume();
    grid_hdl->description.setValue(description_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_description(grid_Ptr grid_hdl, char * description, int description_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(grid_hdl->description.getInheritedValue(), description, description_size))
      ERROR("void cxios_get_grid_description(grid_Ptr grid_hdl, char * description, int description_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_description(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->description.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_mask_0d(grid_Ptr grid_hdl, bool* mask_0d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_0d, shape(extent[0]), neverDeleteData);
    grid_hdl->mask_0d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_mask_0d(grid_Ptr grid_hdl, bool* mask_0d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_0d, shape(extent[0]), neverDeleteData);
    tmp=grid_hdl->mask_0d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_mask_0d(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->mask_0d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_mask_1d(grid_Ptr grid_hdl, bool* mask_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_1d, shape(extent[0]), neverDeleteData);
    grid_hdl->mask_1d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_mask_1d(grid_Ptr grid_hdl, bool* mask_1d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask_1d, shape(extent[0]), neverDeleteData);
    tmp=grid_hdl->mask_1d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_mask_1d(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->mask_1d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_mask_2d(grid_Ptr grid_hdl, bool* mask_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,2> tmp(mask_2d, shape(extent[0], extent[1]), neverDeleteData);
    grid_hdl->mask_2d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_mask_2d(grid_Ptr grid_hdl, bool* mask_2d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,2> tmp(mask_2d, shape(extent[0], extent[1]), neverDeleteData);
    tmp=grid_hdl->mask_2d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_mask_2d(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->mask_2d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_mask_3d(grid_Ptr grid_hdl, bool* mask_3d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,3> tmp(mask_3d, shape(extent[0], extent[1], extent[2]), neverDeleteData);
    grid_hdl->mask_3d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_mask_3d(grid_Ptr grid_hdl, bool* mask_3d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,3> tmp(mask_3d, shape(extent[0], extent[1], extent[2]), neverDeleteData);
    tmp=grid_hdl->mask_3d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_mask_3d(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->mask_3d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_mask_4d(grid_Ptr grid_hdl, bool* mask_4d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,4> tmp(mask_4d, shape(extent[0], extent[1], extent[2], extent[3]), neverDeleteData);
    grid_hdl->mask_4d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_mask_4d(grid_Ptr grid_hdl, bool* mask_4d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,4> tmp(mask_4d, shape(extent[0], extent[1], extent[2], extent[3]), neverDeleteData);
    tmp=grid_hdl->mask_4d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_mask_4d(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->mask_4d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_mask_5d(grid_Ptr grid_hdl, bool* mask_5d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,5> tmp(mask_5d, shape(extent[0], extent[1], extent[2], extent[3], extent[4]), neverDeleteData);
    grid_hdl->mask_5d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_mask_5d(grid_Ptr grid_hdl, bool* mask_5d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,5> tmp(mask_5d, shape(extent[0], extent[1], extent[2], extent[3], extent[4]), neverDeleteData);
    tmp=grid_hdl->mask_5d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_mask_5d(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->mask_5d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_mask_6d(grid_Ptr grid_hdl, bool* mask_6d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,6> tmp(mask_6d, shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]), neverDeleteData);
    grid_hdl->mask_6d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_mask_6d(grid_Ptr grid_hdl, bool* mask_6d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,6> tmp(mask_6d, shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]), neverDeleteData);
    tmp=grid_hdl->mask_6d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_mask_6d(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->mask_6d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_mask_7d(grid_Ptr grid_hdl, bool* mask_7d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,7> tmp(mask_7d, shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5], extent[6]), neverDeleteData);
    grid_hdl->mask_7d.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_mask_7d(grid_Ptr grid_hdl, bool* mask_7d, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,7> tmp(mask_7d, shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5], extent[6]), neverDeleteData);
    tmp=grid_hdl->mask_7d.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_mask_7d(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->mask_7d.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_grid_name(grid_Ptr grid_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    grid_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_grid_name(grid_Ptr grid_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(grid_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_grid_name(grid_Ptr grid_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_grid_name(grid_Ptr grid_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = grid_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
