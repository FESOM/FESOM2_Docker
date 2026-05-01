#ifndef __XIOS_CVariable__
#define __XIOS_CVariable__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "declare_group.hpp"
#include "group_template.hpp"
#include "array_new.hpp"
#include "attribute_enum.hpp"
#include "attribute_enum_impl.hpp"
#include "declare_attribute.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///

      class CVariableGroup;
      class CVariableAttributes;
      class CVariable;
      class CContext;
      ///--------------------------------------------------------------

      // Declare/Define CVarAttribute
      BEGIN_DECLARE_ATTRIBUTE_MAP(CVariable)
#include "var_attribute.conf"
      END_DECLARE_ATTRIBUTE_MAP(CVariable)

      ///--------------------------------------------------------------

      class CVariable
         : public CObjectTemplate<CVariable>
         , public CVariableAttributes
      {
                     /// typedef ///
            typedef CObjectTemplate<CVariable>   SuperClass;
            typedef CVariableAttributes SuperClassAttribute;
            
         public :
            enum EEventId
            {
             EVENT_ID_VARIABLE_VALUE
            };

            friend class CVariableGroup;

         public :

            typedef CVariableAttributes RelAttributes;
            typedef CVariableGroup      RelGroup;

            /// Constructeurs ///
            CVariable(void);
            explicit CVariable(const StdString & id);
            CVariable(const CVariable & var);       // Not implemented yet.
            CVariable(const CVariable * const var); // Not implemented yet.

            /// Destructeur ///
            virtual ~CVariable(void);

         public :
            /// Autres ///
            virtual void parse(xml::CXMLNode & node);
            virtual StdString toString(void) const;

            /// Accesseur ///
            const StdString& getVariableOutputName(void) const;
            const StdString & getContent (void) const;

            void setContent(const StdString& content);


            template <typename T> inline T getData(void) const;
            template <typename T> inline void setData(T data);

            template <typename T, StdSize N>
            inline void getData(CArray<T, N>& _data_array) const;

            static bool dispatchEvent(CEventServer& event) ;

            //! Sending a request to set up variable data
            void sendValue();
            void sendValue(CContextClient* client, bool clientPrim = false);

            static void recvValue(CEventServer& event) ;
            void recvValue(CBufferIn& buffer) ;

         public :

            /// Accesseurs statiques ///
            static StdString GetName(void);
            static StdString GetDefName(void);
            static ENodeType GetType(void);

         private :

            StdString content;

      }; // class CVar

      template <typename T>
      inline T CVariable::getData(void) const
      {
         T retval ;
         std::stringstream sstr(std::stringstream::in | std::stringstream::out);
         sstr<<content ;
         sstr>>retval ;
         if (sstr.fail()) ERROR("CVariable::getdata()",
               << "Cannot convert string <" << content << "> into type required" );
         return retval ;
      }

      template<>
      inline bool CVariable::getData(void) const
      {
         if (content.compare("true")==0 || content.compare(".true.")==0 || content.compare(".TRUE.")==0) return true ;
         else if (content.compare("false")==0 || content.compare(".false.")==0 || content.compare(".FALSE.")==0) return false ;
         else ERROR("CVariable::getdata()",
               << "Cannot convert string <" << content << "> into type required" );
         return false ;
      }

      template<>
      inline std::string CVariable::getData(void) const
      { return content; }

      template<>
      inline void CVariable::setData(bool data)
      {
        if (true == data) content.assign("true");
        else content.assign("false");
      }

      template <typename T>
      inline void CVariable::setData(T data)
      {
        std::stringstream sstr;
        sstr<<data;
        content = sstr.str();
      }

      ///--------------------------------------------------------------

      // Declare/Define CVarGroup and CVarDefinition
      DECLARE_GROUP_PARSE_REDEF(CVariable);
} // namespace xios

#endif // __XIOS_CVariable__
