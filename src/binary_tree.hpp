#pragma once
#include "list.hpp"
template <typename Type> class binary_tree {
  node<Type> *root , *father;
  list<Type> *linked_list;
  void remove_node( node<Type>* );
public:
  binary_tree() : root(NULL), father(NULL) { linked_list = new list<Type>;}
  ~binary_tree() {}
  bool insert( Type );
  void swap( node<Type>*, node<Type>* );
  node<Type> *search( Type );
  bool remove( Type );
  void print() {linked_list->print();}
};
template <typename Type> bool binary_tree<Type>::remove( Type key ) {
  node<Type> *leaf;
  if ( !(leaf = search(key)) ) return false;
  if ( leaf->right_child && leaf->left_child ) swap(leaf, leaf->next);
  if ( !leaf->right_child && !leaf->left_child )
    if (leaf->father)
      if (leaf->father->right_child == leaf) leaf->father->right_child = NULL;
      else leaf->father->left_child = NULL;
    else root = NULL;
  else {
    if ( root == leaf ) {
      if (leaf->right_child) root = leaf->right_child;
      else root = leaf->left_child;
      root->father = NULL;
    }
    remove_node(leaf);
  }
  linked_list->remove(leaf);
  delete leaf;
  return true;
}
template <typename Type> void binary_tree<Type>::swap( node<Type>* n, node<Type>*m ) {
  node<Type>*aux;
  if (n->father == m) {
    aux = n;
    n = m;
    m = aux;
  }
  if (root == n) root = m;

  aux = m->left_child;
  if (n->left_child == m) m->left_child = n;
  else m->left_child = n->left_child;
  n->left_child = aux;

  aux = m->right_child;
  if (n->right_child == m) m->right_child = n;
  else m->right_child = n->right_child;
  n->right_child = aux;

  aux = n->father;
  if (m->father == n) n->father = m;
  else n->father = m->father;
  m->father = aux;

  if (n->left_child) n->left_child->father = n;
  if (m->left_child) m->left_child->father = m;
  if (n->right_child) n->right_child->father = n;
  if (m->right_child) m->right_child->father = m;
  if (n->father)
    if (n->father->right_child == m) n->father->right_child = n;
    else if (n->father->left_child == m) n->father->left_child = n;
  if (m->father)
    if (m->father->right_child == n) m->father->right_child = m;
    else if (m->father->left_child == n) m->father->left_child = m;
}
template <typename Type> void binary_tree<Type>::remove_node( node<Type>* leaf ) {
  if (!leaf->father) return;
  if (leaf->father->right_child == leaf)
    if (leaf->right_child) {
      leaf->father->right_child = leaf->right_child;
      leaf->right_child->father = leaf->father;
    }
    else {
      leaf->father->right_child = leaf->left_child;
      leaf->left_child->father = leaf->father;
    }
  else if (leaf->father->left_child == leaf)
    if (leaf->right_child) {
      leaf->father->left_child = leaf->right_child;
      leaf->right_child->father = leaf->father;
    }
    else {
      leaf->father->left_child = leaf->left_child;
      leaf->left_child->father = leaf->father;
    }
}
template <typename Type> node<Type> *binary_tree<Type>::search( Type key) {
  node<Type> *n = root;
  father = NULL;
  while (n) {
    if ( *n < key ) { father = n; n = n->right_child; }
    else if ( *n > key ) { father = n; n = n->left_child; }
    else return n;
  }
  return NULL;
}
template <typename Type> bool binary_tree<Type>::insert( Type key ) {
  if (search(key)) return false;
  node<Type> *leaf = new node<Type>(key, father);
  if (!father) {
    linked_list->begin = leaf;
    root = leaf;
    return true;
  }
  if ( *father < key ) {
    father->right_child = leaf;
    linked_list->insert_right(father,leaf);
  }
  else {
    father->left_child = leaf;
    linked_list->insert_left(father,leaf);
  }
  return true;
}
