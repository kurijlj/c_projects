# For more information about using CMake read the documentation on:
#   * https://cmake.org/cmake/help/latest/guide/tutorial/index.html
#   * https://cliutils.gitlab.io/modern-cmake/chapters/basics.html
#   * https://cmake.org/examples/

cmake_minimum_required(VERSION 3.15...3.40)

project(
    Maximum_Subarray
    VERSION 0.1
    DESCRIPTION "Maximum Subarray"
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
add_subdirectory(extern/argparse)
add_subdirectory(extern/gsl)
add_subdirectory(src)
