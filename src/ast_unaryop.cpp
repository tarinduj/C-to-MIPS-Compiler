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
  ChunkPtr EXP;
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  std::string nbr = getUNQLabel();
  if(dynamic_cast<Variable*>(expression)) EXP = global_context->resolve_chunk(expression->getName());
  else EXP = global_context->register_chunk("__unary"+nbr, integer_type);
  //auto EXP = global_context->resolve_chunk(expression->getName());  if(expression) expression->mipsPrint(EXP);
  if(expression) expression->mipsPrint(EXP);
  int regExp = EXP->load();
  mipsPrintOp(regExp, nbr);
  EXP->store();
}

void UnaryOperation::mipsPrint(ChunkPtr res){
  LOG << "entered unary mipsprint with chunk\n";
  ChunkPtr EXP;
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  std::string nbr = getUNQLabel();
  if(dynamic_cast<Variable*>(expression)) EXP = global_context->resolve_chunk(expression->getName());
  else EXP = global_context->register_chunk("__unary"+nbr, integer_type);
  //auto EXP = global_context->resolve_chunk(expression->getName());
  if(expression) expression->mipsPrint(EXP);
  int regExp = EXP->load();
  int regRes = res->load();
  mipsPrintOp(regExp, nbr);
  //*global_context->get_stream() << "\tmove\t$" << regRes << ",\t$" << regExp << "\n";
  *global_context->get_stream() << "\taddu\t$" << regRes << "\t,$zero,\t$" << regExp << "\n";
 
  res->store();
  EXP->store();
}

void UnaryOperation::mipsPrintOp(int regExp, const std::string& nbr){
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
    std::string end = "__unary_end" + nbr;
    std::string gtz = "__unary_gtz" + nbr;
    *global_context->get_stream() << "\tbne\t$" <<regExp << ",\t$zero,\t" << gtz << "\n"
                                  << "\tnop\n" //16?
                                  << "\taddiu\t$" <<regExp << ",\t$zero,\t1\n"
                                  << "\tb\t" << end << "\n"
                                  << "\tnop\n"
                                  << gtz <<":\taddu\t$" <<regExp << ",\t$zero,\t$zero\n"
                                  << end << ":\n";
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