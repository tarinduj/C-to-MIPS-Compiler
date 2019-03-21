#include "ast/ast_variable.hpp"

Variable::Variable(std::string *_s) : name(*_s) { delete _s; }
void Variable::pyPrint(std::ostream &os) { os << name; }
void Variable::mipsPrint(ChunkPtr res){
  auto tmp = global_context->resolve_chunk(name);
  int res_reg = res->load();
  int tmp_reg = tmp->load();
  *global_context->get_stream() << "\tmove\t$" << res_reg << ",\t$" << tmp_reg <<"\n";
  res->store();
}
std::string Variable::getName() { return name; }