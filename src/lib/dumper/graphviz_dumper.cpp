module;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <cassert>
#include <ostream>
#include <string>
#include <string_view>

#include "AST.hpp"
#include "visitor.hpp"

module dumper;

namespace dumper {

class GraphvizDumper : public visitor::Visitor {
  struct Token {
    std::string label;
  };

  using Graph =
      boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, Token>;
  using Vertex = Graph::vertex_descriptor;

  Graph graph_;
  Vertex subtree_root_;

  void VisitQuestionMarkNode(
      [[maybe_unused]] const QuestionMarkNode* node) override {
    assert(node);

    constexpr std::string_view name = "?";
    subtree_root_ = boost::add_vertex(Token{std::string(name)}, graph_);
  }

  void VisitIdNode(const IdNode* node) override {
    assert(node);

    subtree_root_ = boost::add_vertex(Token{node->GetVarName()}, graph_);
  }

  void VisitIntNode(const IntNode* node) override {
    assert(node);

    subtree_root_ =
        boost::add_vertex(Token{std::to_string(node->GetValue())}, graph_);
  }

  void VisitParenExprNode(const ParenExprNode* node) override {
    assert(node);
    const auto* expr = node->GetExprPtr();

    constexpr std::string_view name = "ParenExpr";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (expr) {
      expr->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitUnaryMinusNode(const UnaryMinusNode* node) override {
    assert(node);
    const auto* atom = node->GetAtomPtr();

    constexpr std::string_view name = "-";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (atom) {
      atom->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitUnaryPlusNode(const UnaryPlusNode* node) override {
    assert(node);
    const auto* atom = node->GetAtomPtr();

    constexpr std::string_view name = "+";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (atom) {
      atom->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitMulNode(const MulNode* node) override {
    assert(node);
    const auto* left = node->GetTermPtr();
    const auto* right = node->GetAtomPtr();

    constexpr std::string_view name = "*";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitDivNode(const DivNode* node) override {
    assert(node);
    const auto* left = node->GetTermPtr();
    const auto* right = node->GetAtomPtr();

    constexpr std::string_view name = "/";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitAddNode(const AddNode* node) override {
    assert(node);
    const auto* left = node->GetArithPtr();
    const auto* right = node->GetTermPtr();

    constexpr std::string_view name = "+";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitSubNode(const SubNode* node) override {
    assert(node);
    const auto* left = node->GetArithPtr();
    const auto* right = node->GetTermPtr();

    constexpr std::string_view name = "-";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitEqNode(const EqNode* node) override {
    assert(node);
    const auto* left = node->GetExprPtr();
    const auto* right = node->GetArithPtr();

    constexpr std::string_view name = "==";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitNeqNode(const NeqNode* node) override {
    assert(node);
    const auto* left = node->GetExprPtr();
    const auto* right = node->GetArithPtr();

    constexpr std::string_view name = "!=";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitLtNode(const LtNode* node) override {
    assert(node);
    const auto* left = node->GetExprPtr();
    const auto* right = node->GetArithPtr();

    constexpr std::string_view name = "<";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitGtNode(const GtNode* node) override {
    assert(node);
    const auto* left = node->GetExprPtr();
    const auto* right = node->GetArithPtr();

    constexpr std::string_view name = ">";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitLteNode(const LteNode* node) override {
    assert(node);
    const auto* left = node->GetExprPtr();
    const auto* right = node->GetArithPtr();

    constexpr std::string_view name = "<=";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitGteNode(const GteNode* node) override {
    assert(node);
    const auto* left = node->GetExprPtr();
    const auto* right = node->GetArithPtr();

    constexpr std::string_view name = ">=";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (left) {
      left->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (right) {
      right->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitBlockNode(const BlockNode* node) override {
    assert(node);
    const auto* block = node->GetBlockPtr();
    const auto* stmt = node->GetStmtPtr();

    constexpr std::string_view name = "block";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (block) {
      block->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (stmt) {
      stmt->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitIfStmtNode(const IfStmtNode* node) override {
    assert(node);
    const auto* condition = node->GetExprPtr();
    const auto* body = node->GetBlockPtr();

    constexpr std::string_view name = "if";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (condition) {
      condition->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (body) {
      body->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitWhileStmtNode(const WhileStmtNode* node) override {
    assert(node);
    const auto* condition = node->GetExprPtr();
    const auto* body = node->GetBlockPtr();

    constexpr std::string_view name = "while";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (condition) {
      condition->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (body) {
      body->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitPrintStmtNode(const PrintStmtNode* node) override {
    assert(node);
    const auto* expr = node->GetExprPtr();

    constexpr std::string_view name = "print";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (expr) {
      expr->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

  void VisitAssignmentStmtNode(const AssignmentStmtNode* node) override {
    assert(node);
    const auto* id = node->GetIdPtr();
    const auto* expr = node->GetExprPtr();

    constexpr std::string_view name = "=";
    const Vertex vertex = boost::add_vertex(Token{std::string(name)}, graph_);

    if (id) {
      id->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    if (expr) {
      expr->Accept(*this);
      boost::add_edge(vertex, subtree_root_, graph_);
    }

    subtree_root_ = vertex;
  }

 public:
  void WriteDot(std::ostream& out) const {
    boost::write_graphviz(out, graph_,
                          boost::make_label_writer(get(&Token::label, graph_)));
  }
};

void GraphvizDump(std::ostream& out, const ASTNode* ast) {
  assert(ast);

  GraphvizDumper dumper;
  ast->Accept(dumper);
  dumper.WriteDot(out);
}

}  // namespace dumper
