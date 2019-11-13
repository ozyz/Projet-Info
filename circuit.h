#ifndef DEF_CIRCUIT
#define DEF_CIRCUIT


#include <string>
#include <iostream>
#include <map>
#include "node.h"

using namespace std;

class Circuit{
private:
  string name;    //Circuit name
  string dotFile; //Dotfile path
  map<string, Node> circuitInputs;  //Map of the circuit inputs
  map<string, Node> circuitOutputs; //Map of the circuit outputs
  map<string, Node> circuitGates;   //Map of the circuit gates
public:
  Circuit(const string & nom, const string & dotFile);  //Constructor
  ~Circuit(){;}                                         //Destructor

  parse();          //Parses the dot file and creates the circuit inputs, outputs and gates with the link between them.
  checkSumDelta();  //Checks the delta of all the circuit nodes.
  evaluate();       //Runs the simulation of the circuit 1 time, sets the outputs.
};

#endif
