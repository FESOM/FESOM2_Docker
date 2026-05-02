#include "interpolate_domain.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CInterpolateDomain::CInterpolateDomain(void)
    : CObjectTemplate<CInterpolateDomain>(), CInterpolateDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CInterpolateDomain::CInterpolateDomain(const StdString & id)
    : CObjectTemplate<CInterpolateDomain>(id), CInterpolateDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CInterpolateDomain::~CInterpolateDomain(void)
  {}

  CTransformation<CDomain>* CInterpolateDomain::create(const StdString& id, xml::CXMLNode* node)
  {
    CInterpolateDomain* interpDomain = CInterpolateDomainGroup::get("interpolate_domain_definition")->createChild(id);
    if (node) interpDomain->parse(*node);
    return static_cast<CTransformation<CDomain>*>(interpDomain);
  }

  bool CInterpolateDomain::_dummyRegistered = CInterpolateDomain::registerTrans();
  bool CInterpolateDomain::registerTrans()
  {
    return registerTransformation(TRANS_INTERPOLATE_DOMAIN, create);
  }

  //----------------------------------------------------------------

  StdString CInterpolateDomain::GetName(void)    { return StdString("interpolate_domain"); }
  StdString CInterpolateDomain::GetDefName(void) { return StdString("interpolate_domain"); }
  ENodeType CInterpolateDomain::GetType(void)    { return eInterpolateDomain; }

  void CInterpolateDomain::checkValid(CDomain* domainSrc)
  {
    int order = 2;
    if (!this->order.isEmpty()) order = this->order.getValue();
    else this->order.setValue(order);
    if (order < 1)
    {
       ERROR("void CInterpolateDomain::checkValid(CDomain* domainSrc)",
             << "Interpolation order is less than 1, it should be greater than 0."
             << "Please define a correct one") ;
    }

    bool detect_missing_value=false ;
    if (!this->detect_missing_value.isEmpty()) detect_missing_value = this->detect_missing_value.getValue();
    else this->detect_missing_value.setValue(detect_missing_value);

    bool renormalize=false ;
    if (!this->renormalize.isEmpty()) renormalize = this->renormalize.getValue();
    else this->renormalize.setValue(renormalize);

    bool quantity=false ;
    if (!this->quantity.isEmpty()) quantity = this->quantity.getValue();
    else this->quantity.setValue(quantity);

    if (this->mode.isEmpty()) this->mode.setValue(mode_attr::compute);
    if (this->write_weight.isEmpty()) this->write_weight.setValue(false);

    if (this->read_write_convention.isEmpty()) this->read_write_convention.setValue(read_write_convention_attr::fortran);


  }

}
