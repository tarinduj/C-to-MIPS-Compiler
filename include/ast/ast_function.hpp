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
    std::string functionName;
public:
    Function(std::string* _r, std::string* _n, NodePtr _arg, NodePtr _s);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
    void insert(NodePtr _n){}//;
};


class FunctionCall: public Node
{
private:
    NodePtr arguments;
    std::string callName;  
public:
    FunctionCall(std::string* _n, NodePtr _arg);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
    void insert(NodePtr _n){}//;
};

class FunctionDeclaration: public Node
{
private:
    NodePtr arguments;
    std::string returnType;
    std::string functionName;
public:
    FunctionDeclaration(NodePtr _ret, std::string* _n, NodePtr _arg);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
    void insert(NodePtr _n){}//;
};


#endif