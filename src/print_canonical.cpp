#include "../include/ast.hpp"
#include <iostream>

int main()
{
    const Node *ast=parseAST();

    ast->pyprint(std::cout);
    std::cout<<std::endl;

    return 0;
}
