#include <ostream>
#include <sstream>
#include <string>
#include "Logger.h"

#include "ExampleRegistry.h"

namespace {

namespace terminal_color_code {

inline constexpr const char* kReset = "\033[0m";
inline constexpr const char* kBlack = "\033[30m";
inline constexpr const char* kRed = "\033[31m";
inline constexpr const char* kGreen = "\033[32m";
inline constexpr const char* kYellow = "\033[33m";
inline constexpr const char* kBlue = "\033[34m";
inline constexpr const char* kMagenta = "\033[35m";
inline constexpr const char* kCyan = "\033[36m";
inline constexpr const char* kWhite = "\033[37m";

// Bold variants
inline constexpr const char* kBoldBlack = "\033[1m\033[30m";
inline constexpr const char* kBoldRed = "\033[1m\033[31m";
inline constexpr const char* kBoldGreen = "\033[1m\033[32m";
inline constexpr const char* kBoldYellow = "\033[1m\033[33m";
inline constexpr const char* kBoldBlue = "\033[1m\033[34m";
inline constexpr const char* kBoldMagenta = "\033[1m\033[35m";
inline constexpr const char* kBoldCyan = "\033[1m\033[36m";
inline constexpr const char* kBoldWhite = "\033[1m\033[37m";
}  // namespace terminal_color_code

void run() {
  LOG("Terminal Color Example");

  std::ostringstream oss;

  oss.str("");
  oss << terminal_color_code::kRed << "RED" << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBlack << "BLACK" << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kGreen << "GREEN" << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kYellow << "YELLOW"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBlue << "BLUE" << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kMagenta << "MAGENTA"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kCyan << "CYAN" << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kWhite << "WHITE" << terminal_color_code::kReset;
  LOG(oss.str());

  // Bold variants
  oss.str("");
  oss << terminal_color_code::kBoldRed << "BOLD RED"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBoldGreen << "BOLD GREEN"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBoldBlue << "BOLD BLUE"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBoldCyan << "BOLD CYAN"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBoldMagenta << "BOLD MAGENTA"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBoldWhite << "BOLD WHITE"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBoldYellow << "BOLD YELLOW"
      << terminal_color_code::kReset;
  LOG(oss.str());

  oss.str("");
  oss << terminal_color_code::kBoldBlack << "BOLD BLACK"
      << terminal_color_code::kReset;
  LOG(oss.str());
}
}  // namespace

class TerminalColor : public IExample {
 public:
  std::string group() const override { return "core/filehandle"; }
  std::string name() const override { return "TerminalColor"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(TerminalColor);