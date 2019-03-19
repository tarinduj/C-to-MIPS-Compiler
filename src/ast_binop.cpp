#include "ast/ast_binop.hpp"

BinaryOperation::BinaryOperation(NodePtr left, std::string *opPtr,
                                 NodePtr right)
    : lExp(left), rExp(right), op(*opPtr) {
  delete opPtr;
};
void BinaryOperation::pyPrint(std::ostream &os) {
  os << "(";
  lExp->pyPrint(os);
  //os << ") " << op << " (";
  pyPrintOp(os);
  rExp->pyPrint(os);
  os << ")";
}

void BinaryOperation::pyPrintOp(std::ostream& os){
  if(op == "&&"){
    os << ") and (";
  }
  else if(op == "||"){
    os << ") or (";
  }
  else{
    os << ") " << op << " (";
  }
}

SizeOfOp::SizeOfOp(NodePtr _exp) : exp(_exp){};
SizeOfOp::SizeOfOp(std::string *_n) : typeName(*_n) { delete _n; };
