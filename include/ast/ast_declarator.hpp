#ifndef AST_DECLARATOR_HPP
#define AST_DECLARAOTR_HPP

#include <string>
#include <vector>
#include "ast_node.hpp"

class DirectDeclarator: public Node
{
private:
    std::string val;
    std::vector<NodePtr> parameters;
public:
    DirectDeclarator(std::string* _v);
    void insert(NodePtr _n);
    void pyPrint(std::ostream& _o){}//; when implementing delete {} and leave ;
    void mipsPrint(std::ostream& _o){}//;    
};

#endif