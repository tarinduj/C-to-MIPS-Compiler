#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "ast_node.hpp"
#include <string>

class Expression;

typedef const Expression* ExpressionPtr;


class Expression : public Node
{
protected:
    std::string op;
    ExpressionPtr _left;
    ExpressionPtr _right;    
public:
    Expression(std::string* in_op): op(*in_op){}
    Expression(ExpressionPtr left, std::string* in_op, ExpressionPtr right): _left(left), op(*in_op), _right(right){}
    virtual void pyprint(std::ostream& outfile) const;
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
        
    public:
        assignmentExpression(ExpressionPtr unaryExp, std::string* in_op, ExpressionPtr assignmentExp): Expression(unaryExp, in_op, assignmentExp) {}
        void pyprint(std::ostream& outfile) const {
            if(_left != NULL) _left->pyprint(outfile);
            outfile << op;
            if(_right != NULL) _right->pyprint(outfile);
        }
};

#endif
