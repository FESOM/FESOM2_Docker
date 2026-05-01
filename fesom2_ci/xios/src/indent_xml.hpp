#ifndef __XIOS_CIndent_XML__
#define __XIOS_CIndent_XML__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "xml_node.hpp"

namespace xios
{
   /// ////////////////////// Déclarations ////////////////////// ///
   class CIndent
   {
      public :

         /// Méthodes statiques ///
         static StdOStream & NIndent  (StdOStream & out);
         static StdOStream & IncIndent(StdOStream & out);
         static StdOStream & DecEndl  (StdOStream & out);

      private :

         /// Propriétés  statiques ///
         static unsigned int Indent;
         static StdString    Increm;
         static bool         WithLine;

   }; // class CIndent

    ///--------------------------------------------------------------
    
   class CIndentedXml
   {
      public :

         /// Méthode statique ///
         static StdString Indented(const StdString & content);

   }; // class CIndentedXml

    ///--------------------------------------------------------------

} // namespace xios

   /// ////////////////////// Macros ////////////////////// ///
   
#define NIndent   CIndent::NIndent
#define IncIndent CIndent::IncIndent
#define DecEndl   CIndent::DecEndl

#endif // __XIOS_CIndent__
