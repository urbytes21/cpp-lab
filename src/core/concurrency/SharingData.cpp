#include <thread>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {

int global_variable = 9;

// Pass-by-value
void set_global(int arg) {
  LOG("arg: " + std::to_string(arg));
  global_variable = 100;
  LOG("global_variable: " + std::to_string(global_variable));
}

void set_local(int& arg) {
  //   thread_local int thread_local_variable = 1;
  LOG("arg: " + std::to_string(arg));
  arg = 100;
  LOG("arg: " + std::to_string(arg));
}

void run() {
  int local_variable = 10;
  std::cout << "local: " << local_variable << '\n';
  std::cout << "global: " << global_variable << '\n';

  std::thread thread1(set_global, local_variable);
  thread1.join();

  std::cout << "local: " << local_variable << '\n';
  std::cout << "global: " << global_variable << '\n';

  std::thread thread2(set_local, std::ref(local_variable));
  thread2.join();
  std::cout << "local: " << local_variable << '\n';
}
}  // namespace

class SharingData : public IExample {

  std::string group() const override { return "core/concurrency"; }
  std::string name() const override { return "SharingData"; }
  std::string description() const override {
    return "The examples for <thread> sharing data";
  }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(SharingData, "core/concurrency", "SharingData");