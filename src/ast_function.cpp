#include "ast/ast_function.hpp"
#include "ast/ast_variable.hpp"

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
    : functionName(_exp), arguments(_arg){};

void FunctionCall::pyPrint(std::ostream &os) {
  if (dynamic_cast<Variable *>(functionName)) {
    functionName->pyPrint(os);
    os << "(";
    if (arguments)
      arguments->pyPrint(os);
    os << ")";
  } else {
    functionName->pyPrint(os);
  }
}