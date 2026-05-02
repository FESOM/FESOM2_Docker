#ifndef __XIOS_TYPE_SPECIALISATION_HPP__
#define __XIOS_TYPE_SPECIALISATION_HPP__

#include "xios_spl.hpp"
#include "exception.hpp"
#include "buffer_in.hpp"
#include "buffer_out.hpp"
#include "type.hpp"
#include <string>
#include <boost/algorithm/string.hpp>
#include "date.hpp"
 
namespace xios
{

// template specialization for bool

  template <> void CType<bool>::_fromString(const string& str)
  {
    string tmpStr=boost::to_lower_copy(boost::trim_copy(str)) ;
    if (tmpStr=="true" || tmpStr==".true." || tmpStr=="yes" || tmpStr=="y") set(true) ;
    else if (tmpStr=="false" || tmpStr==".false." || tmpStr=="no" || tmpStr=="n") set(false) ;
    else ERROR("template <> CType<bool>::fromString(const string& str)",<< tmpStr << " cannot be converted in a boolean value") ;
  }
  
  template <> string CType<bool>::_toString(void) const
  {
    if (get()) return string("true") ;
    else return string("false") ;
  }
 
  template <> void CType_ref<bool>::_fromString(const string& str) const
  {
    string tmpStr=boost::to_lower_copy(boost::trim_copy(str)) ;
    if (tmpStr=="true" || tmpStr==".true." || tmpStr=="yes" || tmpStr=="y") set(true) ;
    else if (tmpStr=="false" || tmpStr==".false." || tmpStr=="no" || tmpStr=="n") set(false) ;
    else ERROR("template <> CType<bool>::fromString(const string& str)",<< tmpStr << " cannot be converted in a boolean value") ;
  }
 
  template <> void CType_ref<bool>::_fromString(const string& str)
  {
    string tmpStr=boost::to_lower_copy(boost::trim_copy(str)) ;
    if (tmpStr=="true" || tmpStr==".true." || tmpStr=="yes" || tmpStr=="y") set(true) ;
    else if (tmpStr=="false" || tmpStr==".false." || tmpStr=="no" || tmpStr=="n") set(false) ;
    else ERROR("template <> CType<bool>::fromString(const string& str)",<< tmpStr << " cannot be converted in a boolean value") ;
  }
  
  template <> string CType_ref<bool>::_toString(void) const
  {
    if (get()) return string("true") ;
    else return string("false") ;
  }

// template specialization for string

  template <>
  size_t CType<string>::_size() const
  {
    size_t typeSize=0 ;
    typeSize+=sizeof(size_t) ;
    typeSize+=ptrValue->size() ;
    return typeSize ;
  }

  template <>
  size_t CType_ref<string>::_size() const
  {
    size_t typeSize=0 ;
    typeSize+=sizeof(size_t) ;
    typeSize+=ptrValue->size() ;
    return typeSize ;
  }
  
  template <>
  void CType<string>::_fromString(const string& str)
  {
    allocate() ;
    *ptrValue=str ;
  }  

  template <>
  void CType_ref<string>::_fromString(const string& str)
  {
    checkEmpty() ;
    *ptrValue=str ;
  }  

  template <>
  void CType_ref<string>::_fromString(const string& str) const
  {
    checkEmpty() ;
    *ptrValue=str ;
  }  
  
  template <>
  bool CType<string>::_toBuffer(CBufferOut& buffer) const
  {
    if (buffer.remain()<size()) return false ;
    else
    {
      bool ret=true ;
      if (ret) ret&=buffer.put(ptrValue->size()) ;
      if (ret) ret&=buffer.put(ptrValue->data(),ptrValue->size()) ;
      return ret ;
    }
  }
  
  template <>
  bool CType_ref<string>::_toBuffer(CBufferOut& buffer) const
  {
    if (buffer.remain()<size()) return false ;
    else
    {
      bool ret=true ;
      if (ret) ret&=buffer.put(ptrValue->size()) ;
      if (ret) ret&=buffer.put(ptrValue->data(),ptrValue->size()) ;
      return ret ;
    }
  }
  
  
  
  template <>
  bool CType<string>::_fromBuffer(CBufferIn& buffer)
  {
    allocate() ;
    bool ret=true ;
    size_t typeSize ;
    if (ret) ret&=buffer.get(typeSize) ;
    
    char* str;
    str= (char*) buffer.ptr() ;
    if (ret) buffer.advance(typeSize) ;
    if (ret) *ptrValue=string(str,typeSize) ;
    
    return ret ;
  }  

