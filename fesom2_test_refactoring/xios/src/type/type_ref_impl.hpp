
#ifndef __XIOS_TYPE_REF_IMPL__
#define __XIOS_TYPE_REF_IMPL__

#include "xios_spl.hpp"
#include "exception.hpp"
#include "buffer_in.hpp"
#include "buffer_out.hpp"
#include "message.hpp"
#include "type.hpp"



namespace xios
{
    
  using namespace std;
  
  template <typename T>
  CType_ref<T>::CType_ref(void)
  {
    empty=true ;
  }
    
  template <typename T>
  CType_ref<T>::CType_ref(T& val)
  {
    empty=true ;
    set_ref(val) ;
  }
  
  template <typename T>
  CType_ref<T>::CType_ref(CType<T>& type)
  {
    empty=true ;
    set_ref(type) ;
  }

  template <typename T>
  CType_ref<T>::CType_ref(const CType_ref<T>& type)
  {
    empty=true ;
    set_ref(type) ;
  }  

  
  template <typename T>
  void CType_ref<T>::set_ref(T& val)
  {
    ptrValue=&val ;
    empty=false ;
  }

  template <typename T>
  void CType_ref<T>::set_ref(CType<T>& type)
  {
    ptrValue=&type.get() ;
    empty=false ;
  }

  template <typename T>
  void CType_ref<T>::set_ref(const CType_ref<T>& type)
  {
    ptrValue=type.ptrValue ;
    empty=type.empty ;
  }

  template <typename T>
  void CType_ref<T>::set(const T& val) const
  {
    checkEmpty() ;
    *ptrValue=val ;
  }

  template <typename T>
  void CType_ref<T>::set(const CType<T>& type) const
  {
    checkEmpty() ;
    *ptrValue=type.get() ;
  }

  template <typename T>
  void CType_ref<T>::set(const CType_ref<T>& type) const
  {
    checkEmpty() ;
    *ptrValue=type.get() ;
  }
  
  template <typename T>
  T& CType_ref<T>::get(void) const
  {
    checkEmpty() ;
    return *ptrValue ;
  }
  
  template <typename T>
  const CType_ref<T>& CType_ref<T>::operator = (T& val) const
  {
    set(val) ;
    return *this ;
  }

  template <typename T>
  const CType_ref<T>& CType_ref<T>::operator = (CType<T>& type) const
  {
    set(type) ;
    return *this ;
  }
   
  template <typename T>
  const CType_ref<T>& CType_ref<T>::operator = (const CType_ref<T>& type) const
  {
    set(type) ;
    return *this ;
  }
  
  template <typename T>
  CType_ref<T>::operator T&() const
  {
    checkEmpty() ;
    return *ptrValue ;
  }

  template <typename T>
  CType_ref<T>* CType_ref<T>::_clone(void) const
  {
    checkEmpty() ;
    return new CType_ref<T>(*this) ;
  }
   
  template <typename T>
  void CType_ref<T>::_fromString(const string& str) const
  {
    istringstream iss(str);
    checkEmpty() ;
    iss>>*ptrValue ;
  }
 
  template <typename T>
  void CType_ref<T>::_fromString(const string& str)
  {
    istringstream iss(str);
    checkEmpty() ;
    iss>>*ptrValue ;
  }
  
  template <typename T>
  string CType_ref<T>::_toString(void) const
  {
    ostringstream oss;
    checkEmpty() ;
    oss<<*ptrValue ;
    return oss.str() ;
  }

    
  template <typename T>
  bool CType_ref<T>::_toBuffer(CBufferOut& buffer) const
  {
    checkEmpty() ;
    return buffer.put(*ptrValue) ;
  }
  
  template <typename T>
  bool CType_ref<T>::_fromBuffer(CBufferIn& buffer)
  {
    checkEmpty() ;
    return buffer.get(*ptrValue) ;
  }
 
  template <typename T>
  bool CType_ref<T>::_fromBuffer(CBufferIn& buffer) const
  {
    checkEmpty() ;
    return buffer.get(*ptrValue) ;
  }
 
  template <typename T>
  size_t CType_ref<T>::_size(void) const
  {
    return sizeof(T) ;
  }
  
  template <typename T>
  bool CType_ref<T>::_isEmpty(void) const
  {
    return empty ;
  }
   
  template <typename T>
  void CType_ref<T>::_reset(void)
  {
      empty=true ;
  }
  
  template <typename T>
  void CType_ref<T>::checkEmpty(void) const
  {
    if (empty) ERROR("template <typename T> void CType_ref<T>::checkEmpty(void)",
                     <<"Data reference is not initialized.") ;
  }
                     
  template <typename T>
  bool operator==(const CType_ref<T>& lhs, const T& rhs)
  {
    if (lhs.isEmpty()) return false;
    return (*lhs.ptrValue == rhs);    
  }

  template <typename T>
  bool operator==(const T& lhs, const CType_ref<T>& rhs)
  {
    return (rhs == lhs);
  }

  template <typename T>
  bool operator==(const CType_ref<T>& lhs, const CType_ref<T>& rhs)
  {
    if ((lhs.isEmpty() && !rhs.isEmpty()) || (!lhs.isEmpty() && rhs.isEmpty())) return false;
    if (lhs.isEmpty() && rhs.isEmpty()) return true;
    
    return (*lhs.ptrValue == *rhs.ptrValue);
  }
  
  template <typename T>
  CBufferOut& operator<<(CBufferOut& buffer, const CType_ref<T>& type)
  {
    if (!type.toBuffer(buffer)) ERROR("CBuffer& operator<<(CBuffer& buffer, CType<T>& type)",
                                      << "Not enough free space in buffer to queue the data.");
    return buffer ;
  }

  template <typename T>
  CBufferOut& operator<<(CBufferOut& buffer, T& type)
  {
    if (!CType_ref<T>(type).toBuffer(buffer)) ERROR("CBufferOut& operator<<(CBufferOut& buffer, T& type)",
                                                    << "Not enough free space in buffer to queue the data.");
    return buffer ;
  }

  template <typename T>
  CBufferIn& operator>>(CBufferIn& buffer, T& type)
  {
    if (! CType_ref<T>(type).fromBuffer(buffer)) ERROR(" template <typename T> CBufferIn& operator>>(CBufferIn& buffer, T& type)",
                                                       << "Not enough data in buffer to unqueue the data.");
    return buffer ;
  }

  template <typename T>
  CBufferIn& operator>>(CBufferIn& buffer, const CType_ref<T>& type)
  {
    if (! type.fromBuffer(buffer) ) ERROR("CBuffer& operator<<(CBuffer& buffer, CType<T>& type)",
                                          << "Not enough data in buffer to unqueue the data.");
    return buffer ;
  }

  template <typename T>
  CMessage& operator<<(CMessage& msg, T& type)
  {
    msg.push(CType_ref<T>(type)) ;
    return msg ;
  }
  
}

#endif
