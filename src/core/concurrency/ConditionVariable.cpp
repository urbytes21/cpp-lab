#include <iostream>
#include <string>

#include <condition_variable>
#include <mutex>
#include <thread>

#include "ExampleRegistry.h"

namespace {

std::mutex mutex;
std::condition_variable cv;
std::string data;
bool ready = false;
bool finish = false;

void worker_thread() {
  std::unique_lock g_mutex(mutex);

  std::cout << "worker_thread started. Waiting for data \n";
  cv.wait(g_mutex, []() { return ready; });
  std::cout << "worker_thread proccessing data \n";
  data += " after processing";
  finish = true;
  cv.notify_one();
}

void run() {
  std::thread w_thread(worker_thread);

  // send data
  std::cout << "main_thread signals data ready for processing\n";
  {
    std::unique_lock g_mutex(mutex);
    data = "dummy data";
    ready = true;
  }
  cv.notify_one();

  // wait for worker
  {
    std::unique_lock g_mutex(mutex);
    cv.wait(g_mutex, []() { return finish; });
  }
  std::cout << "main_thread data: " << data << '\n';
  w_thread.join();
}
}  // namespace

class ConditionVariable : public IExample {

  std::string group() const override { return "core/concurrency"; }
  std::string name() const override { return "ConditionVariable"; }
  std::string description() const override {
    return "The examples for <thread> condition variable";
  }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(ConditionVariable, "core/concurrency", "ConditionVariable");