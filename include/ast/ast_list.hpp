#ifndef AST_LIST_HPP
#define AST_LIST_HPP

#include <vector>
#include "ast_node.hpp"

class List: public Node
{
private:
    std::vector<NodePtr> elements;
public:
    List();
    void insert(NodePtr _n);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
    void getList(std::vector<NodePtr>& res);
};

class Scope: public Node
{
private:
    std::vector<NodePtr> executionList;
public:
    Scope(NodePtr _lst1, NodePtr _lst2);
    Scope(NodePtr _lst);
    void insert(NodePtr _n);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
};

class IdentifierList: public Node
{
private:
    std::vector<std::string> identifiers;
public:
    IdentifierList();
    void insert(NodePtr _n){}
    void insert(std::string _n);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
};

#endif
