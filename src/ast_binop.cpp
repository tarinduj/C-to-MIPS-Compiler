#include "ast/ast_binop.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_variable.hpp"
#include "ast/ast_function.hpp"
#include "fmt/format.h"

using namespace fmt::literals;


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

    mipsPrintOp(regL, regR);

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
    *global_context->get_stream() << "\taddu\t${},\t${},\t${}\n"_format(regRes,regL,regR);
  } 
  else if(op == "-"){
    *global_context->get_stream() << "\tsubu\t${},\t${},\t${}\n"_format(regRes,regL,regR);
  }
  else if(op == "*"){
    *global_context->get_stream() << "\tmultu\t${},\t${}\n"_format(regL, regR)
                                  << "\tmflo\t${}\n"_format(regRes)
                                  << "\tnop\n"
                                  << "\tnop\n";
  }
  else if(op == "/"){
    *global_context->get_stream() << "\tdivu\t${},\t${}\n"_format(regL, regR)
                                  << "\tmflo\t${}\n"_format(regRes)
                                  << "\tnop\n"
                                  << "\tnop\n";    
  }
  else if(op == "%"){
    *global_context->get_stream() << "\tdivu\t${},\t${}\n"_format(regL, regR)
                                  << "\tmfhi\t${}\n"_format(regRes)
                                  << "\tnop\n"
                                  << "\tnop\n";    
  }
  //bitwise operators
  else if(op == "<<"){
    *global_context->get_stream() << "\tsllv\t${},\t${},\t${}\n"_format(regRes, regL, regR);
  }
  else if(op == ">>"){
    *global_context->get_stream() << "\tsrlv\t${},\t${},\t${}\n"_format(regRes, regL, regR);
  }
  else if(op == "&"){
    *global_context->get_stream() << "\tand\t${},\t${},\t${}\n"_format(regRes, regL, regR);
  }
  else if(op == "|"){
    *global_context->get_stream() << "\tor\t${},\t${},\t${}\n"_format(regRes, regL, regR);
  }
  else if(op == "^"){
    *global_context->get_stream() << "\txor\t${},\t${},\t${}\n"_format(regRes, regL, regR);
  }
  //logical operators
  else if(op == "&&"){
    std::string nbrUNQ = getUNQLabel();
    std::string end = "__end_L_AND" + nbrUNQ;
    std::string pass1 = "__pass1_L_AND" + nbrUNQ;
    std::string pass2 = "__pass2_L_AND" + nbrUNQ;
    *global_context->get_stream() << "\tbne\t${},\t$zero,\t{}\n"_format(regL, pass1)
                                  << "\taddiu\t${},\t$zero,\t0\n"_format(regRes)
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << pass1 << ":\n"
                                  << "\tbne\t${},\t$zero,\t{}\n"_format(regR, pass2)
                                  << "\taddiu\t${},\t$zero,\t0\n"_format(regRes)
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << pass2 << ":\n"
                                  << "\taddiu\t${},\t$zero,\t1\n"_format(regRes)
                                  << end << ":\n";
  }
  else if(op == "=="){
    std::string nbrUNQ = getUNQLabel();
    std::string end = "__end_eq" + nbrUNQ;
    std::string eq = "__true_eq" + nbrUNQ;
    *global_context->get_stream() << "\tsubu\t${},\t${},\t${}\n"_format(regL, regL, regR)
                                  << "\tbeq\t$zero,\t${},\t{}\n"_format(regL, eq)
                                  << "\taddiu\t${},\t$zero,\t0\n"_format(regRes)
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << eq << ":\n"
                                  << "\taddiu\t${},\t$zero,\t1\n"_format(regRes)
                                  << end << ":\n";
  }
   else if(op == "!="){
    std::string nbrUNQ = getUNQLabel();
    std::string end = "__end_neq" + nbrUNQ;
    std::string eq = "__true_neq" + nbrUNQ;
    *global_context->get_stream() << "\tsubu\t${},\t${},\t${}\n"_format(regL, regL, regR)
                                  << "\tbne\t$zero,\t${},\t{}\n"_format(regL, eq)
                                  << "\taddiu\t${},\t$zero,\t0\n"_format(regRes)
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << eq << ":\n"
                                  << "\taddiu\t${},\t$zero,\t1\n"_format(regRes)
                                  << end << ":\n";
  } 
  else if(op == "||"){
    std::string nbrUNQ = getUNQLabel();
    std::string end = "__end_L_OR" + nbrUNQ;
    std::string pass = "__pass_L_OR" + nbrUNQ;
    *global_context->get_stream() << "\tbne\t${},\t$zero,\t{}\n"_format(regL, pass)
                                  << "\taddiu\t${},\t$zero,\t0\n"_format(regRes)
                                  << "\tbne\t${},\t$zero,\t{}\n"_format(regL, pass)
                                  << "\taddiu\t${},\t$zero,\t0\n"_format(regRes)
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << pass << ":\n"
                                  << "\taddiu\t${},\t$zero,\t1\n"_format(regRes)
                                  << end << ":\n";
  }  
  else if(op == "<"){
    *global_context->get_stream() << "\tslt\t${},\t${},\t${}\n"_format(regRes, regL, regR);
  }
  else if(op == ">"){
    *global_context->get_stream() << "\tslt\t${},\t${},\t${}\n"_format(regRes, regR, regL);
  }
  else if(op == "<="){
    *global_context->get_stream() << "\taddiu\t${0},\t${0},\t1\n"_format(regR)
                                  << "\tslt\t${},\t${},\t${}\n"_format(regRes, regL, regR);
  }
  else if(op == ">="){
    *global_context->get_stream() << "\taddiu\t${0},\t{0},\t1\n"_format(regL)
                                  << "\tslt\t${},\t${},\t${}\n"_format(regRes, regR, regL);
  }
}
void BinaryOperation::mipsPrintOp(int regL, int regR){
  if (op == "="){
    *global_context->get_stream() << "\tmove\t${},\t${}\n"_format(regL, regR);
  }
  else if (op == "+="){
    *global_context->get_stream() << "\taddu\t${},\t${},\t${}\n"_format(regL, regL, regR);
  }
  else if (op == "-="){
    *global_context->get_stream() << "\tsubu\t${},\t${},\t${}\n"_format(regL, regL, regR);
  }
  else if(op == "<<="){
    *global_context->get_stream() << "\tsllv\t${},\t${},\t${}\n"_format(regL, regL, regR);
  }
  else if(op == ">>="){
    *global_context->get_stream() << "\tsrlv\t${},\t${},\t${}\n"_format(regL, regL, regR);
  }
  else if(op == "&="){
    *global_context->get_stream() << "\tand\t${},\t${},\t${}\n"_format(regL, regL, regR);
  }
  else if(op == "|="){
    *global_context->get_stream() << "\tor\t${},\t${},\t${}\n"_format(regL, regL, regR);
  }
  else if(op == "^="){
    *global_context->get_stream() << "\txor\t${},\t${},\t${}\n"_format(regL, regL, regR);
  }
  else if(op == "*="){
    *global_context->get_stream() << "\tmultu\t${},\t${}\n"_format(regL,regR)
                                  << "\tmflo\t${}\n"_format(regL)
                                  << "\tnop\n"
                                  << "\tnop\n";
  }
  else if(op == "/="){
    *global_context->get_stream() << "\tdivu\t${},\t${}\n"_format(regL,regR)
                                  << "\tmflo\t${}\n"_format(regL)
                                  << "\tnop\n"
                                  << "\tnop\n";    
  }
  else if(op == "%="){
    *global_context->get_stream() << "\tdivu\t${},\t${}\n"_format(regL,regR)
                                  << "\tmfhi\t${}\n"_format(regL)
                                  << "\tnop\n"
                                  << "\tnop\n";    
  }
}
SizeOfOp::SizeOfOp(){};
void SizeOfOp::mipsPrint(ChunkPtr res){
  int regRes = res->load();
  *global_context->get_stream() << "\taddiu\t${},\t${},\t{}\n"_format(regRes,"zero",4);
  res->store();
}
