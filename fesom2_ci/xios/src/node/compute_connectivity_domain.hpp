#ifndef __XIOS_CComputeConnectivityDomain__
#define __XIOS_CComputeConnectivityDomain__

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
  class CComputeConnectivityDomainGroup;
  class CComputeConnectivityDomainAttributes;
  class CComputeConnectivityDomain;
  class CDomain;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CComputeConnectivityDomain)
#include "compute_connectivity_domain_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CComputeConnectivityDomain)

  ///--------------------------------------------------------------
  /*!
    \class CComputeConnectivityDomain
    This class describes zoom_domain in xml file.
  */
  class CComputeConnectivityDomain
    : public CObjectTemplate<CComputeConnectivityDomain>
    , public CComputeConnectivityDomainAttributes
    , public CTransformation<CDomain>
  {
    public :
      typedef CObjectTemplate<CComputeConnectivityDomain> SuperClass;
      typedef CComputeConnectivityDomainAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CComputeConnectivityDomain(void);
      explicit CComputeConnectivityDomain(const StdString& id);

      /// Destructeur ///
      virtual ~CComputeConnectivityDomain(void);

      virtual void checkValid(CDomain* domain);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CDomain>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CComputeConnectivityDomain

  DECLARE_GROUP(CComputeConnectivityDomain);
} // namespace xios

#endif // __XIOS_CComputeConnectivityDomain__
