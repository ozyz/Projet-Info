#include "circuit.h"
#include "node.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
//#include <bits/stdc++.h>

using namespace std;

Circuit::Circuit(const string & nom, const string & dotFile): my_name(nom), my_dotFile(dotFile){

}

//Parsing the dotfile of the circuit
void Circuit::parse(){

  ifstream fichier(my_dotFile.c_str());

  string str;
  size_t found;
  int in_circuit_idx = 0;
  int out_circuit_idx = 0;
  int gate_circuit_idx = 0;

  bool in_from_found = 0;
  bool gate_from_found = 0;

  bool out_to_found = 0;
  bool gate_to_found = 0;


  while (getline(fichier, str)) {

    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    //Tests if current line has "digraph" and sets the name of the circuit
    if(str.find("digraph") != string::npos){
        found = str.find("{");
        if(found != string::npos){
           my_name = str.substr(7,found-7);
           // std::cout << "name: "<< my_name << '\n';
        } else {std::cout << "ERREUR : Accolade manquante sur la première ligne" << '\n';}
    }

    //Tests if current line has "label" and creates de nodes of the circuit
    if (str.find("label") != string::npos) {
       size_t found1 = str.find("label");
       string node_name = str.substr(0,found1-1); //Takes the node name from the line
       string node_type = str.substr(found1+7);   //Deletes the first part of the line
       size_t found2 = node_type.find("\"");
       node_type = node_type.substr(0,found2);    //Takes the node type from the line

       Node* B = new Node(node_name,node_type);   //Creates a Node with the obtained name and type

       // std::cout << "Node name:"<< B->getName()<< " Node Type :" << B->getType()<<" Delta :"<<B->getDelta() << " Result :" << B->getResult() << '\n';

      //Testing the node type and filling the
       if (node_type == "INPUT") {
         my_circuitInputs.insert(pair<int, Node*>(in_circuit_idx, B));
         in_circuit_idx+=1;
       } else if (node_type == "OUTPUT") {
         my_circuitOutputs.insert(pair<int, Node*>(out_circuit_idx, B));
         out_circuit_idx+=1;
       } else{
         my_circuitGates.insert(pair<int, Node*>(gate_circuit_idx, B));
         gate_circuit_idx+=1;
       }
    //   std::cout << str.substr(3,found1) << " and "<< str.substr(found1+7,found2-found1-3 + 7 - 1) << '\n';
     }

     //Tests if current line has "->" and fills the inputs of the nodes
     if (str.find("->") != string::npos) {
     if(in_circuit_idx == 0 ){
       std::cout << "Erreur : Aucune entrée n'est définie" << '\n';
       exit(1);
     }

     if(out_circuit_idx == 0){
       std::cout << "Erreur : Aucune sortie n'est définie" << '\n';
       exit(1);
     }
      size_t found3 = str.find("->");
      string from_name = str.substr(0,found3);
      string to_name = str.substr(found3+2);

      map<int, Node*>::iterator it1;
      map<int, Node*>::iterator it2;
      for (it1 = my_circuitInputs.begin(); it1 != my_circuitInputs.end(); it1++) {
        if(it1->second->getName() == from_name){
          in_from_found = 1;
          for (it2 = my_circuitGates.begin(); it2 != my_circuitGates.end(); it2++) {
             if(it2->second->getName() == to_name){
               it2->second->addInput(it1->second);
               gate_to_found = 1;
             }
          }
        }
      }
      for (it1 = my_circuitGates.begin(); it1 != my_circuitGates.end(); it1++) {
        if(it1->second->getName() == from_name){
          gate_from_found = 1;
          for (it2 = my_circuitGates.begin(); it2 != my_circuitGates.end(); it2++) {
            if(it2->second->getName() == to_name){
              gate_to_found = 1;
               it2->second->addInput(it1->second);

            }
          }
        }
      }
      for (it1 = my_circuitOutputs.begin(); it1 != my_circuitOutputs.end(); it1++) {
        if(it1->second->getName() == to_name){
          out_to_found = 1;
          for (it2 = my_circuitGates.begin(); it2 != my_circuitGates.end(); it2++) {
            if(it2->second->getName() == from_name){
              gate_from_found = 1;
               it1->second->addInput(it2->second);
            }
          }
        }
      }
      if (in_from_found == 0 && gate_from_found == 0) {
        std::cout << "Erreur sur le nom de la connection de l'entrée :\"" << from_name<<"\"" << '\n';
        exit(1);
      } else {
         in_from_found =0;
         gate_from_found=0;
      }
      if (out_to_found == 0 && gate_to_found == 0){
        std::cout << "Erreur sur le nom de la connection de la sortie :\"" << to_name<<"\"" <<'\n';
        exit(1);
      } else {
        out_to_found = 0;
        gate_to_found = 0;
      }
       // std::cout << from_name << "" << to_name << '\n';
     }
    // cout << str <<'\n';
  }
}

