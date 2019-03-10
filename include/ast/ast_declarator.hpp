#ifndef AST_DECLARATOR_HPP
#define AST_DECLARAOTR_HPP

#include <string>
#include <vector>
#include "ast_node.hpp"

class DirectDeclarator: public Node
{
private:
    std::string val;
    NodePtr paramList;
public:
    DirectDeclarator(NodePtr _name, NodePtr _list);
    void insert(NodePtr _n){}
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;    
};

class Declaration: public Node
{
private:
public:
};

class InitDeclarator: public Node
{
private:
public:
};

#endif