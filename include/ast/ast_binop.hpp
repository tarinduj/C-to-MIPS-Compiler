#ifndef AST_BINOP_HPP
#define AST_BINOP_HPP
#include "ast_node.hpp"
#include <string>

class BinaryOperation : public Node {
private:
  NodePtr lExp;
  NodePtr rExp;
  std::string op;

public:
  BinaryOperation(NodePtr left, std::string *opPtr, NodePtr right);
  virtual void pyPrint(std::ostream &_o);
  virtual void mipsPrint(std::ostream &_o) {} //;
  virtual void insert(NodePtr _n) {}          //;
};

class SizeOfOp : public Node {
private:
  int size;
  NodePtr exp;
  std::string typeName;

public:
  SizeOfOp(NodePtr _exp);
  SizeOfOp(std::string *_n);
  virtual void pyPrint(std::ostream &_o) {}
  virtual void mipsPrint(std::ostream &_o) {} //;
  virtual void insert(NodePtr _n) {}          //;
};

#endif