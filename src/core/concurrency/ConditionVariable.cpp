#include <string>

#include <condition_variable>
#include <mutex>
#include <thread>

#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
std::mutex mutex;
std::condition_variable cv;

std::string data;
bool ready = false;
bool finish = false;

void worker_thread() {
  std::unique_lock lock(mutex);

  LOG("Waiting for data");

  // wait() temporarily unlocks the mutex and puts the thread to sleep, allowing other threads to modify 'ready'.
  // When notified, it wakes up, re-locks the mutex, and re-checks the condition.
  // The thread continues only when 'ready' becomes true.
  cv.wait(lock, []() { return ready; });

  LOG("Proccessing data");

  data += " after processing";
  finish = true;

  LOG("cv.notify_one");
  cv.notify_one();
}

void run() {
  LOG("Condition Example Begin");
  std::thread w_thread(worker_thread);

  // send data
  LOG("Signals data ready for processing");
  {
    std::lock_guard<std::mutex> lock(mutex);
    data = "THIS IS A PRIVATE KEY: ABCxyz123";
    ready = true;
  }

  LOG("cv.notify_one");
  cv.notify_one();  // wake up one thread waiting on this cv

  {
    std::unique_lock g_mutex(mutex);
    LOG("Waiting for finishing");
    cv.wait(g_mutex, []() { return finish; });
  }
  LOG("data: " + data);
  w_thread.join();

  LOG("Condition Example End");
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