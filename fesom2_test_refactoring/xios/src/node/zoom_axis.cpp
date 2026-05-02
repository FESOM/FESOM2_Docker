#include "zoom_axis.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CZoomAxis::CZoomAxis(void)
    : CObjectTemplate<CZoomAxis>(), CZoomAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CZoomAxis::CZoomAxis(const StdString & id)
    : CObjectTemplate<CZoomAxis>(id), CZoomAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CZoomAxis::~CZoomAxis(void)
  {}

  CTransformation<CAxis>* CZoomAxis::create(const StdString& id, xml::CXMLNode* node)
  {
    CZoomAxis* zoomAxis = CZoomAxisGroup::get("zoom_axis_definition")->createChild(id);
    if (node) zoomAxis->parse(*node);
    return static_cast<CTransformation<CAxis>*>(zoomAxis);
  }

  bool CZoomAxis::registerTrans()
  {
    return registerTransformation(TRANS_ZOOM_AXIS, CZoomAxis::create);
  }

  bool CZoomAxis::_dummyRegistered = CZoomAxis::registerTrans();

  //----------------------------------------------------------------

  StdString CZoomAxis::GetName(void)    { return StdString("zoom_axis"); }
  StdString CZoomAxis::GetDefName(void) { return StdString("zoom_axis"); }
  ENodeType CZoomAxis::GetType(void)    { return eZoomAxis; }

  void CZoomAxis::checkValid(CAxis* axisDest)
  {
    int axisIBegin, axisNi, axisGlobalSize;
    int begin, end, n;

    axisIBegin = axisDest->begin.getValue();
    axisNi     = axisDest->n.getValue();
    axisGlobalSize   = axisDest->n_glo.getValue();

    bool zoomByIndex = !this->index.isEmpty() && (0 != this->index.numElements());

    if (zoomByIndex)
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
      ERROR("CZoomAxis::checkValid(CAxis* axisDest)",
            << "One or more attributes among 'begin' (" << begin << "), 'end' (" << end << "), 'n' (" << n << ") "
            << "of axis transformation [ id = '" << axisDest->getId() << "' , context = '" << CObjectFactory::GetCurrentContextId() << "' ] are not well specified");
    
    if (zoomByIndex && (!this->begin.isEmpty() || !this->n.isEmpty()))
      ERROR("CZoomAxis::checkValid(CAxis* axisDest)",
            << "Only one type of zoom is accepted. Define zoom by index with global_zoom_index or define zoom with begin and n. "
            << "Axis transformation [ id = '" << axisDest->getId() << "' , context = '" << CObjectFactory::GetCurrentContextId() << "' ] are not well specified");

    this->begin.setValue(begin);
    this->n.setValue(n);

  }

}
