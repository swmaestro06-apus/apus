
set(TEST_EXE example)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -std=c++0x")

list(APPEND TEST_SRC
    factorial.cpp
    factorial_unit_test.cpp
)

add_executable(${TEST_EXE} ${TEST_SRC})

find_library(gtest_main ${CMAKE_CURRENT_DIR}/../lib)
target_link_libraries(${TEST_EXE} gtest_main)

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
