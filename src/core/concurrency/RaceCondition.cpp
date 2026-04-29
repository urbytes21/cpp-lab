#include <atomic>
#include <mutex>
#include <thread>
#include "ExampleRegistry.h"
#include "Logger.h"

template <typename F, typename T>
void run_case(const std::string& name, F work, T& global) {
  global = 0;
  LOG(name + "Begin");
  std::cout << "global_variable: " << global << '\n';

  std::thread thread1(work);
  std::thread thread2(work);

  thread1.join();
  thread2.join();

  std::cout << "global_variable: " << global << '\n';
  LOG(name + "End");
}

/**
 * @brief Race Condition Problem
 */
namespace problem {
int global_variable = 0;

void run() {
  auto work = []() {
    for (int i = 0; i < 100000; ++i) {
      global_variable++;
    }
  };
  run_case("Problem", work, global_variable);
}
}  // namespace problem

/**
 * @brief Mutex Example
 */
namespace mutex {
int global_variable = 0;
std::mutex g_mutex;

void run() {
  auto work = []() {
    for (int i = 0; i < 100000; ++i) {
      // // anti pattern
      // g_mutex.lock();
      // global_variable += 1;
      // g_mutex.unlock();

      // a RAII lock for mutex
      std::lock_guard<std::mutex> log(g_mutex);
      global_variable++;
    }
  };

  run_case("Mutex", work, global_variable);
}
}  // namespace mutex

/**
 * @brief Atomic Example 
 */
namespace atomic {
std::atomic<int> global_variable = 0;

void run() {
  auto work = []() {
    for (int i = 0; i < 100000; ++i) {
      global_variable++;
    }
  };

  run_case("Atomic", work, global_variable);
}
}  // namespace atomic

class RaceCondition : public IExample {

  std::string group() const override { return "core/concurrency"; }
  std::string name() const override { return "RaceCondition"; }
  std::string description() const override {
    return "The examples for <thread> race condition";
  }

  void execute() override {
    problem::run();
    atomic::run();
    mutex::run();
  }
};

REGISTER_EXAMPLE(RaceCondition, "core/concurrency", "RaceCondition");