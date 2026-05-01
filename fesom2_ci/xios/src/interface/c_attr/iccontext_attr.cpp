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
  typedef xios::CContext* context_Ptr;

  void cxios_set_context_output_dir(context_Ptr context_hdl, const char * output_dir, int output_dir_size)
  {
    std::string output_dir_str;
    if (!cstr2string(output_dir, output_dir_size, output_dir_str)) return;
    CTimer::get("XIOS").resume();
    context_hdl->output_dir.setValue(output_dir_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_context_output_dir(context_Ptr context_hdl, char * output_dir, int output_dir_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(context_hdl->output_dir.getInheritedValue(), output_dir, output_dir_size))
      ERROR("void cxios_get_context_output_dir(context_Ptr context_hdl, char * output_dir, int output_dir_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_context_output_dir(context_Ptr context_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = context_hdl->output_dir.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
