# Create the gtk4-setting interface library
# Link against the libraries found for GTKMM
add_library(gtk4-settings INTERFACE)
target_link_libraries(gtk4-settings INTERFACE ${GTKMM_LIBRARIES})

# Include the directories where gtkmm.h resides
target_include_directories(gtk4-settings INTERFACE ${GTKMM_INCLUDE_DIRS})

# Add compiler flags (defines, etc.) required by gtkmm
target_compile_options(gtk4-settings INTERFACE ${GTKMM_CFLAGS_OTHER})

# ap executable
add_executable(ap)
target_sources(ap
    PRIVATE
    simple_ap.cpp
)
target_link_libraries(ap PRIVATE gtk4-settings)

add_subdirectory(mvc)
# add_subdirectory(mvvm)
