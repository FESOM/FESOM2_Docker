#ifndef __STRING_TOOLS_HPP__
#define __STRING_TOOLS_HPP__

#include <string>
#include <regex>
#include <vector>

namespace xios
{
  std::vector<std::string> splitRegex(const std::string& input, const std::string& regex) ;

  inline std::vector<std::string> splitRegex(const std::string& input, const std::string& regex)
  {
      // passing -1 as the submatch index parameter performs splitting
      std::regex re(regex);
      std::regex_token_iterator<std::string::const_iterator>
          first{input.begin(), input.end(), re, -1},
          last;
      return {first, last}; 
  }

}
#endif
