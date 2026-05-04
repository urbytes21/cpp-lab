// cppcheck-suppress-file [functionStatic]

// Factory Method is a creational design pattern that provides an interface for
// creating objects in a superclass, but allows subclasses to alter the type of
// objects that will be created. Appicability:
// (*)  when you don’t know beforehand the exact types and dependencies of the
// objects your code should work with.
// (**) when you want to provide users of your library or framework with a way
// to extend its internal components.
// (***)when you want to save system resources by reusing existing objects
// instead of rebuilding them each time.

// UML: docs/uml/patterns_creational_factorymethod.drawio.svg

#include <iostream>
#include <string>
namespace {
namespace factory_method {
/**
 * The Product interface declares the operations that all concrete products must
 * implement.
 */
class IGdbProduct {
 public:
  virtual ~IGdbProduct() = default;
  virtual void launch() const = 0;
};

/**
 * Concrete Products provide various implementations of the Product interface.
 */
class LinuxGdbProduct : public IGdbProduct {
 public:
  void launch() const override {
    std::cout
        << "\tsudo apt update && sudo apt install -y gdb && gdb --version\n";
  }
};

class WindowsGdbProduct : public IGdbProduct {
 public:
  void launch() const override {
    std::cout << "\tpacman -Syu mingw-w64-x86_64-gdb && gdb --version\n";
  }
};

class MacOsGdbProduct : public IGdbProduct {
 public:
  void launch() const override {
    std::cout << "\tbrew install gdb && gdb --version\n";
  }
};

// ===================================================================================

/**
 * The Creator class declares the factory method that is supposed to return an
 * object of a Product class. The Creator's subclasses usually provide the
 * implementation of this method. (a.k.a IGdbFactory)
 */
class IGdbFactory {
 public:
  virtual ~IGdbFactory() = default;
  virtual IGdbProduct* factoryMethod() = 0;
  virtual void launchGdb() = 0;
};

class AbstractGdbFactory : public IGdbFactory {
 public:
  // Call the factory method to create a Product object.
  void launchGdb() final {
    IGdbProduct* gdb = this->factoryMethod();
    gdb->launch();
    delete gdb;
  }
};

/**
 * Concrete Creators override the factory method in order to change the
 * resulting product's type.
 */
class WindowsGdbFactory : public AbstractGdbFactory {
 public:
  IGdbProduct* factoryMethod() override { return new WindowsGdbProduct(); }
};

class LinuxGdbFactory : public AbstractGdbFactory {
 public:
  IGdbProduct* factoryMethod() override { return new LinuxGdbProduct(); }
};

class MacOsGdbFactory : public AbstractGdbFactory {
 public:
  IGdbProduct* factoryMethod() override { return new MacOsGdbProduct(); }
};

// ===================================================================================

/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
namespace client_code {
void clientCode(IGdbFactory* gdb) {
  if (gdb != nullptr)
    gdb->launchGdb();
}
}  // namespace client_code

IGdbFactory* createGdbFactory(const std::string& os) {
  if (os == "linux") {
    return new LinuxGdbFactory();
  }
  if (os == "windows") {
    return new WindowsGdbFactory();
  }
  if (os == "macos") {
    return new MacOsGdbFactory();
  }
  std::cout << "OS not support yet - " << os << "\n";
  return nullptr;
}

void run() {
  std::string os = "linux";
  IGdbFactory* gdb = createGdbFactory(os);
  client_code::clientCode(gdb);
  delete gdb;
}
}  // namespace factory_method
}  // namespace

#include "ExampleRegistry.h"

class FactoryMethodExample : public IExample {
 public:
  std::string group() const override { return "dp/creational"; }
  std::string name() const override { return "FactoryMethod"; }
  std::string description() const override {
    return "FactoryMethod Pattern Example";
  }
  void execute() override { factory_method::run(); }
};

REGISTER_EXAMPLE(FactoryMethodExample);