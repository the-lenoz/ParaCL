#include <fstream>
#include <utility>

#include "AST.hpp"
#include <iostream>

import parser;
import interpreter;
import exceptions;
import dumper;

int main() try {
  std::unique_ptr<ASTNode> root;

  std::ifstream test{"samples/test01.lang"};
  auto lexer = YY::ParaLexer(test, std::cout);
  YY::Parser parser(lexer, &root);
  parser.parse();


  interpreter::InterpreterVisitor visitor{};

  dumper::OneLineDumper dumper;
  root->Accept(dumper);
  // root->Accept();
} catch(const exception::ParaCLException& e) {
  std::cout << e.what() << '\n';
  e.Log();
  return static_cast<int>(e.GetErrorCode());
}
