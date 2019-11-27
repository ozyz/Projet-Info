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

void Circuit::parse(){
  ifstream fichier(my_dotFile.c_str());

  string str;
  size_t found;
  int in_circuit_idx = 0;
  int out_circuit_idx = 0;
  int gate_circuit_idx = 0;

  while (getline(fichier, str)) {

    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    if(str.find("digraph") != string::npos){
        found = str.find("{");
        if(found != string::npos){
           my_name = str.substr(7,found-7);
           std::cout << "name: "<< my_name << '\n';
        }
    }
    if (str.find("label") != string::npos) {
       size_t found1 = str.find("label");
       string node_name = str.substr(0,found1-1);
       string node_type = str.substr(found1+7);
       size_t found2 = node_type.find("\"");
       node_type = node_type.substr(0,found2);

       Node* B = new Node(node_name,node_type);
       std::cout << "Node name:"<< B->getName()<< " Node Type :" << B->getType()<<" Delta :"<<B->getDelta() << " Result :" << B->getResult() << '\n';
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
     if (str.find("->") != string::npos) {
      size_t found3 = str.find("->");
      string from_name = str.substr(0,found3);
      string to_name = str.substr(found3+2);

      map<int, Node*>::iterator it1;
      map<int, Node*>::iterator it2;
      for (it1 = my_circuitInputs.begin(); it1 != my_circuitInputs.end(); it1++) {
        if(it1->second->getName() == from_name){
          for (it2 = my_circuitGates.begin(); it2 != my_circuitGates.end(); it2++) {
             if(it2->second->getName() == to_name){
               it2->second->addInput(it1->second);
             }
          }
        }
      }
      for (it1 = my_circuitGates.begin(); it1 != my_circuitGates.end(); it1++) {
        if(it1->second->getName() == from_name){
          for (it2 = my_circuitGates.begin(); it2 != my_circuitGates.end(); it2++) {
            if(it2->second->getName() == to_name){
               it2->second->addInput(it1->second);
            }
          }
        }
      }
      for (it1 = my_circuitOutputs.begin(); it1 != my_circuitOutputs.end(); it1++) {
        if(it1->second->getName() == to_name){
          for (it2 = my_circuitGates.begin(); it2 != my_circuitGates.end(); it2++) {
            if(it2->second->getName() == from_name){
               it1->second->addInput(it2->second);
            }
          }
        }
      }

       std::cout << from_name << "" << to_name << '\n';
     }

    cout << str <<'\n';
  }
}

void Circuit::setInputValues(map<string, bool> inputs){
  map<int, Node*>::iterator it_nodes;
  map<string, bool>::iterator it_inputs;

  for (it_inputs= inputs.begin(); it_inputs != inputs.end(); it_inputs++){
    for (it_nodes= my_circuitInputs.begin(); it_nodes != my_circuitInputs.end(); it_nodes++){
      if(it_inputs->first == it_nodes->second->getName()){
        it_nodes->second->setResult(it_inputs->second);
        std::cout << "Input : " <<   it_nodes->second->getName() << " = " << it_nodes->second->getResult()<<'\n';
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

bool Circuit::evaluate(){
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
    return it->second->getResult();
  }
}
