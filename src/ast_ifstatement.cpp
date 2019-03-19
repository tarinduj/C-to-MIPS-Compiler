#include "ast/ast_ifstatement.hpp"
#include "ast/ast_list.hpp"

IfStatement::IfStatement(NodePtr _c, NodePtr _t, NodePtr _e)
    : condition(_c), trueStatement(_t), elseStatement(_e){};
void IfStatement::pyPrint(std::ostream &os) {
  if (!elif) {
    os << "if(";
  } else {
    os << "elif(";
    endELIF();
  }

  condition->pyPrint(os);
  os << "):\n";

  if (trueStatement) {
    pyPrintStatement(os, trueStatement);
  }

  if (elseStatement) {
    os << "\n";
    printIndent(os);
    if (dynamic_cast<IfStatement *>(elseStatement)) {
      startELIF();
      elseStatement->pyPrint(os);
    } else {
      os << "else:\n";
      pyPrintStatement(os, elseStatement);
    }
  }
}

void IfStatement::pyPrintStatement(std::ostream &os, NodePtr s) {
  if (dynamic_cast<Scope *>(s)) {
    s->pyPrint(os);
  } else {
    addIndent();
    printIndent(os);
    s->pyPrint(os);
    delIndent();
  }
}
