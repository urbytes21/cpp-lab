#include <chrono>
#include <iostream>
#include <thread>
#include "ExampleRegistry.h"

namespace {
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
  std::cout << "glo_var: " << glo_var << '\n';
  std::thread t1(f1);
  std::thread t2(f2);
  t1.join();
  t2.join();
  // expect: 200 ?
  std::cout << "glo_var: " << glo_var << '\n';
}
}  // namespace

class RaceCondition : public IExample {

  std::string group() const { return "core/concurrency"; }
  std::string name() const { return "RaceCondition"; }
  std::string description() const {
    return "The examples for <thread> race condition";
  }

  void execute() { run(); }
};

REGISTER_EXAMPLE(RaceCondition, "core/concurrency", "RaceCondition");