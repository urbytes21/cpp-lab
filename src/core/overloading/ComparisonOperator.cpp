// cppcheck-suppress-file[]

#include <iostream>
#include "ExampleRegistry.h"

namespace {
class Cents {
 private:
  int m_cents{};

 public:
  explicit Cents(int cents) : m_cents{cents} {}
  int getCents() const { return m_cents; }

  auto operator<=> (const Cents&) const = default;  // std 20
  // friend bool operator== (const Cents& c1, const Cents& c2) { return c1.m_cents == c2.m_cents; }
  // friend bool operator!= (const Cents& c1, const Cents& c2) { return !(operator==(c1, c2)); }

  // friend bool operator< (const Cents& c1, const Cents& c2) { return c1.m_cents < c2.m_cents; }
  // friend bool operator> (const Cents& c1, const Cents& c2) { return operator<(c2, c1); }

  // friend bool operator<= (const Cents& c1, const Cents& c2) { return !(operator>(c1, c2)); }
  // friend bool operator>= (const Cents& c1, const Cents& c2) { return !(operator<(c1, c2)); }
};

void run() {
  Cents pt1{25};
  Cents pt2{30};
  std::cout << std::boolalpha << (pt1 == pt2) << ' '  // false
            << (pt1 != pt2) << ' '                    // true
            << (pt1 < pt2) << ' '                     // true
            << (pt1 <= pt2) << ' '                    // true
            << (pt1 > pt2) << ' '                     // false
            << (pt1 >= pt2) << ' ';                   // false
}
}  // namespace

class ComparisonOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading"; }
  std::string name() const override { return "ComparisonOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(ComparisonOperator, "core/overloading", "ComparisonOperator");