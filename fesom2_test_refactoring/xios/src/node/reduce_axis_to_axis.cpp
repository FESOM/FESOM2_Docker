#include "reduce_axis_to_axis.hpp"
#include "type.hpp"
#include "axis.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CReduceAxisToAxis::CReduceAxisToAxis(void)
    : CObjectTemplate<CReduceAxisToAxis>(), CReduceAxisToAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CReduceAxisToAxis::CReduceAxisToAxis(const StdString & id)
    : CObjectTemplate<CReduceAxisToAxis>(id), CReduceAxisToAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CReduceAxisToAxis::~CReduceAxisToAxis(void)
  {}

  CTransformation<CAxis>* CReduceAxisToAxis::create(const StdString& id, xml::CXMLNode* node)
  {
    CReduceAxisToAxis* reduceAxis = CReduceAxisToAxisGroup::get("reduce_axis_to_axis_definition")->createChild(id);
    if (node) reduceAxis->parse(*node);
    return static_cast<CTransformation<CAxis>*>(reduceAxis);
  }

  bool CReduceAxisToAxis::registerTrans()
  {
    return registerTransformation(TRANS_REDUCE_AXIS_TO_AXIS, CReduceAxisToAxis::create);
  }

  bool CReduceAxisToAxis::_dummyRegistered = CReduceAxisToAxis::registerTrans();

  //----------------------------------------------------------------

  StdString CReduceAxisToAxis::GetName(void)    { return StdString("reduce_axis_to_axis"); }
  StdString CReduceAxisToAxis::GetDefName(void) { return StdString("reduce_axis_to_axis"); }
  ENodeType CReduceAxisToAxis::GetType(void)    { return eReduceAxisToAxis; }

  void CReduceAxisToAxis::checkValid(CAxis* axisDst, CAxis* axisSrc)
  {
  
    if (this->operation.isEmpty())
      ERROR("CReduceAxisToAxis::checkValid(CAxis* axisDst, CAxis* axisSrc)",
             << "An operation must be defined."
             << "Axis source " <<axisSrc->getId() << std::endl
             << "Axis destination " << axisDst->getId());


    if (axisDst->n_glo != axisSrc->n_glo)
       ERROR("CReduceAxisToAxis::checkValid(CAxis* axisDst, CAxis* axisSrc)",
            << "both axis should have same n_glo"
            << "Axis source " <<axisSrc->getId() << " has n_glo " << axisSrc->n_glo << std::endl
            << "Axis destination " << axisDst->getId() << " has n_glo " << axisDst->n_glo);
    
  }

}
