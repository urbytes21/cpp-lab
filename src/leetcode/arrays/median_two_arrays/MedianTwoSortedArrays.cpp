#include "MedianTwoSortedArrays.h"
#include <algorithm>

/**
 * Time Complexity: O((m+n) + (m+n)log(m+n)) ~ O((m+n)log(m+n))
 * Space Complexity: O(n+m)
 */
double Solution::findMedianSortedArrays(const std::vector<int>& nums1,
                                        const std::vector<int>& nums2) {
  std::vector<int> nums{};
  nums.reserve(
      nums1.size() +
      nums2.size());  // should use reserve to pre-allocate the required mem

  nums.insert(nums.end(), nums1.begin(),
              nums1.end());  // insert: copy n + m => O(m+n)
  nums.insert(nums.end(), nums2.begin(), nums2.end());

  std::sort(nums.begin(), nums.end());  // sort: NLogN => (m+n)Log(m+n)

  size_t size = nums.size();
  if (size == 0) {
    return -1;
  }

  if (size % 2 != 0) {
    int index =
        size /
        2;  // integer division truncates toward zero, so size / 2 gives the lower middle index
    return nums.at(index);
  } else {
    int index1 = size / 2;
    int index2 = size / 2 - 1;
    int sum = nums.at(index1) + nums.at(index2);
    return sum / 2.0;
  }
}