%{
#include "filter_expr_node.hpp"
#include <string>
#include <iostream>
#include "exception.hpp"

using namespace std;
using namespace xios;

extern "C"
{
  int yyparse(void);
  int yylex(void);
  int yyerror(const char *s);
}

  IFilterExprNode* parsed;
  std::string globalInputText;
  size_t globalReadOffset = 0;

  int readInputForLexer(char* buffer, size_t* numBytesRead, size_t maxBytesToRead)
  {
    size_t numBytesToRead = maxBytesToRead;
    size_t bytesRemaining = globalInputText.length()-globalReadOffset;
    size_t i;
    if (numBytesToRead > bytesRemaining) numBytesToRead = bytesRemaining;
    for (i = 0; i < numBytesToRead; i++) buffer[i] = globalInputText.c_str()[globalReadOffset + i];
    *numBytesRead = numBytesToRead;
    globalReadOffset += numBytesToRead;
    return 0;
  }
%}

%union
{
  std::string* str;                /* symbol table index */
  xios::IScalarExprNode* scalarNode;
  xios::IFilterExprNode* filterNode;
};

%token <str> NUMBER
%token <str> VAR ID AVERAGE
%token PLUS MINUS TIMES DIVIDE POWER
%token EQ LT GT LE GE NE
%token LEFT_PARENTHESIS RIGHT_PARENTHESIS
%token QUESTION_MARK COLON
%token <str> END

%nonassoc QUESTION_MARK COLON
%left EQ LT GT LE GE NE
%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc NEG
%right POWER

%type <scalarNode> Expression
%type <filterNode> Line Field_expr
%start Line
%%


Line:
     END            { /* Nothing to do */ }
   | Field_expr END { parsed = $1; }
  ;

Expression:
            NUMBER { $$ = new CScalarValExprNode(*$1); delete $1; }
          | VAR    { $$ = new CScalarVarExprNode(*$1); delete $1; }
          | Expression PLUS Expression   { $$ = new CScalarBinaryOpExprNode($1, "add", $3); }
          | Expression MINUS Expression  { $$ = new CScalarBinaryOpExprNode($1, "minus", $3); }
          | Expression TIMES Expression  { $$ = new CScalarBinaryOpExprNode($1, "mult", $3); }
          | Expression DIVIDE Expression { $$ = new CScalarBinaryOpExprNode($1, "div", $3); }
          | MINUS Expression %prec NEG   { $$ = new CScalarUnaryOpExprNode("neg", $2); }
          | Expression POWER Expression  { $$ = new CScalarBinaryOpExprNode($1, "pow", $3); }
          | Expression EQ Expression  { $$ = new CScalarBinaryOpExprNode($1, "eq", $3); }
          | Expression LT Expression  { $$ = new CScalarBinaryOpExprNode($1, "lt", $3); }
          | Expression GT Expression  { $$ = new CScalarBinaryOpExprNode($1, "gt", $3); }
          | Expression LE Expression  { $$ = new CScalarBinaryOpExprNode($1, "le", $3); }
          | Expression GE Expression  { $$ = new CScalarBinaryOpExprNode($1, "ge", $3); }
          | Expression NE Expression  { $$ = new CScalarBinaryOpExprNode($1, "ne", $3); }
          | Expression QUESTION_MARK Expression COLON Expression {$$ = new CScalarTernaryOpExprNode($1, "cond", $3, $5);} 
          | LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS    { $$ = $2; }
          | ID LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS { $$ = new CScalarUnaryOpExprNode(*$1, $3); delete $1; }
          ;

