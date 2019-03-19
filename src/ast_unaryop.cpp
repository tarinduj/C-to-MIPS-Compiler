#include "ast/ast_unaryop.hpp"

UnaryOperation::UnaryOperation(std::string* _op, NodePtr _exp): op(*_op), expression(_exp){
    delete _op;
  }
void UnaryOperation::pyPrint(std::ostream& os){
  os << op <<"(";
  if(expression) expression->pyPrint(os);
  os << ")";
}