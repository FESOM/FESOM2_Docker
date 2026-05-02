#ifndef __XIOS_ATTRIBUTE_ARRAY__
#define __XIOS_ATTRIBUTE_ARRAY__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "attribute.hpp"
#include "buffer_in.hpp"
#include "buffer_out.hpp"
#include "array_new.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
      /*!
        \class CAttributeArray
        This class implements the attribute representing array of value
      */
      template <typename T_numtype, int N_rank>
         class CAttributeArray : public CAttribute, public CArray<T_numtype, N_rank>
      {
        public :

           using CArray<T_numtype,N_rank>::operator = ;

            /// Constructeurs ///
            explicit CAttributeArray(const StdString & id);
            CAttributeArray(const StdString & id, xios_map<StdString, CAttribute*> & umap);
            CAttributeArray(const StdString & id, const CArray<T_numtype, N_rank>& value);
            CAttributeArray(const StdString & id, const CArray<T_numtype, N_rank>& value,
                           xios_map<StdString, CAttribute*> & umap);

            /// Accesseur ///
            CArray<T_numtype, N_rank> getValue(void) const;

            /// Mutateurs ///
            void setValue(const CArray<T_numtype, N_rank>& value);
            void set(const CAttribute& attr) ;
            void set(const CAttributeArray& attr) ;
            void reset(void) ;
            void setInheritedValue(const CAttributeArray& attr );
            void setInheritedValue(const CAttribute& attr );
            CArray<T_numtype, N_rank> getInheritedValue(void) const ;
            bool hasInheritedValue(void) const;
                        
            bool isEqual(const CAttribute& attr);

            /// Destructeur ///
            virtual ~CAttributeArray(void) { }


            /// Autre ///
            virtual string toString(void) const { return _toString();}
            virtual void fromString(const StdString & str) { if (str==resetInheritanceStr) { reset(); _canInherite=false ;}  else _fromString(str);}
            virtual bool toBuffer  (CBufferOut& buffer) const { return _toBuffer(buffer);}
            virtual bool fromBuffer(CBufferIn& buffer) { return _fromBuffer(buffer); }
            virtual string dump(void) const { return _dump();}
            virtual string dump4graph(void) const { return _dump4graph();}

            virtual void generateCInterface(ostream& oss,const string& className) ;
            virtual void generateFortran2003Interface(ostream& oss,const string& className) ;
            virtual void generateFortranInterfaceDeclaration_(ostream& oss,const string& className) ;
            virtual void generateFortranInterfaceBody_(ostream& oss,const string& className) ;
            virtual void generateFortranInterfaceDeclaration(ostream& oss,const string& className) ;
            virtual void generateFortranInterfaceGetDeclaration_(ostream& oss,const string& className) ;
            virtual void generateFortranInterfaceGetBody_(ostream& oss,const string& className) ;
            virtual void generateFortranInterfaceGetDeclaration(ostream& oss,const string& className) ;

         private :
          bool isEqual_(const CAttributeArray& attr);
          CArray<T_numtype, N_rank> inheritedValue ;
          StdString _toString(void) const;
          StdString _dump(void) const;
          StdString _dump4graph(void) const;
          void _fromString(const StdString & str);
          bool _toBuffer  (CBufferOut& buffer) const;
          bool _fromBuffer(CBufferIn& buffer) ;
      }; // class CAttributeEnum
} // namespace xios

#endif // __XIOS_ATTRIBUTE_ARRAY__
