module;

#include <cassert>
#include <cstdio>
#include <iostream>
#include <variant>
#include <print>

#include "AST.hpp"

module interpreter;

import exceptions;

namespace interpreter {

IRV InterpreterVisitor::Eval(const ASTNode* node) {
  assert(node);

  node->Accept(*this);
  return val_;
}

void InterpreterVisitor::VisitQuestionMarkNode(const QuestionMarkNode* node) {
  assert(node);
  std::cin.exceptions(std::ios::badbit);

  int val = 0;

  try {
    std::cin >> val;
    int next_symbol = std::cin.get();    // clean stream (after std::cin, delete '\n')
    if (next_symbol != EOF && next_symbol != '\n') {
      throw exception::ParaCLException{"Incorrect input format!",
                                     exception::ErrorCode::kInputData};
    }
  } catch (const std::ios_base::failure& e) {
    std::println(std::cerr, "{}, code: {}",
                  e.what(), e.code().value());
    std::cin.clear();
  }
  val_ = val;
}

void InterpreterVisitor::VisitIdNode(const IdNode* node) {
  assert(node);

  val_ = GetVarValue(node->GetVarName());
}

void InterpreterVisitor::VisitIntNode(const IntNode* node) {
  assert(node);

  val_ = node->GetValue();
}

void InterpreterVisitor::VisitParenExprNode(const ParenExprNode* node) {
  assert(node);

  const ExprNode* expr_node = node->GetExprPtr();
  assert(expr_node);

  expr_node->Accept(*this);
}

void InterpreterVisitor::VisitUnaryMinusNode(const UnaryMinusNode* node) {
  assert(node);

  const ExprNode* expr_node = node->GetAtomPtr();
  assert(expr_node);

  expr_node->Accept(*this);

  val_ = -std::get<int>(val_);
}

void InterpreterVisitor::VisitUnaryPlusNode(const UnaryPlusNode* node) {
  assert(node);

  const ExprNode* expr_node = node->GetAtomPtr();
  assert(expr_node);

  expr_node->Accept(*this);

  // Do nothing!
}

void InterpreterVisitor::VisitMulNode(const MulNode* node) {
  assert(node);

  const TermNode* left = node->GetTermPtr();
  const AtomNode* right = node->GetAtomPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = left_res * right_res;
}

void InterpreterVisitor::VisitDivNode(const DivNode* node) {
  assert(node);

  const TermNode* left = node->GetTermPtr();
  const AtomNode* right = node->GetAtomPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  if (right_res == 0) {
    throw exception::ParaCLException{"Division by zero!",
                                     exception::ErrorCode::kZeroDiv};
  }

  val_ = left_res / right_res;
}

void InterpreterVisitor::VisitAddNode(const AddNode* node) {
  assert(node);

  const ArithNode* left = node->GetArithPtr();
  const TermNode* right = node->GetTermPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = left_res + right_res;
}

void InterpreterVisitor::VisitSubNode(const SubNode* node) {
  assert(node);

  const ArithNode* left = node->GetArithPtr();
  const TermNode* right = node->GetTermPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = left_res - right_res;
}

void InterpreterVisitor::VisitEqNode(const EqNode* node) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<int>(left_res == right_res);
}

void InterpreterVisitor::VisitNeqNode(const NeqNode* node) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<int>(left_res != right_res);
}

void InterpreterVisitor::VisitLtNode(const LtNode* node) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<int>(left_res < right_res);
}

void InterpreterVisitor::VisitGtNode(const GtNode* node) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<int>(left_res > right_res);
}

void InterpreterVisitor::VisitLteNode(const LteNode* node) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<int>(left_res <= right_res);
}

void InterpreterVisitor::VisitGteNode(const GteNode* node) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const ArithNode* right = node->GetArithPtr();

  assert(left && right);

  int left_res = std::get<int>(Eval(left));
  int right_res = std::get<int>(Eval(right));

  val_ = static_cast<int>(left_res >= right_res);
}

void InterpreterVisitor::VisitBlockNode(const BlockNode* node) {
  assert(node);

  const BlockNode* left = node->GetBlockPtr();
  const StmtNode* right = node->GetStmtPtr();

  assert(right);

  if (left) {
    left->Accept(*this);
  }
  right->Accept(*this);
}

void InterpreterVisitor::VisitIfStmtNode(const IfStmtNode* node) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const BlockNode* right = node->GetBlockPtr();

  int left_res = std::get<int>(Eval(left));

  if (right && left_res != 0) {
    right->Accept(*this);
  }
}

void InterpreterVisitor::VisitWhileStmtNode(const WhileStmtNode* node) {
  assert(node);

  const ExprNode* left = node->GetExprPtr();
  const BlockNode* right = node->GetBlockPtr();

  bool left_res;
  while (right && (left_res = std::get<int>(Eval(left))) != 0) {
    right->Accept(*this);
  }
}

void InterpreterVisitor::VisitPrintStmtNode(const PrintStmtNode* node) {
  assert(node);

  const ExprNode* expr = node->GetExprPtr();
  assert(expr);

  expr->Accept(*this);

  auto lambda = [](const auto& arg) { std::print("{}", arg); };

  std::visit(lambda, val_);
}

void InterpreterVisitor::VisitAssignmentStmtNode(
    const AssignmentStmtNode* node) {
  assert(node);

  const IdNode* left = node->GetIdPtr();
  const ExprNode* right = node->GetExprPtr();

  assert(left && right);

  int value = std::get<int>(Eval(right));

  SetVarValue(left->GetVarName(), value);
}
}  // namespace interpreter
