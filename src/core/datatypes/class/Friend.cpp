// cppcheck-suppress-file [functionStatic]
#include <iostream>
#include "ExampleRegistry.h"
namespace {
namespace NonMember {

class Accumulator {
 private:
  int value_{0};

 public:
  void add(int value) { value_ += value; }

  // print out the Accumulator use <<
  // S1: Overloading
  std::ostream& operator<<(std::ostream& os) const {
    os << "S1: " << value_ << "\n";
    return os;
  }

  // S2: Friend
  friend std::ostream& operator<<(std::ostream& os, const Accumulator& acc);
};

std::ostream& operator<<(std::ostream& os, const Accumulator& acc) {
  os << "S2: " << acc.value_ << "\n";
  return os;
}

void run() {
  Accumulator acc{};
  acc.add(5);

  // Use S1:
  acc << std::cout;  // backward and weird

  // Use S2: expect std::cout << acc;
  std::cout << acc;  // good
}

}  // namespace NonMember

namespace Member {
class Accumulator;
class Display {
 public:
  void f_display(const Accumulator& acc) const;

  void display(const Accumulator& acc) const;
};

class Accumulator {
 private:
  int value_{0};

 public:
  void add(int value) { value_ += value; }

  // Make Display class a friend of Acc
  friend void Display::f_display(const Accumulator& acc) const;
};

void Display::f_display(const Accumulator& acc) const{
  std::cout << "S4: " << acc.value_ << "\n";
}

void Display::display(const Accumulator& acc) const {
  // std::cout << "S4: " << acc.value_ << "\n"; // cannot access
}

void run() {
  Accumulator acc{};
  acc.add(-99);
  Display d{};
  d.display(acc);
  d.f_display(acc);
}
}  // namespace Member

}  // namespace

namespace Class {

class Display;
class Accumulator {
 private:
  int value_{0};

 public:
  void add(int value) { value_ += value; }

  // Make Display class a friend of Acc
  friend class Display;
};

class Display {
 public:
  void display(const Accumulator& acc) {
    std::cout << "S3: " << acc.value_ << "\n";
  }
};

void run() {
  Accumulator acc{};
  acc.add(99);
  Display d{};
  d.display(acc);
}
}  // namespace Class

class Friend : public IExample {
  std::string group() const override { return "core/class"; };

  std::string name() const override { return "Friend"; };
  std::string description() const override { return "Friend examples"; };

  void execute() override {
    NonMember::run();
    Member::run();
    Class::run();
  };
};

REGISTER_EXAMPLE(Friend, "core/class", "Friend");