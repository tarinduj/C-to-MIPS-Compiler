#ifndef AST_DECLARATOR_HPP
#define AST_DECLARAOTR_HPP

#include <string>
#include <vector>
#include "ast_node.hpp"

class DirectDeclarator: public Node
{
private:
    NodePtr dirDec;
    NodePtr paramList;
    std::string val;
public:
    DirectDeclarator(NodePtr _decl, NodePtr _list); //possibly add bolean to specify whether its a function or array
    void insert(NodePtr _n){}
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;   
    //std::string getID(); 
};

//pseudo for getID
//if decl->type = variable
//id = variable.val
//else decl->getID

class Declaration: public Node
{
private:
    std::string decSpec;
    NodePtr initDecList;
public:
    Declaration(std::string* _spec, NodePtr _list);
    void insert(NodePtr _n){}
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
};

class InitDeclarator: public Node
{
private:
    NodePtr declarator; //will store name of the variable/function
    NodePtr initializer; //expression so the value of variable which we pass as default
public:
    InitDeclarator(NodePtr _d, NodePtr _i);
    void insert(NodePtr _n){}
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
};

#endif