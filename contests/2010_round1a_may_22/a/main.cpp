#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <reader.hpp>
#include <writer.hpp>

using namespace std;
using namespace jam;

struct JoinK {
  
  JoinK(vector<vector<char>>&& input, int kIn) : g(input), k(kIn) { n = g.size(); }
  
  void rotate() {
    for (auto& v : g) {
      v.erase(remove(v.begin(), v.end(), '.'), v.end());
      v.insert(v.begin(), g.size() - v.size(), '.');
    }
  }
  
  bool winAt(int i, int j, char c) {
    bool winRight = false, winDown = false, winDiagRight = false, winDiagLeft = false;
    if (i <= n - k) {
      winDown = true;
      for (int x = i; x < i + k; ++x) { if (g[x][j] != c) { winDown = false; break; } }
    }
    if (j <= n - k) {
      winRight = true;
      for (int x = j; x < j + k; ++x) { if (g[i][x] != c) { winRight = false; break; } }
    }
    if (i <= n - k && j >= k - 1) {
      winDiagLeft = true;
      for (int x = 0; x < k; ++x) { if (g[i + x][j - x] != c) { winDiagLeft = false; break; } }
    }
    if (i <= n - k && j <= n - k) {
      winDiagRight = true;
      for (int x = 0; x < k; ++x) { if (g[i + x][j + x] != c) { winDiagRight = false; break; } }
    }
    return winRight || winDown || winDiagRight || winDiagLeft;
  }
  
  bool winFor(char c) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (winAt(i, j, c)) { return true; }
      }
    }
    return false;
  }
  
  void dump() {
    cout << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << g[i][j];
      }
      cout << endl;
    }
  }
  
  string result() {
    //dump();
    bool redWins = winFor('R');
    bool blueWins = winFor('B');
    if (redWins && blueWins) return "Both";
    else if (redWins) return "Red";
    else if (blueWins) return "Blue";
    else return "Neither";
  }
  
  vector<vector<char>> g;
  int k;
  size_t n = 0;
  
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
    
    int n, k;
    ss >> n >> k;
    
    vector<vector<char>> input;
    for (int j = 0; j < n; ++j) {
      r.nextLine(ss);
      string line;
      ss >> line;
      vector<char> temp;
      move(line.begin(), line.end(), back_inserter(temp));
      input.push_back(temp);
    }
    
    JoinK j(move(input), k);
    j.rotate();
    w.out() << "Case #" << (i + 1) << ": " << j.result() << '\n';
  }

  return 0;
}
