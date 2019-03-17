#include "ast/ast_list.hpp"

List::List() {}
void List::insert(NodePtr _n) { elements.push_back(_n); }
void List::getList(std::vector<NodePtr> &res) { res = elements; }
void List::pyPrint(std::ostream &os) {
  for (int i = 0; i < elements.size(); i++) {
    if (elements[i]) {
      // os<<type<<": ";
      if (i != 0 && type == "init")
        printIndent(os);
      if (type != "init")
        printIndent(os);
      elements[i]->pyPrint(os);
      if (elements.size() != 0 && i < elements.size() - 1) {
        os << "\n";
      }
    }
  }
}
void List::setType(std::string *_t) {
  type = *_t;
  delete _t;
}

void List::getDeclaredVarNames(std::vector<std::string> &v) const {
  if (type == "init") {
    for (int i = 0; i < elements.size(); i++) {
      if (elements[i]) {
        elements[i]->getDeclaredVarNames(v);
      }
    }
  }
}

Scope::Scope(NodePtr _lst) : statList(_lst){};
Scope::Scope(NodePtr _lst1, NodePtr _lst2) : decList(_lst1), statList(_lst2){};
void Scope::pyPrint(std::ostream &os) {
  addIndent();
  // os<<"decList: ";
  if (decList)
    decList->pyPrint(os);
  os << "\n";
  // os<<"statList: ";
  if (statList)
    statList->pyPrint(os);
  delIndent();
}

IdentifierList::IdentifierList(){};
void IdentifierList::insert(std::string *_n) {
  identifiers.push_back(*_n);
  delete _n;
};