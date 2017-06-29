cmake_minimum_required (VERSION 3.1)
project (epic-battle-db)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# config
enable_testing()

# compile & link
add_library (table sources/table.cpp sources/rowStoreTable.cpp sources/columnStoreTable.cpp)
add_executable (create tests/create.cpp)
add_executable (scan tests/scan.cpp)
add_executable (materialize tests/materialize.cpp)
add_executable (insert tests/insert.cpp)

target_link_libraries (create table)
target_link_libraries (scan table)
target_link_libraries (materialize table)
target_link_libraries (insert table)

# test
#include(CTest)
add_test (createTest create)
add_test (scanTest scan)
add_test (materializeTest materialize)
add_test (insertTest insert)

# optimization flags
message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")

SET(OPT1 OFF CACHE BOOL "Enable -O1 optimizations")
SET(OPT2 OFF CACHE BOOL "Enable -O2 optimizations")
SET(OPT3 OFF CACHE BOOL "Enable -O3 optimizations")
SET(OPT4 OFF CACHE BOOL "Enable -O4 optimizations")

if (OPT1)
    message("Compile with O-flag -O1")
    set(CMAKE_CXX_FLAGS "-O1")
endif ()
if (OPT2)
    message("Compile with O-flag -O2")
    set(CMAKE_CXX_FLAGS "-O2")
endif ()
if (OPT3)
    message("Compile with O-flag -O3")
    set(CMAKE_CXX_FLAGS "-O3")
endif ()
if (OPT4)
    message("Compile with O-flag -O4")
    set(CMAKE_CXX_FLAGS "-O4")
endif ()
