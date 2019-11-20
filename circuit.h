#ifndef DEF_CIRCUIT
#define DEF_CIRCUIT


#include <string>
#include <iostream>
#include <map>
#include "node.h"

using namespace std;

class Circuit{
private:
  string my_name;    //Circuit name
  string my_dotFile; //Dotfile path
  map<int, Node> my_circuitInputs;  //Map of the circuit inputs
  map<int, Node> my_circuitOutputs; //Map of the circuit outputs
  map<int, Node> my_circuitGates;   //Map of the circuit gates
public:
  Circuit(const string & nom, const string & dotFile);  //Constructor
  ~Circuit(){;}                                         //Destructor
  void displayCircuit(){
    map<int, Node>::iterator it;
    std::cout << "Ce Circuit a pour nom :" <<my_name <<". Voici ses INPUTS:"<<'\n';
    for (it= my_circuitInputs.begin(); it != my_circuitInputs.end(); it++){
      it->second.displayNode();
    }
    std::cout << "\nVoici ses GATES:"<<'\n';
    for (it= my_circuitGates.begin(); it != my_circuitGates.end(); it++){
      it->second.displayNode();
    }
    std::cout << "\nVoici ses OUTPUTS:"<<'\n';
    for (it= my_circuitOutputs.begin(); it != my_circuitOutputs.end(); it++){
      it->second.displayNode();
    }
  }
  void parse();          //Parses the dot file and creates the circuit inputs, outputs and gates with the link between them.
  void setInputValues(bool tab[]); //Sets the values of the circuit inputs
  bool checkSumDelta();  //Checks the delta of all the circuit nodes.
  void evaluate();       //Runs the simulation of the circuit for 1 clock tick, based on the inputs, sets the outputs.
};

#endif
