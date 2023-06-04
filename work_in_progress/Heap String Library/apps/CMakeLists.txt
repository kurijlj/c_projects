SET(APPS app)

SET(INCLUDE_DIRS
    ${Heap_String_Library_SOURCE_DIR}/extern/argparse
    ${Heap_String_Library_SOURCE_DIR}/extern/exitstatus
    ${Heap_String_Library_SOURCE_DIR}/extern/hstring
    )

add_library(argparse
    STATIC
    ${Heap_String_Library_SOURCE_DIR}/extern/argparse/argparse.c
    )

add_library(exitstatus
    STATIC
    ${Heap_String_Library_SOURCE_DIR}/extern/exitstatus/exitstatus.c
    )

add_library(hstring
    STATIC
    ${Heap_String_Library_SOURCE_DIR}/extern/hstring/hstring.c
    )

target_include_directories(hstring
    PRIVATE ${Heap_String_Library_SOURCE_DIR}/extern/exitstatus
    )

target_link_libraries(hstring
    PRIVATE exitstatus
    )

foreach(program ${APPS})
    add_executable(${program} ${program}.c)
    target_include_directories(${program} PRIVATE ${INCLUDE_DIRS})
    target_link_libraries(${program}
        PRIVATE argparse
        PRIVATE exitstatus
        PRIVATE hstring
        )
    target_link_options(${program} PRIVATE)
    target_compile_features(${program} PRIVATE c_std_11)
endforeach(program)
