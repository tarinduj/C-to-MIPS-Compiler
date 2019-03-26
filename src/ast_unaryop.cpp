#include "ast/ast_unaryop.hpp"
#include "ast/ast_variable.hpp"

UnaryOperation::UnaryOperation(std::string *_op, NodePtr _exp)
    : op(*_op), expression(_exp) {
  delete _op;
}
void UnaryOperation::pyPrint(std::ostream &os) {
  os << op << "(";
  if (expression)
    expression->pyPrint(os);
  os << ")";
}
void UnaryOperation::mipsPrint(){
  LOG << "entered unary mipsprint without chunk\n";
  auto EXP = global_context->resolve_chunk(expression->getName());  if(expression) expression->mipsPrint(EXP);
  int regExp = EXP->load();
  mipsPrintOp(regExp);
  EXP->store();
}

void UnaryOperation::mipsPrint(ChunkPtr res){
  LOG << "entered unary mipsprint with chunk\n";
  ChunkPtr EXP;
  TypePtr integer_type = std::make_shared<PrimitiveType>();

  if(dynamic_cast<Variable*>(expression)) EXP = global_context->resolve_chunk(expression->getName());
  else{
    EXP = global_context->register_chunk(makeUNQ("__unary"), integer_type);
  } 
  //auto EXP = global_context->resolve_chunk(expression->getName());
  if(expression) expression->mipsPrint(EXP);
  int regExp = EXP->load();
  int regRes = res->load();
  mipsPrintOp(regExp);
  //*global_context->get_stream() << "\tmove\t$" << regRes << ",\t$" << regExp << "\n";
  *global_context->get_stream() << "\taddu\t$" << regRes << "\t,$zero,\t$" << regExp << "\n";
 
  res->store();
  EXP->store();
}

void UnaryOperation::mipsPrintOp(int regExp){
  if(op == "++"){
    *global_context->get_stream() << "\taddiu\t$" <<regExp << ",\t$" << regExp << ",\t1\n";
  }
  if(op == "--"){
    *global_context->get_stream() << "\taddiu\t$" <<regExp << ",\t$" << regExp << ",\t-1\n";
  }
  if(op == "+"){
    //do nothing
  }
  if(op == "-"){
    *global_context->get_stream() << "\tsubu\t$" <<regExp << ",\t$zero,\t$" << regExp << "\n";
  }
  if(op == "!"){
    *global_context->get_stream() << "\tbne\t$" <<regExp << ",\t$zero,\t12\n" //16?
                                  << "\taddiu\t$" <<regExp << ",\t$zero,\t1\n"
                                  << "\tb\t8\n" //4?
                                  << "\tnop\n"
                                  << "\taddiu\t$" <<regExp << ",\t$zero,\t0\n";
  //idk
  }
  if(op == "~"){
    *global_context->get_stream() << "\tnot\t$" <<regExp << ",\t$" << regExp << "\n";
  }
}

std::string UnaryOperation::getName(){
  return expression->getName();
}

std::string PostFixExpression::getName(){
  return expression->getName();
}

PostFixExpression::PostFixExpression(NodePtr _exp, std::string *_op): expression(_exp), op(*_op){
  delete _op;
}
void PostFixExpression::mipsPrint(){
  auto EXP = global_context->resolve_chunk(expression->getName());  if(expression) expression->mipsPrint(EXP);
  int regExp = EXP->load();
  mipsPrintOp(regExp);
  EXP->store();
}

void PostFixExpression::mipsPrint(ChunkPtr res){
  auto EXP = global_context->resolve_chunk(expression->getName());
  if(expression) expression->mipsPrint(EXP);
  int regExp = EXP->load();
  int regRes = res->load();
  *global_context->get_stream() << "\tmove\t$" << regRes << ",\t$" << regExp << "\n";
  mipsPrintOp(regExp);
  res->store();
  EXP->store();
}

void PostFixExpression::mipsPrintOp(int regExp){
  if(op == "++"){
    *global_context->get_stream() << "\taddiu\t$" <<regExp << ",\t$" << regExp << ",\t1\n";
  }
  if(op == "--"){
    *global_context->get_stream() << "\taddiu\t$" <<regExp << ",\t$" << regExp << ",\t-1\n";
  }
}