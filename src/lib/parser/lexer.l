%option c++
%option yyclass="YY::ParaLexer"
     
%{
  #include "parser.tab.hh"
  #include "lexer.hpp"
  #include <cstdlib>
  #include <iostream>


  #undef YY_DECL
  #define YY_DECL YY::Parser::symbol_type YY::ParaLexer::next_token()

  int yyFlexLexer::yywrap() {
    return 1;
  }

%}


%%

"{" { return YY::Parser::make_LBRACE(); }
"}" { return YY::Parser::make_RBRACE(); }

";" { return YY::Parser::make_SEMICOLON(); }

"if" { return YY::Parser::make_IF(); }
"while" { return YY::Parser::make_WHILE(); }
"print" { return YY::Parser::make_PRINT(); }

"=" { return YY::Parser::make_ASSIGN(); }

"==" { return YY::Parser::make_EQ(); }
"!=" { return YY::Parser::make_NEQ(); }
"<" { return YY::Parser::make_LT(); }
">" { return YY::Parser::make_GT(); }
"<=" { return YY::Parser::make_LTE(); }
">=" { return YY::Parser::make_GTE(); }

"+" { return YY::Parser::make_PLUS(); }
"-" { return YY::Parser::make_MINUS(); }
"*" { return YY::Parser::make_STAR(); }
"/" { return YY::Parser::make_SLASH(); }

"(" { return YY::Parser::make_LPAREN(); }
")" { return YY::Parser::make_RPAREN(); }

"?" { return YY::Parser::make_QUESTION_MARK(); }

[0-9]+ { return YY::Parser::make_INT_TOKEN(std::atoi(yytext)); }

[A-Za-z_][A-Za-z_0-9]* { return YY::Parser::make_ID_TOKEN(yytext); }

"//".* {
  /* Ignore oneline comments */
}

"/*"([^*]|\*+[^*/])*\*+"/" {
  /* Ignore multiline comments */
}

[ \t\n\r]+ {
  /* Ignore whitespace */
}

. { std::cerr << "Unexpected char: " << yytext << "\n"; }
%%
