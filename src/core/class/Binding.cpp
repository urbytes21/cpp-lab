// cppcheck-suppress-file [functionStatic,duplInheritedMember]
#include <iostream>
#include "ExampleRegistry.h"
namespace {
namespace EarlyBinding {
using namespace std;

class Animal {
 public:
  virtual ~Animal() = default;
  void speak() {  // NOT virtual
    cout << "Animal speaks\n";
  }
};

class Dog : public Animal {
 public:
  void speak() {  // Hides Animal::speak()
    cout << "Dog barks\n";
  }
};

void print(int x) {
  cout << "int\n";
}

void print(double x) {
  cout << "double\n";
}

void run() {
  std::cout << "\n---EarlyBinding---\n";
  Animal* a = new Dog();
  a->speak();  // Early binding: Non-virtual member function

  print(5);  // Early binding: int version chosen at compile time
  delete a;
}
}  // namespace EarlyBinding

namespace LateBinding {
using namespace std;

class Animal {
 public:
  virtual ~Animal() = default;
  virtual void speak() {  // Virtual!
    cout << "Animal speaks\n";
  }
};

class Dog : public Animal {
 public:
  void speak() override { cout << "Dog barks\n"; }
};

void run() {
  std::cout << "\n---LateBinding---\n";
  Animal* a = new Dog();
  a->speak();  // Late binding
  delete a;
}
}  // namespace LateBinding
}  // namespace

class Binding : public IExample {
  std::string group() const override { return "core/class"; };

  std::string name() const override { return "Binding"; };
  std::string description() const override { return "Binding examples"; };

  void execute() override {
    EarlyBinding::run();
    LateBinding::run();
  };
};

REGISTER_EXAMPLE(Binding, "core/class", "Binding");