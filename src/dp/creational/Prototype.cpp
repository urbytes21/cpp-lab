// cppcheck-suppress-file [functionStatic]

// Prototype = create new objects by cloning existing ones.
//
// Flow in this file:
//   1. Define a cloneable interface          -> IExtensionPrototype
//   2. Implement concrete prototypes         -> Logger / Analytics
//   3. (Optional) Store named presets        -> ExtensionPrototypeRegistry
//   4. Client asks registry to clone by id   -> never mentions concrete types

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
namespace prototy {

constexpr std::string_view kLoggerExtId = "logger";
constexpr std::string_view kAnalyzeId = "analyze";

/// @class Prototype interface: "I know how to copy myself."
/// @brief client code only depends on this class
class IExtensionPrototype {
 public:
  virtual ~IExtensionPrototype() = default;

  /// return a new object
  virtual std::unique_ptr<IExtensionPrototype> clone() const = 0;

  virtual void execute() const = 0;
};

/// @class Concrete Prototype
/// @brief each class copies itself
class LoggerExtension : public IExtensionPrototype {
 public:
  explicit LoggerExtension(std::string level = "DEBUG")
      : log_level_{std::move(level)} {}

  std::unique_ptr<IExtensionPrototype> clone() const override {
    return std::make_unique<LoggerExtension>(*this);
  }

  void execute() const override { LOG("log level: " + log_level_); }

 private:
  std::string log_level_;
};

class AnalyticsExtension : public IExtensionPrototype {
 public:
  explicit AnalyticsExtension(int sampling_rate = 1)
      : sampling_rate_{sampling_rate} {}

  std::unique_ptr<IExtensionPrototype> clone() const override {
    return std::make_unique<AnalyticsExtension>(*this);
  }

  void execute() const override { LOG_S("sampling rate: " << sampling_rate_); }

 private:
  int sampling_rate_;
};

/// @class Prototype Registry
/// @brief a map of named presets ready to be cloned.
class ExtensionPrototypeRegistry {
 public:
  void register_extension(std::string_view id,
                          std::unique_ptr<IExtensionPrototype> proto) {
    LOG(id);
    prototypes_[std::string(id)] = std::move(proto);
  }

  /// clone the preset for `id`. Returns nullptr if the id is unknown.
  std::unique_ptr<IExtensionPrototype> create(std::string_view id) const {
    auto it = prototypes_.find(std::string(id));
    if (it == prototypes_.end()) {
      return nullptr;
    }
    return it->second->clone();  // copy the template, leave the original intact
  }

 private:
  std::unordered_map<std::string, std::unique_ptr<IExtensionPrototype>>
      prototypes_;
};

void run() {
  // build presets once, register by name
  ExtensionPrototypeRegistry registry;
  registry.register_extension(kLoggerExtId,
                              std::make_unique<LoggerExtension>("DEBUG"));
  registry.register_extension(kAnalyzeId,
                              std::make_unique<AnalyticsExtension>(1200));

  // create-by-clone
  auto client_code = [](const ExtensionPrototypeRegistry& reg) {
    auto logger_ext = reg.create(kLoggerExtId);
    auto analytics_ext = reg.create(kAnalyzeId);

    if (logger_ext) {
      logger_ext->execute();
    }
    if (analytics_ext) {
      analytics_ext->execute();
    }
  };

  client_code(registry);
}

}  // namespace prototy
}  // namespace

class PrototypeExample : public IExample {
 public:
  std::string group() const override { return "dp/creational"; }
  std::string name() const override { return "Prototype"; }
  std::string description() const override {
    return "Clone configured objects via a prototype interface + registry";
  }
  void execute() override { prototy::run(); }
};

REGISTER_EXAMPLE(PrototypeExample);
