#include <thread>
#include "ExampleRegistry.h"
#include "Logger.h"

#include <chrono>

void run() {
  const auto start = std::chrono::steady_clock::now();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  const auto finished = std::chrono::steady_clock::now();

  const std::chrono::duration<double> elapsed =
      finished - start;  // default unit is second
  LOG_S("Elapsed time: " << elapsed);
}

class Timing : public IExample {
 public:
  std::string group() const override { return "core/concurrency"; }
  std::string name() const override { return "Timing"; }
  std::string description() const override {
    return "The examples for <chrono> code timing";
  }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(Timing);