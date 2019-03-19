#include "ast/ast_ifstatement.hpp"
#include "ast/ast_list.hpp"

IfStatement::IfStatement(NodePtr _c, NodePtr _t, NodePtr _e):
  condition(_c), trueStatement(_t), elseStatement(_e) {};
void IfStatement::pyPrint(std::ostream& os){
  os << "if(";
  condition->pyPrint(os);
  os << "):\n";

  // if(dynamic_cast<Scope*>(trueStatement)){
  //   trueStatement->pyPrint(os);
  // }
  // else{
  //   addIndent();
  //   trueStatement->pyPrint(os);
  //   delIndent();
  // }
  pyPrintStatement(os, trueStatement);

  if(elseStatement){
    os << "else:\n";
    //addIndent();
    //elseStatement->pyPrint(os);
    //delIndent();
    pyPrintStatement(os, elseStatement);
  }
}

void IfStatement::pyPrintStatement(std::ostream& os, NodePtr s){
  if(dynamic_cast<Scope*>(s)){
    s->pyPrint(os);
  }
  else{
    addIndent();
    s->pyPrint(os);
    delIndent();
  }
}
