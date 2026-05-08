#include <chrono>  // chrono::millisecond()
#include <stdexcept>
#include <thread>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {

/**
   * @brief Check whether the thread is joinable
   * joinable() tells you whether a std::thread is still owned and needs to be handled (joined or detached).
   * @param thread 
   */
void checkJoinable(std::thread& thread) {
  if (thread.joinable()) {
    LOG("Thread Object is joinable.");
  } else {
    LOG("Thread Object is not joinable.");
  }
}
}  // namespace

/**
 * @brief Thread Exception Example
 */
namespace exception_before_join {
class ThreadGuard {
 public:
  explicit ThreadGuard(std::thread& thread);
  ~ThreadGuard();

  // no copy & move
  ThreadGuard operator=(const ThreadGuard& other) = delete;
  ThreadGuard(const ThreadGuard& other) = delete;
  ThreadGuard& operator=(ThreadGuard&& other) noexcept = delete;
  ThreadGuard(ThreadGuard&& other) noexcept = delete;

 private:
  std::thread& thread_;
};

ThreadGuard::ThreadGuard(std::thread& thread) : thread_{thread} {}

ThreadGuard::~ThreadGuard() {
  if (thread_.joinable()) {
    thread_.join();
  }
}

void callable() {
  LOG("begin");
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  LOG("end");
}

void exceptionThrow() {
  throw std::runtime_error("callable runtime exception");
}

void run() {
  LOG("Thread Exception Example Begin");
  std::thread thread(callable);

  // try {
  //   exceptionThrow();
  //   thread.join();
  // } catch (...) {
  //   thread.join();
  // }

  ThreadGuard tg(thread);
  try {
    exceptionThrow();
  } catch (...) {}
  LOG("Thread Exception Example End");
}

}  // namespace exception_before_join

/**
 * @brief Thread Detach Example
 */
namespace detach {
void foo() {
  LOG("begin");
  std::this_thread::sleep_for(std::chrono::microseconds(1000));
  LOG("end");
}

void bar() {
  LOG("begin");
  std::this_thread::sleep_for(std::chrono::microseconds(2000));
  LOG("end");
}

void run() {
  LOG("Thread Detach Example Begin");

  std::thread foo_thread(foo);
  std::thread bar_thread(bar);

  bar_thread
      .detach();  // https://stackoverflow.com/questions/22803600/when-should-i-use-stdthreaddetach
  foo_thread.join();  // wait until foo_thread finishes

  LOG("Thread Detach Example End");
}
}  // namespace detach

/**
 * @brief Thread Join Example
 */
namespace join {
void callable() {
  LOG("begin");
  for (size_t i = 0; i < 10; ++i) {
    LOG(std::to_string(i));
    std::this_thread::sleep_for(std::chrono::milliseconds(5));  // sleep for 5ms
  }
  LOG("end");
}

void run() {
  unsigned int threads_num = std::thread::hardware_concurrency();
  std::cout << "The number of hardware thread contexts: " << threads_num
            << '\n';

  LOG("Thread Join Example Begin");

  // thread object
  std::thread user_thread;
  checkJoinable(user_thread);
  user_thread = std::thread(callable);
  checkJoinable(user_thread);

  for (size_t i = 0; i < 10; ++i) {
    LOG(std::to_string(i));
    std::this_thread::sleep_for(std::chrono::milliseconds(5));  // sleep for 5ms
  }

  // sync point, block the execution of the caller until the thread executation(callable) finished
  user_thread.join();
  checkJoinable(user_thread);

  LOG("Thread Join Example End");
}
}  // namespace join

class ThreadManagement : public IExample {
 public:
  std::string group() const override { return "core/concurrency"; }
  std::string name() const override { return "ThreadManagement"; }
  std::string description() const override {
    return "The examples for <thread>";
  }

  void execute() override {
    join::run();
    detach::run();
    exception_before_join::run();
  }
};

REGISTER_EXAMPLE(ThreadManagement);