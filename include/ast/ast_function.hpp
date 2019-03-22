#ifndef AST_FUNCTION_HPP
#define AST_FUNCTION_HPP
#include "ast_node.hpp"
#include <string>
#include <vector>

class Function : public Node {
private:
  NodePtr decl = NULL;
  NodePtr statements = NULL; // scope
  std::string returnType;
  void printPreamble(std::string &f_name);
  void printEnd(std::string &f_name);

public:
  Function(std::string *_decSpec, NodePtr _d, NodePtr _s);
  void pyPrint(std::ostream &os); //; when implementing delete {} and leave ;
  void mipsPrint();
  void insert(NodePtr _n) {} //;
};

class FunctionCall : public Node {
private:
  NodePtr arguments = NULL;
  NodePtr functionName;

public:
  FunctionCall(NodePtr _exp, NodePtr _arg);
  void pyPrint(std::ostream &os); //; when implementing delete {} and leave ;
  void mipsPrint();
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