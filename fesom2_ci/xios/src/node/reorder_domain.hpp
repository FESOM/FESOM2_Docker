#ifndef __XIOS_CReorderDomain__
#define __XIOS_CReorderDomain__

/// xios headers ///
#include "xios_spl.hpp"
#include "attribute_enum.hpp"
#include "attribute_enum_impl.hpp"
#include "attribute_array.hpp"
#include "declare_attribute.hpp"
#include "object_template.hpp"
#include "group_factory.hpp"
#include "declare_group.hpp"
#include "transformation.hpp"
#include "domain.hpp"

namespace xios {
  /// ////////////////////// Déclarations ////////////////////// ///
  class CReorderDomainGroup;
  class CReorderDomainAttributes;
  class CReorderDomain;
  class CDomain;

  ///--------------------------------------------------------------

  // Declare/Define CReorderDomainAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CReorderDomain)
#include "reorder_domain_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CReorderDomain)

  ///--------------------------------------------------------------
  /*!
    \class CReorderDomain
    This class describes reorder_domain in xml file.
  */
  class CReorderDomain
    : public CObjectTemplate<CReorderDomain>
    , public CReorderDomainAttributes
    , public CTransformation<CDomain>
  {
    public :
      typedef CObjectTemplate<CReorderDomain> SuperClass;
      typedef CReorderDomainAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CReorderDomain(void);
      explicit CReorderDomain(const StdString& id);

      /// Destructeur ///
      virtual ~CReorderDomain(void);

      virtual void checkValid(CDomain* domainSrc);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CDomain>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CReorderDomain

  DECLARE_GROUP(CReorderDomain);
} // namespace xios

#endif // __XIOS_CReorderDomain__
