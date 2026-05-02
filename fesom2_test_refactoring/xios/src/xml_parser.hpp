#ifndef __XIOS_CXMLParser__
#define __XIOS_CXMLParser__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "cxios.hpp"
#include "xml_node.hpp"


namespace xios
{
   namespace xml
   {
      /// ////////////////////// Déclarations ////////////////////// ///
      class CXMLParser
      {
         public :

            static void ParseFile(const StdString & filename, const std::set<StdString>& parseList = std::set<StdString>());
            static void ParseString(const StdString & xmlContent);
            static void ParseStream(StdIStream & stream, const string& fluxId, const std::set<StdString>& parseList);
            template <class T>
               static void ParseInclude(StdIStream & stream, const string& fluxId, T & object);

      }; //class CXMLParser
/*
      template <class T>
         void CXMLParser::ParseInclude(StdIStream & stream, T& object)
      {
         StdOStringStream oss;
         while(!stream.eof() && !stream.fail ())
            oss.put(stream.get());
         try
         {
            const StdString xmlcontent( oss.str(), 0, oss.str().size()-1 );
            rapidxml::xml_document<char> doc;
            doc.parse<0>(const_cast<char*>(xmlcontent.c_str()));
            CXMLNode node(doc.first_node());
            object.parse(node);
         }
         catch (rapidxml::parse_error & exc)
         {
            ERROR("CXMLParser::ParseStream(StdIStream & stream)",
                  << "RapidXML error : " << exc.what() << " !");
         }
      }
*/
   }// namespace xml
} // namespace xios

#endif // __XIOS_CXMLParser__
