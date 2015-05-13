////////////////////////////////////////////////////////////////////////////////
///
/// @file reader.hpp
/// @brief Input helper class for Code Jam.
/// @author Zenon Parker
/// @date 2015
///
////////////////////////////////////////////////////////////////////////////////

#ifndef READER_HPP
#define READER_HPP

// std
#include <fstream>
#include <sstream>

// jam
#include <log.hpp>

namespace jam {

class Reader {
public:

  /// Read from standard input.
  Reader(int argc, char** argv) {
    if (argc > 1) {
      DLOG("Reading from input file [" << argv[1] << "]");
      input = new std::ifstream(argv[1]);
      usingFile = true;
    } else {
      DLOG("Reading from standard input.");
      input = &std::cin;
    }
  }

  ~Reader() {
    if (usingFile) {
      DLOG("Cleaning up input file handle.");
      delete input;
    }
  }

  bool eof() {
    return !(input->good());
  }

  std::istream& nextLine(std::stringstream& ss) {
    std::string temp;
    auto& ret = std::getline(*input, temp);
    ss = std::stringstream(temp);
    return ret;
  }

private:

  std::istream* input;
  bool usingFile = false;

  // No copy construction/assignment.
  Reader(const Reader&) = delete;
  Reader& operator=(const Reader&) = delete;

};

} // end namespace jam

#endif // READER_HPP

