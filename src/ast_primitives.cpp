#include "ast/ast_primitives.hpp"

IntConst::IntConst(int _v) : val(_v) {}
void IntConst::pyPrint(std::ostream &os) { os << val; }
int IntConst::getVal() { return val; }
void IntConst::mipsPrint(ChunkPtr res){
  int regRes = res->load();
  *global_context->get_stream() << "\tli\t,$"<< regRes << ",\t" << val << "\n";
  res->store();
}
FloatConst::FloatConst(double _v) : val(_v) {}
CharConst::CharConst(int _v) : val(_v){};
String::String(std::string *_v) : val(*_v) { delete _v; }
