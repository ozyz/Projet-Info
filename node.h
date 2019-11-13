#ifndef DEF_NODE
#define DEF_NODE


#include <string>
#include <iostream>
#include <map>
#include "circuit.h"
using namespace std;

class Node : public Circuit{
private:
  string name;  //Name of the node
  string type;  //Type of the node (INPUT, OUTPUT, AND_2, NOT...)
  bool delta;   //Delta of the node
  bool output;  //Output of the node, calcultated by "computeOutput()" method.
  map<string, Node> inputs;   //Map of the node inputs
  map<string, Node> outputs;  //Map of the node outputs
public:
  Node(const string & nom, const string & type);  //Constructor
  ~Node(){;}                                      //Destructor

  void computeOutput(); //Calculate the output from the inputs and node type
  void checkDelta(); //Check if the deltas of the inputs = 1
};
#endif
