module;

#include <string>
#include <fstream>
#include <iostream>

#include "AST.hpp"

export module execute_file;

import parser;
import interpreter;
import file_management;
import dumper;

namespace interpreter {

export int ExecuteFile(const std::string& input_path) {

  std::ifstream input_stream = file_manager::FileManager::OpenStream(input_path);

  YY::Driver drv{input_stream};

  drv.Parse();

  if (drv.HasErrors()) {
    for (auto& errcode : drv.GetErrorCodes())
      for (auto& err : drv.GetErrorsByCode(errcode))
        std::cerr << err.message << std::endl;
    return -1;
  }

  std::unique_ptr<ASTNode> root = drv.TakeAST();

  interpreter::InterpreterVisitor interpreter{};

  root->Accept(interpreter);

  dumper::GraphvizDump(std::cout, root.get());
  return 0;
}
} // namespace interpreter
