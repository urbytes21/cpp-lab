// cppcheck-suppress-file [unreadVariable,unusedVariable]

/**
 * std::array
 *  
 * <array>
 *  template< class T, std::size_t N > struct array;
 */
#include <array>  // for std::array
#include <iostream>

namespace {
void run() {
  std::cout << "\n--- std::array Example ---\n";
  // 1) Init
  std::array<int, 3> m_array = {9, 100, 0};
  // m_array = {1,2,3,5,6}; // ERROR

  std::array<int, 3> a2{3, 4, 5};
  std::array<int, 3> a3;     // garbage values for a3[0]-> a4[]
  std::array<int, 3> a4{};   // all elements have value 0
  std::array<int, 3> a5{1};  // a5[0] = 0, others elements have value 0

  // 2) Element access
  std::cout << m_array.front() << std::endl;
  std::cout << m_array.back() << std::endl;

  int* ptr_arr = m_array.data();
  std::cout << *(ptr_arr++) << " ";
  std::cout << *(ptr_arr++) << " ";
  std::cout << *(ptr_arr++) << " ";
  std::cout << std::endl;

  // raw for loop
  for (std::size_t i = 0; i < m_array.size(); ++i) {
    std::cout << m_array.at(i) << " ";
  }

  std::cout << std::endl;

  // for range
  for (const int& e : m_array) {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  // 3) Iterators
  std::array<int, 3>::iterator it = m_array.begin();
  std::array<int, 3>::iterator itEnd = m_array.end();
  for (; it != itEnd; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  auto r_it = m_array.rbegin();
  auto r_it_end = m_array.rend();
  for (; r_it != r_it_end; r_it++) {
    std::cout << *r_it << " ";
  }
  std::cout << std::endl;

  // 4) Capacity
  std::cout << m_array.max_size()
            << std::endl;  // fixed-size => max_size = size
  std::cout << m_array.size() << std::endl;
  bool is_empty = m_array.empty();

  // 5) Operation
  constexpr std::size_t kXy = 4;
  using Cell = std::array<unsigned char, 8>;
  std::array<Cell, kXy * kXy> board;
  board.fill({0xE2, 0x96, 0x84, 0xE2, 0x96, 0x80, 0,
              0});  // "▄▀"; // fill means fill all 16 Cell with "▄▀"
  //   board = {Cell{0xE2, 0x96, 0x84, 0xE2, 0x96, 0x80, 0, 0},Cell{0xE2, 0x96, 0x84, 0xE2, 0x96, 0x80, 0, 0}};
  for (size_t count{}; Cell c : board)
    std::cout << c.data() << ((++count % kXy) ? "" : "\n");
}
}  // namespace

#include "ExampleRegistry.h"

class Array : public IExample {
 public:
  std::string group() const override { return "core/container"; }
  std::string name() const override { return "Array"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Array);