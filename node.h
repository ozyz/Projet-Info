#ifndef DEF_NODE
#define DEF_NODE

#include <string>
#include <iostream>
#include <map>

using namespace std;

class Node {

private:

  //Déclaration des variables
  int nb_inputs;
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
    nb_inputs=0;
  }

  //Modifieurs et accesseurs

  void addInput(int pos, Node A){
    my_inputs.insert(pair<int, Node>(pos, A));
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

   void setType(string type){
     this->my_type = type;
   }

   void setResult(bool A){
     this->my_result = A;
   }

   int getNbInputs(){
     return this->nb_inputs;
   }

   bool getResult(){
     return this->my_result;
   }
   bool getDelta(){
     return my_delta;
   }
   string getName(){
     return my_name;
   }

   void displayNode(){
     map<int, Node>::iterator it;
     std::cout << "Ce noeud a pour nom :" <<my_name <<", pour type :" << my_type << " et un nombre d'entrées:"<<nb_inputs<< ". Voici ses inputs:"<<'\n';
     for (it= my_inputs.begin(); it != my_inputs.end(); it++){
       std::cout << "Noeud n°" << it->first <<" de nom:"<< it->second.getName() << " et de type:" <<it->second.getType()<< '\n';
     }
   }

  //Méthodes
  void computeOutput();
  bool checkInputDelta();


  //Destructeur de la classe Node
  //~Node(){
  //  cout << "Destructeur de la classe Node" << endl;
  //};

};

#endif
