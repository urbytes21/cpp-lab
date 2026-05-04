// cppcheck-suppress-file [functionStatic,duplInheritedMember]

#include <iostream>
#include "ExampleRegistry.h"

namespace {
namespace early_binding {

class Animal {
 public:
  virtual ~Animal() = default;
  void speak() {  // NOT virtual
    std::cout << "Animal speaks\n";
    dump_++;
  }

 protected:
  int dump_{0};
};

class Dog : public Animal {
 public:
  void speak() {  // Hides Animal::speak()
    std::cout << "Dog barks\n";
    dump_++;
  }
};

void print(int x) {
  std::cout << "int: " << x << "\n";
}

void print(double x) {
  std::cout << "double: " << x << "\n";
}

void run() {
  std::cout << "\n---EarlyBinding---\n";
  Animal* a = new Dog();
  a->speak();  // Early binding: Non-virtual member function

  print(5);     // Early binding: int version chosen at compile time
  print(0.5F);  // Early binding: float version chosen at compile time
  delete a;
}
}  // namespace early_binding

namespace late_binding {
class Animal {
 public:
  virtual ~Animal() = default;
  virtual void speak() {  // Virtual!
    std::cout << "Animal speaks\n";
  }
};

class Dog : public Animal {
 public:
  void speak() override { std::cout << "Dog barks\n"; }
};

void run() {
  std::cout << "\n---LateBinding---\n";
  Animal* a = new Dog();
  a->speak();  // Late binding
  delete a;
}
}  // namespace late_binding
}  // namespace

class Binding : public IExample {
 public:
  std::string group() const override { return "core/class"; };

  std::string name() const override { return "Binding"; };
  std::string description() const override { return "Binding examples"; };

  void execute() override {
    early_binding::run();
    late_binding::run();
  };
};

REGISTER_EXAMPLE(Binding);