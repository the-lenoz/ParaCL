#include <CLI/CLI.hpp>
#include <utility>
#include <fstream>
#include <string>
#include <cstddef>
#include <iostream>

import interpreter;
import execute_file;
import exceptions;
import repl;

int main(int argc, char** argv) try {

  std::string input_path;
  interpreter::ReplFlags repl_flags{};

  CLI::App app("Interpreter ParaCL");
  argv = app.ensure_utf8(argv);
  CLI::Option* input_file_opt = app.add_option("-f,--input_file,input_file", input_path,
                                                  "The input code file");
  app.add_flag("-q,--quiet", repl_flags.quiet_repl, "Don't write a greeting in the repl");
  app.add_flag("-c,--no-colors", repl_flags.no_colors, "Don't use color output");
  CLI11_PARSE(app, argc, argv);

  size_t input_file_numbers = input_file_opt->count();

  if (input_file_numbers > 1) {
    throw exception::ParaCLException{"You can choose only one input file!",
                                      exception::ErrorCode::kInputFlags};
  } else if (input_file_numbers == 1) {
    interpreter::ExecuteFile(input_path);
  } else {
    interpreter::REPL(repl_flags);
  }

} catch(const exception::ParaCLException& e) {
  std::cout << e.what() << '\n';
  e.Log();
  return static_cast<int>(e.GetErrorCode());
}
