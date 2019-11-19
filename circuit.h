#ifndef DEF_CIRCUIT
#define DEF_CIRCUIT


#include <string>
#include <iostream>
#include <map>
#include "node.h"

using namespace std;

class Circuit{
private:
  string m_name;    //Circuit name
  string m_dotFile; //Dotfile path
  map<string, Node> m_circuitInputs;  //Map of the circuit inputs
  map<string, Node> m_circuitOutputs; //Map of the circuit outputs
  map<string, Node> m_circuitGates;   //Map of the circuit gates
public:
  Circuit(const string & nom, const string & dotFile);  //Constructor
  ~Circuit(){;}                                         //Destructor

  void parse();          //Parses the dot file and creates the circuit inputs, outputs and gates with the link between them.
  setInputValues(bool a, bool b); //Sets the values of the circuit inputs
  checkSumDelta();  //Checks the delta of all the circuit nodes.
  evaluate();       //Runs the simulation of the circuit for 1 clock tick, based on the inputs, sets the outputs.
};

#endif
