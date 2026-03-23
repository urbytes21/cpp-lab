set(EXCERCISE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/DriverAccount.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DriverStudentManager.cpp
)

set(EXCERCISE_SOURCES ${EXCERCISE_SOURCES} PARENT_SCOPE)

add_subdirectory(account)
add_subdirectory(student_manager)