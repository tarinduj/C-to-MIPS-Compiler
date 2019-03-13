#include "ast/ast_binop.hpp"

BinaryOperation::BinaryOperation(NodePtr left, std::string *opPtr,
                                 NodePtr right)
    : lExp(left), rExp(right), op(*opPtr) {
  delete opPtr;
};

SizeOfOp::SizeOfOp(NodePtr _exp) : exp(_exp){};
SizeOfOp::SizeOfOp(std::string *_n) : typeName(*_n) { delete _n; };
