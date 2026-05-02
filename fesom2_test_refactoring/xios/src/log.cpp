#include "log.hpp"

namespace xios
{
  CLog info("info") ;
  CLog report("report") ;
  CLog error("error", cerr.rdbuf()) ;
}
