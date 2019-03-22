#ifndef AST_LOOPS_HPP
#define AST_LOOPS_HPP

#include "ast_node.hpp"

class WhileLoop : public Node {
private:
  NodePtr condition;
  NodePtr statement;
  void pyPrintStatement(std::ostream &os, NodePtr s);

public:
  WhileLoop(NodePtr _c, NodePtr _s);
  void pyPrint(std::ostream &_o);
  void mipsPrint();
  void insert(NodePtr _n) {}
};

#endif