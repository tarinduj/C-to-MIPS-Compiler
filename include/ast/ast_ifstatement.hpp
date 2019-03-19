#ifndef AST_IFSTATEMENT_HPP
#define AST_IFSTATEMENT_HPP

#include "ast_node.hpp"

class IfStatement : public Node {
private:
  NodePtr condition;
  NodePtr trueStatement;
  NodePtr elseStatement = NULL;
  void pyPrintStatement(std::ostream &os, NodePtr s);

public:
  IfStatement(NodePtr _c, NodePtr _t, NodePtr _e);
  void pyPrint(std::ostream &os); //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &os) {} //;
  void insert(NodePtr _n) {}
};

#endif