// cppcheck-suppress-file[]

// - + ! (-2, +3)
#include <iostream>
#include "ExampleRegistry.h"

namespace {
class Cents {
 private:
  int m_cents{};

 public:
  explicit Cents(int cents) : m_cents{cents} {}
  int getCents() const { return m_cents; }

  Cents operator-() const { return Cents{-m_cents}; }

  Cents operator+() const { return Cents{m_cents}; }

  bool operator!() const { return m_cents == 0; }
};

void run() {
  Cents c1{25};
  if (!c1 == false) {
    c1 = -c1;
    std::cout << c1.getCents();
  }
}
}  // namespace

class UnaryOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading"; }
  std::string name() const override { return "UnaryOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(UnaryOperator, "core/overloading", "UnaryOperator");