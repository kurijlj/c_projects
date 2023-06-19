add_executable(
    inplace_insertion_sort
    inplace_insertion_sort.c
    ${SORT_ALGORITHMS_SOURCES}
    )
target_compile_features(inplace_insertion_sort PRIVATE c_std_11)
target_link_libraries (inplace_insertion_sort LINK_PUBLIC argparse gsl)
