#include "ast/ast_declarator.hpp"

DirectDeclarator::DirectDeclarator(NodePtr _decl, NodePtr _list)
    : dirDec(_decl), paramList(_list){};

Declaration::Declaration(std::string *_spec, NodePtr _list)
    : decSpec(*_spec), initDecList(_list) {
  delete _spec;
};

InitDeclarator::InitDeclarator(NodePtr _d, NodePtr _i)
    : declarator(_d), initializer(_i){};