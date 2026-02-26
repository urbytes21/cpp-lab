// cppcheck-suppress-file [unreadVariable]

// Overloading operator=

#include <iostream>
#include "ExampleRegistry.h"

namespace {
class Cents {
 private:
  int m_cents{};

 public:
  explicit Cents(int cents = 0) : m_cents{cents} {}

  int getCents() const { return m_cents; }
  void setCents(int cents) { m_cents = cents; }

  // Copy constructor
  Cents(const Cents& other) {
    std::cout << "Cents(const Cents& other)\n";
    m_cents = other.m_cents;
  }

  // Overload copy assignment
  Cents& operator=(const Cents& cents) {
    // do the copy
    std::cout << "Cents& operator=(const Cents& cents)\n";
    m_cents = cents.m_cents;
    return *this;
  }
};

void run() {
  Cents c1{100};
  Cents c2;
  c2 = c1;        // calls overloaded copy assignment
  Cents c3 = c1;  // calls copy constructor because c3 didn't exist yet
}
}  // namespace

class AssignmentOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading"; }
  std::string name() const override { return "AssignmentOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(AssignmentOperator, "core/overloading", "AssignmentOperator");