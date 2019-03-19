#include "ast/ast_node.hpp"

Node::Node(){};
Node::~Node(){};
void Node::insert(NodePtr _n){};
void Node::insert(std::string *_n){};
void Node::getList(std::vector<NodePtr> &res) const {};
void Node::setType(listType t){};
void Node::getGlobal(std::vector<std::string>& v){};
std::string Node::getName(){return "";};
void addIndent() { scopeCounter++;}
void delIndent() { scopeCounter--;}
void printIndent(std::ostream &os) { os << std::string(scopeCounter, '\t'); }