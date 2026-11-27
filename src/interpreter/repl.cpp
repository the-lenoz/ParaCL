module;

#include <fmt/color.h>
#include <string>
#include <sstream>
#include <iostream>

module repl;

namespace {

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

/**
  Priority System:
    1. MachineState::kDead
    2. MachineState::kUnfinished
    3. MachineState::kIntermediate
  (the higher the enum class (MachineState) number, the higher the priority)

  a state with a higher priority changes it
*/
PrioritySystem ComparePriority(MachineState current, MachineState last) {
  int compare_res = static_cast<int>(current) - static_cast<int>(last);

  return (compare_res > 0 ? PrioritySystem::kHigher : PrioritySystem::kLower);
}

void ReplFsm::Greet() {
  active_state_ = &ReplFsm::Invite;

  if (repl_flags_.quiet_output) {
    return ;
  }

  auto command_style = (repl_flags_.no_colors ?
                        fmt::text_style() :
                        fmt::fg(fmt::color::yellow) | fmt::emphasis::bold);

  auto lang_style = (repl_flags_.no_colors ?
                    fmt::text_style() :
                    fmt::fg(fmt::color::green));

  auto greeting_style = (repl_flags_.no_colors ?
                        fmt::text_style() :
                        fmt::fg(fmt::color::gray));

  fmt::print(lang_style, "ParaCL\n");
  fmt::print(greeting_style, "Type \"{}\" {} \"{}\" {}",
            fmt::styled("--help", command_style),
            fmt::styled("for more information, or", greeting_style),
            fmt::styled("Ctrl+D", command_style),
            fmt::styled(" to quit.\n", greeting_style));
}

void ReplFsm::Invite() {
  PrintInvitation(InviteLineType::kArrows);

  active_state_ = &ReplFsm::Parse;
}

void ReplFsm::ContinueOperation() {
  PrintInvitation(InviteLineType::kDots);

  active_state_ = &ReplFsm::Parse;
}

void ReplFsm::Parse() {
  std::istringstream in = CreateStream(command_);
  YY::Driver drv{in};
  MachineState machine_state = ParseCommand(drv);
  root_ = drv.TakeAST();

  switch (machine_state) {
    case MachineState::kIntermediate:
      command_.clear();
      active_state_ = &ReplFsm::ExecuteCommand;
      break;
    case MachineState::kUnfinished:
      active_state_ = &ReplFsm::ContinueOperation;
      break;
    case MachineState::kDead:
      command_.clear();
      active_state_ = &ReplFsm::Invite;
      break;
    default:
      break;
  }
}

void ReplFsm::ExecuteCommand() try {
  if (root_) {
    root_->Accept(visitor);
  }

  active_state_ = &ReplFsm::Invite;
} catch (const exception::ParaCLException& e) {
  std::cout << e.what() << '\n';
  e.Log();
  active_state_ = &ReplFsm::Invite;
}

void ReplFsm::PrintInvitation(InviteLineType invite_line_type) {
  auto invitation_style = (repl_flags_.no_colors ?
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

MachineState ReplFsm::ParseCommand(YY::Driver& drv) {

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
} // namespace interpreter


