// cppcheck-suppress-file [postfixOperator]

// prefix/posfix
#include <iostream>
#include "ExampleRegistry.h"

namespace {
class Cents {
 private:
  int m_cents{};

 public:
  explicit Cents(int cents) : m_cents{cents} {}
  int getCents() const { return m_cents; }

  // pre: inc -> return new
  Cents& operator++();
  Cents& operator--();

  // return old -> inc
  Cents operator++(int);
  Cents operator--(int);
};

// pre ++x/--x
Cents& Cents::operator++() {
  ++m_cents;
  return *this;
}
Cents& Cents::operator--() {
  --m_cents;
  return *this;
}

// pos x++/x--
Cents Cents::operator++(int) {
  Cents temp{*this};  // create copy
  ++(*this);          // increase origin
  return temp;        // return old
}
Cents Cents::operator--(int) {
  Cents temp{*this};
  --(*this);
  return temp;
}

void run() {
  Cents cent{25};
  cent++;
  ++cent;
  cent--;
  --cent;
  std::cout << cent.getCents() << "\n";
}
}  // namespace

class InDecOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading"; }
  std::string name() const override { return "InDecOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(InDecOperator, "core/overloading", "InDecOperator");