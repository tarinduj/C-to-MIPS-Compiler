#ifndef NODE_HPP
#define NODE_HPP

#include <ostream>
#include <string>
#include <vector>

class Node;
typedef Node *NodePtr;

class Node {
public:
  Node();
  ~Node();
  virtual void pyPrint(std::ostream &os) = 0;
  virtual void mipsPrint(std::ostream &os) = 0;
  virtual void insert(NodePtr _n);
  virtual void insert(std::string *_n);
  virtual void getList(std::vector<NodePtr> &res) const;
  // virtual std::string getType() const = 0;
  // virtual void setType(const std::string& s) = 0;
  // virtual std::string getID() const = 0;
  // virtual unsigned int getSize() const = 0;
};

#endif
