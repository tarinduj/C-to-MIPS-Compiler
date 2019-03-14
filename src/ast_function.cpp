#include "ast/ast_function.hpp"

Function::Function(std::string *_decSpec, NodePtr _d, NodePtr _s)
    : returnType(*_decSpec), statements(_s), decl(_d) {
  delete _decSpec;
};
void Function::pyPrint(std::ostream& os){
  //os<<"function printing \n";
  os<<returnType<<" ";
  if(decl) decl->pyPrint(os);
  if(statements) statements->pyPrint(os);
}
FunctionCall::FunctionCall(NodePtr _exp, NodePtr _arg)
    : postExp(_exp), arguments(_arg){};
