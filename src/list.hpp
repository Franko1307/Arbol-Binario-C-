#pragma once
#include "structures.hpp"
template <typename Type> class list {
public:
  node<Type> *begin;
  list() : begin(NULL){}
  ~list();
  bool insert_right( node<Type>*, node<Type>* );
  bool insert_left ( node<Type>*, node<Type>* );
  bool remove( node<Type>* );
  void print ();
};
template <typename Type> list<Type>::~list() {
  node<Type> *n;
  while (begin) {
    n = begin;
    begin = begin->next;
    delete n;
  }
}
template <typename Type> bool list<Type>::insert_right( node<Type> *previous, node<Type> *leaf ) {
  leaf->next = previous->next;
  leaf->previous = previous;
  previous->next = leaf;
  if (leaf->next) leaf->next->previous = leaf;
}
template <typename Type> bool list<Type>::insert_left( node<Type> *previous, node<Type> *leaf ) {
  leaf->previous = previous->previous;
  previous->previous = leaf;
  leaf->next = previous;
  if (!leaf->previous) begin = leaf;
  else leaf->previous->next = leaf;
}
template <typename Type> bool list<Type>::remove( node<Type> *leaf) {
  if (leaf->previous) leaf->previous->next = leaf->next;
  if (leaf->next) leaf->next->previous = leaf->previous;
  if (begin == leaf) begin = begin->next;        
}
template <typename Type> void list<Type>::print() {
  node<Type> *n = begin;
  std::cout << "List: " << std::endl;
  while (n) {
    std::cout << "Nodo: " << n->key << std::endl;
    if (n->father) std::cout << "Padre: " << n->father->key << std::endl;
    if (n->left_child) std::cout << "Hijo izquierdo: " << n->left_child->key << std::endl;
    if (n->right_child) std::cout << "Hijo derecho: " << n->right_child->key << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    n = n->next;
  }
  std::cout << "\b " << std::endl;
}
