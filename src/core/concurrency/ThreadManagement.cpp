#include <chrono>  // chrono::millisecond()
#include <iostream>
#include <stdexcept>
#include <thread>
#include "ExampleRegistry.h"

namespace {
void checkJoinable(std::thread& thread) {
  if (thread.joinable()) {
    std::cout << "Thread Object is joinable.\n";
  } else {
    std::cout << "Thread Object is not joinable.\n";
  }
}
}  // namespace

namespace ExceptionBeforeJoin {
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
  std::cout << "\ncallable started\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  std::cout << "\ncallable finished\n";
}

void exceptionThrow() {
  throw std::runtime_error("callable runtime exception");
}

void run() {
  std::cout << "\n---ExceptionBeforeJoin Ex---\n";
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
  std::cout << "\nrun finished\n";
}

}  // namespace ExceptionBeforeJoin

namespace Detach {
void foo() {
  std::cout << "\nfoo started\n";
  std::this_thread::sleep_for(std::chrono::microseconds(1000));
  std::cout << "\nfoo finished\n";
}

void bar() {
  std::cout << "\nbar started\n";
  std::this_thread::sleep_for(std::chrono::microseconds(2000));
  std::cout << "\nbar finished\n";
}

void run() {
  std::cout << "\n---Detach Ex---\n";
  std::cout << "\nrun started\n";
  std::thread foo_thread(foo);
  std::thread bar_thread(bar);

  bar_thread.detach();

  foo_thread.join();
  std::cout << "\nrun finished\n";
}
}  // namespace Detach

namespace Join {
void callable() {
  for (size_t i = 0; i < 10; ++i) {
    std::cout << "callable " << i << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(5));  // sleep for 5ms
  }
  std::cout << "\ncallable finished\n";
}

void run() {
  std::cout << "\n---Join Ex---\n";
  std::thread user_thread(callable);
  for (size_t i = 0; i < 10; ++i) {
    std::cout << "run " << i << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(5));  // sleep for 5ms
  }
  checkJoinable(user_thread);
  user_thread
      .join();  // sync point, block the execution of the caller until the thread executation(callable) finished
  checkJoinable(user_thread);

  std::cout << "\nrun finished\n";
}
}  // namespace Join

class ThreadManagement : public IExample {

  std::string group() const { return "core/concurrency"; }
  std::string name() const { return "ThreadManagement"; }
  std::string description() const { return "The examples for <thread>"; }

  void execute() {
    Join::run();
    Detach::run();
    ExceptionBeforeJoin::run();
  }
};

REGISTER_EXAMPLE(ThreadManagement, "core/concurrency", "ThreadManagement");