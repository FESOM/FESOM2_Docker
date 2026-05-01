#ifndef __XIOS_CReduceDomainToAxis__
#define __XIOS_CReduceDomainToAxis__

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
  class CReduceDomainToAxisGroup;
  class CReduceDomainToAxisAttributes;
  class CReduceDomainToAxis;
  class CAxis;
  class CDomain;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CReduceDomainToAxis)
#include "reduce_domain_to_axis_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CReduceDomainToAxis)

  ///--------------------------------------------------------------
  /*!
    \class CReduceDomainToAxis
    This class describes reduce_domain in xml file.
  */
  class CReduceDomainToAxis
    : public CObjectTemplate<CReduceDomainToAxis>
    , public CReduceDomainToAxisAttributes
    , public CTransformation<CAxis>
  {
    public :
      typedef CObjectTemplate<CReduceDomainToAxis> SuperClass;
      typedef CReduceDomainToAxisAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CReduceDomainToAxis(void);
      explicit CReduceDomainToAxis(const StdString& id);

      /// Destructeur ///
      virtual ~CReduceDomainToAxis(void);

      virtual void checkValid(CAxis* axisDst, CDomain* domainSrc);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CAxis>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CReduceDomainToAxis

  DECLARE_GROUP(CReduceDomainToAxis);
} // namespace xios

#endif // __XIOS_CReduceDomainToAxis__
