#include "circuit.h"
#include "node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Circuit::Circuit(const string & nom, const string & dotFile): m_name(nom), m_dotFile(dotFile){

}

void Circuit::parse(){
  ifstream fichier(m_dotFile.c_str());
  string str;
  size_t found;

  while (getline(fichier, str)) {

    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    if(str.find("digraph") != string::npos){
        found = str.find("{");
        if(found != string::npos){
           m_name = str.substr(7,found-7);
           std::cout << "name: "<< m_name << '\n';
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
    //   std::cout << str.substr(3,found1) << " and "<< str.substr(found1+7,found2-found1-3 + 7 - 1) << '\n';
     }
    cout << str <<'\n';
  }
}
