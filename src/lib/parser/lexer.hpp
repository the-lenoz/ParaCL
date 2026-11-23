#pragma once

#include <istream>
#include <ostream>

#include "parser.tab.hh"
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
namespace YY {
  
class ParaLexer : public yyFlexLexer {
 public:
  using yyFlexLexer::yylex;
  explicit ParaLexer(std::istream& in, std::ostream& out)
      : yyFlexLexer(in, out) {}

  Parser::symbol_type next_token();
};
}  // namespace YY