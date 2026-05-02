#include "expand_domain.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CExpandDomain::CExpandDomain(void)
    : CObjectTemplate<CExpandDomain>(), CExpandDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CExpandDomain::CExpandDomain(const StdString & id)
    : CObjectTemplate<CExpandDomain>(id), CExpandDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CExpandDomain::~CExpandDomain(void)
  {}

  CTransformation<CDomain>* CExpandDomain::create(const StdString& id, xml::CXMLNode* node)
  {
    CExpandDomain* expandDomain = CExpandDomainGroup::get("expand_domain_definition")->createChild(id);
    if (node) expandDomain->parse(*node);
    return static_cast<CTransformation<CDomain>*>(expandDomain);
  }

  bool CExpandDomain::_dummyRegistered = CExpandDomain::registerTrans();
  bool CExpandDomain::registerTrans()
  {
    return registerTransformation(TRANS_EXPAND_DOMAIN, CExpandDomain::create);
  }

  //----------------------------------------------------------------

  StdString CExpandDomain::GetName(void)    { return StdString("expand_domain"); }
  StdString CExpandDomain::GetDefName(void) { return StdString("expand_domain"); }
  ENodeType CExpandDomain::GetType(void)    { return eExpandDomain; }

  void CExpandDomain::checkValid(CDomain* domainDst)
  {
    // if (CDomain::type_attr::unstructured != domainDst->type)
    // {
    //   ERROR("CExpandDomain::checkValid(CDomain* domainDst)",
    //         << "Domain extension is only supported for unstructured" << std::endl
    //         << "Check type of domain destination, id = " << domainDst->getId());
    // }

    if (this->type.isEmpty()) this->type.setValue(CExpandDomain::type_attr::edge);
  }

}
