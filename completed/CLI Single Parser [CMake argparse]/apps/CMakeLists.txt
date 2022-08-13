set(HEADER_LIST "${CLI_App_Framework_SOURCE_DIR}/extern/argparse/argparse.h")
set(SRC_LIST "${CLI_App_Framework_SOURCE_DIR}/extern/argparse/argparse.c")

SET(APPS app_name)

SET(INCLUDE_DIRS ../extern/argparse)

foreach(program ${APPS})
    add_executable(${program} ${program}.c ${SRC_LIST})
    target_include_directories(${program} PRIVATE ${INCLUDE_DIRS})
    target_compile_features(${program} PRIVATE c_std_11)
endforeach(program)
