#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "chunk.hpp"
#include "run.hpp"
#include "context.hpp"
#include "fmt/format.h"

enum listType { INIT, INITDEC, PARAM, DECL, STAT, ARG_EXP };
class Node;
typedef Node *NodePtr;

class Node {

public:
  Node();
  ~Node();
  virtual void pyPrint(std::ostream &os) = 0;
  virtual void mipsPrint(ChunkPtr ret);
  virtual void mipsPrint();
  virtual void insert(NodePtr _n);
  virtual void insert(std::string *_n);
  virtual void getList(std::vector<NodePtr> &res) const;
  virtual void setType(listType t);
  virtual void getGlobal(std::vector<std::string> &v);
  virtual std::string getName();
  virtual int getVal();
  // virtual void setType(const std::string& s) = 0;
  // virtual std::string getID() const = 0;
  // virtual unsigned int getSize() const = 0;
};

// global declarations
extern int scopeCounter;
extern std::vector<std::string> globalVarNames;
extern bool elif;
extern void addIndent();
extern void delIndent();
extern void printIndent(std::ostream &os);
extern void startELIF();
extern void endELIF();
#endif
