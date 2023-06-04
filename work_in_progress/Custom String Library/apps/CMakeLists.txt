set(HEADER_LIST
    "${Custom_String_Library_SOURCE_DIR}/extern/argparse/argparse.h"
    "${Custom_String_Library_SOURCE_DIR}/include/Custom_String/custom_string.h"
    )
set(SRC_LIST "${Custom_String_Library_SOURCE_DIR}/extern/argparse/argparse.c")

SET(APPS app)

SET(INCLUDE_DIRS
    ../extern/argparse
    ../include/Custom_String
    )

foreach(program ${APPS})
    add_executable(${program} ${program}.c ${SRC_LIST})
    target_include_directories(${program} PRIVATE ${INCLUDE_DIRS})
    target_compile_features(${program} PRIVATE c_std_11)
endforeach(program)
