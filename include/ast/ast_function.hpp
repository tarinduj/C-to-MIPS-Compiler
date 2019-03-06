#ifndef AST_FUNCTION_HPP
#define AST_FUNCTION_HPP
#include <vector>
#include <string>
#include "ast_node.hpp"
class Function: public Node
{
private:
    NodePtr arguments;
    NodePtr statements;
    std::string returnType;
    std::string name;
public:
    FunctionDeclaration(std::string* _n, std::string* _r, NodePtr _arg, NodePtr _s): name(*_n), returnType(*_r), arguments(_arg), statements(_s) {};
    ~FunctionDeclaration();
    void print(std::ostream& o);
};


class FunctionCall: public Node
{
private:
    /* data */
public:
    FunctionCall(/* args */);
    ~FunctionCall();
};

class FunctionDeclaration: public Node
{
private:
    /* data */
public:
    Function(/* args */) { }
    ~Function() { }
};


#endif