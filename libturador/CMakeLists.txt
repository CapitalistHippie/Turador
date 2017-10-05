cmake_minimum_required(VERSION 3.2)

###############################################################################
## Constants.
###############################################################################
set(LIBTURADOR_PROJECT_NAME "Turador library")
set(LIBTURADOR_BINARY_NAME "turadorlogic")
set(LIBTURADOR_TESTS_BINARY_NAME "libturador-tests")

set(LIBTURADOR_DIR ${CMAKE_CURRENT_LIST_DIR})
set(LIBTURADOR_SRC_DIR "${LIBTURADOR_DIR}/src")
set(LIBTURADOR_INCLUDE_DIR "${LIBTURADOR_DIR}/include")

set(LIBTURADOR_SRC_FILES
    "${LIBTURADOR_INCLUDE_DIR}/game.h"
    "${LIBTURADOR_SRC_DIR}/game.cpp")

set(LIBTURADOR_TESTS_SRC_DIR "${LIBTURADOR_DIR}/tests")
set(LIBTURADOR_TEST_SRC_FILES
    "${LIBTURADOR_TESTS_SRC_DIR}/tests.cpp")


###############################################################################
## Project.
###############################################################################
project(${LIBTURADOR_PROJECT_NAME})

add_library(${LIBTURADOR_BINARY_NAME}
    STATIC
    ${LIBTURADOR_SRC_FILES})

target_include_directories(${LIBTURADOR_BINARY_NAME}
    PUBLIC ${LIBTURADOR_INCLUDE_DIR})


###############################################################################
## 3rd party libraries.
###############################################################################

# GTest. Is included and linked into the tests executable.
find_package(GTest REQUIRED)


###############################################################################
## Testing.
###############################################################################
enable_testing()

add_executable(${LIBTURADOR_TESTS_BINARY_NAME}
    ${LIBTURADOR_TEST_SRC_FILES})

target_link_libraries(${LIBTURADOR_TESTS_BINARY_NAME}
    ${GTEST_BOTH_LIBRARIES})

target_include_directories(${LIBTURADOR_TESTS_BINARY_NAME}
    PRIVATE ${GTEST_INCLUDE_DIRS})

add_test("Tests" ${LIBTURADOR_TESTS_BINARY_NAME})
