#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;

int main(){
  Node A('A', AND2);
  Node B('B', OR2);
  Node C('C', OR2);
  setInput(A, B);
  setOuput(C);
  computeOutput();
}
