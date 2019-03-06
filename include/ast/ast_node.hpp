#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node
{
    public:

        Node();
        virtual ~Node() {}
        virtual void pyprint(std::ostream& o) const = 0;
        virtual void codegen(std::ostream& o) const = 0;
        virtual void print(std::ostream& o) const = 0;
};

typedef Node* NodePtr;


#endif
