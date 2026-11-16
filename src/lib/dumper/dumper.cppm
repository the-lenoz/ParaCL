module;

#include <print>

#include "AST.hpp"
#include "visitor.hpp"

export module dumper;

namespace dumper {

export class DumpVisitor : public visitor::Visitor {
  int indent_ = 0;
  void VisitQuestionMarkNode(const QuestionMarkNode* node) override {
    std::println("{:{}}", "?", indent_);
  }

  void VisitIdNode(const IdNode* node) override {
    std::println("{:{}}IdNode{{{}}}", "", indent_, node->GetVarName());
  }

  void VisitIntNode(const IntNode* node) override {
    std::println("{:{}}IntNode{{{}}}", "", indent_, node->GetValue());
  }

  void VisitParenExprNode(const ParenExprNode* node) override {
    std::println("{:{}}ParenExprNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitMulNode(const MulNode* node) override {
    std::println("{:{}}MulNode:", "", indent_);
    indent_ += 2;

    node->GetTermPtr()->Accept(*this);
    node->GetAtomPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitDivNode(const DivNode* node) override {
    std::println("{:{}}DivNode:", "", indent_);
    indent_ += 2;

    node->GetTermPtr()->Accept(*this);
    node->GetAtomPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitAddNode(const AddNode* node) override {
    std::println("{:{}}AddNode:", "", indent_);
    indent_ += 2;

    node->GetArithPtr()->Accept(*this);
    node->GetTermPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitSubNode(const SubNode* node) override {
    std::println("{:{}}SubNode:", "", indent_);
    indent_ += 2;

    node->GetArithPtr()->Accept(*this);
    node->GetTermPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitEqNode(const EqNode* node) override {
    std::println("{:{}}EqNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);
    node->GetArithPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitLtNode(const LtNode* node) override {
    std::println("{:{}}LtNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);
    node->GetArithPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitGtNode(const GtNode* node) override {
    std::println("{:{}}GtNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);
    node->GetArithPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitLteNode(const LteNode* node) override {
    std::println("{:{}}LteNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);
    node->GetArithPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitGteNode(const GteNode* node) override {
    std::println("{:{}}GteNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);
    node->GetArithPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitBlockNode(const BlockNode* node) override {
    std::println("{:{}}BlockNode:", "", indent_);
    indent_ += 2;
    node->GetASTPtr()->Accept(*this);
    if (node->GetStmtPtr()) {
      node->GetStmtPtr()->Accept(*this);
    }

    indent_ -= 2;
  }

  void VisitIfStmtNode(const IfStmtNode* node) override {
    std::println("{:{}}IfStmtNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);
    if (node->GetBlockPtr()) {
      node->GetBlockPtr()->Accept(*this);
    }

    indent_ -= 2;
  }

  void VisitWhileStmtNode(const WhileStmtNode* node) override {
    std::println("{:{}}WhileStmtNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);
    if (node->GetBlockPtr()) {
      node->GetBlockPtr()->Accept(*this);
    }
    indent_ -= 2;
  }

  void VisitPrintStmtNode(const PrintStmtNode* node) override {
    std::println("{:{}}PrintStmtNode:", "", indent_);
    indent_ += 2;

    node->GetExprPtr()->Accept(*this);

    indent_ -= 2;
  }

  void VisitAssignmentStmtNode(const AssignmentStmtNode* node) override {
    std::println("{:{}}AssignmentStmtNode:", "", indent_);
    indent_ += 2;

    node->GetIdPtr()->Accept(*this);
    node->GetExprPtr()->Accept(*this);

    indent_ -= 2;
  }
};

}  // namespace dumper