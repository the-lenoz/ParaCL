module;

#include "AST.hpp"
#include "lexer.hpp"
#include "parser.tab.hh"

export module parser;

export namespace YY {
    using YY::ParaLexer;
    using YY::Parser;
}

