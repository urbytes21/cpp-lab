// cppcheck-suppress-file [functionStatic]
#include <iostream>
#include "ExampleRegistry.h"
namespace {

namespace problem {
class PoweredDevice {
 public:
  PoweredDevice() { std::cout << "Powered Device created\n"; }
  ~PoweredDevice() { std::cout << "Powered Device destroyed\n"; }
};

class Scanner : public PoweredDevice {
 public:
  Scanner() { std::cout << "Scanner created\n"; }
  ~Scanner() { std::cout << "Scanner destroyed\n"; }

  void start() { std::cout << "Scanner started\n"; }
};

class Printer : public PoweredDevice {
 public:
  Printer() { std::cout << "Printer created\n"; }
  ~Printer() { std::cout << "Printer destroyed\n"; }

  void start() { std::cout << "Printer started\n"; }
};

class Copier : public Scanner, public Printer {
 public:
  Copier() { std::cout << "Copier created\n"; }
  ~Copier() { std::cout << "Copier destroyed\n"; }
};

void run() {
  std::cout << "\n---Problem---\n";
  Copier c{};
  std::cout << "\n";
  c.Scanner::start();
  c.Printer::start();
  std::cout << "\n";
  // Output:
  // Powered Device created <-- multiple "instances" of the Powered Device appearing in an inheritance hierarchy
  // Scanner created
  // Powered Device created <--
  // Printer created
  // Copier created

  // Scanner started
  // Printer started
  // Copier destroyed
  // Printer destroyed
  // Powered Device destroyed
  // Scanner destroyed
  // Powered Device destroyed
}

}  // namespace Problem

namespace virtual_base_classes {
class PoweredDevice {
 public:
  PoweredDevice() { std::cout << "Powered Device created\n"; }
  ~PoweredDevice() { std::cout << "Powered Device destroyed\n"; }
};

class Scanner : public virtual PoweredDevice {
 public:
  Scanner() { std::cout << "Scanner created\n"; }
  ~Scanner() { std::cout << "Scanner destroyed\n"; }

  void start() { std::cout << "Scanner started\n"; }
};

class Printer : public virtual PoweredDevice {
 public:
  Printer() { std::cout << "Printer created\n"; }
  ~Printer() { std::cout << "Printer destroyed\n"; }

  void start() { std::cout << "Printer started\n"; }
};

class Copier : public Scanner, public Printer {
 public:
  Copier() { std::cout << "Copier created\n"; }
  ~Copier() { std::cout << "Copier destroyed\n"; }
};

void run() {
  std::cout << "\n---Solved by Virtual Base Class---\n";
  // The most derived class is responsible for constructing the virtual base class (Copier)
  Copier c{};
  std::cout << "\n";
  c.Scanner::start();
  c.Printer::start();
  std::cout << "\n";
  // Output:
  // Powered Device created <-- there is only one base object
  // Scanner created
  // Printer created
  // Copier created

  // Scanner started
  // Printer started

  // Copier destroyed
  // Printer destroyed
  // Scanner destroyed
  // Powered Device destroyed
}
}  // namespace VirtualBaseClasses
}  // namespace

class VirtualBase : public IExample {
  std::string group() const override { return "core/class"; };

  std::string name() const override { return "VirtualBase"; };
  std::string description() const override { return "VirtualBase examples"; };

  void execute() override {
    problem::run();
    virtual_base_classes::run();
  };
};

REGISTER_EXAMPLE(VirtualBase, "core/class", "VirtualBase");