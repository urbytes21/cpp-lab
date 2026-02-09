// cppcheck-suppress-file []

/**
 * std::queue
 * template<
 *    class T,
 *    class Container = std::deque<T>
 * > class queue;
 *
 * Queue acts as a wrapper to the underlying container (sequence container e.g. std::deque, std::list)
 *  but only a specific 
 * set of functions is provided.
 * It pushs the elements on the back of the underlying container and pops them from the front
 * 
 */
#include <iostream>
#include <queue>  // for std::queue

namespace {
void run() {
  // 1. Init
  std::queue<int> m_queue{};

  // 2. Modifiers
  m_queue.push(0);  // inserts elements at the end
  m_queue.push(1);  // q = 0 1
  m_queue.push(2);  // q = 0 1 2
  m_queue.push(3);  // q = 0 1 2 3

  m_queue.pop();  // removes the 1st element q = 1 2 3

  // 3. Element access
  std::cout << "fisrt ele: " << m_queue.front() << "\n";
  std::cout << "last ele: " << m_queue.back() << "\n";

  // 4. Get all elements and remove
  std::cout << "all ele: \n";
  for (; !m_queue.empty(); m_queue.pop()) {
    std::cout << m_queue.front() << " ";
  }
  std::cout << "\n";
}
}  // namespace

struct QueueRunner {
  QueueRunner() {
    std::cout << "\n--- std::queue Example ---\n";
    run();
  }
};

static QueueRunner autoRunner;