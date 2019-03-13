#ifndef AST_TRANSLATION_HPP
#define AST_TRANSLATION_HPP

#include "ast_node.hpp"
#include <vector>

class TranslationUnit : public Node {
private:
  std::vector<NodePtr> parts;

public:
  TranslationUnit();
  void pyPrint(std::ostream &_o) {} //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
  void insert(NodePtr _n);
};
#endif