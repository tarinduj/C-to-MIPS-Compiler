#ifndef AST_FUNCTION_HPP
#define AST_FUNCTION_HPP
#include "ast_node.hpp"
#include <string>
#include <vector>

class Function : public Node {
private:
  NodePtr decl;
  NodePtr statements;
  std::string returnType;

public:
  Function(std::string *_decSpec, NodePtr _d, NodePtr _s);
  void pyPrint(std::ostream &_o) {} //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
  void insert(NodePtr _n) {}          //;
};

class FunctionCall : public Node {
private:
  NodePtr arguments;
  NodePtr postExp;

public:
  FunctionCall(NodePtr _exp, NodePtr _arg);
  void pyPrint(std::ostream &_o) {} //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
  void insert(NodePtr _n) {}          //;
};

// class FunctionDeclaration: public Node
// {
// private:
//     NodePtr arguments;
//     std::string returnType;
//     std::string functionName;
// public:
//     FunctionDeclaration(NodePtr _ret, std::string* _n, NodePtr _arg);
//     void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave
//     ; void mipsPrint(std::ostream& _o){}//; void insert(NodePtr _n){}//;
// };

#endif