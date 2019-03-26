#ifndef AST_CONDITIONAL_HPP
#define AST_CONDITIONAL_HPP
#include "ast_node.hpp"

class ConditionalOperation: public Node 
{
private:
  NodePtr condition;
  NodePtr trueExp;
  NodePtr falseExp;
public:
  void mipsPrint(ChunkPtr res);
  void mipsPrint() {};
  void pyPrint(std::ostream& os) {};
  ConditionalOperation(NodePtr _c, NodePtr _t, NodePtr _f);

};

#endif