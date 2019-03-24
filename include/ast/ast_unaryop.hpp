#ifndef AST_UNARYOP_HPP
#define AST_UNARYOP_HPP
#include "ast_node.hpp"

class UnaryOperation : public Node {
private:
  std::string op;
  NodePtr expression;
  void mipsPrintOp(int regExp);

public:
  UnaryOperation(std::string *_op, NodePtr _exp);
  void pyPrint(std::ostream &_o);
  void mipsPrint();
  void mipsPrint(ChunkPtr res);
  void insert(NodePtr _n) {}
  std::string getName();
};

class PostFixExpression: public Node
{
private:
  std::string op;
  NodePtr expression;
  void mipsPrintOp(int regExp);
public:
  PostFixExpression(NodePtr _exp, std::string *_op);
  void pyPrint(std::ostream &_o) {}
  void mipsPrint();
  void mipsPrint(ChunkPtr res);
  void insert(NodePtr _n) {}
  std::string getName();
};
#endif