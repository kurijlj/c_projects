# Find clang-tidy if available
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

# Set clang-tidy arguments
if(CLANG_TIDY_EXE)
    set(
        CLANG_TIDY_COMMAND
        "${CLANG_TIDY_EXE}"
        "clang-diagnostic-*,clang-analyzer-*,readability-*,performance-*"
        )
endif()

include_directories (${GTK4_INCLUDE_DIRS})
link_directories (${GTK4_LIBRARY_DIRS})
add_executable (
    focus_precision
    focus_precision.c
    focus_precision_app.c
    focus_precision_resources.c
    main_app_window.c
    ${GSL_FRAMEWORK_SOURCES}
)
set_target_properties(
    focus_precision
    PROPERTIES
    C_CLANG_TIDY
    "${CLANG_TIDY_COMMAND}"
    )
target_compile_features (focus_precision PRIVATE c_std_11)
target_link_libraries (
    focus_precision
    LINK_PRIVATE
    argparse
    gsl
    ${GTK4_LIBRARIES}
    )
