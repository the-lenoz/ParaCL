#pragma once

#include <iostream>
#include <memory>
#include <string>

/**
 * Basic class for AST node; Declares print function 
 */
class ASTNode {
 public:
  virtual ~ASTNode() = default;
  virtual void print(int indent = 0) const = 0;
};

/**
 * Basic class for expression AST node; expressions are all the constructions with values
 */
class ExprNode : public ASTNode {};

/**
 * Basic class for arithmetic expression AST node, could be addition, substraction or term
 */
class ArithNode : public ExprNode {};

/**
 * Basic class for arithmetic term AST node - could be multiplication, division or atom
 */
class TermNode : public ArithNode {};

/**
 * Basic class for atomic expression AST node - could be a numeric const, variable, input sign or an expression in parentheses
 */
class AtomNode : public TermNode {};

/**
 * Question mark AST node - in ParaCL it means input
 */
class QuestionMarkNode : public AtomNode {
 public:
  QuestionMarkNode() {}
  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "?\n";
  }
};

/**
 * Any identifier AST node (only variables supported yet)
 */
class IdNode : public AtomNode {
  std::string value_;

public:
  IdNode(const std::string& val) : value_(val) {}
  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Id: " << value_ << '\n';
  }
};

/**
 * Integer constant AST node
 */
class IntNode : public AtomNode {
  int value_;

 public:
  IntNode(int val) : value_(val) {}
  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "Int: " << value_ << "\n";
  }
};


/**
 * Expression in parentheses AST node
 */
class ParenExprNode : public AtomNode {
  std::unique_ptr<ExprNode> expr_;

 public:
  ParenExprNode(std::unique_ptr<ExprNode> expr) : expr_(std::move(expr)) {}
  void print(int indent) const override {
    std::cout << std::string(indent, ' ') << "ParenExpr:\n";
    expr_->print(indent + 2);
  }
};

/**
 * Multiplication AST node
 */
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

/**
 * Division AST node
 */
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

/**
 * Addition AST node 
 */
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

/**
 * Substraction AST node 
 */
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

/**
 * AST node for '==' operator
 */
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

/**
 * AST node for '<' operator
 */
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

/**
 * AST node for '>' operator
 */
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

/**
 * AST node for '<=' operator
 */
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

/**
 * AST node for '>=' operator
 */
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

/**
 * Base class for statement AST node.
 * could be if, while, print or assignment
 */
class StmtNode : public ASTNode {};


/**
 * AST node for statement block.
 * if there is only one statement, the
 * right_ field is nullptr
 */
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

/**
 * AST node for 'if' statemnt
 */
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

/**
 * AST node for 'while' statement
 */
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

/**
 * AST node for 'print' statement
 */
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
/**
 * AST node for assignment
 */
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


