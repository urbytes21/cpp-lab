// cppcheck-suppress-file[]
// + - * /
#include <iostream>
#include "ExampleRegistry.h"

namespace {
class Cents {
 private:
  int m_cents_{};

 public:
  explicit Cents(int cents) : m_cents_{cents} {}
  int getCents() const { return m_cents_; }

  // Problem: A member operator only works when the left-hand operand is an object of the class (e.g., Cents).
  // Cents sum = 5 + s1;
  // int.operator+(5)
  // => error
  //   Cents operator+(const Cents& other) {
  //     return Cents{this->getCents() + other.getCents()};
  //   }

  // For operands of different types
  friend Cents operator+(int v1, const Cents& c2) {
    return Cents{v1 + c2.getCents()};
  }

  friend Cents operator+(const Cents& c1, int v2) {
    return Cents{v2 + c1.getCents()};
  }

  // ArithmeticOperator operators
  friend Cents operator+(const Cents& c1, const Cents& c2) {
    return Cents{c1.getCents() + c2.getCents()};
  }

  friend Cents operator-(const Cents& c1, const Cents& c2) {
    return Cents{c1.getCents() - c2.getCents()};
  }

  friend Cents operator*(const Cents& c1, const Cents& c2) {
    return Cents{c1.getCents() * c2.getCents()};
  }

  friend Cents operator/(const Cents& c1, const Cents& c2) {
    return Cents{c1.getCents() / c2.getCents()};
  }
};

void run() {
  Cents c1{25};
  Cents c2{75};

  // Sum
  Cents sum = c1 + c2;
  Cents sum2 = operator+(125, c2);
  std::cout << "Sum: " << sum.getCents() << " " << sum2.getCents() << std::endl;

  // Sub
  Cents sub = c1 - c2;
  std::cout << "Sub: " << sub.getCents() << std::endl;

  // Div
  Cents div = c1 / c2;
  std::cout << "Div: " << div.getCents() << std::endl;

  // Mul
  Cents mul = c1 * c2;
  std::cout << "Mul: " << mul.getCents() << std::endl;
}
}  // namespace

class ArithmeticOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading_operator"; }
  std::string name() const override { return "ArithmeticOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(ArithmeticOperator);