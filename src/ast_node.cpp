#include "ast/ast_node.hpp"

Node::Node(){};
Node::~Node(){};
void Node::insert(NodePtr _n){};
void Node::insert(std::string *_n){};
void Node::getList(std::vector<NodePtr> &res) const {};
void Node::setType(std::string *_t){};
void Node::getDeclaredVarNames(std::vector<std::string> &v) const {};
std::string Node::getName(){};

void addIndent() { scopeCounter++; }
void delIndent() { scopeCounter--; }
void printIndent(std::ostream &os) { os << std::string("\t", scopeCounter); }