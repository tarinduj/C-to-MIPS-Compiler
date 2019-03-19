#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

enum listType {INIT, INITDEC, PARAM, DECL, STAT, ARG_EXP};
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
  virtual void setType(listType t);
  virtual void getGlobal(std::vector<std::string>& v);
  virtual std::string getName();
  // virtual void setType(const std::string& s) = 0;
  // virtual std::string getID() const = 0;
  // virtual unsigned int getSize() const = 0;
};


// global declarations
extern int scopeCounter;
extern std::vector<std::string> globalVarNames;
extern void addIndent();
extern void delIndent();
extern void printIndent(std::ostream &os);
#endif
