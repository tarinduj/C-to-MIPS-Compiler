#include "ast/ast_list.hpp"
#include "ast/ast_declarator.hpp"

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
  LOG << "printing list of type: " << type << "\n";
  LOG << "0.INIT, 1.INITDEC, 2.PARAM, 3.DECL, 4.STAT, 5.ARG_EXP \n";
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
void List::registerVariables() {
  for (int i = 0; i < elements.size(); i++) {
    if (elements[i]) {
      switch (type) {
      case INITDEC: {
        LOG << "regVariables initdec list\n";
        elements[i]->registerSingleVar();
        break;
      }
      case DECL: {
        LOG << "regVariables declaration list\n";
        elements[i]->registerVariables();
        break;
      }
      }
    }
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
void Scope::mipsPrint() {
  global_context->new_scope();
  if (decList)
    decList->registerVariables();
  if (statList)
    statList->mipsPrint();
  global_context->del_scope();
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