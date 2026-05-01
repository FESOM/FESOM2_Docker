#ifndef __XIOS_CReduceScalarToScalar__
#define __XIOS_CReduceScalarToScalar__

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
  class CReduceScalarToScalarGroup;
  class CReduceScalarToScalarAttributes;
  class CReduceScalarToScalar;
  class CScalar;

  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CReduceScalarToScalar)
#include "reduce_scalar_to_scalar_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CReduceScalarToScalar)

  ///--------------------------------------------------------------
  /*!
    \class CReduceScalarToScalar
    This class describes reduce_scalar in xml file.
  */
  class CReduceScalarToScalar
    : public CObjectTemplate<CReduceScalarToScalar>
    , public CReduceScalarToScalarAttributes
    , public CTransformation<CScalar>
  {
    public :
      typedef CObjectTemplate<CReduceScalarToScalar> SuperClass;
      typedef CReduceScalarToScalarAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CReduceScalarToScalar(void);
      explicit CReduceScalarToScalar(const StdString& id);

      /// Destructeur ///
      virtual ~CReduceScalarToScalar(void);

      virtual void checkValid(CScalar* scalarDst);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CScalar>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CReduceScalarToScalar

  DECLARE_GROUP(CReduceScalarToScalar);
} // namespace xios

#endif // __XIOS_CReduceScalarToScalar__
