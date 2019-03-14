#include "ast/ast_variable.hpp"

Variable::Variable(std::string *_s) : name(*_s) { delete _s; }
void Variable::pyPrint(std::ostream& os){
  os<<name<<"\n";
}
