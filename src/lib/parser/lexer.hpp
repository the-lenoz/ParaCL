#pragma once

#include "location.hh"
#include "parser.tab.hh"
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
namespace YY {
  
class ParaLexer : public yyFlexLexer {
  Driver &drv_;
 public:
  location loc;
  using yyFlexLexer::yylex;
  explicit ParaLexer(Driver &drv);

  Parser::symbol_type next_token();
};}  // namespace YY