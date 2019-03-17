#ifndef AST_TRANSLATION_HPP
#define AST_TRANSLATION_HPP

#include "ast_node.hpp"
#include <vector>

class TranslationUnit : public Node {
private:
  std::vector<NodePtr> parts;

public:
  TranslationUnit();
  void pyPrint(std::ostream &os);
  void mipsPrint(std::ostream &os) {} //;
  void insert(NodePtr _n);
};
#endif