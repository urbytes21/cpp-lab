// cppcheck-suppress-file []

// Overloading typecast

#include <iostream>
#include "ExampleRegistry.h"

namespace {
class Cents {
 private:
  int m_cents{};

 public:
  explicit Cents(int cents = 0) : m_cents{cents} {}

  // note that there is a space between operator keyword and the type we are casting
  // overloading explicit cast operator
  explicit operator int() const {
    std::cout << "explicit operator int() const\n";
    return m_cents;
  }

  int getCents() const { return m_cents; }
  void setCents(int cents) { m_cents = cents; }
};

class Dollars {
 private:
  int m_dollars{};

 public:
  // overloading non-explicit cast operator
  operator Cents() const {
    std::cout << "operator Cents() const\n";
    return Cents{m_dollars * 1000};
  }

  explicit Dollars(int dollars = 0) : m_dollars{dollars} {}
};

void printCents(Cents c) {
  // we are using explicit for the overloading operator int()
  std::cout << static_cast<int>(c);
}

void run() {
  Dollars d{100};
  printCents(d);  // Dollars -> Cents
}
}  // namespace

class TypeCast : public IExample {
 public:
  std::string group() const override { return "core/overloading"; }
  std::string name() const override { return "TypeCast"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(TypeCast, "core/overloading", "TypeCast");