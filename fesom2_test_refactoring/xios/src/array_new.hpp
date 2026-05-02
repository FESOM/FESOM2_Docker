#ifndef __XIOS_ARRAY_HPP__
#define __XIOS_ARRAY_HPP__

#define BZ_COLUMN_MAJOR_ARRAY
#include <blitz/array.h>
#include "buffer_in.hpp"
#include "buffer_out.hpp"
#include "message.hpp"
#include <cmath>

using namespace blitz;
BZ_DECLARE_FUNCTION(round)

namespace xios
{
  template <typename T_numtype,int N_rank>
  class CArray : public Array<T_numtype,N_rank>, public virtual CBaseType
  {
    private:
      bool initialized;

    public:
      typedef typename Array<T_numtype,N_rank>::T_default_storage T_default_storage;
      using Array<T_numtype,N_rank>::operator =;

      template<typename T_expr> explicit CArray(_bz_ArrayExpr<T_expr> expr)
        : Array<T_numtype,N_rank>(expr)
        , initialized(true)
      {}

      CArray(GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(storage)
        , initialized(false)
      {}

      explicit CArray(int length0, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0, length1, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, int length2, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0, length1, length2, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, int length2, int length3, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0, length1, length2, length3, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, int length2, int length3, int length4, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0,length1, length2, length3, length4, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, int length2, int length3, int length4, int length5, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0, length1, length2, length3, length4, length5, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, int length2, int length3, int length4, int length5, int length6, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0, length1, length2, length3, length4, length5, length6, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, int length2, int length3, int length4, int length5, int length6, int length7,
             GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0, length1, length2, length3, length4, length5, length6, length7, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, int length2, int length3, int length4, int length5, int length6,
             int length7, int length8, GeneralArrayStorage<N_rank> storage = T_default_storage())
       : Array<T_numtype,N_rank>(length0, length1, length2, length3, length4, length5, length6, length7, length8, storage)
       , initialized(true)
      {}

      CArray(int length0, int length1, int length2, int length3, int length4,
             int length5, int length6, int length7, int length8, int length9, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(length0, length1, length2, length3, length4, length5, length6, length7, length8, length9, storage)
        , initialized(true)
      {}

      CArray(int length0, int length1, int length2, int length3, int length4, int length5, int length6,
             int length7, int length8, int length9, int length10, GeneralArrayStorage<N_rank> storage = T_default_storage())
       : Array<T_numtype,N_rank>(length0, length1, length2, length3, length4, length5, length6, length7, length8, length9, length10, storage)
       , initialized(true)
      {}

      CArray(T_numtype* restrict dataFirst, TinyVector<int, N_rank> shape, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(dataFirst, shape, storage)
        , initialized(true)
      {}

      CArray(T_numtype* restrict dataFirst, TinyVector<int, N_rank> shape, TinyVector<diffType, N_rank> stride,
             GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(dataFirst, shape, stride, storage)
        , initialized(true)
      {}

      CArray(T_numtype* restrict dataFirst, TinyVector<int, N_rank> shape, preexistingMemoryPolicy deletionPolicy,
            GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(dataFirst, shape, deletionPolicy, storage)
        , initialized(true)
      {}

      CArray(T_numtype* restrict dataFirst, TinyVector<int, N_rank> shape, TinyVector<diffType, N_rank> stride,
             preexistingMemoryPolicy deletionPolicy, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(dataFirst, shape, stride, deletionPolicy, storage)
        , initialized(true)
      {}

      CArray(const TinyVector<int, N_rank>& extent, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(extent, storage)
        , initialized(true)
      {}

      CArray(const TinyVector<int, N_rank>& lbounds, const TinyVector<int, N_rank>& extent,
             const GeneralArrayStorage<N_rank>& storage)
        : Array<T_numtype,N_rank>(lbounds, extent, storage)
        , initialized(true)
      {}

      CArray(Range r0, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, Range r3, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, r3, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, Range r3, Range r4, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, r3, r4, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, r3, r4, r5, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6,
             GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, r3, r4, r5, r6, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7,
             GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, r3, r4, r5, r6, r7, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5,
             Range r6, Range r7, Range r8, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, r3, r4, r5, r6, r7, r8, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5,
             Range r6, Range r7, Range r8, Range r9, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, storage)
        , initialized(true)
      {}

      CArray(Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6, Range r7,
             Range r8, Range r9, Range r10, GeneralArrayStorage<N_rank> storage = T_default_storage())
        : Array<T_numtype,N_rank>(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, storage)
        , initialized(true)
      {}

      CArray(const CArray<T_numtype, N_rank>& array)
        : Array<T_numtype,N_rank>(array)
        , initialized(array.initialized)
      {}

      CArray(const Array<T_numtype, N_rank>& array)
        : Array<T_numtype,N_rank>(array)
        , initialized(true)
      {}

      CArray(const TinyVector<int,N_rank-1>& shape, int lastExtent, const GeneralArrayStorage<N_rank>& storage)
        : Array<T_numtype,N_rank>(shape, lastExtent, storage)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0)
        : Array<T_numtype,N_rank>(array, r0)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1)
        : Array<T_numtype,N_rank>(array, r0, r1)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2)
        : Array<T_numtype,N_rank>( array, r0, r1, r2)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2, Range r3)
        : Array<T_numtype,N_rank>(array, r0, r1, r2, r3)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2,
             Range r3, Range r4)
        : Array<T_numtype,N_rank>(array, r0, r1, r2, r3,  r4)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2,
             Range r3, Range r4, Range r5)
        : Array<T_numtype,N_rank>( array, r0, r1, r2, r3, r4, r5)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2, Range r3,
             Range r4, Range r5, Range r6)
        : Array<T_numtype,N_rank>( array, r0, r1, r2, r3, r4, r5, r6)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2, Range r3, Range r4,
             Range r5, Range r6, Range r7)
        : Array<T_numtype,N_rank>(array, r0, r1, r2, r3, r4, r5, r6, r7)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5,
             Range r6, Range r7, Range r8)
        : Array<T_numtype,N_rank>(array, r0, r1, r2, r3, r4, r5, r6, r7, r8)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5,
             Range r6, Range r7, Range r8, Range r9)
        : Array<T_numtype,N_rank>(array, r0, r1, r2, r3, r4, r5, r6, r7, r8, r9)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, Range r0, Range r1, Range r2, Range r3, Range r4, Range r5, Range r6,
             Range r7, Range r8, Range r9, Range r10)
        : Array<T_numtype,N_rank>(array, r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, const RectDomain<N_rank>& subdomain)
        : Array<T_numtype,N_rank>(array, subdomain)
        , initialized(true)
      {}

      CArray(Array<T_numtype, N_rank>& array, const StridedDomain<N_rank>& subdomain)
        : Array<T_numtype,N_rank>(array, subdomain)
        , initialized(true)
      {}

      template<int N_rank2, typename R0, typename R1, typename R2, typename R3, typename R4, typename R5,
                            typename R6, typename R7, typename R8, typename R9, typename R10>
      CArray(Array<T_numtype,N_rank2>& array, R0 r0, R1 r1, R2 r2, R3 r3, R4 r4, R5 r5, R6 r6, R7 r7, R8 r8, R9 r9, R10 r10)
        : Array<T_numtype,N_rank>(array, r0,r1, r2, r3, r4, r5, r6, r7, r8, r9, r10)
        , initialized(true)
      {}

      virtual ~CArray() {}

      CArray<T_numtype, N_rank> copy() const
      {
        CArray<T_numtype, N_rank> copy = Array<T_numtype, N_rank>::copy();
        copy.initialized = initialized;
        return copy;
      }

      void reference(const CArray<T_numtype, N_rank>& array)
      {
        Array<T_numtype,N_rank>::reference(array);
        initialized = array.initialized;
      }

      void reference(const Array<T_numtype,N_rank>& array)
      {
        Array<T_numtype,N_rank>::reference(array);
        initialized = true;
      }

      bool operator== (const CArray<T_numtype,N_rank>& array)
      {
        size_t nbThis = this->numElements();
        size_t nbArr  = array.numElements();
        if (nbThis != nbArr) return false;
        if (nbThis==0 && nbArr==0) return true;
        typename Array<T_numtype,N_rank>::const_iterator itx=array.begin(), itxe=array.end(), ity=this->begin() ;
        for(;itx!=itxe;++itx,++ity) if (*itx!=*ity) return false ;
        return true;
      }

      bool operator== (const Array<T_numtype,N_rank>& array)
      {
        return ((*this) == (dynamic_cast<const CArray<T_numtype,N_rank>& >(array)));
      }

      void resize(int extent)
      {
        Array<T_numtype,N_rank>::resize(extent);
        initialized = true;
      }
      void resize(int extent1, int extent2)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3, int extent4)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3, extent4);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3, int extent4, int extent5)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3, extent4, extent5);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3, extent4, extent5, extent6);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3, int extent4, int extent5,
                  int extent6, int extent7)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3, extent4, extent5,
                                        extent6, extent7);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3, int extent4, int extent5,
                  int extent6, int extent7, int extent8)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3, extent4, extent5,
                                        extent6, extent7, extent8);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3, int extent4, int extent5,
                  int extent6, int extent7, int extent8, int extent9)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3, extent4, extent5,
                                        extent6, extent7, extent8, extent9);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3, int extent4, int extent5,
                  int extent6, int extent7, int extent8, int extent9, int extent10)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3, extent4, extent5,
                                        extent6, extent7, extent8, extent9, extent10);
        initialized = true;
      }
      void resize(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6,
                  int extent7, int extent8, int extent9, int extent10, int extent11)
      {
        Array<T_numtype,N_rank>::resize(extent1, extent2, extent3, extent4, extent5, extent6,
                                        extent7, extent8, extent9, extent10, extent11);
        initialized = true;
      }

      void resize(Range r1)
      {
        Array<T_numtype,N_rank>::resize(r1);
        initialized = true;
      }
      void resize(Range r1, Range r2)
      {
        Array<T_numtype,N_rank>::resize(r1, r2);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3, Range r4)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3, r4);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3, Range r4, Range r5)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3, r4, r5);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3, Range r4, Range r5, Range r6)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3, r4, r5, r6);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3, Range r4, Range r5,
                  Range r6, Range r7)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3, r4, r5,
                                        r6, r7);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3, Range r4, Range r5,
                  Range r6, Range r7, Range r8)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3, r4, r5,
                                        r6, r7, r8);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3, Range r4, Range r5,
                  Range r6, Range r7, Range r8, Range r9)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3, r4, r5,
                                        r6, r7, r8, r9);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3, Range r4, Range r5,
                  Range r6, Range r7, Range r8, Range r9, Range r10)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3, r4, r5,
                                        r6, r7, r8, r9, r10);
        initialized = true;
      }
      void resize(Range r1, Range r2, Range r3, Range r4, Range r5, Range r6,
                  Range r7, Range r8, Range r9, Range r10, Range r11)
      {
        Array<T_numtype,N_rank>::resize(r1, r2, r3, r4, r5, r6,
                                        r7, r8, r9, r10, r11);
        initialized = true;
      }

      void resize(const TinyVector<int,N_rank>& extent)
      {
        Array<T_numtype,N_rank>::resize(extent);
        initialized = true;
      }

      void resizeAndPreserve(const TinyVector<int,N_rank>& extent)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent);
        initialized = true;
      }

      void resizeAndPreserve(int extent)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3, int extent4)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3, extent4);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3, int extent4, int extent5)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3, extent4, extent5);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3, int extent4,
                             int extent5, int extent6)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3, extent4,
                                                   extent5, extent6);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3, int extent4,
                             int extent5, int extent6, int extent7)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3, extent4,
                                                   extent5, extent6, extent7);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3, int extent4,
                             int extent5, int extent6, int extent7, int extent8)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3, extent4,
                                                   extent5, extent6, extent7, extent8);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3, int extent4, int extent5,
                             int extent6, int extent7, int extent8, int extent9)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3, extent4, extent5,
                                                   extent6, extent7, extent8, extent9);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3, int extent4, int extent5,
                             int extent6, int extent7, int extent8, int extent9, int extent10)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3, extent4, extent5,
                                                   extent6, extent7, extent8, extent9, extent10);
        initialized = true;
      }
      void resizeAndPreserve(int extent1, int extent2, int extent3, int extent4, int extent5, int extent6,
                             int extent7, int extent8, int extent9, int extent10, int extent11)
      {
        Array<T_numtype,N_rank>::resizeAndPreserve(extent1, extent2, extent3, extent4, extent5, extent6,
                                                   extent7, extent8, extent9, extent10, extent11);
        initialized = true;
      }

      virtual void fromString(const string& str) { istringstream iss(str); iss >> *this; initialized = true; }
      virtual string toString(void) const { ostringstream oss; oss << *this; return oss.str(); }

      virtual string dump(void) const
      {
        ostringstream oss;
        oss << this->shape()<<" ";
        if (this->shape().numElements() == 1 && this->shape().dataFirst()[0] == 1)
          oss << this->dataFirst()[0];
        else
          oss << this->dataFirst()[0] <<" ... "<< this->dataFirst()[this->numElements()-1];
        return oss.str();
      }

      virtual void reset(void) { this->free(); initialized = false; }
      virtual bool isEmpty(void) const { return !initialized; }
      virtual size_t size(void) const { return size(this->numElements()); }
      static size_t size(sizeType numElements) { return (N_rank + 1) * sizeof(int) + sizeof(size_t) + numElements * sizeof(T_numtype); }

      virtual CBaseType* clone(void) const { return new CArray(*this); }

      virtual bool toBuffer(CBufferOut& buffer) const
      {
        bool ret;
        ret =  buffer.put(this->dimensions());
        ret &= buffer.put(this->shape().data(), this->dimensions());
        ret &= buffer.put(this->numElements());
        ret &= buffer.put(this->dataFirst(), this->numElements());
        return ret;
      }

      virtual bool fromBuffer(CBufferIn& buffer)
      {
        bool ret;
        int numDim;
        TinyVector<int,N_rank> vect;
        size_t ne;

        ret =  buffer.get(numDim);
        ret &= buffer.get(vect.data(), N_rank);
        this->resize(vect);
        ret &= buffer.get(ne);
        ret &= buffer.get(this->dataFirst(), ne);

        initialized = true;

        return ret;
      }
  };


