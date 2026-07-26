// cppcheck-suppress-file[]

// operator>> and operator<<
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
class Cents {
 public:
  explicit Cents(int cents) : cents_{cents} {}
  int getCents() const { return cents_; }

  //   // We won’t be able to use a member overload if the left operand is either not a class (e.g. int),
  //   // or it is a class that we can’t modify (e.g. std::ostream).
  //   // _cents << std::cout; work
  //   // std::cout << _cents; error
  //   std::ostream& operator<<(std::ostream& out) {
  //     out << m_cents;
  //     return out;
  //   }

 private:
  int cents_{};
};

/// @brief Write obj to stream
std::ostream& operator<<(std::ostream& out, const Cents& c) {
  LOG("");
  out << c.getCents();
  return out;
}

/// @brief Read obj from stream
std::istream& operator>>(std::istream& in, Cents& c) {
  LOG("");
  int cents{};
  in >> cents;
  c = in ? Cents{cents} : Cents{0};
  return in;
}

void run() {
  Cents c1{25};
  // out >>
  std::cout << c1 << "\n";

  // in >>
  std::cin >> c1;
  std::cout << c1 << "\n";

  // clearing lefover newline
  std::string line;
  std::getline(std::cin, line);
}
}  // namespace

class StreamOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading_operator"; }
  std::string name() const override { return "StreamOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(StreamOperator);