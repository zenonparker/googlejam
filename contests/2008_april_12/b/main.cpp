#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <reader.hpp>
#include <writer.hpp>

using namespace std;
using namespace jam;

enum class Direction : char { N, S, E, W };

struct Room {
  Room() {
    // Default all walls exist. (Can't travel N, S, E, or W)
    n = s = e = w = false;
  }

  char legendValue() const {
    //Character   Can walk north?   Can walk south?   Can walk west?    Can walk east?  
    //  1 Yes No  No  No
    //  2 No  Yes No  No
    //  3 Yes Yes No  No
    //  4 No  No  Yes No
    //  5 Yes No  Yes No
    //  6 No  Yes Yes No
    //  7 Yes Yes Yes No
    //  8 No  No  No  Yes
    //  9 Yes No  No  Yes
    //  a No  Yes No  Yes
    //  b Yes Yes No  Yes
    //  c No  No  Yes Yes
    //  d Yes No  Yes Yes
    //  e No  Yes Yes Yes
    //  f Yes Yes Yes Yes
    if (n == true && s == false && w == false && e == false) { return '1'; }
    if (n == false && s == true && w == false && e == false) { return '2'; }
    if (n == true && s == true && w == false && e == false) { return '3'; }
    if (n == false && s == false && w == true && e == false) { return '4'; }
    if (n == true && s == false && w == true && e == false) { return '5'; }
    if (n == false && s == true && w == true && e == false) { return '6'; }
    if (n == true && s == true && w == true && e == false) { return '7'; }
    if (n == false && s == false && w == false && e == true) { return '8'; }
    if (n == true && s == false && w == false && e == true) { return '9'; }
    if (n == false && s == true && w == false && e == true) { return 'a'; }
    if (n == true && s == true && w == false && e == true) { return 'b'; }
    if (n == false && s == false && w == true && e == true) { return 'c'; }
    if (n == true && s == false && w == true && e == true) { return 'd'; }
    if (n == false && s == true && w == true && e == true) { return 'e'; }
    if (n == true && s == true && w == true && e == true) { return 'f'; }
    return ' ';
  }

  bool n, s, e, w;
};

struct Maze {

  Maze() : grid(1, vector<Room>(1)) {
  }

  void addRow(bool top = false) {
    if (top) {
      grid.insert(grid.begin(), vector<Room>(grid[0].size()));
      ++row;
    } else {
      grid.push_back(vector<Room>(grid[0].size()));
    }
    DEBUG("Grid is " << grid.size() << "x" << grid[0].size() << " after addRow().");
  }

  void addCol(bool left = false) {
    for (auto& thisRow : grid) {
      if (left) {
        thisRow.insert(thisRow.begin(), Room());
      } else {
        thisRow.push_back(Room());
      }
    }
    if (left) { ++col; }
    DEBUG("Grid is " << grid.size() << "x" << grid[0].size() << " after addCol().");
  }

  Room& curRoom() {
    return grid[row][col];
  }

  void move(Direction d) {
    switch (d) {
      case Direction::N:
        curRoom().n = true;
        if (row == 0) { addRow(true); }
        --row;
        curRoom().s = true;
        break;
      case Direction::E:
        curRoom().e = true;
        if (col == grid[0].size() - 1) { addCol(false); }
        ++col;
        curRoom().w = true;
        break;
      case Direction::S:
        curRoom().s = true;
        if (row == grid.size() - 1) { addRow(false); }
        ++row;
        curRoom().n = true;
        break;
      default: // W
        curRoom().w = true;
        if (col == 0) { addCol(true); }
        --col;
        curRoom().e = true;
        break;
    }
  }

  void performAction(char action) {
    if (action == 'W') {
      move(dir);
    } else if (action == 'R') {
      switch (dir) {
        case Direction::N: dir = Direction::E; break;
        case Direction::E: dir = Direction::S; break;
        case Direction::S: dir = Direction::W; break;
        default: /* W */ dir = Direction::N; break;
      }
    } else if (action == 'L') {
      switch (dir) {
        case Direction::N: dir = Direction::W; break;
        case Direction::E: dir = Direction::N; break;
        case Direction::S: dir = Direction::E; break;
        default: /* W */ dir = Direction::S; break;
      }
    }
    DEBUG("Player at " << row << "," << col << " after move '" << action << "'");
  }

  void reverse() {
    DEBUG("Reversing!");
    finishSide = dir;
    performAction('R');
    performAction('R');
  }

  void dump(ostream& out) {
    int rowRangeEnd = grid.size();
    int colRangeStart = 0;
    int colRangeEnd = grid[0].size();

    if (finishSide == Direction::S) { --rowRangeEnd; }
    if (finishSide == Direction::E) { --colRangeEnd; }
    if (finishSide == Direction::W) { ++colRangeStart; }

    for (int r = 1; r < rowRangeEnd; ++r) {
      const auto& row = grid[r];

      for (int c = colRangeStart; c < colRangeEnd; ++c) {
        out << row[c].legendValue();
      }

      out << '\n';
    }
  }

  int row = 0;
  int col = 0;
  Direction finishSide = Direction::W;
  Direction dir = Direction::S; // Always start on north wall going south.
  vector<vector<Room>> grid;
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

    DEBUG("Reading " << ss.str());

    string forward, backward;
    ss >> forward >> backward;

    Maze m;
    for (char action : forward) {
      m.performAction(action);
    }
    m.reverse();
    for (char action : backward) {
      m.performAction(action);
    }

    w.out() << "Case #" << (i + 1) << ": \n";
    m.dump(w.out());
  }

  return 0;
}

