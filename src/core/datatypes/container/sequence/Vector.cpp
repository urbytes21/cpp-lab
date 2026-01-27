// cppcheck-suppress-file [unreadVariable,unusedVariable,redundantInitialization]

// ArrayList
/**
 * std::vector
 *  
 * <vector>
 */
#include <iostream>
#include <span>
#include <vector>  // for std::vector

namespace {
void example() {
  std::cout << "\n--- std::vector Example ---\n";
  // 1) Init
  std::vector<int> m_vec = {9, 100, 0};
  m_vec = {1, 2, 3, 5, 6};  // OK

  std::vector<int> m_vec1{9, 100, 0};
  std::vector<int> m_vec2;
  std::vector<int> m_vec3{};
  std::vector<int> m_vec4();

  m_vec.assign({1, 1, 3});

  // 2) Modifiers
  m_vec.clear();

  auto pos = m_vec.begin();
  m_vec.insert(pos, 99);
  pos = m_vec.begin();  // pos may be no longer valid, get a new one
  m_vec.insert(pos, 9);
  pos = m_vec.begin();
  m_vec.erase(pos);

  m_vec.push_back(1);
  m_vec.push_back(2);
  m_vec.push_back(3);
  m_vec.push_back(4);

  m_vec.pop_back();

  for (const auto& e : m_vec) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}
}  // namespace

struct VectorRunner {
  VectorRunner() { example(); }
};

static VectorRunner autoRunner;