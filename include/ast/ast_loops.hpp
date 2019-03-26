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
  void pyPrint(std::ostream &os);
  void mipsPrint();
  void insert(NodePtr _n) {}
};

class DoWhileLoop : public Node {
private:
  NodePtr condition;
  NodePtr statement;
public:
  void pyPrint(std::ostream &os){}
  DoWhileLoop(NodePtr _s, NodePtr _c);
  void mipsPrint();
};

class ForLoop : public Node {
private:
  NodePtr expressionL;
  NodePtr expressionM;
  NodePtr expressionR;
  NodePtr statement;
public:
  void pyPrint(std::ostream &os){}
  ForLoop(NodePtr _Left, NodePtr _Middle, NodePtr _Right, NodePtr _Stat);
  void mipsPrint();
};

#endif