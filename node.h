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
  map<int, Node*> my_inputs;
  map<int, Node*> my_outputs;

public:

  //Constructeur de la classe Node
  Node(const string & nom, const string & type):my_name(nom), my_type(type){
    cout << "Constructeur de la classe Node" << endl;
    nb_inputs=0;
  }

  //Modifieurs et accesseurs
<<<<<<< HEAD
  void addInput(Node* A){
    my_inputs.insert(pair<int, Node*>(nb_inputs, A));
    nb_inputs++;
=======

  void addInput(int pos, Node A){
    my_inputs.insert(pair<int, Node>(pos, A));
>>>>>>> 9d359f8151578a9b754d96f324811959dbbe8884
  }

  void setOutputs(Node* C){
    my_outputs.insert(pair<int, Node*>(0, C));
  }
  map<int, Node*> getInputs(){
    return this->my_inputs;
   }

   string getType(){
    return this->my_type;
   }

   void setDelta(bool a){
     my_delta = a;
   }

   void setType(string type){
     this->my_type = type;
   }

   bool getFirstInputResult(){
     map<int, Node*>::iterator it;
     for (it= my_inputs.begin(); it != my_inputs.end(); it++){
        if(it->first == 0) {
          return it->second->getResult();
        }
     }
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
     map<int, Node*>::iterator it;
     std::cout << "Ce noeud a pour nom :" <<my_name << ", pour type :" << my_type << " et un nombre d'entrées:"<<nb_inputs<< ". Voici ses inputs:"<<'\n';

     for (it= my_inputs.begin(); it != my_inputs.end(); it++){
       Node* tmp = it->second;
       std::cout << "Noeud n°" << it->first <<"\n de nom:"<< tmp->getName() << "\n et de type:" <<tmp->getType()<< '\n';
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
