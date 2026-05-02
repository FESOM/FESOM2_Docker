#ifndef __XIOS_CXML_PARSER_IMPL__
#define __XIOS_CXML_PARSER_IMPL__

/// XIOS headers ///
#include "xml_parser.hpp"

namespace xios
{
   namespace xml
   {
     template <class T> void CXMLParser::ParseInclude(StdIStream & stream, const string& fluxId,  T& object)
      {
         StdOStringStream oss;
         while(!stream.eof() && !stream.fail ()) oss.put(stream.get());
         const StdString xmlcontent( oss.str(), 0, oss.str().size()-1 );
         try
         {
            rapidxml::xml_document<char> doc;
            doc.parse<0>(const_cast<char*>(xmlcontent.c_str()));
            CXMLNode node(doc.first_node());
            object.parse(node);
         }
         catch (rapidxml::parse_error & exc)
         {
             const char* ptr = exc.where<char>() ;
            const char* begin = xmlcontent.c_str() ;
            const char* content=oss.str().c_str() ;
            size_t pos=ptr-begin ;
            int lineNumber = 1 ;
            int columnNumber = 0 ;
            const char* line;
            const char* endLine;
            
            for(const char* i=content;i<content+pos; ++i, ++columnNumber) if (*i=='\n') { lineNumber++ ; line=i ; columnNumber=0 ;}
            for(endLine=content+pos; *endLine!='\n' && *endLine!='\0' ; ++endLine) ;
            string strLine(line,endLine-line) ;
                  
            ERROR("CXMLParser::ParseStream(StdIStream & stream)", << endl
                  << "Error is occuring when parsing XML flux from <"<<fluxId<<"> at character "<< pos<<" line "<<lineNumber<<" column "<< columnNumber<< endl
                  << strLine<<endl
                  << string(columnNumber-1,'x')<<'^'<<endl)
//                  <<" Error : " << exc.what() )
         }
      }

   } // namespace xml
} // namespace xios

#endif // __XIOS_CXML_PARSER_IMPL__

