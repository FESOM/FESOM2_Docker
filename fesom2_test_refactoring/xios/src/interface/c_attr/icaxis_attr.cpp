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
  typedef xios::CAxis* axis_Ptr;

  void cxios_set_axis_axis_ref(axis_Ptr axis_hdl, const char * axis_ref, int axis_ref_size)
  {
    std::string axis_ref_str;
    if (!cstr2string(axis_ref, axis_ref_size, axis_ref_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->axis_ref.setValue(axis_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_axis_ref(axis_Ptr axis_hdl, char * axis_ref, int axis_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->axis_ref.getInheritedValue(), axis_ref, axis_ref_size))
      ERROR("void cxios_get_axis_axis_ref(axis_Ptr axis_hdl, char * axis_ref, int axis_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_axis_ref(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->axis_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_axis_type(axis_Ptr axis_hdl, const char * axis_type, int axis_type_size)
  {
    std::string axis_type_str;
    if (!cstr2string(axis_type, axis_type_size, axis_type_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->axis_type.fromString(axis_type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_axis_type(axis_Ptr axis_hdl, char * axis_type, int axis_type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->axis_type.getInheritedStringValue(), axis_type, axis_type_size))
      ERROR("void cxios_get_axis_axis_type(axis_Ptr axis_hdl, char * axis_type, int axis_type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_axis_type(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->axis_type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_begin(axis_Ptr axis_hdl, int begin)
  {
    CTimer::get("XIOS").resume();
    axis_hdl->begin.setValue(begin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_begin(axis_Ptr axis_hdl, int* begin)
  {
    CTimer::get("XIOS").resume();
    *begin = axis_hdl->begin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_begin(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->begin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_bounds(axis_Ptr axis_hdl, double* bounds, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(bounds, shape(extent[0], extent[1]), neverDeleteData);
    axis_hdl->bounds.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_bounds(axis_Ptr axis_hdl, double* bounds, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,2> tmp(bounds, shape(extent[0], extent[1]), neverDeleteData);
    tmp=axis_hdl->bounds.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_bounds(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->bounds.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_bounds_name(axis_Ptr axis_hdl, const char * bounds_name, int bounds_name_size)
  {
    std::string bounds_name_str;
    if (!cstr2string(bounds_name, bounds_name_size, bounds_name_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->bounds_name.setValue(bounds_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_bounds_name(axis_Ptr axis_hdl, char * bounds_name, int bounds_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->bounds_name.getInheritedValue(), bounds_name, bounds_name_size))
      ERROR("void cxios_get_axis_bounds_name(axis_Ptr axis_hdl, char * bounds_name, int bounds_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_bounds_name(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->bounds_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_comment(axis_Ptr axis_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_comment(axis_Ptr axis_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_axis_comment(axis_Ptr axis_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_comment(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_data_begin(axis_Ptr axis_hdl, int data_begin)
  {
    CTimer::get("XIOS").resume();
    axis_hdl->data_begin.setValue(data_begin);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_data_begin(axis_Ptr axis_hdl, int* data_begin)
  {
    CTimer::get("XIOS").resume();
    *data_begin = axis_hdl->data_begin.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_data_begin(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->data_begin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_data_index(axis_Ptr axis_hdl, int* data_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(data_index, shape(extent[0]), neverDeleteData);
    axis_hdl->data_index.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_data_index(axis_Ptr axis_hdl, int* data_index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(data_index, shape(extent[0]), neverDeleteData);
    tmp=axis_hdl->data_index.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_data_index(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->data_index.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_data_n(axis_Ptr axis_hdl, int data_n)
  {
    CTimer::get("XIOS").resume();
    axis_hdl->data_n.setValue(data_n);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_data_n(axis_Ptr axis_hdl, int* data_n)
  {
    CTimer::get("XIOS").resume();
    *data_n = axis_hdl->data_n.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_data_n(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->data_n.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_dim_name(axis_Ptr axis_hdl, const char * dim_name, int dim_name_size)
  {
    std::string dim_name_str;
    if (!cstr2string(dim_name, dim_name_size, dim_name_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->dim_name.setValue(dim_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_dim_name(axis_Ptr axis_hdl, char * dim_name, int dim_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->dim_name.getInheritedValue(), dim_name, dim_name_size))
      ERROR("void cxios_get_axis_dim_name(axis_Ptr axis_hdl, char * dim_name, int dim_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_dim_name(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->dim_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_formula(axis_Ptr axis_hdl, const char * formula, int formula_size)
  {
    std::string formula_str;
    if (!cstr2string(formula, formula_size, formula_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->formula.setValue(formula_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_formula(axis_Ptr axis_hdl, char * formula, int formula_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->formula.getInheritedValue(), formula, formula_size))
      ERROR("void cxios_get_axis_formula(axis_Ptr axis_hdl, char * formula, int formula_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_formula(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->formula.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_formula_bounds(axis_Ptr axis_hdl, const char * formula_bounds, int formula_bounds_size)
  {
    std::string formula_bounds_str;
    if (!cstr2string(formula_bounds, formula_bounds_size, formula_bounds_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->formula_bounds.setValue(formula_bounds_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_formula_bounds(axis_Ptr axis_hdl, char * formula_bounds, int formula_bounds_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->formula_bounds.getInheritedValue(), formula_bounds, formula_bounds_size))
      ERROR("void cxios_get_axis_formula_bounds(axis_Ptr axis_hdl, char * formula_bounds, int formula_bounds_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_formula_bounds(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->formula_bounds.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_formula_term(axis_Ptr axis_hdl, const char * formula_term, int formula_term_size)
  {
    std::string formula_term_str;
    if (!cstr2string(formula_term, formula_term_size, formula_term_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->formula_term.setValue(formula_term_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_formula_term(axis_Ptr axis_hdl, char * formula_term, int formula_term_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->formula_term.getInheritedValue(), formula_term, formula_term_size))
      ERROR("void cxios_get_axis_formula_term(axis_Ptr axis_hdl, char * formula_term, int formula_term_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_formula_term(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->formula_term.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_formula_term_bounds(axis_Ptr axis_hdl, const char * formula_term_bounds, int formula_term_bounds_size)
  {
    std::string formula_term_bounds_str;
    if (!cstr2string(formula_term_bounds, formula_term_bounds_size, formula_term_bounds_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->formula_term_bounds.setValue(formula_term_bounds_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_formula_term_bounds(axis_Ptr axis_hdl, char * formula_term_bounds, int formula_term_bounds_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->formula_term_bounds.getInheritedValue(), formula_term_bounds, formula_term_bounds_size))
      ERROR("void cxios_get_axis_formula_term_bounds(axis_Ptr axis_hdl, char * formula_term_bounds, int formula_term_bounds_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_formula_term_bounds(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->formula_term_bounds.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_index(axis_Ptr axis_hdl, int* index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(index, shape(extent[0]), neverDeleteData);
    axis_hdl->index.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_index(axis_Ptr axis_hdl, int* index, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(index, shape(extent[0]), neverDeleteData);
    tmp=axis_hdl->index.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_index(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->index.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_label(axis_Ptr axis_hdl, char* label, int str_len, int* str_size, int* extent)
  {
    CTimer::get("XIOS").resume();
    axis_hdl->label.resize(shape(extent[0]));
    Array<StdString,1>::iterator it, itb=axis_hdl->label.begin(), ite=axis_hdl->label.end() ;
    int i, n ;
    for(it=itb, i=0, n=0 ; it!=ite ; ++it,n+=str_len,++i) *it=StdString(&label[n],str_size[i]) ;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_label(axis_Ptr axis_hdl, char* label, int str_size, int* extent)
  {
    CTimer::get("XIOS").resume();
    Array<StdString,1>::const_iterator it, itb=axis_hdl->label.getInheritedValue().begin(), ite=axis_hdl->label.getInheritedValue().end() ;
    int n ;
    for(it=itb, n=0 ; it!=ite ; ++it, n+=str_size) it->copy(&label[n],it->size()) ; 
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_label(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->label.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_long_name(axis_Ptr axis_hdl, const char * long_name, int long_name_size)
  {
    std::string long_name_str;
    if (!cstr2string(long_name, long_name_size, long_name_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->long_name.setValue(long_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_long_name(axis_Ptr axis_hdl, char * long_name, int long_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->long_name.getInheritedValue(), long_name, long_name_size))
      ERROR("void cxios_get_axis_long_name(axis_Ptr axis_hdl, char * long_name, int long_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_long_name(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->long_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_mask(axis_Ptr axis_hdl, bool* mask, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask, shape(extent[0]), neverDeleteData);
    axis_hdl->mask.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_mask(axis_Ptr axis_hdl, bool* mask, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<bool,1> tmp(mask, shape(extent[0]), neverDeleteData);
    tmp=axis_hdl->mask.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_mask(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->mask.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_n(axis_Ptr axis_hdl, int n)
  {
    CTimer::get("XIOS").resume();
    axis_hdl->n.setValue(n);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_n(axis_Ptr axis_hdl, int* n)
  {
    CTimer::get("XIOS").resume();
    *n = axis_hdl->n.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_n(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->n.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_n_distributed_partition(axis_Ptr axis_hdl, int n_distributed_partition)
  {
    CTimer::get("XIOS").resume();
    axis_hdl->n_distributed_partition.setValue(n_distributed_partition);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_n_distributed_partition(axis_Ptr axis_hdl, int* n_distributed_partition)
  {
    CTimer::get("XIOS").resume();
    *n_distributed_partition = axis_hdl->n_distributed_partition.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_n_distributed_partition(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->n_distributed_partition.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_n_glo(axis_Ptr axis_hdl, int n_glo)
  {
    CTimer::get("XIOS").resume();
    axis_hdl->n_glo.setValue(n_glo);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_n_glo(axis_Ptr axis_hdl, int* n_glo)
  {
    CTimer::get("XIOS").resume();
    *n_glo = axis_hdl->n_glo.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_n_glo(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->n_glo.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_name(axis_Ptr axis_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_name(axis_Ptr axis_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_axis_name(axis_Ptr axis_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_name(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_positive(axis_Ptr axis_hdl, const char * positive, int positive_size)
  {
    std::string positive_str;
    if (!cstr2string(positive, positive_size, positive_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->positive.fromString(positive_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_positive(axis_Ptr axis_hdl, char * positive, int positive_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->positive.getInheritedStringValue(), positive, positive_size))
      ERROR("void cxios_get_axis_positive(axis_Ptr axis_hdl, char * positive, int positive_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_positive(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->positive.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_prec(axis_Ptr axis_hdl, int prec)
  {
    CTimer::get("XIOS").resume();
    axis_hdl->prec.setValue(prec);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_prec(axis_Ptr axis_hdl, int* prec)
  {
    CTimer::get("XIOS").resume();
    *prec = axis_hdl->prec.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_prec(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->prec.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_standard_name(axis_Ptr axis_hdl, const char * standard_name, int standard_name_size)
  {
    std::string standard_name_str;
    if (!cstr2string(standard_name, standard_name_size, standard_name_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->standard_name.setValue(standard_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_standard_name(axis_Ptr axis_hdl, char * standard_name, int standard_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->standard_name.getInheritedValue(), standard_name, standard_name_size))
      ERROR("void cxios_get_axis_standard_name(axis_Ptr axis_hdl, char * standard_name, int standard_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_standard_name(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->standard_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_unit(axis_Ptr axis_hdl, const char * unit, int unit_size)
  {
    std::string unit_str;
    if (!cstr2string(unit, unit_size, unit_str)) return;
    CTimer::get("XIOS").resume();
    axis_hdl->unit.setValue(unit_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_unit(axis_Ptr axis_hdl, char * unit, int unit_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(axis_hdl->unit.getInheritedValue(), unit, unit_size))
      ERROR("void cxios_get_axis_unit(axis_Ptr axis_hdl, char * unit, int unit_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_unit(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->unit.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_axis_value(axis_Ptr axis_hdl, double* value, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(value, shape(extent[0]), neverDeleteData);
    axis_hdl->value.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_axis_value(axis_Ptr axis_hdl, double* value, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<double,1> tmp(value, shape(extent[0]), neverDeleteData);
    tmp=axis_hdl->value.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_axis_value(axis_Ptr axis_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = axis_hdl->value.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
