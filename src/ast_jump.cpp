#include "ast/ast_jump.hpp"

Return::Return(NodePtr _r) : returnExp(_r){};
void Return::pyPrint(std::ostream &os) {
  os << "return ";
  if (returnExp) {
    returnExp->pyPrint(os);
  }
}
void Return::mipsPrint() { 
  if (returnExp){
    TypePtr integer_type = std::make_shared<PrimitiveType>();
    auto RET = global_context->register_chunk(makeUNQ("__retVal"), integer_type);
    returnExp->mipsPrint(RET);
    int retReg = RET->load();
    *global_context->get_stream() << "\tmove\t$2,\t$" << retReg << "\n";
    RET->store();
  }
  *global_context->get_stream() << "\tb\t" << return_to << "\n"
                                << "\tnop\n";
}