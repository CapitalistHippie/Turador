cmake_minimum_required(VERSION 3.2)

###############################################################################
## Constants.
###############################################################################
set(TURADOR_PROJECT_NAME "Turador")
set(TURADOR_EXECUTABLE_NAME "turador")
set(TURADOR_TESTS_EXECUTABLE_NAME "turador-tests")

set(TURADOR_DIR ${CMAKE_CURRENT_LIST_DIR})
set(TURADOR_SRC_DIR "${TURADOR_DIR}/src")

set(TURADOR_SRC_FILES
    "${TURADOR_SRC_DIR}/main.cpp")

set(TURADOR_TESTS_SRC_DIR "${TURADOR_DIR}/tests")
set(TURADOR_TEST_SRC_FILES
    "${TURADOR_TESTS_SRC_DIR}/tests.cpp")


###############################################################################
## Project.
###############################################################################
project(${TURADOR_PROJECT_NAME})

add_executable(${TURADOR_EXECUTABLE_NAME}
    ${TURADOR_SRC_FILES})


###############################################################################
## 3rd party libraries.
###############################################################################

# GTest. Is included and linked into the tests executable.
find_package(GTest REQUIRED)


###############################################################################
## Testing.
###############################################################################
enable_testing()

add_executable(${TURADOR_TESTS_EXECUTABLE_NAME}
    ${TURADOR_TEST_SRC_FILES})

target_link_libraries(${TURADOR_TESTS_EXECUTABLE_NAME}
    ${GTEST_BOTH_LIBRARIES})

target_include_directories(${TURADOR_TESTS_EXECUTABLE_NAME}
    PRIVATE ${GTEST_INCLUDE_DIRS})

add_test("Tests" ${TURADOR_TESTS_EXECUTABLE_NAME})
