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

  //Modifieurs et accesseurs
  void setInputs(Node A, Node B, Node C){
    my_inputs.insert(pair<int, Node>(0, A));
    my_inputs.insert(pair<int, Node>(1, B));
    my_inputs.insert(pair<int, Node>(2, C));
  }

  void setOutputs(Node C){
    my_outputs.insert(pair<int, Node>(0, C));
  }

   map<int, Node> getInputs(){
    return this->my_inputs;
   }

   string getType(){
    return this->my_type;
   }

   void setResult(bool A){
     this->my_result = A;
   }


   bool getResult(){
     return this->my_result;
   }


  //Méthodes
  void computeOutput();
  void checkInputDelta();


  //Destructeur de la classe Node
  //~Node(){
  //  cout << "Destructeur de la classe Node" << endl;
  //};

};

#endif
