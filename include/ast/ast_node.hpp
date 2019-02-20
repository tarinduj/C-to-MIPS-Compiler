#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node
{
    public:
        virtual ~Node() {}
        virtual void pyprint(std::ostream& outfile) const = 0;
}

#endif
