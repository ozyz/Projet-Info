#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;

//Function which allows the compute of a node
void Node::computeOutput(){

  map<int, Node*>::iterator it;
  bool tab[2];

  //AND_2 Gate
  if(my_type == "AND_2"){
    // std::cout << "Computing AND_2..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second->my_result;
    }
    this->my_result = tab[0] && tab[1];
    this->my_delta = 1;
    // std::cout << "Compute AND_2 ended"<< '\n';
  }

  //OR_2 Gate
  else if(my_type == "OR_2"){
    // std::cout << "Computing OR_2..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second->my_result;
    }
    this->my_result = tab[0] || tab[1];
    this->my_delta = 1;
    // std::cout << "Compute OR_2 ended"<< '\n';
  }

  //NOT Gate
  else if(my_type == "NOT"){
    // std::cout << "Computing NOT..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second->my_result;
    }
    this->my_result = !tab[0];
    this->my_delta = 1;
    // std::cout << "Compute NOT ended"<< '\n';
  }

  //XOR_2 Gate
  else if(my_type == "XOR_2"){
    // std::cout << "Computing XOR_2..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second->my_result;
    }
    this->my_result = tab[0] ^ tab[1];
    this->my_delta = 1;
    // std::cout << "Compute XOR_2 ended"<< '\n';
  }

  //MUX_2 Gate
  else if(my_type == "MUX_2"){
    // std::cout << "Computing MUX_2..." << '\n';
    bool tab1[3];
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab1[it->first] = it->second->my_result;
    }
    if(tab1[0] == 0){
      this->my_result = tab1[1];
      this->my_delta = 1;
    }
    else if(tab1[0] == 1){
      this->my_result = tab1[2];
      this->my_delta = 1;
    }
    // std::cout << "Compute MUX_2 ended"<< '\n';
  }

  else if(my_type == "INPUT"){

  }

  else if(my_type == "OUTPUT"){

  }

  else{
    cout << "Error : the type " << this->my_type << " of the node " << this->my_name << " is not accepted" << endl;
    exit(1);
  }

/*
  //D gate
  Node<bool> clock; //définition de l'horloge
  Node<bool> signal_input; //définition du signal d'entrée
  Node<bool> signal_output; //définition du signal de sortie

*/


}


//This function can check if the delta relating to one/some Node(s), which are behind the current Node, is equal to 1
bool Node::checkInputDelta(){

  map<int, Node*>::iterator it;
  bool a;

  for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
    // std::cout << "Node testé : "<< this->my_name << endl;
    // std::cout << "Node d'entrée testée :" << it->second->getName() << ", son résultat : "<<it->second->getResult() <<", son delta: "<<it->second->getDelta()<<'\n';
    // std::cout << "My delta :" << this->my_delta <<", my result : " <<this->my_result <<'\n';
    if(it->second->my_delta == 1){
      // cout << "OK pour le Node " << endl;
      a = 1;
      // cin.ignore();
    }
    else{
      // cout << "erreur le Node " << this->my_name << " a des inputs a 0" << " delta :"<< it->second->getDelta() << " son nom : "<< it->second->getName()<< endl;
      // cin.ignore();
      return 0;
    }
  }
  return a;
}
