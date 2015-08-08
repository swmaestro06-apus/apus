cmake_minimum_required(VERSION 3.2)
project(apus)

set(SRC_DIR src)
set(TEST_DIR test)

# source
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}")

# test
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${TEST_DIR}")
