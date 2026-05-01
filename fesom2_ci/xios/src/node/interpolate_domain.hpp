#ifndef __XIOS_CInterpolateDomain__
#define __XIOS_CInterpolateDomain__

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
  class CInterpolateDomainGroup;
  class CInterpolateDomainAttributes;
  class CInterpolateDomain;
  class CDomain;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CInterpolateDomain)
#include "interpolate_domain_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CInterpolateDomain)

  ///--------------------------------------------------------------
  /*!
    \class CInterpolateDomain
    This class describes interpolate_from_file_domain in xml file.
  */
  class CInterpolateDomain
    : public CObjectTemplate<CInterpolateDomain>
    , public CInterpolateDomainAttributes
    , public CTransformation<CDomain>
  {
    public :
      typedef CObjectTemplate<CInterpolateDomain> SuperClass;
      typedef CInterpolateDomainAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CInterpolateDomain(void);
      explicit CInterpolateDomain(const StdString& id);

      /// Destructeur ///
      virtual ~CInterpolateDomain(void);

      virtual void checkValid(CDomain* domainSource);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CDomain>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CInterpolateDomain

  DECLARE_GROUP(CInterpolateDomain);
} // namespace xios

#endif // __XIOS_CInterpolateDomain__
