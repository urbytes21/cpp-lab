# ------------------------------------------------------------------------------
# Create a library that contains implementations of multiple LeetCode problems.
# This library can be reused by:
# 1. main executable programs
# 2. unit tests
#
# Structure:
# leetcode_lib (library)
# │
# ┌────┴────┐
# ▼         ▼
# main app   unit tests
#
# # Use the library in unit test
# target_link_libraries(test_arrays
# PRIVATE
# leetcode_lib
# )
# ------------------------------------------------------------------------------

add_library(leetcode
    arrays/two_sum/TwoSum.cpp
    arrays/median_two_arrays/MedianTwoSortedArrays.cpp
    arrays/container_with_most_water/ContainerWithMostWater.cpp
    arrays/longest_common_prefix/Solution.cpp
    arrays/3sum/Solution.cpp
    arrays/4sum/Solution.cpp
)

# ------------------------------------------------------------------------------
# Expose header files to any target that links with this library.
# PUBLIC means:
# - This library can use the headers
# - Any target linking to this library can also use them
# ------------------------------------------------------------------------------
target_include_directories(leetcode
    PUBLIC
    ${PROJECT_SOURCE_DIR} # for arrays/... headers
    ${PROJECT_SOURCE_DIR}/include # for shared public headers
)