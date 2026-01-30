#include <iostream>
#include <sstream>
#include <string>
namespace {
void run() {
  std::cout << "\n--- String Stream Example ---\n";

  std::stringstream os{};

  // input
  os << "0xF";
  std::cout << os.str();

  // Note: After changing .str(), always call .clear() before reading.
  os.str("0x1 0x2");
  os.clear();
  std::cout << os.str();

  // output
  std::string bytesStr = os.str();
  std::cout << bytesStr;

  os.str("0x0 0xF 0xE 0x2");
  os.clear();
  os >> bytesStr;
  std::cout << bytesStr;

  // conversions
  int byte_low = 0xFFF;
  int byte_high = 0x001;
  os.clear();
  os << byte_low << ' ' << byte_high;
  std::cout << os.str();
}
}  // namespace

struct StringStreamRunner {
  StringStreamRunner() { run(); }
};

static StringStreamRunner autoRunner;