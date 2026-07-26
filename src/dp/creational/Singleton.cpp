// cppcheck-suppress-file [functionStatic]

#include <string>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
namespace singleton_pattern {

/// @class Singleton class
/// @brief defines the `GetInstance` method that serves as an alternative to constructor
class SingletonConfig {

 public:
  // 1. Should not be cloneable.
  SingletonConfig(const SingletonConfig& other) = delete;

  // 2. Should not be assignable
  SingletonConfig& operator=(const SingletonConfig& other) = delete;

  static SingletonConfig& get_instance() {
    static SingletonConfig instance;
    return instance;
  }

  void init(const std::string& input) {
    LOG(input);
    value_ = input;
  }

  const std::string& get_value() const {
    LOG("");
    return value_;
  };

 private:
  /// @brief Default constructor should always be private
  SingletonConfig() = default;
  std::string value_;
};

void run() {
  auto client_code = []() {
    LOG(SingletonConfig::get_instance().get_value());
  };

  SingletonConfig& s1 = SingletonConfig::get_instance();
  s1.init("0x001");
  client_code();

  // Singleton* s3 = new Singleton(); // ERROR
}

}  // namespace singleton_pattern
}  // namespace

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