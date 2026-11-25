module;

#include <cassert>
#include <ostream>
#include <print>

#include "AST.hpp"
#include "visitor.hpp"

module dumper;

namespace dumper {

class OneLineDumper : public visitor::Visitor {
  std::ostream& out_;
  size_t indent_ = 0;

  void VisitQuestionMarkNode(
      [[maybe_unused]] const QuestionMarkNode* node) override {
    assert(node);

    std::println(out_, "{:{}}", "?", indent_);
  }

  void VisitIdNode(const IdNode* node) override {
    assert(node);

    std::println(out_, "{:{}}IdNode{{{}}}", "", indent_, node->GetVarName());
  }

  void VisitIntNode(const IntNode* node) override {
    assert(node);

    std::println(out_, "{:{}}IntNode{{{}}}", "", indent_, node->GetValue());
  }

  void VisitParenExprNode(const ParenExprNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();

    std::println(out_, "{:{}}ParenExprNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);

    indent_ -= 2;
  }

  void VisitUnaryMinusNode(const UnaryMinusNode* node) override {
    assert(node);

    const auto* atom = node->GetAtomPtr();

    std::println(out_, "{:{}}UnaryMinusNode:", "", indent_);
    indent_ += 2;

    if (atom) atom->Accept(*this);

    indent_ -= 2;
  }

  void VisitUnaryPlusNode(const UnaryPlusNode* node) override {
    assert(node);

    const auto* atom = node->GetAtomPtr();

    std::println(out_, "{:{}}UnaryPlusNode:", "", indent_);
    indent_ += 2;

    if (atom) atom->Accept(*this);

    indent_ -= 2;
  }

  void VisitMulNode(const MulNode* node) override {
    assert(node);

    const auto* term = node->GetTermPtr();
    const auto* atom = node->GetAtomPtr();

    std::println(out_, "{:{}}MulNode:", "", indent_);
    indent_ += 2;

    if (term) term->Accept(*this);
    if (atom) atom->Accept(*this);

    indent_ -= 2;
  }

  void VisitDivNode(const DivNode* node) override {
    assert(node);

    const auto* term = node->GetTermPtr();
    const auto* atom = node->GetAtomPtr();

    std::println(out_, "{:{}}DivNode:", "", indent_);
    indent_ += 2;

    if (term) term->Accept(*this);
    if (atom) atom->Accept(*this);

    indent_ -= 2;
  }

  void VisitAddNode(const AddNode* node) override {
    assert(node);

    const auto* arith = node->GetArithPtr();
    const auto* term = node->GetTermPtr();

    std::println(out_, "{:{}}AddNode:", "", indent_);
    indent_ += 2;

    if (arith) arith->Accept(*this);
    if (term) term->Accept(*this);

    indent_ -= 2;
  }

  void VisitSubNode(const SubNode* node) override {
    assert(node);

    const auto* arith = node->GetArithPtr();
    const auto* term = node->GetTermPtr();

    std::println(out_, "{:{}}SubNode:", "", indent_);
    indent_ += 2;

    if (arith) arith->Accept(*this);
    if (term) term->Accept(*this);

    indent_ -= 2;
  }

  void VisitEqNode(const EqNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();
    const auto* arith = node->GetArithPtr();

    std::println(out_, "{:{}}EqNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);
    if (arith) arith->Accept(*this);

    indent_ -= 2;
  }

  void VisitNeqNode(const NeqNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();
    const auto* arith = node->GetArithPtr();

    std::println(out_, "{:{}}NeqNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);
    if (arith) arith->Accept(*this);

    indent_ -= 2;
  }

  void VisitLtNode(const LtNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();
    const auto* arith = node->GetArithPtr();

    std::println(out_, "{:{}}LtNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);
    if (arith) arith->Accept(*this);

    indent_ -= 2;
  }

  void VisitGtNode(const GtNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();
    const auto* arith = node->GetArithPtr();

    std::println(out_, "{:{}}GtNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);
    if (arith) arith->Accept(*this);

    indent_ -= 2;
  }

  void VisitLteNode(const LteNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();
    const auto* arith = node->GetArithPtr();

    std::println(out_, "{:{}}LteNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);
    if (arith) arith->Accept(*this);

    indent_ -= 2;
  }

  void VisitGteNode(const GteNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();
    const auto* arith = node->GetArithPtr();

    std::println(out_, "{:{}}GteNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);
    if (arith) arith->Accept(*this);

    indent_ -= 2;
  }

  void VisitBlockNode(const BlockNode* node) override {
    assert(node);

    const auto* block = node->GetBlockPtr();
    const auto* stmt = node->GetStmtPtr();

    std::println(out_, "{:{}}BlockNode:", "", indent_);
    indent_ += 2;

    if (block) block->Accept(*this);
    if (stmt) stmt->Accept(*this);

    indent_ -= 2;
  }

  void VisitIfStmtNode(const IfStmtNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();
    const auto* block = node->GetBlockPtr();

    std::println(out_, "{:{}}IfStmtNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);
    if (block) block->Accept(*this);

    indent_ -= 2;
  }

  void VisitWhileStmtNode(const WhileStmtNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();
    const auto* block = node->GetBlockPtr();

    std::println(out_, "{:{}}WhileStmtNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);
    if (block) block->Accept(*this);

    indent_ -= 2;
  }

  void VisitPrintStmtNode(const PrintStmtNode* node) override {
    assert(node);

    const auto* expr = node->GetExprPtr();

    std::println(out_, "{:{}}PrintStmtNode:", "", indent_);
    indent_ += 2;

    if (expr) expr->Accept(*this);

    indent_ -= 2;
  }

  void VisitAssignmentStmtNode(const AssignmentStmtNode* node) override {
    assert(node);

    const auto* id = node->GetIdPtr();
    const auto* expr = node->GetExprPtr();

    std::println(out_, "{:{}}AssignmentStmtNode:", "", indent_);
    indent_ += 2;

    if (id) id->Accept(*this);
    if (expr) expr->Accept(*this);

    indent_ -= 2;
  }

 public:
  explicit OneLineDumper(std::ostream& out) : out_(out) {}
};

void OneLineDump(std::ostream& out, const ASTNode* ast) {
  assert(ast);

  OneLineDumper dumper(out);
  ast->Accept(dumper);
}

}  // namespace dumper
