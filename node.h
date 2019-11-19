#ifndef DEF_NODE
#define DEF_NODE


#include <string>
#include <iostream>
#include <map>
#include "circuit.h"
using namespace std;

<<<<<<< HEAD
class Node : public Circuit {

private:

  //Déclaration des variables
  string name;
  string type;
  bool delta;
  bool output;
  map<string, Node> inputs;
  map<string, Node> outputs;

public:

  //Constructeur de la classe Node
  Node(const string & nom) :
  Circuit(nom){
    cout << "Constructeur de la classe Node" << endl;
  }

  //Destructeur de la classe Node
  ~Node(){
    cout << "Destructeur de la classe Node" << endl;
  };

  //Modifieurs et accesseurs


  //Méthodes
  void computeOutput();
  void checkInputDelta();

=======
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
>>>>>>> 003ccaa0756f173077e04192aaba6b88d70e641e
};
#endif
