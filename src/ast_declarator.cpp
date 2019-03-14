#include "ast/ast_declarator.hpp"

DirectDeclarator::DirectDeclarator(NodePtr _decl, NodePtr _list)
    : dirDec(_decl), paramList(_list){};
void DirectDeclarator::pyPrint(std::ostream& os){
  os<<"direct declarator printing \n";
  //os<<dirDec<<" "<<paramList<<"\n";
  if(dirDec) dirDec->pyPrint(os);
  if(paramList) paramList->pyPrint(os);
}
Declaration::Declaration(std::string *_spec, NodePtr _list)
    : decSpec(*_spec), initDecList(_list) {
  delete _spec;
};
void Declaration::pyPrint(std::ostream& os){
  os << "Declaration printing\n";
  os << decSpec << " ";
  if(initDecList) initDecList->pyPrint(os);
}

InitDeclarator::InitDeclarator(NodePtr _d, NodePtr _i)
    : declarator(_d), initializer(_i){};
void InitDeclarator::pyPrint(std::ostream& os){
  os << "InitDeclarator printing\n";
  os << declarator << " " << initializer << "\n";
  if(declarator) declarator->pyPrint(os);
  if(initializer) initializer->pyPrint(os);
}