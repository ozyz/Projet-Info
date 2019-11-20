#include "circuit.h"
#include "node.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>

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

  int in_gate_idx = 0;
  int out_gate_idx = 0;
  int gate_gate_idx = 0;

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

       std::cout << node_name << " "<< node_type << '\n';
       Node A(node_name,node_type);
       if (node_type == "INPUT") {
         my_circuitInputs.insert(pair<int, Node>(in_circuit_idx, A));
         in_circuit_idx+=1;
       } else if (node_type == "OUTPUT") {
         my_circuitOutputs.insert(pair<int, Node>(out_circuit_idx, A));
         out_circuit_idx+=1;
       } else{
         my_circuitGates.insert(pair<int, Node>(gate_circuit_idx, A));
         gate_circuit_idx+=1;
       }
    //   std::cout << str.substr(3,found1) << " and "<< str.substr(found1+7,found2-found1-3 + 7 - 1) << '\n';
     }
     if (str.find("->") != string::npos) {
      size_t found3 = str.find("->");
      string from_name = str.substr(0,found3);
      string to_name = str.substr(found3+2);

      map<int, Node>::iterator it1;
      map<int, Node>::iterator it2;
      for (it1 = my_circuitInputs.begin(); it1 != my_circuitInputs.end(); it1++) {
        if(it1->second.getName() == from_name){
          for (it2 = my_circuitGates.begin(); it2 != my_circuitInputs.end(); it2++) {
            if(it2->second.getName() == to_name){
              it2->second.addInput(0,it1->second);
            }
          }
        }
      }

       std::cout << from_name << "" << to_name << '\n';
     }

    cout << str <<'\n';
  }
}
