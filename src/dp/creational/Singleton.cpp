// cppcheck-suppress-file [functionStatic]

// Singleton is a creational design pattern that lets you ensure that a class
// has only one instance, while providing a global access point to this
// instance. Appicability:
// (*)  when a class in your program should have just a single instance
// available to all clients; for example, a single database object shared by
// different parts of the program.
// (**) when you need stricter control over global variables.

// UML: docs/uml/patterns_creational_singleton.drawio.svg

#include <string>
#include "Logger.h"

namespace {
namespace singleton_pattern {

/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Singleton {
 private:
  static inline Singleton* instance_ = nullptr;
  static inline int id_ = 0;
  int dummy_{};
  /**
   * The Singleton's constructor should always be private to prevent direct
   * construction calls with the `new` operator.
   */
  Singleton() = default;

 public:
  // 1. Should not be cloneable.
  Singleton(const Singleton& other) = delete;

  // 2. Should not be assignable
  Singleton& operator=(const Singleton& other) = delete;

  static Singleton* get_instance() {
    if (instance_ == nullptr) {
      instance_ = new Singleton();
      id_++;
    }
    LOG("id: " + std::to_string(id_));
    return instance_;
  }

  void operation() {
    LOG("id: " + std::to_string(id_));
    dummy_++;
  }
};

void run() {
  auto client_code = [](Singleton* s) {
    s->operation();
  };

  Singleton* s1 = Singleton::get_instance();
  client_code(s1);

  Singleton* s2 = Singleton::get_instance();
  client_code(s2);

  // Singleton* s3 = new Singleton(); // ERROR
}

}  // namespace singleton_pattern
}  // namespace

#include "ExampleRegistry.h"

class SingletonExample : public IExample {
 public:
  std::string group() const override { return "dp/creational"; }
  std::string name() const override { return "Singleton"; }
  std::string description() const override {
    return "Singleton Pattern Example";
  }
  void execute() override { singleton_pattern::run(); }
};

REGISTER_EXAMPLE(SingletonExample);