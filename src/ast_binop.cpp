#include "ast/ast_binop.hpp"

BinaryOperation::BinaryOperation(NodePtr left, std::string *opPtr,
                                 NodePtr right)
    : lExp(left), rExp(right), op(*opPtr) {
  delete opPtr;
};
void BinaryOperation::pyPrint(std::ostream &os) {
  os << "(";
  lExp->pyPrint(os);
  os << ") " << op << " (";
  rExp->pyPrint(os);
  os << ")";
}

SizeOfOp::SizeOfOp(NodePtr _exp) : exp(_exp){};
SizeOfOp::SizeOfOp(std::string *_n) : typeName(*_n) { delete _n; };
