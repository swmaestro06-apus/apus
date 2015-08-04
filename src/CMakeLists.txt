
# Append compile option
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Add include directory
set(INCLUDE_DIR ../include)
include_directories("${INCLUDE_DIR}")

# Scan whole files under 'src' and 'include' folders, recursively.
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.cc" "*.c")
file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.hpp" "${INCLUDE_DIR}/*.hh" "${INCLUDE_DIR}/*.h")

set_source_files_properties(${LEX_OUT} GENERATED)
set_source_files_properties(${YACC_OUT} GENERATED)

# Build executable
add_executable(
    apus
    ${SOURCE_FILES} ${HEADER_FILES}
    ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${LEX_OUT}
    ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${YACC_OUT}
)

add_dependencies(apus lex;yacc)
