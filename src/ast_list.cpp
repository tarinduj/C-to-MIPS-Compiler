#include "ast/ast_list.hpp"

List::List() {}
void List::insert(NodePtr _n) { elements.push_back(_n); }
void List::getList(std::vector<NodePtr> &res) { res = elements; }
void List::pyPrint(std::ostream &os) {
  for (int i = 0; i < elements.size(); i++) {
    if (elements[i]) {
      switch (type) {
      case INITDEC: {
        if (i != 0)
          printIndent(os);
        elements[i]->pyPrint(os);
        if (elements.size() != 0 && i < elements.size() - 1)
          os << "\n";
        break;
      }
      case ARG_EXP:
      case PARAM: {
        elements[i]->pyPrint(os);
        if (elements.size() != 0 && i < elements.size() - 1)
          os << ", ";
        break;
      }
      default: {
        printIndent(os);
        elements[i]->pyPrint(os);
        if (elements.size() != 0 && i < elements.size() - 1)
          os << "\n";
        break;
      }
      }
    }
  }
}

void List::mipsPrint() {
  for (int i = 0; i < elements.size(); i++) {
    if (elements[i])
      elements[i]->mipsPrint();
  }
}

void List::setType(listType t) { type = t; };

void List::getGlobal(std::vector<std::string> &v) {
  for (int i = 0; i < elements.size(); i++) {
    if (elements[i])
      elements[i]->getGlobal(v);
  }
}

Scope::Scope(NodePtr _lst) : statList(_lst){};
Scope::Scope(NodePtr _lst1, NodePtr _lst2) : decList(_lst1), statList(_lst2){};
void Scope::pyPrint(std::ostream &os) {
  addIndent();
  if (decList == NULL && statList == NULL) {
    printIndent(os);
    os << "pass\n";
  } else {
    if (decList) {
      decList->pyPrint(os);
      os << "\n";
    }
    if (statList)
      statList->pyPrint(os);
  }
  delIndent();
}

IdentifierList::IdentifierList(){};
void IdentifierList::insert(std::string *_n) {
  identifiers.push_back(*_n);
  delete _n;
};
void IdentifierList::pyPrint(std::ostream &os) {
  for (int i = 0; i < identifiers.size(); i++) {
    os << identifiers[i] << "\n";
  }
}