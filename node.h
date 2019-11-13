#include <string>
#include <iostream>
#include <map>
using namespace std;

class Node{
private:
  string name;
  string type;
  bool delta;
  bool output;
  map<string, Node> inputs;
public:
  Node(const string & nom);
  ~Node(){;}
};
