cmake_minimum_required(VERSION 3.1)
project(szlab2_nhf_btree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES tests.cpp)
add_executable(szlab2_nhf_btree ${SOURCE_FILES} BTree.cpp BTree.h)