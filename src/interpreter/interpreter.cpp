module;

#include <memory>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <exception>
#include <variant>

#include "AST.hpp"

module interpreter;

import exceptions;

namespace interpreter {

IRV InterpreterVisitor::Eval(
  const ASTNode* node
) {
  assert(node);

  node->Accept(*this);
  return val_;
}

void InterpreterVisitor::VisitQuestionMarkNode(
  const QuestionMarkNode* node
) {
  assert(node);
  clearerr(stdin);
  std::cin.exceptions(std::ios::failbit | std::ios::badbit);

  int val = 0;
  std::cin >> val;

  val_ = val;
}

void InterpreterVisitor::VisitIdNode(
  const IdNode* node
) {
  assert(node);

  val_ = GetVarValue(node->GetVarName());
}

void InterpreterVisitor::VisitIntNode(
  const IntNode* node
) {
  assert(node);

  val_ = node->GetValue();
}

void InterpreterVisitor::VisitParenExprNode(
  const ParenExprNode* node
) {
  assert(node);

  const ExprNode* expr_node = node->GetExprPtr();
  assert(expr_node);

  expr_node->Accept(*this);
}

void InterpreterVisitor::VisitMulNode(
  const MulNode* node
) {
  assert(node);

  const TermNode* left = node->GetTermPtr();
  const AtomNode* right = node->GetAtomPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = left_res * right_res;
}

void InterpreterVisitor::VisitDivNode(
  const DivNode* node
) {
  assert(node);

  const TermNode* left = node->GetTermPtr();
  const AtomNode* right = node->GetAtomPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  if (right == 0) {
    throw exception::Exception{
      "Division by zero!",
      exception::ErrorCode::kZeroDiv};
  }

  val_ = left_res / right_res;
}

void InterpreterVisitor::VisitAddNode(
  const AddNode* node
) {
  assert(node);

  const ArithNode* left = node->GetArithPtr();
  const TermNode* right = node->GetTermPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = left_res + right_res;
}

void InterpreterVisitor::VisitSubNode(
  const SubNode* node
) {
  assert(node);

  const ArithNode* left = node->GetArithPtr();
  const TermNode* right = node->GetTermPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = left_res - right_res;
}

void InterpreterVisitor::VisitEqNode(
  const EqNode* node
) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<bool>(left_res == right_res);
}

void InterpreterVisitor::VisitLtNode(
  const LtNode* node
) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<bool>(left_res < right_res);
}

void InterpreterVisitor::VisitGtNode(
  const GtNode* node
) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<bool>(left_res > right_res);
}

void InterpreterVisitor::VisitLteNode(
  const LteNode* node
) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<bool>(left_res <= right_res);
}

void InterpreterVisitor::VisitGteNode(
  const GteNode* node
) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<bool>(left_res >= right_res);
}

void InterpreterVisitor::VisitBlockNode(
  const BlockNode* node
) {
  assert(node);

  const ASTNode* left = node->GetASTPtr();
  const StmtNode* right = node->GetStmtPtr();

  assert(left);

  left->Accept(*this);

  if (right) {
    right->Accept(*this);
  }
}

void InterpreterVisitor::VisitIfStmtNode(
  const IfStmtNode* node
) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const BlockNode* right = node->GetBlockPtr();

  bool left_res = std::get<bool>(Eval(left));

  if (right && left_res) {
    right->Accept(*this);
  }
}

void InterpreterVisitor::VisitWhileStmtNode(
  const WhileStmtNode* node
) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const BlockNode* right = node->GetBlockPtr();

  bool left_res;
  while (right && (left_res = std::get<bool>(Eval(left)))) {
    right->Accept(*this);
  }
}

void InterpreterVisitor::VisitPrintStmtNode(
  const PrintStmtNode* node
) {
  assert(node);

  const ExprNode* expr = node->GetExprPtr();
  assert(expr);

  expr->Accept(*this);

  auto lambda = [](const auto& arg) {
    std::cout << arg;
  };

  std::visit(lambda, val_);
}

void InterpreterVisitor::VisitAssignmentStmtNode(
  const AssignmentStmtNode* node
) {
  assert(node);

  const IdNode* left = node->GetIdPtr();
  const ExprNode* right = node->GetExprPtr();

  assert(left && right);

  int value = std::get<int>(Eval(right));

  SetVarValue(left->GetVarName(), value);
}
} // interpreter

