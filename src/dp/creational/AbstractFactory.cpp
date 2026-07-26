// cppcheck-suppress-file [functionStatic]

// Abstract Factory is a creational design pattern that lets you produce
// families of related objects without specifying their concrete classes.

#include <memory>
#include <string>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
namespace abstract_factory {

/// @class Product Interface
/// @brief Declares the operations that all concrete products must implement
class IGdbProduct {
 public:
  virtual ~IGdbProduct() = default;
  virtual void launch() const = 0;
};

/// @brief The concrete product
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

/// @class Abstract Factory
/// @brief Provide abstract interface for creating a family of products
class IProductAbstractFactory {
 public:
  virtual ~IProductAbstractFactory() = default;
  virtual std::unique_ptr<IGdbProduct> create_gdb_product() = 0;
  virtual std::unique_ptr<ICMakeProduct> create_cmake_product() = 0;
};

/// @class Concrete Factory
/// @brief concrete factory create a family of products and client uses
/// one of these factories so it never has to instantiate a product object
class WindowsProductFactory : public IProductAbstractFactory {
 public:
  std::unique_ptr<IGdbProduct> create_gdb_product() override {
    return std::make_unique<WindowsGdbProduct>();
  }
  std::unique_ptr<ICMakeProduct> create_cmake_product() override {
    return std::make_unique<WindowsCMakeProduct>();
  }
};

class LinuxProductFactory : public IProductAbstractFactory {
 public:
  std::unique_ptr<IGdbProduct> create_gdb_product() override {
    return std::make_unique<LinuxGdbProduct>();
  }

  std::unique_ptr<ICMakeProduct> create_cmake_product() override {
    return std::make_unique<LinuxCMakeProduct>();
  }
};

class MacOsProductFactory : public IProductAbstractFactory {
 public:
  std::unique_ptr<IGdbProduct> create_gdb_product() override {
    return std::make_unique<MacOsGdbProduct>();
  }

  std::unique_ptr<ICMakeProduct> create_cmake_product() override {
    return std::make_unique<MacOsCMakeProduct>();
  }
};

/// @brief Factory selector
/// static redudant inside anonymous namespace
std::unique_ptr<IProductAbstractFactory> create_product_factory(
    const std::string& os) {
  if (os == "linux") {
    return std::make_unique<LinuxProductFactory>();
  }
  if (os == "windows") {
    return std::make_unique<WindowsProductFactory>();
  }
  if (os == "macos") {
    return std::make_unique<MacOsProductFactory>();
  }
  LOG("OS not support yet - " + os);

  return nullptr;
}

void run() {
  LOG("Abstract Factory Pattern Example");

  auto client_code = [](IProductAbstractFactory* f) {
    auto cmake = f->create_cmake_product();
    auto gdb = f->create_gdb_product();
    cmake->launch();
    gdb->launch();
  };

  const std::string os = "linux";
  auto factory = create_product_factory(os);
  client_code(factory.get());
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