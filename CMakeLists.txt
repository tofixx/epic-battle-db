cmake_minimum_required (VERSION 3.1)
project (Task1.1)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

enable_testing()

# compile & link
add_library (table sources/table.cpp sources/rowStoreTable.cpp sources/columnStoreTable.cpp)
add_executable (create tests/create.cpp)
add_executable (scan tests/scan.cpp)
add_executable (materialize tests/materialize.cpp)
add_executable (insert tests/insert.cpp)
add_executable (bench_scan tests/benchmark_scan.cpp)
add_executable (bench_insert tests/benchmark_insert.cpp)

target_link_libraries (create table)
target_link_libraries (scan table)
target_link_libraries (materialize table)
target_link_libraries (insert table)
target_link_libraries (bench_scan table)
target_link_libraries (bench_insert table)

# test
#include(CTest)
add_test (createTest create)
add_test (scanTest scan)
add_test (materializeTest materialize)
add_test (insertTest insert)
add_test (benchScanTest bench_scan)
add_test (benchInsertTest bench_insert)
