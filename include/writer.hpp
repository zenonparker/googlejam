////////////////////////////////////////////////////////////////////////////////
///
/// @file writer.hpp
/// @brief Output helper class for Code Jam.
/// @author Zenon Parker
/// @date 2015
///
////////////////////////////////////////////////////////////////////////////////

#ifndef WRITER_HPP
#define WRITER_HPP

// std
#include <fstream>

namespace jam {

class Writer {
public:

  /// Write to standard output.
  Writer(int argc, char** argv) {
    if (argc > 2) {
      DEBUG("Writing to output file [" << argv[2] << "]");
      output = new std::ofstream(argv[2]);
      usingFile = true;
    } else {
      DEBUG("Writing to standard output.");
      output = &std::cout;
    }
  }

  ~Writer() {
    if (usingFile) {
      DEBUG("Cleaning up output file handle.");
      delete output;
    }
  }

  std::ostream& out() {
    return *output;
  }

private:

  std::ostream* output;
  bool usingFile = false;

  // No copy construction/assignment.
  Writer(const Writer&) = delete;
  Writer& operator=(const Writer&) = delete;

};

} // end namespace jam

#endif // WRITER_HPP

