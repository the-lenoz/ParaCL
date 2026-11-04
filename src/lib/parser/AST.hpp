#pragma once

#include <iostream>
#include <memory>
#include <string>

class ASTNode {
 public:
  virtual ~ASTNode() = default;
  virtual void print(int indent = 0) const = 0;
};

class ExprNode : public ASTNode {};

class ArithNode : public ExprNode {};

class TermNode : public ArithNode {};

class AtomNode : public TermNode {};

class QuestionMarkNode : public AtomNode {
 public:
  QuestionMarkNode() {}
  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "?";
  }
};

class IdNode : public AtomNode {
  std::string value_;

public:
  IdNode(const std::string& val) : value_(val) {}
  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Id: " << value_ << '\n';
  }
};

class IntNode : public AtomNode {
  int value_;

 public:
  IntNode(int val) : value_(val) {}
  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Int: " << value_ << "\n";
  }
};

class ParenExprNode : public AtomNode {
  std::unique_ptr<ExprNode> expr_;

 public:
  ParenExprNode(std::unique_ptr<ExprNode> expr) : expr_(std::move(expr)) {}
  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "ParenExpr:\n";
    expr_->print(indent + 2);
  }
};

class MulNode : public TermNode {
  std::unique_ptr<TermNode> left_;
  std::unique_ptr<AtomNode> right_;

 public:
  MulNode(std::unique_ptr<TermNode> l, std::unique_ptr<AtomNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: *\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class DivNode : public TermNode {
  std::unique_ptr<TermNode> left_;
  std::unique_ptr<AtomNode> right_;

 public:
  DivNode(std::unique_ptr<TermNode> l, std::unique_ptr<AtomNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: /\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class AddNode : public ArithNode {
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<TermNode> right_;

 public:
  AddNode(std::unique_ptr<ArithNode> l, std::unique_ptr<TermNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: +\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class SubNode : public ArithNode {
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<TermNode> right_;

 public:
  SubNode(std::unique_ptr<ArithNode> l, std::unique_ptr<TermNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: -\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class EqNode : public ExprNode {
  std::unique_ptr<ExprNode> left_;
  std::unique_ptr<ArithNode> right_; public:
  EqNode(std::unique_ptr<ExprNode> l, std::unique_ptr<ArithNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: ==\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class LtNode : public ExprNode {
  std::unique_ptr<ExprNode> left_;
  std::unique_ptr<ArithNode> right_;

 public:
  LtNode(std::unique_ptr<ExprNode> l, std::unique_ptr<ArithNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: <\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class GtNode : public ExprNode {
  std::unique_ptr<ExprNode> left_;
  std::unique_ptr<ArithNode> right_;

 public:
  GtNode(std::unique_ptr<ExprNode> l, std::unique_ptr<ArithNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: >\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class LteNode : public ExprNode {
  std::unique_ptr<ExprNode> left_;
  std::unique_ptr<ArithNode> right_;

 public:
  LteNode(std::unique_ptr<ExprNode> l, std::unique_ptr<ArithNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: <=\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class GteNode : public ExprNode {
  std::unique_ptr<ExprNode> left_;
  std::unique_ptr<ArithNode> right_;

 public:
  GteNode(std::unique_ptr<ExprNode> l, std::unique_ptr<ArithNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Op: >=\n";
    left_->print(indent + 2);
    right_->print(indent + 2);
  }
};

class StmtNode : public ASTNode {};


class BlockNode : public ASTNode {
  std::unique_ptr<ASTNode> left_;
  std::unique_ptr<StmtNode> right_;

 public:
  BlockNode(std::unique_ptr<ASTNode> l, std::unique_ptr<StmtNode> r)
      : left_(std::move(l)), right_(std::move(r)) {}

  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Block: \n";
    left_->print(indent + 2);
    if (right_)
    {
      right_->print(indent + 2);
    }
  }
};


class IfStmtNode : public StmtNode {
  std::unique_ptr<ExprNode> condition_;
  std::unique_ptr<BlockNode> body_;
public:
  IfStmtNode(std::unique_ptr<ExprNode> l, std::unique_ptr<BlockNode> r)
    : condition_(std::move(l)), body_(std::move(r)) {}

  virtual void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "If statement: \n";
    condition_->print(indent + 2);
    if (body_)
    {
      body_->print(indent + 2);
    }
  }
};

class WhileStmtNode : public StmtNode {
  std::unique_ptr<ExprNode> condition_;
  std::unique_ptr<BlockNode> body_;
public:
  WhileStmtNode(std::unique_ptr<ExprNode> condition, std::unique_ptr<BlockNode> body)
    : condition_(std::move(condition)), body_(std::move(body)) {}

  virtual void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "While statement: \n";
    condition_->print(indent + 2);
    if (body_)
    {
      body_->print(indent + 2);
    }
  }
};

class PrintStmtNode : public StmtNode {
  std::unique_ptr<ExprNode> expr_;
public:
  PrintStmtNode(std::unique_ptr<ExprNode> expr)
    : expr_(std::move(expr)) {}

  virtual void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "print statement: \n";
    expr_->print(indent + 2);
  }
};

class AssignmentStmtNode : public StmtNode {
  std::unique_ptr<IdNode> id_;
  std::unique_ptr<ExprNode> value_;
public:
  AssignmentStmtNode(std::unique_ptr<IdNode> id, std::unique_ptr<ExprNode> value)
    : id_(std::move(id)), value_(std::move(value)) {}
   virtual void print(int indent) const override {
    std::cout<<std::string(indent, ' ') << "Assignment statement: \n";
    id_->print(indent +2);
    value_->print(indent +2);
  }  
};


