#include "reduce_domain_to_scalar.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CReduceDomainToScalar::CReduceDomainToScalar(void)
    : CObjectTemplate<CReduceDomainToScalar>(), CReduceDomainToScalarAttributes(), CTransformation<CScalar>()
  { /* Ne rien faire de plus */ }

  CReduceDomainToScalar::CReduceDomainToScalar(const StdString & id)
    : CObjectTemplate<CReduceDomainToScalar>(id), CReduceDomainToScalarAttributes(), CTransformation<CScalar>()
  { /* Ne rien faire de plus */ }

  CReduceDomainToScalar::~CReduceDomainToScalar(void)
  {}

  CTransformation<CScalar>* CReduceDomainToScalar::create(const StdString& id, xml::CXMLNode* node)
  {
    CReduceDomainToScalar* reduceDomain = CReduceDomainToScalarGroup::get("reduce_domain_to_scalar_definition")->createChild(id);
    if (node) reduceDomain->parse(*node);
    return static_cast<CTransformation<CScalar>*>(reduceDomain);
  }

  bool CReduceDomainToScalar::registerTrans()
  {
    return registerTransformation(TRANS_REDUCE_DOMAIN_TO_SCALAR, CReduceDomainToScalar::create);
  }

  bool CReduceDomainToScalar::_dummyRegistered = CReduceDomainToScalar::registerTrans();

  //----------------------------------------------------------------

  StdString CReduceDomainToScalar::GetName(void)    { return StdString("reduce_domain_to_scalar"); }
  StdString CReduceDomainToScalar::GetDefName(void) { return StdString("reduce_domain_to_scalar"); }
  ENodeType CReduceDomainToScalar::GetType(void)    { return eReduceDomainToScalar; }

  void CReduceDomainToScalar::checkValid(CScalar* scalarDst, CDomain* domainSrc)
  {
    if (this->local.isEmpty()) local=false ;
  }

}
