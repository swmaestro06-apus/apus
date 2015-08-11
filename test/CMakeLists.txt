cmake_minimum_required(VERSION 3.2)

# set google test directory
set(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gtest)

# build libgtest_main.a
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(
    gtest_main
    STATIC

    ${GTEST_DIR}/gtest-all.cc
    ${GTEST_DIR}/gtest_main.cc
    ${GTEST_DIR}/gtest.h
)

add_subdirectory("./example")
