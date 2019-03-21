#include "ast/ast_translation.hpp"
#include "ast/ast_declarator.hpp"
#include "context.hpp"
#include "run.hpp"
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

void TranslationUnit::mipsPrint() {
  *global_context->get_stream() << ".section .mdebug.abi32\n"
                                << ".previous\n"
                                << ".nan	legacy\n"
                                << ".module	fp=32\n"
                                << ".module	nooddspreg\n"
                                << ".abicalls\n";
  for (int i = 0; i < parts.size(); i++) {
    if (parts[i]) {
      parts[i]->mipsPrint();
    }
  }

  *global_context->get_stream() << ".ident	\"GCC: (Ubuntu "
                                   "5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609\"\n";
}