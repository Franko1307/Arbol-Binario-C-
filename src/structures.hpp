#pragma once
#include <iostream>
template <typename Type> class node {
public:
  Type key;
  node<Type> *father;
  node<Type> *next;
  node<Type> *previous;
  node<Type> *right_child;
  node<Type> *left_child;
  node ( Type key , node<Type> *father ) :  key(key), father(father), next(NULL)
      ,previous(NULL), right_child(NULL), left_child(NULL) {}
  ~node() { father = NULL; next = NULL; previous = NULL; right_child = NULL; left_child = NULL; }
  bool operator == (Type key) { return this->key == key; }
  bool operator != (Type key) { return this->key != key; }
  bool operator < (Type key) { return this->key < key; }
  bool operator > (Type key) { return this->key > key; }
};
