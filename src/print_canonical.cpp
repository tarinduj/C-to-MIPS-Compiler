#include "../include/ast.hpp"
#include <iostream>

int main()
{
    Node *ast=parseAST("test.c");

    ast->pyprint(std::cout);
    std::cout<<std::endl;

    return 0;
}
