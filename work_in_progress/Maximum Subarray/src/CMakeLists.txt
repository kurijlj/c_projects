add_executable(
    maximum_subarray
    maximum_subarray.c
    ${MAXIMUM_SUBARRAY_SOURCES}
    )
target_compile_features(maximum_subarray PRIVATE c_std_11)
target_link_libraries (maximum_subarray LINK_PUBLIC argparse gsl)
