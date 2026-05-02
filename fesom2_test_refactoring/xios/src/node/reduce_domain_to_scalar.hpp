#ifndef __XIOS_CReduceDomainToScalar__
#define __XIOS_CReduceDomainToScalar__

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

namespace xios {
  /// ////////////////////// Déclarations ////////////////////// ///
  class CReduceDomainToScalarGroup;
  class CReduceDomainToScalarAttributes;
  class CReduceDomainToScalar;
  class CDomain;
  class CScalar;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CReduceDomainToScalar)
#include "reduce_domain_to_scalar_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CReduceDomainToScalar)

  ///--------------------------------------------------------------
  /*!
    \class CReduceDomainToScalar
    This class describes reduce_domain in xml file.
  */
  class CReduceDomainToScalar
    : public CObjectTemplate<CReduceDomainToScalar>
    , public CReduceDomainToScalarAttributes
    , public CTransformation<CScalar>
  {
    public :
      typedef CObjectTemplate<CReduceDomainToScalar> SuperClass;
      typedef CReduceDomainToScalarAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CReduceDomainToScalar(void);
      explicit CReduceDomainToScalar(const StdString& id);

      /// Destructeur ///
      virtual ~CReduceDomainToScalar(void);

      virtual void checkValid(CScalar* scalarDst, CDomain* domainSrc);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CScalar>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CReduceDomainToScalar

  DECLARE_GROUP(CReduceDomainToScalar);
} // namespace xios

#endif // __XIOS_CReduceDomainToScalar__
