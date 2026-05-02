#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace xios
{
  
  std::string getUuidStr(void)
  {
    boost::uuids::random_generator gen;
    boost::uuids::uuid u = gen();
    return boost::uuids::to_string(u) ;
  }
  
  std::string getUuidStr(const std::string& format)
  {
    size_t pos ;
    std::string retStr(format) ;
    std::string uuid(getUuidStr()) ;
    std::string id("%uuid%");
    pos=retStr.find(id) ;
    while(pos!=std::string::npos)
    {
      retStr.replace(pos,id.size(),uuid) ;
      pos=retStr.find(id) ;
    }
    return retStr;
  }
}

