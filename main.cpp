#include <iostream>
#include "circuit.h"
#include "node.h"
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

#include "build/VCDFileParser.hpp"

//! Convert a VCDBit to a single char
static char VCDBit2Char(VCDBit b) {
    switch(b) {
        case(VCD_0):
            return '0';
        case(VCD_1):
            return '1';
        case(VCD_Z):
            return 'Z';
        case(VCD_X):
        default:
            return 'X';
    }
}
map<int, map<string, bool>> vcdParser(string vcdFile)
{

    std::string infile("in.vcd");
    map<int, map<string, bool>> timing_inputs_map;
    map<string, bool> inputs_map;
    const string ref;

    // std::cout << "Parsing " << infile << std::endl;

    VCDFileParser parser;

    VCDFile *trace = parser.parse_file(infile);

    if (trace)
    {
        std::cout << "Parse successful." << std::endl;
        std::cout << "Version:       " << trace->version << std::endl;
        std::cout << "Date:          " << trace->date << std::endl;
        std::cout << "Signal count:  " << trace->get_signals()->size() << std::endl;
        std::cout << "Times Recorded:" << trace->get_timestamps()->size() << std::endl;

        // Print out every signal in every scope.
        for (VCDScope *scope : *trace->get_scopes())
        {

            // std::cout << "Scope: " << scope->name << std::endl;

            for (VCDSignal *signal : scope->signals)
            {

                // std::cout << "\t" << signal->hash << "\t"
                          // << signal->reference;
//
                if (signal->size > 1)
                {
                    // std::cout << " [" << signal->size << ":0]";
                }

                std::cout << std::endl;
            }
          }
          // std::cout << "Looking for signals" <<std::endl;
          auto my_signals =  trace->get_signals();
          // std::cout << "Looking for timestamps" <<std::endl;
        auto  my_timestamps = trace->get_timestamps();
         int i=0;
        for (VCDTime instant : *my_timestamps)
          {
            for (VCDSignal *cur_signal : *my_signals)
             {
                 // std::cout << "[" << instant <<"] : " << cur_signal->reference
                   // << " = ";
                   // Assumes val is not nullptr!
                   VCDBitVector * vecval;
                   auto val = trace->get_signal_value_at(cur_signal->hash,instant);
                   switch(val -> get_type()) {
                       case (VCD_SCALAR):
                           // std::cout << val -> get_value_bit() ; //VCDValue::VCDBit2Char(val -> get_value_bit());
                           inputs_map.insert(make_pair(cur_signal->reference, val->get_value_bit()));
                           break;
                       case (VCD_VECTOR):
                           vecval = val -> get_value_vector();
                           for(auto it = vecval -> begin();
                                    it != vecval -> end();
                                    ++it) {
                               // std::cout << VCDBit2Char(*it);
                           }
                           break;
                       case (VCD_REAL):
                           // std::cout << val -> get_value_real();
                       default:
                           break;
                   }
              // std::cout <<std::endl;
             }
             timing_inputs_map.insert(make_pair(instant, inputs_map));
             inputs_map.clear();
             i++;
          }

        delete trace;

        return timing_inputs_map;
    }
    else
    {
        std::cout << "Parse Failed." << std::endl;
    }
}

int main(int argc, char const *argv[]) {

  map<int, map<string, bool>> inputs = vcdParser("in.vcd");
  map<int, map<string, bool>>::iterator it_timings;
  map<string, bool>::iterator it_inputs;
  ostringstream line_time, line_result;

  Circuit a("yo", "test.dot");
  a.parse();
  // a.displayCircuit();
  std::cout << "Starting simulation...\n" << '\n';
  line_time << "\nTime:   ";
  line_result << "Results:";

  for (it_timings = inputs.begin(); it_timings != inputs.end(); it_timings++) {
      line_time << std::setw(6) << it_timings->first;
      a.setInputValues(it_timings->second);
      line_result << std::setw(6) << a.evaluate();
      a.reset();
  }
  std::cout << line_time.str() << '\n';
  std::cout << line_result.str() << '\n';
  return 0;
}

// map<int, map<int, bool>> inParser(string inFile, int* simulationTime, Circuit a){
//   ifstream fichier(inFile.c_str());
//
//   int in_circuit_idx = 0;
//   string str;
//   size_t found;
//
//   while (getline(fichier, str)) {
//     str.erase(remove(str.begin(), str.end(), ' '), str.end());
//
//     if(str.find("$") != string::npos){
//       found = str.find("$");
//       *simulationTime = stoi(str.substr(1));
//     }
//     if(str.find("#") != string::npos){
//         found = str.find("#");
//
//     }
//
//   }
// }
/*!
@file
@brief Definition of the VCDFileParser class
*/


/*!
@brief Standalone test function to allow testing of the VCD file parser.
*/
