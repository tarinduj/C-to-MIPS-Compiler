#include "ast/ast_function.hpp"

Function::Function(std::string *_decSpec, NodePtr _d, NodePtr _s)
    : returnType(*_decSpec), statements(_s), decl(_d) {
  delete _decSpec;
};
void Function::pyPrint(std::ostream &os) {
  os << "def ";
  if (decl)
    decl->pyPrint(os);
  for (int i = 0; i < globalVarNames.size(); i++) {
    os << "\tglobal " << globalVarNames[i] << "\n";
  }
  if (statements)
    statements->pyPrint(os);
  os << "\n";
}
FunctionCall::FunctionCall(NodePtr _exp, NodePtr _arg)
    : postExp(_exp), arguments(_arg){};
