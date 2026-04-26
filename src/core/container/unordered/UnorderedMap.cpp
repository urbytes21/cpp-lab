// cppcheck-suppress-file [unreadVariable,unusedVariable,redundantInitialization]

// HashMap: Collection of key-value pairs that are hashed by their keys where no two pairs have same keys.
/**
 * std::unordered_map
 *  
 * <vector>
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
void run() {
  std::cout << "\n--- std::unordered_map Example ---\n";
  // 1) Init
  std::unordered_map<std::string, int> m_map{
      {"k_1", 1}, {"k_2", 2}, {"k_3", 3}};

  // 2) Modifiers
  m_map.insert({"k_4", 4});

  std::pair<std::string, int> new_elem1 = {"k_5", 0};
  m_map.insert(new_elem1);

  std::string m_key = "k_6";
  int m_value = 99;
  auto new_elem2 = std::make_pair(m_key, m_value);
  m_map.insert(new_elem2);

  auto m_map2 = m_map;
  for (auto it = m_map.begin(); it != m_map.end();) {
    it = m_map.erase(it);
  }
  for (const std::pair<const std::string, int>& e : m_map) {
    std::cout << "[" << e.first << "," << e.second << "]" << " ";
  }
  std::cout << std::endl;

  m_map2.insert_or_assign("k_6", 8888);  // WORK

  auto pos = m_map2.find("k_6");
  if (pos != nullptr) {
    m_map2.insert(std::make_pair(
        "k_6", 9999));  // cannot reassign if this pair already existed
  }

  // 3) Lookup
  pos = m_map.find("k_1");
  std::cout << (pos != nullptr ? "true" : "false") << std::endl;

  for (auto const& [k, v] : m_map2) {
    std::cout << "[" << k << "," << v << "]" << " ";
  }
  std::cout << std::endl;

  // 4) Make fun
  std::vector<std::string> keys{};
  keys.reserve(m_map2.size());
  for (auto const& [k, v] : m_map2) {
    keys.push_back(k);
  }

  std::cout << "Keys: " << std::endl;
  for (auto const& k : keys) {
    std::cout << k << " ";
  }
  std::cout << std::endl;
}
}  // namespace

#include "ExampleRegistry.h"

class UnorderedMap : public IExample {
 public:
  std::string group() const override { return "core/container"; }
  std::string name() const override { return "UnorderedMap"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(UnorderedMap, "core/container", "UnorderedMap");