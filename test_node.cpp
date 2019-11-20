#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;

int main(){
  Node A("A", "AND_2");
  Node B("B", "OR_2");
  Node C("C", "AND_2");
  Node D("D", "AND_2");

  //Affichage des valeurs des Nodes A et B
  A.setResult(1);
  B.setResult(0);
  D.setResult(1);
  cout << "A: "<< A.getResult()<< " B: " << B.getResult()<< " C: " << C.getResult() << " D: " << D.getResult() << endl << endl;

  //Test AND_2
  cout << "TEST AND_2" << endl; //le type de C est déjà défini avant au début du main
  C.addInput(0,A);
  C.addInput(1,B);
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;

  //Test OR_2
  cout << "TEST OR_2" << endl;
  C.setType("OR_2");
  C.addInput(0,A);
  C.addInput(1,B);
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;

  //Test NOT_2
  cout << "TEST NOT" << endl;
  C.setType("NOT");
  C.addInput(0,A);
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;

  //Test XOR_2
  cout << "TEST XOR_2" << endl;
  C.setType("XOR_2");
  C.addInput(0,A);
  C.addInput(1,B);
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;

  //Test MUX_2
  cout << "TEST MUX_2" << endl;
  C.setType("MUX_2");
  C.addInput(0,D);
  C.addInput(1,A);
  C.addInput(2,B);                                       //On met D en premier car c'est la variable de sélection
  C.computeOutput();
  cout << "Resultat :" << C.getResult() << endl << endl;


  return 0;
}
