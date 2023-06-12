add_executable(gsl_framework main.c ${GSL_FRAMEWORK_SOURCES})
target_compile_features(gsl_framework PRIVATE c_std_11)
target_link_libraries (gsl_framework LINK_PUBLIC argparse gsl)
