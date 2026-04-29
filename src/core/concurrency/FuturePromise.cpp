#include <chrono>
#include <future>
#include <string>
#include <thread>

#include "ExampleRegistry.h"
#include "Logger.h"

namespace {

// Simulated heavy work
int heavy_work() {
  LOG("Begin (2s)");
  std::this_thread::sleep_for(std::chrono::seconds(2));
  LOG("End");
  return 1000;
}

// Shared helper to simulate main thread work
void do_other_work(std::chrono::steady_clock::time_point start) {
  for (int i = 1; i <= 4; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();
    LOG("doing other work... " + std::to_string(elapsed) + " ms");
  }
}

}  // namespace

/**
 * @brief std::async example (high-level async)
 * Prefer to implement this - run a task and give me the result later
 */
namespace async_example {

void run() {
  LOG("Begin");
  auto start = std::chrono::steady_clock::now();

  // Launch async task (guaranteed new thread)
  std::future<int> fut = std::async(std::launch::async, heavy_work);

  LOG("launched");
  do_other_work(start);

  // Wait and get result
  int result = fut.get();

  auto end = std::chrono::steady_clock::now();
  auto total =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  LOG("result = " + std::to_string(result));
  LOG("total time = " + std::to_string(total) + " ms");
  LOG("End");
}

}  // namespace async_example

/**
 * @brief std::promise + std::thread example (manual control)
 */
namespace promise_example {

void worker(std::promise<int> prom) {
  int result = heavy_work();
  prom.set_value(result);
}

void run() {
  LOG("Begin");
  auto start = std::chrono::steady_clock::now();

  // Create promise/future pair
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();

  // Launch thread manually
  std::thread t(worker, std::move(prom));

  LOG("launched");

  do_other_work(start);

  // Wait and get result
  int result = fut.get();

  auto end = std::chrono::steady_clock::now();
  auto total =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  LOG("result = " + std::to_string(result));
  LOG("total time = " + std::to_string(total) + " ms");

  t.join();

  LOG("End");
}

}  // namespace promise_example

class FuturePromise : public IExample {

  std::string group() const override { return "core/concurrency"; }
  std::string name() const override { return "FuturePromise"; }
  std::string description() const override {
    return "The examples for <future>";
  }

  void execute() override {
    async_example::run();
    promise_example::run();
  }
};

REGISTER_EXAMPLE(FuturePromise, "core/concurrency", "FuturePromise");