  template <>
  bool CType_ref<string>::_fromBuffer(CBufferIn& buffer) const
  {
    bool ret=true ;
    size_t typeSize ;
    if (ret) ret&=buffer.get(typeSize) ;
    
    char* str;
    str= (char*) buffer.ptr() ;
    if (ret) buffer.advance(typeSize) ;
    if (ret) *ptrValue=string(str,typeSize) ;
    
    return ret ;
  }   

  template <>
  bool CType_ref<string>::_fromBuffer(CBufferIn& buffer)
  {
    bool ret=true ;
    size_t typeSize ;
    if (ret) ret&=buffer.get(typeSize) ;
    
    char* str;
    str= (char*) buffer.ptr() ;
    if (ret) buffer.advance(typeSize) ;
    if (ret) *ptrValue=string(str,typeSize) ;
    
    return ret ;
  }     

// template specializations for CDate

  template <>
  size_t CType<CDate>::_size() const
  {
    return 6 * sizeof(int);
  }

  template <>
  size_t CType_ref<CDate>::_size() const
  {
    return 6 * sizeof(int);
  }

  template <>
  bool CType<CDate>::_toBuffer(CBufferOut& buffer) const
  {
    if (buffer.remain() < size()) return false;
    else
    {
      bool ret = true;
      if (ret) ret &= buffer.put(ptrValue->getYear());
      if (ret) ret &= buffer.put(ptrValue->getMonth());
      if (ret) ret &= buffer.put(ptrValue->getDay());
      if (ret) ret &= buffer.put(ptrValue->getHour());
      if (ret) ret &= buffer.put(ptrValue->getMinute());
      if (ret) ret &= buffer.put(ptrValue->getSecond());
      return ret;
    }
  }
  
  template <>
  bool CType_ref<CDate>::_toBuffer(CBufferOut& buffer) const
  {
    if (buffer.remain() < size()) return false;
    else
    {
      bool ret = true;
      if (ret) ret &= buffer.put(ptrValue->getYear());
      if (ret) ret &= buffer.put(ptrValue->getMonth());
      if (ret) ret &= buffer.put(ptrValue->getDay());
      if (ret) ret &= buffer.put(ptrValue->getHour());
      if (ret) ret &= buffer.put(ptrValue->getMinute());
      if (ret) ret &= buffer.put(ptrValue->getSecond());
      return ret;
    }
  }

  template <>
  bool CType<CDate>::_fromBuffer(CBufferIn& buffer)
  {
    allocate();
    bool ret = true;

    int year, month, day, hour, min, sec;
    if (ret) ret &= buffer.get(year);
    if (ret) ret &= buffer.get(month);
    if (ret) ret &= buffer.get(day);
    if (ret) ret &= buffer.get(hour);
    if (ret) ret &= buffer.get(min);
    if (ret) ret &= buffer.get(sec);
    if (ret)
    {
      ptrValue->setYear(year);
      ptrValue->setMonth(month);
      ptrValue->setDay(day);
      ptrValue->setHour(hour);
      ptrValue->setMinute(min);
      ptrValue->setSecond(sec);
    }

    return ret;
  }

  template <>
  bool CType_ref<CDate>::_fromBuffer(CBufferIn& buffer) const
  {
    bool ret = true;
    
    int year, month, day, hour, min, sec;
    if (ret) ret &= buffer.get(year);
    if (ret) ret &= buffer.get(month);
    if (ret) ret &= buffer.get(day);
    if (ret) ret &= buffer.get(hour);
    if (ret) ret &= buffer.get(min);
    if (ret) ret &= buffer.get(sec);
    if (ret)
    {
      ptrValue->setYear(year);
      ptrValue->setMonth(month);
      ptrValue->setDay(day);
      ptrValue->setHour(hour);
      ptrValue->setMinute(min);
      ptrValue->setSecond(sec);
    }

    return ret;
  }

  template <>
  bool CType_ref<CDate>::_fromBuffer(CBufferIn& buffer)
  {
    bool ret = true;
    
    int year, month, day, hour, min, sec;
    if (ret) ret &= buffer.get(year);
    if (ret) ret &= buffer.get(month);
    if (ret) ret &= buffer.get(day);
    if (ret) ret &= buffer.get(hour);
    if (ret) ret &= buffer.get(min);
    if (ret) ret &= buffer.get(sec);
    if (ret)
    {
      ptrValue->setYear(year);
      ptrValue->setMonth(month);
      ptrValue->setDay(day);
      ptrValue->setHour(hour);
      ptrValue->setMinute(min);
      ptrValue->setSecond(sec);
    }

    return ret;
  }

// template specializations for CDuration

