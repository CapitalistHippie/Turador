cmake_minimum_required(VERSION 3.2)

###############################################################################
## Constants.
###############################################################################
set(TURADOR_PROJECT_NAME "Turador")
set(TURADOR_BINARY_NAME "turador")

set(TURADOR_DIR ${CMAKE_CURRENT_LIST_DIR})
set(TURADOR_SRC_DIR "${TURADOR_DIR}/src")
set(TURADOR_INCLUDE_DIR "${TURADOR_DIR}/src")

set(TURADOR_SRC_FILES
    "${TURADOR_SRC_DIR}/tura/ui/cli/cliui.cpp"
    "${TURADOR_SRC_DIR}/main.cpp")


###############################################################################
## Project.
###############################################################################
project(${TURADOR_PROJECT_NAME})

add_executable(${TURADOR_BINARY_NAME}
    ${TURADOR_SRC_FILES})

target_include_directories(${TURADOR_BINARY_NAME}
    PRIVATE ${TURADOR_INCLUDE_DIR})

# Copy assets.
# file(GLOB assets "assets/*")
# foreach(asset ${assets})
#     configure_file(${asset} "assets/${asset}" COPYONLY)
# endforeach()


###############################################################################
## 1st party libraries.
###############################################################################
target_link_libraries(${TURADOR_BINARY_NAME}
    "turadorlogic")
