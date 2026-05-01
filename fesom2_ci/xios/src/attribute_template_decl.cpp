#include "attribute_template_impl.hpp"
#include "attribute_template_specialisation.hpp"
#include <string>
#include "date.hpp"

namespace xios
{
  template class CAttributeTemplate<int> ;
  template class CAttributeTemplate<double> ;
  template class CAttributeTemplate<bool> ;
  template class CAttributeTemplate<string> ;
  template class CAttributeTemplate<CDate> ;
  template class CAttributeTemplate<CDuration> ;
}
