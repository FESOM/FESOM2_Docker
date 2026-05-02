#ifndef __XIOS_CExtractAxisToScalar__
#define __XIOS_CExtractAxisToScalar__

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
  class CExtractAxisToScalarGroup;
  class CExtractAxisToScalarAttributes;
  class CExtractAxisToScalar;
  class CAxis;
  class CScalar;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CExtractAxisToScalar)
#include "extract_axis_to_scalar_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CExtractAxisToScalar)

  ///--------------------------------------------------------------
  /*!
    \class CExtractAxisToScalar
    This class describes reduce_domain in xml file.
  */
  class CExtractAxisToScalar
    : public CObjectTemplate<CExtractAxisToScalar>
    , public CExtractAxisToScalarAttributes
    , public CTransformation<CScalar>
  {
    public :
      typedef CObjectTemplate<CExtractAxisToScalar> SuperClass;
      typedef CExtractAxisToScalarAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CExtractAxisToScalar(void);
      explicit CExtractAxisToScalar(const StdString& id);

      /// Destructeur ///
      virtual ~CExtractAxisToScalar(void);

      virtual void checkValid(CScalar* scalarDst, CAxis* axisSrc);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CScalar>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CExtractAxisToScalar

  DECLARE_GROUP(CExtractAxisToScalar);
} // namespace xios

#endif // __XIOS_CExtractAxisToScalar__
