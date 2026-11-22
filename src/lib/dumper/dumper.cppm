module;

#include <ostream>

#include "AST.hpp"

export module dumper;

export namespace dumper {

void OneLineDump(std::ostream& out, const ASTNode* ast);
void GraphvizDump(std::ostream& out, const ASTNode* ast);

}  // namespace dumper
