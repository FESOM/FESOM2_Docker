#ifndef __XIOS_LEX_PARSER_HPP__
#define __XIOS_LEX_PARSER_HPP__

#include <string>
namespace xios
{
  IFilterExprNode* parseExpr(const std::string& strExpr);
}

#endif
