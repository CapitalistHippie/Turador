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
    "${LIBTURADOR_INCLUDE_DIR}/tura/models/cargo.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/models/gamestate.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/models/harbor.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/models/harborcargo.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/models/harborcargostats.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/models/harborstats.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/game.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/gamebuilder.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/gameconfiguration.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/harborbuilder.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/harborfactory.h"
    "${LIBTURADOR_INCLUDE_DIR}/tura/harborfactoryinterface.h"
    "${LIBTURADOR_INCLUDE_DIR}/csvparser.hpp"
    "${LIBTURADOR_SRC_DIR}/tura/game.cpp"
    "${LIBTURADOR_SRC_DIR}/tura/harborfactory.cpp")

set(LIBTURADOR_TESTS_SRC_DIR "${LIBTURADOR_DIR}/tests")
set(LIBTURADOR_TEST_SRC_FILES
    "${LIBTURADOR_TESTS_SRC_DIR}/helpers/testhelpers.h"
    "${LIBTURADOR_TESTS_SRC_DIR}/mocks/harborfactorymock.h"
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/gameunittests.cpp"
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/harborfactoryunittests.cpp"
    "${LIBTURADOR_TESTS_SRC_DIR}/main.cpp")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


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
## Testing.
###############################################################################
enable_testing()

add_executable(${LIBTURADOR_TESTS_BINARY_NAME}
    ${LIBTURADOR_TEST_SRC_FILES})

target_link_libraries(${LIBTURADOR_TESTS_BINARY_NAME}
    gtest gtest_main gmock gmock_main
    ${LIBTURADOR_BINARY_NAME})

target_include_directories(${LIBTURADOR_TESTS_BINARY_NAME}
    PRIVATE ${LIBTURADOR_INCLUDE_DIR})

add_test("Tests" ${LIBTURADOR_TESTS_BINARY_NAME})
