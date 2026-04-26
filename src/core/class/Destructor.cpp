#include <iostream>

// ** 1. Basic Destructor**
// - Generated if no destructor is declared
// - Calls destructors of members automatically
// - Does not free dynamically allocated memory unless you write it
namespace basic {
class Destructor {
 public:
  Destructor() { std::cout << "Called Destructor() \n"; }

  ~Destructor() { std::cout << "Called ~Destructor() \n"; }

  // Using `default` keyword
  // ~Destructor() = default;

  // Using `delete` // I forbid this destructor
  // ~Destructor() = delete;
};

void destructers() {
  std::cout << "\n--- Basic Destructer Examples ---\n";
  { Destructor obj; }
}
}  // namespace basic

// **2. Virtual Destructor**
namespace virtual_desctructor {
class DestructorBase  // final => cannot inherit
{
 public:
  DestructorBase() { std::cout << "Called DestructorBase() \n"; }

  virtual ~DestructorBase() { std::cout << "Called ~DestructorBase() \n"; }

  // Using `default` keyword
  // ~DestructorBase() = default;
};

class DestructorDerived : public DestructorBase {
 public:
  DestructorDerived() { std::cout << "Called DestructorDerived() \n"; }

  ~DestructorDerived() override {
    std::cout << "Called ~DestructorDerived() \n";
  }
};

void destructers() {
  std::cout << "\n--- Virtual Destructer Examples ---\n";
  DestructorDerived* derived = {new DestructorDerived()};
  DestructorBase* base{derived};
  delete base;
  // without virtual -> only call ~DestructorBase()
  // with virtual -> call ~DestructorBase() && ~DestructorDerived()
}
}  // namespace virtual_desctructor

#include "ExampleRegistry.h"

class Destructor : public IExample {
 public:
  std::string group() const override { return "core/class"; }
  std::string name() const override { return "Destructor"; }
  std::string description() const override { return ""; }
  void execute() override {
    basic::destructers();
    virtual_desctructor::destructers();
  }
};

REGISTER_EXAMPLE(Destructor, "core/class", "Destructor");
