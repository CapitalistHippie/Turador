cmake_minimum_required(VERSION 3.2)

set(TURADOR_PROJECT_NAME "Turador")
set(TURADOR_EXECUTABLE_NAME "turador")

set(TURADOR_DIR ${CMAKE_CURRENT_LIST_DIR})
set(TURADOR_SRC_DIR "${TURADOR_DIR}/src")

project(${TURADOR_PROJECT_NAME})

# Source files.
set(TURADOR_SRC_FILES
    "${TURADOR_SRC_DIR}/main.cpp")

add_executable(${TURADOR_EXECUTABLE_NAME}
    ${TURADOR_SRC_FILES})
