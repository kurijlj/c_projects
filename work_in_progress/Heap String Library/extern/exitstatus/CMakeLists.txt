cmake_minimum_required(VERSION 3.15)

project(exitstatus VERSION 0.1.0 LANGUAGES C)

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

set(sources exitstatus.c)

option(EXITSTATUS_SHARED "Build shared library" OFF)
option(EXITSTATUS_STATIC "Build static library" ON)

if(EXITSTATUS_SHARED)
    add_library(exitstatus_shared SHARED ${sources})
    target_include_directories(exitstatus_shared PUBLIC .)
    set_target_properties(exitstatus_shared PROPERTIES OUTPUT_NAME exitstatus)
endif()
if(EXITSTATUS_STATIC)
    add_library(exitstatus STATIC ${sources})
    target_include_directories(exitstatus PUBLIC .)
endif()
if(NOT (EXITSTATUS_STATIC OR EXITSTATUS_SHARED))
    add_library(exitstatus OBJECT ${sources})
endif()
