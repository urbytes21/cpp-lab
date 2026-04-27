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
    GTest::gtest_main
    GTest::gmock_main
)

# Register the unit test executable with CTest
# `ctest --output-on-failure`
add_test(
    NAME unit_tests
    COMMAND ${PROJECT_NAME_TEST}
)

# Automatically register tests with CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME_TEST})