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


%token LBRACE
%token RBRACE

%token SEMICOLON

%token IF
%token WHILE
%token PRINT

%token ASSIGN

%token EQ
%token LT
%token GT
%token LTE
%token GTE

%token PLUS
%token MINUS
%token STAR
%token SLASH

%token LPAREN
%token RPAREN

%token QUESTION_MARK

%token <std::string> ID_TOKEN
%token <int> INT_TOKEN

%token END 0 "end of file"

%type <std::unique_ptr<BlockNode>> block
			
%type <std::unique_ptr<StmtNode>> stmt
%type <std::unique_ptr<IfStmtNode>> if
%type <std::unique_ptr<WhileStmtNode>> while
%type <std::unique_ptr<PrintStmtNode>> print
%type <std::unique_ptr<AssignmentStmtNode>> assignment

%type <std::unique_ptr<ExprNode>> expr
%type <std::unique_ptr<EqNode>> eq
%type <std::unique_ptr<LtNode>> lt
%type <std::unique_ptr<GtNode>> gt
%type <std::unique_ptr<LteNode>> lte
%type <std::unique_ptr<GteNode>> gte

%type <std::unique_ptr<ArithNode>> arith
%type <std::unique_ptr<AddNode>> add
%type <std::unique_ptr<SubNode>> sub
			
%type <std::unique_ptr<TermNode>> term
%type <std::unique_ptr<MulNode>> mul
%type <std::unique_ptr<DivNode>> div

%type <std::unique_ptr<AtomNode>> atom
%type <std::unique_ptr<ParenExprNode>> paren_expr
%type <std::unique_ptr<QuestionMarkNode>> question_mark
%type <std::unique_ptr<IdNode>> id
%type <std::unique_ptr<IntNode>> number

												
%parse-param { std::unique_ptr<ASTNode>* root }

%%

program:
  block {
    *root = std::move($1);
  };

block:
  /* empty */ { 
    $$ = nullptr;
  }
  | stmt {
      $$ = std::make_unique<BlockNode>(std::move($1), nullptr);
  }
  | block stmt {
      $$ = std::make_unique<BlockNode>(std::move($1), std::move($2));
  };

stmt:
  if { $$ = std::move($1); }
  | while { $$ = std::move($1); }
  | print { $$ = std::move($1); }
  | assignment { $$ = std::move($1); };

if:
  IF LPAREN expr RPAREN LBRACE block RBRACE {
    $$ = std::make_unique<IfStmtNode>(std::move($3), std::move($6));
  };
while:
  WHILE LPAREN expr RPAREN LBRACE block RBRACE {
    $$ = std::make_unique<WhileStmtNode>(std::move($3), std::move($6));
  };
print:
  PRINT expr SEMICOLON {
    $$ = std::make_unique<PrintStmtNode>(std::move($2));
  };
assignment:	
  id ASSIGN expr SEMICOLON {
    $$ = std::make_unique<AssignmentStmtNode>(std::move($1), std::move($3));
  };

expr:
  arith { $$ = std::move($1); }
  | eq { $$ = std::move($1); }
  | lt { $$ = std::move($1); }
  | gt { $$ = std::move($1); }
  | lte { $$ = std::move($1); }
  | gte { $$ = std::move($1); };

eq:		
  expr EQ arith {
    $$ = std::make_unique<EqNode>(std::move($1), std::move($3));
  };
lt:		
  expr LT arith {
    $$ = std::make_unique<LtNode>(std::move($1), std::move($3));
  };
gt:		
  expr GT arith {
    $$ = std::make_unique<GtNode>(std::move($1), std::move($3));
  };
lte:		
  expr LTE arith {
    $$ = std::make_unique<LteNode>(std::move($1), std::move($3));
  };
gte:		
  expr GTE arith {
    $$ = std::make_unique<GteNode>(std::move($1), std::move($3));
  };
arith:
  add { $$ = std::move($1); }
  | sub { $$ = std::move($1); }
  | term { $$ = std::move($1); };
add:
  arith PLUS term {
    $$ = std::make_unique<AddNode>(std::move($1), std::move($3));
  };
sub:
  arith MINUS term {
    $$ = std::make_unique<SubNode>(std::move($1), std::move($3));
  };
term:
  mul { $$ = std::move($1);}
  | div { $$ = std::move($1); }
  | atom { $$ = std::move($1); };
mul:		
  term STAR atom {
    $$ = std::make_unique<MulNode>(std::move($1), std::move($3));
  };
div:
  term SLASH atom {
      $$ = std::make_unique<DivNode>(std::move($1), std::move($3));
  };
atom:
  paren_expr { $$ = std::move($1); }
  | question_mark { $$ = std::move($1); }
  | number { $$ = std::move($1); }
  | id { $$ = std::move($1); }
paren_expr:
  LPAREN expr RPAREN {
      $$ = std::make_unique<ParenExprNode>(std::move($2));
  };
question_mark:
  QUESTION_MARK {
    $$ = std::make_unique<QuestionMarkNode>();
  };
id:
  ID_TOKEN {
    $$ = std::make_unique<IdNode>($1);
  };
number:
  INT_TOKEN {
    $$ = std::make_unique<IntNode>($1);
  };
%%

void YY::Parser::error(const std::string& msg) {
    std::cerr << "Parser error: " << msg << std::endl;
}
