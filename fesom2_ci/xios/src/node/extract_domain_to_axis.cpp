#include "extract_domain_to_axis.hpp"
#include "type.hpp"
#include "axis.hpp"
#include "domain.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CExtractDomainToAxis::CExtractDomainToAxis(void)
    : CObjectTemplate<CExtractDomainToAxis>(), CExtractDomainToAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CExtractDomainToAxis::CExtractDomainToAxis(const StdString & id)
    : CObjectTemplate<CExtractDomainToAxis>(id), CExtractDomainToAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CExtractDomainToAxis::~CExtractDomainToAxis(void)
  {}

  CTransformation<CAxis>* CExtractDomainToAxis::create(const StdString& id, xml::CXMLNode* node)
  {
    CExtractDomainToAxis* extractDomain = CExtractDomainToAxisGroup::get("extract_domain_to_axis_definition")->createChild(id);
    if (node) extractDomain->parse(*node);
    return static_cast<CTransformation<CAxis>*>(extractDomain);
  }

  bool CExtractDomainToAxis::registerTrans()
  {
    return registerTransformation(TRANS_EXTRACT_DOMAIN_TO_AXIS, CExtractDomainToAxis::create);
  }

  bool CExtractDomainToAxis::_dummyRegistered = CExtractDomainToAxis::registerTrans();

  //----------------------------------------------------------------

  StdString CExtractDomainToAxis::GetName(void)    { return StdString("extract_domain_to_axis"); }
  StdString CExtractDomainToAxis::GetDefName(void) { return StdString("extract_domain_to_axis"); }
  ENodeType CExtractDomainToAxis::GetType(void)    { return eExtractDomainToAxis; }

  void CExtractDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)
  {
    if (CDomain::type_attr::unstructured == domainSrc->type)
      ERROR("CExtractDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
       << "Domain reduction is only supported for rectilinear or curvillinear grid."
       << "Domain source " <<domainSrc->getId() << std::endl
       << "Axis destination " << axisDst->getId());

    int axis_n_glo = axisDst->n_glo;
    int domain_ni_glo = domainSrc->ni_glo;
    int domain_nj_glo = domainSrc->nj_glo;

    if (this->direction.isEmpty())
      ERROR("CExtractDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
             << "A direction to apply the operation must be defined. It should be: 'iDir' or 'jDir'"
             << "Domain source " <<domainSrc->getId() << std::endl
             << "Axis destination " << axisDst->getId());
 
    if (this->position.isEmpty())
      ERROR("CExtractDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
             << "Position to extract axis must be defined. " << std::endl
             << "Domain source " <<domainSrc->getId() << std::endl
             << "Axis destination " << axisDst->getId());
    
    switch (direction)
    {
      case direction_attr::jDir:
        if (axis_n_glo != domain_nj_glo)
          ERROR("CExtractDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
            << "Extract domain along j, axis destination should have n_glo equal to nj_glo of domain source"
            << "Domain source " <<domainSrc->getId() << " has nj_glo " << domain_nj_glo << std::endl
            << "Axis destination " << axisDst->getId() << " has n_glo " << axis_n_glo);
        if ((position < 0) || (position >= domain_ni_glo))
        ERROR("CExtractDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
          << "Extract domain along j, position should be inside 0 and ni_glo-1 of domain source"
          << "Domain source " <<domainSrc->getId() << " has ni_glo " << domain_ni_glo << std::endl
          << "Axis destination " << axisDst->getId() << std::endl
          << "Position " << position);
         break;

      case direction_attr::iDir:
        if (axis_n_glo != domain_ni_glo)
          ERROR("CExtractDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
            << "Extract domain along i, axis destination should have n_glo equal to ni_glo of domain source"
            << "Domain source " <<domainSrc->getId() << " has ni_glo " << domain_ni_glo << std::endl
            << "Axis destination " << axisDst->getId() << " has n_glo " << axis_n_glo);
        if ((position < 0) || (position >= domain_nj_glo))
        ERROR("CExtractDomainToAxis::checkValid(CAxis* axisDst, CDomain* domainSrc)",
          << "Extract domain along i, position should be inside 0 and nj_glo-1 of domain source"
          << "Domain source " <<domainSrc->getId() << " has nj_glo " << domain_nj_glo << std::endl
          << "Axis destination " << axisDst->getId() << std::endl
          << "Position " << position);
        break;

      default:
        break;
    }
  }

}
