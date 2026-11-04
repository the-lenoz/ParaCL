#include <utility>

#include "AST.hpp"
import parser;

int main() {
  std::unique_ptr<ASTNode> root;
  YY::Parser parser(&root);
  parser.parse();
  root->print();
  return 0;
}
