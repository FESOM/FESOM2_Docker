#include "reduce_scalar_to_scalar.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CReduceScalarToScalar::CReduceScalarToScalar(void)
    : CObjectTemplate<CReduceScalarToScalar>(), CReduceScalarToScalarAttributes(), CTransformation<CScalar>()
  { /* Ne rien faire de plus */ }

  CReduceScalarToScalar::CReduceScalarToScalar(const StdString & id)
    : CObjectTemplate<CReduceScalarToScalar>(id), CReduceScalarToScalarAttributes(), CTransformation<CScalar>()
  { /* Ne rien faire de plus */ }

  CReduceScalarToScalar::~CReduceScalarToScalar(void)
  {}

  CTransformation<CScalar>* CReduceScalarToScalar::create(const StdString& id, xml::CXMLNode* node)
  {
    CReduceScalarToScalar* reduceScalar = CReduceScalarToScalarGroup::get("reduce_scalar_to_scalar_definition")->createChild(id);
    if (node) reduceScalar->parse(*node);
    return static_cast<CTransformation<CScalar>*>(reduceScalar);
  }

  bool CReduceScalarToScalar::registerTrans()
  {
    return registerTransformation(TRANS_REDUCE_SCALAR_TO_SCALAR, CReduceScalarToScalar::create);
  }

  bool CReduceScalarToScalar::_dummyRegistered = CReduceScalarToScalar::registerTrans();

  //----------------------------------------------------------------

  StdString CReduceScalarToScalar::GetName(void)    { return StdString("reduce_scalar_to_scalar"); }
  StdString CReduceScalarToScalar::GetDefName(void) { return StdString("reduce_scalar_to_scalar"); }
  ENodeType CReduceScalarToScalar::GetType(void)    { return eReduceScalarToScalar; }

  void CReduceScalarToScalar::checkValid(CScalar* scalarDst)
  {
  }

}
