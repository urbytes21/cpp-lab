#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include "ExampleRegistry.h"

namespace create {
void run() {
  // 1. Direct initialization with literal
  std::string s1 = "string 1";

  // 2. Constructor initialization
  std::string s2("string 2");

  // 3. Repeat character constructor
  std::string s3(5, 's');  // "sssss"

  // 4. Concatenated string literals (compile-time)
  std::string s4 =
      "First "
      "Second";  // -> "First Second"

  // 5. Raw string literal (no escaping needed)
  std::string s5 = R"(C:\folder\file.txt)";

  // Print results
  std::cout << "s1: " << s1 << '\n';
  std::cout << "s2: " << s2 << '\n';
  std::cout << "s3: " << s3 << '\n';
  std::cout << "s4: " << s4 << '\n';
  std::cout << "s5: " << s5 << '\n';
}
}  // namespace create

namespace modify {
void run() {
  std::string ss = "xPhong";
  std::cout << "init      : " << ss << '\n';

  // append
  ss.append("Nguyen");
  std::cout << "append    : " << ss << '\n';

  // insert at position
  ss.insert(6, "Vanxx");
  std::cout << "insert    : " << ss << '\n';

  // erase (pos, length)
  ss.erase(9, 2);
  std::cout << "erase     : " << ss << '\n';

  // erase char using pos
  auto new_end = std::remove(ss.begin(), ss.end(), 'O');
  ss.erase(new_end, ss.end());
  std::cout << "erase 'O')  : " << ss << '\n';
  // #include <algorithm>
  // std::erase(ss, '\n');

  // replace (pos, length, new_string)
  ss.replace(0, 1, "My name is ");
  std::cout << "replace   : " << ss << '\n';

  // convert case
  std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
  std::cout << "tolower   : " << ss << '\n';
  std::transform(ss.begin(), ss.end(), ss.begin(), ::toupper);
  std::cout << "toupper   : " << ss << '\n';

  // trim white
  ss.erase(0, ss.find_first_not_of(" \t\n\r"));
  std::cout << "trim first   : " << ss << '\n';
  ss.erase(ss.find_last_not_of(" \t\n\r") + 1);
  std::cout << "trim last   : " << ss << '\n';
}
}  // namespace modify

namespace sub {
void run() {
  std::string ss = "PhongNguyen";
  std::cout << "init      : " << ss << '\n';
  std::string first_name = ss.substr(0, 5);
  std::cout << "sub     : " << first_name << '\n';
}
}  // namespace sub

namespace search {
void run() {
  std::string ss = "PhongNguyen";
  std::cout << "init           : " << ss << '\n';

  // find char
  size_t pos = ss.find('N');
  if (pos != std::string::npos) {
    std::string second_name = ss.substr(pos);  // from pos to end (default)
    std::cout << "find 'N'       : at " << pos << " -> " << second_name << '\n';
  }

  // find substring
  pos = ss.find("ong");
  if (pos != std::string::npos) {
    std::cout << "find \"ong\"    : at " << pos << '\n';
  }

  // find last occurrence
  pos = ss.rfind('n');
  if (pos != std::string::npos) {
    std::cout << "rfind 'n'      : at " << pos << '\n';
  }
}
}  // namespace search

namespace compare {
void run() {
  std::string ss1 = "PhongNguyen";
  std::string ss2 = "PhongNguyen";

  int result = ss1.compare(ss2);

  std::cout << "compare result : " << result << '\n';
  std::cout << "equal ?        : " << std::boolalpha << (result == 0) << '\n';
}

}  // namespace compare

namespace convert {
void run() {
  // string -> int
  std::string sint = "3";
  int ivalue = std::stoi(sint);
  std::cout << "stoi           : " << ivalue << '\n';

  // string -> double
  std::string sdouble = "3.3";
  double dvalue = std::stod(sdouble);
  std::cout << "stod           : " << std::setprecision(4) << dvalue << '\n';

  // number -> string
  int value = 999;
  std::string svalue = std::to_string(value);
  std::cout << "to_string      : " << svalue << '\n';
}
}  // namespace convert

namespace parsing {
void run() {
  std::string line = "a,b,c";
  std::cout << "init      : " << line << '\n';
  char deli = ',';
  std::stringstream ss(line);
  std::string item;

  std::cout << "Parsing with delimiter ',': \n";
  while (std::getline(ss, item, deli)) {
    std::cout << item << std::endl;
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
