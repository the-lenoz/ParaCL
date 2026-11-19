module;

#include <string>
#include <fstream>
#include <iostream>

#include "AST.hpp"

export module execute_file;

import parser;
import interpreter;
import file_management;

namespace interpreter {

export void ExecuteFile(const std::string& input_path) {

  std::ifstream input_stream = file_manager::FileManager::OpenStream(input_path);

  std::unique_ptr<ASTNode> root;

  auto lexer = YY::ParaLexer(input_stream, std::cout);
  YY::Parser parser(lexer, &root);
  parser.parse();

  interpreter::InterpreterVisitor visitor{};
  root->Accept(visitor);
}
} // namespace interpreter
