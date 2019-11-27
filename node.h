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
    // cout << "Constructeur de la classe Node" << endl;
    my_delta = 0;
    my_result=0;
    nb_inputs=0;
  }

//Modifieurs et accesseurs

  //Ajout d'une entrée sur un Node
  void addInput(Node* A){
    my_inputs.insert(pair<int, Node*>(nb_inputs, A));
    nb_inputs++;
  }

  //Récupérer les entrées d'un Node
  map<int, Node*> getInputs(){
      return this->my_inputs;
     }

  //Editer les sorties d'un Node
  void setOutputs(Node* C){
    my_outputs.insert(pair<int, Node*>(0, C));
  }

  //Récupérer la variable "my_type" d'un Node
   string getType(){
    return this->my_type;
   }

    //Editer la variable "my_type" d'un Node
    void setType(string type){
        this->my_type = type;
      }

   //Editer la valeur du delta d'un Node
   void setDelta(bool a){
     my_delta = a;
   }

   //Récupérer la valeur de la variable "my_result" d'un Node
   bool getFirstInputResult(){
     map<int, Node*>::iterator it;
     for (it= my_inputs.begin(); it != my_inputs.end(); it++){
        if(it->first == 0) {
          return it->second->getResult();
        }
     }
   }

   //Editer la variable "my_result" d'un Node
   void setResult(bool A){
     this->my_result = A;
   }

   //Récupérer la valeur de la variable "my_result"
   bool getResult(){
     return this->my_result;
   }

   //Récupérer le nombre d'entrées d'un Node
   int getNbInputs(){
     return this->nb_inputs;
   }

   //Récupérer la valeur de la variable "my_delta" d'un Node
   bool getDelta(){
     return my_delta;
   }

   //Récupérer la valeur de la variable "my_name" d'un Node
   string getName(){
     return my_name;
   }

   //Afficher un Node : nom, type, nombre d'entrées, et entrées (nom du noeud, type, ...)
   void displayNode(){
     map<int, Node*>::iterator it;
     std::cout << "Ce noeud a pour nom :" <<my_name << ", pour type :" << my_type << " et un nombre d'entrées:"<<nb_inputs << ".Delta = "<< my_delta <<", result=" <<my_result << ". Voici ses inputs:"<<'\n';

     for (it= my_inputs.begin(); it != my_inputs.end(); it++){
       Node* tmp = it->second;
       std::cout << "Noeud n°" << it->first <<"\n de nom:"<< tmp->getName() << "\n et de type:" <<tmp->getType()<< '\n';
     }
   }


//Méthodes
  void computeOutput();
  bool checkInputDelta();


  //Destructeur de la classe Node (en commentaire, car il perturbe le fonctionnement du programme => supprime directement le node après l'avoir créé)
  //~Node(){
  //  cout << "Destructeur de la classe Node" << endl;
  //};

};

#endif
