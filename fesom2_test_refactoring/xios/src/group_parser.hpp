#ifndef __XIOS_GroupParser__
#define __XIOS_GroupParser__

/// boost headers ///
#include <boost/cast.hpp>

namespace xios
{
   /// ////////////////////// Définitions ////////////////////// ///
   template <class U, class V, class W>
      void CGroupTemplate<U, V, W>::parse(xml::CXMLNode & node, bool withAttr)
   {

      StdString name = node.getElementName();
      xml::THashAttributes attributes = node.getAttributes();
      if (withAttr)
      {
         CGroupTemplate<U, V, W>::SuperClass::parse(node);
         if (attributes.end() != attributes.find("src"))
         {
            StdIFStream ifs ( attributes["src"].c_str() , StdIFStream::in );
            if ( (ifs.rdstate() & std::ifstream::failbit ) != 0 )
               ERROR(" void CGroupTemplate<U, V, W>::parse(xml::CXMLNode & node, bool withAttr)",
                     <<endl<< "Can not open <"<<attributes["src"].c_str()<<"> file" );
            if (!ifs.good())
               ERROR("CGroupTemplate<U, V, W>::parse(xml::CXMLNode & node, bool withAttr)",
                     << "[ filename = " << attributes["src"] << " ] Bad xml stream !");
            xml::CXMLParser::ParseInclude(ifs, attributes["src"].c_str(), *this);
         }
      }

      // PARSING POUR GESTION DES ENFANTS
           V* group_ptr = (this->hasId()) 
         ? V::get(this->getId())
         : boost::polymorphic_downcast<V*>(this);

      if (!(node.goToChildElement()))
      {
         if (this->hasId())
         {
            DEBUG(<< "L'objet de type \'" << V::GetName()
                  << "\' nommé \'" << this->getId()
                  << "\' ne contient pas d\'enfant !");
         }
      }
      else
      {
         do { // Parcours pour traitement.

            StdString name = node.getElementName();
            attributes.clear();
            attributes = node.getAttributes();

            if (name.compare(V::GetName()) == 0)
            {
               if (attributes.end() == attributes.find("id"))
                  CGroupFactory::CreateGroup(group_ptr->getShared())->parse(node);
               else
                  CGroupFactory::CreateGroup(group_ptr->getShared(), attributes["id"])->parse(node);
               continue;
            }

            if (name.compare(U::GetName()) == 0)
            {
               if (attributes.end() == attributes.find("id"))
                  CGroupFactory::CreateChild(group_ptr->getShared())->parse(node);
               else
                  CGroupFactory::CreateChild(group_ptr->getShared(), attributes["id"])->parse(node);
               continue;
            }

            DEBUG(<< "Dans le contexte \'" << CContext::getCurrent()->getId()
                  << "\', un objet de type \'" << V::GetName()
                  << "\' ne peut contenir qu'un objet de type \'" << V::GetName()
                  << "\' ou de type \'" << U::GetName()
                  << "\' (reçu : " << name << ") !");

         } while (node.goToNextElement());
         node.goToParentElement(); // Retour au parent
      }
   }
 
  /// ////////////////////// Définitions ////////////////////// ///
   template <class U, class V, class W>
      void CGroupTemplate<U, V, W>::parseChild(xml::CXMLNode & node)
   {


      // PARSING POUR GESTION DES ENFANTS
           V* group_ptr = (this->hasId()) 
         ? V::get(this->getId())
         : boost::polymorphic_downcast<V*>(this);

          StdString name = node.getElementName();
          attributes.clear();
          attributes = node.getAttributes();

          if (name.compare(V::GetName()) == 0)
          {
             if (attributes.end() == attributes.find("id"))
                CGroupFactory::CreateGroup(group_ptr->getShared())->parse(node);
                return ;
             else
                CGroupFactory::CreateGroup(group_ptr->getShared(), attributes["id"])->parse(node);
             continue;
          }

          if (name.compare(U::GetName()) == 0)
          {
             if (attributes.end() == attributes.find("id"))
                CGroupFactory::CreateChild(group_ptr->getShared())->parse(node);
                return ;
             else
                CGroupFactory::CreateChild(group_ptr->getShared(), attributes["id"])->parse(node);
             continue;
          }

          DEBUG(<< "Dans le contexte \'" << CContext::getCurrent()->getId()
                << "\', un objet de type \'" << V::GetName()
                << "\' ne peut contenir qu'un objet de type \'" << V::GetName()
                << "\' ou de type \'" << U::GetName()
                << "\' (reçu : " << name << ") !");

   }
} // namespace xios

#endif // __XIOS_GroupParser__
