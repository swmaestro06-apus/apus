
# set google test directory
set(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gtest)

set(TEST_EXE unit_test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -std=c++0x")

# build libgtest_main.a
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(
    gtest_main
    STATIC
    ${GTEST_DIR}/gtest-all.cc
    ${GTEST_DIR}/gtest_main.cc
    ${GTEST_DIR}/gtest.h)

# scan every ".cpp" test files
file(GLOB_RECURSE TEST_SRC "*.cpp")

# scan src files
file(GLOB_RECURSE SOURCE
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cc
    ${CMAKE_SOURCE_DIR}/src/*.cpp)

## but the main.cpp
list(REMOVE_ITEM SOURCE
    ${CMAKE_SOURCE_DIR}/src/main.cpp)

# scan header files
file(GLOB_RECURSE HEADER
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.hh
    ${CMAKE_SOURCE_DIR}/include/*.hpp)

#include header directory
include_directories("${CMAKE_SOURCE_DIR}/include")

# set lex yacc files 'GENERATED'
set_source_files_properties(${CMAKE_SOURCE_DIR}/${SRC_DIR}/${LEX_OUT} GENERATED)
set_source_files_properties(${CMAKE_SOURCE_DIR}/${SRC_DIR}/${YACC_OUT} GENERATED)

# test executable
add_executable(${TEST_EXE}
    ${TEST_SRC} ${SOURCE} ${HEADER}
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

add_custom_target(run_${TEST_EXE} DEPENDS exec)

