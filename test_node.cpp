#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;


int main(){
  Node A("A", "AND_2");
  Node B("B", "OR_2");
  Node D("D", "AND_2");

  //Affichage des valeurs des Nodes A et B
  A.setResult(0);
  B.setResult(0);
  cout << "A: "<< A.getResult()<< " B: " << B.getResult()<<endl<<endl;

  //Test AND_2
  cout << "TEST AND_2" << endl;
  Node C("C", "AND_2");
  C.setInputs(A,B,D);
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;

  //Test OR_2
  cout << "TEST AND_2" << endl;
  Node C("C", "OR_2");
  C.setInputs(A,B,D);
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;

  //Test NOT_2
  cout << "TEST NOT_2" << endl;
  Node C("C", "NOT_2");
  C.setInputs(A,B,D);
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;

  //Test XOR_2
  cout << "TEST XOR_2" << endl;
  Node C("C", "XOR_2");
  C.setInputs(A,B,D);
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;

  //Test MUX_2
  cout << "TEST MUX_2" << endl;
  Node C("C", "MUX_2");
  C.setInputs(D,A,B);                                                           //On met D en premier car c'est la variable de sélection
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;


  return 0;
}
