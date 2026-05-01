#ifndef __XIOS_CObjectFactory__
#define __XIOS_CObjectFactory__

#include <memory>

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "object_template.hpp"

namespace xios
{
   /// ////////////////////// Déclarations ////////////////////// ///
   class CObjectFactory
   {
      public :

         /// Mutateurs ///
         static void SetCurrentContextId(const StdString & context);

         /// Accesseurs ///
         static StdString & GetCurrentContextId(void);

         template <typename U>
            static  std::shared_ptr<U> GetObject(const StdString & id);

         template <typename U>
            static  std::shared_ptr<U> GetObject(const StdString& context,const StdString & id);

         template <typename U>
            static  std::shared_ptr<U> GetObject(const U * const object);

         template <typename U>
            static  int GetObjectNum(void);
         template <typename U>
            static  int GetObjectIdNum(void);

         template <typename U>
            static  const std::vector<std::shared_ptr<U> > &
               GetObjectVector(const StdString & context = CObjectFactory::GetCurrentContextId());

         /// Tests ///
         template <typename U>
            static  bool HasObject(const StdString & id);

         template <typename U>
            static  bool HasObject(const StdString& context,const StdString & id);

         /// Instanciateur ///
         template <typename U>
            static  std::shared_ptr<U> CreateObject(const StdString & id = StdString(""));

         template <typename U> static const StdString& GetUIdBase(void);
         template <typename U> static StdString GenUId(void);
         template <typename U> static bool IsGenUId(const StdString& id);

      private :

         /// Propriétés statiques ///
         static StdString CurrContext;

   }; // class CObjectFactory
} // namespace xios

//#include "object_factory_impl.hpp"

#endif // __XIOS_CObjectFactory__
