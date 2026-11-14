#include <utility>

#include "AST.hpp"

import parser;
import interpreter;
import exceptions;

int main() try {
  std::unique_ptr<ASTNode> root;
  YY::Parser parser(&root);
  parser.parse();
  //root->print();

  interpreter::InterpreterVisitor visitor{};

  interpreter::Execute(std::move(root), visitor);

} catch(const exception::Exception& e) {
  std::cout << e.what() << '\n';
  e.Log();
}
