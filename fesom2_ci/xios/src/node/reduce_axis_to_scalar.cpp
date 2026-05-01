#include "reduce_axis_to_scalar.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CReduceAxisToScalar::CReduceAxisToScalar(void)
    : CObjectTemplate<CReduceAxisToScalar>(), CReduceAxisToScalarAttributes(), CTransformation<CScalar>()
  { /* Ne rien faire de plus */ }

  CReduceAxisToScalar::CReduceAxisToScalar(const StdString & id)
    : CObjectTemplate<CReduceAxisToScalar>(id), CReduceAxisToScalarAttributes(), CTransformation<CScalar>()
  { /* Ne rien faire de plus */ }

  CReduceAxisToScalar::~CReduceAxisToScalar(void)
  {}

  CTransformation<CScalar>* CReduceAxisToScalar::create(const StdString& id, xml::CXMLNode* node)
  {
    CReduceAxisToScalar* reduceAxis = CReduceAxisToScalarGroup::get("reduce_axis_to_scalar_definition")->createChild(id);
    if (node) reduceAxis->parse(*node);
    return static_cast<CTransformation<CScalar>*>(reduceAxis);
  }

  bool CReduceAxisToScalar::registerTrans()
  {
    return registerTransformation(TRANS_REDUCE_AXIS_TO_SCALAR, CReduceAxisToScalar::create);
  }

  bool CReduceAxisToScalar::_dummyRegistered = CReduceAxisToScalar::registerTrans();

  //----------------------------------------------------------------

  StdString CReduceAxisToScalar::GetName(void)    { return StdString("reduce_axis_to_scalar"); }
  StdString CReduceAxisToScalar::GetDefName(void) { return StdString("reduce_axis_to_scalar"); }
  ENodeType CReduceAxisToScalar::GetType(void)    { return eReduceAxisToScalar; }

  void CReduceAxisToScalar::checkValid(CScalar* scalarDst)
  {
  }

}
