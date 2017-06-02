cmake_minimum_required(VERSION 3.7)
project(B_plus_tree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BPlusTree.h Node.hpp LeafNode.h)
add_executable(B_plus_tree ${SOURCE_FILES})