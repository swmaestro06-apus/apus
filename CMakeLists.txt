cmake_minimum_required(VERSION 3.2)
project(apus)

# Append compile option
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SRC src)
set(INCLUDE include)

set(LEX lex)
set(YACC yacc)

# Add include directory
include_directories("${INCLUDE}")

# Scan whole files under 'src' and 'include' folders, recursively.
file(GLOB_RECURSE SOURCE_FILES "${SRC}/*.cpp" "${SRC}/*.cc" "${SRC}/*.c")
file(GLOB_RECURSE HEADER_FILES "${INCLUDE}/*.hpp" "${INCLUDE}/*.hh" "${INCLUDE}/*.h")

# Build executable
add_executable(apus ${SOURCE_FILES} ${HEADER_FILES})

# lex
add_custom_target(
    lex ${LEX} ${CMAKE_SOURCE_DIR}/${SRC}/apus.l
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${SRC}
    COMMENT "exec lex"
)

# yacc
add_custom_target(
    yacc ${YACC} -dv ${CMAKE_SOURCE_DIR}/${SRC}/apus.y
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${SRC}
    COMMENT "exex yacc"
)

add_dependencies(apus lex;yacc)
