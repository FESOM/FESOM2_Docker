bison --verbose -d yacc_parser.yacc -o yacc_parser.cpp
flex -o lex_parser.cpp -f lex_parser.lex 
