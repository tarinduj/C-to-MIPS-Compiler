#ifndef AST_VARIABLE_HPP
#define AST_VARIABLE_HPP

#include "ast_node.hpp"

class Variable: public Node
{
private:
    std::string name;
public:
    Variable(std::string* _s);
};

#endif