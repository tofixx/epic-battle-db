cmake_minimum_required (VERSION 3.1)
project (epuc-battle-db)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (table sources/table.cpp sources/rowStoreTable.cpp sources/columnStoreTable.cpp)
add_executable (run tests/tests.cpp)
target_link_libraries (run table)

# test
#include(CTest)
#add_test (run-runs run)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")

SET(OPT0 OFF CACHE BOOL "Some user-specified option")
SET(OPT1 OFF CACHE BOOL "Some user-specified option")
SET(OPT2 OFF CACHE BOOL "Some user-specified option")
SET(OPT3 OFF CACHE BOOL "Some user-specified option")
SET(OPT4 OFF CACHE BOOL "Some user-specified option")

if(OPT0)
    message("Compile with O-flag -O0")
    set(CMAKE_CXX_FLAGS "-O0")        ## Optimize
endif()
if(OPT1)
    message("Compile with O-flag -O1")
    set(CMAKE_CXX_FLAGS "-O1")        ## Optimize
endif()
if(OPT2)
    message("Compile with O-flag -O2")
    set(CMAKE_CXX_FLAGS "-O2")        ## Optimize
endif()
if(OPT3)
    message("Compile with O-flag -O3")
    set(CMAKE_CXX_FLAGS "-O3")        ## Optimize
endif()
if(OPT4)
    message("Compile with O-flag -O4")
    set(CMAKE_CXX_FLAGS "-O4")        ## Optimize
endif()