  template <>
  size_t CType<CDuration>::_size() const
  {
    return 7 * sizeof(double);
  }

  template <>
  size_t CType_ref<CDuration>::_size() const
  {
    return 7 * sizeof(double);
  }

  template <>
  bool CType<CDuration>::_toBuffer(CBufferOut& buffer) const
  {
    if (buffer.remain() < size()) return false;
    else
    {
      bool ret = true;
      if (ret) ret &= buffer.put(ptrValue->year);
      if (ret) ret &= buffer.put(ptrValue->month);
      if (ret) ret &= buffer.put(ptrValue->day);
      if (ret) ret &= buffer.put(ptrValue->hour);
      if (ret) ret &= buffer.put(ptrValue->minute);
      if (ret) ret &= buffer.put(ptrValue->second);
      if (ret) ret &= buffer.put(ptrValue->timestep);
      return ret;
    }
  }
  
  template <>
  bool CType_ref<CDuration>::_toBuffer(CBufferOut& buffer) const
  {
    if (buffer.remain() < size()) return false;
    else
    {
      bool ret = true;
      if (ret) ret &= buffer.put(ptrValue->year);
      if (ret) ret &= buffer.put(ptrValue->month);
      if (ret) ret &= buffer.put(ptrValue->day);
      if (ret) ret &= buffer.put(ptrValue->hour);
      if (ret) ret &= buffer.put(ptrValue->minute);
      if (ret) ret &= buffer.put(ptrValue->second);
      if (ret) ret &= buffer.put(ptrValue->timestep);
      return ret;
    }
  }

  template <>
  bool CType<CDuration>::_fromBuffer(CBufferIn& buffer)
  {
    allocate();
    bool ret = true;

    if (ret) ret &= buffer.get(ptrValue->year);
    if (ret) ret &= buffer.get(ptrValue->month);
    if (ret) ret &= buffer.get(ptrValue->day);
    if (ret) ret &= buffer.get(ptrValue->hour);
    if (ret) ret &= buffer.get(ptrValue->minute);
    if (ret) ret &= buffer.get(ptrValue->second);
    if (ret) ret &= buffer.get(ptrValue->timestep);

    return ret;
  }

  template <>
  bool CType_ref<CDuration>::_fromBuffer(CBufferIn& buffer) const
  {
    bool ret = true;
    
    if (ret) ret &= buffer.get(ptrValue->year);
    if (ret) ret &= buffer.get(ptrValue->month);
    if (ret) ret &= buffer.get(ptrValue->day);
    if (ret) ret &= buffer.get(ptrValue->hour);
    if (ret) ret &= buffer.get(ptrValue->minute);
    if (ret) ret &= buffer.get(ptrValue->second);
    if (ret) ret &= buffer.get(ptrValue->timestep);

    return ret;
  }

  template <>
  bool CType_ref<CDuration>::_fromBuffer(CBufferIn& buffer)
  {
    bool ret = true;
    
    if (ret) ret &= buffer.get(ptrValue->year);
    if (ret) ret &= buffer.get(ptrValue->month);
    if (ret) ret &= buffer.get(ptrValue->day);
    if (ret) ret &= buffer.get(ptrValue->hour);
    if (ret) ret &= buffer.get(ptrValue->minute);
    if (ret) ret &= buffer.get(ptrValue->second);
    if (ret) ret &= buffer.get(ptrValue->timestep);

    return ret;
  }

