#ifndef __XIOS_CExtractDomain__
#define __XIOS_CExtractDomain__

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
  class CExtractDomainGroup;
  class CExtractDomainAttributes;
  class CExtractDomain;
  class CDomain;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CExtractDomain)
#include "extract_domain_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CExtractDomain)

  ///--------------------------------------------------------------
  /*!
    \class CExtractDomain
    This class describes extract_domain in xml file.
  */
  class CExtractDomain
    : public CObjectTemplate<CExtractDomain>
    , public CExtractDomainAttributes
    , public CTransformation<CDomain>
  {
    public :
      typedef CObjectTemplate<CExtractDomain> SuperClass;
      typedef CExtractDomainAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CExtractDomain(void);
      explicit CExtractDomain(const StdString& id);

      /// Destructeur ///
      virtual ~CExtractDomain(void);

      virtual void checkValid(CDomain* axisDest);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CDomain>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CExtractDomain

  DECLARE_GROUP(CExtractDomain);
} // namespace xios

#endif // __XIOS_CExtractDomain__
