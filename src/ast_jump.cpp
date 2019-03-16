#include "ast/ast_jump.hpp"

Return::Return(NodePtr _r) : returnExp(_r){};
void Return::pyPrint(std::ostream& os){
  if(returnExp){
    os<<"return ";
    returnExp->pyPrint(os);
  } 
}