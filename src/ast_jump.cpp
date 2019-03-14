#include "ast/ast_jump.hpp"

Return::Return(NodePtr _r) : returnExp(_r){};
void Return::pyPrint(std::ostream& os){
  os<<"\treturn printing\n";
  if(returnExp) returnExp->pyPrint(os);
  os << "\n";
}