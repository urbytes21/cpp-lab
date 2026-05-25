#include <cstdio>
#include <format>
#include <iomanip>
#include <sstream>
#include <string>

#include "ExampleRegistry.h"
#include "Logger.h"

namespace {

void log_formatted(const char* method, const std::string& text) {
  LOG_S(method << ": \"" << text << "\"" << " | size=" << text.size());
}

}  // namespace

namespace std_format {

void run() {
  LOG("=== std_format ===");

  std::string name{"Phong"};
  int score = 100;

  /// @brief C++20 std::format
  std::string str =
      std::format("User {} has {} points, Pi: {:.2f}", name, score, 3.14159);
  log_formatted("std::format", str);
}

}  // namespace std_format

namespace concatenation {

void run() {
  LOG("=== concatenation ===");

  std::string name{"Phong"};
  int score = 100;

  /// @brief String concatenation using operator+
  std::string str = "User " + name + " has " + std::to_string(score) +
                    " points, Pi: " + std::to_string(3.14159);
  log_formatted("concatenation", str);
}

}  // namespace concatenation

namespace stream {

void run() {
  LOG("=== stream ===");

  std::string name{"Phong"};
  int score = 100;

  /// @brief String formatting using stringstream
  std::stringstream ss;
  ss << "User " << name << " has " << score << " points, Pi: " << std::fixed
     << std::setprecision(2) << 3.14159;
  log_formatted("stringstream", ss.str());
}

}  // namespace stream

namespace c_style {

void run() {
  LOG("=== c_style ===");

  std::string name{"Phong"};
  int score = 100;

  /// @brief C-style formatting using snprintf
  char buffer[128];
  std::snprintf(buffer, sizeof(buffer), "User %s has %d points, Pi: %.2f",
                name.c_str(), score, 3.14159);
  log_formatted("snprintf", buffer);
}

}  // namespace c_style

class StringFormatting : public IExample {
 public:
  std::string group() const override { return "core/string"; }
  std::string name() const override { return "StringFormatting"; }
  std::string description() const override {
    return "String formatting examples "
           "(std::format, concatenation, stringstream, C-style)";
  }

  void execute() override {
    std_format::run();
    concatenation::run();
    stream::run();
    c_style::run();
  }
};

REGISTER_EXAMPLE(StringFormatting);