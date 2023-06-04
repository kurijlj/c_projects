cmake_minimum_required(VERSION 3.15)

project(heapstring VERSION 0.1.0 LANGUAGES C)

if(NOT CMAKE_C_FLAGS)
    set(CMAKE_C_FLAGS "-O3")
endif()
if(NOT CMAKE_C_FLAGS_DEBUG)
    set(CMAKE_C_FLAGS_DEBUG "-g -ggdb")
endif()

# Append custom flags
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-v -Wall -Wextra -pedantic -fcolor-diagnostics -fdiagnostics-format=vi)
endif()

set(sources heapstring.c)

option(HEAPSTRING_SHARED "Build shared library" OFF)
option(HEAPSTRING_STATIC "Build static library" ON)

if(HEAPSTRING_SHARED)
    add_library(heapstring_shared SHARED ${sources})
    target_include_directories(heapstring_shared PUBLIC .)
    set_target_properties(heapstring_shared PROPERTIES OUTPUT_NAME heapstring)
endif()
if(HEAPSTRING_STATIC)
    add_library(heapstring STATIC ${sources})
    target_include_directories(heapstring PUBLIC .)
endif()
if(NOT (HEAPSTRING_STATIC OR HEAPSTRING_SHARED))
    add_library(heapstring OBJECT ${sources})
endif()
