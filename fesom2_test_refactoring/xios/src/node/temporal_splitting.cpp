#include "temporal_splitting.hpp"
#include "type.hpp"
#include "axis.hpp"
#include "domain.hpp"
#include "scalar.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CTemporalSplitting::CTemporalSplitting(void)
    : CObjectTemplate<CTemporalSplitting>(), CTemporalSplittingAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CTemporalSplitting::CTemporalSplitting(const StdString & id)
    : CObjectTemplate<CTemporalSplitting>(id), CTemporalSplittingAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CTemporalSplitting::~CTemporalSplitting(void)
  {}

  CTransformation<CAxis>* CTemporalSplitting::create(const StdString& id, xml::CXMLNode* node)
  {
    CTemporalSplitting* temporalSplitting = CTemporalSplittingGroup::get("temporal_splitting_definition")->createChild(id);
    if (node) temporalSplitting->parse(*node);
    return static_cast<CTransformation<CAxis>*>(temporalSplitting);
  }

  bool CTemporalSplitting::registerTrans()
  {
    return registerTransformation(TRANS_TEMPORAL_SPLITTING, CTemporalSplitting::create);
  }

  bool CTemporalSplitting::_dummyRegistered = CTemporalSplitting::registerTrans();

  //----------------------------------------------------------------

  StdString CTemporalSplitting::GetName(void)    { return StdString("temporal_splitting"); }
  StdString CTemporalSplitting::GetDefName(void) { return StdString("temporal_splitting"); }
  ENodeType CTemporalSplitting::GetType(void)    { return eTemporalSplitting; }

  void CTemporalSplitting::checkValid(CAxis* axisDst, CScalar* scalarSrc)
  {

  }

}
