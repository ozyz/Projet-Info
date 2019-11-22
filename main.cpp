#include <iostream>
#include "circuit.h"
#include "node.h"

int main(int argc, char const *argv[]) {
  Circuit a("yo", "test.dot");
  bool tab[3];
  tab[0] = 1;
  tab[1]= 0;
  tab[2]= 1;
  a.parse();
  a.displayCircuit();
  a.setInputValues(tab);
  a.evaluate();
  return 0;
}
