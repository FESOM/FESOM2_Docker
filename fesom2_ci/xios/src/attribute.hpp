#ifndef __XIOS_CAttribute__
#define __XIOS_CAttribute__

/// boost headers ///
#include <boost/any.hpp>

/// XIOS headers ///
#include "xios_spl.hpp"
#include "object.hpp"
#include "base_type.hpp"
#include "message.hpp"
#include "buffer_in.hpp"
#include "buffer_out.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
   /*!
   \class CAttribute
      The fundamental class which describes the attributes of other different class in XIOS.
      This class only plays a role of interface, its class child will have specific implelemtation corresponding to type of attribute
   */
      class CAttribute : public CObject, public virtual CBaseType
      {
            typedef CObject SuperClass;

         public :

            /// Constructeurs ///
            explicit CAttribute(const StdString & id);

            /// Accesseurs ///
            const StdString & getName(void) const;

            virtual void set(const CAttribute& ) =0 ;
            virtual void reset(void ) =0 ;
            /// Destructeur ///
            virtual ~CAttribute(void);

            /// Autres ///
            virtual StdString toString(void) const = 0;
            virtual void fromString(const StdString & str) = 0;
            virtual StdString dump(void) const = 0;
            virtual StdString dump4graph(void) const = 0;
            virtual bool isEqual(const CAttribute& ) = 0;

            //! Returns true if and only if the attribute should be publicly exposed in the API
            virtual bool isPublic() const { return true; }
            
            //! Return true if the attribute should be sent to other clients or servers
            virtual bool doSend() const { return true; }

            /*
              Groupd of functions to generate C and Fortran interface 
            */
            virtual void generateCInterface(ostream& oss, const string& className) = 0 ;
            virtual void generateCInterfaceIsDefined(ostream& oss, const string& className) ;
            virtual void generateFortran2003Interface(ostream& oss, const string& className) = 0 ;
            virtual void generateFortran2003InterfaceIsDefined(ostream& oss, const string& className) ;
            virtual void generateFortranInterfaceDeclaration_(ostream& oss,const string& className) = 0 ;
            virtual void generateFortranInterfaceDeclaration(ostream& oss,const string& className) = 0 ;
            virtual void generateFortranInterfaceBody_(ostream& oss,const string& className) = 0 ;
            virtual void generateFortranInterfaceGetDeclaration_(ostream& oss,const string& className) = 0 ;
            virtual void generateFortranInterfaceGetDeclaration(ostream& oss,const string& className) = 0 ;
            virtual void generateFortranInterfaceGetBody_(ostream& oss,const string& className) = 0 ;
            virtual void generateFortranInterfaceIsDefinedDeclaration_(ostream& oss,const string& className) ;
            virtual void generateFortranInterfaceIsDefinedDeclaration(ostream& oss,const string& className)  ;
            virtual void generateFortranInterfaceIsDefinedBody_(ostream& oss,const string& className) ;

            virtual void setInheritedValue(const CAttribute& ) = 0 ;
            virtual bool hasInheritedValue(void) const = 0;

            bool canInherite(void) {return _canInherite ;}
         protected : 
            bool _canInherite ;
            static const StdString resetInheritanceStr ; 

      }; // class CAttribute

   CMessage& operator<<(CMessage& msg,CAttribute& type) ;
   CMessage& operator<<(CMessage& msg, const CAttribute&  type) ;
 
   CBufferOut& operator<<(CBufferOut& buffer,CAttribute& type) ;
   CBufferIn& operator>>(CBufferIn& buffer, CAttribute&  type) ;

}
  // namespace xios

#endif // __XIOS_CAttribute__
