#include "extract_domain.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CExtractDomain::CExtractDomain(void)
    : CObjectTemplate<CExtractDomain>(), CExtractDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CExtractDomain::CExtractDomain(const StdString & id)
    : CObjectTemplate<CExtractDomain>(id), CExtractDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CExtractDomain::~CExtractDomain(void)
  {}

  CTransformation<CDomain>* CExtractDomain::create(const StdString& id, xml::CXMLNode* node)
  {
    CExtractDomain* extractDomain = CExtractDomainGroup::get("extract_domain_definition")->createChild(id);
    if (node) extractDomain->parse(*node);
    return static_cast<CTransformation<CDomain>*>(extractDomain);
  }

  bool CExtractDomain::_dummyRegistered = CExtractDomain::registerTrans();
  bool CExtractDomain::registerTrans()
  {
    return registerTransformation(TRANS_EXTRACT_DOMAIN, CExtractDomain::create);
  }

  //----------------------------------------------------------------

  StdString CExtractDomain::GetName(void)    { return StdString("extract_domain"); }
  StdString CExtractDomain::GetDefName(void) { return StdString("extract_domain"); }
  ENodeType CExtractDomain::GetType(void)    { return eExtractDomain; }

  void CExtractDomain::checkValid(CDomain* domainSrc)
  {
    int ni_glo = domainSrc->ni_glo.getValue();
    int nj_glo = domainSrc->nj_glo.getValue();

    // Résolution et vérification des données globales de extract.
    if (!this->ni.isEmpty() || !this->nj.isEmpty() ||
        !this->ibegin.isEmpty() || !this->jbegin.isEmpty())
    {
       if (this->ni.isEmpty()     || this->nj.isEmpty() ||
           this->ibegin.isEmpty() || this->jbegin.isEmpty())
       {
         ERROR("CExtractDomain::checkValid(CDomain* domainSrc)",
               << "If one of extract attributes is defined then all extract attributes must be defined.") ;
       }
       else
       {
          int iend = ibegin + ni - 1;
          int jend = jbegin + nj - 1;

          if (ibegin < 0  || jbegin < 0 || iend > ni_glo - 1 || jend > nj_glo - 1)
            ERROR("CExtractDomain::checkValid(CDomain* domainSrc)",
                  << "Extract is wrongly defined, "
                  << "please check the values : 'ni' (" << ni.getValue() << "), 'nj' (" << nj.getValue() << "), "
                  << "'ibegin' (" << ibegin.getValue() << "), 'jbegin' (" << jbegin.getValue() << ")");
       }
    }
    else
    {
       ni = ni_glo;
       nj = nj_glo;
       ibegin = 0;
       jbegin = 0;
    }
  }

}
