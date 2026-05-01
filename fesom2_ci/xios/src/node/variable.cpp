#include "variable.hpp"

#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"
#include "object_factory.hpp"
#include "xios_spl.hpp"
#include "type.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include <boost/algorithm/string.hpp>

namespace xios {

   /// ////////////////////// Définitions ////////////////////// ///

   CVariable::CVariable(void)
      : CObjectTemplate<CVariable>()
      , CVariableAttributes()
      , content()
   { /* Ne rien faire de plus */ }

   CVariable::CVariable(const StdString & id)
      : CObjectTemplate<CVariable>(id)
      , CVariableAttributes()
      , content()
   { /* Ne rien faire de plus */ }

   CVariable::~CVariable(void)
   { /* Ne rien faire de plus */ }

   StdString CVariable::GetName(void)   { return (StdString("variable")); }
   StdString CVariable::GetDefName(void){ return (CVariable::GetName()); }
   ENodeType CVariable::GetType(void)   { return (eVariable); }

   void CVariable::parse(xml::CXMLNode & node)
   {
      SuperClass::parse(node);
      StdString id = (this->hasId()) ? this->getId() : StdString("undefined");
      if (!node.getContent(this->content))
      {
        xml::THashAttributes attributes = node.getAttributes();
        StdString variableName = attributes["name"];

        node.goToParentElement();
        StdString parentName = node.getElementName();
        attributes = node.getAttributes();
        error << "The variable id = " << id << " and name = " << variableName << " does not have any content. Please define it!" << std::endl
              << "This variable is inside another element whose attributes are :" << std::endl;

        for (xml::THashAttributes::iterator it = attributes.begin(); it != attributes.end(); ++it)
        {
           error << it->first << "=\"" << it->second.c_str() << "\" ";
        }
        error << std::endl; 

         ERROR("CVariable::parse(xml::CXMLNode & node)",
               << "[ variable id = " << id
               << " ] variable is not defined !. It does not have any content. See error log for more details.");
      }
      content = boost::trim_copy(content) ;
   }

   const StdString& CVariable::getVariableOutputName(void) const
   {
     return name.isEmpty() ? getId() : name;
   }

   const StdString & CVariable::getContent (void) const
   {
      return (this->content);
   }

   void CVariable::setContent(const StdString& contentStr)
   {
     this->content = contentStr;
   }

   StdString CVariable::toString(void) const
   {
      StdOStringStream oss;

      oss << "<" << CVariable::GetName() << " ";
      if (this->hasId())
         oss << " id=\"" << this->getId() << "\" ";
      oss << SuperClassAttribute::toString() << ">" << std::endl
          << this->content /*<< std::endl*/;
      oss << "</" << CVariable::GetName() << " >";
      return (oss.str());
   }

   /*
   *\brief Sending value of a variable with its id from client to server
   *
   */
   void CVariable::sendValue()
   {
     CContext* context=CContext::getCurrent() ;

     if (context->hasClient)
     {
       // Use correct context client to send message
       // int nbSrvPools = (context->hasServer) ? context->clientPrimServer.size() : 1;
      int nbSrvPools = (context->hasServer) ? (context->hasClient ? context->clientPrimServer.size() : 0) : 1;
       for (int i = 0; i < nbSrvPools; ++i)
       {
//       CContextClient* contextClientTmp = (0 != context->clientPrimServer) ? context->clientPrimServer
         CContextClient* contextClientTmp = (context->hasServer) ? context->clientPrimServer[i]
                                                                             : context->client;

         CEventClient event(this->getType(),EVENT_ID_VARIABLE_VALUE) ;
         if (contextClientTmp->isServerLeader())
         {
           CMessage msg ;
           msg<<this->getId() ;
           msg<<content ;
           const std::list<int>& ranks = contextClientTmp->getRanksServerLeader();
           for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
             event.push(*itRank,1,msg);
           contextClientTmp->sendEvent(event) ;
         }
         else contextClientTmp->sendEvent(event) ;
      }
     }
   }

   void CVariable::sendValue(CContextClient* client, bool clientPrim /*= false*/)
   {
     CEventClient event(this->getType(),EVENT_ID_VARIABLE_VALUE) ;
     if (client->isServerLeader())
     {
       CMessage msg ;
       msg<<this->getId() ;
       msg<<content ;
       const std::list<int>& ranks = client->getRanksServerLeader();
       for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
         event.push(*itRank,1,msg);
       client->sendEvent(event) ;
     }
     else client->sendEvent(event) ;
   }

   /*
   *\brief Receive value of a variable with its id from client to server
   *
   */
   void CVariable::recvValue(CEventServer& event)
   {
      CBufferIn* buffer=event.subEvents.begin()->buffer;
      string id;
      *buffer>>id ;
      get(id)->recvValue(*buffer);
   }

   /*
   *\brief Receive value of a variable with its id from client to server
   *
   */
   void CVariable::recvValue(CBufferIn& buffer)
   {
      string str ;
      buffer>>str;
      setContent(str);
   }

   bool CVariable::dispatchEvent(CEventServer& event)
   {
    if (SuperClass::dispatchEvent(event)) return true ;
    else
    {
      switch(event.type)
      {
        case EVENT_ID_VARIABLE_VALUE :
          recvValue(event) ;
          return true ;
          break ;

        default :
          ERROR("bool CVariable::dispatchEvent(CEventServer& event)",<<"Unknown Event") ;
          return false ;
      }
    }
   }

/*
   void CVariable::toBinary(StdOStream & os) const
   {
     const StdString & content = this->content;
     const StdSize size        =  content.size();
     SuperClass::toBinary(os);

     os.write (reinterpret_cast<const char*>(&size), sizeof(StdSize));
     os.write (content.data(), size * sizeof(char));
   }

   void CVariable::fromBinary(StdIStream & is)
   {
      SuperClass::fromBinary(is);
      StdSize size  = 0;
      is.read (reinterpret_cast<char*>(&size), sizeof(StdSize));
      this->content.assign(size, ' ');
      is.read (const_cast<char *>(this->content.data()), size * sizeof(char));
   }
*/
   void CVariableGroup::parse(xml::CXMLNode & node, bool withAttr)
   {
      CVariableGroup* group_ptr = (this->hasId())
         ? CVariableGroup::get(this->getId()) : CVariableGroup::get(this);

      StdString content;
      if (this->getId().compare(CVariableGroup::GetDefName()) != 0 && node.getContent(content))
      {
        StdSize beginid = 0, endid = 0, begindata = 0, enddata = 0;
        StdString subdata, subid;

        while ((beginid = content.find_first_not_of ( " \r\n\t;", enddata)) != StdString::npos)
        {
           endid   = content.find_first_of ( " \r\n\t=", beginid );
           subid   = content.substr ( beginid, endid-beginid);
           subid   = boost::to_lower_copy(boost::trim_copy(subid)) ;

           begindata = content.find_first_of ( "=", endid ) + 1;
           enddata   = content.find_first_of ( ";", begindata );
           subdata   = content.substr ( begindata, enddata-begindata);
           subdata   = boost::trim_copy(subdata) ;
           group_ptr->createChild(subid)->content = subdata ;
        }
      }
      else
      {
         SuperClass::parse(node, withAttr);
      }
      //SuperClass::parse(node, withAttr);

   }

} // namespace xios
