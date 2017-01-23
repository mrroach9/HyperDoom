# Main CMake file of the core renderer.
# Usage: cd to HyperDoom/renderer/build, then cmake ..
# Output binaries and libs will be output to renderer/build.

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(PROJ_NAME "HyperDoom")
project(${PROJ_NAME}
    LANGUAGES CXX
    VERSION 0.1)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME "${PROJ_NAME}_test" 
    COMMAND "${PROJ_NAME}_test"
)