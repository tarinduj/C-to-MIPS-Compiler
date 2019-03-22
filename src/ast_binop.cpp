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
void BinaryOperation::mipsPrint() {
  if (dynamic_cast<Variable *>(lExp)) {
    TypePtr integer_type = std::make_shared<PrimitiveType>();
    std::string assign_to = lExp->getName();
    auto LHS = global_context->resolve_chunk(assign_to);
    auto RHS =
        global_context->register_chunk(makeUNQ("__BinOP_RHS"), integer_type);
    if (rExp)
      rExp->mipsPrint(RHS);

    int regL = LHS->load();
    int regR = RHS->load();

    if (op == "=")
      *global_context->get_stream()
          << "\tmove\t$" << regL << ",\t$" << regR << "\n";
    else if (op == "+=")
      *global_context->get_stream()
          << "\taddu\t$" << regL << ",\t$" << regL << ",\t$" << regR << "\n";

    LHS->store();
    RHS->discard();
  }
}
void BinaryOperation::mipsPrint(ChunkPtr res) {
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  auto LHS =
      global_context->register_chunk(makeUNQ("__BinOP_LHS"), integer_type);
  auto RHS =
      global_context->register_chunk(makeUNQ("__BinOP_RHS"), integer_type);
  if (lExp)
    lExp->mipsPrint(LHS);
  if (rExp)
    rExp->mipsPrint(RHS);
  int regL = LHS->load();
  int regR = RHS->load();
  int regRes = res->load();

  mipsPrintOp(regRes, regL, regR);

  LHS->discard();
  RHS->discard();
  res->store();
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

void BinaryOperation::mipsPrintOp(int regRes, int regL, int regR){
  //arithmetic operators
  if (op == "+"){
    *global_context->get_stream() << "\taddu\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  } 
  else if(op == "-"){
    *global_context->get_stream() << "\tsubu\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  }
  else if(op == "*"){
    *global_context->get_stream() << "\tmultu\t$" << regL << ",\t$" << regR << "\n"
                                  << "\tmflo\t$" << regRes << "\n"
                                  << "\tnop\n"
                                  << "\tnop\n";
  }
  else if(op == "/"){
    *global_context->get_stream() << "\tdivu\t$" << regL << ",\t$" << regR << "\n"
                                  << "\tmflo\t$" << regRes << "\n"
                                  << "\tnop\n"
                                  << "\tnop\n";    
  }
  else if(op == "%"){
    *global_context->get_stream() << "\tdivu\t$" << regL << ",\t$" << regR << "\n"
                                  << "\tmfhi\t$" << regRes << "\n"
                                  << "\tnop\n"
                                  << "\tnop\n";    
  }
  //bitwise operators
  else if(op == "<<"){
    *global_context->get_stream() << "\tsllv\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  }
  else if(op == ">>"){
    *global_context->get_stream() << "\tsrlv\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  }
  else if(op == "&"){
    *global_context->get_stream() << "\tand\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  }
  else if(op == "|"){
    *global_context->get_stream() << "\tor\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  }
  else if(op == "^"){
    *global_context->get_stream() << "\txor\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  }
  //logical operators
  else if(op == "&&"){
    std::string nbrUNQ = getUNQLabel();
    std::string end = "__end_&&" + nbrUNQ;
    std::string pass1 = "__pass1_&&" + nbrUNQ;
    std::string pass2 = "__pass2_&&" + nbrUNQ;
    *global_context->get_stream() << "\tbne\t$" << regL << ",\t$zero,\t" << pass1 << "\n"
                                  << "\taddiu\t$" << regRes << ",\t$zero,\t0\n"
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << pass1 << ":\n"
                                  << "\tbne\t$" << regR << ",\t$zero,\t" << pass2 << "\n"
                                  << "\taddiu\t$" << regRes << ",\t$zero,\t0\n"
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << pass2 << ":\n"
                                  << "\taddiu\t$" << regRes << ",\t$zero,\t1\n"
                                  << end << ":\n";
  }
  else if(op == "=="){
    std::string nbrUNQ = getUNQLabel();
    std::string end = "__end_eq" + nbrUNQ;
    std::string eq = "__true_eq" + nbrUNQ;
    *global_context->get_stream() << "\tsubu\t$" << regL << ",\t$" << regL << ",\t$" << regR << "\n"
                                  << "\tbeq\t$zero,\t$" << regL << ",\t" << eq << "\n"
                                  << "\taddiu\t$" << regRes << ",\t$zero,\t0\n"
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << eq << ":\n"
                                  << "\taddiu\t$" << regRes << ",\t$zero,\t1\n"
                                  << end << ":\n";
  }
  else if(op == "||"){
    std::string nbrUNQ = getUNQLabel();
    std::string end = "__end_||" + nbrUNQ;
    std::string pass = "__pass_||" + nbrUNQ;
    *global_context->get_stream() << "\tbne\t$" << regL << ",\t$zero,\t" << pass << "\n"
                                  << "\taddiu\t$" << regRes << ",\t$zero,\t0\n"
                                  << "\tbne\t$" << regL << ",\t$zero,\t" << pass << "\n"
                                  << "\taddiu\t$" << regRes << ",\t$zero,\t0\n"
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << pass << ":\n"
                                  << "\taddiu\t$" << regRes << ",\t$zero,\t1\n"
                                  << end << ":\n";
  }  
  else if(op == "<"){
    *global_context->get_stream() << "\tslt\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  }
  else if(op == ">"){
    *global_context->get_stream() << "\tslt\t$" << regRes << ",\t$" << regR << ",\t$" << regL << "\n";
  }
  else if(op == "<="){
    *global_context->get_stream() << "\taddiu\t$" << regR << ",\t$" << regR << ",\t1\n"
                                  << "\tslt\t$" << regRes << ",\t$" << regL << ",\t$" << regR << "\n";
  }
  else if(op == ">="){
    *global_context->get_stream() << "\taddiu\t$" << regL << ",\t$" << regL << ",\t1\n"
                                  << "\tslt\t$" << regRes << ",\t$" << regR << ",\t$" << regL << "\n";
  }
}

// SizeOfOp::SizeOfOp(NodePtr _exp) : exp(_exp){};
// SizeOfOp::SizeOfOp(std::string *_n) : typeName(*_n) { delete _n; };
