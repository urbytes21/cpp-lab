// cppcheck-suppress-file[]

// >> <<
#include <iostream>
#include "ExampleRegistry.h"

namespace {
class Cents {
 private:
  int m_cents_{};

 public:
  explicit Cents(int cents) : m_cents_{cents} {}
  int getCents() const { return m_cents_; }

  //   // We won’t be able to use a member overload if the left operand is either not a class (e.g. int),
  //   // or it is a class that we can’t modify (e.g. std::ostream).
  //   // _cents << std::cout; work
  //   // std::cout << _cents; error
  //   std::ostream& operator<<(std::ostream& out) {
  //     out << m_cents;
  //     return out;
  //   }
};

std::ostream& operator<<(std::ostream& out, const Cents& c) {
  out << c.getCents();
  return out;
}

std::istream& operator>>(std::istream& in, Cents& c) {
  int cents{};
  in >> cents;
  c = in ? Cents{cents} : Cents{0};
  return in;
}

void run() {
  Cents c1{25};
  // out >>
  std::cout
      << c1
      << "\n";  // operator<<(std::cout, c1) -> operator<<(std::ostream,Cents)

  // in >>
  std::cin >> c1;  // operator>>(std::cin,c1) -> operator<<(std::istream,Cents)
  std::cout << c1 << "\n";

  // clearing lefover newline
  std::string line;
  std::getline(std::cin, line);
}
}  // namespace

class IOOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading"; }
  std::string name() const override { return "IOOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(IOOperator, "core/overloading", "IOOperator");