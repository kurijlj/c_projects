cmake_minimum_required(VERSION 3.15...3.20)

project(
    Custom_String_Library
    VERSION 0.1
    DESCRIPTION "Custom String Library"
    LANGUAGES C
    )

# Append custom flags
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-v -Wall -Wextra -pedantic -fcolor-diagnostics -fdiagnostics-format=vi)
endif()

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  # set(CMAKE_C_EXTENSIONS OFF)

endif()

# The executable code is here
add_subdirectory(apps)
