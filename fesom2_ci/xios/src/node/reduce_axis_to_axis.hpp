#ifndef __XIOS_CReduceAxisToAxis__
#define __XIOS_CReduceAxisToAxis__

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
  class CReduceAxisToAxisGroup;
  class CReduceAxisToAxisAttributes;
  class CReduceAxisToAxis;
  class CAxis;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CReduceAxisToAxis)
#include "reduce_axis_to_axis_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CReduceAxisToAxis)

  ///--------------------------------------------------------------
  /*!
    \class CReduceAxisToAxis
    This class describes reduce_domain in xml file.
  */
  class CReduceAxisToAxis
    : public CObjectTemplate<CReduceAxisToAxis>
    , public CReduceAxisToAxisAttributes
    , public CTransformation<CAxis>
  {
    public :
      typedef CObjectTemplate<CReduceAxisToAxis> SuperClass;
      typedef CReduceAxisToAxisAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CReduceAxisToAxis(void);
      explicit CReduceAxisToAxis(const StdString& id);

      /// Destructeur ///
      virtual ~CReduceAxisToAxis(void);

      virtual void checkValid(CAxis* axisDst, CAxis* axisSrc);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CAxis>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CReduceAxisToAxis

  DECLARE_GROUP(CReduceAxisToAxis);
} // namespace xios

#endif // __XIOS_CReduceAxisToAxis__
