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
  std::weak_ptr<const AppConfig> observeConfig;
  {
    std::shared_ptr<AppConfig> config =
        std::make_shared<AppConfig>("test.server.com", 80);

    // check lock() to determine if pointer is valid
    observeConfig = config;
    if (auto tmpConfig = observeConfig.lock()) {
      std::cout << "[O] config value is: " << tmpConfig->port << " "
                << tmpConfig->server << '\n';
    } else {
      std::cout << "[O] config is expired\n";
    }
  }

  if (auto tmpConfig = observeConfig.lock()) {
    std::cout << "[O] config value is: " << tmpConfig->port << " "
              << tmpConfig->server << '\n';
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
#include "IExample.h"

class Weak : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "Weak"; }
  std::string description() const override { return "Weak Pointer Example"; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Weak, "core", "Weak");