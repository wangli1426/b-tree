cmake_minimum_required(VERSION 3.7)
project(b_tree)

set(CMAKE_CXX_STANDARD 11)

include(ExternalProject)

ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )
include_directories("${source_dir}/googletest/include"
        "${source_dir}/googlemock/include")

# Used to generate lib when there are some cpp files.
set(SOURCE_FILES
        src/main.cc
        src/insert_split_info.h)
add_library(libtree ${SOURCE_FILES})

# Generate b_tree executable
add_executable(b_tree src/main.cc)
target_link_libraries(b_tree libtree)


# Generate btree_test executable for test
set(TEST_FILES
        test/test.cc test/leaf_node_test.cc)
add_executable(btree_test ${TEST_FILES})
target_link_libraries(btree_test libgtest)
