#ifndef AST_FUNCTION_HPP
#define AST_FUNCTION_HPP
#include <vector>
#include <string>
#include "../declarations.hpp"

class FunctionDeclaration: public Node
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


class FunctionCall
{
private:
    /* data */
public:
    FunctionCall(/* args */);
    ~FunctionCall();
};

#endif