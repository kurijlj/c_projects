add_executable(
    tree_implementation
    tree_implementation.c
    ${SORT_ALGORITHMS_SOURCES}
    )
target_compile_features(tree_implementation PRIVATE c_std_11)
target_link_libraries (tree_implementation LINK_PUBLIC argparse)
