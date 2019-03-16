#ifndef AST_VARIABLE_HPP
#define AST_VARIABLE_HPP

#include "ast_node.hpp"

class Variable : public Node {
private:
  std::string name;

public:
  Variable(std::string *_s);
  void pyPrint(std::ostream &_o); //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
  void insert(NodePtr _n) {}   
  std::string getName();
};

#endif