#define macro(NRANK)\
\
  template <>\
  inline size_t CArray<StdString,NRANK>::size(void) const\
  {\
    size_t size=(1 + NRANK) * sizeof(int) ;\
    Array<StdString,NRANK>::const_iterator it, itb=this->begin(), ite=this->end() ;\
\
    for(it=itb;it!=ite;++it)\
    {\
      size+= sizeof(size_t) ;\
      size+= (*it).size();\
    } \
    return size ;\
  }\
\
/* for array string this function is an evaluation of maximum size of the array, considering stringArrayLen is the maximum size of the strings*/ \
  template <>\
  inline size_t CArray<StdString,NRANK>::size(sizeType numElements)\
  {\
    return (NRANK + 1) * sizeof(int) + numElements * stringArrayLen;\
  }\
  \
  template <>\
  inline bool CArray<StdString,NRANK>::toBuffer(CBufferOut& buffer) const\
  {\
    bool ret;\
    ret =  buffer.put(this->dimensions());\
    ret &= buffer.put(this->shape().data(), this->dimensions());\
\
    Array<StdString,NRANK>::const_iterator it, itb=this->begin(), ite=this->end() ;\
\
    for(it=itb;it!=ite;++it)\
    {\
      ret &= buffer.put((*it).size()) ;\
      ret &= buffer.put((*it).data(),(*it).size());\
    } \
    return ret;\
  }\
