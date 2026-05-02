#ifndef __XIOS_CObjectTemplate__
#define __XIOS_CObjectTemplate__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "attribute_map.hpp"
#include "node_enum.hpp"
#include "buffer_in.hpp"
#include "event_server.hpp"
#include "attribute.hpp"
#include "context_client.hpp"

namespace xios
{
   /// ////////////////////// Déclarations ////////////////////// ///
   template <class T>
      class CObjectTemplate
         : public CObject
         , public virtual CAttributeMap
   {

         /// Friend ///
         friend class CObjectFactory;

         /// Typedef ///
         typedef CAttributeMap SuperClassMap;
         typedef CObject SuperClass;
         typedef T DerivedType;

         enum EEventId
         {
           EVENT_ID_SEND_ATTRIBUTE=100
         } ;

      public :

         /// Autres ///
         virtual StdString toString(void) const;
         virtual void fromString(const StdString & str);

//         virtual void toBinary  (StdOStream & os) const;
//         virtual void fromBinary(StdIStream & is);
         virtual string getName(void) const ;
         virtual void parse(xml::CXMLNode & node);

         /// Accesseurs ///
         ENodeType getType(void) const;

         /// Test ///
         virtual bool hasChild(void) const;

         /// Traitements ///
         virtual void solveDescInheritance(bool apply, const CAttributeMap * const parent = 0);

         /// Traitement statique ///
         static void ClearAllAttributes(void);
         std::map<int, size_t> getMinimumBufferSizeForAttributes(CContextClient* client);
         void sendAttributToServer(const string& id);
         void sendAttributToServer(const string& id, CContextClient* client);
         void sendAttributToServer(CAttribute& attr) ;
         void sendAttributToServer(CAttribute& attr, CContextClient* client) ;
         void sendAllAttributesToServer();
         void sendAllAttributesToServer(CContextClient* client);
         void sendAddItem(const string& id, int itemType);
         void sendAddItem(const string& id, int itemType, CContextClient* client);
         static void recvAttributFromClient(CEventServer& event) ;
         static bool dispatchEvent(CEventServer& event) ;

         bool isEqual(const string& id, const vector<StdString>& excludedAttrs);
         bool isEqual(T* obj, const vector<StdString>& excludedAttrs);

         /// Accesseur statique ///
         static std::vector<std::shared_ptr<DerivedType> > &
            GetAllVectobject(const StdString & contextId);

         /// Destructeur ///
         virtual ~CObjectTemplate(void);

         static bool has(const string& id) ;
         static bool has(const string& contextId, const string& id) ;
         static T* get(const string& id) ;
         static T* get(const T* ptr) ;
         static T* get(const string& contextId, const string& id) ;
         T* get(void) ;
         std::shared_ptr<T> getShared(void) ;
         static std::shared_ptr<T> getShared(const T* ptr) ;

         static T* create(const string& id=string("")) ;
         static const vector<T*> getAll() ;
         static const vector<T*> getAll(const string& contextId) ;

         void generateCInterface(ostream& oss) ;
         void generateFortran2003Interface(ostream& oss) ;
         void generateFortranInterface(ostream& oss) ;

      protected :

         /// Constructeurs ///
         CObjectTemplate(void);
         explicit CObjectTemplate(const StdString & id);
         CObjectTemplate(const CObjectTemplate<T> & object,
                         bool withAttrList = true, bool withId = true);
         CObjectTemplate(const CObjectTemplate<T> * const object); // Not implemented.

      private :

         /// Propriétés statiques ///
         static xios_map<StdString,
                xios_map<StdString,
                std::shared_ptr<DerivedType> > > AllMapObj;
         static xios_map<StdString,
                std::vector<std::shared_ptr<DerivedType> > > AllVectObj;

         static xios_map< StdString, long int > GenId ;

   }; // class CObjectTemplate
} // namespace xios

//#include "object_template_impl.hpp"

#endif // __XIOS_CObjectTemplate__
