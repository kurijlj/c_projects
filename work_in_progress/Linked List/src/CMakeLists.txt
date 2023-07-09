add_executable(
    linked_list
    linked_list.c
    ${SORT_ALGORITHMS_SOURCES}
    )
target_compile_features(linked_list PRIVATE c_std_11)
target_link_libraries (linked_list LINK_PUBLIC argparse)
