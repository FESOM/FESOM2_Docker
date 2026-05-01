#include "duplicate_scalar_to_axis.hpp"
#include "type.hpp"
#include "axis.hpp"
#include "scalar.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CDuplicateScalarToAxis::CDuplicateScalarToAxis(void)
    : CObjectTemplate<CDuplicateScalarToAxis>(), CDuplicateScalarToAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CDuplicateScalarToAxis::CDuplicateScalarToAxis(const StdString & id)
    : CObjectTemplate<CDuplicateScalarToAxis>(id), CDuplicateScalarToAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CDuplicateScalarToAxis::~CDuplicateScalarToAxis(void)
  {}

  CTransformation<CAxis>* CDuplicateScalarToAxis::create(const StdString& id, xml::CXMLNode* node)
  {
    CDuplicateScalarToAxis* duplicateScalar = CDuplicateScalarToAxisGroup::get("duplicate_scalar_to_axis_definition")->createChild(id);
    if (node) duplicateScalar->parse(*node);
    return static_cast<CTransformation<CAxis>*>(duplicateScalar);
  }

  bool CDuplicateScalarToAxis::registerTrans()
  {
    return registerTransformation(TRANS_DUPLICATE_SCALAR_TO_AXIS, CDuplicateScalarToAxis::create);
  }

  bool CDuplicateScalarToAxis::_dummyRegistered = CDuplicateScalarToAxis::registerTrans();

  //----------------------------------------------------------------

  StdString CDuplicateScalarToAxis::GetName(void)    { return StdString("duplicate_scalar_to_axis"); }
  StdString CDuplicateScalarToAxis::GetDefName(void) { return StdString("duplicate_scalar_to_axis"); }
  ENodeType CDuplicateScalarToAxis::GetType(void)    { return eDuplicateScalarToAxis; }

  void CDuplicateScalarToAxis::checkValid(CAxis* axisDst, CScalar* scalarSrc)
  {
   
  }

}
