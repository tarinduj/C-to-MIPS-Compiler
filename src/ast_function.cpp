#include "ast/ast_function.hpp"

Function::Function(std::string *_decSpec, NodePtr _d, NodePtr _s)
    : returnType(*_decSpec), statements(_s), decl(_d) {
  delete _decSpec;
};

FunctionCall::FunctionCall(NodePtr _exp, NodePtr _arg)
    : postExp(_exp), arguments(_arg){};