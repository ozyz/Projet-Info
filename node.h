#ifndef DEF_NODE
#define DEF_NODE


#include <string>
#include <iostream>
#include <map>

using namespace std;

class Node {

private:

  //Déclaration des variables
  string my_name;
  string my_type;
  bool my_delta;
  bool my_result;
  map<int, Node> my_inputs;
  map<int, Node> my_outputs;

public:

  //Constructeur de la classe Node
  Node(const string & nom, const string & type):my_name(nom), my_type(type){
    cout << "Constructeur de la classe Node" << endl;
  }

  //Destructeur de la classe Node
  ~Node(){
    cout << "Destructeur de la classe Node" << endl;
  };

  //Modifieurs et accesseurs
  void setInput(Node A, Node B){
    my_inputs.insert(pair<int, Node>(0, A));
    my_inputs.insert(pair<int, Node>(1, B));
  }

  void setOutput(Node C){
    my_outputs.insert(pair<int, Node>(0, C));
  }

   map<int, Node> getInputs(){
    return my_inputs;
   }

   string getType(){
    return my_type;
   }

   void setResult(bool A){
     my_result = A;
   }


  //Méthodes
  void computeOutput();
  void checkInputDelta();

};

#endif
