#include <iostream>
#include <memory>
#include <string>
#include "Logger.h"

namespace {
// Shared resource rather than copy to optimize memory
struct AppConfig {
  std::string server;
  int port;

  AppConfig(std::string s, int p) : server(std::move(s)), port(p) {
    std::cout << "Config loaded\n";
  }

  void setPort(int p) { port = p; }

  ~AppConfig() { std::cout << "Config destroyed\n"; }
};

void validatePointer(const std::weak_ptr<AppConfig>& wp) {
  if (auto tmp = wp.lock()) {
    LOG("config value is: " + std::to_string(tmp->port) + " " + tmp->server);
  } else {
    LOG("config is expired");
  }
}

/**
 * wp.expired() == false // at least one shared_ptr still owns it
 * wp.lock() != nullptr  // same condition
 */
void run() {
  std::weak_ptr<AppConfig> observer;
  {
    std::shared_ptr<AppConfig> config =
        std::make_shared<AppConfig>("test.server.com", 80);

    // check lock() to determine if pointer is valid
    observer = config;
    std::cout << "use_count: " << config.use_count() << "\n";
    std::cout << "expired? " << std::boolalpha << observer.expired() << "\n";
    validatePointer(observer);
  }

  // now the config is expired
  std::cout << "expired? " << std::boolalpha << observer.expired() << "\n";
  validatePointer(observer);
}

}  // namespace

#include "ExampleRegistry.h"

class Weak : public IExample {
 public:
  std::string group() const override { return "core/smart_pointer"; }
  std::string name() const override { return "Weak"; }
  std::string description() const override { return "Weak Pointer Example"; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Weak, "core/smart_pointer", "Weak");