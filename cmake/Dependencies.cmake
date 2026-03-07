
# ----------------------------------------------------------------------------------------
# Dependencies - GoogleTest
# ----------------------------------------------------------------------------------------
# FetchContent allows downloading dependencies at configure time
include(FetchContent)

# Declare GoogleTest dependency
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)
