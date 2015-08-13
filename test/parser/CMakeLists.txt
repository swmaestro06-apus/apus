
set(TEST_EXE parser)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -std=c++0x")

# list source code here
list(APPEND TEST_SRC
    data_decl_test.cpp
)

set_source_files_properties(${CMAKE_SOURCE_DIR}/${SRC_DIR}/${LEX_OUT} GENERATED)
set_source_files_properties(${CMAKE_SOURCE_DIR}/${SRC_DIR}/${YACC_OUT} GENERATED)

add_executable(${TEST_EXE}
    ${TEST_SRC}
    ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${LEX_OUT}
    ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${YACC_OUT})

# find and link google test library
find_library(gtest_main ${CMAKE_CURRENT_DIR}/../lib)
target_link_libraries(${TEST_EXE} gtest_main)

add_dependencies(${TEST_EXE} lex;yacc)

add_custom_command(
    OUTPUT exec
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_EXE}
    DEPENDS ${TEST_EXE}
    COMMENT "executing '${TEST_EXE}'"
    VERBATIM
)

add_custom_target(
    run_${TEST_EXE}
    DEPENDS exec
)

