#pragma once //Compilar una vez
#include "list.hpp"
template <typename Type> class binary_tree {
  node<Type> *root , *father;
  list<Type> *linked_list;
  void remove_node( node<Type>* );
  void swap( node<Type>*, node<Type>* ); //El swap es privado ya que del modo que funciona sólo yo debo usarlo.
public:
  binary_tree() : root(NULL), father(NULL) { linked_list = new list<Type>; }
  ~binary_tree() {}
  bool insert( Type );
  node<Type> *search( Type );
  bool remove( Type );
  void print() {linked_list->print();}
};
template <typename Type> bool binary_tree<Type>::remove( Type key ) {
  node<Type> *leaf;
  if ( !(leaf = search(key)) ) return false;
  if ( leaf->right_child && leaf->left_child ) swap(leaf, leaf->next); //Si tiene dos hijos lo cambiamos y ahora tiene 1 ó 0
  if ( !leaf->right_child && !leaf->left_child ) { //Caso sin hijos
    if (leaf->father) //Para distuinguir del root (este no es el root)
      if (leaf->father->right_child == leaf) leaf->father->right_child = NULL; // Desconectamos
      else leaf->father->left_child = NULL; //Desconectamos
    else root = NULL;
  } else { //Caso con un hijo
    if ( root == leaf ) { //Caso especial cuando está el root y sólo hijo (Reasignar el root)
      if (leaf->right_child) root = leaf->right_child;
      else root = leaf->left_child;
      root->father = NULL;
    }
    remove_node(leaf); //Removemos el nodo (un hijo)
  }
  linked_list->remove(leaf); //Sacamos de la lista
  delete leaf;
  return true;
}
template <typename Type> void binary_tree<Type>::swap( node<Type>* n, node<Type>*m ) {
  if (root == n) root = m; //Si se ocupa cambiamos la root
  //Partimos de la idea principal que n siempre está arriba en nivel de m.
  //Esto esta garantizado.
  //Como el hijo izquierdo de m es nulo ya que buscamos al siguiente por la derecha y el de n siempre existe entonces:
  m->left_child = n->left_child; //Le decimos a m quién es su hijo izquierdo.
  m->left_child->father = m; //Le decimos al hijo izquierdo quien es su verdadero padre (spoiler)
  n->left_child = NULL; //Le quitamos a n su hijo izquierdo (Y sin dejar ir a visitarlo)
  //Ahora el hijo derecho de m puede o no existir así que vamos a usar una variable para manejarlo
  node<Type>* aux = m->right_child;
  //Checamos si el hijo derecho de n es distinto de m, para ponerle a m un nuevo hijo derecho
  if (n->right_child != m){
    m->right_child = n->right_child;
    m->right_child->father = m;
  }
  else m->right_child = n;
  //Ahora vamos a ponerle el antiguo hijo derecho de m (aux) a n, si este existe le decimos quien es su padre también
  n->right_child = aux;
  if (aux) aux->father = n;
  //Ahora vamos a intercambiar los padres de m y n.
  //Sabemos que el padre de m existe y el de n puede no existir
  //Guardaremos el de n, por ejemplo.
  aux = n->father;
  //Ahora si el padre de m es distinto de n, le asignamos a n ese padre, sino le ponemos m
  if (m->father != n) {
    n->father = m->father;
    n->father->left_child = n;
  } else n->father = m;
  //Asignamos el padre de m
  m->father = aux;
  //Si ese padre existe le decimos quién es su nuevo hijo izquierdo o derecho.
  if (m->father)
    if (m->father->right_child == n) m->father->right_child = m;
    else m->father->left_child = m;
}
template <typename Type> void binary_tree<Type>::remove_node( node<Type>* leaf ) {
  if (!leaf->father) return; //Si es la root no nos preocupamos
  if (leaf->father->right_child == leaf) //Desconectar del padre el hijo derecho
    if (leaf->right_child) { //Sabemos que tiene un hijo, así que checamos cuál es y lo ponemos al padre
      leaf->father->right_child = leaf->right_child;
      leaf->right_child->father = leaf->father;
    }
    else {
      leaf->father->right_child = leaf->left_child;
      leaf->left_child->father = leaf->father;
    }
  else if (leaf->father->left_child == leaf) //Sino el izquierdo. (Se checa ya que puede no existir)
    if (leaf->right_child) { //Checar línea 76
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
  if ( search( key ) ) return false;
  node<Type> * leaf = new node<Type>(key, father);
  if (!father) { linked_list->begin = leaf; root = leaf; return true; }
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
