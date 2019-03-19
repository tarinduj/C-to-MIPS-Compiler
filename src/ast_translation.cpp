#include "ast/ast_translation.hpp"
#include "ast/ast_declarator.hpp"

#include <iostream>
TranslationUnit::TranslationUnit(){};
void TranslationUnit::insert(NodePtr _n) { parts.push_back(_n); }
void TranslationUnit::pyPrint(std::ostream &os) {
  for (int i = 0; i < parts.size(); i++) {
    if (dynamic_cast<Declaration *>(parts[i])) {
      parts[i]->getGlobal(globalVarNames);
    }
  }

  for (int i = 0; i < parts.size(); i++) {
    if (parts[i]) {
      parts[i]->pyPrint(os);
      os << "\n";
    }
  }
}