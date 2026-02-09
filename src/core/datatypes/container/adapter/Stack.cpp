// cppcheck-suppress-file []

/**
 * std::stack
 * template<
 *    class T,
 *    class Container = std::deque<T>
 * > class stack;
 *
 * Queue acts as a wrapper to the underlying container (sequence container e.g. std::deque, std::list)
 *  but only a specific 
 * set of functions is provided.
 * It pushs and pops the element from the back of the underlying container, a.k.a the top of the stack
 * 
 */
#include <iostream>
#include <stack>  // for std::queue

namespace {
void run() {
  // 1. Init
  std::stack<int> m_stack{};

  // 2. Modifiers
  m_stack.push(0);  // inserts elements at the end
  m_stack.push(1);  // q = 0 1
  m_stack.push(2);  // q = 0 1 2
  m_stack.push(3);  // q = 0 1 2 3
  m_stack.pop();    // removes the top element q = 0 1 2

  // 3. Element access
  std::cout << "top ele: " << m_stack.top()
            << "\n";  // access the top of the stack

  // 4. Get all elements and remove
  std::cout << "all ele (reverse): \n";
  for (; !m_stack.empty(); m_stack.pop()) {
    std::cout << m_stack.top() << " ";
  }
  std::cout << "\n";
}
}  // namespace

struct StackRunner {
  StackRunner() {
    std::cout << "\n--- std::stack Example ---\n";
    run();
  }
};

static StackRunner autoRunner;