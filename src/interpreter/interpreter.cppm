module;

#include <variant>
#include <string>

#include "AST.hpp"
#include "visitor.hpp"

export module interpreter;

import environment;

namespace interpreter {

/**
 * Specific visitor (for interpreter)
 * IRV - Interpreter Return Value
 */
using IRV = std::variant<int, bool>;
export class InterpreterVisitor: public visitor::Visitor {
 public:
  InterpreterVisitor() = default;

  IRV Eval(const ASTNode* node);

  int GetVarValue(const std::string& var) {
    return environment[var];
  }

  void SetVarValue(const std::string& var, int val) {
    environment[var] = val;
  }

  void VisitQuestionMarkNode(
    const QuestionMarkNode* node
  ) override;

  void VisitIdNode(
    const IdNode* node
  ) override;

  void VisitIntNode(
    const IntNode* node
  ) override;

  void VisitParenExprNode(
    const ParenExprNode* node
  ) override;

  void VisitMulNode(
    const MulNode* node
  ) override;

  void VisitDivNode(
    const DivNode* node
  ) override;

  void VisitAddNode(
    const AddNode* node
  ) override;

  void VisitSubNode(
    const SubNode* node
  ) override;

  void VisitEqNode(
    const EqNode* node
  ) override;

  void VisitLtNode(
    const LtNode* node
  ) override;

  void VisitGtNode(
    const GtNode* node
  ) override;

  void VisitLteNode(
    const LteNode* node
  ) override;

  void VisitGteNode(
    const GteNode* node
  ) override;

  void VisitBlockNode(
    const BlockNode* node
  ) override;

  void VisitIfStmtNode(
    const IfStmtNode* node
  ) override;

  void VisitWhileStmtNode(
    const WhileStmtNode* node
  ) override;

  void VisitPrintStmtNode(
    const PrintStmtNode* node
  ) override;

  void VisitAssignmentStmtNode(
    const AssignmentStmtNode* node
  ) override;
 private:
  IRV val_;

  env::Environment environment;
};

export void Execute(std::unique_ptr<ASTNode> node,
             visitor::Visitor& visitor) {

  node->Accept(visitor);
}

} // interpreter
