#ifndef __XIOS_CZoomAxis__
#define __XIOS_CZoomAxis__

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
  class CZoomAxisGroup;
  class CZoomAxisAttributes;
  class CZoomAxis;
  class CAxis;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CZoomAxis)
#include "zoom_axis_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CZoomAxis)

  ///--------------------------------------------------------------
  /*!
    \class CZoomAxis
    This class describes zoom_axis in xml file.
  */
  class CZoomAxis
    : public CObjectTemplate<CZoomAxis>
    , public CZoomAxisAttributes
    , public CTransformation<CAxis>
  {
    public :
      typedef CObjectTemplate<CZoomAxis> SuperClass;
      typedef CZoomAxisAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CZoomAxis(void);
      explicit CZoomAxis(const StdString& id);

      /// Destructeur ///
      virtual ~CZoomAxis(void);

      virtual void checkValid(CAxis* axisDest);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CAxis>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CZoomAxis

  DECLARE_GROUP(CZoomAxis);
} // namespace xios

#endif // __XIOS_CZoomAxis__
