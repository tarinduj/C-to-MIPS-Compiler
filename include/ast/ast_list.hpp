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
};

class Scope: public Node
{
private:
    std::vector<NodePtr> statements;
public:
    Scope();
    void insert(NodePtr _n);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;
};

#endif
