#include "ast/ast_jump.hpp"

Return::Return(NodePtr _r) : returnExp(_r){};
void Return::pyPrint(std::ostream &os) {
  os << "return ";
  if (returnExp) {
    returnExp->pyPrint(os);
  }
}