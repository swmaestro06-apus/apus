cmake_minimum_required(VERSION 3.2)
project(apus)

# Append compile option
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(INCLUDE_DIR ../include)

set(LEX lex)
set(YACC yacc)

# Add include directory
include_directories("${INCLUDE_DIR}")

# Scan whole files under 'src' and 'include' folders, recursively.
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.cc" "*.c")
file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.hpp" "${INCLUDE_DIR}/*.hh" "${INCLUDE_DIR}/*.h")

# Build executable
add_executable(apus ${SOURCE_FILES} ${HEADER_FILES})

# lex
add_custom_target(
    lex ${LEX} -o lex.yy.cc ${CMAKE_CURRENT_SOURCE_DIR}/apus.l
    COMMENT "exec lex"
)

# yacc
add_custom_target(
    yacc ${YACC} -dv -o y.tab.cc ${CMAKE_CURRENT_SOURCE_DIR}/apus.y
    COMMENT "exex yacc"
)

add_dependencies(apus lex;yacc)
