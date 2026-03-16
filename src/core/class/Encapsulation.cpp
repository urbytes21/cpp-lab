// Encapsulation means grouping data and the functions that use that data
// inside a single unit, usually a class.

// Benefits of encapsulation:

// 1. Data Hiding
// The internal data of a class can be hidden from outside code.
// Other code cannot directly modify it, which helps protect the object's state.

// 2. Modularity
// Data and related functions are organized in one place.
// This makes the code easier to understand, maintain, and test.

// 3. Flexibility and Maintainability
// The internal implementation of a class can change without affecting
// the code that uses it, as long as the public interface stays the same.

// 4. Improved Security
// Restricting access to internal data helps prevent unintended or incorrect use.

// Implementation in C++:
// Encapsulation is implemented using access specifiers such as
// `private` and `protected` to restrict access to class members.
// Public getter and setter functions can be used to access or modify
// the internal data in a controlled way.

#include <ExampleRegistry.h>
#include <iostream>
#include <string>

namespace {
class Person {
 private:
  std::string name_;
  int age_;

 public:
  Person(const std::string& name, int age) : name_(name), age_(age) {}

  std::string getName() const { return name_; }
  int getAge() const { return age_; }

  void setAge(int age) {
    if (age >= 0) {
      age_ = age;
    }
  }

  void introduce() const {
    std::cout << "Name: " << name_ << ", Age: " << age_ << '\n';
  }
};

void run() {
  Person person("Alice", 25);

  std::cout << "Initial state:\n";
  person.introduce();

  std::cout << "\nUpdating age through setter:\n";
  person.setAge(30);
  person.introduce();

  std::cout << "\nAccessing data through getters:\n";
  std::cout << "Name: " << person.getName() << '\n';
  std::cout << "Age: " << person.getAge() << '\n';
}

}  // namespace

class Encapsulation : public IExample {
  std::string group() const override { return "core/class"; }
  std::string name() const override { return "Encapsulation"; }
  std::string description() const override {
    return "Examples demonstrating encapsulation in C++";
  }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(Encapsulation, "core/class", "Encapsulation");