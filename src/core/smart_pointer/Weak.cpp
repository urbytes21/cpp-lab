#include <iostream>
#include <memory>
#include <string>
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

void run() {
  std::weak_ptr<const AppConfig> observe_config;
  {
    std::shared_ptr<AppConfig> config =
        std::make_shared<AppConfig>("test.server.com", 80);

    // check lock() to determine if pointer is valid
    observe_config = config;
    if (auto tmp_config = observe_config.lock()) {
      std::cout << "[O] config value is: " << tmp_config->port << " "
                << tmp_config->server << '\n';
    } else {
      std::cout << "[O] config is expired\n";
    }
  }

  if (auto tmp_config = observe_config.lock()) {
    std::cout << "[O] config value is: " << tmp_config->port << " "
              << tmp_config->server << '\n';
  } else {
    std::cout << "[O] config is expired\n";
  }
}

}  // namespace

/**
 * wp.expired() == false // at least one shared_ptr still owns it
 * wp.lock() != nullptr  // same condition
 */
#include "ExampleRegistry.h"

class Weak : public IExample {
 public:
  std::string group() const override { return "core/smart_pointer"; }
  std::string name() const override { return "Weak"; }
  std::string description() const override { return "Weak Pointer Example"; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Weak, "core/smart_pointer", "Weak");