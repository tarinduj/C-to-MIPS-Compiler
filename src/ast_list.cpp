#include "ast/ast_list.hpp"

List::List() {}
void List::insert(NodePtr _n) { elements.push_back(_n); }
void List::getList(std::vector<NodePtr> &res) { res = elements; }
void List::pyPrint(std::ostream& os){
  os<<"\tlist printing\n";
  for(int i = 0; i < elements.size(); i++){
    if(elements[i]) elements[i]->pyPrint(os);
  }
}

Scope::Scope(NodePtr _lst) : statList(_lst){};
Scope::Scope(NodePtr _lst1, NodePtr _lst2) : decList(_lst1), statList(_lst2){};
void Scope::pyPrint(std::ostream& os){
  os<<"\tscope printing\n";
  if(decList) {os<<"decList: \n"; decList->pyPrint(os);}
  if(statList) {os<<"statList: \n"; statList->pyPrint(os);}
}

IdentifierList::IdentifierList(){};
void IdentifierList::insert(std::string *_n) {
  identifiers.push_back(*_n);
  delete _n;
};