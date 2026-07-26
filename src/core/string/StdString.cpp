#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

#include "ExampleRegistry.h"
#include "Logger.h"

namespace {

void log_string_info(const char* label, const std::string& str) {
  LOG_S(label << ": \"" << str << "\"" << " | size=" << str.size()
              << " | empty=" << std::boolalpha << str.empty());
}

}  // namespace

namespace create {

void run() {
  LOG("=== create ===");

  /// @brief Direct initialization with literal
  std::string s1 = "string 1";

  /// @brief Constructor initialization
  std::string s2("string 2");

  /// @brief Repeat character constructor
  std::string s3(5, 's');  // "sssss"

  /// @brief Concatenated string literals (compile-time)
  std::string s4 =
      "First "
      "Second";

  /// @brief Raw string literal (no escaping needed)
  std::string s5 = R"(C:\folder\file.txt)";

  log_string_info("s1", s1);
  log_string_info("s2", s2);
  log_string_info("s3", s3);
  log_string_info("s4", s4);
  log_string_info("s5", s5);
}

}  // namespace create

namespace modify {

void run() {
  LOG("=== modify ===");

  std::string str = "xPhong";
  log_string_info("init", str);

  /// @brief Append
  str.append("Nguyen");
  log_string_info("append", str);

  /// @brief Insert at position
  str.insert(6, "Vanxx");
  log_string_info("insert", str);

  /// @brief Erase by position and length
  str.erase(9, 2);
  log_string_info("erase", str);

  /// @brief Erase character using remove + erase idiom
  auto new_end = std::remove(str.begin(), str.end(), 'O');
  str.erase(new_end, str.end());
  log_string_info("erase 'O'", str);

  // C++20
  // std::erase(str, 'O');

  /// @brief Replace sub
  str.replace(0, 1, "My name is ");
  log_string_info("replace", str);

  /// @brief Convert to lowercase
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  log_string_info("tolower", str);

  /// @brief Convert to uppercase
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  log_string_info("toupper", str);

  /// @brief Trim leading whitespace
  str = "   Hello World   ";
  log_string_info("before trim", str);

  str.erase(0, str.find_first_not_of(" \t\n\r"));
  log_string_info("trim first", str);

  /// @brief Trim trailing whitespace
  str.erase(str.find_last_not_of(" \t\n\r") + 1);
  log_string_info("trim last", str);
}

}  // namespace modify

namespace sub {

void run() {
  LOG("=== sub ===");

  std::string str = "PhongNguyen";
  log_string_info("init", str);

  /// @brief Extract sub
  std::string first_name = str.substr(0, 5);
  log_string_info("substr", first_name);
}

}  // namespace sub

namespace search {

void run() {
  LOG("=== search ===");

  std::string str = "PhongNguyen";
  log_string_info("init", str);

  /// @brief Find character
  size_t pos = str.find('N');
  if (pos != std::string::npos) {
    std::string last_name = str.substr(pos);

    LOG_S("find('N')" << " | pos=" << pos << " | result=\"" << last_name
                      << "\"");
  }

  /// @brief Find sub
  pos = str.find("ong");
  if (pos != std::string::npos) {
    LOG_S("find(\"ong\")" << " | pos=" << pos);
  }

  /// @brief Find last occurrence
  pos = str.rfind('n');
  if (pos != std::string::npos) {
    LOG_S("rfind('n')" << " | pos=" << pos);
  }
}

}  // namespace search

namespace compare {

void run() {
  LOG("=== compare ===");

  std::string str1 = "PhongNguyen";
  std::string str2 = "PhongNguyen";

  /// @brief Compare strings
  int result = str1.compare(str2);
  LOG_S("compare result = " << result);
  LOG_S("equal = " << std::boolalpha << (result == 0));
}

}  // namespace compare

namespace convert {

void run() {
  LOG("=== convert ===");

  /// @brief String to integer
  std::string str_int = "3";
  int ivalue = std::stoi(str_int);
  LOG_S("stoi(\"3\") = " << ivalue);

  /// @brief String to double
  std::string str_double = "3.3";
  double dvalue = std::stod(str_double);
  LOG_S("stod(\"3.3\") = " << std::setprecision(4) << dvalue);

  /// @brief Number to string
  int value = 999;
  std::string str_value = std::to_string(value);
  log_string_info("to_string", str_value);
}

}  // namespace convert

namespace parsing {

void run() {
  LOG("=== parsing ===");

  std::string line = "a,b,c";
  log_string_info("init", line);

  /// @brief Parse CSV-like string
  char delimiter = ',';
  std::stringstream ss(line);
  std::string item;

  LOG_S("Parsing with delimiter ','");
  while (std::getline(ss, item, delimiter)) {
    LOG_S("token = " << item);
  }
}

}  // namespace parsing

class StdString : public IExample {
 public:
  std::string group() const override { return "core/string"; }
  std::string name() const override { return "StdString"; }
  std::string description() const override { return "StdString Example"; }

  void execute() override {
    create::run();
    modify::run();
    sub::run();
    search::run();
    compare::run();
    convert::run();
    parsing::run();
  }
};

REGISTER_EXAMPLE(StdString);