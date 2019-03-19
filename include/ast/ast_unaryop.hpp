#ifndef AST_UNARYOP_HPP
#define AST_UNARYOP_HPP
#include "ast_node.hpp"

class UnaryOperation : public Node {
private:
  std::string op;
  NodePtr expression;

public:
  UnaryOperation(std::string *_op, NodePtr _exp);
  void pyPrint(std::ostream &_o);
  void mipsPrint(std::ostream &_o) {} //;
  void insert(NodePtr _n) {}
};

#endif