Field_expr:
            ID      { $$ = new CFilterFieldExprNode(*$1); delete $1; }
          | AVERAGE { $$ = new CFilterTemporalFieldExprNode(*$1); delete $1; }
          | Field_expr PLUS Field_expr   { $$ = new CFilterFieldFieldOpExprNode($1, "add", $3); }
          | Field_expr MINUS Field_expr  { $$ = new CFilterFieldFieldOpExprNode($1, "minus", $3); }
          | Field_expr TIMES Field_expr  { $$ = new CFilterFieldFieldOpExprNode($1, "mult", $3); }
          | Field_expr DIVIDE Field_expr { $$ = new CFilterFieldFieldOpExprNode($1, "div", $3); }
          | MINUS Field_expr %prec NEG   { $$ = new CFilterUnaryOpExprNode("neg", $2); }
          | Field_expr POWER Field_expr  { $$ = new CFilterFieldFieldOpExprNode($1, "pow", $3); }
          | Field_expr EQ Field_expr { $$ = new CFilterFieldFieldOpExprNode($1, "eq", $3); }
          | Field_expr LT Field_expr { $$ = new CFilterFieldFieldOpExprNode($1, "lt", $3); }
          | Field_expr GT Field_expr { $$ = new CFilterFieldFieldOpExprNode($1, "gt", $3); }
          | Field_expr LE Field_expr { $$ = new CFilterFieldFieldOpExprNode($1, "le", $3); }
          | Field_expr GE Field_expr { $$ = new CFilterFieldFieldOpExprNode($1, "ge", $3); }
          | Field_expr NE Field_expr { $$ = new CFilterFieldFieldOpExprNode($1, "ne", $3); }
          | LEFT_PARENTHESIS Field_expr RIGHT_PARENTHESIS	{ $$ = $2; }
          | Expression QUESTION_MARK Expression COLON Field_expr {$$ = new CFilterScalarScalarFieldOpExprNode($1, "cond",$3, $5);}
          | Expression QUESTION_MARK Field_expr COLON Expression {$$ = new CFilterScalarFieldScalarOpExprNode($1, "cond",$3, $5);}
          | Expression QUESTION_MARK Field_expr COLON Field_expr {$$ = new CFilterScalarFieldFieldOpExprNode($1, "cond",$3, $5);}
          | Field_expr QUESTION_MARK Expression COLON Expression {$$ = new CFilterFieldScalarScalarOpExprNode($1, "cond",$3, $5);}
          | Field_expr QUESTION_MARK Expression COLON Field_expr {$$ = new CFilterFieldScalarFieldOpExprNode($1, "cond",$3, $5);}
          | Field_expr QUESTION_MARK Field_expr COLON Expression {$$ = new CFilterFieldFieldScalarOpExprNode($1, "cond",$3, $5);}
          | Field_expr QUESTION_MARK Field_expr COLON Field_expr {$$ = new CFilterFieldFieldFieldOpExprNode($1, "cond",$3, $5);}
          | Field_expr PLUS Expression   { $$ = new CFilterFieldScalarOpExprNode($1, "add", $3); }
          | Expression PLUS Field_expr   { $$ = new CFilterScalarFieldOpExprNode($1, "add", $3); }
          | Field_expr MINUS Expression  { $$ = new CFilterFieldScalarOpExprNode($1, "minus", $3); }
          | Expression MINUS Field_expr  { $$ = new CFilterScalarFieldOpExprNode($1, "minus", $3); }
          | Field_expr TIMES Expression  { $$ = new CFilterFieldScalarOpExprNode($1, "mult", $3); }
          | Expression TIMES Field_expr  { $$ = new CFilterScalarFieldOpExprNode($1, "mult", $3); }
          | Field_expr DIVIDE Expression { $$ = new CFilterFieldScalarOpExprNode($1, "div", $3); }
          | Expression DIVIDE Field_expr { $$ = new CFilterScalarFieldOpExprNode($1, "div", $3); }
          | Field_expr POWER Expression  { $$ = new CFilterFieldScalarOpExprNode($1, "pow", $3); }
          | Field_expr EQ Expression { $$ = new CFilterFieldScalarOpExprNode($1, "eq", $3); }
          | Expression EQ Field_expr { $$ = new CFilterScalarFieldOpExprNode($1, "eq", $3); }
          | Field_expr LT Expression { $$ = new CFilterFieldScalarOpExprNode($1, "lt", $3); }
          | Expression LT Field_expr { $$ = new CFilterScalarFieldOpExprNode($1, "lt", $3); }
          | Field_expr GT Expression { $$ = new CFilterFieldScalarOpExprNode($1, "gt", $3); }
          | Expression GT Field_expr { $$ = new CFilterScalarFieldOpExprNode($1, "gt", $3); }
          | Field_expr LE Expression { $$ = new CFilterFieldScalarOpExprNode($1, "le", $3); }
          | Expression LE Field_expr { $$ = new CFilterScalarFieldOpExprNode($1, "le", $3); }
          | Field_expr GE Expression { $$ = new CFilterFieldScalarOpExprNode($1, "ge", $3); }
          | Expression GE Field_expr { $$ = new CFilterScalarFieldOpExprNode($1, "ge", $3); }
          | Field_expr NE Expression { $$ = new CFilterFieldScalarOpExprNode($1, "ne", $3); }
          | Expression NE Field_expr { $$ = new CFilterScalarFieldOpExprNode($1, "ne", $3); }
          | ID LEFT_PARENTHESIS Field_expr RIGHT_PARENTHESIS { $$ = new CFilterUnaryOpExprNode(*$1, $3); delete $1; }
          ;
%%

extern "C"
{
  int yyerror(const char *s)
  {
    ERROR("int yyerror(const char *s)", << "Parsing error: " << s << endl);
  }
}

namespace xios
{
  IFilterExprNode* parseExpr(const string& strExpr)
  {
    globalInputText = strExpr;
    globalReadOffset = 0;
    yyparse();
    return parsed;
  }
}


