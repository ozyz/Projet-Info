#include <string>
#include <iostream>

using namespace std;

class Circuit{
private:
  string m_nom;
  int m_nb_inputs;
  int m_nb_outputs;
  int m_inputs[];
  int m_outputs[];

public:
  Circuit(const string & nom);
  ~Circuit(){;}
};
