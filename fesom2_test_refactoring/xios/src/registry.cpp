#include "registry.hpp"
#include "type.hpp"
#include <mpi.hpp>
#include <fstream>
#include <sstream>

namespace xios
{
  using namespace std;

  CRegistry::CRegistry(const CRegistry& reg) : communicator(reg.communicator)
  {
    for(map<string,pair<size_t,char*> >::const_iterator it=reg.registry.begin() ; it!=reg.registry.end() ; ++it)
    {
      char* buffer=new char[it->second.first] ;
      memcpy(buffer,it->second.second,it->second.first) ;
      registry.insert(pair<string, pair<size_t,char*> >(it->first, pair<size_t,char*>(it->second.first,buffer))) ; 
    }
  }

        
  void CRegistry::reset()
  {
    for(map<string,pair<size_t,char*> >::const_iterator it=registry.begin() ; it!=registry.end() ; ++it)
    {
      if (it->second.first>0) delete[] it->second.second ;
    }
    registry.clear() ;
  }

  void CRegistry::setKey_(const string& key_, const CBaseType& value)
  {
    const string key=path+key_ ;
    if (!value.isEmpty())
    {
      size_t size=value.size();
      
      map<string,pair<size_t,char*> >::iterator it=registry.find(key) ;

      if (it!=registry.end())
      {
        delete[] it->second.second ;
        registry.erase(it) ;
      }

      char* buffer=new char[size] ;
      CBufferOut tmpBuff(buffer,size) ;
      value.toBuffer(tmpBuff) ;
      registry.insert(pair<string, pair<size_t,char*> >(key, pair<size_t,char*>(size,buffer))) ;
    }
  }

  void CRegistry::getKey_(const string& key_, CBaseType& value)
  {
    const string key=path+key_ ;
    size_t size=value.size();
      
    map<string,pair<size_t,char*> >::iterator it=registry.find(key) ;

    if (it!=registry.end())
    {
      CBufferIn tmpBuff(it->second.second,it->second.first) ;
      value.fromBuffer(tmpBuff) ;
    }
    else value.reset() ;
  }

  bool CRegistry::foundKey(const string& key_) const
  {
    const string key=path+key_ ;
    map<string,pair<size_t,char*> >::const_iterator it=registry.find(key) ;
    if (it!=registry.end()) return true ;
    else return false ;
  }
  
  bool CRegistry::toBuffer(CBufferOut& buffer) const
  {
    buffer<<registry.size() ;
    for(map<string,pair<size_t,char*> >::const_iterator it=registry.begin() ; it!=registry.end() ; ++it)
    {
      buffer<<it->first<<it->second.first ;
      if (!buffer.put(it->second.second,it->second.first)) ERROR("bool CRegistry::toBuffer(CBufferOut& buffer) const)",
                                                           << "Not enough free space in buffer to queue the data."); 
    }
    return true ;
  }

  size_t CRegistry::size() const
  {
    size_t s=0;
    size_t size_t_size=CType<size_t>(0).size() ;
    s+=size_t_size ;
    for(map<string,pair<size_t,char*> >::const_iterator it=registry.begin() ; it!=registry.end() ; ++it)
      s+=(CType<string>(it->first)).size() + size_t_size + it->second.first ;
    return s ;
  }

  void CRegistry::fromString(const string& str)
  {
     ERROR("void CRegistry::fromString(const string& str)",<< "This method has not been implemented"); 
  }

  string CRegistry::toString() const
  {
    ostringstream oss;
    
    for(map<string,pair<size_t,char*> >::const_iterator it=registry.begin() ; it!=registry.end() ; ++it)
    {
      oss<<"Key = "<< it->first  <<" , size : "<<it->second.first<<"  ASCII value : "<<string((char*) it->second.second,it->second.first)<<endl ;
    }
    return oss.str() ;
  }

  

  bool CRegistry::fromBuffer(CBufferIn& buffer)
  {
    string key ;
    size_t size ;
    char* value ;
    size_t nKeys ;
    buffer >> nKeys ;
    for(size_t i=0;i<nKeys;++i)
    {
      buffer>>key>>size ;
      if (size > 0)
      {
        value = new char[size] ;
        buffer.get(value,size) ;
      }
      
      map<string,pair<size_t,char*> >::iterator it=registry.find(key) ;
      if (it!=registry.end())
      {
        delete[] it->second.second ;
        registry.erase(it) ;
      }
      registry.insert(pair<string, pair<size_t,char*> >(key, pair<size_t,char*>(size,value))) ;        
    }
    return true ;
  }  

  void CRegistry::toFile(const string& filename)
  {
    if (registry.size()==0) return ;
    
    CBufferOut buffer(this->size()) ;
    this->toBuffer(buffer) ;
    ofstream file(filename.c_str(), ofstream::out ) ;
    size_t size=buffer.count() ;
    file.write((const char*) &size,sizeof(size)) ;
    file.write((const char*) buffer.start(),size) ;
    file.close() ;
  }

