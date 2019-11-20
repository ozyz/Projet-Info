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
    cout << "AND" << endl;
  }

  //Porte OR_2
  if(my_type == "OR_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
      cout<<"tab[" << it->first <<"]=" << it->second.my_result << endl;
    }
    this->my_result = tab[0] || tab[1];
    cout << "OR" << endl;
  }

  //Porte NOT_2
  if(my_type == "NOT_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
    }
    this->my_result = !tab[0];
    cout << "NOT" << endl;
  }

  //Porte XOR_2
  if(my_type == "XOR_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
    }
    this->my_result = tab[0] ^ tab[1];
    cout << "XOR" << endl;
  }

  //Porte MUX_2
  if(my_type == "MUX_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second.my_result;
    }
    if(tab[0] == 0){
      this->my_result = tab[1];
    }
    else if(tab[0] == 1){
      this->my_result = tab[2];
    }
    cout << "MUX" << endl;
  }

}
//void checkInputDelta(){}
