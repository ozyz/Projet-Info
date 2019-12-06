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

    std::string infile(vcdFile);
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

void displayResults(Circuit c,map<int, map<string, bool>> inputs,map<int, map<string, bool>> results){
    vector<string> input_names = c.getInputNames();
    vector<string> output_names = c.getOutputNames();
    map<int, map<string, bool>>::iterator it_inputs;
    map<int, map<string, bool>>::iterator it_results;
    map<string, bool>::iterator it_name_value;
    int inputs_length = input_names.size();
    int outputs_length = input_names.size();
    ostringstream line_results[outputs_length];
    ostringstream line_inputs[inputs_length];
    ostringstream line_time;
    line_time <<"Time : ";
    vector<string>::iterator it_v;
    int idx;
    int diff =0;
    int period = c.getPeriod();
    //Input display
    for (it_v = input_names.begin(); it_v != input_names.end(); it_v++) {
        idx= distance(input_names.begin(), it_v);
        diff = 7- it_v->length();
        line_inputs[idx] << *it_v <<std::setw(diff) <<":";
    }
    //Output display
    for (it_v = output_names.begin(); it_v != output_names.end(); it_v++) {
        idx= distance(output_names.begin(), it_v);
        diff = 7- it_v->length();
        line_results[idx]<<*it_v<<std::setw(diff) <<":";
    }

    //Result printing
    for (int i = 0; i < inputs.rbegin()->first; i++) {
        if (i%period == 0){
            line_time<< std::setw(6)<<i;
            for(it_inputs = inputs.begin(); it_inputs != inputs.end();it_inputs++){
                if(it_inputs->first == i){
                    for(it_name_value = it_inputs->second.begin(); it_name_value != it_inputs->second.end();it_name_value++){
                        idx= distance(it_inputs->second.begin(), it_name_value);
                        line_inputs[idx]<< std::setw(6)<<it_name_value->second;
                    }
                }
            }
            for(it_results = results.begin(); it_results != results.end();it_results++){
                if(it_results->first == i){
                    for(it_name_value = it_results->second.begin(); it_name_value != it_results->second.end();it_name_value++){
                        idx= distance(it_results->second.begin(), it_name_value);
                        line_results[idx]<< std::setw(6)<<it_name_value->second;
                    }
                }
            }
        }
   }
    cout << line_time.str() << '\n';
    for (int i = 0; i<inputs_length; i++) {
        cout <<line_inputs[i].str()<<'\n';
    }
    for (int i = 0; i<outputs_length; i++) {
        cout <<line_results[i].str()<<'\n';
    }
}

int main(int argc, char const *argv[]) {
  string dotFile = argv[1];
  string vcdFile = argv[2];
  int period = stoi(argv[3]);
  map<int, map<string, bool>> inputs = vcdParser(vcdFile);
  map<int, map<string, bool>>::iterator it_inputs;
  map<string, bool> tmp;
  map<int, map<string, bool>> results;
  map<string, bool>::iterator it_name_value;

  Circuit a("yo", dotFile, period);

  a.parse();

  for (it_inputs = inputs.begin(); it_inputs != inputs.end(); it_inputs++) {
    std::cout << it_inputs->first << '\n';
    for (it_name_value = it_inputs->second.begin(); it_name_value!=it_inputs->second.end(); it_name_value++) {
        std::cout<<it_name_value->first<<":" << it_name_value->second << '\n';
    }
  }
  //Evaluation
  for (int i = 0; i < inputs.rbegin()->first; i++) {
      for (it_inputs = inputs.begin(); it_inputs != inputs.end(); it_inputs++) {
          if (it_inputs->first == i) {
              a.setInputValues(it_inputs->second);
              std::cout << "setInput at i = " << i<< '\n';
              tmp = it_inputs->second;
              inputs.erase(it_inputs->first);
          }
      }
      if(i%period ==0){
          // a.displayCircuit();
          results.insert(make_pair(i,a.evaluate(i)));
          inputs.insert(make_pair(i, tmp));
          a.reset();
      }
  }
  displayResults(a, inputs,results);

  return 0;
}
