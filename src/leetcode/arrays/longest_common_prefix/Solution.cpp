#include "Solution.h"
/**
 * @brief Complexity
 *  - Time: O(n*m)
 *  - Space: O(1)
 */
std::string Solution::longestCommonPrefix(
    const std::vector<std::string>& strs) {
  const std::string& str_benchmark =
      strs.at(0);  // use 1st string as a benchmark

  // Iterator charactor-by-charator over the first string
  // to compare it against all other strings
  for (size_t i = 0; i < str_benchmark.size(); ++i) {
    char c = str_benchmark.at(i);
    for (size_t j = 1; j < strs.size(); ++j) {
      const std::string& str = strs.at(j);
      if (i >= str.size() || c != str.at(i)) {
        return str_benchmark.substr(0, i);
      }
    }
  }

  return str_benchmark;
}
