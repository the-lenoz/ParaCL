%{
  #include "parser.tab.hh"
  #include <cstdlib>
  #include <iostream>


  #ifndef YY_DECL
  #define YY_DECL int yylex(YY::Parser::semantic_type* yylval)
  YY_DECL;
  #endif
%}

%option noyywrap

%%
[0-9]+ {
  yylval->emplace<int>(std::atoi(yytext));
  return YY::Parser::token::INT_TOKEN;
}

"+" {
  return YY::Parser::token::PLUS;
}

[ \t\n\r]+ {
  /* Ignore whitespace */
}

.       { std::cerr << "Unexpected char: " << yytext << "\n"; }
%%
