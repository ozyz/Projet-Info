#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;


int main(){
  Node A("A", "AND2");
  Node B("B", "OR2");
  Node C("C", "OR2");
  A.setResult(0);
  B.setResult(0);
  cout << "A: "<< A.getResult()<< " B: " << B.getResult()<<endl;
  C.setInputs(A,B);
  C.computeOutput();

  cout << "Resultat :" << C.getResult() << endl;

  return 0;
}
