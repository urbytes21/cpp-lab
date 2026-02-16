#include <iostream>
#include <sstream>
#include <string>

#include "ExampleRegistry.h"
#include "IExample.h"

namespace {
void run() {
  std::cout << "\n--- IO Streams Example ---\n";
  // 1) input stream

  // input source using std::stringstream
  std::string inputStr{};
  std::stringstream input("input aa aa");

  // save and redirect std::cin
  auto* oldBuf = std::cin.rdbuf(input.rdbuf());

  // input from keyboard,
  // std::cin >> inputStr; // skip whitespace
  std::getline(std::cin, inputStr);  // get all

  // have to restore std::cin
  std::cin.rdbuf(oldBuf);

  // 2) output stream
  std::cout << "[cout] " << inputStr << '\n';
  std::cerr << "[cerr] " << inputStr << '\n';  // unbuffered
  std::clog << "[clog] " << inputStr << '\n';  // buffered
}
}  // namespace

class IOStream : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "IOStream"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(IOStream, "core", "IOStream");