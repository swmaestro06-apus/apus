cmake_minimum_required(VERSION 2.8)
project(apus)

# build output settings
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# sub directories
set(SRC_DIR src)
set(TEST_DIR test)

# lex & yacc
set(LEX lex)
set(YACC yacc)

set(LEX_OUT lex.yy.c)
set(YACC_OUT y.tab.c)

# lex
add_custom_target(
    lex
    ${LEX} -o ${LEX_OUT} ${CMAKE_SOURCE_DIR}/${SRC_DIR}/apus.l
    COMMENT "exec lex"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${SRC_DIR}
)

# yacc
add_custom_target(
    yacc
    ${YACC} -dv -o ${YACC_OUT} ${CMAKE_SOURCE_DIR}/${SRC_DIR}/apus.y
    COMMENT "exex yacc"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${SRC_DIR}
)

# source
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}")

# test
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${TEST_DIR}")
