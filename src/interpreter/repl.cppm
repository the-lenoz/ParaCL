module;

#include <iostream>
#include <sstream>
#include <string>

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
  kIntermediate,
  kUnfinished,
  kDead
};

enum class PrioritySystem {
  kHigher,
  kLower
};

enum class InviteLineType {
  kArrows,
  kDots
};

class ReplFsm {
 public:
  using State = void (ReplFsm::*)();

  ReplFsm(const ReplFlags& repl_flags)
    : active_state_(&ReplFsm::Greet), repl_flags_(repl_flags) {}

  void ExecuteState() {
    if (active_state_) {
      (this->*active_state_)();
    }
  }

 private:

  State active_state_ = nullptr;
  std::string command_;
  ReplFlags repl_flags_;
  std::unique_ptr<ASTNode> root_ = nullptr;
  interpreter::InterpreterVisitor visitor;

  void Greet();

  void Invite();

  void ContinueOperation();

  void Parse();

  void ExecuteCommand();

  void PrintInvitation(InviteLineType invite_line_type);

  MachineState ParseCommand(YY::Driver& drv);
};

export int REPL(const ReplFlags& repl_flags) {

  ReplFsm repl_fsm{repl_flags};
  repl_fsm.ExecuteState();

  while (std::cin) {
    repl_fsm.ExecuteState();
  }
  return 0;
}
} // interpreter


