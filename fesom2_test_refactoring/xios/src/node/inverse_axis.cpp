#include "inverse_axis.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CInverseAxis::CInverseAxis(void)
    : CObjectTemplate<CInverseAxis>(), CInverseAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CInverseAxis::CInverseAxis(const StdString & id)
    : CObjectTemplate<CInverseAxis>(id), CInverseAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CInverseAxis::~CInverseAxis(void)
  {}

  CTransformation<CAxis>* CInverseAxis::create(const StdString& id, xml::CXMLNode* node)
  {
    CInverseAxis* invAxis = CInverseAxisGroup::get("inverse_axis_definition")->createChild(id);
    if (node) invAxis->parse(*node);
    return static_cast<CTransformation<CAxis>*>(invAxis);
  }

  bool CInverseAxis::registerTrans()
  {
    return registerTransformation(TRANS_INVERSE_AXIS, CInverseAxis::create);
  }

  bool CInverseAxis::_dummyRegistered = CInverseAxis::registerTrans();

  //----------------------------------------------------------------
  StdString CInverseAxis::GetName(void)    { return StdString("inverse_axis"); }
  StdString CInverseAxis::GetDefName(void) { return StdString("inverse_axis"); }
  ENodeType CInverseAxis::GetType(void)    { return eInverseAxis; }

  void CInverseAxis::checkValid(CAxis* axisSrc)
  {}

}
