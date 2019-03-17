#include "ast/ast_primitives.hpp"

IntConst::IntConst(int _v) : val(_v) {}
void IntConst::pyPrint(std::ostream &os) { os << val; }
FloatConst::FloatConst(double _v) : val(_v) {}
CharConst::CharConst(int _v) : val(_v){};
String::String(std::string *_v) : val(*_v) { delete _v; }
