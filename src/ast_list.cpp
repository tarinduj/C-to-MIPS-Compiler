#include "ast/ast_list.hpp"

List::List() {}
void List::insert(NodePtr _n) { elements.push_back(_n); }
void List::getList(std::vector<NodePtr> &res) { res = elements; }
Scope::Scope(NodePtr _lst) : statList(_lst){};
Scope::Scope(NodePtr _lst1, NodePtr _lst2) : decList(_lst1), statList(_lst2){};

IdentifierList::IdentifierList(){};
void IdentifierList::insert(std::string *_n) {
  identifiers.push_back(*_n);
  delete _n;
};