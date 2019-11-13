#ifndef DEF_NODE
#define DEF_NODE


#include <string>
#include <iostream>
#include <map>
#include "circuit.h"
using namespace std;

class Node : public Circuit{
private:
  string name;
  string type;
  bool delta;
  bool output;
  map<string, Node> inputs;
  map<string, Node> outputs;
public:
  Node(const string & nom, const string & type);
  ~Node(){;}

  void computeOutput();
  void checkDelta();
};
#endif
