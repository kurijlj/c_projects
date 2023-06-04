cmake_minimum_required(VERSION 3.15...3.20)

project(
    Heap_String_Library
    VERSION 0.1
    DESCRIPTION "Heap String Library"
    LANGUAGES C
    )

# Append custom flags
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-v -Wall -Wextra -pedantic -fcolor-diagnostics -fdiagnostics-format=vi)
endif()

# Include argparse library into the build
# add_subdirectory(${Heap_String_Library_SOURCE_DIR}/extern/argparse)

# The executable code is here
add_subdirectory(${Heap_String_Library_SOURCE_DIR}/apps)
