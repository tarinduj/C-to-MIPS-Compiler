#ifndef AST_PRIMITIVES_HPP
#define AST_PRIMITIVES_HPP

#include "ast_node.hpp"
#include <string>

class IntConst : public Node {
private:
  int val;
  int size;
  std::string type;

public:
  IntConst(int _v);
  void insert(NodePtr _n) {}
  void pyPrint(std::ostream &_o) {} //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
};

class FloatConst : public Node {
private:
  double val;
  int size;

public:
  FloatConst(double _v);
  void insert(NodePtr _n) {}
  void pyPrint(std::ostream &_o) {} //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
};

class CharConst : public Node {
private:
  int val;
  int size;

public:
  CharConst(int _v);
  void insert(NodePtr _n) {}
  void pyPrint(std::ostream &_o) {} //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
};

class String : public Node {
private:
  std::string val;

public:
  String(std::string *_v);
  void insert(NodePtr _n) {}
  void pyPrint(std::ostream &_o) {} //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
};

#endif