#include "xios_spl.hpp"
#include "buffer_in.hpp"


namespace xios
{
    CBufferIn::CBufferIn(void* buffer,size_t size)
    {
      own=false ;
      size_=0 ;
      this->realloc(buffer,size) ;
    }
    
    CBufferIn::CBufferIn(size_t size)
    {
      own=false ;
      size_=0 ;
      realloc(size) ;
    }

    CBufferIn::CBufferIn(void)
    {
      own=false ;
      size_=0 ;
    }

    void CBufferIn::realloc(size_t size)
    {
      this->realloc(new char[size],size) ;
      own=true ;
    }

    void CBufferIn::realloc(void* buffer,size_t size)
    {
      if (own) delete [] begin ;
      begin=(char*)buffer ;
      size_=size ;
      current=begin ;
      end=begin+size_ ;
      count_=0 ;
      own=false ;
    }

    bool CBufferIn::advance(size_t n) { return advance<char>(n); }

    size_t CBufferIn::remain(void)
    {
      return size_-count_ ;
    }    

    size_t CBufferIn::count(void)
    {
      return count_ ;
    }

    size_t CBufferIn::bufferSize(void)
    {
      return size_ ;
    }
    
    CBufferIn::~CBufferIn()
    {
      if (own) delete [] begin ;
    }

    void* CBufferIn::ptr(void) { return current; }
    
}
    
      
    
