#include "object_factory_impl.hpp"
#include "node_type.hpp"


#define macro(U) \
  template std::shared_ptr<U> CObjectFactory::GetObject<U>(const StdString& id);  \
  template std::shared_ptr<U> CObjectFactory::GetObject<U>(const StdString& context,const StdString& id); \
  template std::shared_ptr<U> CObjectFactory::GetObject<U>(const U* const object); \
  template int CObjectFactory::GetObjectNum<U>(void); \
  template int CObjectFactory::GetObjectIdNum<U>(void); \
  template const std::vector<std::shared_ptr<U> >& CObjectFactory::GetObjectVector<U>(const StdString& context ); \
  template bool CObjectFactory::HasObject<U>(const StdString& id); \
  template bool CObjectFactory::HasObject<U>(const StdString& context,const StdString& id); \
  template std::shared_ptr<U> CObjectFactory::CreateObject<U>(const StdString& id ); \
  template const StdString& CObjectFactory::GetUIdBase<U>(void); \
  template StdString CObjectFactory::GenUId<U>(void); \
  template bool CObjectFactory::IsGenUId<U>(const StdString& id);


