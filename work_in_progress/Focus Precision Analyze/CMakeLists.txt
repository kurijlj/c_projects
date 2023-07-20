# For more information about using CMake read the documentation on:
#   * https://cmake.org/cmake/help/latest/guide/tutorial/index.html
#   * https://cliutils.gitlab.io/modern-cmake/chapters/basics.html
#   * https://cmake.org/examples/

cmake_minimum_required (VERSION 3.15...3.40)

project (
    GTK_Test
    VERSION 0.1
    DESCRIPTION "GTK Test"
    LANGUAGES C
    )

# Check for GTK and its dependencies
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK4 REQUIRED IMPORTED_TARGET gtk4)
message (STATUS "GTK version: ${GTK4_VERSION}")
message (STATUS "GTK include dirs: ${GTK4_INCLUDE_DIRS}")
message (STATUS "GTK link dirs: ${GTK4_LIBRARY_DIRS}")
message (STATUS "GTK libraries: ${GTK4_LIBRARIES}")

# Append custom flags
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options (-v -Wall -Wextra -pedantic -fcolor-diagnostics
        -fdiagnostics-format=vi)
endif ()

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD,
  # CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  # set(CMAKE_C_EXTENSIONS OFF)

endif ()

# The executable code is here
add_subdirectory (extern/argparse)
add_subdirectory (extern/gsl)
add_subdirectory (src)
