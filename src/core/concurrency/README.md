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
- `thread object`: refers to a C++ instance `that associated with` an `active thread` of execution in hardware level.
- `std::thread(callable)`: request the kernel OS to create a thread.
- `join`: blocks the current thread until the thread that identified by *this (a.ka. object thread) finished its execution. Note that if the exception
is throw before `join`, `std::terminate` might be called, leading to an undefined behavior.
- `detach`: separates the `thread of the execution` from the `thread object`, allowing the execution to continue running.


