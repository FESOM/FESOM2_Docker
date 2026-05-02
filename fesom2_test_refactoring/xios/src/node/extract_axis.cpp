#include "extract_axis.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CExtractAxis::CExtractAxis(void)
    : CObjectTemplate<CExtractAxis>(), CExtractAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CExtractAxis::CExtractAxis(const StdString & id)
    : CObjectTemplate<CExtractAxis>(id), CExtractAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CExtractAxis::~CExtractAxis(void)
  {}

  CTransformation<CAxis>* CExtractAxis::create(const StdString& id, xml::CXMLNode* node)
  {
    CExtractAxis* extractAxis = CExtractAxisGroup::get("extract_axis_definition")->createChild(id);
    if (node) extractAxis->parse(*node);
    return static_cast<CTransformation<CAxis>*>(extractAxis);
  }

  bool CExtractAxis::registerTrans()
  {
    return registerTransformation(TRANS_EXTRACT_AXIS, CExtractAxis::create);
  }

  bool CExtractAxis::_dummyRegistered = CExtractAxis::registerTrans();

  //----------------------------------------------------------------

  StdString CExtractAxis::GetName(void)    { return StdString("extract_axis"); }
  StdString CExtractAxis::GetDefName(void) { return StdString("extract_axis"); }
  ENodeType CExtractAxis::GetType(void)    { return eExtractAxis; }

  void CExtractAxis::checkValid(CAxis* axisDest)
  {
    int axisIBegin, axisNi, axisGlobalSize;
    int begin, end, n;

    axisIBegin = axisDest->begin.getValue();
    axisNi     = axisDest->n.getValue();
    axisGlobalSize   = axisDest->n_glo.getValue();

    bool extractByIndex = !this->index.isEmpty() && (0 != this->index.numElements());

    if (extractByIndex)
    {
      begin = min(this->index);
      end   = max(this->index);
      n     = end - begin + 1;
    }
    else
    {
      begin = (this->begin.isEmpty()) ?  0 : this->begin.getValue();
      n     = (this->n.isEmpty()) ?  axisGlobalSize : this->n.getValue();
      end   = begin+n-1;
    }

    if (begin < 0 || begin > axisGlobalSize - 1 || end < 0 || end > axisGlobalSize - 1
        || n < 1 || n > axisGlobalSize || begin > end)
      ERROR("CExtractAxis::checkValid(CAxis* axisDest)",
            << "One or more attributes among 'begin' (" << begin << "), 'end' (" << end << "), 'n' (" << n << ") "
            << "of axis transformation [ id = '" << axisDest->getId() << "' , context = '" << CObjectFactory::GetCurrentContextId() << "' ] are not well specified");
    
    if (extractByIndex && (!this->begin.isEmpty() || !this->n.isEmpty()))
      ERROR("CExtractAxis::checkValid(CAxis* axisDest)",
            << "Only one type of extract is accepted. Define extract by index with global_extract_index or define extract with begin and n. "
            << "Axis transformation [ id = '" << axisDest->getId() << "' , context = '" << CObjectFactory::GetCurrentContextId() << "' ] are not well specified");

    this->begin.setValue(begin);
    this->n.setValue(n);

  }

}
