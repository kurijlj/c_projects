cmake_minimum_required(VERSION 3.15)

project(hstring VERSION 0.1.0 LANGUAGES C)

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

option(HSTRING_SHARED "Build shared library" OFF)
option(HSTRING_STATIC "Build static library" ON)

if(HSTRING_SHARED)
    add_library(hstring_shared SHARED ${sources})
    target_include_directories(hstring_shared PUBLIC .)
    set_target_properties(hstring_shared PROPERTIES OUTPUT_NAME hstring)
endif()
if(HSTRING_STATIC)
    add_library(hstring STATIC ${sources})
    target_include_directories(hstring PUBLIC .)
endif()
if(NOT (HSTRING_STATIC OR HSTRING_SHARED))
    add_library(hstring OBJECT ${sources})
endif()
