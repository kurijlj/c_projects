SET(APPS hello_world)

foreach(program ${APPS})
    add_executable(${program} ${program}.c)
    target_include_directories(${program} PRIVATE ${INCLUDE_DIRS})
    target_compile_features(${program} PRIVATE c_std_11)
endforeach(program)
