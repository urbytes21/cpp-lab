#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include "IExample.h"

#define REGISTER_EXAMPLE(CLASS, GROUP, NAME)                        \
  namespace {                                                       \
  struct CLASS##Registrar {                                         \
    CLASS##Registrar() {                                            \
      ExampleRegistry::instance().registerExample(                  \
          GROUP, NAME, []() { return std::make_unique<CLASS>(); }); \
    }                                                               \
  };                                                                \
  static CLASS##Registrar global_##CLASS##Registrar;                \
  }

class ExampleRegistry {
 public:
  using Factory = std::function<std::unique_ptr<IExample>()>;

  static ExampleRegistry& instance() {
    static ExampleRegistry inst;
    return inst;
  }

  void registerExample(const std::string& group, const std::string& name,
                       Factory factory) {
    registry_[group][name] = std::move(factory);
  }

  const auto& getAll() const { return registry_; }

  std::unique_ptr<IExample> create(const std::string& group,
                                   const std::string& name) {

    return registry_.at(group).at(name)();
  }

 private:
  std::unordered_map<std::string, std::unordered_map<std::string, Factory>>
      registry_;
};
