#ifndef __XIOS_CExtractDomainToAxis__
#define __XIOS_CExtractDomainToAxis__

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
  class CExtractDomainToAxisGroup;
  class CExtractDomainToAxisAttributes;
  class CExtractDomainToAxis;
  class CAxis;
  class CDomain;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CExtractDomainToAxis)
#include "extract_domain_to_axis_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CExtractDomainToAxis)

  ///--------------------------------------------------------------
  /*!
    \class CExtractDomainToAxis
    This class describes reduce_domain in xml file.
  */
  class CExtractDomainToAxis
    : public CObjectTemplate<CExtractDomainToAxis>
    , public CExtractDomainToAxisAttributes
    , public CTransformation<CAxis>
  {
    public :
      typedef CObjectTemplate<CExtractDomainToAxis> SuperClass;
      typedef CExtractDomainToAxisAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CExtractDomainToAxis(void);
      explicit CExtractDomainToAxis(const StdString& id);

      /// Destructeur ///
      virtual ~CExtractDomainToAxis(void);

      virtual void checkValid(CAxis* axisDst, CDomain* domainSrc);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CAxis>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CExtractDomainToAxis

  DECLARE_GROUP(CExtractDomainToAxis);
} // namespace xios

#endif // __XIOS_CExtractDomainToAxis__
