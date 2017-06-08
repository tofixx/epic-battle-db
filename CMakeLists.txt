cmake_minimum_required (VERSION 3.1)
project (Task1.1)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (table sources/table.cpp)
add_executable (run tests/tests.cpp)
target_link_libraries (run table)

# test
#include(CTest)
#add_test (run-runs run)
