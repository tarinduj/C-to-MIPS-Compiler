#include "ast/ast_conditional.hpp"

ConditionalOperation::ConditionalOperation(NodePtr _c, NodePtr _t, NodePtr _f): condition(_c), trueExp(_t), falseExp(_f) {};
void ConditionalOperation::mipsPrint(ChunkPtr res){
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  std::string nbrUNQ = getUNQLabel();
  std::string falseLabel = "__condFALSE" + nbrUNQ;
  std::string endLabel = "__condEND" + nbrUNQ;
  //auto TR = global_context->register_chunk(makeUNQ("__Cond_T"), integer_type);
  //auto FA = global_context->register_chunk(makeUNQ("__Cond_F"), integer_type);
  if(condition) condition->mipsPrint(res);
  int regRes = res->load();
  *global_context->get_stream() << "\tbeq\t$" << regRes<< ",\t$0,\t" << falseLabel << "\n"
                                << "\tnop\n";
  res->discard();
  if(trueExp) trueExp->mipsPrint(res);
  *global_context->get_stream() << "\tj\t" << endLabel << "\n"
                                << "\tnop\n"
                                << falseLabel << ":\n";
  if(falseExp) falseExp->mipsPrint(res);
  *global_context->get_stream() << endLabel << ":\n";
}

// void ConditionalOperation::mipsPrint(){
//   TypePtr integer_type = std::make_shared<PrimitiveType>();
//   std::string nbrUNQ = getUNQLabel();
//   std::string falseLabel = "__condFALSE" + nbrUNQ;
//   std::string endLabel = "__condEND" + nbrUNQ;

//   auto CON = global_context->register_chunk(makeUNQ("__condExp"), integer_type);
//   if(condition) condition->mipsPrint(CON);
//   int regCON = CON->load();
//   *global_context->get_stream() << "\tbeq\t$" << regCON << ",\t$0,\t" << elseLabel << "\n"
//                                 << "\tnop\n";
//   CON->discard();
//   if(t_Exp) t_Exp->mipsPrint();
//   *global_context->get_stream() << "\tj\t" << endLabel << "\n";
//   *global_context->get_stream() << "\tnop\n";
//   *global_context->get_stream() << elseLabel << ":\n";
//   if(f_exp) f_exp->mipsPrint();
//   *global_context->get_stream() << endLabel << ":\n";

// }