#include "ast/ast_declarator.hpp"
#include "ast/ast_primitives.hpp"
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
std::string DirectDeclarator::getName(){
  return dirDec->getName();
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
void Declaration::mipsPrint() {
  if (decSpec == "int" && initDecList) {
    initDecList->mipsPrint();
  }
}

void Declaration::getGlobal(std::vector<std::string> &v) {
  initDecList->getGlobal(v);
}
void Declaration::registerVariables(){
  if(initDecList) initDecList->registerVariables();
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

void InitDeclarator::mipsPrint() {
  std::string var_name;
  int val;
  if (dynamic_cast<Variable *>(declarator))
    var_name = declarator->getName();
  if (dynamic_cast<IntConst *>(initializer))
    val = initializer->getVal();
    *global_context->get_stream() << ".globl " << var_name << "\n"
                                  << ".data\n"
                                  << ".align 2\n"
                                  << ".type " << var_name << ", @object\n"
                                  << ".size " << var_name << ", 4\n"
                                  << var_name << ":\n"
                                  << ".word " << val << "\n";
}

void InitDeclarator::getGlobal(std::vector<std::string> &v) {
  if (dynamic_cast<Variable *>(declarator))
    v.push_back(declarator->getName());
}
void InitDeclarator::registerSingleVar(){
  if(dynamic_cast<Variable*>(declarator) && dynamic_cast<IntConst*>(initializer)){
    std::string var_name = declarator->getName();
    int var_val = initializer->getVal();
    TypePtr integer_type = std::make_shared<PrimitiveType>();

    ChunkPtr init;
    if(registerGlobal) 
      init = global_context->register_global_chunk(var_name, integer_type);
    else 
      init = global_context->register_chunk(var_name, integer_type);

    int reg = init->load();
    *global_context->get_stream() << "\tli\t$" << reg << ",\t" << var_val <<"\n";
    init->store();
  }
  else if(dynamic_cast<Variable*>(declarator)){
    std::string var_name = declarator->getName();
    LOG << "InitDec registering variable without value: " << var_name << "\n";
    TypePtr integer_type = std::make_shared<PrimitiveType>();
    if(registerGlobal) 
      auto init = global_context->register_global_chunk(var_name, integer_type);
    else 
      auto init = global_context->register_chunk(var_name, integer_type);  }
}

ParamDeclaration::ParamDeclaration(std::string *_s, NodePtr _d)
    : decSpec(*_s), declarator(_d) {
  delete _s;
}

void ParamDeclaration::pyPrint(std::ostream &os) {
  if (declarator)
    declarator->pyPrint(os);
}