void Circuit::setInputValues(map<string, bool> inputs){
  map<int, Node*>::iterator it_nodes;
  map<string, bool>::iterator it_inputs;

  for (it_inputs= inputs.begin(); it_inputs != inputs.end(); it_inputs++){
    for (it_nodes= my_circuitInputs.begin(); it_nodes != my_circuitInputs.end(); it_nodes++){
      if(it_inputs->first == it_nodes->second->getName()){
        it_nodes->second->setResult(it_inputs->second);
        // std::cout << "Input : " <<   it_nodes->second->getName() << " = " << it_nodes->second->getResult()<<'\n';
        it_nodes->second->setDelta(1);
      }
    }
    // std::cout <<"resultat: " <<it->second->getResult()<<" name:"<< it->second->getName()<<" delta:"<< it->second->getDelta()<< '\n';
    // cin.ignore();
  }
}

void Circuit::reset(){
  map<int, Node*>::iterator it;
  for (it= my_circuitInputs.begin(); it != my_circuitInputs.end(); it++){
    it->second->setDelta(0);
    it->second->setResult(0);
  }
  for (it= my_circuitGates.begin(); it != my_circuitGates.end(); it++){
    it->second->setDelta(0);
    it->second->setResult(0);
  }
  for (it= my_circuitOutputs.begin(); it != my_circuitOutputs.end(); it++){
    it->second->setDelta(0);
    it->second->setResult(0);
  }
}

bool Circuit::checkSumDelta(){
  map<int, Node*>::iterator it;
  for (it= my_circuitInputs.begin(); it != my_circuitInputs.end(); it++){
    if (it->second->getDelta()==0){
      return 0;
    }
  }
  for (it= my_circuitGates.begin(); it != my_circuitGates.end(); it++){
    if (it->second->getDelta()==0){
      return 0;
    }
  }
  for (it= my_circuitOutputs.begin(); it != my_circuitOutputs.end(); it++){
    if (it->second->getDelta()==0){
      return 0;
    }
  }
  return 1;
}

map<string,bool>  Circuit::evaluate(){
  map<string,bool> results;
  map<int, Node*>::iterator it;
  while (checkSumDelta() == false){
    for (it= my_circuitGates.begin(); it != my_circuitGates.end(); it++){
      if (it->second->checkInputDelta()){
        // std::cout << "entering compute" << '\n';
        it->second->computeOutput();
      }
    }
    for (it= my_circuitOutputs.begin(); it != my_circuitOutputs.end(); it++){
      if (it->second->checkInputDelta()){
        it->second->setResult(it->second->getFirstInputResult());
        it->second->setDelta(1);
      }
    }
  }
  for (it= my_circuitOutputs.begin(); it != my_circuitOutputs.end(); it++){

    // std::cout << "Resultat:" << it->second->getResult()<< '\n';
    results.insert(make_pair(it->second->getName(),it->second->getResult()));
  }
  return results;
}
