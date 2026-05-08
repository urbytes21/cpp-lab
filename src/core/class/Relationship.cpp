// cppcheck-suppress-file [functionStatic]
#include <iostream>
#include "ExampleRegistry.h"

namespace {

namespace composition {
// Engine is a part of the Car
// Engine is managed by the Car
class Engine {
 public:
  Engine() { std::cout << "Engine created\n"; }
  ~Engine() { std::cout << "Engine destroyed\n"; }
};

class Car {
 public:
  Car() { std::cout << "Car created\n"; }
  ~Car() { std::cout << "Car destroyed\n"; }

 private:
  Engine engine_;  // composition
};

void run() {
  std::cout << "\n---Composition---\n";
  Car car;
}
};  // namespace composition

namespace aggregations {
// Teacher is a part of the Department
// Teacher can belong to one or more Department
// Department does not managed Patient existence
class Teacher {
 public:
  std::string name;
  explicit Teacher(const std::string& n) : name(n) {
    std::cout << "Teacher created: " << name << "\n";
  }

  ~Teacher() { std::cout << "Teacher destroyed: " << name << "\n"; }
};

class Department {
 private:
  Teacher* teacher_;  // aggregation

 public:
  explicit Department(Teacher* t) : teacher_(t) {
    std::cout << "Department created \n";
  }

  ~Department() { std::cout << "Department destroyed \n"; }
};

void run() {
  std::cout << "\n---Aggregations---\n";
  Teacher t{"Mr.A"};
  {
    Department dep1{&t};
    Department dep2{&t};
  }
}
};  // namespace aggregations

// Doctor uses Patient
// Doctor does not managed Patient existence
namespace associations {
class Patient {
 public:
  Patient() { std::cout << "Patient created \n"; }
  ~Patient() { std::cout << "Patient destroyed \n"; }
  std::string name;
};

class Doctor {
 public:
  Doctor() { std::cout << "Doctor created \n"; }
  ~Doctor() { std::cout << "Doctor destroyed \n"; }
  void treat(const Patient& p) { std::cout << "Treating " << p.name << "\n"; }
};

void run() {
  std::cout << "\n---Associations---\n";
  Patient p{};
  Doctor d{};
  d.treat(p);
}
}  // namespace associations

// Car creates and uses Logger to log
namespace dependency {
class Logger {
 public:
  Logger() { std::cout << "Logger created \n"; }
  ~Logger() { std::cout << "Logger destroyed \n"; }

  void log(const std::string& msg) { std::cout << msg << std::endl; }
};

class Car {
 public:
  Car() { std::cout << "Car created \n"; }
  ~Car() { std::cout << "Car destroyed \n"; }

  void start() {
    std::cout << "Car started\n";
    Logger logger;  // dependency
    logger.log("Log Car started");
  }
};
void run() {
  std::cout << "\n---Dependency---\n";
  Car car{};
  car.start();
}
}  // namespace dependency

namespace container {
// class Library1 {
//  private:
//   std::vector<std::string> books;  // copy values
// };

// class Library2 {
//  private:
//   std::vector<Teacher*> teachers;  // store pointers
// };
}  // namespace container

namespace inner_class {
class Car {
 public:
  class Engine {
   public:
    void start();
  };
};
}  // namespace inner_class
}  // namespace

class Relationship : public IExample {
 public:
  std::string group() const override { return "core/class"; };

  std::string name() const override { return "Relationship"; };
  std::string description() const override { return "Relationship examples"; };

  void execute() override {
    composition::run();
    aggregations::run();
    associations::run();
    dependency::run();
  };
};

REGISTER_EXAMPLE(Relationship);