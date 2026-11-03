%skeleton "lalr1.cc"
%require "3.2"
%header
%defines
%define api.parser.class {Parser}
%define api.namespace {YY}
%define api.value.type variant
%define parse.error verbose

%code provides {
    #define YY_DECL int yylex(YY::Parser::semantic_type* yylval)
    YY_DECL;
}

%code requires {
    #include <memory>
    #include <iostream>
    #include <utility>
    #include "AST.hpp"
}


%token <int> INT_TOKEN
%token PLUS
%token END 0 "end of file"


%type <std::unique_ptr<ASTNode>> program
%type <std::unique_ptr<ASTNode>> expr

%parse-param { std::unique_ptr<ASTNode>* root }

%%

program:
  expr { 
    *root = std::move($1);
  };

expr:
  INT_TOKEN { 
    $$ = std::make_unique<IntNode>($1); 
  }
  | expr PLUS INT_TOKEN { 
    auto right_node = std::make_unique<IntNode>($3);
    $$ = std::make_unique<AddNode>(std::move($1), std::move(right_node)); 
  };

%%

void YY::Parser::error(const std::string& msg) {
    std::cerr << "Parser error: " << msg << std::endl;
}
