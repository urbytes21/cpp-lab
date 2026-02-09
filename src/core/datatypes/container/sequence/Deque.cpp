// cppcheck-suppress-file []

/**
 *  Double-ended queue is an indexed sequence container that allows fast insertion and deletion
 *  and never invalidates pointers or references to the rest of the elements because it use two pointer for 1 elem.
=> Indexing and iterating performance  < vector
 *  The elements of a deque are not stored contiguously

 *  Insertion or removal of elements - linear O(n)
 *  Random access - constant O(1)
 */
#include <deque>
#include <iostream>

namespace {
void run() {
  // 1) Init
  std::deque<int> m_deque = {9, 100, 0};

  // 2) Modifiers
  m_deque.clear();

  m_deque.push_back(1);
  m_deque.push_back(2);
  m_deque.push_back(3);
  m_deque.push_back(4);
  m_deque.pop_back();
  m_deque.pop_front();
  m_deque.push_front(99);

  for (const auto& e : m_deque) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}
}  // namespace

struct DequeRunner {
  DequeRunner() {
    std::cout << "\n--- std::deque Example ---\n";
    run();
  }
};

static DequeRunner autoRunner;