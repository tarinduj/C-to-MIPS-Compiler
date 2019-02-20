#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>

class Expression;

typedef const Expression* ExpressionPtr;
typedef const Node* NodePtr;


class Expression : public Node
{
protected:
    std::string operator;
    ExpressionPtr _left;
    ExpressionPtr _right;    
public:
    Expression(std::string* op) {operator = *op;}
};

class unaryExpression : public Expression
{

};

class castExpression : public Expression
{

};

class multiplicativeExpression : public Expression
{

};

class additiveExpression : public Expression
{

};

class shiftExpression : public Expression
{

};

class relationalExpression : public Expression
{

};

class equalityExpression : public Expression
{

};

class andExpression : public Expression
{

};

class xorExpression : public Expression
{

};

class orExpression : public Expression
{

};

class logicalOrExpression : public Expression
{

};

class logicalAndExpression : public Expression
{

};

class conditionalExpression : public Expression
{

};

class assignmentExpression : public Expression
{
    protected:
        ExpressionPtr
    public:
        assignmentExpression(NodePtr unaryExp, std::string* op, NodePtr assignmentExp);
};

#endif
