%option noyywrap
%{

extern "C"
{
  int yylex(void);
}
#undef  YY_INPUT
#define YY_INPUT(b, r, s) readInputForLexer(b, &r, s)
#include <string>

int readInputForLexer(char* buffer, size_t* numBytesRead, size_t maxBytesToRead);

#include "filter_expr_node.hpp"
#include "yacc_parser.hpp"

%}

white    [ \t]+

digit    [0-9]
integer  {digit}+
exponant [eE][+-]?{integer}
real     {integer}("."{integer})?{exponant}?
id       [a-zA-Z][a-zA-Z0-9_]*
average  @{id}
var      \${id}

%%

{white}   { /* We ignore white characters */ }

{real}    {
            yylval.str = new std::string(yytext);
            return NUMBER;
          }

{average} {
            yylval.str = new std::string(yytext + 1);
            return AVERAGE;
          }

{var}     {
            yylval.str = new std::string(yytext + 1);
            return VAR;
          }

{id}      {
            yylval.str = new std::string(yytext);
            return ID;
          }                   
                 

"+"  return PLUS;
"-"  return MINUS;

"*"  return TIMES;
"/"  return DIVIDE;

"^"  return POWER;

"==" return EQ;
"<"  return LT;
">"  return GT;
"<=" return LE;
">=" return GE;
"/=" return NE;
"?" return QUESTION_MARK;
":" return COLON;
"("  return LEFT_PARENTHESIS;
")"  return RIGHT_PARENTHESIS;

"\0" return END;
