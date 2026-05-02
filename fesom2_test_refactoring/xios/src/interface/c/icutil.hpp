/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */


#ifndef __ICUTIL_HPP__
#define __ICUTIL_HPP__

#include <string>
#include <algorithm>

// ///////////////////////// Définitions/Déclarations /////////////////////// //

inline bool cstr2string(const char* cstr, int cstr_size, std::string& str)
{
  if (cstr_size != -1)
  { 
    std::string valtemp;
    std::size_t d, f = 0;

    valtemp.append(cstr, cstr_size);
    d = valtemp.find_first_not_of(' ');
    f = valtemp.find_last_not_of (' ');
    str = valtemp.substr(d, f - d + 1);

    return true;
  }
  else
     return false;
}

inline bool string_copy(const std::string& str, char* cstr, int cstr_size)
{
  if (str.size() > cstr_size)
    return false;
  else
  {
    std::fill(cstr, cstr + cstr_size, ' ');
    str.copy(cstr, cstr_size);
    return true;
  }
}

#endif // __ICUTIL_HPP__
