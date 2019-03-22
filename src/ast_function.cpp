#include "ast/ast_function.hpp"
#include "ast/ast_variable.hpp"

Function::Function(std::string *_decSpec, NodePtr _d, NodePtr _s)
    : returnType(*_decSpec), statements(_s), decl(_d) {
  delete _decSpec;
};
void Function::pyPrint(std::ostream &os) {
  os << "def ";
  if (decl)
    decl->pyPrint(os);
  for (int i = 0; i < globalVarNames.size(); i++) {
    os << "\tglobal " << globalVarNames[i] << "\n";
  }
  if (statements)
    statements->pyPrint(os);
  os << "\n";
}
void Function::mipsPrint() {
  std::string f_name = decl->getName();
  decl->registerVariables();
  LOG << "entered function: " << returnType << " " << f_name << "\n";
  printPreamble(f_name);
  //LOG << "finished preamble\n";
  if (returnType == "int" && statements) {
    // std::string fpChunkName = saveFP();
    global_context->normalize_argument_chunks();
    statements->mipsPrint();
    // restoreFP(fpChunkName);
    //*global_context->get_stream() << "\tjr\t$31\n\tnop\n";
    printEnd(f_name);
  }
}
void Function::printPreamble(std::string &f_name) {
  *global_context->get_stream() << ".text\n"
                                << ".align 2\n"
                                << ".globl " << f_name << "\n"
                                << f_name << ":\n"
                                << "\taddiu\t$sp,$sp,-8\n"
                                << "\tsw\t$fp,4($sp)\n"
                                << "\tmove\t$fp,$sp\n";
}
void Function::printEnd(std::string &f_name) {
  *global_context->get_stream() << "\tmove $sp,$fp\n"
                                << "\tlw $fp,4($sp)\n"
                                << "\taddiu $sp,$sp,8\n"
                                << "\tjr $31\n"
                                << "\tnop\n";
}
std::string Function::saveFP() {
  // global_context->new_scope();
  *global_context->get_stream() << "\tmove\t$fp,\t$sp\n";

  std::string fpChunkName = makeUNQ("fpchunk");
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  auto FP = global_context->register_chunk(fpChunkName, integer_type);
  int regFP = FP->load();
  *global_context->get_stream() << "\tmove\t$" << regFP << ",\t$fp\n";
  FP->store();
  return fpChunkName;
}
void Function::restoreFP(std::string &cName) {
  auto FP = global_context->resolve_chunk(cName);
  int regFP = FP->load();
  *global_context->get_stream() << "\tmove\t$sp,\t$fp\n";
  *global_context->get_stream() << "\tmove\t$fp,\t$" << regFP << "\n";
  FP->discard();
  // global_context->del_scope();
}

FunctionCall::FunctionCall(NodePtr _exp, NodePtr _arg)
    : functionName(_exp), arguments(_arg){};

void FunctionCall::pyPrint(std::ostream &os) {
  if (dynamic_cast<Variable *>(functionName)) {
    functionName->pyPrint(os);
    os << "(";
    if (arguments)
      arguments->pyPrint(os);
    os << ")";
  } else {
    functionName->pyPrint(os);
  }
}

// 1. calculate size in bytes
// 2. sp = sp - size
// 3. save fp at top of the frame
// 4. overwrite framepointer with stack pointer
// 5. save all parameters from registers to stack

// to get size I need to store sizes of all the functions in context for ease of
// access - use the size from context when calculating size of each function
// function declared set to -1 to indicate that it has to be updated once
// function is calculated
//
