#ifndef DEF_NODE
#define DEF_NODE


#include <string>
#include <iostream>
#include <map>

using namespace std;

class Node {

private:

  //Déclaration des variables
  string m_name;
  string type;
  bool delta;
  bool output;
  map<string, Node> inputs;
  map<string, Node> outputs;

public:

  //Constructeur de la classe Node
  Node(const string & nom):m_name(nom){
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
};
#endif
