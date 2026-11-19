module;

#include <fmt/color.h>
#include <iostream>
#include <sstream>
#include <variant>

#include "AST.hpp"

export module repl;

import parser;
import interpreter;
import exceptions;

namespace interpreter {

export struct ReplFlags {
  bool quiet_repl = false;
  bool no_colors = false;
};

enum class ReadStatus {
  kEOF       = 0,
  kEmptyLine = 1
};

using ReadResult = std::variant<std::istringstream, ReadStatus>;
} // namespace interpreter

namespace {

void PrintGreeting(const interpreter::ReplFlags& repl_flags) {

  auto command_style = (repl_flags.no_colors ?
                        fmt::text_style() :
                        fmt::fg(fmt::color::yellow) | fmt::emphasis::bold);

  auto lang_style = (repl_flags.no_colors ?
                     fmt::text_style() :
                     fmt::fg(fmt::color::green));

  auto greeting_style = (repl_flags.no_colors ?
                         fmt::text_style() :
                         fmt::fg(fmt::color::gray));

  fmt::print(lang_style, "ParaCL\n");
  fmt::print(greeting_style, "Type \"{}\" {} \"{}\" {}",
             fmt::styled("--help", command_style),
             fmt::styled("for more information, or", greeting_style),
             fmt::styled("Ctrl+D", command_style),
             fmt::styled(" to quit.\n", greeting_style));
}

void PrintInvitation(const interpreter::ReplFlags& repl_flags) {

  auto invitation_style = (repl_flags.no_colors ?
                           fmt::text_style() :
                           fmt::fg(fmt::color::purple) | fmt::emphasis::bold);

  fmt::print(invitation_style, "\n>>> ");
}

interpreter::ReadResult ReadLine(std::string& command, int& next_symbol) {

  if ((next_symbol = std::cin.peek()) == EOF) {
    return interpreter::ReadStatus::kEOF;
  } else if (next_symbol == '\n') {
    std::cin.get();                        // clean stream (after std::cin)
  }

  std::getline(std::cin, command);
  if (command.empty()) {
    return interpreter::ReadStatus::kEmptyLine;
  }

  std::istringstream in{command};

  return in;
}
} // namespace

namespace interpreter {

export void REPL(const ReplFlags& repl_flags) {

  if (!repl_flags.quiet_repl) {
    PrintGreeting(repl_flags);
  }

  interpreter::InterpreterVisitor visitor{};
  std::string command;
  int next_symbol = 0;
  ReadStatus* read_status;

  [&] {
    while (std::cin) {
      PrintInvitation(repl_flags);

      ReadResult read_result = ReadLine(command, next_symbol);
      if ((read_status = std::get_if<ReadStatus>(&read_result))) {
        switch (*read_status) {
          case ReadStatus::kEOF:       return ;
          case ReadStatus::kEmptyLine: continue;
          default:                     break;
        }
      }

      std::istringstream& in = *(std::get_if<std::istringstream>(&read_result));
      std::unique_ptr<ASTNode> root;
      auto lexer = YY::ParaLexer(in, std::cout);
      YY::Parser parser(lexer, &root);
      parser.parse();

      if (root) {
        root->Accept(visitor);
      }
    }
  }();  // execute lambda in place
}
} // interpreter


