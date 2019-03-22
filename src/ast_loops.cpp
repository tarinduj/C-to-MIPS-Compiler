#include "ast/ast_loops.hpp"
#include "ast/ast_list.hpp"

WhileLoop::WhileLoop(NodePtr _c, NodePtr _s) : condition(_c), statement(_s){};
void WhileLoop::pyPrint(std::ostream &os) {
  os << "while (";
  condition->pyPrint(os);
  os << "):\n";
  pyPrintStatement(os, statement);
}
void WhileLoop::pyPrintStatement(std::ostream &os, NodePtr s) {
  if (dynamic_cast<Scope *>(s)) {
    s->pyPrint(os);
  } else {
    addIndent();
    printIndent(os);
    s->pyPrint(os);
    delIndent();
  }
}

void WhileLoop::mipsPrint(){
  TypePtr type = std::make_shared<PrimitiveType>();
  std::string nbrUNQ = getUNQLabel();
  std::string begin = "__beginWHILE" + nbrUNQ;
  std::string end = "__endWHILE" + nbrUNQ;

  auto CON = global_context->register_chunk(makeUNQ("__WHILEcondition"), type);
  *global_context->get_stream() << begin << ":\n";
  condition->mipsPrint(CON);
  int regC = CON->load();
  *global_context->get_stream() << "\tbeq\t$zero,\t$" << regC << ",\t" << end <<"\n"
                                << "\tnop\n";
  statement->mipsPrint();
  *global_context->get_stream() << "\tb\t" << begin <<"\n"
                                << "\tnop\n"
                                << end << ":\n";
  CON->discard();
}

DoWhileLoop::DoWhileLoop(NodePtr _s, NodePtr _c): condition(_c), statement(_s) {};
void DoWhileLoop::mipsPrint(){
  TypePtr type = std::make_shared<PrimitiveType>();
  std::string nbrUNQ = getUNQLabel();
  std::string begin = "__beginDOWHILE" + nbrUNQ;

  auto CON = global_context->register_chunk(makeUNQ("__DOWHILEcondition"), type);
  *global_context->get_stream() << begin << ":\n";
  statement->mipsPrint();
  int regC = CON->load();
  condition->mipsPrint(CON);
  *global_context->get_stream() << "\tbne\t$zero,\t$" << regC << ",\t" << begin <<"\n"
                                << "\tnop\n";
  CON->discard();
}

ForLoop::ForLoop(NodePtr _Left, NodePtr _Middle, NodePtr _Right, NodePtr _Stat): expressionL(_Left), expressionM(_Middle), expressionR(_Right), statement(_Stat) {};
void ForLoop::mipsPrint(){
  TypePtr type = std::make_shared<PrimitiveType>();
  std::string nbrUNQ = getUNQLabel();
  std::string begin = "__beginFOR" + nbrUNQ;
  std::string end = "__endFOR" + nbrUNQ;
  
  //auto CTR = global_context->register_chunk(makeUNQ("__FORcontrol"), type);
  auto CON = global_context->register_chunk(makeUNQ("__FORcondition"), type);
  if(expressionL) expressionL->mipsPrint();
  *global_context->get_stream() << "\tb\t" << end <<"\n"
                                << "\tnop\n";
  
  *global_context->get_stream() << begin << ":\n";
  statement->mipsPrint();
  expressionR->mipsPrint();

  *global_context->get_stream() << end << ":\n";  
  if(expressionM) expressionM->mipsPrint(CON);
  int regC = CON->load();
  *global_context->get_stream() << "\tbne\t$zero,\t$" << regC << ",\t" << begin <<"\n"
                                << "\tnop\n";
  CON->discard();
}