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
}