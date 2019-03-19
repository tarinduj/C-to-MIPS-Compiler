#include "ast/ast_declarator.hpp"
#include "ast/ast_variable.hpp"

DirectDeclarator::DirectDeclarator(NodePtr _decl, NodePtr _list)
    : dirDec(_decl), idList(_list){};
void DirectDeclarator::pyPrint(std::ostream &os) {
  if (dirDec)
    dirDec->pyPrint(os);
  os << "(";
  if (idList)
    idList->pyPrint(os);
  os << "):\n";
}
void DirectDeclarator::getGlobal(std::vector<std::string> &v) {
  if (dynamic_cast<Variable *>(dirDec)) {
    v.push_back(dirDec->getName());
  }
}

Declaration::Declaration(std::string *_spec, NodePtr _list)
    : decSpec(*_spec), initDecList(_list) {
  delete _spec;
};
void Declaration::pyPrint(std::ostream &os) {
  if (initDecList) {
    initDecList->pyPrint(os);
  }
}

void Declaration::getGlobal(std::vector<std::string> &v) {
  initDecList->getGlobal(v);
}

InitDeclarator::InitDeclarator(NodePtr _d, NodePtr _i)
    : declarator(_d), initializer(_i){};
void InitDeclarator::pyPrint(std::ostream &os) {
  // os << declarator << " " << initializer << "\n";
  if (declarator && initializer) {
    declarator->pyPrint(os);
    os << " = ";
    initializer->pyPrint(os);
  } else {
    declarator->pyPrint(os);
    os << " = 0";
  }
}

void InitDeclarator::getGlobal(std::vector<std::string> &v) {
  if (dynamic_cast<Variable *>(declarator))
    v.push_back(declarator->getName());
}

ParamDeclaration::ParamDeclaration(std::string *_s, NodePtr _d)
    : decSpec(*_s), declarator(_d) {
  delete _s;
}

void ParamDeclaration::pyPrint(std::ostream &os) {
  if (declarator)
    declarator->pyPrint(os);
}