// cppcheck-suppress-file [functionStatic]

// Flow in this file:
//   1. Define a product interface            -> IGdbProduct
//   2. Implement concrete products           -> Linux / Windows / MacOs Gdb
//   3. Define a creator interface            -> IGdbFactory (+ AbstractGdbFactory)
//   4. Implement concrete creators           -> Linux / Windows / MacOs factories
//   5. Client picks a factory, then uses it  -> never constructs products directly

#include <memory>
#include <string>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
namespace factory_method {

/// @class Product Interface
class IGdbProduct {
 public:
  virtual ~IGdbProduct() = default;
  virtual void launch() const = 0;
};

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

/// @class Creator Interface
class IGdbFactory {
 public:
  virtual ~IGdbFactory() = default;
  virtual std::unique_ptr<IGdbProduct> factory_method() = 0;
  virtual void launch_gdb() = 0;
};

class AbstractGdbFactory : public IGdbFactory {
 public:
  /// @brief call the factory method to create a Product object
  /// execute operation
  void launch_gdb() final {
    auto gdb = this->factory_method();
    gdb->launch();
  }
};

class WindowsGdbFactory : public AbstractGdbFactory {
 public:
  std::unique_ptr<IGdbProduct> factory_method() override {
    return std::make_unique<WindowsGdbProduct>();
  }
};

class LinuxGdbFactory : public AbstractGdbFactory {
 public:
  std::unique_ptr<IGdbProduct> factory_method() override {
    return std::make_unique<LinuxGdbProduct>();
  }
};

class MacOsGdbFactory : public AbstractGdbFactory {
 public:
  std::unique_ptr<IGdbProduct> factory_method() override {
    return std::make_unique<MacOsGdbProduct>();
  }
};

/// @brief selector
std::unique_ptr<IGdbFactory> create_gdb_factory(const std::string& os) {
  if (os == "linux") {
    return std::make_unique<LinuxGdbFactory>();
  }
  if (os == "windows") {
    return std::make_unique<WindowsGdbFactory>();
  }
  if (os == "macos") {
    return std::make_unique<MacOsGdbFactory>();
  }
  LOG("OS not support yet - " + os);
  return nullptr;
}

void run() {
  auto client_code = [](IGdbFactory* gdb) {
    if (gdb != nullptr) {
      gdb->launch_gdb();
    }
  };

  // Create factory base on the os
  {
    const std::string os = "linux";
    auto gdb = create_gdb_factory(os);

    client_code(gdb.get());
  }
  {
    const std::string os = "windows";
    auto gdb = create_gdb_factory(os);

    client_code(gdb.get());
  }
  {
    const std::string os = "macos";
    auto gdb = create_gdb_factory(os);

    client_code(gdb.get());
  }
  {
    const std::string os = "unknown";
    auto gdb = create_gdb_factory(os);
    client_code(gdb.get());
  }
}
}  // namespace factory_method
}  // namespace

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