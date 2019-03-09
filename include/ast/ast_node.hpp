#ifndef NODE_HPP
#define NODE_HPP

#include <ostream>

class Node
{
    public:
        Node();
        ~Node(){}
        virtual void pyPrint(std::ostream& _o) const = 0;
        virtual void mipsPrint(std::ostream& _o) const = 0;
        virtual void insert(NodePtr _n) = 0;
        //virtual std::string getType() const = 0;
        //virtual void setType(const std::string& s) = 0;
        //virtual std::string getVal() const = 0;
        //virtual unsigned int getSize() const = 0;
};

typedef Node* NodePtr;


#endif
