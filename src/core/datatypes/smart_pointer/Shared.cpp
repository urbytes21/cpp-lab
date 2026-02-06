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

// Module A
class NetworkManager {
 public:
  explicit NetworkManager(std::shared_ptr<const AppConfig> cfg)
      : mConfig(std::move(cfg)) {}

  void connect() const {
    std::cout << "Connecting to " << mConfig->server << ":" << mConfig->port
              << "\n";
  }

 private:
  // const means we cannot modify config at this point
  std::shared_ptr<const AppConfig> mConfig;
};

// Module B
class Logger {
 public:
  explicit Logger(std::shared_ptr<const AppConfig> cfg)
      : mConfig(std::move(cfg)) {}

  void log_start() const {
    std::cout << "Logging enabled for " << mConfig->server << "\n";
  }

 private:
  std::shared_ptr<const AppConfig> mConfig;
};

void run() {
  // auto config = std::make_shared<AppConfig>("api.example.com", 443);
  std::shared_ptr<AppConfig> config =
      std::make_shared<AppConfig>("test.server.com", 80);

  NetworkManager net(config);
  Logger logger(config);

  net.connect();
  logger.log_start();

  std::cout << "use_count = " << config.use_count() << "\n";
  config->setPort(8080);
  net.connect();
  logger.log_start();
}

}  // namespace

struct SharedRunner {
  SharedRunner() {
    std::cout << "\n--- Shared Pointer Example ---\n";
    run();
  }
};

static SharedRunner autoRunner;