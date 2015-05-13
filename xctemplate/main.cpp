#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <reader.hpp>
#include <writer.hpp>

using namespace std;
using namespace jam;

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

    w.out() << "Case #" << (i + 1) << ": " << val << '\n';
  }

  return 0;
}

