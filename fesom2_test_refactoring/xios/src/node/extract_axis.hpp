#ifndef __XIOS_CExtractAxis__
#define __XIOS_CExtractAxis__

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
#include "axis.hpp"

namespace xios {
  /// ////////////////////// Déclarations ////////////////////// ///
  class CExtractAxisGroup;
  class CExtractAxisAttributes;
  class CExtractAxis;
  class CAxis;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CExtractAxis)
#include "extract_axis_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CExtractAxis)

  ///--------------------------------------------------------------
  /*!
    \class CExtractAxis
    This class describes extract_axis in xml file.
  */
  class CExtractAxis
    : public CObjectTemplate<CExtractAxis>
    , public CExtractAxisAttributes
    , public CTransformation<CAxis>
  {
    public :
      typedef CObjectTemplate<CExtractAxis> SuperClass;
      typedef CExtractAxisAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CExtractAxis(void);
      explicit CExtractAxis(const StdString& id);

      /// Destructeur ///
      virtual ~CExtractAxis(void);

      virtual void checkValid(CAxis* axisDest);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CAxis>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CExtractAxis

  DECLARE_GROUP(CExtractAxis);
} // namespace xios

#endif // __XIOS_CExtractAxis__