\
  template <>\
  inline bool CArray<StdString,NRANK>::fromBuffer(CBufferIn& buffer)\
  {\
     bool ret;\
     int numDim;\
     TinyVector<int,NRANK> vect;\
     size_t ne;\
\
     ret =  buffer.get(numDim);\
     ret &= buffer.get(vect.data(), NRANK);\
     this->resize(vect);\
\
     Array<StdString,NRANK>::iterator it, itb=this->begin(), ite=this->end() ;\
     for(it=itb;it!=ite;++it)\
     {\
       ret &= buffer.get(ne) ;\
       char* str = new char[ne] ;\
       ret &= buffer.get(str, ne);\
       *it = string(str,ne) ;\
       delete [] str ;\
     }\
     initialized = true;\
     return ret;\
  }
macro(1)
macro(2)
macro(3)
macro(4)
macro(5)
macro(6)
macro(7)

#undef macro

  template <typename T_numtype,int N_rank> inline CBufferOut& operator<<(CBufferOut& buffer, const CArray<T_numtype,N_rank>& array)
  {
    if (!array.toBuffer(buffer)) ERROR("template <typename T_numtype,int N_rank> inline CBufferOut& operator<<(CBufferOut& buffer, const CArray& array)",
                                       << "Not enough free space in buffer to queue the array.");
    return buffer;
  }

  template <typename T_numtype,int N_rank> inline CBufferIn& operator>>(CBufferIn& buffer, CArray<T_numtype, N_rank>& array)
  {
    if (!array.fromBuffer(buffer)) ERROR("template <typename T_numtype,int N_rank> inline CBufferIn& operator>>(CBufferIn& buffer, CArray& array)",
                                         << "Not enough data in buffer to unqueue the array.");
    return buffer;
  }

  template <typename T_numtype,int N_rank> inline CMessage& operator<<(CMessage& msg, const CArray<T_numtype, N_rank>& array)
  {
    msg.push(array);
    return msg;
  }

  template <typename T_numtype,int N_rank> inline CMessage& operator<<(CMessage& msg, CArray<T_numtype, N_rank>& array)
  {
    msg.push(array);
    return msg;
  }
}

#endif
