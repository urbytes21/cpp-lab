#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>

#include "ExampleRegistry.h"

namespace Async {
int async_worker() {
  std::cout << "[worker] started, needs 2000 ms\n";
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "[worker] finished\n";
  return 1000;
}

void run() {
  std::cout << "\n=== std::promise/std::future example ===\n";
  auto start = std::chrono::steady_clock::now();

  // launch heavy_work asynchronously and get a future
  std::future<int> futur =
      std::async(std::launch::async, []() { return async_worker(); });

  std::cout << "[main] async launched\n";
  for (int i = 1; i <= 4; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();

    std::cout << "[main] doing other work... " << elapsed << " ms\n";
  }

  // get result
  int result = futur.get();

  auto end = std::chrono::steady_clock::now();
  auto total =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "[main] result = " << result << '\n';
  std::cout << "[main] total time = " << total << " ms\n";
}

}  // namespace Async

namespace Simple {
void promise_worker(std::promise<int>* prom) {
  std::cout << "[worker] started, needs 2000 ms\n";
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "[worker] finished\n";
  prom->set_value(100);
}

void run() {
  std::cout << "\n=== std::async example ===\n";
  auto start = std::chrono::steady_clock::now();

  // create a promise and future
  std::promise<int> promis;
  std::future<int> futur = promis.get_future();

  // start heavy work async
  std::thread thread(promise_worker, &promis);

  std::cout << "[main] async launched\n";
  for (int i = 1; i <= 4; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();

    std::cout << "[main] doing other work... " << elapsed << " ms\n";
  }

  // get result
  int result = futur.get();

  auto end = std::chrono::steady_clock::now();
  auto total =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  std::cout << "[main] result = " << result << '\n';
  std::cout << "[main] total time = " << total << " ms\n";

  thread.join();
}

}  // namespace Simple

class FuturePromise : public IExample {

  std::string group() const override { return "core/concurrency"; }
  std::string name() const override { return "FuturePromise"; }
  std::string description() const override {
    return "The examples for <future>";
  }

  void execute() override {
    Async::run();

    Simple::run();
  }
};

REGISTER_EXAMPLE(FuturePromise, "core/concurrency", "FuturePromise");