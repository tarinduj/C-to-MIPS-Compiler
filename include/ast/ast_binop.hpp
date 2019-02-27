#ifndef AST_BINOP_HPP
#define AST_BINOP_HPP
#include <string>
#include "../declarations.hpp"


class BinaryOperation: public Node
{
private:
    NodePtr _left;
    NodePtr _right;
    std::string op;
public:
    BinaryOperation(NodePtr left, std::string* opPtr, NodePtr right): _left(left), _right(right), op(*opPtr) { }
    ~BinaryOperation() { }
};

#endif