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
  string dotFile = argv[1];
  string vcdFile = argv[2];
  map<int, map<string, bool>> inputs = vcdParser(vcdFile);
  map<int, map<string, bool>>::iterator it_inputs;
  vector<int> timings;
  vector<int>::iterator it_timings;
  map<int, map<string, bool>> results;
  map<int, map<string, bool>>::iterator it_results;
  map<string, bool>::iterator it_name_value;

  vector<string> input_names;
  vector<string> output_names;
  vector<string>::iterator it_v;
  int idx;
  int diff =0;
  ostringstream line_time;
  line_time <<"Time : ";


  Circuit a("yo", dotFile);

  a.parse();
  input_names = a.getInputNames();
  output_names = a.getOutputNames();
  int inputs_length = input_names.size();
  int outputs_length = input_names.size();
  ostringstream line_results[outputs_length];
  ostringstream line_inputs[inputs_length];

  for (it_v = input_names.begin(); it_v != input_names.end(); it_v++) {
      idx= distance(input_names.begin(), it_v);
      diff = 7- it_v->length();
      line_inputs[idx] << *it_v <<std::setw(diff) <<":";
  }
  for (it_v = output_names.begin(); it_v != output_names.end(); it_v++) {
      idx= distance(output_names.begin(), it_v);
      diff = 7- it_v->length();
      line_results[idx]<<*it_v<<std::setw(diff) <<":";
  }

  //Remplissage du vecteur de timings
  for (it_inputs = inputs.begin(); it_inputs != inputs.end(); it_inputs++) {
      timings.push_back(it_inputs->first);
      line_time<< std::setw(6)<<it_inputs->first;
  }

  //Evaluation
  for (it_inputs = inputs.begin(); it_inputs != inputs.end(); it_inputs++) {
      a.setInputValues(it_inputs->second);
      results.insert(make_pair(it_inputs->first,a.evaluate()));
      a.reset();
  }
  //Result printing
  for (it_timings = timings.begin(); it_timings != timings.end(); it_timings++) {
      for(it_inputs = inputs.begin(); it_inputs != inputs.end();it_inputs++){
          if(it_inputs->first == *it_timings){
              for(it_name_value = it_inputs->second.begin(); it_name_value != it_inputs->second.end();it_name_value++){
                  idx= distance(it_inputs->second.begin(), it_name_value);
                  line_inputs[idx]<< std::setw(6)<<it_name_value->second;
              }
          }
      }
      for(it_results = results.begin(); it_results != results.end();it_results++){
          if(it_results->first == *it_timings){
              for(it_name_value = it_results->second.begin(); it_name_value != it_results->second.end();it_name_value++){
                  idx= distance(it_results->second.begin(), it_name_value);
                  line_results[idx]<< std::setw(6)<<it_name_value->second;
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
  return 0;
}
