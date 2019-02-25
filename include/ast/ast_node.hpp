#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node
{
    public:
        
        Node();
        virtual ~Node() {}
        virtual void pyprint(std::ostream& outfile) const = 0;
        virtual void codegen(std::ostream& outfile) const = 0;
        virtual void preetyprint() const = 0;
};

typedef const Node* NodePtr;

#endif
