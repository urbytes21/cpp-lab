#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include "ExampleRegistry.h"

namespace problem {
int glo_var = 0;

void f1() {
  for (size_t i = 0; i < 100000; i++) {
    glo_var += 1;
  }
}

void f2() {
  for (size_t i = 0; i < 100000; i++) {
    glo_var += 1;
  }
}

void run() {
  std::cout << "\n---Problem---\n";
  std::cout << "glo_var: " << glo_var << '\n';
  std::thread t1(f1);
  std::thread t2(f2);
  t1.join();
  t2.join();
  // expect: 200 ?
  std::cout << "glo_var: " << glo_var << '\n';
}
}  // namespace problem

namespace mutex {
int glo_var = 0;
std::mutex g_mutex;

void f1() {
  for (size_t i = 0; i < 100000; i++) {
    // anti pattern
    g_mutex.lock();
    glo_var += 1;
    g_mutex.unlock();
  }
}

void f2() {
  for (size_t i = 0; i < 100000; i++) {
    // use RAII
    std::lock_guard<std::mutex> lock(g_mutex);
    glo_var += 1;
  }
}

void run() {
  std::cout << "\n---Mutex---\n";
  std::cout << "glo_var: " << glo_var << '\n';
  std::thread t1(f1);
  std::thread t2(f2);
  t1.join();
  t2.join();
  // expect: 200 ?
  std::cout << "glo_var: " << glo_var << '\n';
}
}  // namespace mutex

namespace atomic {
std::atomic<int> glo_var = 0;

void f1() {
  for (size_t i = 0; i < 100000; i++) {
    glo_var += 1;
  }
}

void f2() {
  for (size_t i = 0; i < 100000; i++) {
    glo_var += 1;
  }
}

void run() {
  std::cout << "\n---Atomic---\n";
  std::cout << "glo_var: " << glo_var << '\n';
  std::thread t1(f1);
  std::thread t2(f2);
  t1.join();
  t2.join();
  // expect: 200 ?
  std::cout << "glo_var: " << glo_var << '\n';
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