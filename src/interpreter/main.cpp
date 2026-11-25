#include <iostream>
#include <memory>
#include <utility>

#include "AST.hpp"

import parser;
import interpreter;
import exceptions;

int main() try {
  YY::Driver drv{std::cin};

  drv.Parse();

  if (drv.HasErrors()) {
    for (auto &errcode : drv.GetErrorCodes()) {
      for (auto &err_info : drv.GetErrorsByCode(errcode)) {
        std::cerr << err_info.message << std::endl;
      }
    }
    return -1;
  }

  std::unique_ptr<ASTNode> root = drv.TakeAST();

  interpreter::InterpreterVisitor visitor{};

  interpreter::Execute(std::move(root), visitor);

} catch (const exception::ParaCLException& e) {
  std::cout << e.what() << '\n';
  e.Log();
  return static_cast<int>(e.GetErrorCode());
}
