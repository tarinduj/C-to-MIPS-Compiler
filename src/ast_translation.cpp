#include "ast/ast_translation.hpp"

TranslationUnit::TranslationUnit(){};
void TranslationUnit::insert(NodePtr _n) { parts.push_back(_n); }