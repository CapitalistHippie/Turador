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
    "${LIBTURADOR_INCLUDE_DIR}/tura/domain/commandhandlers/purchasecargocommandhandler.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/domain/commandhandlers/sellcargocommandhandler.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/domain/commandhandlers/startgamecommandhandler.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/domain/commandmediator.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/domain/gamehelpers.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/domain/harborgenerator.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/domain/shipgenerator.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/helpers/array.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/helpers/chararray.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/helpers/csvparser.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/harborbuilder.hpp"
    "${LIBTURADOR_INCLUDE_DIR}/tura/shipbuilder.hpp"
    "${LIBTURADOR_SRC_DIR}/tura/dal/repositories/shiptypefilerepository.cpp"
    "${LIBTURADOR_SRC_DIR}/tura/dal/repositories/harborgenerationparametersfilerepository.cpp"
    "${LIBTURADOR_SRC_DIR}/tura/domain/game.cpp"
    "${LIBTURADOR_SRC_DIR}/tura/error.cpp")

set(LIBTURADOR_TESTS_SRC_DIR "${LIBTURADOR_DIR}/tests")
set(LIBTURADOR_TESTS_INCLUDE_DIR "${LIBTURADOR_DIR}/tests")

set(LIBTURADOR_TEST_SRC_FILES
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/dal/repositories/harborgenerationparametersfilerepositoryunittests.cpp"
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/dal/repositories/shiptypefilerepositoryunittests.cpp"
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/domain/commandhandlers/purchasecargocommandhandlerunittests.cpp"
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/domain/commandhandlers/sellcargocommandhandlerunittests.cpp"
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/domain/commandhandlers/startgamecommandhandlerunittests.cpp"
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/domain/harborgeneratorunittests.cpp"
    "${LIBTURADOR_TESTS_SRC_DIR}/tura/service/gameclientunittests.cpp"
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
    PRIVATE ${LIBTURADOR_TESTS_INCLUDE_DIR}
    PRIVATE ${LIBTURADOR_INCLUDE_DIR})

add_test("Tests" ${LIBTURADOR_TESTS_BINARY_NAME})
