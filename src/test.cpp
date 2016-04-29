#include <iostream>
#include "binary_tree.hpp"
#include <stdlib.h>
#include <time.h>
int main() {

  srand (time(NULL));

  binary_tree<int> A;
  while (1) {
    for (size_t i = 0; i < 1500000; i++) A.insert( rand() % 500000 - 250000 );
    for (size_t i = 0; i < 5000000; i++) A.remove( rand() % 500000 - 250000 );
    A.print();
  }
  return 0;
}
