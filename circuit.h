#ifndef DEF_CIRCUIT
#define DEF_CIRCUIT


#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "node.h"


using namespace std;

class Circuit{
private:
  string my_name;    //Circuit name
  string my_dotFile; //Dotfile path
  int my_period;
  map<int, Node*> my_circuitInputs;  //Map of the circuit inputs
  map<int, Node*> my_circuitOutputs; //Map of the circuit outputs
  map<int, Node*> my_circuitGates;   //Map of the circuit gates
public:
  Circuit(const string & nom, const string & dotFile, const int & period);  //Constructor
  ~Circuit(){;} //Destructor


  void displayCircuit(){
    map<int, Node*>::iterator it;
    std::cout << "The circuit name is :" <<my_name <<". Its INPUTS are :"<<'\n';
    for (it= my_circuitInputs.begin(); it != my_circuitInputs.end(); it++){
      it->second->displayNode();
    }
    std::cout << "\nIts GATES are :"<<'\n';
    for (it= my_circuitGates.begin(); it != my_circuitGates.end(); it++){
      it->second->displayNode();
    }
     std::cout << "\nIts OUTPUTS are :"<<'\n';
    for (it= my_circuitOutputs.begin(); it != my_circuitOutputs.end(); it++){
      it->second->displayNode();
    }
  }

  vector<string> getInputNames(){
    vector<string> names;
    map<int, Node*>::iterator it;
    for (it= my_circuitInputs.begin(); it != my_circuitInputs.end(); it++){
      names.push_back(it->second->getName());
    }
    return names;
  }

  int getPeriod(){
    return my_period;
  }

  vector<string> getOutputNames(){
    vector<string> names;
    map<int, Node*>::iterator it;
    for (it= my_circuitOutputs.begin(); it != my_circuitOutputs.end(); it++){
      names.push_back(it->second->getName());
    }
    return names;
  }
<<<<<<< HEAD

  
=======
  int getNumberOfGates(){
    int cnt;
    map<int, Node*>::iterator it;
    for (it= my_circuitGates.begin(); it != my_circuitGates.end(); it++){
      cnt++;
    }
    for (it= my_circuitOutputs.begin(); it != my_circuitOutputs.end(); it++){
      cnt++;
    }
    return cnt;
  }
>>>>>>> e60529594e7ada476d229d16fadc99947a253160
  void parse();          //Parses the dot file and creates the circuit inputs, outputs and gates with the link between them.
  void setInputValues(map<string, bool> inputs); //Sets the values of the circuit inputs
  bool checkSumDelta();  //Checks the delta of all the circuit nodes.
  map<string,bool> evaluate(int time);       //Runs the simulation of the circuit for 1 clock tick, based on the inputs, sets the outputs.
  void reset();          //resets the circuit (sets all the nodes deltas to 0)
};

#endif
