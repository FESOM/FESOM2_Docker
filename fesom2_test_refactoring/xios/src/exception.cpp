#include "exception.hpp"

/// boost headers ///
#include <boost/cast.hpp>
#include "client.hpp"
#include "server.hpp"
#include "log.hpp"

namespace xios
{
  /// ////////////////////// Définitions ////////////////////// ///
   CException::CException(void)
      : CObject(), desc_rethrow(true), stream()
   { /* Ne rien faire de plus */ }

   CException::CException(const std::string & id)
      : CObject(id), desc_rethrow(true), stream()
   { /* Ne rien faire de plus */ }

   CException::CException(const CException & exception)
//      : std::basic_ios<char>()
       : CObject(exception.getId())
//      , StdOStringStream()
//      , desc_rethrow(false)
   { (*this) << exception.str(); }

   CException::~CException(void)
   {
//      if (desc_rethrow)
//#ifdef __XIOS_NOABORT
//      {
//        throw (*this);
//      }
//#else
//     {
//      error << this->getMessage() << std::endl;
//        throw 4;
//      MPI_Abort(CXios::globalComm, -1); //abort();
//      }
//#endif
   }

   //---------------------------------------------------------------

   std::string CException::getMessage(void) const
   {
//     StdOStringStream oss;
//     oss << "> Error [" << this->getId() << "] : " << this->str();
//     return (oss.str());
     return (stream.str());
   }

   StdOStringStream &  CException::getStream(void)
//   { return (*boost::polymorphic_cast<StdOStringStream*>(this)); }
   { return stream; }

   std::string CException::toString(void) const
//   { return (std::string(this->getMessage())); }
   { return stream.str(); }

   void CException::fromString(const std::string & str)
   { }
//   { this->str(str); }

   //---------------------------------------------------------------

} // namespace xios
