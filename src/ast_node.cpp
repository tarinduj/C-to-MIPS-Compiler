#include "ast/ast_node.hpp"

Node::Node(){};
Node::~Node(){};
void Node::mipsPrint(ChunkPtr ret){};
void Node::mipsPrint(){};
void Node::insert(NodePtr _n){};
void Node::insert(std::string *_n){};
void Node::getList(std::vector<NodePtr> &res) const {};
void Node::setType(listType t){};
void Node::getGlobal(std::vector<std::string> &v){};
int Node::getVal(){};
std::string Node::getName() { return ""; };
int Node::getSize(){};
void Node::registerSingleVar(){};
void Node::registerVariables(){};


int scopeCounter = 0;
std::vector<std::string> globalVarNames;
bool elif = 0;
unsigned unq = 0;
bool registerGlobal = 1;
void addIndent() { scopeCounter++; }
void delIndent() { scopeCounter--; }
void printIndent(std::ostream &os) { os << std::string(scopeCounter, '\t'); }
void startELIF() { elif = 1; }
void endELIF() { elif = 0; }
std::string makeUNQ(std::string s){ return (s + std::to_string(unq++)); }