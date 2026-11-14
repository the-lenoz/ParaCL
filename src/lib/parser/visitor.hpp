#pragma once

/**
 * AST nodes
 */
class QuestionMarkNode;
class IdNode;
class IntNode;
class ParenExprNode;
class MulNode;
class DivNode;
class AddNode;
class SubNode;
class EqNode;
class GtNode;
class GteNode;
class LtNode;
class LteNode;
class BlockNode;
class IfStmtNode;
class WhileStmtNode;
class PrintStmtNode;
class AssignmentStmtNode;


#include <memory>

namespace visitor {

/**
 * Interface for visiting each node in AST
 */
class Visitor {
 public:
  Visitor() = default;

  virtual void VisitQuestionMarkNode(
    const QuestionMarkNode* node
  ) = 0;

  virtual void VisitIdNode(
    const IdNode* node
  ) = 0;

  virtual void VisitIntNode(
    const IntNode* node
  ) = 0;

  virtual void VisitParenExprNode(
    const ParenExprNode* node
  )  = 0;

  virtual void VisitMulNode(
    const MulNode* node
  ) = 0;

  virtual void VisitDivNode(
    const DivNode* node
  ) = 0;

  virtual void VisitAddNode(
    const AddNode* node
  ) = 0;

  virtual void VisitSubNode(
    const SubNode* node
  ) = 0;

  virtual void VisitEqNode(
    const EqNode* node
  ) = 0;

  virtual void VisitLtNode(
    const LtNode* node
  ) = 0;

  virtual void VisitGtNode(
    const GtNode* node
  ) = 0;

  virtual void VisitLteNode(
    const LteNode* node
  ) = 0;

  virtual void VisitGteNode(
    const GteNode* node
  ) = 0;

  virtual void VisitBlockNode(
    const BlockNode* node
  ) = 0;

  virtual void VisitIfStmtNode(
    const IfStmtNode* node
  ) = 0;

  virtual void VisitWhileStmtNode(
    const WhileStmtNode* node
  ) = 0;

  virtual void VisitPrintStmtNode(
    const PrintStmtNode* node
  ) = 0;

  virtual void VisitAssignmentStmtNode(
    const AssignmentStmtNode* node
  ) = 0;
};
} // namespace visitor
