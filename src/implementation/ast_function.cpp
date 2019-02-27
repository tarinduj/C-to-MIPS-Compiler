#include "ast.hpp"
void FunctionDeclaration::print(std::ostream& o){
    o << returnType << " " << name << "(";
    if(arguments != NULL) arguments->print(o);
    o << ") \n";
    if(statements != NULL) statements->print(o);
    }
