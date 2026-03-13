## 1. Concurrency
- Concurrency `refers to the ability` `to proccess` `multiple tasks` `at the same time.` 
`On a single core`, it uses `context-switching`, `on multi-core systems`, it can run in parallel.
- It's `used to improve` the `program performance` and `response time`.
- In C/C++, we can archive concurrency by using `threads`.

- `<chrono>` is a C++ header that provide `a collection of types and functions` to work with time.

### 1.1. Thread <thread>
- Threads are `the basic unit of` multitasking.
- There are many errors and risks associated with concurrency, including:
 - `Deadlocks`: `refers to the situation where` two or more threads are blocked, `waiting for each other indefinitely`.
 - `Race condition`: `refers to the situation where` two or more threads access `shared data` concurrently, leading to the `undefined behavior`.
 - `Starvation`: `refer to the situation where` a thread `is unable to gain` regular access to the shared resources.
=> We can avoid these problems by `proper synchronization` between the threads.

### 1.2. Thead Synchronization
- The synchronization can be done by using the following components:
 - `Mutex/Lock`: <mutex> they are used to protect the shared resouces, ensure that only one thread can access `the critical sections` at a time.
 - `Semaphore`: 
 - `Futures and Promises`: <future>, <promise> are used for the asynchronous task execution.
 - `Condition variable`: <condition_variable>

### 1.3. Thread Management
- `thread`: an `OS thread` `managed by` the kernel.
- Each `thread` has it own `call stack`, but all `threads` share the heap.
- `thread object`: refers to a C++ instance `that associated with` an `active thread` of execution in hardware level.
- `std::thread(callable)`: request the kernel OS to create a thread.
- `std::this_thread`: refer to the current thread
- `join`: blocks the current thread until the thread that identified by *this (a.ka. object thread) finished its execution. Note that if the exception
is throw before `join`, `std::terminate` might be called, and will kill the entire program process, not an invidual thread.
- `detach`: separates the `thread of the execution` from the `thread object`, allowing the execution to continue running.
- `yield`: give priority to other threads, pause its execution
- Use `return` to kill a thread.


### 1.4. Sharing Data
- `Global/Static Variable`: can be accessed by all threads.
- `Pass By Reference`: we need to explicitly wrap the args in `std::ref` to pass by reference and is the only way to properly get data out of a thread
- `thread_local` to create a static variable per thread.

### 1.5. Atomic <std::atomic>
- An atomic type is a type that implements atomic operations. It's used to guarantee no race conditions will occur.
- e.g.
`std::atomic<bool>` - `std::atomic_bool`
- e.g.
```cpp
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
 
std::atomic_int acnt;
int cnt;
 
void f()
{
    for (auto n{10000}; n; --n)
    {
        ++acnt;
        ++cnt;
        // Note: for this example, relaxed memory order is sufficient,
        // e.g. acnt.fetch_add(1, std::memory_order_relaxed);
    }
}
 
int main()
{
    {
        std::vector<std::jthread> pool;
        for (int n = 0; n < 10; ++n)
            pool.emplace_back(f);
    }
 
    std::cout << "The atomic counter is " << acnt << '\n'
              << "The non-atomic counter is " << cnt << '\n';
}
```

### 1.6. Mutex/Locks
- Mutexs are mutual exclusion objects, are owned by the thread that takes it.
- e.g.
```cpp
#include <mutex>

// Create your mutex here
std::mutex my_mutex;

// 
thread_function()
{
  my_mutex.lock(); // Acquire lock
  // Do some non-thread safe stuff...
  my_mutex.unlock(); // Release lock
}
```

- There are serveral types of mutex, including:
    - `mutex`
    - `timed_mutex`
    - `recursive_mutex`
    - `recursive_timed_mutex`
    - `shared_timed_mutex`

- `Lock Guard Type` is a wrapper mutex that provides a convinient RAII-style mechanism.
- They are several `lock guard types`, including:
    - `std::lock_guard`<mutex>, `std::scoped_lock`<mutex,mutex>
    - `std::unique_lock`, `shared_lock`

### 1.7. Condition Variable for event handling - <condition_variable>
- `std::condition_variable` is a synchronization primitive used with a `std::mutex` to block one or more threads until another thread both modifies a `shared variable` (the condition) and `notifies` the `std::condition_variable`.
- `wait` will releases the lock and blocks the thread until the condition is fullfilled.
- e.g.
```cpp
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
 
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    // 1. wait until main() sends data
    std::unique_lock lk(m);
    cv.wait(lk, []{ return ready; });
 
    // after the wait, we own the lock
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}
 
int main()
{
    std::thread worker(worker_thread);
 
    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // wait for the worker
    {
        std::unique_lock lk(m);
        cv.wait(lk, []{ return processed; });
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}

Output:
main() signals data ready for processing
Worker thread is processing data
Worker thread signals data processing completed
Back in main(), data = Example data after processing
```