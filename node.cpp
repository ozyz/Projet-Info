#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;

//Fonction permettant de réaliser le calcul d'un Node
void Node::computeOutput(){

  map<int, Node*>::iterator it;
  bool tab[2];

  //Porte AND_2
  if(my_type == "AND_2"){
    std::cout << "Computing AND_2..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second->my_result;
    }
    this->my_result = tab[0] && tab[1];
    this->my_delta = 1;
    std::cout << "Compute ended"<< '\n';
  }

  //Porte OR_2
  if(my_type == "OR_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second->my_result;
      //cout<<"tab[" << it->first <<"]=" << it->second.my_result << endl;
    }
    this->my_result = tab[0] || tab[1];
    this->my_delta = 1;
  }

  //Porte NOT
  if(my_type == "NOT"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second->my_result;
    }
    this->my_result = !tab[0];
    this->my_delta = 1;
  }

  //Porte XOR_2
  if(my_type == "XOR_2"){
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      tab[it->first] = it->second->my_result;
    }
    this->my_result = tab[0] ^ tab[1];
    this->my_delta = 1;
  }

  //Porte MUX_2
  if(my_type == "MUX_2"){
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
  }

}

//Fonction permettant de vérifier si le delta du/des Node(s) précédant le Node actuel est égal à 1
bool Node::checkInputDelta(){

  map<int, Node*>::iterator it;
  bool a;

  for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
    std::cout << "Node testée : "<< this->my_name << endl;
    std::cout << "Node d'entrée testée :" << it->second->getName() << ", son résultat : "<<it->second->getResult() <<", son delta: "<<it->second->getDelta()<<'\n';
    std::cout << "My delta :" << this->my_delta <<", my result : " <<this->my_result <<'\n';
    if(it->second->my_delta == 1){
      cout << "OK pour le Node " << endl;
      a = 1;
      cin.ignore();
    }
    else{
      cout << "erreur le Node " << this->my_name << " a des inputs a 0" << " delta :"<< it->second->getDelta() << " son nom : "<< it->second->getName()<< endl;
      cin.ignore();
      return 0;
    }
  }
  return a;
}
