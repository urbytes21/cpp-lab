#include <iostream>
#include "ExampleRegistry.h"

#include <ctime>

namespace {
void run() {
  // **1. Get the current timestamp**
  std::time_t now = time(NULL);
  const auto* ts = ctime(&now);
  std::cout << "Current time: " << ts << '\n';

  // **2. Create the dt structure**
  struct tm datetime = *localtime(&now);
  std::cout << "Year: " << datetime.tm_year + 1900 << '\n';
  std::cout << "Current time stamp: " << mktime(&datetime) << '\n';

  // **3. Formatting**
  char output[50];
  strftime(output, 50, "%B %e, %Y", &datetime);
  std::cout << output << "\n";
  strftime(output, 50, "%I:%M:%S %p", &datetime);
  std::cout << output << "\n";
  strftime(output, 50, "%m/%d/%y", &datetime);
  std::cout << output << "\n";
  strftime(output, 50, "%a %b %e %H:%M:%S %Y", &datetime);
  std::cout << output << "\n";
}
}  // namespace

class CTime : public IExample {
 public:
  std::string group() const override { return "core/datetime"; }
  std::string name() const override { return "CTime"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(CTime, "core/datetime", "CTime");