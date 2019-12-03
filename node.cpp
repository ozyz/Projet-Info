#include <string>
#include <iostream>
#include <map>
#include "node.h"
#include "circuit.h"

using namespace std;

//Function which allows the compute of a node
//Max number of inputs : INFINITE !!

void Node::computeOutput(){

  map<int, Node*>::iterator it;
  bool tab[2]; // we use this tab just for the MUX
  size_t found;
  bool result;
  int n; // number of inputs of a node
  int i = 0;
  std::vector<bool> v; //new version : we use a vector instead of a tab to consider nodes with "infinite" inputs

  string str = this->my_type;

  //AND Gate
  if(str.find("AND") != string::npos){
    found = str.find("_");
    if(found != string::npos){
       n = stoi(str.substr(found+1));
    }
    else{
      std::cout << "Error AND: number of inputs not defined" << '\n';
    }
    // std::cout << "Computing AND..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      v.push_back(it->second->my_result);
    }
    for(i=0;i<n;i++){
      if(i==0){
        result = v[0];
      }
      else{
        result = v[i] && result;
      }
    }
    this->my_result = result;
    this->my_delta = 1;
    // std::cout << "Compute AND ended"<< '\n';
  }


  //NAND Gate
  if(str.find("NAND") != string::npos){
    found = str.find("_");
    if(found != string::npos){
       n = stoi(str.substr(found+1));
    }
    else{
      std::cout << "Error NAND: number of inputs not defined" << '\n';
    }
    // std::cout << "Computing NAND..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      v.push_back(it->second->my_result);
    }
    for(i=0;i<n;i++){
      if(i==0){
        result = v[0];
      }
      else{
        result = v[i] && result;
      }
    }
    this->my_result = !result;
    this->my_delta = 1;
    // std::cout << "Compute NAND ended"<< '\n';
  }


  //OR Gate
  else if(str.find("OR") != string::npos){
    found = str.find("_");
    if(found != string::npos){
      n = stoi(str.substr(found+1));
    }
    else{
      std::cout << "Error OR: number of inputs not defined" << '\n';
    }
    // std::cout << "Computing OR..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      v.push_back(it->second->my_result);
    }
    for(i=0;i<n;i++){
      if(i==0){
        result = v[0];
      }
      else{
        result = v[i] || result;
      }
    }
    this->my_result = result;
    this->my_delta = 1;
    // std::cout << "Compute OR ended"<< '\n';
  }


  //NOR Gate
  else if(str.find("NOR") != string::npos){
    found = str.find("_");
    if(found != string::npos){
      n = stoi(str.substr(found+1));
    }
    else{
      std::cout << "Error NOR: number of inputs not defined" << '\n';
    }
    // std::cout << "Computing NOR..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      v.push_back(it->second->my_result);
    }
    for(i=0;i<n;i++){
      if(i==0){
        result = v[0];
      }
      else{
        result = v[i] || result;
      }
    }
    this->my_result = !result;
    this->my_delta = 1;
    // std::cout << "Compute NOR ended"<< '\n';
  }


  //NOT Gate
  else if(str.find("NOT") != string::npos){
        // std::cout << "Computing NOT..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      v.push_back(it->second->my_result);
    }
    result = !v[0];
    this->my_result = result;
    this->my_delta = 1;
    // std::cout << "Compute NOT ended"<< '\n';
  }

  //XOR Gate
  else if(str.find("XOR") != string::npos){
    found = str.find("_");
    if(found != string::npos){
      n = stoi(str.substr(found+1));
    }
    else{
      std::cout << "Error XOR: number of inputs not defined" << '\n';
    }
    // std::cout << "Computing XOR..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      v.push_back(it->second->my_result);
    }
    for(i=0;i<n;i++){
      if(i==0){
        result = v[0];
      }
      else{
        result = v[i] ^ result;
      }
    }
    this->my_result = result;
    this->my_delta = 1;
    // std::cout << "Compute XOR ended"<< '\n';
  }


  //NXOR Gate
  else if(str.find("NXOR") != string::npos){
    found = str.find("_");
    if(found != string::npos){
      n = stoi(str.substr(found+1));
    }
    else{
      std::cout << "Error NXOR: number of inputs not defined" << '\n';
    }
    // std::cout << "Computing NXOR..." << '\n';
    for(it=my_inputs.begin(); it!=my_inputs.end(); it++){
      v.push_back(it->second->my_result);
    }
    for(i=0;i<n;i++){
      if(i==0){
        result = v[0];
      }
      else{
        result = v[i] ^ result;
      }
    }
    this->my_result = !result;
    this->my_delta = 1;
    // std::cout << "Compute NXOR ended"<< '\n';
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
