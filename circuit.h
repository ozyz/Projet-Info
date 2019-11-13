#ifndef DEF_CIRCUIT
#define DEF_CIRCUIT


#include <string>
#include <iostream>
#include <map>
#include "node.h"

using namespace std;

class Circuit{
private:
  string name;
  string dotFile;
  map<string, Node> circuitInputs;
  map<string, Node> circuitOutputs;
  map<string, Node> circuitGates;
public:
  Circuit(const string & nom, const string & dotFile);
  ~Circuit(){;}

  parse();
  checkSumDelta();
  evaluate();
};

#endif
