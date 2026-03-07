# ----------------------------------------------------------------------------------------
# Unit testing target
# ----------------------------------------------------------------------------------------

# Define the test executable name
set(PROJECT_NAME_TEST ${PROJECT_NAME}_unit_test)

# Test source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/DeleteMe.cpp
)

set(TEST_SOURCES
    DeleteMeTest.cpp
    two_sum_ut.cpp
    median_two_sorted_arrays_ut.cpp
    container_with_most_water_ut.cpp
    longest_common_prefix_ut.cpp
    three_sum_ut.cpp
    four_sum_ut.cpp
)

# Build the test executable
add_executable(${PROJECT_NAME_TEST}
    ${SOURCES}
    ${TEST_SOURCES}
)

# Header files directory
set(APP_HEADERS
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/generated # cmake generated headers
)

# Add include paths for the test target
target_include_directories(${PROJECT_NAME_TEST}
    PRIVATE ${APP_HEADERS}
)

# Link GoogleTest and GoogleMock
target_link_libraries(${PROJECT_NAME_TEST}
    leetcode
    GTest::gtest_main
    GTest::gmock_main
)

# Automatically register tests with CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME_TEST})