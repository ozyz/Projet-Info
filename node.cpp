#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;

void Node::computeOutput(){

  map<int, Node>::iterator it;
  bool tab[2];

  //Porte AND2
  if(my_type == "AND2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
    }
    this->my_result = tab[0] && tab[1];
  }

  //Porte OR2
  if(my_type == "OR2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
      cout<<"tab[" << it->first <<"]=" << it->second.my_result << endl;
      cout << "OR" << endl;
    }
    this->my_result = tab[0] || tab[1];
  }

}
//void checkInputDelta(){}
