#ifndef AST_BINOP_HPP
#define AST_BINOP_HPP
#include <string>
#include "ast_node.hpp"



class BinaryOperation: public Node
{
private:
    NodePtr _left;
    NodePtr _right;
    std::string op;
public:
    BinaryOperation(NodePtr left, std::string* opPtr, NodePtr right);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
    void insert(NodePtr _n){}//;
};

class SizeOfOp: public Node
{
private:
    int size;
    NodePtr _exp;
    std::string typeName;
public:
    SizeOfOp(NodePtr exp);
    SizeOfOp(std::string* t);
    void pyPrint(std::ostream& _o){}//;
    void mipsPrint(std::ostream& _o){}//;
    void insert(NodePtr _n){}//;
};

#endif