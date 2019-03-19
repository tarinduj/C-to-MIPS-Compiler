#include "ast/ast_loops.hpp"
#include "ast/ast_list.hpp"

WhileLoop::WhileLoop(NodePtr _c, NodePtr _s):
  condition(_c), statement(_s){};
void WhileLoop::pyPrint(std::ostream& os){
  os << "while (";
  condition->pyPrint(os);
  os << "):\n";
  pyPrintStatement(os, statement);
}
void WhileLoop::pyPrintStatement(std::ostream& os, NodePtr s){
  if(dynamic_cast<Scope*>(s)){
    s->pyPrint(os);
  }
  else{
    addIndent();
    printIndent(os);
    s->pyPrint(os);
    delIndent();
  }
}