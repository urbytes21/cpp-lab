// cppcheck-suppress-file [functionStatic]

// Prototype is a creational design pattern that lets you "copy existing objects" without making your code "dependent on their classes".
// Appicability:
// (*)  when your code shouldn’t depend on the concrete classes of objects that you need to copy.
// (**) when you want to reduce the number of subclasses that only differ in the way they initialize their respective objects.

// UML: docs/uml/patterns_behavioral_prototype.drawio.svg

#include <iostream>
#include <unordered_map>
#include <utility>
namespace {
namespace prototy {

/*
 * Prototype interface declares the cloning methods.
 * In most cases, it’s a single `clone` method.
 */
class IExtensionPrototype {
 public:
  virtual ~IExtensionPrototype() = default;
  virtual IExtensionPrototype* clone() = 0;
  virtual void execute() const = 0;
};

/*
 * Concrete Prototype implement an operation for cloning itself
 * In addition to copying the original object’s data to the clone,
 * this method may also handle some edge cases of the cloning process related to cloning linked objects,
 * untangling recursive dependencies, etc.
 */
class LoggerExtension : public IExtensionPrototype {
 private:
  std::string logLevel_;

 public:
  explicit LoggerExtension(std::string level = "DEBUG")
      : logLevel_{std::move(level)} {}

  IExtensionPrototype* clone() override { return new LoggerExtension(*this); }

  void execute() const override {
    std::cout << "[Logger] log level: " << logLevel_ << "\n";
  }
};

class AnalyticsExtension : public IExtensionPrototype {
 private:
  int sRate_;

 public:
  explicit AnalyticsExtension(int level = 1) : sRate_{level} {}

  IExtensionPrototype* clone() override {
    return new AnalyticsExtension(*this);
  }

  void execute() const override {
    std::cout << "[Analytics] sampling rate: " << sRate_ << "\n";
  }
};

/**
 * Prototype Registry provides an easy way to access frequently-used prototypes.
 * It stores a set of pre-built objects that are ready to be copied.
 * The simplest prototype registry is a name ^ prototype hash map.
 * However, if you need better search criteria than a simple name, you can build a much more robust version of the registry.
 */
class ExtensionPrototypeRegistry {
 private:
  std::unordered_map<std::string, IExtensionPrototype*> prototypes_;

 public:
  ~ExtensionPrototypeRegistry() {
    for (auto it = prototypes_.begin(); it != prototypes_.end();) {
      delete it->second;           // free the pointer
      it = prototypes_.erase(it);  // erase and move to next
    }
  }
  void registerExtension(const std::string& id, IExtensionPrototype* proto) {
    prototypes_[id] = proto;
  }

  IExtensionPrototype* create(const std::string& id) const {
    auto it = prototypes_.find(id);
    if (it != prototypes_.end()) {
      return it->second->clone();
    }
    return nullptr;
  }
};

/*
 * Client creates a new object by asking a prototype to clone itself
 */
namespace client {
void clientCode(const ExtensionPrototypeRegistry* const registry) {
  IExtensionPrototype* logger_etx = registry->create("logger");
  logger_etx->execute();
  IExtensionPrototype* analyx_etx = registry->create("analyze");
  analyx_etx->execute();

  delete logger_etx;
  delete analyx_etx;
}

}  // namespace client

void run() {
  auto* registry = new ExtensionPrototypeRegistry();
  registry->registerExtension("logger", new LoggerExtension("DEBUG"));
  registry->registerExtension("analyze", new AnalyticsExtension(1200));
  client::clientCode(registry);

  delete registry;
}
}  // namespace prototy
}  // namespace

#include "ExampleRegistry.h"

class PrototypeExample : public IExample {
 public:
  std::string group() const override { return "dp/creational"; }
  std::string name() const override { return "Prototype"; }
  std::string description() const override {
    return "Prototype Pattern Example";
  }
  void execute() override { prototy::run(); }
};

REGISTER_EXAMPLE(PrototypeExample, "dp/creational", "Prototype");