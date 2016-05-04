#include <iostream>
#include "binary_tree.hpp"
#include <stdlib.h>
#include <time.h>
int main() {
  srand (time(NULL));
  binary_tree<int> A;

  while (true) {
    for (size_t i = 0; i < 15000; i++) A.insert( rand() % 25000 + 1 );
    for (size_t i = 0; i < 50000; i++) A.remove( rand() % 25000 + 1 );
    A.print();
  }
  return 0;
}
