/*!
   \file netCdfException.hpp
   \author Ha NGUYEN
   \date 08 Oct 2014
   \since 07 Oct 2014

   \brief Exception management.
 */
#ifndef __NETCDF_EXCEPTION_HPP__
#define __NETCDF_EXCEPTION_HPP__

#include <iostream>
#include <exception>

namespace xios
{
/*!
\class CNetCdfException
 This class manages exceptions risen by CNetCdfInterface
*/
class CNetCdfException : public virtual std::exception
{
public:
  CNetCdfException(const std::string& ss) : exStr_(ss) {}
  CNetCdfException(const CNetCdfException& netEx) : exStr_(netEx.exStr_) {}
  ~CNetCdfException() throw() {}
  const char* what() const throw() { return exStr_.c_str();}
protected:
  std::string exStr_;
};

}

#endif // __NETCDF_EXCEPTION_HPP__
