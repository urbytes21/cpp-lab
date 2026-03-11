add_library(leetcode)

target_include_directories(leetcode
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include # for shared public headers
)

target_sources(leetcode
    PRIVATE
        arrays/two_sum/TwoSum.cpp
        arrays/median_two_arrays/MedianTwoSortedArrays.cpp
        arrays/container_with_most_water/ContainerWithMostWater.cpp
        arrays/longest_common_prefix/Solution.cpp
        arrays/3sum/Solution.cpp
        arrays/4sum/Solution.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS arrays
        FILES
            arrays/3sum/Solution.h
            arrays/4sum/Solution.h
            arrays/container_with_most_water/ContainerWithMostWater.h
            arrays/longest_common_prefix/Solution.h
            arrays/median_two_arrays/MedianTwoSortedArrays.h
            arrays/two_sum/TwoSum.h
)