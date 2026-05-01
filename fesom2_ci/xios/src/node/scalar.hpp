#ifndef __XIOS_CScalar__
#define __XIOS_CScalar__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "declare_group.hpp"
#include "declare_ref_func.hpp"
#include "group_template.hpp"
#include "array_new.hpp"
#include "attribute_enum.hpp"
#include "attribute_enum_impl.hpp"
#include "attribute_array.hpp"
#include "transformation.hpp"
#include "transformation_enum.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///

      class CScalarGroup;
      class CScalarAttributes;
      class CScalar;
      ///--------------------------------------------------------------

      // Declare/Define CVarAttribute
      BEGIN_DECLARE_ATTRIBUTE_MAP(CScalar)
#include "scalar_attribute.conf"
      END_DECLARE_ATTRIBUTE_MAP(CScalar)

      ///--------------------------------------------------------------

      class CScalar
         : public CObjectTemplate<CScalar>
         , public CScalarAttributes
      {
            /// typedef ///
            typedef CObjectTemplate<CScalar>   SuperClass;
            typedef CScalarAttributes SuperClassAttribute;

            friend class CScalarGroup;

         public :

            typedef CScalarAttributes RelAttributes;
            typedef CScalarGroup      RelGroup;
            typedef CTransformation<CScalar>::TransformationMapTypes TransMapTypes;

            /// Constructeurs ///
            CScalar(void);
            explicit CScalar(const StdString & id);
            CScalar(const CScalar & var);       // Not implemented yet.
            CScalar(const CScalar * const var); // Not implemented yet.

            /// Destructeur ///
            virtual ~CScalar(void);

         public :
            /// Accesseurs statiques ///
            static StdString GetName(void);
            static StdString GetDefName(void);
            static ENodeType GetType(void);

         public:
            static CScalar* createScalar();

         public:
            void checkAttributes(void);
            void addRelFile(const StdString& filename);
            bool IsWritten(const StdString& filename) const;
            void checkAttributesOnClient();
            virtual void parse(xml::CXMLNode & node);

         public:
           bool hasTransformation();
           void solveInheritanceTransformation();
           TransMapTypes getAllTransformations();
           void duplicateTransformation(CScalar*);
           CTransformation<CScalar>* addTransformation(ETranformationType transType, const StdString& id="");
           bool isEqual(CScalar* scalar);

         private:
           std::set<StdString> relFiles;
           TransMapTypes transformationMap_;

            void setTransformations(const TransMapTypes&);

       private:
           static bool initializeTransformationMap(std::map<StdString, ETranformationType>& m);
           static std::map<StdString, ETranformationType> transformationMapList_;
           static bool dummyTransformationMapList_;


            DECLARE_REF_FUNC(Scalar,scalar)

      }; // class CVar
      ///--------------------------------------------------------------

      // Declare/Define CScalarGroup and CScalarDefinition
      DECLARE_GROUP(CScalar);
} // namespace xios

#endif // __XIOS_CScalar__
