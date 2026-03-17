
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


# ----------------------------------------------------------------------------------------
# Dependencies - GTK4
# ----------------------------------------------------------------------------------------
# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)

# Check for gtkmm-4.0 specifically, not just gtk4
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
