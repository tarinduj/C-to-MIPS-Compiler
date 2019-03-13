#ifndef AST_JUMP_HPP
#define AST_JUMP_HPP
#include "ast_node.hpp"
#include <string>

// class Break: public Node
// {
// private:
//     /* data */
// public:
//     Break(/* args */) { }
//     ~Break() { }
// };

// class Continue: public Node
// {
// private:
//     /* data */
// public:
//     Continue(/* args */) { }
//     ~Continue() { }
// };

class Return : public Node {
private:
  NodePtr returnExp;

public:
  Return(NodePtr _r);
  void pyPrint(std::ostream &_o) {} //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
  void insert(NodePtr _n) {}          //;
};

#endif