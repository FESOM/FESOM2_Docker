#ifndef __XIOS_CXMLNode__
#define __XIOS_CXMLNode__

/// rapidXML headers ///
#include <rapidxml.hpp>

/// XIOS headers ///
#include "xios_spl.hpp"

namespace xios
{
   namespace xml
   {
      /// ////////////////////// Déclarations ////////////////////// ///
      typedef xios_map<StdString, StdString> THashAttributes;

      class CXMLNode
      {
         public :

            /// Constructeurs ///
            CXMLNode(rapidxml::xml_node<char> * const root);

            /// Destructeur ///
            ~CXMLNode(void);

            /// Accesseurs ///
            StdString getElementName(void) const;
            THashAttributes getAttributes(void) const;

            /// Mutateurs ///
            bool goToNextElement(void);
            bool goToChildElement(void);
            bool goToParentElement(void);
            bool getContent(StdString & content);

            /// Accesseurs statiques ///
            static const StdString & GetRootName(void);

         private :

            /// Constructeurs ///
            CXMLNode(void);                        // Not implemented yet.
            CXMLNode(const CXMLNode & node);       // Not implemented yet.
            CXMLNode(const CXMLNode * const node); // Not implemented yet.

            rapidxml::xml_node<char> * node;
            int level;

            static StdString RootName;

      }; //class CXMLParser

   }// namespace xml
} // namespace xios

#endif // __XIOS_CXMLNode__
