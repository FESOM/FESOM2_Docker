#include "reduce_domain_to_axis.hpp"
#include "type.hpp"
#include "axis.hpp"
#include "domain.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CReduceDomainToAxis::CReduceDomainToAxis(void)
    : CObjectTemplate<CReduceDomainToAxis>(), CReduceDomainToAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CReduceDomainToAxis::CReduceDomainToAxis(const StdString & id)
    : CObjectTemplate<CReduceDomainToAxis>(id), CReduceDomainToAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CReduceDomainToAxis::~CReduceDomainToAxis(void)
  {}

  CTransformation<CAxis>* CReduceDomainToAxis::create(const StdString& id, xml::CXMLNode* node)
  {
    CReduceDomainToAxis* reduceDomain = CReduceDomainToAxisGroup::get("reduce_domain_to_axis_definition")->createChild(id);
    if (node) reduceDomain->parse(*node);
    return static_cast<CTransformation<CAxis>*>(reduceDomain);
  }

  bool CReduceDomainToAxis::registerTrans()
  {
    return registerTransformation(TRANS_REDUCE_DOMAIN_TO_AXIS, CReduceDomainToAxis::create);
  }

  bool CReduceDomainToAxis::_dummyRegistered = CReduceDomainToAxis::registerTrans();

  //----------------------------------------------------------------

  StdString CReduceDomainToAxis::GetName(void)    { return StdString("reduce_domain_to_axis"); }
  StdString CReduceDomainToAxis::GetDefName(void) { return StdString("reduce_domain_to_axis"); }
  ENodeType CReduceDomainToAxis::GetType(void)    { return eReduceDomainToAxis; }

  void CReduceDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)
  {
    if (CDomain::type_attr::unstructured == domainSrc->type)
      ERROR("CReduceDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
       << "Domain reduction is only supported for rectilinear or curvillinear grid."
       << "Domain source " <<domainSrc->getId() << std::endl
       << "Axis destination " << axisDst->getId());

    int axis_n_glo = axisDst->n_glo;
    int domain_ni_glo = domainSrc->ni_glo;
    int domain_nj_glo = domainSrc->nj_glo;

    if (this->operation.isEmpty())
      ERROR("CReduceDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
             << "An operation must be defined."
             << "Domain source " <<domainSrc->getId() << std::endl
             << "Axis destination " << axisDst->getId());

    if (this->direction.isEmpty())
      ERROR("CReduceDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
             << "A direction to apply the operation must be defined. It should be: 'iDir' or 'jDir'"
             << "Domain source " <<domainSrc->getId() << std::endl
             << "Axis destination " << axisDst->getId());
    if (this->local.isEmpty()) local=false ;

    switch (direction)
    {
      case direction_attr::jDir:
        if (axis_n_glo != domain_ni_glo)
          ERROR("CReduceDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
            << "Extract domain along j, axis destination should have n_glo equal to ni_glo of domain source"
            << "Domain source " <<domainSrc->getId() << " has nj_glo " << domain_ni_glo << std::endl
            << "Axis destination " << axisDst->getId() << " has n_glo " << axis_n_glo);
         break;

      case direction_attr::iDir:
        if (axis_n_glo != domain_nj_glo)
          ERROR("CReduceDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
            << "Extract domain along i, axis destination should have n_glo equal to nj_glo of domain source"
            << "Domain source " <<domainSrc->getId() << " has nj_glo " << domain_nj_glo << std::endl
            << "Axis destination " << axisDst->getId() << " has n_glo " << axis_n_glo);
        break;

      default:
        break;
    }
  }

}
