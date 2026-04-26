#include <iostream>
#include <sstream>
#include <string>

#include "ExampleRegistry.h"

namespace {
void run() {
  std::cout << "\n--- IO Streams Example ---\n";
  // 1) input stream

  // input source using std::stringstream
  std::string input_str{};
  std::stringstream input("input aa aa");

  // save and redirect std::cin
  auto* old_buf = std::cin.rdbuf(input.rdbuf());

  // input from keyboard,
  // std::cin >> inputStr; // skip whitespace
  std::getline(std::cin, input_str);  // get all

  // have to restore std::cin
  std::cin.rdbuf(old_buf);

  // 2) output stream
  std::cout << "[cout] " << input_str << '\n';
  std::cerr << "[cerr] " << input_str << '\n';  // unbuffered
  std::clog << "[clog] " << input_str << '\n';  // buffered
}
}  // namespace

class IOStream : public IExample {
 public:
  std::string group() const override { return "core/filehandle"; }
  std::string name() const override { return "IOStream"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(IOStream, "core/filehandle", "IOStream");