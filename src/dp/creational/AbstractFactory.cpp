// cppcheck-suppress-file [functionStatic]

// Abstract Factory is a creational design pattern that lets you produce
// families of related objects without specifying their concrete classes.
// Appicability:
// (*)  when your code needs to work with various families of related products,
//      but you don’t want it to depend on the concrete classes
//      of those products—they might be unknown beforehand or you simply want to
//      allow for future extensibility.
// (**) when you have a class with a set of Factory Methods that blur its
//      primary responsibility.

// UML: docs/uml/patterns_creational_abstractfactory.drawio.svg
#include <memory>
#include <string>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
namespace abstract_factory {
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
    LOG("sudo apt update && sudo apt install -y gdb && gdb --version");
  }
};

class WindowsGdbProduct : public IGdbProduct {
 public:
  void launch() const override {
    LOG("pacman -Syu mingw-w64-x86_64-gdb && gdb --version");
  }
};

class MacOsGdbProduct : public IGdbProduct {
 public:
  void launch() const override { LOG("brew install gdb && gdb --version"); }
};

class ICMakeProduct {
 public:
  virtual ~ICMakeProduct() = default;
  virtual void launch() const = 0;
};

class LinuxCMakeProduct : public ICMakeProduct {
 public:
  void launch() const override {
    LOG("sudo apt update && sudo apt install -y cmake && cmake --version");
  }
};

class WindowsCMakeProduct : public ICMakeProduct {
 public:
  void launch() const override { LOG("pacman -Syu cmake && cmake --version"); }
};

class MacOsCMakeProduct : public ICMakeProduct {
 public:
  void launch() const override {
    LOG("\tbrew install cmake && cmake --version");
  }
};

// ===================================================================================

/*
 * Abstract Factory
 * provides an abstract interface for creating a family of products
 */
class IProductAbstractFactory {
 public:
  virtual ~IProductAbstractFactory() = default;
  virtual IGdbProduct* create_gdb_product() = 0;
  virtual ICMakeProduct* create_cmake_product() = 0;
};

/*
 * Concrete Factory
 * each concrete factory create a family of products and client uses
 * one of these factories so it never has to instantiate a product object
 */
class WindowsProductFactory : public IProductAbstractFactory {
 public:
  IGdbProduct* create_gdb_product() override { return new WindowsGdbProduct(); }
  ICMakeProduct* create_cmake_product() override {
    return new WindowsCMakeProduct();
  }
};

class LinuxProductFactory : public IProductAbstractFactory {
 public:
  IGdbProduct* create_gdb_product() override { return new LinuxGdbProduct(); }
  ICMakeProduct* create_cmake_product() override {
    return new LinuxCMakeProduct();
  }
};

class MacOsProductFactory : public IProductAbstractFactory {
 public:
  IGdbProduct* create_gdb_product() override { return new MacOsGdbProduct(); }
  ICMakeProduct* create_cmake_product() override {
    return new MacOsCMakeProduct();
  }
};

// ===================================================================================

// static redudant inside anonymous namespace
IProductAbstractFactory* create_product_factory(const std::string& os) {
  if (os == "linux") {
    return new LinuxProductFactory();
  }
  if (os == "windows") {
    return new WindowsProductFactory();
  }
  if (os == "macos") {
    return new MacOsProductFactory();
  }
  LOG("OS not support yet - " + os);

  return nullptr;
}

void run() {
  LOG("Abstract Factory Pattern Example");

  /**
  * The client code works with factories and products only through abstract
  * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
  * product subclass to the client code without breaking it.
  */
  auto client_code = [](IProductAbstractFactory* f) {
    ICMakeProduct* cmake = f->create_cmake_product();
    IGdbProduct* gdb = f->create_gdb_product();
    cmake->launch();
    gdb->launch();

    delete cmake;
    delete gdb;
  };

  std::string os = "linux";
  IProductAbstractFactory* factory = create_product_factory(os);
  client_code(factory);
  delete factory;
}
}  // namespace abstract_factory
}  // namespace

class AbstractFactoryExample : public IExample {
 public:
  std::string group() const override { return "dp/creational"; }
  std::string name() const override { return "AbstractFactory"; }
  std::string description() const override {
    return "AbstractFactory Pattern Example";
  }
  void execute() override { abstract_factory::run(); }
};

REGISTER_EXAMPLE(AbstractFactoryExample);