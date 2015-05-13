#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <reader.hpp>
#include <writer.hpp>
#include <set>
#include <unordered_map>

using namespace std;
using namespace jam;

struct NumSystem {
  
  NumSystem(string s) : numStr(s) { }
  
  unsigned long minVal() {
    
    set<char> langChars;
    for (char c : numStr) {
      langChars.insert(c);
    }
    unsigned long numSymbols = langChars.size();
    DLOG("Found " << langChars.size() << " unique digits")
    
    if (numSymbols == 1) {
      numSymbols = 2;
      langChars.insert('*');
    }
    
    unordered_map<char, unsigned long> vals;
    
    unsigned long minVal = 0;
    unsigned long lowestAvail = 0;
    
    for (int i = 0; i < numStr.length(); ++i) {
      char c = numStr[i];
      
      if (vals.find(c) == vals.end()) {
        if (i == 0) {
          // First character always given value 1.
          vals[c] = 1;
        } else {
          vals[c] = lowestAvail;
          if (lowestAvail == 0) {
            lowestAvail = 2; // 1 was already taken by first.
          } else {
            lowestAvail++;
          }
        }
      }
      
      minVal *= numSymbols;
      minVal += vals[c];
    }
    
    return minVal;
  }
  
  string numStr;
  
};

int main(int argc, char** argv) {

  Writer w(argc, argv);
  Reader r(argc, argv);

  stringstream ss;

  int numCases = 0;
  r.nextLine(ss);
  ss >> numCases;
  
  for (int i = 0; i < numCases; ++i) {

    r.nextLine(ss);
    DLOG("Reading " << ss.str());

    string val;
    ss >> val;
    
    NumSystem n(val);

    w.out() << "Case #" << (i + 1) << ": " << n.minVal() << '\n';
  }

  return 0;
}

