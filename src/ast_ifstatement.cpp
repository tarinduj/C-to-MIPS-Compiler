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

void IfStatement::mipsPrint(){
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  std::string nbrUNQ = getUNQLabel();
  std::string elseLabel = "__elseIF" + nbrUNQ;
  std::string endLabel = "__endIF" + nbrUNQ;

  auto CON = global_context->register_chunk(makeUNQ("__IFcondition"), integer_type);
  if(condition) condition->mipsPrint(CON);
  int regCON = CON->load();
  *global_context->get_stream() << "\tbeq\t$" << regCON << ",\t$0,\t" << elseLabel << "\n";
  CON->discard();
  if(trueStatement) trueStatement->mipsPrint();
  *global_context->get_stream() << "\tj\t" << endLabel << "\n";
  *global_context->get_stream() << "\tnop\n";
  *global_context->get_stream() << elseLabel << ":\n";
  if(elseStatement) elseStatement->mipsPrint();
  *global_context->get_stream() << endLabel << ":\n";

}
