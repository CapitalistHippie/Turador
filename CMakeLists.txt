cmake_minimum_required(VERSION 3.2)

set(DOMUM_PROJECT_NAME "Turador")

project(${DOMUM_PROJECT_NAME})

enable_testing()

###############################################################################
## 1st party libraries.
###############################################################################
add_subdirectory("libturador")

###############################################################################
## Executables.
###############################################################################
add_subdirectory("turador")
