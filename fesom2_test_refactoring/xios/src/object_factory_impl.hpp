#ifndef __XIOS_CObjectFactory_impl__
#define __XIOS_CObjectFactory_impl__

#include "object_factory.hpp"

namespace xios
{
   /// ////////////////////// Définitions ////////////////////// ///
   template <typename U>
       int CObjectFactory::GetObjectNum(void)
   {
      if (CurrContext.size() == 0)
         ERROR("CObjectFactory::GetObjectNum(void)",
               << "please define current context id !");
      return (U::AllVectObj[CObjectFactory::CurrContext].size());
   }

   template <typename U>
      int CObjectFactory::GetObjectIdNum(void)
   {
      if (CurrContext.size() == 0)
         ERROR("CObjectFactory::GetObjectIdNum(void)",
               << "please define current context id !");
      return (U::AllMapObj[CObjectFactory::CurrContext].size());
   }

   template <typename U>
      bool CObjectFactory::HasObject(const StdString & id)
   {
      if (CurrContext.size() == 0)
         ERROR("CObjectFactory::HasObject(const StdString & id)",
               << "[ id = " << id << " ] please define current context id !");
      return (U::AllMapObj[CObjectFactory::CurrContext].find(id) !=
              U::AllMapObj[CObjectFactory::CurrContext].end());
   }

   template <typename U>
      bool CObjectFactory::HasObject(const StdString & context, const StdString & id)
   {
      if (U::AllMapObj.find(context) == U::AllMapObj.end()) return false ;
      else return (U::AllMapObj[context].find(id) !=  U::AllMapObj[context].end());
   }

   template <typename U>
      std::shared_ptr<U> CObjectFactory::GetObject(const U * const object)
   {
      if (CurrContext.size() == 0)
         ERROR("CObjectFactory::GetObject(const U * const object)",
               << "please define current context id !");
      std::vector<std::shared_ptr<U> > & vect =
                     U::AllVectObj[CObjectFactory::CurrContext];

      typename std::vector<std::shared_ptr<U> >::const_iterator
         it = vect.begin(), end = vect.end();

      for (; it != end; it++)
      {
         std::shared_ptr<U> ptr = *it;
         if (ptr.get() == object)
            return (ptr);
      }

      ERROR("CObjectFactory::GetObject(const U * const object)",
               << "[type = " << U::GetName() << ", adress = " << object << "] "
               << "object was not found.");
      return (std::shared_ptr<U>()); // jamais atteint
   }

   template <typename U>
      std::shared_ptr<U> CObjectFactory::GetObject(const StdString & id)
   {
      if (CurrContext.size() == 0)
         ERROR("CObjectFactory::GetObject(const StdString & id)",
               << "[ id = " << id << " ] please define current context id !");
      if (!CObjectFactory::HasObject<U>(id))
         ERROR("CObjectFactory::GetObject(const StdString & id)",
               << "[ id = " << id << ", U = " << U::GetName() << " ] "
               << "object was not found.");
      return (U::AllMapObj[CObjectFactory::CurrContext][id]);
   }

   template <typename U>
      std::shared_ptr<U> CObjectFactory::GetObject(const StdString & context, const StdString & id)
   {
      if (!CObjectFactory::HasObject<U>(context,id))
         ERROR("CObjectFactory::GetObject(const StdString & id)",
               << "[ id = " << id << ", U = " << U::GetName() <<", context = "<<context<< " ] "
               << "object was not found.");
      return (U::AllMapObj[context][id]);
   }

   template <typename U>
   std::shared_ptr<U> CObjectFactory::CreateObject(const StdString& id)
   {
      if (CurrContext.empty())
         ERROR("CObjectFactory::CreateObject(const StdString& id)",
               << "[ id = " << id << " ] please define current context id !");

      if (CObjectFactory::HasObject<U>(id))
      {
         return CObjectFactory::GetObject<U>(id);
      }
      else
      {
         std::shared_ptr<U> value(new U(id.empty() ? CObjectFactory::GenUId<U>() : id));

         U::AllVectObj[CObjectFactory::CurrContext].insert(U::AllVectObj[CObjectFactory::CurrContext].end(), value);
         U::AllMapObj[CObjectFactory::CurrContext].insert(std::make_pair(value->getId(), value));

         return value;
      }
   }

   template <typename U>
      const std::vector<std::shared_ptr<U> > &
         CObjectFactory::GetObjectVector(const StdString & context)
   {
      return (U::AllVectObj[context]);
   }

   template <typename U>
   const StdString& CObjectFactory::GetUIdBase(void)
   {
      static const StdString base = "__" + U::GetName() + "_undef_id_";
      return base;
   }

   template <typename U>
   StdString CObjectFactory::GenUId(void)
   {
      StdOStringStream oss;
      oss << GetUIdBase<U>() << U::GenId[CObjectFactory::CurrContext]++;
      return oss.str();
   }

   template <typename U>
   bool CObjectFactory::IsGenUId(const StdString& id)
   {
      const StdString& base = GetUIdBase<U>();
      return (id.size() > base.size() && id.compare(0, base.size(), base) == 0);
   }

} // namespace xios

#endif // __XIOS_CObjectFactory_impl__
