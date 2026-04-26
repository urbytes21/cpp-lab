#include <iostream>
#include <thread>
#include "ExampleRegistry.h"

namespace {
int glo_var = 99;

void f1(int arg) {
  std::cout << "arg: " << arg << '\n';
  glo_var = 100;
}

void f2(int& arg) {
  //   thread_local int thread_loc_var = 1;
  std::cout << "arg: " << arg << '\n';
  arg = 100;
}

void run() {
  int loc_var = 10;
  std::cout << "loc_var: " << loc_var << '\n';
  std::cout << "glo_var: " << glo_var << '\n';

  std::thread t1(f1, loc_var);
  t1.join();
  std::cout << "loc_var: " << loc_var << '\n';
  std::cout << "glo_var: " << glo_var << '\n';

  std::thread t2(f2, std::ref(loc_var));
  t2.join();
  std::cout << "loc_var: " << loc_var << '\n';
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