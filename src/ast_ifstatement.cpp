#include "ast/ast_ifstatement.hpp"
#include "ast/ast_list.hpp"

IfStatement::IfStatement(NodePtr _c, NodePtr _t, NodePtr _e):
  condition(_c), trueStatement(_t), elseStatement(_e) {};
void IfStatement::pyPrint(std::ostream& os){
  os << "if(";
  condition->pyPrint(os);
  os << "):\n";
  pyPrintStatement(os, trueStatement);
  if(elseStatement){
    os << "\n";
    printIndent(os);
    os << "else:\n";
    pyPrintStatement(os, elseStatement);
  }
}

void IfStatement::pyPrintStatement(std::ostream& os, NodePtr s){
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
