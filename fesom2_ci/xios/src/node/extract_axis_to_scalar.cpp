#include "extract_axis_to_scalar.hpp"
#include "type.hpp"
#include "axis.hpp"
#include "scalar.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CExtractAxisToScalar::CExtractAxisToScalar(void)
    : CObjectTemplate<CExtractAxisToScalar>(), CExtractAxisToScalarAttributes(), CTransformation<CScalar>()
  { /* Ne rien faire de plus */ }

  CExtractAxisToScalar::CExtractAxisToScalar(const StdString & id)
    : CObjectTemplate<CExtractAxisToScalar>(id), CExtractAxisToScalarAttributes(), CTransformation<CScalar>()
  { /* Ne rien faire de plus */ }

  CExtractAxisToScalar::~CExtractAxisToScalar(void)
  {}

  CTransformation<CScalar>* CExtractAxisToScalar::create(const StdString& id, xml::CXMLNode* node)
  {
    CExtractAxisToScalar* extractAxis = CExtractAxisToScalarGroup::get("extract_axis_to_scalar_definition")->createChild(id);
    if (node) extractAxis->parse(*node);
    return static_cast<CTransformation<CScalar>*>(extractAxis);
  }

  bool CExtractAxisToScalar::registerTrans()
  {
    return registerTransformation(TRANS_EXTRACT_AXIS_TO_SCALAR, CExtractAxisToScalar::create);
  }

  bool CExtractAxisToScalar::_dummyRegistered = CExtractAxisToScalar::registerTrans();

  //----------------------------------------------------------------

  StdString CExtractAxisToScalar::GetName(void)    { return StdString("extract_axis_to_scalar"); }
  StdString CExtractAxisToScalar::GetDefName(void) { return StdString("extract_axis_to_scalar"); }
  ENodeType CExtractAxisToScalar::GetType(void)    { return eExtractAxisToScalar; }

  void CExtractAxisToScalar::checkValid(CScalar* scalarDst, CAxis* axisSrc)
  {
    int axis_n_glo = axisSrc->n_glo;
    if (position.isEmpty())
      ERROR("CExtractAxisToScalar::checkValid(CScalar* scalarDst, CAxis* axisSrc)",
        << "Position should be specified"
        << "Axis source " << axisSrc->getId() << std::endl
        << "CScalar destination " << scalarDst->getId() << std::endl);

    int position = this->position;

    if ((position < 0) || (position > (axis_n_glo-1)))
        ERROR("CExtractAxisToScalar::checkValid(CScalar* scalarDst, CAxis* axisSrc)",
          << "Extract axis, position should be inside 0 and ni_glo of axis source"
          << "Axis source " << axisSrc->getId() << std::endl
          << "CScalar destination " << scalarDst->getId() << std::endl);
  }

}
