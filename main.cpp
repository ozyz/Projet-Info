#include <iostream>
#include "circuit.h"
#include "node.h"

int main(int argc, char const *argv[]) {
  Circuit a("yo", "test.dot");
  a.parse();
  return 0;
}
