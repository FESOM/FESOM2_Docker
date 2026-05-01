#ifndef __XIOS_CTemporalSplitting__
#define __XIOS_CTemporalSplitting__

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
  class CTemporalSplittingGroup;
  class CTemporalSplittingAttributes;
  class CTemporalSplitting;
  class CAxis;
  class CScalar;
  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CTemporalSplitting)
#include "temporal_splitting.conf"
  END_DECLARE_ATTRIBUTE_MAP(CTemporalSplitting)

  ///--------------------------------------------------------------
  /*!
    \class CExtractDomainToAxis
    This class describes reduce_domain in xml file.
  */
  class CTemporalSplitting
    : public CObjectTemplate<CTemporalSplitting>
    , public CTemporalSplittingAttributes
    , public CTransformation<CAxis>
  {
    public :
      typedef CObjectTemplate<CTemporalSplitting> SuperClass;
      typedef CTemporalSplittingAttributes SuperClassAttribute;

    public :
      /// Constructeurs ///
      CTemporalSplitting(void);
      explicit CTemporalSplitting(const StdString& id);

      /// Destructeur ///
      virtual ~CTemporalSplitting(void);

      virtual void checkValid(CAxis* axisDst, CScalar* scalarSrc);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);
    private:
      static bool registerTrans();
      static CTransformation<CAxis>* create(const StdString& id, xml::CXMLNode* node);
      static bool _dummyRegistered;
  }; // class CTemporalSplitting

  DECLARE_GROUP(CTemporalSplitting);
} // namespace xios

#endif // __XIOS_CTemporalSplitting__
