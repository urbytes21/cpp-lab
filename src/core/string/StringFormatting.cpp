#include <cstdio>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

#include "ExampleRegistry.h"

namespace std_format {
void run() {
  std::string name{"Phong"};
  int score = 100;

  std::string s =
      std::format("User {} has {} points, Pi: {:.2f}\n", name, score, 3.14159);

  std::cout << s;
}
}  // namespace std_format

namespace concatenation {
void run() {
  std::string name{"Phong"};
  int score = 100;

  std::string s = "User " + name + " has " + std::to_string(score) +
                  " points, Pi: " + std::to_string(3.14159) + "\n";

  std::cout << s;
}
}  // namespace concatenation

namespace stream {
void run() {
  std::string name{"Phong"};
  int score = 100;

  std::stringstream ss;
  ss << "User " << name << " has " << score << " points, Pi: " << 3.14159
     << "\n";

  std::cout << ss.str();
}
}  // namespace stream

namespace c_style {
void run() {
  std::string name{"Phong"};
  int score = 100;

  char buffer[128];
  std::snprintf(buffer, sizeof(buffer), "User %s has %d points, Pi: %.2f\n",
                name.c_str(), score, 3.14159);

  std::cout << buffer;
}
}  // namespace c_style

class StringFormatting : public IExample {
 public:
  std::string group() const override { return "core/string"; }

  std::string name() const override { return "StringFormatting"; }

  std::string description() const override {
    return "String formatting examples (format, concatenation, stream, "
           "C-style)";
  }

  void execute() override {
    std_format::run();
    concatenation::run();
    stream::run();
    c_style::run();
  }
};

REGISTER_EXAMPLE(StringFormatting);