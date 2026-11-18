%option c++
%option yyclass="YY::ParaLexer"
     
%{
  #include "parser.tab.hh"
  #include "lexer.hpp"
  #include <cstdlib>
  #include <iostream>


  #undef YY_DECL
  #define YY_DECL int YY::ParaLexer::yylex(YY::Parser::semantic_type* yylval)

  int yyFlexLexer::yywrap() {
    return 1;
  }

%}


%%

"{" { return YY::Parser::token::LBRACE; }
"}" { return YY::Parser::token::RBRACE; }

";" { return YY::Parser::token::SEMICOLON; }

"if" { return YY::Parser::token::IF; }
"while" { return YY::Parser::token::WHILE; }
"print" { return YY::Parser::token::PRINT; }

"=" { return YY::Parser::token::ASSIGN; }

"==" { return YY::Parser::token::EQ; }
"!=" { return YY::Parser::token::NEQ; }
"<" { return YY::Parser::token::LT; }
">" { return YY::Parser::token::GT; }
"<=" { return YY::Parser::token::LTE; }
">=" { return YY::Parser::token::GTE; }

"+" { return YY::Parser::token::PLUS; }
"-" { return YY::Parser::token::MINUS; }
"*" { return YY::Parser::token::STAR; }
"/" { return YY::Parser::token::SLASH; }

"(" { return YY::Parser::token::LPAREN; }
")" { return YY::Parser::token::RPAREN; }

"?" { return YY::Parser::token::QUESTION_MARK; }

[0-9]+ {
  yylval->emplace<int>(std::atoi(yytext));
  return YY::Parser::token::INT_TOKEN;
}

[A-Za-z_][A-Za-z_0-9]* {
  yylval->emplace<std::string>(yytext);
  return YY::Parser::token::ID_TOKEN;
}

"//".* {
  /* Ignore oneline comments */
}

"/*"([^*]|\*+[^*/])*\*+"/" {
  /* Ignore multiline comments */
}

[ \t\n\r]+ {
  /* Ignore whitespace */
}

.       { std::cerr << "Unexpected char: " << yytext << "\n"; }
%%