  // template specialisation for CArray
/*
  template<>
  size_t CType< ARRAY(int, 1)>::size() const
  {
     return (*(this->ptrValue))->getSize() ;
  }
  
  template <>
  bool CType<ARRAY(int, 1)>::toBuffer(CBufferOut& buffer) const
  {
      return (*(this->ptrValue))->toBuffer(buffer) ;
  }

  template <>
  bool CType<ARRAY(int, 1)>::fromBuffer(CBufferIn& buffer) const
  {
    return (*(this->ptrValue))->fromBuffer(buffer) ;
  }

  template <>
  void CType<ARRAY(int, 1)>::fromString(const string& str) const
  {
 // to implement
  }

  template <>
  string CType<ARRAY(int, 1)>::toString(void) const
  {
 // to implement
   return string("") ;
 
  }
*/


/*
template<size_t numDim>
boost::detail::multi_array::extent_gen<numDim> getExtentNull(void) { return getExtentNull<numDim-1>()[0];}

template<>
boost::detail::multi_array::extent_gen<1> getExtentNull<1>(void) { return extents[0]; }
*/
/*
#define CTYPE_ARRAY(ValueType,NumsDims)                                \
                                                                       \
  template <>                                                          \
  void CType<ARRAY(ValueType,NumsDims)>::allocate(void)  \
  {                                                                    \
    if (empty) ptrValue=new shared_ptr<CArray<ValueType, NumsDims> >(new  CArray<ValueType, NumsDims>()) ;\
    empty=false ;                                                      \
  }                                                                    \
                                                                        \   
  template<>                                                           \
  size_t CType< ARRAY(ValueType,NumsDims)>::_size() const               \
  {                                                                    \
     return (*(this->ptrValue))->getSize() ;                           \
  }                                                                    \
                                                                       \
  template<>                                                           \
  size_t CType_ref< ARRAY(ValueType,NumsDims)>::_size() const           \
  {                                                                    \
     return (*(this->ptrValue))->getSize() ;                           \
  }                                                                    \
                                                                       \
  template <>                                                          \
  bool CType<ARRAY(ValueType,NumsDims)>::_toBuffer(CBufferOut& buffer) const        \
  {                                                                    \
      return (*(this->ptrValue))->toBuffer(buffer) ;                   \
  }                                                                    \
                                                                       \
  template <>                                                          \
  bool CType_ref<ARRAY(ValueType,NumsDims)>::_toBuffer(CBufferOut& buffer) const        \
  {                                                                    \
      return (*(this->ptrValue))->toBuffer(buffer) ;                   \
  }                                                                    \
                                                                       \
  template <>                                                          \
  bool CType<ARRAY(ValueType,NumsDims)>::_fromBuffer(CBufferIn& buffer)       \
  {                                                                    \
    allocate();                                                        \
    return (*(ptrValue))->fromBuffer(buffer) ;                         \
  }                                                                    \
                                                                       \
  template <>                                                          \
  bool CType_ref<ARRAY(ValueType,NumsDims)>::_fromBuffer(CBufferIn& buffer) const  \
  {                                                                    \
    checkEmpty() ;                                                     \ 
    return (*(this->ptrValue))->fromBuffer(buffer) ;                   \
  }                                                                    \
                                                                       \
 template <>                                                          \
  bool CType_ref<ARRAY(ValueType,NumsDims)>::_fromBuffer(CBufferIn& buffer)   \
  {                                                                    \
    shared_ptr<CArray<ValueType, NumsDims> > tmp(new CArray<ValueType, NumsDims>() ) ; \
    *(this->ptrValue)=tmp ;\
    return (*(this->ptrValue))->fromBuffer(buffer) ;                   \
  }                                                                    \
                                                                       \
                                                                       \
  template <>                                                          \
  void CType<ARRAY(ValueType,NumsDims)>::_fromString(const string& str)       \
  {                                                                    \
                                      \
  }                                                                    \
                                                                       \
  template <>                                                          \
  void CType_ref<ARRAY(ValueType,NumsDims)>::_fromString(const string& str) const \
  {                                                                    \
                                        \
  }                                                                    \
  template <>                                                          \
  void CType_ref<ARRAY(ValueType,NumsDims)>::_fromString(const string& str) \
  {                                                                    \
                                                \
  }                                                                    \
                                                                          \
  template <>                                                          \
  string CType<ARRAY(ValueType,NumsDims)>::_toString(void) const                    \
  {                                                                    \
                               \
   return string("") ;                                                 \
  }                                                                    \
                                                                          \
  template <>                                                          \
  string CType_ref<ARRAY(ValueType,NumsDims)>::_toString(void) const                    \
  {                                                                    \
                                      \
   return string("") ;                                                 \
  }
//CTYPE_ARRAY(double,1) 

//CTYPE_ARRAY(double,2) 


CTYPE_ARRAY(int,1)
CTYPE_ARRAY(int,2)
CTYPE_ARRAY(int,3)
CTYPE_ARRAY(bool,1) 
CTYPE_ARRAY(bool,2) 
CTYPE_ARRAY(bool,3) 
CTYPE_ARRAY(double,1) 
CTYPE_ARRAY(double,2) 
CTYPE_ARRAY(double,3) 
CTYPE_ARRAY(float,1) 
CTYPE_ARRAY(float,2) 
CTYPE_ARRAY(float,3) 
*/
}  

#endif  
