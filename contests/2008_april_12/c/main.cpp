#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <reader.hpp>
#include <writer.hpp>

using namespace std;
using namespace jam;

// TODO: Not complete and inefficient!

struct EggDrop {
  
  EggDrop(long ff, long dd, long bb) : f(ff), d(dd), b(bb) {}
  
  static bool solvableBrute(long f, long d, long b) {
    
    if (b == 0 || d == 0) {
      return false;
    }
    
    if (d >= f && b >= 1) {
      return true;
    }
    
    if (f == 1) {
      return (d >= 1 && b >= 1);
    }
    
    bool oneSolvable = false;
    
    for (int i = 1; i <= f; ++i) {
      bool thisSolvable = solvableBrute(i - 1, d - 1, b - 1) &&
                          solvableBrute(f - i, d - 1, b);
      if (thisSolvable) {
        DLOG("Split at: " << i << " [" << f << ", " << d << ", " << b << "] solvable")
        return true;
      }
      oneSolvable |= thisSolvable;
    }
    
    return oneSolvable;
  }
  
  static bool solvable(long f, long d, long b) {
    if (b == 0 || d == 0) {
      return false;
    }
   
    if (d >= f && b >= 1) {
      return true;
    }
   
    if (f == 1) {
      return (d >= 1 && b >= 1);
    }
    
    long splitFloor = ceil(double(f) / 2.0) - max(d - b, long(0)) + (1 - (f % 2));
    splitFloor = max(splitFloor, 1L);
    
    bool solvBottom = false;
    bool solvTop = false;
    
    if (splitFloor == 1) {
      solvBottom = true;
      solvTop = solvable(f - splitFloor, d - 1, b);
    } else {
      solvBottom = solvable(splitFloor - 1, d - 1, b - 1);
      if (solvBottom) {
        solvTop = solvable(f - splitFloor, d - 1, b);
      }
    }
    
    DLOG("Split at: " << splitFloor << " [" << f << ", " << d << ", " << b << "] bottom " << (solvBottom ? "YES" : "NO"))
    DLOG("Split at: " << splitFloor << " [" << f << ", " << d << ", " << b << "] top " << (solvTop ? "YES" : "NO"))
    
    return solvBottom && solvTop;
  }
  
  long maxF() {
    double jump = f;
    double i = double(f) + jump;
    double min = double(f);
    
    // Find top end.
    while (solvable(long(i), d, b)) {
      if (i >= 4294967296L) { return -1; }
      jump *= 2.0;
      i += jump;
    }
    
    double max = i;
    
    // Binary search range between [min, max].
    long maxSuccess = -1;
    while (abs(max - min) > 0.5) {
      long thisTest = long((max + min) / 2.0);
      if (solvable(thisTest, d, b)) {
        if (thisTest >= 4294967296L) { return -1; }
        maxSuccess = std::max(thisTest, maxSuccess);
        min += (max - min) / 2.0;
      } else {
        max -= (max - min) / 2.0;
      }
    }
    
    return maxSuccess;
  }
  
  long minD() {
    long i = d - 1;
    while (solvable(f, i, b)) {
      --i;
    }
    return i + 1;
  }
  
  long minB() {
    long i = b - 1;
    while (solvable(f, d, i)) {
      --i;
    }
    return i + 1;
  }
  
  long f, d, b;
  
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

    long f, d, b;
    ss >> f >> d >> b;
    
    EggDrop ed(f, d, b);

    w.out() << "Case #" << (i + 1) << ": " << ed.maxF() << " "
            << ed.minD() << " " << ed.minB() << endl;
  }

  return 0;
}
