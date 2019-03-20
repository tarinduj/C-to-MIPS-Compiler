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
  std::cerr << "entered translation unit\n";
  //*global_context->get_stream() << "hello";
  // << "\t.file	1 \"\"\n"
  *global_context->get_stream() << "\t.section .mdebug.abi32\n"
                                << "\t.previous\n"
                                << "\t.nan	legacy\n"
                                << "\t.module	fp=32\n"
                                << "\t.module	nooddspreg\n"
                                << "\t.abicalls\n";
  std::cerr << "finished first printing\n";
  for (int i = 0; i < parts.size(); i++) {
    if (parts[i]) {
      parts[i]->mipsPrint();
    }
  }

  *global_context->get_stream() << ".ident	\"GCC: (Ubuntu "
                                   "5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609\"";
}