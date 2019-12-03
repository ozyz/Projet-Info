#ifndef DEF_NODE
#define DEF_NODE

#include <string>
#include <iostream>
#include <map>

using namespace std;

class Node {

private:

//Declaration of the variables
  int nb_inputs; //Number of inputs of a Node
  string my_name; //Name of the Node
  string my_type; //Type of the Node : AND, OR, XOR, ...
  bool my_delta; //Delta of a Node
  bool my_result; //Result of a Node
  map<int, Node*> my_inputs; //Map which contains all the inputs of a Node
  map<int, Node*> my_outputs; //Map which contains all the outputs of a Node

public:

//Constructor for the Node class
  Node(const string & nom, const string & type):my_name(nom), my_type(type){
    // cout << "Constructeur de la classe Node" << endl;
    my_delta = 0;
    my_result=0;
    nb_inputs=0;
  }

//Functions which can modify or access the variables of the class

  //Add input on a Node
  void addInput(Node* A){
    my_inputs.insert(pair<int, Node*>(nb_inputs, A));
    nb_inputs++;
  }

  //Get the inputs of a Node
  map<int, Node*> getInputs(){
      return this->my_inputs;
     }

  //Edit the outputs of a Node
  void setOutputs(Node* C){
    my_outputs.insert(pair<int, Node*>(0, C));
  }

  //Get the variable "my_type" of a Node
   string getType(){
    return this->my_type;
   }

    //Edit the variable "my_type" of a Node
    void setType(string type){
        this->my_type = type;
      }

   //Edit delta value of a Node
   void setDelta(bool a){
     my_delta = a;
   }

   //Get the value of the variable "my_result" of a Node
   bool getFirstInputResult(){
     map<int, Node*>::iterator it;
     for (it= my_inputs.begin(); it != my_inputs.end(); it++){
        if(it->first == 0) {
          return it->second->getResult();
        }
     }
   }

   //Edit the variable "my_result" of a Node
   void setResult(bool A){
     this->my_result = A;
   }

   //Get the value of the variable "my_result"
   bool getResult(){
     return this->my_result;
   }

   //Get the number of inputs from a Node
   int getNbInputs(){
     return this->nb_inputs;
   }

   //Get the value of the variable "my_delta" of a Node
   bool getDelta(){
     return my_delta;
   }

   //Get the value of the variable "my_name" of a Node
   string getName(){
     return my_name;
   }

   //Display a Node : name, type, number of inputs, and inputs (Node name, type, ...)
   void displayNode(){
     map<int, Node*>::iterator it;
     std::cout << "This NODE name is :" <<my_name << ", its type is :" << my_type << " its OUPUT number is :"<<nb_inputs << ".Delta = "<< my_delta <<", result=" <<my_result << ". Node OUPUTS :"<<'\n';

     for (it= my_inputs.begin(); it != my_inputs.end(); it++){
       Node* tmp = it->second;
       std::cout << "NODE n°" << it->first <<"\n, name :"<< tmp->getName() << "\n, type :" <<tmp->getType()<< '\n';
     }
   }


//Methods
  void computeOutput();
  bool checkInputDelta();


  //Destructor of the Node class (not active, because it prevents the function to run => the Node is deleted just after being created)
  //~Node(){
  //  cout << "Destructeur de la classe Node" << endl;
  //};

};

#endif
