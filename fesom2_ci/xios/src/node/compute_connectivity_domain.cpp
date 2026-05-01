#include "compute_connectivity_domain.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CComputeConnectivityDomain::CComputeConnectivityDomain(void)
    : CObjectTemplate<CComputeConnectivityDomain>(), CComputeConnectivityDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CComputeConnectivityDomain::CComputeConnectivityDomain(const StdString & id)
    : CObjectTemplate<CComputeConnectivityDomain>(id), CComputeConnectivityDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CComputeConnectivityDomain::~CComputeConnectivityDomain(void)
  {}

  CTransformation<CDomain>* CComputeConnectivityDomain::create(const StdString& id, xml::CXMLNode* node)
  {
    CComputeConnectivityDomain* compute_connectivityDomain = CComputeConnectivityDomainGroup::get("compute_connectivity_domain_definition")->createChild(id);
    if (node) compute_connectivityDomain->parse(*node);
    return static_cast<CTransformation<CDomain>*>(compute_connectivityDomain);
  }

  bool CComputeConnectivityDomain::_dummyRegistered = CComputeConnectivityDomain::registerTrans();
  bool CComputeConnectivityDomain::registerTrans()
  {
    return registerTransformation(TRANS_COMPUTE_CONNECTIVITY_DOMAIN, CComputeConnectivityDomain::create);
  }

  //----------------------------------------------------------------

  StdString CComputeConnectivityDomain::GetName(void)    { return StdString("compute_connectivity_domain"); }
  StdString CComputeConnectivityDomain::GetDefName(void) { return StdString("compute_connectivity_domain"); }
  ENodeType CComputeConnectivityDomain::GetType(void)    { return eComputeConnectivityDomain; }

  void CComputeConnectivityDomain::checkValid(CDomain* domainDst)
  {
    if (CDomain::type_attr::unstructured != domainDst->type)
    {
      ERROR("CComputeConnectivityDomain::checkValid(CDomain* domainDst)",
            << "Domain connectivity computation is only supported for unstructured" << std::endl
            << "Check type of domain destination, id = " << domainDst->getId());
    }

    if (type.isEmpty()) type.setValue(CComputeConnectivityDomain::type_attr::edge);
    if (n_neighbor_max.isEmpty()) n_neighbor_max.setValue(0);
    if (n_neighbor.isEmpty()) n_neighbor.resize(domainDst->i_index.numElements());
    if (local_neighbor.isEmpty()) local_neighbor.resize(1,1);
  }

}
