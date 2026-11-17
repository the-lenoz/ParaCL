#include <utility>

#include "AST.hpp"
#include <iostream>

import parser;
import interpreter;
import exceptions;

int main() try {
  std::unique_ptr<ASTNode> root;
  YY::Parser parser(&root);
  parser.parse();


  interpreter::InterpreterVisitor visitor{};

  interpreter::Execute(std::move(root), visitor);

} catch(const exception::ParaCLException& e) {
  std::cout << e.what() << '\n';
  e.Log();
  return static_cast<int>(e.GetErrorCode());
}
