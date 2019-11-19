#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;

void Node::computeOutput(){

map<int, Node>::iterator it;
bool tab[2];

switch(my_type){

  case "AND2":
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;

    }
    my_result = tab[0] && tab[1];
    break;

  case "OR2":
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
    }
    my_result = tab[0] || tab[1];
    break;

  default:
    break;

  }

}

void checkInputDelta(){

}
