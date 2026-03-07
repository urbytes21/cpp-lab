#include <cstdio>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

#include "ExampleRegistry.h"

namespace StdFormat {
void run() {
  std::string name{"Phong"};
  int score = 100;

  std::string s =
      std::format("User {} has {} points, Pi: {:.2f}\n", name, score, 3.14159);

  std::cout << s;
}
}  // namespace StdFormat

namespace Concatenation {
void run() {
  std::string name{"Phong"};
  int score = 100;

  std::string s = "User " + name + " has " + std::to_string(score) +
                  " points, Pi: " + std::to_string(3.14159) + "\n";

  std::cout << s;
}
}  // namespace Concatenation

namespace Stream {
void run() {
  std::string name{"Phong"};
  int score = 100;

  std::stringstream ss;
  ss << "User " << name << " has " << score << " points, Pi: " << 3.14159
     << "\n";

  std::cout << ss.str();
}
}  // namespace Stream

namespace CStyle {
void run() {
  std::string name{"Phong"};
  int score = 100;

  char buffer[128];
  std::snprintf(buffer, sizeof(buffer), "User %s has %d points, Pi: %.2f\n",
                name.c_str(), score, 3.14159);

  std::cout << buffer;
}
}  // namespace CStyle

class StringFormatting : public IExample {
 public:
  std::string group() const override { return "core/string"; }

  std::string name() const override { return "StringFormatting"; }

  std::string description() const override {
    return "String formatting examples (format, concatenation, stream, "
           "C-style)";
  }

  void execute() override {
    StdFormat::run();
    Concatenation::run();
    Stream::run();
    CStyle::run();
  }
};

REGISTER_EXAMPLE(StringFormatting, "core/string", "StringFormatting");