#include "ast/ast_binop.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_variable.hpp"

BinaryOperation::BinaryOperation(NodePtr left, std::string *opPtr,
                                 NodePtr right)
    : lExp(left), rExp(right), op(*opPtr) {
  delete opPtr;
};
void BinaryOperation::pyPrint(std::ostream &os) {
  os << "(";
  lExp->pyPrint(os);
  // os << ") " << op << " (";
  pyPrintOp(os);
  rExp->pyPrint(os);
  os << ")";
}
void BinaryOperation::mipsPrint(){
  if(op == "=" && dynamic_cast<Variable*>(lExp)){
    TypePtr integer_type = std::make_shared<PrimitiveType>();
    std::string assign_to = lExp->getName();
    auto LHS = global_context->resolve_chunk(assign_to);
    auto RHS = global_context->register_chunk("tmp_assign_from", integer_type);
    int regL = LHS->load();
    if(rExp) rExp->mipsPrint(RHS);
    int regR = RHS->load();

    *global_context->get_stream() << "\tmove\t$" << regL << ",\t$" << regR <<"\n";
    LHS->store();
  }
}
void BinaryOperation::pyPrintOp(std::ostream &os) {
  if (op == "&&") {
    os << ") and (";
  } else if (op == "||") {
    os << ") or (";
  } else {
    os << ") " << op << " (";
  }
}

// SizeOfOp::SizeOfOp(NodePtr _exp) : exp(_exp){};
// SizeOfOp::SizeOfOp(std::string *_n) : typeName(*_n) { delete _n; };
