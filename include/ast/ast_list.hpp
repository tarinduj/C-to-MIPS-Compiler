#ifndef AST_LIST_HPP
#define AST_LIST_HPP

#include "ast_node.hpp"
#include <vector>

class List : public Node {
private:
  std::vector<NodePtr> elements;
  listType type;

public:
  List();
  void insert(NodePtr _n);
  void pyPrint(std::ostream &_o); //; when implementing delete {} and leave ;
  void mipsPrint();
  void getList(std::vector<NodePtr> &res);
  void setType(listType t);
  void getGlobal(std::vector<std::string> &v);
  void registerVariables();
};

class Scope : public Node {
private:
  NodePtr decList = NULL;
  NodePtr statList = NULL;
public:
  Scope(NodePtr _lst1, NodePtr _lst2); // concatenate two lists. it is for
                                       // declaration_list statement_list
  Scope(NodePtr _lst);
  void insert(NodePtr _n) {}
  void pyPrint(std::ostream &os); //; when implementing delete {} and leave ;
  void mipsPrint();
  void mipsPrint(ChunkPtr ret){}
};

class IdentifierList : public Node {
private:
  std::vector<std::string> identifiers;

public:
  IdentifierList();
  void insert(NodePtr _n) {}
  void insert(std::string *_n);
  void pyPrint(std::ostream &_o); //; when implementing delete {} and leave ;
  void mipsPrint(std::ostream &_o) {} //;
};

#endif
