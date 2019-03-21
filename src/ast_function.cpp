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
void Function::mipsPrint(){
  LOG << "entered function\n";
  std::string f_name = decl->getName();
  LOG << f_name << "\n";
}
void Function::printPreamble(std::string& f_name){
// .text
// .align 2
// .globl run
// .set nomips16
// .set nomicromips
// .ent run
// .type run, @function
// run:
// .frame $fp,8,$31 specify frame size
// .mask 0x40000000,-4
// .fmask 0x00000000,0
// .set noreorder
// .set nomacro
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

//to get size I need to store sizes of all the functions in context for ease of access - use the size from context when calculating size of each function
//function declared set to -1 to indicate that it has to be updated once function is calculated
//
