add_library(ex_student_manager)

target_include_directories(ex_student_manager
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_sources(ex_student_manager
    PRIVATE
        Student.cpp
        Manager.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES
            Manager.h
)