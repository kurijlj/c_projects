include_directories (${GTK4_INCLUDE_DIRS})
link_directories (${GTK4_LIBRARY_DIRS})
add_executable (
    focus_precision
    focus_precision.c
    ${GSL_FRAMEWORK_SOURCES}
)
target_compile_features (focus_precision PRIVATE c_std_11)
target_link_libraries (focus_precision LINK_PRIVATE
    argparse
    gsl
    ${GTK4_LIBRARIES}
    )