  void CRegistry::fromFile(const string& filename)
  {
    ifstream file(filename.c_str(), ifstream::in | ifstream::binary) ;
    if (!file) return ;
    size_t size;
    file.read((char*) &size,sizeof(size)) ;
    
    CBufferIn buffer(size) ;
    file.read((char*) buffer.ptr(),size) ;
    this->fromBuffer(buffer) ;

    file.close() ;
  }
    
  void CRegistry::mergeRegistry(const CRegistry& inRegistry)
  {
    size_t size ;
    char* value;
    
    for(map<string,pair<size_t,char*> >::const_iterator it=inRegistry.registry.begin() ; it!=inRegistry.registry.end() ; ++it)
    {
      const string& key=it->first ;
      map<string,pair<size_t,char*> >::iterator it2=registry.find(key) ;
      if (it2==registry.end())
      {
        size=it->second.first ;
        value=new char[size] ;
        memcpy(value,it->second.second,size) ;
        registry.insert(pair<string, pair<size_t,char*> >(key, pair<size_t,char*>(size,value))) ;      
      }
    }
  }

  
  void CRegistry::bcastRegistry(void)
  {
    int rank ;
    MPI_Comm_rank(communicator,&rank);
    if (rank==0)
    {
      CBufferOut buffer(this->size()) ;
      this->toBuffer(buffer) ;
      int size=buffer.count() ;
      MPI_Bcast(&size,1,MPI_INT,0,communicator) ;
      MPI_Bcast(buffer.start(),size,MPI_CHAR,0,communicator) ;
    }
    else
    {
      int size ;
      MPI_Bcast(&size,1,MPI_INT,0,communicator) ;
      CBufferIn buffer(size) ;
      MPI_Bcast(buffer.start(),size,MPI_CHAR,0,communicator) ;
      this->fromBuffer(buffer) ;
    }
  }
  void CRegistry::gatherRegistry(void)
  {
    gatherRegistry(communicator) ;
  }

  void CRegistry::gatherRegistry(const MPI_Comm& comm)
  {
    int rank,mpiSize ;
    MPI_Comm_rank(comm,&rank);
    MPI_Comm_size(comm,&mpiSize);

    int* sizes=new int[mpiSize] ;
    CBufferOut localBuffer(this->size()) ;
    this->toBuffer(localBuffer) ;
    int localSize=localBuffer.count() ;
    MPI_Gather(&localSize,1,MPI_INT,sizes,1,MPI_INT,0,comm) ;

    char* globalBuffer ;
    int*   displs ;
    
    if (rank==0)
    {
      size_t globalBufferSize=0 ;
      displs=new int[mpiSize] ;
      for (int i=0;i<mpiSize;++i)
      {
        displs[i]=globalBufferSize ;
        globalBufferSize+=sizes[i] ;
      }

      globalBuffer=new char[globalBufferSize] ;
      MPI_Gatherv(localBuffer.start(),localSize,MPI_CHAR,globalBuffer,sizes,displs,MPI_CHAR,0,comm) ;
      for(int i=1;i<mpiSize;++i)
      {
        CBufferIn buffer(globalBuffer+displs[i],sizes[i]) ;
        CRegistry reg ;
        reg.fromBuffer(buffer) ;
        mergeRegistry(reg) ;
      }
      delete[] displs ;
      delete[] globalBuffer ;
    }
    else  MPI_Gatherv(localBuffer.start(),localSize,MPI_CHAR,globalBuffer,sizes,displs,MPI_CHAR,0,comm) ;   
    delete[] sizes ;
    
  }

  void CRegistry::hierarchicalGatherRegistry(void)
  {
    hierarchicalGatherRegistry(communicator) ;
  }

  void CRegistry::hierarchicalGatherRegistry(const MPI_Comm& comm)
  {
    int mpiRank,mpiSize ;
    MPI_Comm_rank(comm,&mpiRank);
    MPI_Comm_size(comm,&mpiSize);    

    if (mpiSize>2)
    {
      int color ;
      if (mpiRank<mpiSize/2+mpiSize%2) color=0 ;
      else color=1 ;
      MPI_Comm commUp ;
      MPI_Comm_split(comm,color,mpiRank,&commUp) ,
      hierarchicalGatherRegistry(commUp) ;
      MPI_Comm_free(&commUp) ;
    }

    if (mpiSize>1)
    {
      MPI_Comm commDown ;
      int color ;
      
      if (mpiRank==0 || mpiRank==mpiSize/2+mpiSize%2) color=0 ;
      else color=1 ;
      MPI_Comm_split(comm,color,mpiRank,&commDown) ;
      if (color==0) gatherRegistry(commDown) ;
      MPI_Comm_free(&commDown) ;    
    }
  }

}
