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
  bool quiet_output = false;
  bool no_colors = false;
};

enum class MachineState {
  kInit         = 0,
  kIntermediate = 1,
  kUnfinished   = 2,
  kDead         = 3,
  kFinal        = 4
};

enum class PrioritySystem {
  kHigher = 0,
  kLower  = 1
};

} // namespace interpreter

namespace {

enum class InviteLineType {
  kArrows,
  kDots
};

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

void PrintInvitation(const interpreter::ReplFlags& repl_flags,
                     InviteLineType invite_line_type) {

  auto invitation_style = (repl_flags.no_colors ?
                           fmt::text_style() :
                           fmt::fg(fmt::color::purple) | fmt::emphasis::bold);

  switch (invite_line_type) {
    case InviteLineType::kArrows:
      fmt::print(invitation_style, "\n>>> ");
      break;
    case InviteLineType::kDots:
      fmt::print(invitation_style, "\n... ");
      break;
    default:
      std::unreachable();
  }
}

std::istringstream CreateStream(std::string& command) {

  std::string line;

  std::getline(std::cin, line);

  command += line;
  command += '\n';

  std::istringstream input{command};

  return input;
}

void DumpError(const YY::Driver& drv, YY::ParseErrorCode errcode) {

  for (auto& err : drv.GetErrorsByCode(errcode))
    std::cerr << err.message << std::endl;
}
} // namespace

namespace interpreter {

PrioritySystem ComparePriority(MachineState current, MachineState last) {
  int compare_res = static_cast<int>(current) - static_cast<int>(last);

  return (compare_res > 0 ? PrioritySystem::kHigher : PrioritySystem::kLower);
}

/**
  Priority System:
    1. MachineState::kDead
    2. MachineState::kUnfinished
    3. MachineState::kIntermediate
  (the higher the enum class (MachineState) number, the higher the priority)

  a state with a higher priority changes it
*/
interpreter::MachineState ParseCommand(YY::Driver& drv) {

  MachineState machine_state = MachineState::kIntermediate;

  drv.Parse();

  if (drv.HasErrors()) {
    for (auto& errcode : drv.GetErrorCodes()) {
      if (errcode == YY::ParseErrorCode::UnexpectedEOF &&
          ComparePriority(MachineState::kUnfinished, machine_state) == PrioritySystem::kHigher) {
          machine_state = MachineState::kUnfinished;
      } else {
        DumpError(drv, errcode);
        machine_state = MachineState::kDead;
      }
    }
  }

  return machine_state;
}

export int REPL(const ReplFlags& repl_flags) {

  if (!repl_flags.quiet_output) {
    PrintGreeting(repl_flags);
  }

  interpreter::InterpreterVisitor visitor{};
  std::string command;
  InviteLineType invite_line_type = InviteLineType::kArrows;

  while (std::cin) {
    PrintInvitation(repl_flags, invite_line_type);

    if (std::cin.peek() == EOF) {
      break;
    }

    std::istringstream in = CreateStream(command);
    YY::Driver drv{in};
    MachineState machine_state = ParseCommand(drv);

    switch (machine_state) {
      case MachineState::kIntermediate:
        command.clear();
        invite_line_type = InviteLineType::kArrows;
        break;
      case MachineState::kUnfinished:
        invite_line_type = InviteLineType::kDots;
        continue;
      case MachineState::kDead:
        command.clear();
        invite_line_type =InviteLineType::kArrows;
        continue;
      default:
        break;
    }

    std::unique_ptr<ASTNode> root = drv.TakeAST();
    if (root) {
      root->Accept(visitor);
    }
  }
  return 0;
}
} // interpreter


