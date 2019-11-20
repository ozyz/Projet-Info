#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;

void Node::computeOutput(){

  map<int, Node>::iterator it;
  bool tab[2];

  //Porte AND_2
  if(my_type == "AND_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
    }
    this->my_result = tab[0] && tab[1];
  }

  //Porte OR_2
  if(my_type == "OR_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
      //cout<<"tab[" << it->first <<"]=" << it->second.my_result << endl;
    }
    this->my_result = tab[0] || tab[1];
  }

  //Porte NOT
  if(my_type == "NOT"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
    }
    this->my_result = !tab[0];
  }

  //Porte XOR_2
  if(my_type == "XOR_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
    }
    this->my_result = tab[0] ^ tab[1];
  }

  //Porte MUX_2
  if(my_type == "MUX_2"){
    bool tab1[3];
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab1[it->first] = it->second.my_result;
    }
    if(tab1[0] == 0){
      this->my_result = tab1[1];
    }
    else if(tab1[0] == 1){
      this->my_result = tab1[2];
    }
  }

}

void checkInputDelta(){}
