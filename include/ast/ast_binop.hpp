#ifndef AST_BINOP_HPP
#define AST_BINOP_HPP
#include "ast_node.hpp"
#include <string>

class BinaryOperation : public Node {
private:
  NodePtr lExp;
  NodePtr rExp;
  std::string op;
  void pyPrintOp(std::ostream &os);
  void mipsPrintOp(int regL, int regR);
  void mipsPrintOp(int regRes, int regL, int regR);

public:
  BinaryOperation(NodePtr left, std::string *opPtr, NodePtr right);
  void pyPrint(std::ostream &_o);
  void mipsPrint();
  void mipsPrint(ChunkPtr res);
  void insert(NodePtr _n) {} //;
};

// class SizeOfOp : public Node {
// private:
//   int size;
//   NodePtr exp;
//   std::string typeName;

// public:
//   SizeOfOp(NodePtr _exp);
//   SizeOfOp(std::string *_n);
//   virtual void pyPrint(std::ostream &_o) {}
//   virtual void mipsPrint(std::ostream &_o) {} //;
//   virtual void insert(NodePtr _n) {}          //;
// };

#endif