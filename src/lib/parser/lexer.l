%option c++
%option yyclass="YY::ParaLexer"
     
%{
  #include "parser.tab.hh"
  #include "lexer.hpp"
  #include "driver.hpp"
  #include <cstdlib>
  #include <iostream>

  YY::ParaLexer::ParaLexer(Driver &drv)
    : drv_{drv}, yyFlexLexer(drv.GetIstream(), drv.GetOstream()) {}

  #undef YY_DECL
  #define YY_DECL YY::Parser::symbol_type YY::ParaLexer::next_token()

  #undef yyterminate
  #define yyterminate() return YY::Parser::make_END(loc)

  #define YY_USER_ACTION  loc.step(); loc.columns(yyleng);

  int yyFlexLexer::yywrap() {
    return 1;
  }

%}


%%

"{" { return YY::Parser::make_LBRACE(loc); }
"}" { return YY::Parser::make_RBRACE(loc); }

";" { return YY::Parser::make_SEMICOLON(loc); }

"if" { return YY::Parser::make_IF(loc); }
"while" { return YY::Parser::make_WHILE(loc); }
"print" { return YY::Parser::make_PRINT(loc); }

"=" { return YY::Parser::make_ASSIGN(loc); }

"==" { return YY::Parser::make_EQ(loc); }
"!=" { return YY::Parser::make_NEQ(loc); }
"<" { return YY::Parser::make_LT(loc); }
">" { return YY::Parser::make_GT(loc); }
"<=" { return YY::Parser::make_LTE(loc); }
">=" { return YY::Parser::make_GTE(loc); }

"+" { return YY::Parser::make_PLUS(loc); }
"-" { return YY::Parser::make_MINUS(loc); }
"*" { return YY::Parser::make_STAR(loc); }
"/" { return YY::Parser::make_SLASH(loc); }

"(" { return YY::Parser::make_LPAREN(loc); }
")" { return YY::Parser::make_RPAREN(loc); }

"?" { return YY::Parser::make_QUESTION_MARK(loc); }

[0-9]+ { return YY::Parser::make_INT_TOKEN(std::atoi(yytext), loc); }

[A-Za-z_][A-Za-z_0-9]* { return YY::Parser::make_ID_TOKEN(yytext, loc); }

"//".* {
  /* Ignore oneline comments */
}

"/*"([^*]|\*+[^*/])*\*+"/" {
  /* Ignore multiline comments */
}

[ \t\n\r]+ {
  /* Ignore whitespace */
}

. {
  drv_.AddError(YY::ParseErrorCode::UnexpectedChar,
                {loc, "Unexpected char: '" + std::string(yytext) + "'.\n"});
}

%%
