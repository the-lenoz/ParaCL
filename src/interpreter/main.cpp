#include <iostream>

#include "AST.hpp"

import parser;
import interpreter;
import exceptions;
import dumper;

int main() try {
  YY::Driver drv{std::cin};

  drv.Parse();

  std::unique_ptr<ASTNode> root = drv.TakeAST();

  interpreter::InterpreterVisitor interpreter{};

  root->Accept(interpreter);
  dumper::GraphvizDump(std::cout, root.get());
} catch(const exception::ParaCLException& e) {
  std::cout << e.what() << '\n';
  e.Log();
  return static_cast<int>(e.GetErrorCode());
}
