#include "circuit.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Circuit::Circuit(const string & nom, const string & dotFile): m_name(nom), m_dotFile(dotFile){

}

void Circuit::parse(){
  ifstream is (m_dotFile);
  string str;
  while (getline(is, str)) {
    cout << "str" << '\n';
  }
}
