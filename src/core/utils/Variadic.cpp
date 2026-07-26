#include <cstdarg>  // va_list, va_start, va_arg, va_end
#include <string>

#include "ExampleRegistry.h"
#include "Logger.h"

namespace c_variadic_style {

/// @brief Simple C-style variadic function
/// The format string controls how arguments are read:
///   d -> int
///   c -> char
///   f -> double
void simple_printf(const char* fmt, ...) {
  // Holds all unnamed arguments
  va_list args;

  va_start(args, fmt);  // reading the unnamed arguments that come after fmt

  // Parse format string character by character
  while (*fmt != '\0') {
    if (*fmt == 'd') {
      // Read next argument as int
      int value = va_arg(args, int);
      LOG(std::to_string(value));

    } else if (*fmt == 'c') {
      // char is promoted to int in variadic functions
      int value = va_arg(args, int);
      LOG(std::string(1, static_cast<char>(value)));

    } else if (*fmt == 'f') {
      // float is promoted to double
      double value = va_arg(args, double);
      LOG(std::to_string(value));
    }

    ++fmt;
  }

  // Cleanup
  va_end(args);
}

void run() {
  LOG("C-Style Variadic Example");

  simple_printf("dcff", 3, 'a', 1.999, 42.5);
}

}  // namespace c_variadic_style

namespace modern_variadic_style {

/// @brief Base case for recursion
inline void simple_printf(const char* /*fmt*/) {}

/// @brief Print one argument based on format specifier
template <typename T>
void print_arg(char fmt, const T& value) {
  switch (fmt) {
    case 'd':
      LOG(std::to_string(static_cast<int>(value)));
      break;

    case 'c':
      LOG(std::string(1, static_cast<char>(value)));
      break;

    case 'f':
      LOG(std::to_string(static_cast<double>(value)));
      break;

    default:
      throw std::runtime_error("Unknown format specifier");
  }
}

/// @brief Recursive variadic template implementation
template <typename T, typename... Args>
void simple_printf(const char* fmt, T value, Args... args) {
  if (*fmt == '\0') {
    return;
  }

  print_arg(*fmt, value);

  // Move to next format character
  simple_printf(fmt + 1, args...);
}

void run() {
  LOG("Modern Variadic Example");

  simple_printf("dcff", 3, 'a', 1.999, 42.5);
}

}  // namespace modern_variadic_style

class Variadic : public IExample {
 public:
  std::string group() const override { return "core/utils"; }
  std::string name() const override { return "Variadic"; }
  std::string description() const override {
    return "Examples for C-style variadic arguments";
  }

  void execute() override {
    c_variadic_style::run();
    modern_variadic_style::run();
  }
};

REGISTER_EXAMPLE(Variadic);