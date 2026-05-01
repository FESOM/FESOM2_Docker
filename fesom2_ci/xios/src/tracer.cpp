#include "tracer.hpp"

#if defined(VTRACE)

#include <vt_user.h>

#elif defined(SCOREP)

#include <scorep/SCOREP_User.h>

#elif defined(ITAC)

#include <VT.h>

#endif

#include <string>
#include <map>
#include <iostream>

namespace xios
{
  using namespace std ;

  std::map<std::string,int> regionId ;
  int count=0 ;
  
  void traceOn(void)
  {
#if defined(VTRACE)
    VT_ON() ;
#elif defined(SCOREP)
    SCOREP_RECORDING_ON() ;
#elif defined(ITAC)
    VT_traceon() ;
#endif
  }
  
  void traceOff(void) 
  {
#if defined(VTRACE)
    VT_OFF() ;
#elif defined(SCOREP)
    SCOREP_RECORDING_OFF()
#elif defined(ITAC)
    VT_traceoff()   ;  
#endif
  }
  
  void traceBegin(const string& name)
  {
#if defined(VTRACE)
    VT_USER_START(name.c_str()) ;
#elif defined(SCOREP)
    SCOREP_USER_REGION_BY_NAME_BEGIN(name.c_str(),SCOREP_USER_REGION_TYPE_COMMON)

#elif defined(ITAC)
    int classhandle ;
    auto it = regionId.find(name);
    if (it==regionId.end())
    {
      classhandle=count ;
      count++ ;
      VT_symdef (classhandle, name.c_str(), "XIOS") ;
      regionId[name]=classhandle;
    }
    else classhandle = it->second ;
    VT_begin(classhandle) ;
    cout<<"VT_begin "<<name<<"  "<<classhandle<<endl ;

#endif

  }
  
  void traceEnd(const string& name)
  {
#if defined (VTRACE)
    VT_USER_END(name.c_str()) ;
#elif defined(SCOREP)
    SCOREP_USER_REGION_BY_NAME_END(name.c_str())
#elif defined(ITAC)
    int classhandle ;
    auto it = regionId.find(name);
    if (it==regionId.end())
    {
      return ;
      VT_classdef (name.c_str(), &classhandle) ;
      regionId[name]=classhandle;
    }
    else classhandle = it->second ;
    VT_end(classhandle) ;    
    cout<<"VT_end "<<name<<"  "<<classhandle<<endl ;

#endif
  }
  
   
//  void marker(const string& name,const string& text) ;
  
  
}
